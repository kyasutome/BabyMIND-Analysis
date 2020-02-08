#ifndef _INC_WALLMRD
#define _INC_WALLMRD

#include <iostream>
#include <vector>
#include <time.h>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TChain.h>

#include "EVTCluster.hpp"

class WallMRD
{
  //parameter
private:


public:

  vector<int> chip[4];
  vector<int> chan[4];
  vector<int> bunch[4];
  vector<int> posx[4];
  vector<int> posz[4];

  //function
public:
  WallMRD();
  ~WallMRD();

  void Nhit(EVTCluster* evtcluster, int count[], int dif[]);
  
  
};

#endif
