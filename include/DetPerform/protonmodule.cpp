#include <iostream>
#include <fstream>
#include <vector>

#include "protonmodule.hpp"

using namespace std;
//#define debug

ProtonModule::ProtonModule()
{
  linear = new TF1("linear", "[0]+[1]*x", -4300, -3400);
  linear->SetParameters(0, 0);
  //fithist = new TH2D("fithist", "fithist", 50, 0, 50, 50, 0, 50);
  fithist = new TH2D("fithist", "fithist", 300, -4300, -3400, 300, -3000, -1500);

}

ProtonModule::~ProtonModule()
{
}


void ProtonModule::EasyRecon(EVTCluster* evtcluster, BasicRecon* basicrecon)
{
  fithist->Reset();
  plane.clear();
  channel.clear();
  positionz.clear();
  positionx.clear();

  for(int ihit=0; ihit<evtcluster->mod.size(); ihit++)
    {
      mod = evtcluster->mod.at(ihit);
      view = evtcluster->view.at(ihit);
      pln = evtcluster->pln.at(ihit);
      ch = evtcluster->channel.at(ihit);
      posx = evtcluster->posx.at(ihit);
      posz = evtcluster->posz.at(ihit);

      if(mod==0 && view==1)
	{
	  plane.push_back(pln);
	  channel.push_back(ch);
	  positionz.push_back(posz);
	  positionx.push_back(posx);
	}
    }

  if(plane.size()>6)
    {
      Fitting(linear, positionz, positionx, fitpar);      
      basicrecon->angle[1] = TMath::ATan(fitpar[1])*180/3.14;
    }

  //cout << "intercept= " << fitpar[0] << " slope= " << fitpar[1] << '\n';
}

void ProtonModule::Fitting(TF1* function, vector<int> plane, vector<int> channel, double fitpar[])
{
  for(int ihit=0; ihit<plane.size(); ihit++)
    {
      fithist->Fill(plane.at(ihit), channel.at(ihit));            
    }

  fithist->Fit(function,"Q");
  linear->GetParameters(fitpar);

}
