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

	string a = "teste";

	cout << "npos: " << string::npos << endl;
	cout << "fres: " << a.find(',') << endl;
	cout << (string::npos==a.find(',')) << endl;

//	exit(-1);


	Empresa emp = Empresa("Semprarrolar", "condutores.txt", "linhas.txt");

	Menu menu(emp.getNome(), NULL, NULL, 0);
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
