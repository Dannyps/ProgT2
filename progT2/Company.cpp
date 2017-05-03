#include "Company.h"


Empresa::Empresa(string nome, string fichCondutores, string fichLinhas) {
	this->nome = nome;
	//cout << "reading drivers\n" << flush;
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
	//cout << "construct done\n" << flush;
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

Line * Empresa::getLineByID(int id)
{
	for (unsigned i = 0; i < linhas.size(); i++) {
		if (linhas[i].getId == id) {
			return &linhas[i];
		}
	}
	return nullptr;
}

Driver * Empresa::getDriverByID(int id)
{
	for (unsigned i = 0; i < condutores.size(); i++) {
		if (condutores[i].getId == id) {
			return &condutores[i];
		}
	}
	return nullptr;
}

void Empresa::AlterLines() {
	cout << "Qual o ID da linha? ";
	{
		unsigned int id, NId;
		bool test = false, teste2 = true;
		cin >> id;
		for (unsigned int i = 0; i < linhas.size(); i++)
		{
			if (linhas[i].getId() == id) {
				test = true;
				cout << "Qual o novo id da linha? ";
				cin >> NId;
				for (unsigned int b = 0; b < linhas.size(); b++) {
					if (NId == linhas[b].getId())
					{
						cout << "Esse ID ja existe!";
						teste2 = false;
						break;
					}
				}
				if (teste2)
				{
					linhas[i].AlterLine(NId);
					break;
				}
				break;
			}
		}
		if (!test)
		{
			cout << "Esse id nao corresponde a nenhuma linha";
		}
	}
	cin.clear();
	cin.ignore(1000, '\n');
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

void const Empresa::menu_interface(int mio)
{
	switch (mio) {
	case SAVE_ALL:
		//todo
		break;
	case LOAD_FROM_DISK:
		//todo
		break;
	case LINE_SHOW:
		imprimeLinhas_m();
		break;
	case LINE_EDIT:
		AlterLines();
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
