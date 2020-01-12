#ifndef _INC_TRACKMATCHING
#define _INC_TRACKMATCHING

#include <iostream>
#include <vector>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TMath.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TApplication.h>

#include "BMConst.hpp"
#include "BMDisp.hpp"
#include "BMCluster.hpp"

class TrackMatching
{
  
private:

  bool matching = false;

  double mod;
  double view;
  double pln;
  double channel;
  double bunch;
  double posx, posy, posz;
  double dist = 200;
  double firstz_inbm = 188;
  double intercept, slope;
  double estimatedy, datay;
  double trydif;
  double refdif = 9999;
  
  int matchingid;

public:

  TH2D *pmdisp;
  TH2D *pmdisp_corr;
  TH2D *bmdisp_corr;
  TF1 *linear;

  TrackMatching();
  ~TrackMatching();

  bool Matching_pmbm(BMDisp* bmdisp, BMCluster* bmcluster[100]);
  double ExtraporatedFromPM();
  void Clear();
 
};

#endif
