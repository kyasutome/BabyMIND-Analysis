#ifndef _INC_CHARGEID
#define _INC_CHARGEID

#include <iostream>
#include <vector>
#include <time.h>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TChain.h>
#include <TH1D.h>
#include <TF1.h>

class ChargeID
{
  //parameter
private:

  double gap[17];
  double detector_module_z[19] = {0, 0, 25, 42.7, 53.7, 64.7, 88.9, 106.7,
                                  138.2, 156.1, 186.8, 218.8, 236.7,
                                  261.8, 279.5, 324.3, 369, 401.1, 411.1};

  double iron_module_z[33] = {7, 14.2, 21,49.7, 60.7, 71.7,
                              95.9, 102.9, 113.7, 121, 145.2, 151.9,
                              163.1, 170, 193.8, 200.8, 207.8, 214.8,
                              243.7, 250.6, 257.8, 286.5, 293.7, 300.4,
                              307.4, 331.3, 338.3, 345.4, 352.1, 376,
                              383.3, 390.2, 397.1};

  double planeposition[19] = {-99999, -10, 203, 407, 527, 637, 869, 1047, 1362, 1541, 1858, 2151, 2347, 2571,
			      2775, 3230, 3550, 3974, 4064};

  double B[18];
  double magnet[18]={0, 3, 0, 1, 1, 1, 2, 2, 2, 2, 4, 0, 3, 0, 4, 4, 4, 0};
  double deltaE[18];
  double scinti = 1;
  double rho_iron = 7.874;
  double rho_sci = 1.038;  
  double mip = 2.0;
  double iron_len = 3.1;
  double layer_len = 4.0;
  double B_default = 1.5;
  double cm=10;

  bool magnetflag[18] = {false, true, false, true, true, true, true, true, true, true, true,
			 false, true, false, true, true, true, false};

  double delta;
  double testposy[19], testposz[19];
  double testmomentum[19], testradius[19], testslope[19];
  double slope, positiony, radius, momentum; 
  int bin_slope = 10;
  int bin_posy = 10;
  int bin_radius = 1000;

  double dslope = 0.05;
  double dposy = 0.5;
  double dradius = 20;

  double minslope, minposy, minradius;
  double maxslope, maxposy, maxradius;
  double centerslope, centerposy;

  int bfield, dE;

  double optslope[2], optposy[2], optradius[2], optmomentum[2];
  TGraph *fitgraph[2];
  double graposz0[100], graposz1[100], graposx[100], graposy[100];
  TF1* linear;

public:
  std::vector<double> Hitpositiony[19];
  double Hitposz[19], Hitposy[19];
  double estimateposy[2][19];
  double refposz[19];
  int lastmodule;
  double minchi[2] = {9999, 9999};

  //function
public:
  ChargeID();
  ~ChargeID();

  void MCEST(double posz[], double posy[], double mcest[]);
  bool MakePlnPos(double posz[], double posy[]);
  int Bfield(double posy);
  double dEdX(int i, double magnet[], double momentum);
  double Delta(bool magnetflag, double distz, double radius, double slope, int bfield, int charge);
  double CalcChi2();
  void RangeCalc(double posz_side[], double posy[], double posz_top[], double posx[], double *rangemom);
  
};

#endif
