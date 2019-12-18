#ifndef _INC_BSDApply
#define _INC_BSDApply

#include <iostream>
#include <vector>
#include <time.h>

#include <TFile.h>
#include <TChain.h>
#include <TString.h>
#include <TSystem.h>

#include "BMConst.hpp"
#include "BMBasicRecon.hpp"
#include "BMBeaminfo.hpp"
#include "BMBSD.hpp"

class BSDApply
{
  //parameter
private:
  struct tm* timer;
  TString bsddir;
  TString filename;
  FileStat_t info;
  time_t thebeamtime;
  int startrun;
  int endrun;
  int startsub;
  int endsub;
  int firstmatchspillentry=-1;
  int dayspill = 10000;
  int thebeamspill;
  int thebmspill;


public:
  TChain* bsdchain;
  int trg_sec[3];
  int spillnum;
  int nsubdata = 1000;
  double ct_np[5][9];

  vector<double> bmspill;
  vector<double> bmgroup[100][2];
  vector<double> beamgroup[3];
  vector<double> matchingspill;

  //function
public:
  BSDApply();
  ~BSDApply();

  void ReadBSDfile();
  void GetMonDateHour(time_t unixtime, int* Mon, int* Date, int* Hour);
  void FindFirstSpill(int bmfirstspill, int bmmon, int bmdate, int bmhour);
  void MakeBeamGroup(int isub);
  void SpillMatch(int isub);
  void FillBSD(TTree* tree, TTree* otree, BMBSD* bmbsd);
  void KillAll();

  bool CheckBMTime(time_t unixtime, int mon, int date, int hour);
  bool CheckBMSpill(int bmspill, int beamspill);

  
  
  
};

#endif
