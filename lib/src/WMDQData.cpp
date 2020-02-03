#include <iostream>
#include <stdio.h>

#include "WMDQData.hpp"

using namespace std;

WMDQData::WMDQData()
{
  dif.clear();
  chip.clear();
  chanid.clear();
  column.clear();
  bcid.clear();
  charge.clear();
  time.clear();
  gs.clear();
  hit.clear();
  
  spillmode=-1;
  spill=-1;
  unixtime=-1;
}


WMDQData::~WMDQData()
{
}

void WMDQData::Clear()
{
  dif.clear();
  chip.clear();
  chanid.clear();
  column.clear();
  bcid.clear();
  charge.clear();
  time.clear();
  gs.clear();
  hit.clear();
  
  spillmode=-1;
  spill=-1;
  unixtime=-1;
}

