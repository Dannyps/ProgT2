#include "Company.h"
#include "misc.h"
#include <algorithm>
#include "Misc.h"

Empresa::Empresa(string nome, string fichCondutores, string fichLinhas) {
	this->nome = nome;
	this->fichCondutores = fichCondutores;
	this->fichLinhas = fichLinhas;
	this->loadFromDisk(fichCondutores, fichLinhas);

	for each (Line l in linhas) {
		l.gerarHorario(6 * 60, 23 * 60 + 30 - 1);
		cout << "O autocarro passa " << l.getHorario().size() << " vezes em qualquer paragem.\n";
	}

}

////////////////////////////////
// metodos get
///////////////////////////////
string Empresa::getNome() const {
	return this->nome;
}

//////////////////////////////
// metodos set
/////////////////////////////

vector<Line> Empresa::getLinesByStop(string Paragem) {
	vector<Line> res;

	for (unsigned int i = 0; i < linhas.size(); i++) {
		for (unsigned int j = 0; j < linhas[i].getBusStops().size(); j++) {
			if (linhas[i].getBusStops().at(j) == Paragem)
				res.push_back(linhas[i]);
		}
	}

	return res;
}


////////////////////////////
// outros metodos
///////////////////////////


void Empresa::distribuiServico() {
	if (distrDone)
		return;
	// vamos arranjar primeiro uma lista com todos os turnos a preencher;
	//vector<turno> turnos;
	cout << endl;
	unsigned int day = MONDAY;
	while (day != SATURDAY) {
		for (unsigned j=0;j<linhas.size();j++) {
			Line * l = &linhas[j];
			for (int i = 0; i < l->getHorario().size(); i++) {
				turno temp;
				temp.line = l;
				temp.duration = l->getStopTime(l->getBusStops().back()) * 2; // ir e vir
				temp.busNumber = i;
				temp.wDay = day;
				temp.driver = NULL;
				temp.jasTime = (day * 24 * 60) + (06 * 60) + i*l->getFrequency();
				//cout << l->getId() << " jastime: " << temp.jasTime << endl;
				turnos.push_back(temp);
			}
		}
		day++;
	}

	cout << "Ha' " << turnos.size() << " turnos para preencher.\n";

	// Ordena do primeiro para o último (numa linha temporal).
	std::sort(turnos.begin(), turnos.end(), ordenaTurnos);

	int yy = 0;
	for (unsigned i = 0; i < turnos.size(); i++) {
		turno* t = &turnos[i];
		for (unsigned j=0;j<condutores.size();j++){
			Driver *d = &condutores[j];
			/*cout << "Pode " << d->getName() << " conduzir " << t->line->getId() << "?\n";
			cout << "Pode conduzir " << d->getTSATW(t->jasTime) << "minutos. A linha demora " << t->duration << ".\n";*/
			yy++;
			if (!d->isWorking(t->jasTime) && t->duration < d->getTSATW(t->jasTime)) {// se o condutor puder conduzir o tempo necessário para o turno
				t->driver = d;
				d->acc_shift += t->duration;
				d->acc_week += t->duration;
				d->next_drop = t->jasTime + t->duration;
				break;
			}
		}
		//cout << *t << endl;
	}
	distrDone = 1;
}

Line * Empresa::getLineByID(unsigned id) {
	for (unsigned i = 0; i < linhas.size(); i++) {
		if (linhas[i].getId() == id) {
			return &linhas[i];
		}
	}
	return nullptr;
}

Driver * Empresa::getDriverByID(unsigned id) {
	for (unsigned i = 0; i < condutores.size(); i++) {
		if (condutores[i].getId() == id) {
			return &condutores[i];
		}
	}
	return nullptr;
}

void Empresa::AlterLines() {
	cout << "Qual o ID da linha? ";

	unsigned int id, NId;
	cin >> id;
	Line* linha = getLineByID(id);
	if (linha == nullptr) {
		cout << "Esse id nao corresponde a nenhuma linha.";
		return;
	}
	cout << "Qual o novo id da linha? ";
	cin >> NId;
	if (getLineByID(NId) != nullptr) {
		cout << "Esse ID ja existe!";
		return;
	}

	linha->AlterLine(NId);
}

void Empresa::AlterDrivers() {
	int id, NId, NHorasDiarias, NHorasSemanais, NHorasPausa;
	string NNome;
	cout << "Qual o Id do condutor que quer alterar? ";
	cin >> id;
	Driver* condutor = getDriverByID(id);
	if (condutor == nullptr) {
		cout << "Esse id nao corresponde a nenhum condutor.";
		return;
	}
	cout << "Qual o novo Id? ";
	cin >> NId;
	if (getDriverByID(NId) != nullptr) {
		cout << "Esse ID ja existe!";
		return;
	}
	cout << "Qual o novo nome [" << getNome() << "]? ";
	cin >> NNome;


	cout << "Qual o numero de horas que pode trabalhar por dia? ";
	cin >> NHorasDiarias;
	if (NHorasDiarias <= 0 || NHorasDiarias > 24 || cin.fail()) {
		cout << "Nao e possivel, nao houve alteracoes.";
		return;
	}
	cout << "Qual o numero maximo de horas semanais de trabalho? ";
	cin >> NHorasSemanais;
	if (NHorasSemanais <= 0 || NHorasSemanais > 168 || cin.fail()) {
		cout << "Nao e possivel, nao houve alteracoes.";
		return;
	}
	cout << "Quantas horas e que descanca entre turnos? ";
	cin >> NHorasPausa;
	if (cin.fail() || NHorasPausa <= 0) {
		cout << "Nao e possivel, nao houve alteracoes.";
		return;
	}
	condutor->AlterIdCondutor(NId);
	condutor->AlterNameCondutor(NNome);
	condutor->AlterHorasDiariasCondutor(NHorasDiarias);
	condutor->AlterHorasSemanais(NHorasSemanais);
	condutor->AlterHorasDescanso(NHorasPausa);
	return;
}


////////////////////////////
// outros metodos
///////////////////////////

void Empresa::adicionarLinha_m() {
	vector<string> stopnames;
	vector<int> times;
	unsigned short numero, freq;
	cout << "Insira o numero da nova linha.\n(0 gera um numero automaticamente): ";
	cin >> numero;
	if (numero <= 0) {
		numero = encontraNumeroDisponivel(linhas);
	}
	else if (getLineByID(numero) != NULL) {
		cerr << "O numero especificado ja' existe!\n";
		return;
	}
	cout << "Numero a adicionar: " << numero << endl;
	cout << "Insira a frequencia da nova linha: ";
	cin >> freq;

	if (cin.fail()) {
		cout << "Ocorreu um erro de leitura.\n";
		cin.clear();
		return;
	}
	cin.ignore(100, '\n');
	for (unsigned int i = 0;; i++) {
		cout << "Insira o nome da paragem " << i << " (Ctrl+Z termina): ";
		string stopname; unsigned short tempo;
		if (!getline(cin, stopname)) {
			break;
		}
		if (i == 0) {
			cout << "Tempo de viagem da primeira paragem introduzido automaticamente: 0.\n";
			tempo = 0;
		}
		else {
			cout << "Insira o tempo de viagem para esta paragem: ";
			cin >> tempo;
			getchar(); //remove ENTER from buffer
		}
		stopnames.push_back(stopname);
		times.push_back(tempo);
		cout << endl;
	}

	//Leitura concluída.
	string temp;
	for each (string str in stopnames) {
		temp += " ; " + str;
	}
	for each (int n in times) {
		temp += " ; " + to_string(n);
	}

	linhas.push_back(Line(to_string(numero) + " ; " + to_string(freq) + temp));

	cout << "Linha adicionada com sucesso!\n";
	cin.clear();
}

void Empresa::adicionarCondutor_m() {
	unsigned short numero, nMHT, nMHS, nMHD;
	cout << "Insira o numero do novo condutor.\n(0 gera um numero automaticamente): ";
	cin >> numero;
	if (numero <= 0) {
		numero = encontraNumeroDisponivel(condutores);
	}
	else if (getDriverByID(numero) != NULL) {
		cerr << "O numero especificado ja' existe!\n";
		return;
	}
	cout << "Numero a adicionar: " << numero << endl;
	cout << "Insira o nome do novo condutor: ";
	string nome;
	getchar(); getline(cin, nome);
	cout << "Insira o numero de horas consecutivas por dia (turno): ";
	cin >> nMHT;
	cout << "Insira o numero de horas maximo por semana: ";
	cin >> nMHS;
	cout << "Insira o numero de horas minimo de descanso: ";
	cin >> nMHD;

	//Leitura concluída.

	condutores.push_back(Driver(to_string(numero) + " ; " + nome + " ; " + to_string(nMHT) + " ; " + to_string(nMHS) + " ; " + to_string(nMHD)));

	cout << "Condutor adicionado com sucesso!\n";
	cin.ignore(100, '\n');
}

void Empresa::removerLinha_m() {
	cout << "Indique o numero da linha a remover: ";
	unsigned short n;
	cin >> n;
	Line* lin = getLineByID(n);
	if (lin == NULL) {
		cout << "A linha especificada nao foi encontrada!\n";
		return;
	}
	cout << "Esta' prestes a apagar a seguinte linha:\n";
	cout << *lin;
	cout << "\nConfirme (S/N) ";
	char conf;
	cin >> conf; cin.ignore(100, '\n');
	if (conf == 'S' || conf == 's') {
		for (unsigned int i = 0; i < linhas.size(); i++) {
			if (&linhas[i] == lin) {
				linhas.erase(linhas.begin() + i);
			}
		}
		cout << "Linha removida.\n";
	}
	else {
		cout << "Linha nao removida.\n";
	}
}

void Empresa::removerCondutor_m() {
	cout << "Indique o numero do condutor a remover: ";
	unsigned short n;
	cin >> n;
	Driver* cond = getDriverByID(n);
	if (cond == NULL) {
		cout << "O condutor especificado nao foi encontrado!\n";
		return;
	}
	cout << "Esta' prestes a apagar o seguinte condutor:\n";
	cout << *cond;
	cout << "\nConfirme (S/N) ";
	char conf;
	cin >> conf; cin.ignore(100, '\n');
	if (conf == 'S' || conf == 's') {
		for (unsigned int i = 0; i < condutores.size(); i++) {
			if (&condutores[i] == cond) {
				condutores.erase(condutores.begin() + i);
			}
		}
		cout << "Condutor removido.\n";
	}
	else {
		cout << "Condutor nao removido.\n";
	}
}

void Empresa::imprimeLinhas_m() {
	cout << "Linhas disponiveis: ";
	for (unsigned int i = 0; i < linhas.size(); i++) {
		cout << linhas[i].getId() << " ";
	}
	cout << endl;

	cout << "Indique a linha a imprimir (* imprime todas as linhas): ";
	string opt;
	cin >> opt;
	cin.ignore(100, '\n');
	if (opt == "*") {
		for (unsigned int i = 0; i < linhas.size(); i++) {
			linhas[i].print();
			cout << endl;
		}
		return;
	}
	else if (!isdigit(opt[0])) {
		cout << "Valor invalido!\n";
		return;
	}
	else {
		for (unsigned int i = 0; i < linhas.size(); i++) {
			if (stoi(opt) == linhas[i].getId()) {
				linhas[i].print();
				cout << endl;
				return;
			}
		}
	}

	cout << "Linha nao encontrada!\n";
	return;
}

void Empresa::imprimeCondutores_m() {

	cout << "Condutores disponiveis: ";
	for (unsigned int i = 0; i < condutores.size(); i++) {
		cout << condutores[i].getId() << " ";
	}
	cout << endl;

	cout << "Indique o condutor a imprimir (* imprime todos os condutores): ";
	string opt;
	cin >> opt; cin.ignore(100, '\n');
	if (opt == "*") {
		for (unsigned int i = 0; i < condutores.size(); i++) {
			condutores[i].print();
			cout << endl;
		}
		return;
	}
	else {
		for (unsigned int i = 0; i < condutores.size(); i++) {
			if (condutores[i].getId() == stoi(opt)) {
				condutores[i].print();
				cout << endl;
				return;
			}
		}
	}

	cout << "Condutor nao encontrado!\n";
	return;
}

void Empresa::mostraHorarioLinha_m() {
	cout << "Linhas disponiveis: ";
	for (unsigned int i = 0; i < linhas.size(); i++) {
		cout << linhas[i].getId() << " ";
	}
	cout << endl;

	cout << "Indique a linha a imprimir: ";
	string opt;
	cin >> opt;
	cin.ignore(100, '\n');
	if (!isdigit(opt[0])) {
		cout << "Valor invalido!\n";
		return;
	}
	else {
		for (unsigned int i = 0; i < linhas.size(); i++) {
			if (stoi(opt) == linhas[i].getId()) {
				linhas[i].printTimeTable();
				cout << endl;
				return;
			}
		}
	}

	cout << "Linha nao encontrada!\n";
	return;
}

void Empresa::mostraHorarioParagem_m() {
	cout << "Indique a paragem a imprimir: ";
	string opt;
	getline(cin, opt);
	//cin.ignore(100, '\n');
	vector<Line> res = getLinesByStop(opt);
	if (res.size() == 0) {
		cout << "A paragem nao foi encontrada!\n";
		return;
	}
	else {
		for each (Line l in res) {
			l.printTimeTable(opt);
		}

	}
	return;
}

void Empresa::mostraLinhasByParagem_m() {
	cout << "Indique a paragem a procurar: ";
	string opt;
	getline(cin, opt);
	//cin.ignore(100, '\n');
	vector<Line> res = getLinesByStop(opt);
	if (res.size() == 0) {
		cout << "A paragem nao foi encontrada!\n";
		return;
	}
	else {
		for each (Line l in res) {
			l.print();
		}

	}
	return;
}

void Empresa::mostraHorarioDeCondutor_m() {
	cout << "Indique o numero do condutor a procurar: ";
	string opt;
	getline(cin, opt);
	//cin.ignore(100, '\n');
	Driver* d = getDriverByID(stoi(opt));
	cout << d->getName() << endl;
	int wd = -1;
	for each(turno t in turnos) {
		if (t.driver == d) {
			//if (wd == -1) {
			//	wd = t.wDay;
			//}
			if (wd != t.wDay) {
				cout << endl << weekntostr(t.wDay) << endl;
				wd = t.wDay;
			}
			cout << "\t"; printTime(t.jasTime); cout << "\t Linha: " << t.line->getId() << "\tLocalizacao: " << t.line->getBusStops().front() << endl;
		}
	}

	return;
}

void Empresa::mostraHorarioSemCondutor_m() {
	cout << "Turnos sem condutores: " << endl;
	int wd = -1;
	for each(turno t in turnos) {
		if (t.driver == NULL) {
			if (wd != t.wDay) {
				cout << endl << weekntostr(t.wDay) << endl;
				wd = t.wDay;
			}
			cout << "\t"; printTime(t.jasTime); cout << "\t Linha: " << t.line->getId() << "\tLocalizacao: " << t.line->getBusStops().front() << endl;
		}
	}

	return;
}

void const Empresa::menu_interface(int mio) {
	switch (mio) {
	case SAVE_ALL:
		saveChanges(this->fichCondutores, this->fichLinhas);
		break;
	case LOAD_FROM_DISK:
		loadFromDisk(this->fichCondutores, this->fichLinhas);
		break;
	case LINE_SHOW:
		imprimeLinhas_m();
		break;
	case DRIVER_SHOW:
		imprimeCondutores_m();
		break;
	case LINE_EDIT:
		AlterLines();
		cin.clear(); cin.ignore(1000, '\n'); //clear buffer
		break;
	case TIMETABLE_LINE_SHOW:
		mostraHorarioLinha_m();
		break;
	case TIMETABLE_STOP_SHOW:
		mostraHorarioParagem_m();
		break;
	case DRIVER_EDIT:
		AlterDrivers();
		cin.clear(); cin.ignore(1000, '\n'); //clear buffer
		break;
	case MAKE_DRIVERS_SHIFTS:
		distribuiServico();
		break;
	case STOP_GET_LINES:
		mostraLinhasByParagem_m();
		break;
	case TIMETABLE_DRIVER_SHOW:
		mostraHorarioDeCondutor_m();
		break;
	case TIMETABLE_NO_DRIVER_SHOW:
		mostraHorarioSemCondutor_m();
		break;
	case LINE_ADD:
		adicionarLinha_m();
		break;
	case DRIVER_ADD:
		adicionarCondutor_m();
		break;
	case LINE_REMOVE:
		removerLinha_m();
		break;
	case DRIVER_REMOVE:
		removerCondutor_m();
		break;
	}

	return;
}

/*
Line & Empresa::getLineById(unsigned int id) {
	for (unsigned i = 0; this->linhas.size(); i++) {
		if (this->linhas.at(i).getId() == id) {
			return this->linhas.at(i);
		}
	}

	throw - 1;
}*/

int Empresa::saveChanges(string fichCondutores, string fichLinhas) {
	ofstream file(fichLinhas);
	cout << "Aberto para escrita: " << fichLinhas << ". " << file.good() << endl;
	for (unsigned int i = 0; i < linhas.size(); i++) {
		Line cur = linhas[i];
		file << cur.getId() << " ; " << cur.getFrequency() << " ; ";
		size_t nParagens = cur.getBusStops().size();
		for (unsigned j = 0; j < nParagens; j++) {
			if (j + 1 == nParagens)
				file << cur.getBusStops().at(j);
			else
				file << cur.getBusStops().at(j) << ", ";
		}
		file << "; ";
		for (unsigned j = 1; j < nParagens; j++) {
			if (j + 1 == nParagens)
				file << cur.getTimings().at(j);
			else
				file << cur.getTimings().at(j) << ", ";
		}

		if (i + 1 != linhas.size())
			file << endl;
	}

	file.close();


	ofstream file2(fichCondutores);
	for (unsigned int i = 0; i < condutores.size(); i++) {
		Driver cur = condutores.at(i);
		file << cur.getId() << " ; " << cur.getName() << " ; " << cur.getShiftMaxDuration() << " ; " << cur.getMaxWeekWorkingTime() << " ; " << cur.getMinRestTime();
		if (i + 1 != condutores.size())
			file << endl;
	}

	file2.close();

	return 0;
}

int Empresa::loadFromDisk(string fichCondutores, string fichLinhas) {
	{ // Reading drivers
		ifstream drivers;
		string Sdrivers;
		drivers.open(fichCondutores);
		cout << drivers.good();
		while (getline(drivers, Sdrivers))
			condutores.push_back(Driver(Sdrivers));
		drivers.close();
	}
	//cout << "reading lines\n" << flush;
	{ // Reading lines
		ifstream lines;
		string Slines;
		lines.open(fichLinhas);
		while (getline(lines, Slines))
			linhas.push_back(Line(Slines));
		lines.close();
	}

	return 0;
}

ostream & operator<<(ostream & os, turno t) {
	printTime(t.jasTime);  cout << " Duracao: " << t.duration << endl;
	if (t.driver == NULL)
		cout << "sem condutor" << endl;
	else
		cout << "Condutor: " << t.driver->getName() << endl;
	
	return os;
}
