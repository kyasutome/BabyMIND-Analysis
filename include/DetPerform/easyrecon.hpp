#ifndef _INC_EASYRECON
#define _INC_EASYRECON

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

class EasyRecon
{
  //parameter
private:
  
  int bunch;
  int mod;
  int view;
  int pln;
  int ch;
  int wgview;
  double posx, posy, posz;
  double dposx, dposy, dposz;

  TF1* linear; 
  double fitpar[2];

public:

  vector<int> plane[7][2];
  vector<int> channel[7][2];
  vector<int> splane[7][2];
  vector<int> schannel[7][2];

  vector<int> sdposz[7][2];
  vector<int> sdposx[7][2];
  vector<int> sdposy[7][2];
  vector<int> positionx[7][2];
  vector<int> positiony[7][2];
  vector<int> positionz[7][2];

  TH2D* fithist;
  

  //function
public:
  EasyRecon();
  ~EasyRecon();

  void Recon(EVTCluster* evtcluster, BasicRecon* basicrecon[]);  
  void Fitting(TF1* function, vector<int> plane, vector<int> channel, double fitpar[]);

  bool NHCheck(int mod, int view, BasicRecon* basicrecon, vector<int> *ataribunch);
  bool FVCheck(int mod, int view);
  bool SFVCheck(int mod, int view, double posxy[2], double posz[2]);
  
};

#endif
