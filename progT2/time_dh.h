#pragma once

#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

class time_dh {
private:
	unsigned short hour;
	unsigned short minutes;
	void normalize();
public:
	time_dh(int hours, int minutes);
	time_dh(int minutes);
	unsigned short getHour();
	unsigned short getMinutes();

	friend ostream& operator<<(ostream& os, const time_dh tm);
	friend time_dh operator+(const time_dh& a, const time_dh& b);
	
	int operator<(const time_dh& a);

	//time_dh operator+()
};