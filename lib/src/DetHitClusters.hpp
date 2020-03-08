#ifndef _INC_DETHITCLUSTERS
#define _INC_DETHITCLUSTERS

#include <iostream>
#include <vector>

#include "BMConst.hpp"
#include "DetHitCluster.hpp"

class DetHitClusters
{
  
private:

public:

  vector <DetHitCluster*> cluster;
  double posz;
  double posxy;

  DetHitClusters();
  ~DetHitClusters(); 
  
  void Clear();

};

#endif
