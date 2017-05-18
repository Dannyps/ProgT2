#include "Misc.h"

void printTime(unsigned t) {
	cout << setfill('0') << setw(2) << t / 60 % 24 << ":";
	cout << setfill('0') << setw(2) << t % 60;
}

pair<bool, string> getEnterOrString() {
	pair<bool, string> res;
	char c;
	c = getchar();
	if (c == '\n') {
		res.first = true;
		return res;
	}
	else {
		string aux;
		getline(cin, aux);
		res.first = false;
		res.second = c + aux;
		return res;
	}
}

inline int min(int a, int b) {
	if (a < b)
		return a;
	else
		return b;
}

inline int min(int a, int b, int c) {
	int min = a;
	(min > b) && (min = b);
	(min > c) && (min = c);
	return min;
}

bool ordenaTurnos(turno i, turno j) {
	if (i.busNumber < j.busNumber) {
		return false;
	}
	else
		return i.jasTime < j.jasTime;
}

bool ordenaTurnos2(turno i, turno j) {
	if (i.wDay >= j.wDay) {
		return false;
	}
	else
		return true;
}

string weekntostr(unsigned int day) {
	string res;
	switch (day) {
	case MONDAY:
		res = "segunda-feira";
		break;
	case TUESDAY:
		res = "terca-feira";
		break;
	case WEDNESDAY:
		res = "quarta-feira";
		break;
	case THURSDAY:
		res = "quinta-feira";
		break;
	case FRIDAY:
		res = "sexta-feira";
		break;
	case SATURDAY:
		res = "sabado";
		break;
	case SUNDAY:
		res = "domingo";
		break;
	}
	return res;
}
