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
#include "EVTCluster.hpp"
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
  double posx, posy, posz;
  
  double r;
  int color;

public:

  //function
public:
  MakeHitDisp();
  ~MakeHitDisp();

  void Hit(double z, double xy, double r, double bunch);
  void DrawHit(EVTCluster* evtcluster, int view);

  void ColorScale(int *color, int bunch);
  
};

#endif
