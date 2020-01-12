#ifndef _INC_BMHITCLUSTER
#define _INC_BMHITCLUSTER

#include <iostream>
#include <vector>

#include "BMConst.hpp"

class BMHitCluster
{
  
private:

public:
  
  double mod;
  double view;
  double pln;
  double channel;
  double HG;
  double timedif;
  double Htime;

  BMHitCluster();
  ~BMHitCluster(); 
  
  void Clear();

};

#endif
