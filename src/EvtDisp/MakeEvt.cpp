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


using namespace std;

int main( int argc, char **argv )
{
  if(argc < 5)
    {
      cout << "usage" << '\n';
      cout << "MakeCalib [filepath][date][month][run]" << '\n';
      exit(0);
    }

  std::string name = string(argv[1]);
  std::string date = string(argv[2]);
  std::string month = string(argv[3]);
  std::string run = string(argv[4]);
  int pmrun = std::atoi(argv[5]);
  int pmssub = std::atoi(argv[6]);
  int pmesub = std::atoi(argv[7]);
  TString bmfilepath(name);
  TString pmfilepath;
  pmfilepath.Form("./process/PMClass_%d_%d_%d.root"
		  ,pmrun, pmssub, pmesub);

  BMBasicRecon *bmbasicrecon = new BMBasicRecon();
  BMBeaminfo *bmbeaminfo = new BMBeaminfo();
  BMDisp *bmdisp = new BMDisp();
  PMRecon *pmrecon = new PMRecon();
  EvtFormat *evtformat = new EvtFormat();

  vector<int> commonspill;
  
  TFile *fout = new TFile(Form("./process/4-BMEVT/BMEvt_%s%s_%s.root"
			       ,date.c_str(),month.c_str(),run.c_str()),"recreate");
  TTree *otree = new TTree("tree","tree");
  otree->Branch("BMDisp","BMDisp",&bmdisp,32000,2);

  evtformat->ReadBMTree(bmfilepath, bmbasicrecon, bmbeaminfo);
  evtformat->ReadPMTree(pmfilepath, pmrecon);
  evtformat->SpillMatch(&commonspill, evtformat->bmspill, evtformat->pmspill);

  for(int ientry=0; ientry<commonspill.size(); ientry++)
    { 
      evtformat->FillEvtClass(ientry, commonspill, bmbasicrecon, bmbeaminfo, bmdisp, pmrecon);
      bmdisp->entry = ientry;
      otree->Fill();
    }

  fout->cd();
  otree->Write();
  fout->Close();
  evtformat->FileClose();
  
}
