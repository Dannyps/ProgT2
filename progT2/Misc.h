#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include "Company.h"

using namespace std;

void printTime(unsigned t);
pair<bool, string> getEnterOrString();

inline int min(int a, int b);
inline int min(int a, int b, int c);
bool ordenaTurnos(turno i, turno j);

string weekntostr(unsigned int day);