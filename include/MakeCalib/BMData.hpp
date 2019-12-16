#ifndef _INC_BMDATA
#define _INC_BMDATA

#include <iostream>
#include <vector>

#include "BMConst.hpp"

class BMdata
{
  
private:

public:
  
  //Baby MIND DATA STRUCTURE
  vector<double> *SN;
  vector<double> *SpillTag;
  vector<double> *SpillTime;
  vector<double> *SpillTimeGTrig;
  vector<double> *GTrigTag;
  vector<double> *GTrigTime;
  vector<double> *hitsChannel;
  vector<double> *hitAmpl;
  vector<double> *hitLGAmpl;
  vector<double> *hitLeadTime;
  vector<double> *hitTrailTime;
  vector<double> *hitTimeDif;
  vector<double> *hitTimefromSpill;
  vector<double> *SpillTrailTime;
  vector<double> *AsicTemperature;
  vector<double> *FPGATemperature;
  vector<double> *GlobalHV;
  vector<double> *BoardTemperature;
  vector<double> *BoardHumidity;

  BMdata();
  ~BMdata();
 
};

#endif
