#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "Shift.h"


using namespace std;

class Driver {
private:
	unsigned int id;
	string name;
	unsigned int maxHours;        // maximum duration of a shift
	unsigned int maxWeekWorkingTime;  // maximum number of hours of work in a week
	unsigned int minRestTime;     // minimum number of rest hours between shifts
	vector<Shift> shifts;         // assigned shifts
public:
	Driver(string textLine);
	// get methods
	unsigned int getId() const;
	string getName() const;
	unsigned int getShiftMaxDuration() const;
	unsigned int getMaxWeekWorkingTime() const;
	unsigned int getMinRestTime() const;
	vector<Shift> getShifts() const;
	void AlterIdCondutor(int);
	void AlterNameCondutor(string);
	void AlterHorasDiariasCondutor(int);
	void AlterHorasSemanais(int);
	void AlterHorasDescanso(int);
	~Driver();
	// other methods

	void print();

	// temp distr vars/methods

	int acc_shift = 0;
	int begin_last_rest = -1;
	int acc_week = 0;
	int next_drop = 0;

	// Get time still avaiable to work
	int getTSATW(unsigned time);

	// Get if is working
	int isWorking(unsigned time) const;

	// recalculate acc_shift

	void recalcTemps(unsigned time);


	// Operators (for debugging)
	friend ostream& operator<< (ostream& os, const Driver& d)
	{
		os << d.id << ": " << d.name;
		return os;
	}

	// other methods
	

};
