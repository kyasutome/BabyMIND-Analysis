#include <iostream>
#include <stdio.h>

//include
//#include "WGChannelMap.cpp"
#include "WGData.cpp"
//#include "WMData.cpp"

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
  TString filedir(name);
  TString filepath;

  WGRecon *wgrecon = new WGRecon();
  //WGChannelMap *wgchannelmap = new WGChannelMap();
  WGdata *wgdata = new WGdata();
  //WMdata *wmdata = new WMdata();
  
  TFile *fout[4];
  TTree *otree[4];

  for(int idif=0; idif<4; idif++)
    {
      int DIF=idif+4;
      filepath.Form("%s/physics_run_2020-01-29_18-30-08_92_ecal_dif_%d_tree.root", filedir.Data(), DIF);
      fout[idif] = new TFile(Form("./process/5-WGClass/WGClass_dif%d.root",DIF), "recreate");
      otree[idif] = new TTree("tree","tree");
      otree[idif]->Branch("WGRecon","WGRecon",&wgrecon,32000,2);
      wgdata->ReadTree(filepath, DIF);
      for(int ientry=0; ientry<wgdata->GetTEntry(DIF); ientry++)
      //for(int ientry=0; ientry<100; ientry++)
	{
	  wgrecon->Clear(); 
	  if(wgdata->SignalCreation(ientry, DIF, wgrecon))
	    otree[idif]->Fill();

	  if(ientry%10000==0)
	    cout << "ientry= " << ientry << '\n'; 
	}
      fout[idif]->cd();
      otree[idif]->Write();
      fout[idif]->Close();
    }
 

  return 0;
}
