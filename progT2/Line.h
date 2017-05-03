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
  unsigned int frequency;
 public:
  Line(string textLine);
  // metodos get
  unsigned int getId() const;
  vector<string> getBusStops() const;
  vector<int> getTimings() const;
  // set methods
  void AlterLine(int id);
  // other methods
  void print();

  // Operators (for debugging)
  friend ostream& operator<< (ostream& os, const Line& d)
  {
	  os << d.id << ": " << d.getBusStops().back();
	  return os;
  }


};
