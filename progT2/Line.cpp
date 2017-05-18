#include "Line.h"
#include <sstream>
#include "Misc.h"

Line::Line(string textLine) {
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

	this->nAutocarrosNecessarios = (int) ((double)this->calcTempoIdaEVolta() / getFrequency() + 1.0);

	cout << "\tNumero de autocarros necessarios: " << this->nAutocarrosNecessarios << endl << endl;

	this->gerarHorario(06 * 60, 23 * 60 + 30);
}

////////////////
// get methods
////////////////


unsigned int Line::getFrequency() {
	return this->frequency;
}

unsigned int Line::getId() const {
	return id;
}

vector<string> Line::getBusStops() const {
	return busStopList;
}

vector<int> Line::getTimings() const {
	return timesList;
}

vector<unsigned> Line::getHorario() const {
	return this->horario;
}

int Line::getNumberBuses() const {
	return nAutocarrosNecessarios;
}

int Line::getStopOrder(string stop) {
	int a = 0;
	for each (string s in this->busStopList) {
		if (s == stop)
			return a;
		a++;
	}
	assert(false); // this should never happen!
	return -1;
}

int Line::getStopTime(string stop) {
	int res = 0;
	for (unsigned i = 0; i < this->busStopList.size(); i++) {
		res += this->timesList[i];
		if (this->busStopList[i] == stop)
			return res;
	}
	assert(false); // this should never happen!
	return -1;
}

void Line::print() {
	cout << "==== " << this->id << " ====" << endl;
	cout << "Tempo \t| Nome" << endl;
	cout << "--------|------------------" << endl;
	for (unsigned int j = 0; j < this->getBusStops().size(); j++) {
		cout << this->getTimings().at(j) << "\t| " << this->getBusStops().at(j) << endl;
	}
	return;
}

void Line::printTimeTable() {
	cout << "==== " << this->id << " ====" << endl;
	cout << "Horas de saida de " << this->getBusStops().at(0) << " (primeira paragem):" << endl;
	for (unsigned int j = 0; j < this->getHorario().size(); j++) {
		cout << "\t " << j+1 << ": " ; printTime(this->getHorario().at(j));
		if (j != 0 && (j + 1) % 3 == 0)
			cout << endl;
	}
	return;
}

void Line::printTimeTable(string stop) {
	cout << "Sentido: " << this->getId() << " - " << this->getBusStops().back() << " (ida)" << endl;
	for (unsigned i = 0; i < this->getHorario().size(); i++) {
		cout << "\t"; printTime(this->getHorario()[i] + this->getStopTime(stop));
		if (i != 0 && (i + 1) % 4 == 0)
			cout << endl;
	}
	cout << endl << endl;
	cout << "Sentido: " << this->getId() << " - " << this->getBusStops().front() << " (volta)" << endl;
	for (unsigned i = 0; i < this->getHorario().size(); i++) {
		cout << "\t"; printTime(this->getHorario()[i] + 2 * this->getStopTime(this->busStopList.back()) - this->getStopTime(stop));
		if (i != 0 && (i + 1) % 4 == 0)
			cout << endl;
	}
	cout << endl << endl;
}

int Line::calcTempoIdaEVolta() {
	int res = 0;
	for (unsigned i = 0; i < this->busStopList.size(); i++) {
		res += this->timesList.at(i) + this->timesList.at(i);
	}

	return res;
}

void Line::gerarHorario(unsigned begin, unsigned end) {
	vector<unsigned> res;
	cout << "Quero gerar um horario para uma linha que comeca as ";  printTime(begin); cout << " e acaba as "; printTime(end); cout << ".\n";
	while (begin <= end) {
		res.push_back(begin);
		//cout << "A adicionar "; printTime(begin); cout << endl;
		begin += this->frequency;
	}

	this->horario = res;
}

void Line::AlterLine(int id) {
	this->id = id;
}