#include <iostream>
#include <stdio.h>

//include
#include "DataReader.cpp"
#include "BMData.cpp"
#include "EvtFormat.cpp"

//library
#include "BMBasicRecon.hpp"
#include "BMBeaminfo.hpp"
#include "BMDisp.hpp"
#include "PMRecon.hpp"
#include "WGRecon.hpp"


using namespace std;

int main( int argc, char **argv )
{
  if(argc < 5)
    {
      cout << "usage" << '\n';
      cout << "MakeEvt [filepath][date][month][run]" << '\n';
      exit(0);
    }

  std::string name = string(argv[1]);
  std::string date = string(argv[2]);
  std::string month = string(argv[3]);
  std::string run = string(argv[4]);
  int subrun = std::atoi(argv[5]);
  int pmrun = std::atoi(argv[6]);
  int pmssub = std::atoi(argv[7]);
  int pmesub = std::atoi(argv[8]);
  TString bmfilepath(name);
  TString pmfilepath;
  TString wgwmfilepath;
  pmfilepath.Form("./process/2-PMClass/PMClass_%d_%d_%d.root"
		  ,pmrun, pmssub, pmesub);
  wgwmfilepath.Form("./process/9-WGWMClass/WGWMClass.root");

  BMBasicRecon *bmbasicrecon = new BMBasicRecon();
  BMBeaminfo *bmbeaminfo = new BMBeaminfo();
  BMDisp *bmdisp = new BMDisp();
  PMRecon *pmrecon = new PMRecon();
  WGRecon *wgwmrecon = new WGRecon();
  EvtFormat *evtformat = new EvtFormat();

  vector<int> commonspill_pm_bm;
  vector<int> commonspill_pm_bm_wgwm;
  
  TFile *fout = new TFile(Form("./process/4-BMEVT/BMEvt_%s%s_%s-%d.root"
			       ,date.c_str(),month.c_str(),run.c_str(), subrun),"recreate");
  TTree *otree = new TTree("tree","tree");
  otree->Branch("BMDisp","BMDisp",&bmdisp,32000,2);

  evtformat->ReadBMTree(bmfilepath, bmbasicrecon, bmbeaminfo);
  evtformat->ReadPMTree(pmfilepath, pmrecon);
  evtformat->ReadWGWMTree(wgwmfilepath, wgwmrecon);
  evtformat->SpillMatch(&commonspill_pm_bm, evtformat->bmspill_match, evtformat->pmspill_match);
  evtformat->SpillMatch(&commonspill_pm_bm_wgwm, commonspill_pm_bm, evtformat->wgwmspill_match);

  cout << "first spill= " << commonspill_pm_bm.at(0) << " : end spill= " 
       << commonspill_pm_bm.at(commonspill_pm_bm.size()-1) << '\n';

  cout << "first spill= " << commonspill_pm_bm_wgwm.at(0) << " : end spill= " 
       << commonspill_pm_bm_wgwm.at(commonspill_pm_bm_wgwm.size()-1) << '\n';
  for(int ientry=0; ientry<commonspill_pm_bm_wgwm.size(); ientry++)
    { 
      evtformat->FillEvtClass(ientry, commonspill_pm_bm_wgwm, bmbasicrecon, bmbeaminfo, bmdisp, pmrecon,
			      wgwmrecon);
      bmdisp->entry = ientry;
      otree->Fill();
    }

  fout->cd();
  otree->Write();
  fout->Close();
  evtformat->FileClose();
  
}
