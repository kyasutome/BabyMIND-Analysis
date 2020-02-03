#include <iostream>
#include <stdio.h>

//include
#include "WGWMData.cpp"

//library
#include "WGRecon.hpp"

using namespace std;

int main( int argc, char **argv )
{
  
  
  if(argc < 2)
    {
      cout << "usage" << '\n';
      cout << "MakeWGWMClass [filepath]" << '\n';
      exit(0);
    }

  std::string name = string(argv[1]);
  TString filedir(name);
  TString filepath;

  int Nspill;
  int startspill, endspill;
  int thespill;
  int divide;
  int thewgwmspill[8];

  int eachentry[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  int entrycorr[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  int startentry[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  int spillcount=0;

  bool corrflag;

  WGRecon *wgrecon = new WGRecon();
  WGWMdata *wgwmdata = new WGWMdata();
  
  TFile *fout = new TFile("./process/9-WGWMClass/WGWMClass.root", "RECREATE");
  TTree *otree = new TTree("tree", "tree");
  otree->Branch("WGRecon","WGRecon",&wgrecon,32000,2);

  for(int idif=0; idif<8; idif++)
    {
      int DIF=idif;
      filepath.Form("%s/physics_run_2020-01-29_18-30-08_92_ecal_dif_%d_tree.root", filedir.Data(), DIF);
      wgwmdata->ReadTree(filepath, DIF);
    }

  wgwmdata->EntryCheck(startentry, 0);
  Nspill=wgwmdata->GetNofSpill(0, &startspill, &endspill);
  cout << "Number of Spill= "  << Nspill << '\n';
  cout << "First Spill= " << startspill << " End Spill= " << endspill << '\n';  
  
  for(int ispill=0; ispill<Nspill; ispill++)
  //for(int ispill=0; ispill<100; ispill++)
    {
      bool cont = false;
      thespill = (startspill+ispill)%32767;
      for(int idif=0; idif<8; idif++)
	{
	  if(ispill<30000) divide=0;
	  if(ispill>=30000) divide=1;

	  auto thespillit 
	    = find(wgwmdata->wgwmspill[divide][idif].begin(), wgwmdata->wgwmspill[divide][idif].end(), thespill);
	  //cout << *thespillit << " "  << thewgwmspill[idif] << '\n';
	  if(*thespillit==0 || (ispill!=0 && abs(*thespillit-thespill)>20 && (thespill!=0 || thespill!=1))) 
	    {
	      cont = true;
	      break;
	    }
	  thewgwmspill[idif] = thespillit-wgwmdata->wgwmspill[divide][idif].begin();
	  eachentry[idif] = wgwmdata->wgwmentryid[divide][idif].at(thewgwmspill[idif]);
	} 
      if(cont) continue;
      if(wgwmdata->SignalCreation(eachentry, wgrecon))
	otree->Fill();
      
      
      if(ispill%3000==0)
	cout << "ientry= " << ispill << '\n';      
      wgrecon->Clear(); 
    }
 
  
  fout->cd();
  otree->Write();
  fout->Close(); 
  
  return 0;
}
