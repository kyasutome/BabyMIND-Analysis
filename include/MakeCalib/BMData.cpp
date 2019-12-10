#include <iostream>
#include <stdio.h>

#include "BMData.hpp"

using namespace std;

BMdata::BMdata()
{

  SN=0;
  SpillTag=0;
  SpillTime=0;
  SpillTimeGTrig=0;
  GTrigTag=0;
  GTrigTime=0;
  hitsChannel=0;
  hitAmpl=0;
  hitLGAmpl=0;
  hitLeadTime=0;
  hitTrailTime=0;
  hitTimeDif=0;
  hitTimefromSpill=0;
  SpillTrailTime=0;
  AsicTemperature=0;
  FPGATemperature=0;
  GlobalHV=0;
  BoardTemperature=0;
  BoardHumidity=0;

}


BMdata::~BMdata()
{
}
