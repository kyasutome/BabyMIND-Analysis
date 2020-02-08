#ifndef _INC_WGWMDATA
#define _INC_WGWMDATA

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

class WGWMdata
{
  
private:
  TFile* Fileinput[2][8];
  TString treename;
  TString histname;
  FileStat_t info;  
  int difid;

public:

  TTree* spilltree[8];
  int spillnumber[8];
  int spillmode[8];

  TTree* wgtree[8];
  int Nentry[8];
  vector<int> wgwmspill[2][8];
  vector<int> wgwmsortspill[2][8];
  vector<int> wgwmentryid[2][8];
  //WAGASCI DATA STRUCTURE
  int spill_number[8];
  int spill_mode[8];
  int spill_count[8];
  
  int chipid_wg[4][20];
  int chanid_wg[4][36];
  int colid_wg[4][16];
  int charge_wg[4][20][36][16];
  int time_wg[4][20][36][16];
  int bcid_wg[4][20][16];
  int hit_wg[4][20][36][16];
  int gs_wg[4][20][36][16];
  int debug_chip_wg[4][20][7];
  int debug_spill_wg[4][7];  

  int chipid_wm[4][3];
  int chanid_wm[4][36];
  int colid_wm[4][16];
  int charge_wm[4][3][36][16];
  int time_wm[4][3][36][16];
  int bcid_wm[4][3][16];
  int hit_wm[4][3][36][16];
  int gs_wm[4][3][36][16];
  int debug_chip_wm[4][3][7];
  int debug_spill_wm[4][7];

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
  bool SignalCreation(int eachentry[8], WGRecon* wgrecon);
  bool ModeCheck(int spill_mode);
  void EntryCheck(int startentry[8], int entry_offset);
  bool BCIDCheck(int bcid);
  bool HitCheck(int hit);  
  int GetTEntry(int dif);
  int GetNofSpill(int dif, int *startspill, int *endspill);
  int GetBunch(int bcid);

  WGWMdata();
  ~WGWMdata();
 
};

#endif
