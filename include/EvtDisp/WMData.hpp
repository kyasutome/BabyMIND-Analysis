#ifndef _INC_WGDATA
#define _INC_WGDATA

#include <iostream>
#include <vector>

#include "BMConst.hpp"

class WGdata
{
  
private:
  

public:
  
  //WAGASCI DATA STRUCTURE
  int spill_number;
  int spill_mode;
  int spill_count;
  
  int chipid[20];
  int chanid[36];
  int colid[16];
  int charge[20][36][16];
  int time[20][36][16];
  int bcid[20][16];
  int hit[20][36][16];
  int gs[3][36][16];
  int debug_chip[20][7];
  int debug_spill[7];  
  

  WGdata();
  ~WGdata();
 
};

#endif
