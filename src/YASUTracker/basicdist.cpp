//Standard
#include <iostream>
#include <stdio.h>

//MyInc
#include "DataReader.cpp"
#include "EvtFormat.cpp"
#include "Calibration.cpp"
#include "Efficiency.cpp"

//MyLib
#include "BMBasicRecon.hpp"
#include "BMBeaminfo.hpp"
#include "BMCluster.hpp"

#include <TApplication.h>
#include <TCanvas.h>

using namespace std;

int main( int argc, char **argv )
{
  std::string name = string(argv[1]);
  TString bmfilepath(name);
  //TApplication app("app", 0, 0, 0, 0);
  TFile* ofile = new TFile("./result/YASU/basicdist.root","RECREATE");

  //Set Parameters
  TChain* bmchain = new TChain("tree","tree");

  //Set Classes
  BMBasicRecon* bmbasicrecon = new BMBasicRecon();
  BMBeaminfo* bmbeaminfo = new BMBeaminfo();
  EvtFormat* evtformat = new EvtFormat();
  Calibration* calibration = new Calibration();
  Efficiency* efficiency = new Efficiency();
  
  cout << "Start reading BM chain..." << '\n';
  bmchain->Add(Form("%s/*.root",bmfilepath.Data()));
  bmchain->SetBranchAddress("BMBasicRecon", &bmbasicrecon);
  bmchain->SetBranchAddress("BMBeaminfo", &bmbeaminfo);

  cout << "******* Information for Baby MIND *******" << '\n';
  cout << "total entry = " << bmchain->GetEntries() << '\n';
  
  for(int ientry=0; ientry<bmchain->GetEntries(); ientry++)
  //for(int ientry=0; ientry<100000; ientry++)
    {
      //cout << "ientry= " << ientry << '\n';
      bmchain->GetEntry(ientry);
      calibration->MakeDist(bmbasicrecon);
      efficiency->TimeClustering(bmbasicrecon);

      if(ientry%10000==0)
	cout << "Current Process= " << ientry << '\n';
    }

  efficiency->GetEfficiency();

  //Write Root File
  ofile->cd();
  for(int ipln=0; ipln<2; ipln++)
    for(int ich=0; ich<14; ich++)
      {
	calibration->hist_hg_yasu[ipln][ich]->Write();
	calibration->hist_tdif_yasu[ipln][ich]->Write();
      }
  for(int ihist=0; ihist<2; ihist++)
    {
      calibration->hist_hg[ihist]->Write();
      calibration->hist_tdif[ihist]->Write();
    }
  efficiency->yasumip->Write();
  efficiency->yasumip_pe->Write();

  ofile->Close();

  //app.Run();
  return 0;
  
}//main
