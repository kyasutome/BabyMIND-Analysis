//Standard
#include <iostream>
#include <stdio.h>

//MyInc
#include "BSDApply.cpp"

//MyLib
#include "WGRecon.hpp"
#include "BMBSD.hpp"

#include <TString.h>


using namespace std;

int main( int argc, char **argv )
{

  //Usage
  if(argc < 5)
    {
      cout << "usage" << '\n';
      cout << "BSDAppply_WGnocut [filepath][run][wgmon][wgdate][wghour]" << '\n';
      exit(0);
    }

  //Set Parameters
  
  std::string name = string(argv[1]);

  int wgrun = atoi(argv[2]);
  int wgmon = atoi(argv[3]);
  int wgdate = atoi(argv[4]);
  int wghour = atoi(argv[5]);

  //Set Classes
  WGRecon *wgrecon[8];
  BMBSD *bmbsd[8];

  BSDApply *bsdapply = new BSDApply();

  TString filepath;
  TFile* fin[8];
  TTree* tree[8];

  TString ofilepath;
  TFile* fout[8];
  TTree* otree[8];

  bsdapply->ReadBSDfile();

  for(int idif=0; idif<1; idif++)
    {      
      wgrecon[idif] = new WGRecon();
      bmbsd[idif] = new BMBSD();

      for(int i=0; i<2; i++)
	for(int j=0; j<100; j++)
	  {
	    bsdapply->wggroup[j][i].clear();
	  }

      bsdapply->wgspill.clear();

      filepath.Form("%s/WGCalib_%d_dif%d.root", name.c_str(), wgrun, idif);
      cout << "filepath= " << filepath.Data() << '\n';
      fin[idif] = new TFile(filepath, "read");
      tree[idif]= (TTree*)fin[idif]->Get("tree");
      tree[idif]->SetBranchAddress("WGRecon",&wgrecon[idif]);

      ofilepath.Form("./process/0-WGnocut/WGBSD_%d_dif%d.root", wgrun, idif);      
      fout[idif]= new TFile(ofilepath, "recreate");
      otree[idif]= new TTree("tree", "tree");  
      otree[idif]->Branch("WGRecon","WGRecon", &wgrecon[idif], 32000, 2);
      otree[idif]->Branch("BMBSD", "BMBSD", &bmbsd[idif], 32000, 2);

      tree[idif]->GetEntry(0);
      int wgfirstspill = wgrecon[idif]->spill;
      int subfile=0;
      int icount=0;
      bool firstcheck = false;

      bsdapply->FindFirstSpill(&wgfirstspill, wgmon, wgdate, wghour, 1);      
      cout << "wgfirstspill= " << wgfirstspill << '\n';
      
      for(int ientry=0; ientry<tree[idif]->GetEntries(); ientry++)
	{
	  tree[idif]->GetEntry(ientry);
	  bsdapply->wgspill.push_back(wgrecon[idif]->spill);
	  
	  if(wgrecon[idif]->spill < wgfirstspill && !firstcheck) continue;
	  else if(wgrecon[idif]->spill == wgfirstspill) firstcheck=true;
	  
	  bsdapply->wggroup[subfile][0].push_back(wgrecon[idif]->spill);
	  icount++;
	  if(icount%1000==999)
	    {
	      subfile++;
	      icount=0;
	    }
	}

      cout << "WGSpillSize= " << tree[idif]->GetEntries() << " subfile= " << subfile+1  << '\n';

      for(int isub=0; isub<subfile+1; isub++)
	{
	  bsdapply->MakeBeamGroup(isub);
	  bsdapply->SpillMatch(isub, 1);
	  bsdapply->FillBSD(tree[idif], otree[idif], bmbsd[idif], 1);
	}

      fout[idif]->cd();
      otree[idif]->Write();
      fout[idif]->Close();
      fin[idif]->Close();
    }//idif

  
}//main
