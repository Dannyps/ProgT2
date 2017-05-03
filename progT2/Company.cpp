#include "Company.h"


Empresa::Empresa(string nome, string fichCondutores, string fichLinhas) {

	cout << "reading drivers\n" << flush;
	{ // Reading drivers
		ifstream drivers;
		string Sdrivers;
		drivers.open(fichCondutores);
		while (getline(drivers, Sdrivers))
			condutores.push_back(Driver(Sdrivers));
		drivers.close();
	}
	cout << "reading lines\n" << flush;
	{ // Reading lines
		ifstream lines;
		string Slines;
		lines.open(fichLinhas);
		while (getline(lines, Slines))
			linhas.push_back(Line(Slines));
		lines.close();
	}
	cout << "construct done\n" << flush;
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
		for (unsigned int j = 0; j < linhas[i].getBusStops().size(); j++){
			if (linhas[i].getBusStops().at(j) == Paragem)
				res.push_back(linhas[i]);
		}
	}

	return res;
}

////////////////////////////
// outros metodos
///////////////////////////
void Empresa::distribuiServico(){
}
