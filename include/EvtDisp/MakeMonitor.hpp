#ifndef _INC_MAKEMONITOR
#define _INC_MAKEMONITOR

#include <iostream>
#include <vector>
#include <time.h>

#include <TApplication.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TArc.h>
#include <TBox.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TH2.h>
#include <TText.h>

#include "BMConst.hpp"
#include "EVTCluster.hpp"

class MakeMonitor
{
  //parameter
private:
  bool firstdraw = true;
  TH2F *h;
  TH2F *v;
  int spillnumber;
  time_t unixtime;
  struct tm* timer;
  int year, mon, day,hour, min, sec;
  TString TIME;
  TString SPILL;
public:
  TCanvas *monitor;
  TPad *pad_side;
  TPad *pad_top;
  TPad *pad_bottom;

  TText *timeinfo;
  TText *spillinfo;

  //function
public:
  MakeMonitor();
  ~MakeMonitor();

  void Display(EVTCluster* evtcluster);
  
};

#endif
