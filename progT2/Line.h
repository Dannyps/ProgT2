#pragma once

#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Line{
 private:
  unsigned int id;
  vector<string> busStopList;
  vector<int> timesList;
  vector<unsigned> horario; // Hora de partida de cada autocarro da primeira paragem
  unsigned int frequency;
  int nAutocarrosNecessarios=-1;
 public:
  Line(string textLine);
  // metodos get
  unsigned int getFrequency();
  unsigned int getId() const;
  vector<string> getBusStops() const;
  vector<int> getTimings() const;
  vector<unsigned> getHorario() const;
  // set methods
  void AlterLine(int id);
  // other methods
  void print();
  void printTimeTable();
  int calcTempoIdaEVolta();
  void gerarHorario(unsigned begin, unsigned end);

  // Operators (for debugging)
  friend ostream& operator<< (ostream& os, const Line& d)
  {
	  os << d.id << ": " << d.getBusStops().back();
	  return os;
  }


};
