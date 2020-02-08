#include <iostream>
#include <stdio.h>

#include "WGWMData.hpp"
#include "Dimension.cpp"

using namespace std;
//#define debug

WGWMdata::WGWMdata()
{ 
}

WGWMdata::~WGWMdata()
{
}

Dimension *fdimension = new Dimension();

void WGWMdata::ReadTree(TString filename, int dif)
{
  if(dif<4)  difid = dif;
  if(dif>=4)  difid = dif-4;

  cout << "Start reading WAGASCI tree..." << '\n';
  if (gSystem->GetPathInfo(filename.Data(), info)!=0)
    {
      cout << "File" << filename << " done not exist" << '\n';
      exit(0);
    }else{
    Fileinput[0][dif] = new TFile(filename, "READ");
    Fileinput[1][dif] = new TFile(filename, "READ");
    treename.Form("tree_dif_%d", dif);
    if((TTree*)Fileinput[0][dif]->Get(treename))
      {
	
	if(dif<4)
	  {
	    wgtree[dif] = (TTree*)Fileinput[0][dif]->Get(treename);
	    wgtree[dif]->SetBranchAddress("spill_number", &spill_number[dif]);
	    wgtree[dif]->SetBranchAddress("spill_mode", &spill_mode[dif]);
	    wgtree[dif]->SetBranchAddress("spill_count", &spill_count[dif]);
	    wgtree[dif]->SetBranchAddress("chipid", chipid_wm[difid]);
	    wgtree[dif]->SetBranchAddress("chanid", chanid_wm[difid]);
	    wgtree[dif]->SetBranchAddress("colid", colid_wm[difid]);
	    wgtree[dif]->SetBranchAddress("charge", charge_wm[difid]);
	    wgtree[dif]->SetBranchAddress("time", time_wm[difid]);
	    wgtree[dif]->SetBranchAddress("bcid", bcid_wm[difid]);
	    wgtree[dif]->SetBranchAddress("hit", hit_wm[difid]);
	    wgtree[dif]->SetBranchAddress("gs", gs_wm[difid]);
	    wgtree[dif]->SetBranchAddress("debug_chip", debug_chip_wm[difid]);
	    wgtree[dif]->SetBranchAddress("debug_spill", debug_spill_wm[difid]);
	  }

	if(dif>=4)
	  {
	    wgtree[dif] = (TTree*)Fileinput[0][dif]->Get(treename);
	    wgtree[dif]->SetBranchAddress("spill_number", &spill_number[dif]);
	    wgtree[dif]->SetBranchAddress("spill_mode", &spill_mode[dif]);
	    wgtree[dif]->SetBranchAddress("spill_count", &spill_count[dif]);
	    wgtree[dif]->SetBranchAddress("chipid", chipid_wg[difid]);
	    wgtree[dif]->SetBranchAddress("chanid", chanid_wg[difid]);
	    wgtree[dif]->SetBranchAddress("colid", colid_wg[difid]);
	    wgtree[dif]->SetBranchAddress("charge", charge_wg[difid]);
	    wgtree[dif]->SetBranchAddress("time", time_wg[difid]);
	    wgtree[dif]->SetBranchAddress("bcid", bcid_wg[difid]);
	    wgtree[dif]->SetBranchAddress("hit", hit_wg[difid]);
	    wgtree[dif]->SetBranchAddress("gs", gs_wg[difid]);
	    wgtree[dif]->SetBranchAddress("debug_chip", debug_chip_wg[difid]);
	    wgtree[dif]->SetBranchAddress("debug_spill", debug_spill_wg[difid]);
	  }
       

	Nentry[dif] = wgtree[dif]->GetEntries();
	cout << "DIF" << dif << " Nentry= "  << Nentry[dif] << '\n';
      }
  }

}

bool WGWMdata::SignalCreation(int dif, int entry, WGRecon* wgrecon)
{
  bool fillflag = false;

  wgtree[dif]->GetEntry(entry);
  thespill=spill_number[dif] & 0x7FFF;
  thespillmode=spill_mode[dif];

  if(dif<4)
    {
      difid=dif;      
      if(ModeCheck(thespillmode))
	{
	  for(int ichip=0; ichip<3; ichip++)
	    {
	      thechip=chipid_wm[difid][ichip];
	      for(int icol=0; icol<16; icol++)
		{
		  thecolum=colid_wm[difid][icol];
		  thebcid=bcid_wm[difid][ichip][icol];
		  if(BCIDCheck(thebcid))
		    for(int ich=0; ich<32; ich++)
		      {
			thechan=chanid_wm[difid][ich];
			thehit=hit_wm[difid][ichip][ich][icol];
			thecharge=charge_wm[difid][ichip][ich][icol];
			
			if(HitCheck(thehit) && thecharge>600)
			  {
			    thetime=time_wm[difid][ichip][ich][icol];		   
			    wgrecon->mod.push_back(dif/2+3);
			    wgrecon->view.push_back(dif);
			    wgrecon->pln.push_back(thechip);
			    wgrecon->channel.push_back(thechan);
			    wgrecon->time.push_back(thetime);
			    wgrecon->charge.push_back(thecharge);
			    wgrecon->bunch.push_back(GetBunch(thebcid));
			    wgrecon->spill=thespill;
			    wgrecon->unixtime=-1;
			    
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
	}//if modecheck
    }//if dif<4

  if(dif>=4)
    {
      difid=dif-4;      
      if(ModeCheck(thespillmode))
	{
	  for(int ichip=0; ichip<20; ichip++)
	    {
	      thechip=chipid_wg[difid][ichip];
	      for(int icol=0; icol<16; icol++)
		{
		  thecolum=colid_wg[difid][icol];
		  thebcid=bcid_wg[difid][ichip][icol];
		  if(BCIDCheck(thebcid))
		    for(int ich=0; ich<32; ich++)
		      {
			thechan=chanid_wg[difid][ich];
			thehit=hit_wg[difid][ichip][ich][icol];
			thecharge=charge_wg[difid][ichip][ich][icol];
			
			if(HitCheck(thehit) && thecharge>600)
			  {
			    thetime=time_wg[difid][ichip][ich][icol];		   
			    wgrecon->mod.push_back(dif/2-1);
			    wgrecon->view.push_back(dif);
			    wgrecon->pln.push_back(thechip);
			    wgrecon->channel.push_back(thechan);
			    wgrecon->charge.push_back(thecharge);
			    wgrecon->time.push_back(thetime);
			    wgrecon->bunch.push_back(GetBunch(thebcid));
			    wgrecon->spill=thespill;
			    wgrecon->unixtime=-1;
			    
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
	}//if modecheck
    }//if dif>=4
  
  return fillflag;
}

bool WGWMdata::NocutCreation(int dif, int entry, WGRecon* wgrecon)
{
  bool fillflag = false;

  wgtree[dif]->GetEntry(entry);
  thespill=spill_number[dif] & 0x7FFF;
  thespillmode=spill_mode[dif];
  if(thespillmode==1)
    fillflag=true;
  
  wgrecon->spill=thespill;
  wgrecon->unixtime=-1;
        
  return fillflag;
}


bool WGWMdata::ModeCheck(int spill_mode)
{
  bool modechecker = false;
  if(spill_mode==1)
    modechecker = true;

  return modechecker;
}


bool WGWMdata::BCIDCheck(int bcid)
{
  bool bcidchecker = false;
  if(bcid>=24 && bcid<=31)
    bcidchecker = true;

  return bcidchecker;
}

bool WGWMdata::HitCheck(int hit)
{
  bool hitchecker = false;
  if(hit==1)
    hitchecker = true;

  return hitchecker;

}

int WGWMdata::GetTEntry(int dif)
{
  return wgtree[dif]->GetEntries();
}

int WGWMdata::GetBunch(int bcid)
{
  int bunch;
  if(bcid<24 || bcid>31)
    bunch=-1;

  if(bcid>=24 && bcid<=31)
    bunch=bcid-23;

  return bunch;
}
