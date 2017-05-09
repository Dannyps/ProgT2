#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "time_dh.h"



using namespace std;

class Line{
 private:
  unsigned int id;
  vector<string> busStopList;
  vector<int> timesList;
  unsigned int frequency;
  int nAutocarrosNecessarios=-1;
 public:
  Line(string textLine);
  // metodos get
  unsigned int getFrequency();
  unsigned int getId() const;
  vector<string> getBusStops() const;
  vector<int> getTimings() const;
  // set methods
  void AlterLine(int id);
  // other methods
  void print();
  int calcTempoIdaEVolta();
  vector <time_dh> gerarHorario(time_dh begin, time_dh end);

  // Operators (for debugging)
  friend ostream& operator<< (ostream& os, const Line& d)
  {
	  os << d.id << ": " << d.getBusStops().back();
	  return os;
  }


};
