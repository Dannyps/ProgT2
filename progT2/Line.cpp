#include "Line.h"
#include <sstream>
#include "time_dh.h"

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


	// Everything loaded.

	cout << this->id << ":\n\tTempo de ida e volta: " << calcTempoIdaEVolta() << endl;

	this->nAutocarrosNecessarios = (int)((double)this->calcTempoIdaEVolta() / getFrequency() + 1.0);

	cout << "\tNumero de autocarros necessarios: " << this->nAutocarrosNecessarios<<endl << endl;
}

////////////////
// get methods
////////////////


unsigned int Line::getFrequency()
{
	return this->frequency;
}

unsigned int Line::getId() const{
  return id;
}

vector<string> Line::getBusStops() const{
  return busStopList;
}

vector<int> Line::getTimings() const{
  return timesList;
}

void Line::print()
{
	cout << "==== " << this->id << " ====" << endl;
	cout << "Tempo \t| Nome" << endl;
	cout << "--------|------------------" << endl;
	for (unsigned int j = 0; j < this->getBusStops().size(); j++) {
		cout << this->getTimings().at(j) << "\t| " << this->getBusStops().at(j) << endl;
	}
	return;
}

int Line::calcTempoIdaEVolta()
{
	int res = 0;
	for (unsigned i = 0; i < this->busStopList.size(); i++) {
		res += this->timesList.at(i) + this->timesList.at(i);
		//cout << "a somar " << this->timesList.at(i) << endl;
	}

	return res;
}

vector<time_dh> Line::gerarHorario(time_dh begin, time_dh end)
{
	vector<time_dh> res;
	
	time_dh curr=begin;
	cout << "Quero gerar um horario para uma linha que comeca as " << begin << " e acaba as " << end << ".\n";
	cout << "+freq=" << begin + time_dh(0, this->frequency) << endl;
	/*while (curr < end) {

	}*/


	return res;
}

void Line::AlterLine(int id) {
	this->id = id;
}