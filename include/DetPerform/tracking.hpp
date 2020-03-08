#ifndef _INC_TRACKING
#define _INC_TRACKING

#include <iostream>
#include <vector>
#include <time.h>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TChain.h>
#include <TGraph.h>
#include <TF1.h>

#include "EVTCluster.hpp"
#include "MCTrue.hpp"

class Tracking
{
  //parameter
private:

  double minfvz[6][2];
  double maxfvz[6][2];
  double minfvxy[6][2];
  double maxfvxy[6][2];

  double minfcz[6][2];
  double maxfcz[6][2];
  double minfcxy[6][2];
  double maxfcxy[6][2];

public:


  //function
public:
  Tracking();
  ~Tracking();

  void SearchParticle(int pdg, MCTrue* mctrue, vector<int>* particlelist);
  bool FVcut(int mod, int view, double posz, double posxy);
  bool FCcut(int mod, int view, double posz, double posxy);
  
};

#endif
