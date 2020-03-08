#include <iostream>
#include <fstream>
#include <vector>

#include "MakeMonitor.hpp"
#include "MakeHitDisp.cpp" // should include HitDisp before DetDisp
#include "MakeDetDisp.cpp"

#include "TText.h"

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

void MakeMonitor::Display(EVTCluster* evtcluster)
{

  if(!firstdraw)
    {
      h->Delete();
      v->Delete();
    }

  if(firstdraw)
    {
      monitor = new TCanvas("monitor", "monitor", 2000, 1600);
      pad_side = new TPad("pad_side","This is Side View",0.03,0.23,0.51,0.97);
      pad_top = new TPad("pad_top","This is Top View",0.53,0.23,0.97,0.97);
      pad_bottom = new TPad("pad_bottom","This is Text",0.03,0.03,0.97,0.23);

      pad_side->SetFillColor(11);
      pad_side->Draw();
      pad_top->SetFillColor(11);
      pad_top->Draw();
      pad_bottom->SetFillColor(0);
      pad_bottom->Draw();
      firstdraw=false;
    }


  string dayofweek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  spillnumber = evtcluster->spillnum;
  unixtime = evtcluster->unixtime;
  timer = localtime(&unixtime);
  year = timer->tm_year+1900;
  mon = timer->tm_mon+1;
  day = timer->tm_mday;
  hour = timer->tm_hour;
  min = timer->tm_min;
  sec = timer->tm_sec;
  TIME.Form("%04d/%02d/%02d %s %02d:%02d:%02d", year, mon, day, dayofweek[timer->tm_wday].c_str(), hour, min, sec);
  SPILL.Form("WAGASCI spill number%5d", spillnumber);

  h = new TH2F("","Side View", 7200, -3000, 4200, 7200, -3000, 4200);
  h->GetXaxis()->SetLabelSize(0);
  h->GetYaxis()->SetLabelSize(0);
  h->SetStats(0);
  h->GetXaxis()->SetNdivisions(0);
  h->GetYaxis()->SetNdivisions(0);

  v = new TH2F("","Top View", 7200, -3000, 4200, 7200, -3000, 4200 );
  v->GetXaxis()->SetLabelSize(0);
  v->GetYaxis()->SetLabelSize(0);
  v->SetStats(0);
  v->GetXaxis()->SetNdivisions(0);
  v->GetYaxis()->SetNdivisions(0);

  monitor->cd();
  pad_side->cd();
  h->Draw();
  makedetdisp->DrawBabyMIND(0);
  makedetdisp->DrawProtonModule(0);
  makedetdisp->DrawWAGASCI(1,0);
  makedetdisp->DrawWAGASCI(2,0);
  makehitdisp->DrawHit(evtcluster, 0);
  //makehitdisp->DrawBMHit(evtcluster, 0);
  //makehitdisp->DrawPMHit(evtcluster, 0);
  //makehitdisp->DrawWGHit(evtcluster, 0, 1);
  //makehitdisp->DrawWGHit(evtcluster, 0, 2);

  pad_top->cd();
  v->Draw();
  makedetdisp->DrawBabyMIND(1);
  makedetdisp->DrawProtonModule(1);
  makedetdisp->DrawWAGASCI(1,1);
  makedetdisp->DrawWAGASCI(2,1);
  makedetdisp->DrawWallMRD(3);
  makedetdisp->DrawWallMRD(4);
  makehitdisp->DrawHit(evtcluster, 1);
  //makehitdisp->DrawBMHit(evtcluster, 1);
  //makehitdisp->DrawPMHit(evtcluster, 1);
  //makehitdisp->DrawWGHit(evtcluster, 1, 1);
  //makehitdisp->DrawWGHit(evtcluster, 1, 2);
  //makehitdisp->DrawWMHit(evtcluster, 3);
  //makehitdisp->DrawWMHit(evtcluster, 4);

  cout << TIME.Data() << '\n';

  pad_bottom->cd();
  timeinfo = new TText(0.3, 0.6, TIME);
  timeinfo->SetTextSize(0.3);
  spillinfo = new TText(0.27, 0.2, SPILL);
  spillinfo->SetTextSize(0.3);

  timeinfo->Draw("");
  spillinfo->Draw("");
  monitor->Update();

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




