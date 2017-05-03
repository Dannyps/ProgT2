#include "Line.h"
#include <sstream>

Line::Line(string textLine){
	//cout << "got: " << textLine << endl << flush;
	size_t inicio = 0, fim = 0;
	char sep;
	istringstream iss(textLine);
	iss >> this->id >> sep >> this->frequency >> sep;
	string linhaFicheiro;
	getline(iss, linhaFicheiro, ';');

	linhaFicheiro = linhaFicheiro.substr(1);
	inicio = 1;
	while (1) {
		fim = linhaFicheiro.find(',');
		string stopName = linhaFicheiro.substr(0, fim);
		this->busStopList.push_back(stopName);
		this->timesList.push_back(0);
		linhaFicheiro = linhaFicheiro.substr(fim + 2);
		//cout << fim << " == " << string::npos << ": " << (fim == string::npos) << endl << flush;
		if (fim == string::npos)
			break;
	}

	this->timesList[0] = 0;
	for (unsigned int i = 1; i < this->busStopList.size(); i++) {
		iss >> this->timesList[i];
		if (i != this->busStopList.size() - 1)
			iss >> sep;
	}
}

////////////////
// get methods
////////////////


unsigned int Line::getId() const{
  return id;
}

vector<string> Line::getBusStops() const{
  return busStopList;
}

vector<int> Line::getTimings() const{
  return timesList;
}

void Line::AlterLine(int id) {
	this->id = id;
}