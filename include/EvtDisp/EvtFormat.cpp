#include <iostream>
#include <fstream>
#include <vector>

#include "PickSignal.hpp"
#include "DataReader.hpp"
#include "EvtFormat.hpp"

using namespace std;
//#define debug

EvtFormat::EvtFormat()
{
  pmspill.clear();
  bmspill.clear();
}

EvtFormat::~EvtFormat()
{
}

void EvtFormat::FillEvtClass(int ientry, vector<int> commonspill,
			     BMBasicRecon* bmbasicrecon, BMBeaminfo* bmbeaminfo, BMDisp* bmdisp, PMRecon* pmrecon,
			     WGRecon* wgwmrecon)
{

  //for Baby MIND

  bmtree = (TTree*)bmfile->Get("tree");
  bmtree->SetBranchAddress("BMBasicRecon", &bmbasicrecon);
  bmtree->SetBranchAddress("BMBeaminfo", &bmbeaminfo);
  thebmspill = commonspill.at(ientry);
  auto thespillit = find(bmspill.begin(), bmspill.end(), thebmspill); 
  thebmspill = thespillit - bmspill.begin();
  bmtree->GetEntry(thebmspill);
   
  //for Proton Module

  pmtree = (TTree*)pmfile->Get("tree");
  pmtree->SetBranchAddress("PMRecon", &pmrecon);    
  thepmspill = commonspill.at(ientry);
  thespillit = std::find(pmspill.begin(), pmspill.end(), thepmspill); 
  thepmspill = thespillit - pmspill.begin();
  pmtree->GetEntry(thepmspill);

  //for WAGASCI & WallMRDs

  wgwmtree = (TTree*)wgwmfile->Get("tree");
  wgwmtree->SetBranchAddress("WGRecon", &wgwmrecon);    
  thewgwmspill = commonspill.at(ientry);
  thespillit = std::find(wgwmspill.begin(), wgwmspill.end(), thewgwmspill); 
  thewgwmspill = thespillit - wgwmspill.begin();
  wgwmtree->GetEntry(thewgwmspill);

  (bmbasicrecon->mod).insert(bmbasicrecon->mod.end(), pmrecon->mod->begin(), pmrecon->mod->end());
  (bmbasicrecon->view).insert(bmbasicrecon->view.end(), pmrecon->view->begin(), pmrecon->view->end());
  (bmbasicrecon->pln).insert(bmbasicrecon->pln.end(), pmrecon->pln->begin(), pmrecon->pln->end());
  (bmbasicrecon->channel).insert(bmbasicrecon->channel.end(), pmrecon->channel->begin(), pmrecon->channel->end());
  (bmbasicrecon->Htime).insert(bmbasicrecon->Htime.end(), pmrecon->time->begin(), pmrecon->time->end());
  (bmbasicrecon->bunch).insert(bmbasicrecon->bunch.end(), pmrecon->bunch->begin(), pmrecon->bunch->end());

  (bmbasicrecon->mod).insert(bmbasicrecon->mod.end(), wgwmrecon->mod.begin(), wgwmrecon->mod.end());
  (bmbasicrecon->view).insert(bmbasicrecon->view.end(), wgwmrecon->view.begin(), wgwmrecon->view.end());
  (bmbasicrecon->pln).insert(bmbasicrecon->pln.end(), wgwmrecon->pln.begin(), wgwmrecon->pln.end());
  (bmbasicrecon->channel).insert(bmbasicrecon->channel.end(), wgwmrecon->channel.begin(), wgwmrecon->channel.end());
  (bmbasicrecon->Htime).insert(bmbasicrecon->Htime.end(), wgwmrecon->time.begin(), wgwmrecon->time.end());
  (bmbasicrecon->bunch).insert(bmbasicrecon->bunch.end(), wgwmrecon->bunch.begin(), wgwmrecon->bunch.end());

  bmdisp->mod = bmbasicrecon->mod;
  bmdisp->view = bmbasicrecon->view;
  bmdisp->pln = bmbasicrecon->pln;
  bmdisp->channel = bmbasicrecon->channel;
  bmdisp->Htime = bmbasicrecon->Htime;
  bmdisp->bunch = bmbasicrecon->bunch;
  bmdisp->bm_event = bmbasicrecon->bm_event;
  bmdisp->spillnum = bmbeaminfo->spillnum;
  bmdisp->unixtime = pmrecon->unixtime;

}

void EvtFormat::ReadBMChain(TString filepath, BMBasicRecon* bmbasicrecon, BMBeaminfo* bmbeaminfo, TChain* bmchain)
{
  cout << "Start reading BM chain..." << '\n';
  bmchain->Add(Form("%s/*.root",filepath.Data()));
  bmchain->SetBranchAddress("BMBasicRecon", &bmbasicrecon);
  bmchain->SetBranchAddress("BMBeaminfo", &bmbeaminfo);

  nbmdata = bmchain->GetEntries();  
  cout << "******* Information for Baby MIND *******" << '\n';
  cout << "total entry = " << nbmdata << '\n';
}

void EvtFormat::ReadBMTree(TString filepath, BMBasicRecon* bmbasicrecon, BMBeaminfo* bmbeaminfo)
{
  cout << "Start reading BM tree..." << '\n';
  bmfile = new TFile(filepath, "read");
  bmtree = (TTree*)bmfile->Get("tree");
  bmtree->SetBranchAddress("BMBasicRecon", &bmbasicrecon);
  bmtree->SetBranchAddress("BMBeaminfo", &bmbeaminfo);

  nbmdata = bmtree->GetEntries();  
  for(int ientry=0; ientry<nbmdata; ientry++)
    {
      bmtree->GetEntry(ientry);
      bmspill.push_back(bmbeaminfo->spillnum);
      bmspill_match.push_back(bmbeaminfo->spillnum);
    }

  sort(bmspill_match.begin(), bmspill_match.end());
  
  cout << "******* Information for Baby MIND *******" << '\n';
  cout << "total entry = " << nbmdata << '\n';
  cout << "Spill from = " << bmspill.at(0)  << " to " << bmspill.at(nbmdata-1) << '\n';
  cout << "Spill (sort) from = " << bmspill_match.at(0)  << " to " << bmspill_match.at(nbmdata-1) << '\n';
}

void EvtFormat::ReadWGWMTree(TString filepath, WGRecon* wgwmrecon)
{
  cout << "Start reading BM tree..." << '\n';
  wgwmfile = new TFile(filepath, "read");
  wgwmtree = (TTree*)wgwmfile->Get("tree");
  wgwmtree->SetBranchAddress("WGRecon", &wgwmrecon);

  nwgwmdata = wgwmtree->GetEntries();  
  for(int ientry=0; ientry<nwgwmdata; ientry++)
    {
      wgwmtree->GetEntry(ientry);
      wgwmspill.push_back(wgwmrecon->spill);
      wgwmspill_match.push_back(wgwmrecon->spill);
    }

  sort(wgwmspill_match.begin(), wgwmspill_match.end());
  
  cout << "******* Information for WAGASCI & WallMRD *******" << '\n';
  cout << "total entry = " << nwgwmdata << '\n';
  cout << "Spill from = " << wgwmspill.at(0)  << " to " << wgwmspill.at(nwgwmdata-1) << '\n';
  cout << "Spill (sort) from = " << wgwmspill_match.at(0)  << " to " << wgwmspill_match.at(nwgwmdata-1) << '\n';
}

void EvtFormat::ReadPMTree(TString filepath, PMRecon *pmrecon)
{
  cout << "Start reading PM tree..." << '\n';
  pmfile = new TFile(filepath, "read");
  pmtree = (TTree*)pmfile->Get("tree");
  pmtree->SetBranchAddress("PMRecon", &pmrecon);

  npmdata = pmtree->GetEntries();
  for(int ientry=0; ientry<npmdata; ientry++)
    {
      pmtree->GetEntry(ientry);
      pmspill.push_back(pmrecon->spill);
      pmspill_match.push_back(pmrecon->spill);
    }

  sort(pmspill_match.begin(), pmspill_match.end());

  pmtree->GetEntry(0);
  pmfirsttime = pmrecon->unixtime;
  pmtree->GetEntry(npmdata-1);
  pmlasttime = pmrecon->unixtime;
  
  cout << "******* Information for Proton Module *******" << '\n';
  cout << "total entry = " << npmdata << '\n';
  cout << "Spill from = " << pmspill.at(0)  << " to " << pmspill.at(npmdata-1) << '\n';
  cout << "Spill (sort) from = " << pmspill_match.at(0)  << " to " << pmspill_match.at(npmdata-1) << '\n';
  cout << "Time from ";
  PrintTime(pmfirsttime);
  cout << "to ";
  PrintTime(pmlasttime);
  cout << '\n';  
}

void EvtFormat::PrintTime(time_t unixtime)
{
  struct tm *ptm;
  char buf[128];
  ptm = localtime(&unixtime);
  strftime(buf, sizeof(buf), "%Y/%m/%d %H:%M:%S ", ptm);
  cout << buf;
}

void EvtFormat::SpillMatch(vector<int>* commonspill, vector<int> vec1, vector<int> vec2)
{
  set_intersection(vec1.begin(), vec1.end(),
		   vec2.begin(), vec2.end(),
		   inserter(*commonspill, commonspill->end()));
  
  cout << "Commonspill Size= "  << commonspill->size() << '\n';  
}

void EvtFormat::FileClose()
{
  bmtree->Delete();
  bmfile->Close();
  pmtree->Delete();
  pmfile->Close();
}
