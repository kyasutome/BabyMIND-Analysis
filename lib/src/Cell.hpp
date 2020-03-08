#ifndef _INC_CELL
#define _INC_CELL

#include <iostream>
#include <vector>

#include "BMConst.hpp"
#include "DetHitClusters.hpp"

class Cell
{
  
private:

public:
  DetHitClusters* dethitclusters[2];

  int state;
  int idcard;
  vector<int> upneibor;
  vector<int> downneibor;
  double meanposz;
  double meanposxy;  

  Cell();
  ~Cell(); 
  
  void Clear();

};

#endif
