#include <iostream>
#include <stdio.h>

#include "Calibration.hpp"

using namespace std;

Calibration::Calibration()
{ 
  hist_hg[0] = new TH1D("hist_hg_bm_hor", "hist_hg_bm_hor", 4096, 1, 4096);
  hist_tdif[0] = new TH1D("hist_tdif_bm_hor", "hist_tdif_bm_hor", 100, 0, 100);

  hist_hg[1] = new TH1D("hist_hg_bm_ver", "hist_hg_bm_ver", 4096, 1, 4096);
  hist_tdif[1] = new TH1D("hist_tdif_bm_ver", "hist_tdif_bm_ver", 100, 0, 100);

  for(int ipln=0; ipln<2; ipln++)
    for(int ich=0; ich<14; ich++)
      {
	histname.Form("hist_hg_yasu_%d_%d", ipln,ich);
	hist_hg_yasu[ipln][ich] = new TH1D(histname, histname, 4096, 1, 4096);
	histname.Form("hist_tdif_yasu_%d_%d", ipln,ich);
	hist_tdif_yasu[ipln][ich] = new TH1D(histname, histname, 100, 0, 100);
      }
}

Calibration::~Calibration()
{
}

void Calibration::MakeDist(BMBasicRecon* bmbasicrecon)
{
  for(int idata=0; idata<bmbasicrecon->mod.size(); idata++)
    {
      mod = bmbasicrecon->mod.at(idata);
      view = bmbasicrecon->view.at(idata);
      pln = bmbasicrecon->pln.at(idata);
      channel = bmbasicrecon->channel.at(idata);
      HG = bmbasicrecon->HG.at(idata);
      timedif = bmbasicrecon->timedif.at(idata);

      if(mod==5 && view==0)
	{
	  hist_hg[0]->Fill(HG);
	  hist_tdif[0]->Fill(timedif);
	}
      if(mod==5 && view==1)
	{
	  hist_hg[1]->Fill(HG);
	  hist_tdif[1]->Fill(timedif);
	}
      if(mod==6)
	{
	  int corrpln = pln-19;
	  int corrch = channel;
	  //cout << corrpln << " " << corrch << '\n';
	  if(corrch<=13)
	    {
	      hist_hg_yasu[corrpln][corrch]->Fill(HG);
	      hist_tdif_yasu[corrpln][corrch]->Fill(timedif);
	    }
	}
    }
  
}


void Calibration::CalcGain(double *gain)
{
  *gain = 34.0;
}
