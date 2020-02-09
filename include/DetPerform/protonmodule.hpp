#ifndef _INC_PROTONMODULE
#define _INC_PROTONMODULE

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

class ProtonModule
{
  //parameter
private:
  
  int mod;
  int view;
  int pln;
  int ch;
  double posx, posy, posz;

  TF1* linear; 
  double fitpar[2];

public:

  vector<int> plane;
  vector<int> channel;
  vector<int> positionx;
  vector<int> positionz;

  TH2D* fithist;
  

  //function
public:
  ProtonModule();
  ~ProtonModule();

  void EasyRecon(EVTCluster* evtcluster, BasicRecon* basicrecon);  
  void Fitting(TF1* function, vector<int> plane, vector<int> channel, double fitpar[]);
  
};

#endif
