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
