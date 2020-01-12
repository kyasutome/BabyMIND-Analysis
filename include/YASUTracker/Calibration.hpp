#ifndef _INC_CALIBRATION
#define _INC_CALIBRATION

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

class Calibration
{
  
private:
  
  TString histname;
  double mod;
  double view;
  double pln;
  double channel;
  double HG;
  double timedif;
  

public:
  
  TH1D* hist_hg[2];
  TH1D* hist_tdif[2];
  TH1D* hist_hg_yasu[2][14];
  TH1D* hist_tdif_yasu[2][14];


public:

  Calibration();
  ~Calibration();
  
  void MakeDist(BMBasicRecon* bmbasicrecon);
  void CalcGain(double *gain);
  
 
};

#endif
