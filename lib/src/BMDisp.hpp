#ifndef _INC_BMDISP
#define _INC_BMDISP

#include <iostream>
#include <vector>

#include "BMConst.hpp"

class BMDisp
{
  
private:

public:
  
  vector<double> mod;
  vector<double> view;
  vector<double> pln;
  vector<double> channel;
  vector<double> timedif;
  vector<double> Htime;
  vector<double> bunch;  

  int bm_event;
  int entry;
  int spillnum;
  int unixtime;

  BMDisp();
  ~BMDisp(); 

};

#endif
