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
#include <TCanvas.h>
#include <TArc.h>

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

  double moduleboxz[6];
  double moduleboxx[6];
  double moduleboxy[6];

public:

  double slope[20], intercept[20];
  double intersection[2];
  
  TF1* linear[20];
  TGraph* reconfit[20];
  double graphz[20][1000];
  double graphxy[20][1000];
  int Nhit[20];
  TArc* optpoint;
  
  //function
public:
  Tracking();
  ~Tracking();

  void SearchParticle(int pdg, MCTrue* mctrue, vector<int>* particlelist);
  bool FVcut(int mod, int view, double posz, double posxy);
  bool FCcut(int mod, int view, double posz, double posxy);
  void SearchNuVertex(int mod, int view, int ntrack, 
		      vector<double> posz[], vector<double> posxy[], double estimatevertex[]);

  void SearchIntersection(int mod, int view, int ntrack, double slope[], double intercept[]);
  double CalcDist(double thexy, double thez, double slope, double intercept);
  void SetDisplay(int view, int ntrack);

  double CalcdE(double initpos, double angle);
  
};

#endif
