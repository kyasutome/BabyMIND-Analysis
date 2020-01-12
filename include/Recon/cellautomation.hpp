#ifndef _INC_CELLAUTOMATION
#define _INC_CELLAUTOMATION

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
#include "BMDisp.hpp"

class CellAutomation
{
  
private:
  
  TString histname;
  int nch[2]={96, 16};
  int Nentry;
  double mod;
  double view;
  double pln;
  double channel;
  double bunch;

  

public:

  TH2D *beforefit[2][9];
  TH2D *afterfit[2][9];

  CellAutomation();
  ~CellAutomation();

public:

  void FillBeforeFit(BMDisp* bmdisp);
  void FillAfterFit(BMDisp* bmdisp);
  void Clustering();
 
};

#endif
