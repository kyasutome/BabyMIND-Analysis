#ifndef _INC_WMDQCHECK
#define _INC_WMDQCHECK

#include <iostream>
#include <vector>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TMath.h>
#include <TH1D.h>
#include <TH2D.h>

#include "BMConst.hpp"
#include "WGRecon.hpp"
#include "WGChannelMap.hpp"
#include "WMDQData.hpp"

class WMDQCheck
{
  
private:
  TFile* Fileinput[4];
  TString treename;
  TString histname;
  FileStat_t info;  
  int difid;

public:
  TTree* wgtree[4];
  TH1D* bcid_hist[4][3];
  TH1D* time_hist[4][3][32];
  TH1D* charge_hist[4][3][32];
  TH1D* charge_hist_nohit[4][3][32];
  TH2D* channel_hit[4][3];
  TH2D* channel_adc[4][3];
  TH2D* channel_adc_hit[4][3];
  TH2D* channel_adc_nohit[4][3];

  int Nentry;
  //WAGASCI DATA STRUCTURE
  int spill_number[4];
  int spill_mode[4];
  Long64_t spill_count[4];

  int count_under=0;
  int count_over=0;
  
  int chipid[4][3];
  int chanid[4][36];
  int colid[4][16];
  int charge[4][3][36][16];
  int time[4][3][36][16];
  int bcid[4][3][16];
  int hit[4][3][36][16];
  int gs[4][3][36][16];
  int debug_chip[4][3][7];
  int debug_spill[4][7];  

  int thespill;
  int thespillmode;
  int thechip;
  int thebcid;
  int thecolumn;
  int thechan;
  int thehit;
  int thecharge;
  int thepe;
  int thetime;

  void ReadTree(TString filename, int dif);
  bool SignalCreation(int ientry, int dif, WMDQData* wmdqdata);
  bool ModeCheck(int spill_mode);
  bool HitCheck(int hit);  
  bool BCIDCheck(int bcid);
  int GetTEntry(int dif);
  int GetBunch(int bcid);

  WMDQCheck();
  ~WMDQCheck();
 
};

#endif
