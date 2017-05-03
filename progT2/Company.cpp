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

void Empresa::AlterLines() {
	cout << "Qual o ID da linha?";
	{
		unsigned int id, NId;
		bool test = false;
		cin >> id;
		for (unsigned int i = 0; i < linhas.size(); i++)
		{
			if (linhas[i].getId() == id)
			{
				test = true;
				cout << "Qual o novo id da linha?";
				cin >> NId;
				linhas[i].AlterLine(NId);
				break;
			}
		}

		if (!test)
		{
			cout << "Esse id nao corresponde a nenhuma linha";
		}
	}
}