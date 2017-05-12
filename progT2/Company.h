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
	DRIVER_REMOVE,
	TIMETABLE_LINE_SHOW,
	TIMETABLE_STOP_SHOW,
	TIMETABLE_DRIVER_SHOW,
	STOP_GET_LINES,
	MAKE_DRIVERS_SHIFTS
};

enum weekday {
	MONDAY = 0,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY
};


using namespace std;

typedef struct {
	unsigned short duration;
	Line* line;
	unsigned short busNumber;
	unsigned short wDay;
	Driver* driver;
	unsigned int jasTime;
} turno;

class Empresa {
private:

	string nome;
	string fichCondutores, fichLinhas;
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

	Line* getLineByID(unsigned id);
	Driver* getDriverByID(unsigned id);

	void AlterDrivers();
	void AlterLines();
	void EraseLines();
	void EraseDrivers();

	// menu interface methods
	void imprimeLinhas_m();
	void imprimeCondutores_m();
	void mostraHorarioLinha_m();
	void mostraHorarioParagem_m();

	// io methods
	int saveChanges(string fichCondutores, string fichLinhas);
	int loadFromDisk(string fichCondutores, string fichLinhas);

	// menu interface
	void const menu_interface(int mio);

};
