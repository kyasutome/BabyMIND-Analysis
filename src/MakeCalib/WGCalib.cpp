#include <iostream>
#include <stdio.h>

//include
#include "WGWMData.cpp"

//library
#include "WGRecon.hpp"

using namespace std;

int main( int argc, char **argv )
{
  
  
  if(argc < 3)
    {
      cout << "usage" << '\n';
      cout << "WGCalib [filepath][runnumber]" << '\n';
      exit(0);
    }

  std::string name = string(argv[1]);
  int runnumber = std::atoi(argv[2]);
  TString filedir(name);
  TString filepath;

  WGRecon *wgrecon = new WGRecon();
  WGRecon *wgrecon_nocut = new WGRecon();
  WGWMdata *wgwmdata = new WGWMdata();
  
  TFile *fout[8];
  TTree *otree[8];
  TFile *fout_nocut[8];
  TTree *otree_nocut[8];

  for(int idif=0; idif<1; idif++)
    {
      fout[idif] = new TFile(Form("./process/1-WGCalib/WGCalib_%d_dif%d.root", runnumber, idif), "RECREATE");
      otree[idif] = new TTree("tree", "tree");
      otree[idif]->Branch("WGRecon","WGRecon",&wgrecon,32000,2);

      fout_nocut[idif] = new TFile(Form("./process/0-WGnocut/WGCalib_%d_dif%d.root", runnumber, idif), "RECREATE");
      otree_nocut[idif] = new TTree("tree", "tree");
      otree_nocut[idif]->Branch("WGRecon","WGRecon",&wgrecon_nocut,32000,2);

      int DIF=idif;

      //wgwmdata->ReadTree(filedir, DIF);
      filepath.Form("%s/physics_run_2020-02-10_16-10-46_%d_ecal_dif_%d_tree.root", filedir.Data(), runnumber, DIF);
      wgwmdata->ReadTree(filepath, DIF);

      for(int ientry=0; ientry<wgwmdata->wgtree[idif]->GetEntries(); ientry++)
      //for(int ientry=0; ientry<5000; ientry++)
	{
	  if(wgwmdata->SignalCreation(idif, ientry, wgrecon))
	     otree[idif]->Fill();

	  if(wgwmdata->NocutCreation(idif, ientry, wgrecon_nocut))
	     otree_nocut[idif]->Fill();

	  if(ientry%10000==0)
	    cout << "Analyze : " << ientry << '\n';
	  
	  wgrecon->Clear();
	  wgrecon_nocut->Clear();
	}
      
      fout[idif]->cd();
      otree[idif]->Write();
      fout[idif]->Close(); 

      fout_nocut[idif]->cd();
      otree_nocut[idif]->Write();
      fout_nocut[idif]->Close(); 
    }
 
  return 0;
}
