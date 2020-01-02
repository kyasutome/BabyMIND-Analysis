#include <iostream>
#include <stdio.h>

//include
#include "WGChannelMap.cpp"
#include "WGData.cpp"
#include "WMData.cpp"

//library
#include "WGRecon.hpp"

using namespace std;

int main( int argc, char **argv )
{
  
  
  if(argc < 2)
    {
      cout << "usage" << '\n';
      cout << "MakeWGClass [filepath]" << '\n';
      exit(0);
    }

  std::string name = string(argv[1]);
  TString filepath(name);

  WGRecon *wgrecon = new WGRecon();
  //WGChannelMap *wgchannelmap = new WGChannelMap();
  WGdata *wgdata = new WGdata();
  //WMdata *wmdata = new WMdata();
  
  TFile *fout = new TFile(Form("./process/5-WGClass/WGClass.root"), "recreate");
  TTree *otree = new TTree("tree","tree");
  otree->Branch("WGRecon","WGRecon",&wgrecon,32000,2);

  //TEST CODES
  wgdata->ReadTree(filepath, 4);
  for(int ientry=0; ientry<wgdata->GetTEntry(4); ientry++)
    {
      wgrecon->Clear();
      if(wgdata->SignalCreation(ientry, 4, wgrecon))
	otree->Fill();
    }

  fout->cd();
  otree->Write();
  for(int ihist=0; ihist<4; ihist++)
    wgdata->bcid_hist[ihist]->Write();
  fout->Close();


  return 0;
}
