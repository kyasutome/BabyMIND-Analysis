#include <iostream>
#include <stdio.h>

#include "WMDQCheck.hpp"

using namespace std;

WMDQCheck::WMDQCheck()
{ 
  for(int ihist=0; ihist<4; ihist++)
    {
      for(int ichip=0; ichip<3; ichip++)
	{
	  histname.Form("bcid_hist_%d_%d",ihist, ichip);
	  bcid_hist[ihist][ichip] = new TH1D(histname, histname, 200, 0, 80);

	  histname.Form("channel_adc_%d_%d",ihist, ichip);
	  channel_adc[ihist][ichip] = new TH2D(histname, histname, 32, 0, 32, 200, 100, 2000);

	  histname.Form("channel_adc_hit_%d_%d",ihist, ichip);
	  channel_adc_hit[ihist][ichip] = new TH2D(histname, histname, 32, 0, 32, 200, 100, 2000);

	  histname.Form("channel_adc_nohit_%d_%d",ihist, ichip);
	  channel_adc_nohit[ihist][ichip] = new TH2D(histname, histname, 32, 0, 32, 200, 100, 2000);

	  histname.Form("channel_hit_%d_%d",ihist, ichip);
	  channel_hit[ihist][ichip] = new TH2D(histname, histname, 32, 0, 32, 2, 0, 2);
	  
	  for(int ichan=0; ichan<32; ichan++)
	    {
	      histname.Form("charge_hist_%d_%d_%d", ihist, ichip, ichan);
	      charge_hist[ihist][ichip][ichan] = new TH1D(histname, histname, 1000, 100, 2000);
	      histname.Form("charge_hist_nohit_%d_%d_%d", ihist, ichip, ichan);
	      charge_hist_nohit[ihist][ichip][ichan] = new TH1D(histname, histname, 1000, 100, 2000);
	      histname.Form("time_hist_%d_%d_%d", ihist, ichip, ichan);
	      time_hist[ihist][ichip][ichan] = new TH1D(histname, histname, 1000, 100, 4095);
	    }//ichan
	}//ichip
    }//ihist
}

WMDQCheck::~WMDQCheck()
{
}

void WMDQCheck::ReadTree(TString filename, int dif)
{
  difid = dif;
  cout << "Start reading WAGASCI tree..." << '\n';
  if (gSystem->GetPathInfo(filename.Data(), info)!=0)
    {
      cout << "File" << filename << " done not exist" << '\n';
      exit(0);
    }else{
    Fileinput[difid] = new TFile(filename, "READ");
    treename.Form("tree_dif_%d", dif);
    if((TTree*)Fileinput[difid]->Get(treename))
      {
	wgtree[difid] = (TTree*)Fileinput[difid]->Get(treename);
	wgtree[difid]->SetBranchAddress("spill_number", &spill_number[difid]);
	wgtree[difid]->SetBranchAddress("spill_mode", &spill_mode[difid]);
	wgtree[difid]->SetBranchAddress("spill_count", &spill_count[difid]);
	wgtree[difid]->SetBranchAddress("chipid", chipid[difid]);
	wgtree[difid]->SetBranchAddress("chanid", chanid[difid]);
	wgtree[difid]->SetBranchAddress("colid", colid[difid]);
	wgtree[difid]->SetBranchAddress("charge", charge[difid]);
	wgtree[difid]->SetBranchAddress("time", time[difid]);
	wgtree[difid]->SetBranchAddress("bcid", bcid[difid]);
	wgtree[difid]->SetBranchAddress("hit", hit[difid]);
	wgtree[difid]->SetBranchAddress("gs", gs[difid]);
	wgtree[difid]->SetBranchAddress("debug_chip", debug_chip[difid]);
	wgtree[difid]->SetBranchAddress("debug_spill", debug_spill[difid]);

	Nentry = wgtree[difid]->GetEntries();
	cout << "Nentry= "  << Nentry << '\n';
      }
  }
}

bool WMDQCheck::SignalCreation(int ientry, int dif, WMDQData* wmdqdata)
{
  bool fillflag = false;
  difid=dif;
  wgtree[difid]->GetEntry(ientry);
  thespill=spill_number[difid] & 0x7FFF;
  thespillmode=spill_mode[difid];

  if(ModeCheck(thespillmode))
    for(int ichip=0; ichip<3; ichip++)
      {
	thechip=chipid[difid][ichip];
	for(int icol=0; icol<16; icol++)
	  {
	    thecolumn=colid[difid][icol];
	    thebcid=bcid[difid][ichip][icol];
	      if(BCIDCheck(thebcid))
		for(int ich=0; ich<32; ich++)
		  {
		    thechan=chanid[difid][ich];
		    thehit=hit[difid][ichip][ich][icol];
		    thecharge=charge[difid][ichip][ich][icol];
		    thetime=time[difid][ichip][ich][icol];		    
		   
		    wmdqdata->dif.push_back(dif);
		    wmdqdata->chip.push_back(thechip);
		    wmdqdata->chanid.push_back(thechan);
		    wmdqdata->time.push_back(thetime);
		    wmdqdata->bcid.push_back(thebcid);
		    wmdqdata->column.push_back(thecolumn);
		    wmdqdata->charge.push_back(thecharge);
		    wmdqdata->hit.push_back(thehit);
		    wmdqdata->spill=thespill;
		    wmdqdata->unixtime=-1;

		    //Fill
		    bcid_hist[difid][thechip]->Fill(thebcid);
		    if(thehit==1)
		      {
			charge_hist[difid][thechip][thechan]->Fill(thecharge);
			channel_adc_hit[difid][thechip]->Fill(thechan, thecharge);

			/*
			if(thecharge>=600)
			  cout << "BCID= " << thebcid << " Channel= " << thechan
			       << " charge= " << thecharge << " Time= " << thetime << '\n';
			*/
		      }
		    
		    if(thehit==0)
		      {
			charge_hist_nohit[difid][thechip][thechan]->Fill(thecharge);
			channel_adc_nohit[difid][thechip]->Fill(thechan, thecharge);
		      }

		    time_hist[difid][thechip][thechan]->Fill(thetime);
		    channel_adc[difid][thechip]->Fill(thechan, thecharge);
		    channel_hit[difid][thechip]->Fill(thechan, thehit);
		      
		    fillflag = true;
	
		  }//ich loop
	  }//icol loop
      }//ichip loop

  return fillflag;

}

bool WMDQCheck::ModeCheck(int spill_mode)
{
  bool modechecker = false;
  if(spill_mode==0)
    modechecker = true;

  return modechecker;
}

bool WMDQCheck::BCIDCheck(int bcid)
{
  bool bcidchecker = false;
  //if(bcid>=24 && bcid<=31)
  if(bcid!=-1)
    bcidchecker = true;

  return bcidchecker;
}

bool WMDQCheck::HitCheck(int hit)
{
  bool hitchecker = false;
  if(hit==1)
    hitchecker = true;

  return hitchecker;
}

int WMDQCheck::GetTEntry(int dif)
{
  difid=dif;
  return wgtree[difid]->GetEntries();
}

int WMDQCheck::GetBunch(int bcid)
{
  int bunch;
  if(bcid<24 || bcid>31)
    bunch=-1;

  if(bcid>=24 && bcid<=31)
    bunch=bcid-23;

  return bunch;
}
