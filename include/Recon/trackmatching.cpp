#include <iostream>
#include <stdio.h>

#include "trackmatching.hpp"
#include "Dimension.cpp"
using namespace std;

Dimension* fdimension = new Dimension();

TrackMatching::TrackMatching()
{ 
  pmdisp = new TH2D("pmdisp", "pmdisp", 24, 0, 24, 48, 0, 48);
  pmdisp_corr = new TH2D("pmdisp_corr", "pmdisp_corr", 500, -2000, -1000, 100, -500, 500);
  bmdisp_corr = new TH2D("bmdisp_corr", "bmdisp_corr", 500, -1000, 3000, 100, -1000, 2000);
  //pmbmdisp = new TH2D("pmbmdisp", "pmbmdisp", 24, 0, 24, 48, 0, 48);

  linear = new TF1("linear", "[0]+[1]*x", -2000, -1000);
  linear->SetParameters(0, 0);
}


TrackMatching::~TrackMatching()
{
}

bool TrackMatching::Matching_pmbm(BMDisp* bmdisp, BMCluster* bmcluster[100])
{
  matching = false;
  Clear();
  for(int ihit=0; ihit<bmdisp->mod.size(); ihit++)
    {
      mod = bmdisp->mod.at(ihit);
      view = bmdisp->view.at(ihit);
      pln = bmdisp->pln.at(ihit);
      channel = bmdisp->channel.at(ihit);

      if(mod==0)
	{
	  fdimension->get_pos_pm_FC(mod, view, pln, channel, &posx, &posy, &posz);      
	  if(view==0)
	    {
	      pmdisp_corr->Fill(posz, posy);
	    }
	}

      
      if(mod==5)
	{
	  fdimension->get_pos_bm_FC(mod, view, pln, channel, &posx, &posy, &posz);      
	  bmdisp_corr->Fill(posz, posy);
	}      
    }

  pmdisp_corr->Fit(linear);
  intercept = linear->GetParameter(0);
  slope = linear->GetParameter(1);
  estimatedy = ExtraporatedFromPM();
  cout << "Estimation= " << estimatedy << '\n';

  for(int icluster=0; icluster<100; icluster++)
    {
      if(bmcluster[icluster]->mod.size()==0) continue;
      mod = bmcluster[icluster]->mod.at(0);
      view = bmcluster[icluster]->view.at(0);
      pln = bmcluster[icluster]->pln.at(0);
      channel = bmcluster[icluster]->channel.at(0);
      fdimension->get_pos_bm_FC(mod, view, pln, channel, &posx, &posy, &posz);      
      datay = posy;
      cout << "Data= " << datay << '\n';

      if(fabs(estimatedy-datay)<dist)
	{
	  matching = true;
	  trydif = fabs(estimatedy-datay);
	  if(trydif<refdif)
	    {
	      refdif = trydif;
	      matchingid = icluster;
	    }
	}
    }//icluster

  cout << "refdif= " << refdif << " matchingid= " << matchingid << '\n';
  

  return matching;
}

double TrackMatching::ExtraporatedFromPM()
{
  double estimation;
  estimation = slope*firstz_inbm + intercept;
  return estimation;
}


void TrackMatching::Clear()
{
  pmdisp->Reset();
  pmdisp_corr->Reset();
  bmdisp_corr->Reset();
}
