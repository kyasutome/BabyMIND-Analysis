#include <iostream>
#include <fstream>
#include <vector>

#include "easyrecon.hpp"

using namespace std;
//#define debug

EasyRecon::EasyRecon()
{
  linear = new TF1("linear", "[0]+[1]*x", -4300, -3400);
  linear->SetParameters(0, 0);
  //fithist = new TH2D("fithist", "fithist", 50, 0, 50, 50, 0, 50);
  fithist = new TH2D("fithist", "fithist", 300, -4300, -3400, 300, -3000, -1500);
}

EasyRecon::~EasyRecon()
{
}

void EasyRecon::Recon(EVTCluster* evtcluster, BasicRecon* basicrecon[])
{
  fithist->Reset();
  for(int imod=0; imod<7; imod++)
    {
      for(int iview=0; iview<2; iview++)
	{
	  plane[imod][iview].clear();
	  channel[imod][iview].clear();
	  splane[imod][iview].clear();
	  schannel[imod][iview].clear();
	  
	  positionx[imod][iview].clear();
	  positiony[imod][iview].clear();
	  positionz[imod][iview].clear();
	  
	  sdposx[imod][iview].clear();
	  sdposy[imod][iview].clear();
	  sdposz[imod][iview].clear();

	  for(int ibunch=0; ibunch<9; ibunch++)
	    basicrecon[imod]->Nhit[iview][ibunch]=0;
	}

    }


  
  for(int ihit=0; ihit<evtcluster->mod.size(); ihit++)
    {
      bunch = evtcluster->bunch.at(ihit);
      mod = evtcluster->mod.at(ihit);
      view = evtcluster->view.at(ihit);
      wgview = fabs((int)evtcluster->view.at(ihit)%2-1);
      pln = evtcluster->pln.at(ihit);
      ch = evtcluster->channel.at(ihit);
      posx = evtcluster->posx.at(ihit);
      posy = evtcluster->posy.at(ihit);
      posz = evtcluster->posz.at(ihit);
      dposx = evtcluster->dposx.at(ihit);
      dposy = evtcluster->dposy.at(ihit);
      dposz = evtcluster->dposz.at(ihit);

      if(mod==0 || mod==5 || mod==6)
	view = view;
      if(mod==1 || mod==2)
	view = wgview;
      if(mod==3 || mod==4)
	view = 1;

      plane[mod][view].push_back(pln);
      channel[mod][view].push_back(ch);
      splane[mod][view].push_back(pln);
      schannel[mod][view].push_back(ch);
      
      positionx[mod][view].push_back(dposx);
      positiony[mod][view].push_back(dposy);
      positionz[mod][view].push_back(dposz);
      sdposx[mod][view].push_back(dposx);
      sdposy[mod][view].push_back(dposy);
      sdposz[mod][view].push_back(dposz);
      
      if(bunch!=-1)
	{
	  basicrecon[mod]->Nhit[view][bunch]++;	  
	  basicrecon[mod]->Nhit[view][0]++;
	}     
 
    }

  /*
  if(plane[0][1].size()>6)
    {
      Fitting(linear, positionz[0][1], positionxy[0][1], fitpar);      
      basicrecon[0]->angle[1] = TMath::ATan(fitpar[1])*180/3.14;
    }
  */
    

  //cout << "intercept= " << fitpar[0] << " slope= " << fitpar[1] << '\n';
}

void EasyRecon::Fitting(TF1* function, vector<int> positionz, vector<int> positionxy, double fitpar[])
{
  for(int ihit=0; ihit<positionz.size(); ihit++)
    {
      fithist->Fill(positionz.at(ihit), positionxy.at(ihit));            
    }

  fithist->Fit(function,"Q");
  linear->GetParameters(fitpar);
}

bool EasyRecon::NHCheck(int mod, int view, BasicRecon* basicrecon, vector<int> *ataribunch)
{
  bool nhcheck = false;

  for(int ibunch=1; ibunch<=8; ibunch++)
    {
      if(mod==0 || mod==1 || mod==2)
	if(basicrecon->Nhit[view][ibunch]>6)
	  {
	    ataribunch->push_back(ibunch);
	    nhcheck = true;
	  }
      
      if((mod==3 || mod==4) && basicrecon->Nhit[view][ibunch]>12)
	{
	  ataribunch->push_back(ibunch);
	  nhcheck = true;
	}
      
      if(mod==5)
	if(basicrecon->Nhit[view][ibunch]>0)
	  {
	    ataribunch->push_back(ibunch);
	    nhcheck = true;
	  }
    }

  return nhcheck;

}

bool EasyRecon::FVCheck(int mod, int view)
{
  //FVCheck 0 <= pln <= 18
  //FVCheck 0 <= channel <= 32

  bool fvcheck = true;
  int firstpln, endpln;
  int firstch, endch;
  double firstz, endz;
  double firstx, endx;
  double firsty, endy;

  sort(splane[mod][view].begin(), splane[mod][view].end());
  sort(schannel[mod][view].begin(), schannel[mod][view].end());

  sort(sdposz[mod][view].begin(), sdposz[mod][view].end());
  sort(sdposx[mod][view].begin(), sdposx[mod][view].end());
  sort(sdposy[mod][view].begin(), sdposy[mod][view].end());

  firstpln = splane[mod][view].at(0);
  firstch = schannel[mod][view].at(0);
  endpln = splane[mod][view].at(splane[mod][view].size()-1);
  endch = schannel[mod][view].at(schannel[mod][view].size()-1);

  firstx = sdposx[mod][view].at(0);
  firsty = sdposy[mod][view].at(0);
  firstz = sdposz[mod][view].at(0);

  endx = sdposx[mod][view].at(sdposx[mod][view].size()-1);
  endy = sdposy[mod][view].at(sdposy[mod][view].size()-1);
  endz = sdposz[mod][view].at(sdposz[mod][view].size()-1);

  if(mod==0)
    {
      if(view==0)
	{
	  if(firstpln<=1)
	    fvcheck = false;
	  
	  if(firstch<=3 || endch>=28)
	    fvcheck = false;
	}
      
      if(view==1)
	{
	  if(firstpln<=1)
	    fvcheck = false;
	  
	  if(firstch<=3 || endch>=28)
	    fvcheck = false;
	}
    }

  if(mod==1 || mod==2)
    {
      if(view==0)
	{
	  if(firstz<=-150)
	    fvcheck = false;
	  
	  if(firsty<=-300 || firsty>=300)
	    fvcheck = false;
	}
      
      if(view==1)
	{
	  if(firstz<=-150)
	    fvcheck = false;
	  
	  if(firstx<=-300 || firstx>=300)
	    fvcheck = false;
	}
    }

  if(mod==3 || mod==4)
    {      
      if(mod==3 && view==1)
	{
	  if(firstz<=150)
	    fvcheck = false;
	  
	  if(endx>=400)
	    fvcheck = false;
	}

      if(mod==4 && view==1)
	{
	  if(firstz<=150)
	    fvcheck = false;
	  
	  if(firstx<=50)
	    fvcheck = false;
	}

    }

  if(mod==5)
    {      
      if(view==0)
	{
	  if(firstpln==1)
	    fvcheck = false;
	  
	  if(endch>=93)
	    fvcheck = false;
	}

      if(view==1)
	{
	  if(firstpln==1)
	    fvcheck = false;
	  
	  if(endch>=30)
	    fvcheck = false;
	}
    }

  return fvcheck;
}

bool EasyRecon::SFVCheck(int mod, int view, double posxy[2], double posz[2])
{
  bool fvcheck = true;

  if(mod==0)
    {
      if(view==0)
	{
	  if(posz[0]<=150)
	    fvcheck = false;
	  
	  if(posxy[0]<=40 || posxy[1]>=1100)
	    fvcheck = false;
	}
      
      if(view==1)
	{
	  if(posz[0]<=150)
	    fvcheck = false;
	  
	  if(posxy[0]<=40 || posxy[1]>=1100)
	    fvcheck = false;
	}
    }

  if(mod==1 || mod==2)
    {
      if(view==0)
	{
	  if(posz[0]<=-180)
	    fvcheck = false;
	  
	  if(posxy[0]<=-400 || posxy[1]>=400)
	    fvcheck = false;
	}
      
      if(view==1)
	{
	  if(posz[0]<=-180)
	    fvcheck = false;
	  
	  if(posxy[0]<=-400 || posxy[1]>=400)
	    fvcheck = false;
	}
    }

  if(mod==3 || mod==4)
    {      
      if(mod==3 && view==1)
	{
	  if(posz[0]<=150)
	    fvcheck = false;
	  
	  if(posxy[1]>=400)
	    fvcheck = false;
	}

      if(mod==4 && view==1)
	{
	  if(posz[0]<=150)
	    fvcheck = false;
	  
	  if(posxy[1]<=50)
	    fvcheck = false;
	}

    }

  if(mod==5)
    {      
      if(view==0)
	{
	  if(posz[0]<=250)
	    fvcheck = false;
	  
	  if(posxy[0]<=-900 || posxy[1]>=900)
	    fvcheck = false;
	}

      if(view==1)
	{
	  if(posz[0]<=250)
	    fvcheck = false;
	  
	  if(posxy[0]<=-1250 || posxy[1]>=1250)
	    fvcheck = false;
	}
    }

  return fvcheck;
}
