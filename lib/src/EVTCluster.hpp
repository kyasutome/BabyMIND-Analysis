#ifndef _INC_EVTCLUSTER
#define _INC_EVTCLUSTER

#include <iostream>
#include <vector>

#include "BMConst.hpp"

class EVTCluster
{
  
private:

public:
  
  vector<double> mod;
  vector<double> view;
  vector<double> pln;
  vector<double> channel;
  vector<double> timedif;
  vector<double> charge;
  vector<double> Htime;
  vector<double> bunch;
  vector<double> posx;
  vector<double> posy;
  vector<double> posz;
  vector<double> dposx;
  vector<double> dposy;
  vector<double> dposz;

  double pot;
  double totalpot;
  int unixtime;
  int spillnum;
  int bm_event;
  int entry;

  EVTCluster();
  ~EVTCluster(); 

  void Clear();

};

#endif
