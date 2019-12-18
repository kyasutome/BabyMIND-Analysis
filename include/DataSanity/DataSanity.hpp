#ifndef _INC_DATASANITY
#define _INC_DATASANITY

#include <iostream>
#include <vector>
#include <time.h>

#include <TFile.h>
#include <TChain.h>
#include <TString.h>
#include <TSystem.h>
#include <TH2D.h>

#include "BMConst.hpp"
#include "BMBasicRecon.hpp"
#include "BMBeaminfo.hpp"
#include "BMBSD.hpp"

class DataSanity
{
  //parameter
private:
  TString bmdirpath;
  TString bsddirpath;
  TString bmfilename;
  FileStat_t info;
  
public:
  TChain* bmchain;
  BMBSD* bmbsd;

  int startdate = 0;
  int enddate = 31;
  int startrun = 0;
  int endrun = 5;

  //function
public:
  DataSanity();
  ~DataSanity();

  void ReadBMfile();
  void SetHistLabel(TH2D* h, const char* title, char* ytitle);
  void KillAll();

  
};

#endif
