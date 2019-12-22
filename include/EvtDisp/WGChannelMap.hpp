#ifndef _INC_WGCHANNELMAP
#define _INC_WGCHANNELMAP

#include <iostream>
#include <vector>
#include <time.h>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TChain.h>

#include "BMConst.hh"

class WGChannelMap
{
  //parameter
private:
  const int wgChannelMap::DifView[2] = {TopView,SideView};


  //vector<int>* mod;

  
public:



  //function
public:
  WGChannelMap();
  ~WGChannelMap();

  
  
};

#endif
