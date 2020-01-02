#ifndef _INC_WGDATA
#define _INC_WGDATA

#include <iostream>
#include <vector>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TMath.h>
#include <TH1D.h>

#include "BMConst.hpp"
#include "WGRecon.hpp"
#include "WGChannelMap.hpp"

class WGdata
{
  
private:
  TFile* Fileinput[4];
  TString treename;
  TString histname;
  FileStat_t info;  
  int difid;

public:
  TTree* wgtree[4];
  TH1D* bcid_hist[4];
  int Nentry;
  //WAGASCI DATA STRUCTURE
  int spill_number[4];
  int spill_mode[4];
  int spill_count[4];
  
  int chipid[4][20];
  int chanid[4][36];
  int colid[4][16];
  int charge[4][20][36][16];
  int time[4][20][36][16];
  int bcid[4][20][16];
  int hit[4][20][36][16];
  int gs[4][20][36][16];
  int debug_chip[4][20][7];
  int debug_spill[4][7];  

  int thespill;
  int thespillmode;
  int thechip;
  int thebcid;
  int thecolum;
  int thechan;
  int thehit;
  int thecharge;
  int thepe;
  int thetime;

  void ReadTree(TString filename, int dif);
  bool SignalCreation(int ientry, int dif, WGRecon* wgrecon);
  bool ModeCheck(int spill_mode);
  bool BCIDCheck(int bcid);
  bool HitCheck(int hit);  
  int GetTEntry(int dif);
  int GetBunch(int bcid);

  WGdata();
  ~WGdata();
 
};

#endif
