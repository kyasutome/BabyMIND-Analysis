#include <iostream>
#include <stdio.h>

#include "WGData.hpp"
#include "Dimension.cpp"

using namespace std;

//#define debug

WGdata::WGdata()
{ 
  for(int ihist=0; ihist<4; ihist++)
    {
      histname.Form("bcid_hist_%d",ihist);
      bcid_hist[ihist] = new TH1D(histname, histname, 40, 0, 40);
    }
}

WGdata::~WGdata()
{
}

Dimension *fdimension = new Dimension();

void WGdata::ReadTree(TString filename, int dif)
{
  difid = dif-4;
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

bool WGdata::SignalCreation(int ientry, int dif, WGRecon* wgrecon)
{
  bool fillflag = false;
  difid=dif-4;
  wgtree[difid]->GetEntry(ientry);
  thespill=spill_number[difid] & 0x7FFF;
  thespillmode=spill_mode[difid];

  if(ModeCheck(thespillmode))
    for(int ichip=0; ichip<20; ichip++)
      {
	thechip=chipid[difid][ichip];
	for(int icol=0; icol<16; icol++)
	  {
	    thecolum=colid[difid][icol];
	    thebcid=bcid[difid][ichip][icol];
	      if(BCIDCheck(thebcid))
		for(int ich=0; ich<32; ich++)
		  {
		    thechan=chanid[difid][ich];
		    thehit=hit[difid][ichip][ich][icol];
		    thecharge=charge[difid][ichip][ich][icol];
		    
		    if(HitCheck(thehit))
		      {
			thetime=time[difid][ichip][ich][icol];		   
			wgrecon->mod.push_back(dif/2-1);
			//wgrecon->view.push_back(abs(dif%2-1));
			wgrecon->view.push_back(dif);
			wgrecon->pln.push_back(thechip);
			wgrecon->channel.push_back(thechan);
			wgrecon->time.push_back(thetime);
			wgrecon->bunch.push_back(GetBunch(thebcid));
			wgrecon->spill=thespill;
			wgrecon->unixtime=-1;

			bcid_hist[difid]->Fill(thebcid);			
			fillflag = true;

#ifdef debug
                        double posx, posy, posz;
                        fdimension->get_pos_wg_FC(dif, thechip, thechan, &posx, &posy, &posz);
                        cout << posx << " " << posy << " " << posz << '\n';
#endif

		      }
		  
		  }//ich loop
	  }//icol loop
      }//ichip loop
  return fillflag;
}

bool WGdata::ModeCheck(int spill_mode)
{
  bool modechecker = false;
  if(spill_mode==1)
    modechecker = true;

  return modechecker;
}

bool WGdata::BCIDCheck(int bcid)
{
  bool bcidchecker = false;
  if(bcid!=-1)
    bcidchecker = true;

  return bcidchecker;
}

bool WGdata::HitCheck(int hit)
{
  bool hitchecker = false;
  if(hit==1)
    hitchecker = true;

  return hitchecker;

}

int WGdata::GetTEntry(int dif)
{
  difid=dif-4;
  return wgtree[difid]->GetEntries();
}

int WGdata::GetBunch(int bcid)
{
  int bunch;
  if(bcid<24 || bcid>31)
    bunch=-1;

  if(bcid>=24 && bcid<=31)
    bunch=bcid-23;

  return bunch;
}
