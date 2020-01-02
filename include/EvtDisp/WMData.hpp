#ifndef _INC_WMDATA
#define _INC_WMDATA

#include <iostream>
#include <vector>

#include "BMConst.hpp"

class WMdata
{
  
private:  

public:
  
  //WallMRDs DATA STRUCTURE
  int spill_number;
  int spill_mode;
  int spill_count;
  
  int chipid[3];
  int chanid[36];
  int colid[16];
  int charge[3][36][16];
  int time[3][36][16];
  int bcid[3][16];
  int hit[3][36][16];
  int gs[3][36][16];
  int debug_chip[3][7];
  int debug_spill[7];  
  

  WMdata();
  ~WMdata();
 
};

#endif
