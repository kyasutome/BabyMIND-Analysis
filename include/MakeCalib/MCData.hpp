#ifndef _INC_MCDATA
#define _INC_MCDATA

#include <iostream>
#include <vector>

#include "TString.h"
#include "TFile.h"
#include "TTree.h"

#include "BMConst.hpp"
#include "MCRecon.hpp"
#include "MCTrue.hpp"

class MCdata
{
  
private:
  int npar;
  int nutype;
  int inttype;
  int pdg[20];

  double ipos[4][20];
  double fpos[4][20];
  double momentum[4][20];
  
  double nuE;
  double xnu, ynu, znu;
  double numomentum[3];
  double totcrsne;
  double norm;

  vector<int> *mod;
  vector<int> *view;
  vector<int> *pln;
  vector<int> *channel;
  vector<int> *charge;
  vector<double> *dposx;
  vector<double> *dposy;
  vector<double> *dposz;
  vector<double> *posx;
  vector<double> *posy;
  vector<double> *posz;

  Long64_t tentry;
  TBranch* bmod;
  TBranch* bview;
  TBranch* bpln;
  TBranch* bchannel;
  TBranch* bcharge;
  TBranch* bdposx;
  TBranch* bdposy;
  TBranch* bdposz;
  TBranch* bposx;
  TBranch* bposy;
  TBranch* bposz;

  int MOD, VIEW, POSX, POSY, POSZ;
  

public:

  TFile *fin;
  TTree *tree;
  int Nentry;

  void ReadMCdata(TString filedir, TTree *otree, MCRecon *mcrecon, MCTrue *mctrue);

  MCdata();
  ~MCdata();
 
};

#endif
