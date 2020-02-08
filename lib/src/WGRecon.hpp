#ifndef _INC_WGRecon
#define _INC_WGRecon

#include <iostream>
#include <vector>

#include "BMConst.hpp"

class WGRecon
{
  
private:

public:

  /*
  vector<double> *mod;
  vector<double> *view;
  vector<double> *pln;
  vector<double> *channel;
  vector<double> *time;
  vector<double> *bunch;  
  */

  vector<double> mod;
  vector<double> view;
  vector<double> pln;
  vector<double> channel;
  vector<double> charge;
  vector<double> time;
  vector<double> bunch;  

  int spill;
  int unixtime;

  WGRecon();
  ~WGRecon(); 

  void Clear();

};

#endif
