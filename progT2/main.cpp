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

void const menu_interface(int mio);

Empresa emp = Empresa("Semprarrolar", "condutores.txt", "linhas.txt");


int main(){

	void const (*mi)(int a)=menu_interface; /// define mi


	exit(-1);
	Menu menu(emp.getNome(), NULL, NULL, 0);
	Menu* menu_gerirlinhas =		menu.addOption("Gerir Linhas", '1', NULL);
	Menu* menu_gerircondutores =	menu.addOption("Gerir Condutores", '2', NULL);
	Menu* menu_gerirhorarios =		menu.addOption("Gerir Horarios", '3', NULL);


	menu.addOption("Gravar Alteracoes", 's', mi, SAVE_ALL);
	menu.addOption("Recarregar do disco", 'r', mi, LOAD_FROM_DISK);
	


	menu_gerirlinhas	->	addOption("Mostrar Linha", 'm', mi, LINE_SHOW);
	menu_gerirlinhas	->	addOption("Adicionar Linha", 'a', mi, LINE_ADD);
	menu_gerirlinhas	->	addOption("Editar Linha", 'e', mi, LINE_EDIT);
	menu_gerirlinhas	->	addOption("Remover Linha", 'r', mi, LINE_REMOVE);


	menu_gerircondutores->	addOption("Mostrar Condutor", 'm', mi, DRIVER_SHOW);
	menu_gerircondutores->	addOption("Adicionar Condutor", 'a', mi, DRIVER_ADD);
	menu_gerircondutores->	addOption("Editar Condutor", 'e', mi, DRIVER_EDIT);
	menu_gerircondutores->	addOption("Remover Condutor", 'r', mi, DRIVER_REMOVE);

	menu_gerirhorarios	->	addOption("Ver horario por linha", 'l', mi, DRIVER_REMOVE);
	menu_gerirhorarios	->	addOption("Ver horario por paragem", 'p', mi, DRIVER_REMOVE);
	menu_gerirhorarios	->	addOption("Ver horario por condutor", 'c', mi, DRIVER_REMOVE);


	menu.print();
	menu.waitAndRun();

  return 0;
}

void const menu_interface(int mio)
{
	emp.menu_interface(mio);
	return;
}
