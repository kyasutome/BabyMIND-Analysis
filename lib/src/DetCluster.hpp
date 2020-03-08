#ifndef _INC_DETCLUSTER
#define _INC_DETCLUSTER

#include <iostream>
#include <vector>

#include "BMConst.hpp"
#include "DetHitCluster.hpp"

class DetCluster
{
  
private:

public:

  vector <DetHitCluster*> cluster;
  

  DetCluster();
  ~DetCluster(); 
  
  void Clear();

};

#endif
