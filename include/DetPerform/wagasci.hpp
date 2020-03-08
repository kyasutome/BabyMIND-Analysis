#ifndef _INC_WAGASCI
#define _INC_WAGASCI

#include <iostream>
#include <vector>
#include <time.h>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TChain.h>
#include <TF1.h>
#include <TH2D.h>

#include "EVTCluster.hpp"
#include "BasicRecon.hpp"

class WAGASCI
{
  //parameter
private:
  int TDCmax;
  double slope[2];
  double szone;
  double dzone;
  double bcidwidth;

public:  

  //function
public:
  WAGASCI();
  ~WAGASCI();

  void TDCtoHittime(int oddeven, int TDC, int *htime, int bunch);

  
};

#endif
