#ifndef _INC_BMCLUSTER
#define _INC_BMCLUSTER

#include <iostream>
#include <vector>

#include "BMConst.hpp"

class BMCluster
{
  
private:

public:
  
  vector<double> mod;
  vector<double> view;
  vector<double> pln;
  vector<double> channel;
  vector<double> HG;
  vector<double> timedif;
  vector<double> Htime;
  vector<double> bunch;

  BMCluster();
  ~BMCluster(); 
  
  void Clear();

};

#endif
