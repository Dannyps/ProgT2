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

	Menu menu(emp.getNome(), NULL, NULL, 0);
	Menu* menu_gerirlinhas = menu.addOption("Gerir Linhas", '1', NULL);
	Menu* menu_gerircondutores = menu.addOption("Gerir Condutores", '2', NULL);

	menu.addOption("Gravar Alteracoes", 's', menu_interface, SAVE_ALL);
	menu.addOption("Recarregar do disco", 'r', menu_interface, LOAD_FROM_DISK);
	


	menu_gerirlinhas->addOption("Mostrar Linha", 'm', menu_interface, LINE_SHOW);
	menu_gerirlinhas->addOption("Adicionar Linha", 'a', menu_interface, LINE_ADD);
	menu_gerirlinhas->addOption("Editar Linha", 'e', menu_interface, LINE_EDIT);
	menu_gerirlinhas->addOption("Remover Linha", 'r', menu_interface, LINE_REMOVE);


	menu_gerircondutores->addOption("Mostrar Condutor", 'm', menu_interface, DRIVER_SHOW);
	menu_gerircondutores->addOption("Adicionar Condutor", 'a', menu_interface, DRIVER_ADD);
	menu_gerircondutores->addOption("Remover Condutor", 'r', menu_interface, DRIVER_REMOVE);

	menu.print();
	menu.waitAndRun();

  return 0;
}

void const menu_interface(int mio)
{
	emp.menu_interface(mio);
	return;
}
