#include <iostream>
#include <fstream>
#include <vector>

#include "Dimension.cpp"

#include "PickSignal.hpp"
#include "DataReader.hpp"
#include "EvtFormat.hpp"

using namespace std;
//#define debug

EvtFormat::EvtFormat()
{
  bmchain = new TChain("tree", "tree");
  pmchain = new TChain("tree", "tree");
  for(int idif=0; idif<8; idif++)
    wgchain[idif] = new TChain("tree", "tree");
  mcchain = new TChain("tree", "tree");
}

EvtFormat::~EvtFormat()
{
}

Dimension *fdimension = new Dimension();

void EvtFormat::ReadBMChain(TString filepath, BMBasicRecon* bmbasicrecon, BMBeaminfo* bmbeaminfo, 
			    BMBSD* bmbsd, int *sunixtime, int *eunixtime)
{
  cout << "Start reading BM chain..." << '\n';
  AddBMChain(filepath);
  bmchain->SetBranchAddress("BMBasicRecon", &bmbasicrecon);
  bmchain->SetBranchAddress("BMBeaminfo", &bmbeaminfo);
  bmchain->SetBranchAddress("BMBSD", &bmbsd);  
  nbmdata = bmchain->GetEntries();  

  bmchain->GetEntry(0);
  *sunixtime=bmbsd->unixtime;
  bmchain->GetEntry(nbmdata-1);
  *eunixtime=bmbsd->unixtime;

  for(int ientry=0; ientry<nbmdata; ientry++)
    {
      bmchain->GetEntry(ientry);
      bmunix.push_back(bmbsd->unixtime);
    }

  cout << "******* Information for Baby MIND *******" << '\n';
  cout << "total entry = " << nbmdata << '\n';

}

void EvtFormat::ReadPMChain(TString filepath, PMRecon* pmrecon,  BMBSD* bmbsd, int *sunixtime, int *eunixtime)
{
  cout << "Start reading PM chain..." << '\n';
  AddPMChain(filepath);

  pmchain->SetBranchAddress("PMRecon", &pmrecon);
  pmchain->SetBranchAddress("BMBSD", &bmbsd);
  npmdata = pmchain->GetEntries();  

  pmchain->GetEntry(0);
  *sunixtime=bmbsd->unixtime;
  pmchain->GetEntry(npmdata-1);
  *eunixtime=bmbsd->unixtime;

  for(int ientry=0; ientry<npmdata; ientry++)
    {
      pmchain->GetEntry(ientry);
      pmunix.push_back(bmbsd->unixtime);
    }

  cout << "******* Information for Proton Module *******" << '\n';
  cout << "total entry = " << npmdata << '\n';
}

void EvtFormat::ReadWGChain(TString filepath, WGRecon* wgrecon[],  BMBSD* bmbsd[], int *sunixtime, int *eunixtime)
{
  cout << "Start reading WG chain..." << '\n';

  for(int idif=0; idif<8; idif++)
    {
      AddWGChain(filepath, idif);
      wgchain[idif]->SetBranchAddress("WGRecon", &wgrecon[idif]);
      wgchain[idif]->SetBranchAddress("BMBSD", &bmbsd[idif]);
      nwgdata[idif] = wgchain[idif]->GetEntries();  

      if(idif==4)
	{
	  wgchain[idif]->GetEntry(0);
	  *sunixtime=bmbsd[idif]->unixtime;
	  wgchain[idif]->GetEntry(nwgdata[idif]-1);
	  *eunixtime=bmbsd[idif]->unixtime;
	}

      for(int ientry=0; ientry<nwgdata[idif]; ientry++)
	{
	  wgchain[idif]->GetEntry(ientry);
	  wgunix[idif].push_back(bmbsd[idif]->unixtime);
	}

      cout << "******* Information for WAGASCI & WallMRDs *******" << '\n';
      cout << "total entry = " << nwgdata[idif] << '\n';
    }
  
}

void EvtFormat::ReadMCChain(TString filepath, MCTrue *mctrue, MCRecon* mcrecon, TTree* otree, EVTCluster* evtcluster)
{
  cout << "Start reading MC chain..." << '\n';
  AddMCChain(filepath);
  mcchain->SetBranchAddress("MCRecon", &mcrecon);
  mcchain->SetBranchAddress("MCTrue", &mctrue);
  nmcdata = mcchain->GetEntries();  

  cout << "******* Information for MCData *******" << '\n';
  cout << "total entry = " << nmcdata << '\n';

  for(int ientry=0; ientry<nmcdata; ientry++)
    {
      evtcluster->Clear();
      mcchain->GetEntry(ientry);

      (evtcluster->mod).insert(evtcluster->mod.end(), mcrecon->mod.begin(), mcrecon->mod.end());
      (evtcluster->view).insert(evtcluster->view.end(), mcrecon->view.begin(), mcrecon->view.end());
      (evtcluster->pln).insert(evtcluster->pln.end(), mcrecon->pln.begin(), mcrecon->pln.end());
      (evtcluster->channel).insert(evtcluster->channel.end(), mcrecon->channel.begin(), mcrecon->channel.end());
      //(evtcluster->posx).insert(evtcluster->posx.end(), mcrecon->posx.begin(), mcrecon->posx.end());
      //(evtcluster->posy).insert(evtcluster->posy.end(), mcrecon->posy.begin(), mcrecon->posy.end());
      //(evtcluster->posz).insert(evtcluster->posz.end(), mcrecon->posz.begin(), mcrecon->posz.end());
      //(evtcluster->dposx).insert(evtcluster->posx.end(), mcrecon->posx.begin(), mcrecon->posx.end());
      //(evtcluster->dposy).insert(evtcluster->posy.end(), mcrecon->posy.begin(), mcrecon->posy.end());
      //(evtcluster->dposz).insert(evtcluster->posz.end(), mcrecon->posz.begin(), mcrecon->posz.end());

	  for(int i=0; i<mcrecon->mod.size(); i++)
	    {
	      posx = mcrecon->posx.at(i);
	      posy = mcrecon->posy.at(i);
	      posz = mcrecon->posz.at(i);

	      dposx = mcrecon->dposx.at(i);
	      dposy = mcrecon->dposy.at(i);
	      dposz = mcrecon->dposz.at(i);

	      evtcluster->posx.push_back(posx);
	      evtcluster->posy.push_back(posy);
	      evtcluster->posz.push_back(posz);
	      evtcluster->dposx.push_back(dposx);
	      evtcluster->dposy.push_back(dposy);
	      evtcluster->dposz.push_back(dposz);
	    }

      for(int ihit=0; ihit<mcrecon->mod.size(); ihit++)
	{
	  evtcluster->bunch.push_back(1);
	}

      evtcluster->spillnum=-1;
      evtcluster->unixtime=-1;

      otree->Fill();
    }

}

void EvtFormat::AddBMChain(TString filepath)
{

  //bmchain->Add(Form("%s/BMBSD_BM_29_Jan*.root",filepath.Data()));
  //bmchain->Add(Form("%s/BMBSD_BM_30_Jan*.root",filepath.Data()));
  //bmchain->Add(Form("%s/BMBSD_BM_31_Jan*.root",filepath.Data()));

  
  bmchain->Add(Form("%s/BMBSD_BM_25_Jan*.root",filepath.Data()));
  bmchain->Add(Form("%s/BMBSD_BM_26_Jan*.root",filepath.Data()));
  bmchain->Add(Form("%s/BMBSD_BM_27_Jan*.root",filepath.Data()));
  bmchain->Add(Form("%s/BMBSD_BM_28_Jan*.root",filepath.Data()));
  bmchain->Add(Form("%s/BMBSD_BM_29_Jan*.root",filepath.Data()));
  bmchain->Add(Form("%s/BMBSD_BM_30_Jan*.root",filepath.Data()));
  bmchain->Add(Form("%s/BMBSD_BM_31_Jan*.root",filepath.Data()));
  bmchain->Add(Form("%s/BMBSD_BM_1_Feb*.root",filepath.Data()));
  bmchain->Add(Form("%s/BMBSD_BM_2_Feb*.root",filepath.Data()));
  bmchain->Add(Form("%s/BMBSD_BM_3_Feb*.root",filepath.Data()));
  bmchain->Add(Form("%s/BMBSD_BM_4_Feb*.root",filepath.Data()));
  bmchain->Add(Form("%s/BMBSD_BM_5_Feb*.root",filepath.Data()));
  bmchain->Add(Form("%s/BMBSD_BM_6_Feb*.root",filepath.Data()));
  bmchain->Add(Form("%s/BMBSD_BM_7_Feb*.root",filepath.Data()));
  bmchain->Add(Form("%s/BMBSD_BM_8_Feb*.root",filepath.Data()));
  bmchain->Add(Form("%s/BMBSD_BM_9_Feb*.root",filepath.Data()));
  bmchain->Add(Form("%s/BMBSD_BM_10_Feb*.root",filepath.Data()));
  
  
}

void EvtFormat::AddPMChain(TString filepath)
{
  //pmchain->Add(Form("%s/BMBSD_PM_32462_0_10.root",filepath.Data()));
  //pmchain->Add(Form("%s/BMBSD_PM_32462_10_20.root",filepath.Data()));
  //pmchain->Add(Form("%s/BMBSD_PM_32462_20_34.root",filepath.Data()));
  //pmchain->Add(Form("%s/BMBSD_PM_32462_34_50.root",filepath.Data()));
  //pmchain->Add(Form("%s/BMBSD_PM_32462_50_70.root",filepath.Data()));
  //pmchain->Add(Form("%s/BMBSD_PM_32462_70_90.root",filepath.Data()));
  
  pmchain->Add(Form("%s/BMBSD_PM_32453_60_80.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32453_80_100.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32453_100_123.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32461_0_20.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32461_20_40.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32461_40_48.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32462_0_10.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32462_10_20.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32462_20_34.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32462_34_50.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32462_50_70.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32462_70_90.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32462_90_110.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32462_110_128.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32463_0_20.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32463_20_40.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32463_40_60.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32463_60_77.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32468_0_20.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32468_20_40.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32468_40_60.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32468_60_81.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32469_0_20.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32469_20_34.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32470_0_20.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32470_20_32.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32470_32_50.root",filepath.Data()));
  pmchain->Add(Form("%s/BMBSD_PM_32470_50_84.root",filepath.Data()));

}

void EvtFormat::AddWGChain(TString filepath, int idif)
{
  //wgchain[idif]->Add(Form("%s/BMBSD_WG_92_dif%d.root",filepath.Data(), idif));
  //wgchain[idif]->Add(Form("%s/BMBSD_WG_93_dif%d.root",filepath.Data(), idif));
  
  wgchain[idif]->Add(Form("%s/BMBSD_WG_92_dif%d.root",filepath.Data(), idif));
  wgchain[idif]->Add(Form("%s/BMBSD_WG_93_dif%d.root",filepath.Data(), idif));
  wgchain[idif]->Add(Form("%s/BMBSD_WG_95_dif%d.root",filepath.Data(), idif));
  wgchain[idif]->Add(Form("%s/BMBSD_WG_96_dif%d.root",filepath.Data(), idif));
  wgchain[idif]->Add(Form("%s/BMBSD_WG_97_dif%d.root",filepath.Data(), idif));
  wgchain[idif]->Add(Form("%s/BMBSD_WG_98_dif%d.root",filepath.Data(), idif));
  wgchain[idif]->Add(Form("%s/BMBSD_WG_99_dif%d.root",filepath.Data(), idif));
  wgchain[idif]->Add(Form("%s/BMBSD_WG_100_dif%d.root",filepath.Data(), idif));
  wgchain[idif]->Add(Form("%s/BMBSD_WG_101_dif%d.root",filepath.Data(), idif));
  wgchain[idif]->Add(Form("%s/BMBSD_WG_102_dif%d.root",filepath.Data(), idif));
  wgchain[idif]->Add(Form("%s/BMBSD_WG_103_dif%d.root",filepath.Data(), idif));
  wgchain[idif]->Add(Form("%s/BMBSD_WG_104_dif%d.root",filepath.Data(), idif));
  wgchain[idif]->Add(Form("%s/BMBSD_WG_105_dif%d.root",filepath.Data(), idif));
  wgchain[idif]->Add(Form("%s/BMBSD_WG_106_dif%d.root",filepath.Data(), idif));
  
}

void EvtFormat::AddMCChain(TString filepath)
{
  /*
  for(int i=2; i<20; i++)
    {
      mcchain->Add(Form("%s/MCCalib_%d.root",filepath.Data(), i));
    }
  */

  /*
  for(int i=1; i<20; i++)
    {
      mcchain->Add(Form("%s/MCCalib_anti_%d.root",filepath.Data(), i));
    }
  */

  for(int i=1; i<10; i++)
    {
      mcchain->Add(Form("%s/MCCalib_vertex3_%d.root",filepath.Data(), i));
    }

  
}

bool EvtFormat::FillEvtClass(TTree *otree, int sunixtimeentry, int eunixtimeentry, vector<int> baseunixtime, vector<double> basepot, 
			     BMBasicRecon* bmbasicrecon, BMBeaminfo* bmbeaminfo, PMRecon* pmrecon,
			     WGRecon* wgrecon[8], EVTCluster* evtcluster, TString filepath)
{
  evtcluster->Clear();
  Nentry = eunixtimeentry - sunixtimeentry;

  bmchain->Reset();
  AddBMChain(filepath);
  bmchain->SetBranchAddress("BMBasicRecon", &bmbasicrecon);
  bmchain->SetBranchAddress("BMBeaminfo", &bmbeaminfo);
  
  pmchain->Reset();
  AddPMChain(filepath);
  pmchain->SetBranchAddress("PMRecon", &pmrecon);

  for(int idif=0; idif<8; idif++)
    {
      wgchain[idif]->Reset();
      AddWGChain(filepath, idif);
      wgchain[idif]->SetBranchAddress("WGRecon", &wgrecon[idif]);
    }

  //for(int ientry=0; ientry<20; ientry++)
  //for(int ientry=0; ientry<pmchain->GetEntries(); ientry++)
  for(int ientry=0; ientry<=Nentry; ientry++)
    {

      evtcluster->Clear();
      bmbasicrecon->Clear();
      pmrecon->Clear();
      bmfillflag=false;
      pmfillflag=false;


      for(int idif=0; idif<8; idif++)
	{
	  wgfillflag[idif]=false;
	  wgrecon[idif]->Clear();
	}

      theunixtimeentry = sunixtimeentry + ientry;
      theunixtime = baseunixtime.at(theunixtimeentry);
      thepot = basepot.at(theunixtimeentry);
      totalpot += thepot;


      //BabyMIND check                                                                                                 
      auto bmunixit = find(bmunix.begin(), bmunix.end(), theunixtime);
      //cout << "bm theunixit= " << *bmunixit << '\n';
      if(*bmunixit==theunixtime)
        {
          bmentry=bmunixit-bmunix.begin();
          bmfillflag=true;
        }
      //Proton Module check                                                                                            
      auto pmunixit = find(pmunix.begin(), pmunix.end(), theunixtime);
      //cout << "pm theunixit= " << *pmunixit << '\n';
      if(*pmunixit==theunixtime)
        {
          pmentry=pmunixit-pmunix.begin();
          pmfillflag=true;
        }

      //WAGASCI WallMRD check                                                                                          
      for(int idif=0; idif<8; idif++)
        {
          auto wgunixit = find(wgunix[idif].begin(), wgunix[idif].end(), theunixtime);
          //cout << "wgdif" << idif << " theunixit= " << *wgunixit << '\n';
          if(*wgunixit==theunixtime)
            {
              wgentry[idif]=wgunixit-wgunix[idif].begin();
              wgfillflag[idif]=true;
            }
        }

      
      bool fillflag = false;
      
      if(bmfillflag)
	{	  
	  bmchain->GetEntry(bmentry);
	  spillnum = bmbeaminfo->spillnum;
	  //cout << "mod= " << bmbasicrecon->mod.size() << " LHG= " << bmbasicrecon->LHG.size() << '\n';
	  //cout << "mod= " << bmbasicrecon->mod.size() << " RHG= " << bmbasicrecon->RHG.size() << '\n';
	  //cout << "mod= " << bmbasicrecon->mod.size() << " THG= " << bmbasicrecon->THG.size() << '\n';
	  for(int i=0; i<bmbasicrecon->LHG.size(); i++)
	    {
	      posx=-1;
	      posy=-1;
	      posz=-1;
	      mod = bmbasicrecon->mod.at(i);
	      view = bmbasicrecon->view.at(i);
	      pln = bmbasicrecon->pln.at(i);
	      channel = bmbasicrecon->channel.at(i);
	      
	      LHG = bmbasicrecon->LHG.at(i);
	      RHG = bmbasicrecon->RHG.at(i);
	      THG = bmbasicrecon->THG.at(i);
	      lgain = bmbasicrecon->Lgain.at(i);
	      rgain = bmbasicrecon->Rgain.at(i);
	      tgain = bmbasicrecon->Tgain.at(i);
	      
	      pel = (LHG-50.)/lgain;
	      per = (RHG-50.)/rgain;
	      pet = (THG-50.)/tgain;
	      
	      fdimension->get_pos_bm_FC(mod, view, pln, channel, &dposx, &dposy, &dposz);
	      if(view==0)
		{
		  //posz = dposz+fdimension->offset[(int)view][0][(int)mod];
		  //posy = dposy+fdimension->offset[(int)view][1][(int)mod];
		  posz = dposz;
		  posy = dposy;
		  //cout << "pln= " << pln << " posz= " << posz << '\n';		  
		  
		  if(LHG!=-1)
		    evtcluster->pel.push_back(pel);
		  if(LHG==-1)
		    evtcluster->pel.push_back(-1);
		  if(RHG!=-1)
		    evtcluster->per.push_back(per);
		  if(RHG==-1)
		    evtcluster->per.push_back(-1);
		  if(THG!=-1)
		    evtcluster->pet.push_back(pet);
		  if(THG==-1)
		    evtcluster->pet.push_back(-1);
		}

	      if(view==1)
		{
		  //posz = dposz+fdimension->offset[(int)view][0][(int)mod];
		  //posx = dposx+fdimension->offset[(int)view][1][(int)mod];
		  posz = dposz;
		  posx = dposx;

		  if(LHG!=-1)
		    evtcluster->pel.push_back(pel);
		  if(LHG==-1)
		    evtcluster->pel.push_back(-1);
		  if(RHG!=-1)
		    evtcluster->per.push_back(per);
		  if(RHG==-1)
		    evtcluster->per.push_back(-1);
		  if(THG!=-1)
		    evtcluster->pet.push_back(pet);
		  if(THG==-1)
		    evtcluster->pet.push_back(-1);

		}

	      evtcluster->posx.push_back(posx);
	      evtcluster->posy.push_back(posy);
	      evtcluster->posz.push_back(posz);
	      evtcluster->dposx.push_back(dposx);
	      evtcluster->dposy.push_back(dposy);
	      evtcluster->dposz.push_back(dposz);
	    }
	  
	  (evtcluster->mod).insert(evtcluster->mod.end(), 
				   bmbasicrecon->mod.begin(), bmbasicrecon->mod.end());                 
	  (evtcluster->view).insert(evtcluster->view.end(), 
				    bmbasicrecon->view.begin(), bmbasicrecon->view.end());             
	  (evtcluster->pln).insert(evtcluster->pln.end(), 
				   bmbasicrecon->pln.begin(), bmbasicrecon->pln.end());                 
	  (evtcluster->channel).insert(evtcluster->channel.end(), 
				       bmbasicrecon->channel.begin(),bmbasicrecon->channel.end());
	  (evtcluster->charge).insert(evtcluster->charge.end(), 
				       bmbasicrecon->HG.begin(),bmbasicrecon->HG.end());
	  (evtcluster->Htime).insert(evtcluster->Htime.end(), 
				     bmbasicrecon->Htime.begin(), bmbasicrecon->Htime.end());         
	  (evtcluster->bunch).insert(evtcluster->bunch.end(), 
				     bmbasicrecon->bunch.begin(), bmbasicrecon->bunch.end());
	}
      
      if(pmfillflag)
	{
	  pmchain->GetEntry(pmentry);
	  for(int i=0; i<pmrecon->mod->size(); i++)
	    {
	      posx=-1;
	      posy=-1;
	      posz=-1;

	      mod = pmrecon->mod->at(i);
	      view = pmrecon->view->at(i);
	      pln = pmrecon->pln->at(i);
	      channel = pmrecon->channel->at(i);
	      
	      fdimension->get_pos_pm_FC(mod, view, pln, channel, &dposx, &dposy, &dposz);
	      if(view==0)
		{
		  posz = dposz+fdimension->offset[(int)view][0][(int)mod];
		  posy = dposy+fdimension->offset[(int)view][1][(int)mod];
		}

	      if(view==1)
		{
		  posz = dposz+fdimension->offset[(int)view][0][(int)mod];
		  posx = dposx+fdimension->offset[(int)view][1][(int)mod];
		}

	      evtcluster->posx.push_back(posx);
	      evtcluster->posy.push_back(posy);
	      evtcluster->posz.push_back(posz);
	      evtcluster->dposx.push_back(dposx);
	      evtcluster->dposy.push_back(dposy);
	      evtcluster->dposz.push_back(dposz);

	      evtcluster->pel.push_back(-1);
	      evtcluster->per.push_back(-1);
	      evtcluster->pet.push_back(-1);
	    }

	  (evtcluster->mod).insert(evtcluster->mod.end(), pmrecon->mod->begin(), pmrecon->mod->end());         
	  (evtcluster->view).insert(evtcluster->view.end(), pmrecon->view->begin(), pmrecon->view->end());             
	  (evtcluster->pln).insert(evtcluster->pln.end(), pmrecon->pln->begin(), pmrecon->pln->end());                 
	  (evtcluster->channel).insert(evtcluster->channel.end(), pmrecon->channel->begin(),              
				       pmrecon->channel->end());
	  (evtcluster->charge).insert(evtcluster->charge.end(), pmrecon->time->begin(),              
				      pmrecon->time->end());                                  
	  //(evtcluster->charge).insert(evtcluster->charge.end(), pmrecon->charge->begin(),              
	  //			      pmrecon->charge->end());                                  
	  (evtcluster->Htime).insert(evtcluster->Htime.end(), pmrecon->time->begin(), pmrecon->time->end());         
	  (evtcluster->bunch).insert(evtcluster->bunch.end(), pmrecon->bunch->begin(), pmrecon->bunch->end());
	}
      
      for(int idif=0; idif<8; idif++)
	{
	  if(wgfillflag[idif])
	    {
	      wgchain[idif]->GetEntry(wgentry[idif]);	      
	      spillnum = wgrecon[idif]->spill;

	      for(int i=0; i<wgrecon[idif]->mod.size(); i++)
		{
		  posx=-1;
		  posy=-1;
		  posz=-1;
		  
		  mod = wgrecon[idif]->mod.at(i);
		  view = wgrecon[idif]->view.at(i);
		  pln = wgrecon[idif]->pln.at(i);
		  channel = wgrecon[idif]->channel.at(i);
		  
		  fdimension->get_pos_wg_FC(view, pln, channel, &dposx, &dposy, &dposz);
		  if(view%2==1 && (mod==1||mod==2))
		    {
		      posz = dposz+fdimension->offset[0][0][mod];
		      posy = dposy+fdimension->offset[0][1][mod];
		    }
		  
		  if(view%2==0 && (mod==1||mod==2))
		    {
		      posz = dposz+fdimension->offset[1][0][mod];
		      posx = dposx+fdimension->offset[1][1][mod];
		    }

		  if(mod==3||mod==4)
		    {
		      posz = dposz+fdimension->offset[1][0][mod];
		      posx = dposx+fdimension->offset[1][1][mod];
		    }

		  evtcluster->posx.push_back(posx);
		  evtcluster->posy.push_back(posy);
		  evtcluster->posz.push_back(posz);
		  evtcluster->dposx.push_back(dposx);
		  evtcluster->dposy.push_back(dposy);
		  evtcluster->dposz.push_back(dposz);

		  evtcluster->pel.push_back(-1);
		  evtcluster->per.push_back(-1);
		  evtcluster->pet.push_back(-1);
		}

	      (evtcluster->mod).insert(evtcluster->mod.end(), wgrecon[idif]->mod.begin(), wgrecon[idif]->mod.end());         
	      (evtcluster->view).insert(evtcluster->view.end(), wgrecon[idif]->view.begin(), wgrecon[idif]->view.end()); 
	      (evtcluster->pln).insert(evtcluster->pln.end(), wgrecon[idif]->pln.begin(), wgrecon[idif]->pln.end());
	      (evtcluster->channel).insert(evtcluster->channel.end(), 
				       wgrecon[idif]->channel.begin(), wgrecon[idif]->channel.end()); 
	      (evtcluster->charge).insert(evtcluster->charge.end(), 
				       wgrecon[idif]->charge.begin(), wgrecon[idif]->charge.end()); 
	      (evtcluster->Htime).insert(evtcluster->Htime.end(), wgrecon[idif]->time.begin(), wgrecon[idif]->time.end());
	      (evtcluster->bunch).insert(evtcluster->bunch.end(), wgrecon[idif]->bunch.begin(), wgrecon[idif]->bunch.end());
	    }
	}
      
      if(bmfillflag || pmfillflag)
	fillflag = true;
      
      for(int idif=0; idif<8; idif++)
	if(wgfillflag[idif]) fillflag = true;
      
      if(fillflag)
	{
	  evtcluster->spillnum=spillnum;
	  evtcluster->unixtime=theunixtime;
	  evtcluster->pot=thepot;
	  evtcluster->totalpot = totalpot;
	  otree->Fill();
	}

      if(ientry%500==0)
	cout << "analyzed events: " << ientry << '\n';
    }//ientry
}

void EvtFormat::PrintTime(time_t unixtime)
{
  struct tm *ptm;
  char buf[128];
  ptm = localtime(&unixtime);
  strftime(buf, sizeof(buf), "%Y/%m/%d %H:%M:%S ", ptm);
  cout << buf;
}

void EvtFormat::DeleteChain()
{
  bmchain->Delete();
  pmchain->Delete();

  for(int idif=0; idif<8; idif++)
    wgchain[idif]->Delete();
  
}

