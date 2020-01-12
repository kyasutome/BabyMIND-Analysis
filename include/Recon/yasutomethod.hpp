#ifndef _INC_YASUTOMETHOD
#define _INC_YASUTOMETHOD

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
#include "BMHitCluster.hpp"

class Yasutomethod
{
  
private:

  static const int Ntrack = 200;

  vector<vector<double> >track[Ntrack];  
  vector<vector<double> >recontrack[2];
  vector<vector<double> >ReconTrack;
  vector<BMHitCluster*> hitpln[2][20];
  vector<BMHitCluster*> hitclpln[2][20];
  vector<double> temp;

  BMHitCluster* bmhit[1000];
  BMHitCluster* bmclhit[1000];

  double firsttrack_side, firsttrack_top;
  double posxy;
  double posx, posy, posz;
  double center;
  double cut=15;
  double cut_default=15;  
  double tempy_pre;
  double tempz_pre;
  double cluster_time;

  int last;
  int icount = 0;
  int VIEW = 0;
  int prelayer = 0;
  int count_non = 0;
  int count_non_total = 0;
  int firstpln = 1;
  
  int mod, view, pln, channel,timedif, htime;

  bool cont;
  bool cutflag = false;
  bool findflag = false;

public:

  TH2D* recondisp;

public: 

  Yasutomethod();
  ~Yasutomethod();

  void ystmethod(BMDisp* bmdisp, BMCluster* bmcluster[100]);
  void Clustering(vector<BMHitCluster*> hitpln[2][20], vector<BMHitCluster*> hitclpln[2][20]);
  void ChooseTrack(vector<vector<double> >track[], vector<vector<double> >*ReconTrack);
  void Clear();

 
};

#endif
