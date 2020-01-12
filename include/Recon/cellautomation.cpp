#include <iostream>
#include <stdio.h>

#include "cellautomation.hpp"

using namespace std;

CellAutomation::CellAutomation()
{ 
  for(int iview=0; iview<2; iview++)
    for(int ibunch=0; ibunch<9; ibunch++)
      {
	histname.Form("beforefit_%d_%d", iview, ibunch);
	beforefit[iview][ibunch] = new TH2D(histname, histname, 18, 0, 18, nch[iview], 0, nch[iview]);
	histname.Form("afterfit_%d_%d", iview, ibunch);
	afterfit[iview][ibunch] = new TH2D(histname, histname, 18, 0, 18, nch[iview], 0, nch[iview]);
      }
}


CellAutomation::~CellAutomation()
{
}

void CellAutomation::Clustering()
{

}

void CellAutomation::FillBeforeFit(BMDisp* bmdisp)
{
  Nentry = bmdisp->mod.size();
  for(int idata=0; idata<Nentry; idata++)
    {
      mod = bmdisp->mod.at(idata);
      view = bmdisp->view.at(idata);
      pln = bmdisp->pln.at(idata);
      channel = bmdisp->channel.at(idata);
      bunch = bmdisp->bunch.at(idata);

      if(mod==5 && bunch!=-1)
	{
	  beforefit[(int)view][(int)bunch]->Fill(pln, channel);
	  beforefit[(int)view][0]->Fill(pln, channel);
	}
    }
}

void CellAutomation::FillAfterFit(BMDisp* bmdisp)
{
  

}
