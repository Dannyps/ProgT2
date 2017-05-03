#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

#include "Line.h"
#include "Driver.h"


enum mio // menu interface options
{
	SAVE_ALL,
	LOAD_FROM_DISK,
	LINE_SHOW,
	LINE_ADD,
	LINE_EDIT,
	LINE_REMOVE,
	DRIVER_SHOW,
	DRIVER_ADD,
	DRIVER_EDIT,
	DRIVER_REMOVE
};

using namespace std;

class Empresa{
 private:
	string nome;
	vector<Driver> condutores;
	vector<Line> linhas;
 public:
		Empresa(string nome, string fichCondutores, string fichLinhas);
	// metodos get
	string getNome() const;
	Line& getLineById(unsigned int id);
	// metodos set
	// outros metodos
	vector<Line> getLinesByStop(string Paragem);
	void distribuiServico(); // funcao que implementa a afectacao de servico

	void AlterLines();


	void imprimeLinhas_m();

	// menu interface
	void const menu_interface(int mio);

};
