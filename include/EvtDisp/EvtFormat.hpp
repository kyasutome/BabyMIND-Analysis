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

class EvtFormat
{
  //parameter
private:
  FileStat_t info;
  TString pmfilename;
  TString pathtopm; 
  int npmdata;
  time_t pmfirsttime;
  time_t pmlasttime;
  int thepmspill;

  int nbmdata;
  int thebmspill;


public:
  TFile* bmfile;
  TTree* bmtree;
  TFile* pmfile;
  TTree* pmtree;
  vector<int> bmspill;
  vector<int> pmspill;

  //function
public:
  EvtFormat();
  ~EvtFormat();

  void FillEvtClass(int ientry, vector<int> commonspill,
		    BMBasicRecon* bmbasicrecon, BMBeaminfo* bmbeaminfo, BMDisp* bmdisp, PMRecon* pmrcon);
  void ReadBMTree(TString filepath, BMBasicRecon* bmbasicrecon, BMBeaminfo* bmbeaminfo);
  void ReadPMTree(TString filepath, PMRecon *pmrecon);
  void PrintTime(time_t unixtime);
  void SpillMatch(vector<int>* commonspill, vector<int> vec1, vector<int> vec2);
  void FileClose();
  
};

#endif
