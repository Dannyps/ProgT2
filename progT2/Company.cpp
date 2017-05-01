#include "Company.h"


Empresa::Empresa(string nome, string fichCondutores, string fichLinhas){
	
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
string Empresa::getNome() const{
  return this->nome;
}

//////////////////////////////
// metodos set
/////////////////////////////

////////////////////////////
// outros metodos
///////////////////////////
void Empresa::distribuiServico(){
}
