#include "Company.h"


Empresa::Empresa(string nome, string fichCondutores, string fichLinhas) {
	this->nome = nome;
	this->fichCondutores = fichCondutores;
	this->fichLinhas = fichLinhas;
	this->loadFromDisk(fichCondutores, fichLinhas);

	for each (Line l in linhas)
	{
		l.gerarHorario(time_dh(06,00), time_dh(23,30));
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

vector<Line> Empresa::getLinesByStop(string Paragem)
{
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
}

Line * Empresa::getLineByID(unsigned id)
{
	for (unsigned i = 0; i < linhas.size(); i++) {
		if (linhas[i].getId() == id) {
			return &linhas[i];
		}
	}
	return nullptr;
}

Driver * Empresa::getDriverByID(unsigned id)
{
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
	if (linha == nullptr)
	{
		cout << "Esse id nao corresponde a nenhuma linha";
		return;
	}
	cout << "Qual o novo id da linha? ";
	cin >> NId;
	if (getLineByID(NId) != nullptr)
	{
		cout << "Esse ID ja existe!";
		return;
	}
	
	linha->AlterLine(NId);
}

void Empresa::AlterDrivers() {
	int id, NId;
	cout << "Qual o Id do condutor que quer alterar? ";
	cin >> id;
	Driver* condutor = getDriverByID(id);
	if (condutor == nullptr)
	{
		cout << "Esse id nao corresponde a nenhum condutor";
		return;
	}
	cout << "Qual o novo nome [" << getNome() << "]? " ;
	cin >> NId;
	if (getDriverByID(NId) != nullptr)
	{
		cout << "Esse ID ja existe!";
		return;
	}
	condutor->AlterIdCondutor(NId);
	return;                                                    // Apenas altera o ID
}


////////////////////////////
// outros metodos
///////////////////////////

void Empresa::imprimeLinhas_m()
{
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
	else{
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

void const Empresa::menu_interface(int mio)
{
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
	case LINE_EDIT:
		AlterLines();
		cin.clear(); cin.ignore(1000, '\n'); //clear buffer
	}
		
	return;
}


Line & Empresa::getLineById(unsigned int id){	

	for (unsigned i = 0; this->linhas.size(); i++) {

		if (this->linhas.at(i).getId() == id) {

			return this->linhas.at(i);

		}

	}



	throw -1;

}

int Empresa::saveChanges(string fichCondutores, string fichLinhas) {
	ofstream file(fichLinhas);
	cout << "Aberto para escrita: " << fichLinhas << ". " << file.good() << endl;
	for (unsigned int i = 0; i < linhas.size(); i++) {
		Line cur = linhas[i];
		file << cur.getId() << " ; " << cur.getFrequency() << " ; ";
		size_t nParagens = cur.getBusStops().size();
		for (unsigned j = 0; j<nParagens; j++)
		{
			if (j + 1 == nParagens)
				file << cur.getBusStops().at(j);
			else
				file << cur.getBusStops().at(j) << ", ";
		}
		file << "; ";
		for (unsigned j = 1; j<nParagens; j++)
		{
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

int Empresa::loadFromDisk(string fichCondutores, string fichLinhas)
{
	{ // Reading drivers
		ifstream drivers;
		string Sdrivers;
		drivers.open(fichCondutores);
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

