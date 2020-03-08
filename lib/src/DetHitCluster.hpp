#ifndef _INC_DETHITCLUSTER
#define _INC_DETHITCLUSTER

#include <iostream>
#include <vector>

#include "BMConst.hpp"

class DetHitCluster
{
  
private:

public:
  
  double mod;
  double view;
  double pln;
  double channel;
  double posx;
  double posy;
  double posz;
  double dposx;
  double dposy;
  double dposz;
  double HG;
  double Htime;

  DetHitCluster();
  ~DetHitCluster(); 
  
  void Clear();

};

#endif
