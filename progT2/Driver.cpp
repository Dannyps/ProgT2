#include "Driver.h"
#include "Utility.h"
#include <sstream>

Driver::Driver(string textLine) {
	char sep;
	istringstream iss(textLine);
	iss >> this->id;
	iss >> sep;
	string linhaFicheiro;
	getline(iss, linhaFicheiro, ';');
	linhaFicheiro = trim(linhaFicheiro); //remover espa�os antes e depois.
	this->name = linhaFicheiro;
	iss >> this->maxHours >> sep >> this->maxWeekWorkingTime >> sep >> this->minRestTime;
}

//////////////
// get methods
//////////////

unsigned int Driver::getId() const {
	return id;
}

string Driver::getName() const {
	return name;
}

unsigned int Driver::getShiftMaxDuration() const {
	return maxHours;
}

unsigned int Driver::getMaxWeekWorkingTime() const {
	return maxWeekWorkingTime;
}

unsigned int Driver::getMinRestTime() const {
	return minRestTime;
}

vector<Shift> Driver::getShifts() const {
	return shifts;
}


void Driver::AlterIdCondutor(int NId) {
	this->id = NId;
}
void Driver::AlterNameCondutor(string NNome) {
	this->name = NNome;
}
void Driver::AlterHorasDiariasCondutor(int NHorasDiarias) {
	this->maxHours = NHorasDiarias;
}
void Driver::AlterHorasSemanais(int NHSemanais) {
	this->maxWeekWorkingTime = NHSemanais;
}
void Driver::AlterHorasDescanso(int NDescanso) {
	this->minRestTime = NDescanso;
}

Driver::~Driver() {
}

void Driver::print()
{
	cout << setw(2) << this->id << ": " << this->name << endl;
	cout << "\t Tempo maximo por semana: " << this->maxWeekWorkingTime << endl;
	cout << "\t Tempo minimo de descanso: " << this->minRestTime << endl;
	cout << "\t Tempo maximo por turno: " << this->maxHours << endl;
	return;
}

int Driver::getTSATW() const {
	return 0;
}

