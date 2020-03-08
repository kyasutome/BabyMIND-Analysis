#ifndef _INC_MATCHING
#define _INC_MATCHING

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
#include "Dimension.cpp"

class Matching
{
  //parameter
private:

  double epsilon;
  TGraph* fitgraph[6][2];
  TF1* linear;
  double slope[6][2];
  double intercept[6][2];

public:

  double posfinalpln[6][2];
  double moddisttobm[6][2];
  Dimension* fdimension;

  double aveposxy[2][20];

  //function
public:
  Matching();
  ~Matching();

  bool JudgePenetrate(int mod, int view, double finalpos);
  void CalcSlope(int mod, int view, double posz[], double posxy[]);
  void Extrapolation(int mod, int view, double finalposxy, double* extrapolatexy);
  bool InBM(int mod, int view, double extrapolatexy);
  bool Matchingbm(int view, int itrack, double extrapolatexy, double posz[], double posxy[]);
  bool SearchMatchHit(int view, int bunch, double extrapolatexy,  vector<double> posz, vector<double> posxy);
  
};

#endif
