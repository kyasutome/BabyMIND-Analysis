#ifndef _INC_MESTIMATION
#define _INC_MESTIMATION

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

class Mestimation
{
  
private:
  
  double mod;
  double view;
  double pln;
  double channel;
  double Htime;
  

public:


  Mestimation();
  ~Mestimation();

 
};

#endif
