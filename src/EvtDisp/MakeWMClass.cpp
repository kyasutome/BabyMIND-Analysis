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
      cout << "MakeWMClass [filepath]" << '\n';
      exit(0);
    }

  std::string name = string(argv[1]);
  TString filepath(name);

  WGRecon *wmrecon = new WMRecon();
  //WGChannelMap *wgchannelmap = new WGChannelMap();
  WGdata *wmdata = new WMdata();
  //WMdata *wmdata = new WMdata();
  
  TFile *fout = new TFile(Form("./process/7-WMClass/WMClass.root"), "recreate");
  TTree *otree = new TTree("tree","tree");
  otree->Branch("WMRecon","WMRecon",&wmrecon,32000,2);

  //TEST CODES
  wmdata->ReadTree(filepath, 4);
  for(int ientry=0; ientry<wmdata->GetTEntry(4); ientry++)
    {
      wmrecon->Clear();
      if(wmdata->SignalCreation(ientry, 4, wmrecon))
	otree->Fill();
    }

  fout->cd();
  otree->Write();
  for(int ihist=0; ihist<4; ihist++)
    wmdata->bcid_hist[ihist]->Write();
  fout->Close();


  return 0;
}
