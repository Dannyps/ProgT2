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
	this->maxHours *= 60;
	this->minRestTime *= 60;
	this->maxWeekWorkingTime *= 60;

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

void Driver::print() {
	cout << setw(2) << this->id << ": " << this->name << endl;
	cout << "\t Tempo maximo por semana: " << this->maxWeekWorkingTime << endl;
	cout << "\t Tempo minimo de descanso: " << this->minRestTime << endl;
	cout << "\t Tempo maximo por turno: " << this->maxHours << endl;
	return;
}

int Driver::getTSATW(unsigned time) {
	this->recalcTemps(time);
	if (begin_last_rest == -1) {
		return min(maxWeekWorkingTime - acc_week, maxHours - acc_shift);
	}
	else {
		if (begin_last_rest + minRestTime <= time) {
			return 0;
		}
		else {
			return min(maxWeekWorkingTime - acc_week, maxHours - acc_shift);
		}
	}
}

int Driver::isWorking(unsigned time) const {
	return (time < next_drop);
}

void Driver::recalcTemps(unsigned time) {
	if (next_drop + minRestTime < time) {
		acc_shift = 0;
	}
}
