//Standard
#include <iostream>
#include <stdio.h>

//MyInc
#include "BSDApply.cpp"

//MyLib
#include "PMRecon.hpp"
#include "BMBSD.hpp"

#include <TString.h>


using namespace std;

int main( int argc, char **argv )
{

  //Usage
  if(argc < 4)
    {
      cout << "usage" << '\n';
      cout << "BSDAppply [filepath][run][startsub][endsub]" << '\n';
      exit(0);
    }

  //Set Parameters
  
  std::string name = string(argv[1]);
  std::string run = string(argv[2]);
  std::string ssub = string(argv[3]);
  std::string esub = string(argv[4]);
  int pmmon=0;
  int pmdate=0;
  int pmhour=0;
  TString filepath(name);

  //Set Classes
  PMRecon *pmrecon = new PMRecon();
  BMBSD *bmbsd = new BMBSD();
  BSDApply *bsdapply = new BSDApply();

  TFile* fin = new TFile(filepath, "read");
  TTree* tree = (TTree*)fin->Get("tree");
  tree->SetBranchAddress("PMRecon",&pmrecon);

  TString ofilepath;
  ofilepath.Form("${processdir}/process/2-BMBSD/BMBSD_PM_%s_%s_%s.root", 
		 run.c_str(), ssub.c_str(), esub.c_str());
  TFile* fout = new TFile(ofilepath, "recreate");
  TTree* otree = new TTree("tree", "tree");  
  otree->Branch("PMRecon","PMRecon", &pmrecon, 32000, 2);
  otree->Branch("BMBSD", "BMBSD", &bmbsd, 32000, 2);

  tree->GetEntry(0);
  int pmfirstspill = pmrecon->spill;
  int pmfirstunixtime = pmrecon->unixtime;
  int subfile=0;
  int icount=0;
  bool firstcheck = false;
    
  bsdapply->GetMonDateHour(pmfirstunixtime, &pmmon, &pmdate, &pmhour);
  cout << pmmon << " " << pmdate << " " << pmhour << '\n';
  bsdapply->ReadBSDfile();
  bsdapply->FindFirstSpill(&pmfirstspill, pmmon, pmdate, pmhour, 0);

  cout << "pmfirstspill= " << pmfirstspill << '\n';

  for(int ientry=0; ientry<tree->GetEntries(); ientry++)
    {
      tree->GetEntry(ientry);
      bsdapply->pmspill.push_back(pmrecon->spill);

      if(pmrecon->spill < pmfirstspill && !firstcheck) continue;
      else if(pmrecon->spill == pmfirstspill) firstcheck=true;

      bsdapply->pmgroup[subfile][0].push_back(pmrecon->spill);
      icount++;
      if(icount%1000==999)
	{
	  subfile++;
	  icount=0;
	}
    }

  cout << "PMSpillSize= " << tree->GetEntries() << " subfile= " << subfile+1  << '\n';

  for(int isub=0; isub<subfile+1; isub++)
    {
      bsdapply->MakeBeamGroup(isub);
      bsdapply->SpillMatch(isub, 0);
      //bsdapply->FillBSD(tree, otree, bmbsd, 0);
    }

  fout->cd();
  otree->Write();
  fout->Close();
  fin->Close();
  
}//main
