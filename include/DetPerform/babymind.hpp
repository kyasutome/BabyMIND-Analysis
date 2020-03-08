#ifndef _INC_BABYMIND
#define _INC_BABYMIND

#include <iostream>
#include <vector>
#include <time.h>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TChain.h>
#include <TH1D.h>
#include <TF1.h>

#include "BMBasicRecon.hpp"
#include "BMBeaminfo.hpp"

class BabyMIND
{
  //parameter
private:

  TChain *bmchain;
  int nbmdata;
  TString histname;
  
  int mod, view, pln, channel;
  int LHG, RHG, THG;
  int lgain, rgain, tgain;
  double pe;
  double ped;

  int planepos[20];

  TF1 *landau;

public:

  double pe_hor[18][96][2];
  double pe_ver[18][32];
  double pe_yasu[2][14];

  double gain_hor[18][96][2];
  double gain_ver[18][32];
  double gain_yasu[2][14];
  
  TH1D* adcdist_hor[18][96][2];
  TH1D* adcdist_ver[18][32];
  TH1D* adcdist_yasu[2][14];

  TH1D* adcdist_hor_left_total;
  TH1D* adcdist_hor_right_total;
  TH1D* adcdist_ver_total;
  TH1D* adcdist_yasu_total;

  vector<int> plane;

  //function
public:
  BabyMIND();
  ~BabyMIND();

  void FillADCDist(TString filedir, BMBasicRecon* bmbasicrecon, BMBeaminfo* bmbeaminfo);
  void AddBMChain(TString filedir);
  void CalcPEMean();
  bool ConverttoPln(vector<int> activepln);
  bool SearchCoinPlns(int Plane);
  bool SearchThePln(int Plane);
  void CalcDetEff(int Plane, vector<int> activepln, int* counttotal, int* counteff);
  int JudgeLeftRight(double posx[]);
  bool JudgeFV(double posy[], double posz[]);
  bool SearchYasuHit(int leftright, double avehittime, vector<int>yasuhittime, vector<int>yasuchannel);
  
};

#endif
