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
	MAKE_DRIVERS_SHIFTS,
	TIMETABLE_NO_DRIVER_SHOW
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

ostream & operator<<(ostream &os, turno t);

class Empresa {
private:

	string nome;
	string fichCondutores, fichLinhas;
	vector<Driver> condutores;
	vector<Line> linhas;
	vector<turno> turnos;
public:
	Empresa(string nome, string fichCondutores, string fichLinhas);
	// metodos get
	string getNome() const;
	//Line& getLineById(unsigned int id);
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

	template<class T>
	inline int encontraNumeroDisponivel(T arg);

	// menu interface methods
	void adicionarLinha_m();
	void adicionarCondutor_m();

	void removerLinha_m();
	void removerCondutor_m();

	void imprimeLinhas_m();
	void imprimeCondutores_m();
	void mostraHorarioLinha_m();
	void mostraHorarioParagem_m();
	void mostraLinhasByParagem_m();
	void mostraHorarioDeCondutor_m();
	void mostraHorarioSemCondutor_m();

	// io methods
	int saveChanges(string fichCondutores, string fichLinhas);
	int loadFromDisk(string fichCondutores, string fichLinhas);

	// menu interface
	void const menu_interface(int mio);

	//misc
	bool distrDone = 0;

};

template<class T>
inline int Empresa::encontraNumeroDisponivel(T arg) {
	unsigned int min = 0;
	for (unsigned int i = 0; i < arg.size(); i++) {
		if (arg[i].getId() >= min) {
			min = arg[i].getId() + 1;
		}
	}
	return min;
}
