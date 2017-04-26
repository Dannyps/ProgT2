#include <iostream>
#include "Menu.h"
#include "Bus.h"
#include "Company.h"
#include "Driver.h"
#include "Line.h"
#include "Shift.h"
#include <fstream>
#include <vector>

using namespace std;

int main(){


	vector<Driver> vDrivers;
	vector<Line> vLines;

	{ // Reading drivers
		ifstream drivers;
		string Sdrivers;
		drivers.open("condutores.txt");
		while (getline(drivers, Sdrivers))
			vDrivers.push_back(Driver(Sdrivers));
		drivers.close();
	}
	{ // Reading lines
		ifstream lines;
		string Slines;
		lines.open("linhas.txt");
		while (getline(lines, Slines))
			vLines.push_back(Line(Slines));
		lines.close();
	}

	Menu menu("Semprarrolar", NULL, NULL, 0);
	Menu* menu_gerirlinhas = menu.addOption("Gerir Linhas", '1', NULL);
	Menu* menu_gerircondutores = menu.addOption("Gerir Condutores", '2', NULL);

	menu.addOption("Gravar Alteracoes", 's', NULL, 4);
	menu.addOption("Recarregar do disco", 'r', NULL);

	// void fun(int)

	menu_gerirlinhas->addOption("Mostrar Linha", 'm', NULL);
	menu_gerirlinhas->addOption("Adicionar Linha", 'a', NULL);
	menu_gerirlinhas->addOption("Remover Linha", 'r', NULL);


	menu_gerircondutores->addOption("Mostrar Condutor", 'm', NULL);
	menu_gerircondutores->addOption("Adicionar Condutor", 'a', NULL);
	menu_gerircondutores->addOption("Remover Condutor", 'r', NULL);

	menu.print();
	menu.waitAndRun();

  return 0;
}
