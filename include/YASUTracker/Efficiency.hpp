#ifndef _INC_EFFICIENCY
#define _INC_EFFICIENCY

#include <iostream>
#include <vector>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TMath.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TApplication.h>

#include "BMConst.hpp"
#include "BMBasicRecon.hpp"
#include "BMCluster.hpp"

class Efficiency
{
  
private:
  
  int mod;
  int view;
  int pln;
  int channel;
  int htime;
  int timedif;
  int HG;

  vector<int>plnstock;
  vector<int>yasupln;

  int totaldetectionefficiency[2][2];
  int Ncount[2][2];
  int LR;
  int FB;

  double gain;

public:
  
  BMCluster* yasucluster;
  BMCluster* timecluster[2][100];
  vector<int> leadingtime;
  TH1D* yasumip;
  TH1D* yasumip_pe;
  


public:

  Efficiency();
  ~Efficiency();

  void TimeClustering(BMBasicRecon* bmbasicrecon);
  void Clear();
  void GetEfficiency();

  int GetNpln(BMCluster* bmcluster);
  int VectorFind(vector<int> vec, int number);
  int LeftRightModule(BMCluster* bmcluster);

  int YASUplnSearch(BMCluster* bmcluster);
 
};

#endif
