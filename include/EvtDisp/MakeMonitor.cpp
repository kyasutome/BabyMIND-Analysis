#include <iostream>
#include <fstream>
#include <vector>

#include "MakeMonitor.hpp"
#include "MakeHitDisp.cpp" // should include HitDisp before DetDisp
#include "MakeDetDisp.cpp"

using namespace std;
//#define debug

MakeMonitor::MakeMonitor()
{
}

MakeMonitor::~MakeMonitor()
{
}

MakeHitDisp* makehitdisp = new MakeHitDisp();
MakeDetDisp* makedetdisp = new MakeDetDisp();

void MakeMonitor::Display(BMDisp* bmdisp)
{
  if(firstdraw)
    {
      monitor = new TCanvas("monitor", "monitor", 2000, 1600);
      monitor2 = new TCanvas("monitor2", "monitor2", 2000, 1600);
      firstdraw=false;
    }

  h = new TH2F("","Side View", 6700, -2500, 4200, 2300, -1150, 1150);
  h->GetXaxis()->SetLabelSize(0);
  h->GetYaxis()->SetLabelSize(0);
  h->SetStats(0);
  h->GetXaxis()->SetNdivisions(0);
  h->GetYaxis()->SetNdivisions(0);

  v = new TH2F("","Top View", 7200, -3000, 4200, 3700, -1850, 1850 );
  v->GetXaxis()->SetLabelSize(0);
  v->GetYaxis()->SetLabelSize(0);
  v->SetStats(0);
  v->GetXaxis()->SetNdivisions(0);
  v->GetYaxis()->SetNdivisions(0);

  monitor->cd();
  h->Draw();
  makedetdisp->DrawBabyMIND(0);
  makedetdisp->DrawProtonModule(0);
  makehitdisp->DrawBMHit(bmdisp, 0);
  makehitdisp->DrawPMHit(bmdisp, 0);
  monitor->Update();

  monitor2->cd();
  v->Draw();
  makedetdisp->DrawBabyMIND(1);
  makedetdisp->DrawProtonModule(1);
  makehitdisp->DrawBMHit(bmdisp, 1);
  makehitdisp->DrawPMHit(bmdisp, 1);
  monitor2->Update();

#ifdef debug
  double r = 20;
  monitor->cd();
  for(int ipln=1; ipln<19; ipln++)
      for(int ich=0; ich<96; ich++)
	makehitdisp->bmyhit(ipln, ich, r, 1);

  for(int ipln=0; ipln<2; ipln++)
    {
      int pln=19+ipln;
      for(int ich=0; ich<7; ich++)
	makehitdisp->yasuyhit(0, pln, ich, r, 1);
    }

  for(int ipln=0; ipln<18; ipln++)
    {
      if(ipln==0)
	for(int ich=0; ich<24; ich++)
	  makehitdisp->pmyhit(ipln, ich, r, 1);
      
      if(ipln!=0)
	for(int ich=0; ich<32; ich++)
	  makehitdisp->pmyhit(ipln, ich, r, 1);
    }

  monitor->Update();

  monitor2->cd();
  for(int ipln=1; ipln<19; ipln++)
      for(int ich=0; ich<16; ich++)
	makehitdisp->bmxhit(ipln, ich, r, 1);

  for(int ipln=0; ipln<2; ipln++)
    {
      int pln=19+ipln;
      makehitdisp->yasuxhit(0, pln, 0, r, 1);
      makehitdisp->yasuxhit(1, pln, 0, r, 1);
    }

  for(int ipln=0; ipln<18; ipln++)
    {
      if(ipln==0)        
	for(int ich=0; ich<24; ich++)
	  makehitdisp->pmxhit(ipln, ich, r,1);

      if(ipln!=0)
	for(int ich=0; ich<32; ich++)
	  makehitdisp->pmxhit(ipln, ich, r,1);
    }

  monitor2->Update();

#endif
  
}




