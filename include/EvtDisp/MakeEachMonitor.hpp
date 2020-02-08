#ifndef _INC_MAKEEACHMONITOR
#define _INC_MAKEEACHMONITOR

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

#include "BMConst.hpp"
#include "EVTCluster.hpp"
#include "WGRecon.hpp"

class MakeEachMonitor
{
  //parameter
private:
  bool firstdraw = true;
  TH2F *h;
  TH2F *v;
  
public:
  TCanvas *monitor;
  TCanvas *monitor2;

  //function
public:
  MakeEachMonitor();
  ~MakeEachMonitor();

  void Display(EVTCluster* evtcluster);
  
};

#endif
