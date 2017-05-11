#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

void printTime(unsigned t) {
	cout << setfill('0') << setw(2) << t / 60 << ":";
	cout << setfill('0') << setw(2) << t % 60;
}