#include <iostream>
#include <fstream>
#include <vector>

#include "MakeEachMonitor.hpp"
#include "MakeHitDisp.cpp" // should include HitDisp before DetDisp
#include "MakeDetDisp.cpp"

using namespace std;
//#define debug
//#define WallMRD
#define WAGASCI

MakeEachMonitor::MakeEachMonitor()
{
}

MakeEachMonitor::~MakeEachMonitor()
{
}

MakeHitDisp* makehitdisp = new MakeHitDisp();
MakeDetDisp* makedetdisp = new MakeDetDisp();

void MakeEachMonitor::Display(BMDisp* bmdisp)
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

  v = new TH2F("","Top View", 7200, -3000, 4200, 5000, -2500, 2500 );
  v->GetXaxis()->SetLabelSize(0);
  v->GetYaxis()->SetLabelSize(0);
  v->SetStats(0);
  v->GetXaxis()->SetNdivisions(0);
  v->GetYaxis()->SetNdivisions(0);

#ifdef WallMRD
  monitor->cd();
  h->Draw();
  monitor->Update();
  monitor2->cd();
  v->Draw();
  makedetdisp->DrawWallMRD(0);
  makedetdisp->DrawWallMRD(1);
  makehitdisp->DrawWMHit(bmdisp, 3);
  makehitdisp->DrawWMHit(bmdisp, 4);
  monitor2->Update();
#endif

#ifdef WAGASCI
  monitor->cd();
  h->Draw();
  makedetdisp->DrawWAGASCI(0,0);
  makedetdisp->DrawWAGASCI(1,0);
  makehitdisp->DrawWGHit(bmdisp, 0, 1);
  makehitdisp->DrawWGHit(bmdisp, 0, 2);
  monitor->Update();

  monitor2->cd();
  v->Draw();
  makedetdisp->DrawWAGASCI(0,1);
  makedetdisp->DrawWAGASCI(1,1);
  makehitdisp->DrawWGHit(bmdisp, 1, 1);
  makehitdisp->DrawWGHit(bmdisp, 1, 2);
  monitor2->Update();
#endif

  //makedetdisp->DrawBabyMIND(0);
  //makedetdisp->DrawProtonModule(0);
  //makehitdisp->DrawBMHit(bmdisp, 0);
  //makehitdisp->DrawPMHit(bmdisp, 0);

  //makedetdisp->DrawBabyMIND(1);
  //makedetdisp->DrawProtonModule(1);
  //makedetdisp->DrawWAGASCI(0,1);
  //makedetdisp->DrawWAGASCI(1,1);
  //makedetdisp->DrawWallMRD(0);
  //makedetdisp->DrawWallMRD(1);
  //makehitdisp->DrawBMHit(bmdisp, 1);
  //makehitdisp->DrawPMHit(bmdisp, 1);
  //makehitdisp->DrawWGHit(bmdisp, 1);
  //makehitdisp->DrawWGHit(bmdisp, 2);
  //makehitdisp->DrawWMHit(bmdisp, 3);
  //makehitdisp->DrawWMHit(bmdisp, 4);

#ifdef debug
  double r = 10;
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

    for(int ichip=0; ichip<20; ichip++)	
      for(int ichan=0; ichan<32; ichan++)
	{
	  makehitdisp->wgyhit(5, ichip, ichan, r, 1);	    
	  makehitdisp->wgyhit(7, ichip, ichan, r, 1); 
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

    for(int ichip=0; ichip<20; ichip++)	
      for(int ichan=0; ichan<32; ichan++)
	{
	  makehitdisp->wgxhit(4, ichip, ichan, r, 1);	    
	  makehitdisp->wgxhit(6, ichip, ichan, r, 1);
	}

    for(int ichip=0; ichip<3; ichip++)	
      for(int ichan=0; ichan<32; ichan++)
	{
	  makehitdisp->wmhit(0, ichip, ichan, r, 1);	    
	  makehitdisp->wmhit(1, ichip, ichan, r, 1); 
	  makehitdisp->wmhit(2, ichip, ichan, r, 1);	    
	  makehitdisp->wmhit(3, ichip, ichan, r, 1); 
	}

  monitor2->Update();

#endif
  
}




