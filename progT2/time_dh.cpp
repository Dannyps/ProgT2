#include "time_dh.h"

void time_dh::normalize()
{
	hour += minutes % 60;
	minutes %= 60;
}

time_dh::time_dh(int hours, int minutes)
{
	this->hour = hours;
	this->minutes = minutes;
}

time_dh::time_dh(int minutes)
{
	this->minutes = minutes;
}

unsigned short time_dh::getHour()
{
	return hour;
}

unsigned short time_dh::getMinutes()
{
	return minutes;
}

int time_dh::operator<(const time_dh & a)
{
	return 0;
}

ostream & operator<<(ostream & os, const time_dh tm)
{
	os << setfill('0') << setw(2) << tm.hour << ":";
	os << setfill('0') << setw(2) << tm.minutes;
	return os;
}

time_dh operator+(const time_dh & a, const time_dh & b)
{
	unsigned short hour = a.hour + b.hour;
	unsigned short minutes = a.minutes + b.minutes;
	
	time_dh res(hour, minutes);
	
	res.normalize();

	return res;
}
