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
  int bmcount=0;
  int wgcount=0;
  int pmcount=0;
  int dayspill = 31000;
  int thebeamspill;
  int thebmspill;
  int thewgspill;
  int thepmspill;
  int spillshift;


public:
  TChain* bsdchain;
  int trg_sec[3];
  int spillnum;
  int nsubdata = 1000;
  double ct_np[5][9];

  vector<double> bmspill;
  vector<double> bmgroup[100][2];
  vector<double> wgspill;
  vector<double> wggroup[100][2];
  vector<double> pmspill;
  vector<double> pmgroup[100][2];

  vector<int> baseunixtime;
  vector<double> beamgroup[3];
  vector<double> matchingspill;
  

  //function
public:
  BSDApply();
  ~BSDApply();

  void ReadBSDfile();
  void GetMonDateHour(time_t unixtime, int* Mon, int* Date, int* Hour);
  void FindFirstSpill(int *detfirstspill, int detmon, int detdate, int dethour, int mod);
  void MakeBeamGroup(int isub);
  void SpillMatch(int isub, int mod);
  void FillBSD(TTree* tree, TTree* otree, BMBSD* bmbsd, int mod, BMBasicRecon* bmbasicrecon,
	       BMBeaminfo* bmbeaminfo);
  void KillAll();

  bool CheckDetTime(time_t unixtime, int mon, int date, int hour);
  bool CheckDetSpill(int detspill, int beamspill);
  bool CheckMainteDay(int Mon, int Date, int *detfirstspill, int mod);

  
  
  
};

#endif
