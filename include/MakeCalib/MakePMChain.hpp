#ifndef _INC_MAKEPMCHAIN
#define _INC_MAKEPMCHAIN

#include <iostream>
#include <vector>
#include <time.h>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TChain.h>

#include "PMRecon.hpp"

class MakePMChain
{
  //parameter
private:
  TBranch* bmod;
  TBranch* bview;
  TBranch* bpln;
  TBranch* bchannel;
  TBranch* btime;
  TBranch* bbunch;

  //vector<int>* mod;
  Long64_t tentry;
  TString pmfilename;
  TString pathtopm;
  FileStat_t info;
  int npmfile;
  
public:
  TChain* pmchain;


  //function
public:
  MakePMChain();
  ~MakePMChain();

  void ReadPMTree(int run, int ssub, int esub,  PMRecon *pmrecon);
  void FillPMClass(int ientry, PMRecon *pmrecon);
  
  
};

#endif
