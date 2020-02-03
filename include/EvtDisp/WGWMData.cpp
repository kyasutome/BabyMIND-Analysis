#include <iostream>
#include <stdio.h>

#include "WGWMData.hpp"
#include "Dimension.cpp"

using namespace std;
//#define debug

WGWMdata::WGWMdata()
{ 
  for(int ifile=0; ifile<2; ifile++)
    for(int idif=0; idif<8; idif++)
      {
	wgwmspill[ifile][idif].clear();
	wgwmsortspill[ifile][idif].clear();
	wgwmentryid[ifile][idif].clear();
      }
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

	spilltree[dif] = (TTree*)Fileinput[1][dif]->Get(treename);
	spilltree[dif]->SetBranchAddress("spill_number", &spillnumber[dif]);
	spilltree[dif]->SetBranchAddress("spill_mode", &spillmode[dif]);

	Nentry[dif] = wgtree[dif]->GetEntries();
	cout << "Nentry= "  << Nentry[dif] << '\n';
      }
  }

}


bool WGWMdata::SignalCreation(int eachentry[8], WGRecon* wgrecon)
{
  bool fillflag = false;
  for(int idif=0; idif<8; idif++)
    {
      wgtree[idif]->GetEntry(eachentry[idif]);
      thespill=spill_number[idif] & 0x7FFF;
      thespillmode=spill_mode[idif];

      if(idif<4)
	{
	  difid=idif;      
	  if(ModeCheck(thespillmode))
	    {
	      //cout << "dif= " << idif << " spill= " << thespill << '\n';
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
			    
			    if(HitCheck(thehit))
			      {
				thetime=time_wm[difid][ichip][ich][icol];		   
				wgrecon->mod.push_back(idif/2+3);
				wgrecon->view.push_back(idif);
				wgrecon->pln.push_back(thechip);
				wgrecon->channel.push_back(thechan);
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
	}//if idif<4

      if(idif>=4)
	{
	  difid=idif-4;      
	  if(ModeCheck(thespillmode))
	    {
	      //cout << "dif= " << idif << " spill= " << thespill << '\n';
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
			    
			    if(HitCheck(thehit))
			      {
				thetime=time_wg[difid][ichip][ich][icol];		   
				wgrecon->mod.push_back(idif/2-1);
				wgrecon->view.push_back(idif);
				wgrecon->pln.push_back(thechip);
				wgrecon->channel.push_back(thechan);
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
	}//if idif>=4

    }//idif
  return fillflag;
}

void WGWMdata::EntryCheck(int startentry[8], int entry_offset)
{
  for(int idif=0; idif<8; idif++)
    {
      for(int ientry=1+entry_offset; ientry<20+entry_offset; ientry++)
	{
	  spilltree[idif]->GetEntry(ientry);
	  thespillmode = spillmode[idif];
	  if(ModeCheck(thespillmode))
	    {
	      startentry[idif] = ientry;
	      break;
	    }
	}
      cout  << " idif= " << idif << " startentry= " << startentry[idif] << '\n';
    }

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
  if(bcid!=-1)
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

int WGWMdata::GetNofSpill(int dif, int *startspill, int *endspill)
{
  int numberofspill[8]={0, 0, 0, 0, 0, 0, 0, 0};
  int divide = 0;
  bool firstcheck = false;

  for(int idif=0; idif<8; idif++)
    {
      divide=0;
      cout << "Spill Counting for DIF " << idif << '\n';
      for(int ientry=0; ientry<spilltree[idif]->GetEntries(); ientry++)
      //for(int ientry=0; ientry<10000; ientry++)
	{
	  spilltree[idif]->GetEntry(ientry);
	  thespillmode=spillmode[idif];
	  thespill=spillnumber[idif] &0x7fff;
	  
	  if(ModeCheck(thespillmode))
	    {
	      numberofspill[idif]++;
	      if(numberofspill[idif]==30000) divide=1;
	      
	      wgwmspill[divide][idif].push_back(thespill);
	      wgwmsortspill[divide][idif].push_back(thespill);
	      wgwmentryid[divide][idif].push_back(ientry);
	      
	      if(idif==dif)
		{
		  if(!firstcheck)
		    {
		      *startspill = thespill;
		      firstcheck = true;
		    }
		  
		  *endspill = thespill;
		}
	    }
	}
    }


  return numberofspill[dif];
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
