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

#include "BMConst.hpp"
#include "BMDisp.hpp"

class MakeMonitor
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
  MakeMonitor();
  ~MakeMonitor();

  void Display(BMDisp* bmdisp);
  
};

#endif
