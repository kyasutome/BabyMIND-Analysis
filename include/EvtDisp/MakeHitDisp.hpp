#ifndef _INC_MAKEHITDISP
#define _INC_MAKEHITDISP

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
#include "Dimension.hpp"

class MakeHitDisp
{
  //parameter
private:
  int mod;
  int view;
  int pln;
  int ch;
  int bunch;
  int nhit;
  
  int dif, chip, chan;
  
  double r;
  int color;

public:

  //function
public:
  MakeHitDisp();
  ~MakeHitDisp();

  //for Baby MIND
  void DrawBMHit(BMDisp* bmdisp, int VIEW);
  void bmxhit(double pln, double ch, double r, double bunch);
  void bmyhit(double pln, double ch, double r, double bunch);
  void yasuxhit(double view, double pln, double ch, double r, double bunch);
  void yasuyhit(double view, double pln, double ch, double r, double bunch);

  //for Proton Module
  void DrawPMHit(BMDisp* bmdisp, int VIEW);
  void pmxhit(double pln, double ch, double r, double bunch);
  void pmyhit(double pln, double ch, double r, double bunch);
  void pmvhit(double pln, double ch, double view, double r, double bunch);

  //for WAGASCIs
  void DrawWGHit(BMDisp* bmdisp, int VIEW, int MOD);
  void wgxhit(double dif, double chip, double chan, double r, double bunch);
  void wgyhit(double dif, double chip, double chan, double r, double bunch);

  //for WallMRDs
  void DrawWMHit(BMDisp* bmdisp, int MOD);
  void wmhit(double dif, double chip, double chan, double r, double bunch);

  void ColorScale(int *color, int bunch);
  
};

#endif
