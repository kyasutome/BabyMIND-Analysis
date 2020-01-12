#ifndef _INC_CHARGEID
#define _INC_CHARGEID

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
#include "BMCluster.hpp"

class Chargeid
{
  
private:
  
  double mod;
  double view;
  double pln;
  double channel;
  double Htime;

  double hitcount_over = 0;
  double hitcount_under = 0;
  double count_over = 0;
  double count_under = 0;
  double count_numu_tmp = 0;
  double count_numubar_tmp = 0;

public:

  Chargeid();
  ~Chargeid();

  void algorithm_A(BMCluster* bmcluster, double &count_numu, double &count_numubar,
		   int minimumlimit);

  int positioncheck(double y);
  void CountMuon(double count_numu, double count_numubar,
		 double& number_of_numu, double& number_of_numubar);
  
};
#endif
