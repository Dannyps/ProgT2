#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "Shift.h"


using namespace std;

class Driver{
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
	// other methods

	void print();


	
	
	// Operators (for debugging)
	friend ostream& operator<< (ostream& os, const Driver& d)
	{
		os << d.id << ": " << d.name;
		return os;
	}

  // outher methods

};
