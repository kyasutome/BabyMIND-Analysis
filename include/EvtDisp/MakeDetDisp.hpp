#ifndef _INC_MAKEDETDISP
#define _INC_MAKEDETDISP

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

class MakeDetDisp
{
  //parameter
private:
  
public:
  double uhorl[48], dhorl[48];
  double uhorr[47], dhorr[47];
  double uverl[8], dverl[8];
  double uverr[8], dverr[8];

  //function
public:
  MakeDetDisp();
  ~MakeDetDisp();

  //for Baby MIND
  void DrawBabyMIND(int view);
  void DetModule(double x1, double y1, double x2, double y2);
  void MagModule(double x1, double y1, double x2, double y2);
  void YASUModule(double x1, double y1, double x2, double y2);

  //for Proton Module
  void DrawProtonModule(int view);
  void IngSci(double pln, double ch,double x1,double y1,int view); //Ingrid scintillator
  void ParSci(double pln, double ch,double x1,double y1,int view); 
  void SciSci(double pln, double ch,double x1,double y1,int view); //Sciber scintillator
  void VetoSci(double pln, double ch,double x1,double y1,int view);
  
};

#endif
