#ifndef _INC_MCRecon
#define _INC_MCRecon

#include <iostream>
#include <vector>

#include "BMConst.hpp"

class MCRecon
{
  
private:

public:

  vector<double> mod;
  vector<double> view;
  vector<double> pln;
  vector<double> channel;
  vector<double> charge;
  vector<double> dposx;
  vector<double> dposy;
  vector<double> dposz;
  vector<double> posx;
  vector<double> posy;
  vector<double> posz;


  MCRecon();
  ~MCRecon(); 

  void Clear();

};

#endif
