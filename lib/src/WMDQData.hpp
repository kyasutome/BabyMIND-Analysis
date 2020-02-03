#ifndef _INC_WMDQData
#define _INC_WMDQData

#include <iostream>
#include <vector>

#include "BMConst.hpp"

class WMDQData
{
  
private:

public:

  vector<int> dif;
  vector<int> chip;
  vector<int> chanid;
  vector<int> column;
  vector<int> bcid;
  vector<int> charge;  
  vector<int> time; 
  vector<int> gs;
  vector<int> hit;

  int spillmode;
  int spill;
  int unixtime;

  WMDQData();
  ~WMDQData(); 

  void Clear();

};

#endif
