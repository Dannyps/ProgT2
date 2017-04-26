#include "Driver.h"
#include "Utility.h"
#include <sstream>

Driver::Driver(string textLine){
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

unsigned int Driver::getId() const{
  return id;
}

string Driver::getName() const{
  return name;
}

unsigned int Driver::getShiftMaxDuration() const{
  return maxHours;
}

unsigned int Driver::getMaxWeekWorkingTime() const{
  return maxWeekWorkingTime;
}

unsigned int Driver::getMinRestTime() const{
  return minRestTime;
}

vector<Shift> Driver::getShifts() const{
  return shifts;
}
