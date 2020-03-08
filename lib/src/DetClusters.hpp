#ifndef _INC_DETCLUSTERS
#define _INC_DETCLUSTERS

#include <iostream>
#include <vector>

#include "BMConst.hpp"
#include "DetHitClusters.hpp"

class DetClusters
{
  
private:

public:

  vector <DetHitClusters*> cluster;

  DetClusters();
  ~DetClusters(); 
  
  void Clear();

};

#endif
