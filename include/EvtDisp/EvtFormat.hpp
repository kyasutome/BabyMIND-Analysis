#ifndef _INC_EVTFORMAT
#define _INC_EVTFORMAT

#include <iostream>
#include <vector>
#include <time.h>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TChain.h>

#include "BMData.hpp"
#include "BMBasicRecon.hpp"
#include "BMBeaminfo.hpp"
#include "BMDisp.hpp"
#include "PMRecon.hpp"
#include "WGRecon.hpp"

class EvtFormat
{
  //parameter
private:
  FileStat_t info;
  TString pmfilename;
  TString pathtopm; 
  time_t pmfirsttime;
  time_t pmlasttime;
  int npmdata;
  int thepmspill;
  int nwgwmdata;
  int thewgwmspill;
  int nbmdata;
  int thebmspill;


public:
  TFile* bmfile;
  TTree* bmtree;
  TFile* pmfile;
  TTree* pmtree;
  TFile* wgwmfile;
  TTree* wgwmtree;
  vector<int> bmspill;
  vector<int> wgwmspill;
  vector<int> pmspill;
  vector<int> bmspill_match;
  vector<int> wgwmspill_match;
  vector<int> pmspill_match;
  TChain* bmchain;

  //function
public:
  EvtFormat();
  ~EvtFormat();

  void FillEvtClass(int ientry, vector<int> commonspill,
		    BMBasicRecon* bmbasicrecon, BMBeaminfo* bmbeaminfo, BMDisp* bmdisp, PMRecon* pmrcon,
		    WGRecon* wgwmrecon);
  void ReadBMTree(TString filepath, BMBasicRecon* bmbasicrecon, BMBeaminfo* bmbeaminfo);
  void ReadBMChain(TString filepath, BMBasicRecon* bmbasicrecon, BMBeaminfo* bmbeaminfo, TChain* bmchain);
  void ReadPMTree(TString filepath, PMRecon *pmrecon);
  void ReadWGWMTree(TString filepath, WGRecon *wgwmrecon);
  void PrintTime(time_t unixtime);
  void SpillMatch(vector<int>* commonspill, vector<int> vec1, vector<int> vec2);
  void FileClose();
  
};

#endif
