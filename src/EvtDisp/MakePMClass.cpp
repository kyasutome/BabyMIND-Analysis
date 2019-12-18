#include <iostream>
#include <stdio.h>

//include
#include "MakePMChain.cpp"

//library
#include "PMRecon.hpp"


using namespace std;

int main( int argc, char **argv )
{
  if(argc < 4)
    {
      cout << "usage" << '\n';
      cout << "MakePMClass [date][month][run]" << '\n';
      exit(0);
    }

  int pmrun = std::atoi(argv[1]);
  int pmssub = std::atoi(argv[2]);
  int pmesub = std::atoi(argv[3]);

  PMRecon *pmrecon = new PMRecon();
  MakePMChain *makepmchain = new MakePMChain();
  
  TFile *fout = new TFile(Form("./process/2-PMClass/PMClass_%d_%d_%d.root",pmrun,pmssub,pmesub),"recreate");
  TTree *otree = new TTree("tree","tree");
  otree->Branch("PMRecon","PMRecon",&pmrecon,32000,2);

  makepmchain->ReadPMTree(pmrun, pmssub, pmesub, pmrecon);
  
  for(int ientry=0; ientry<makepmchain->pmchain->GetEntries(); ientry++)
    {
      pmrecon->Clear();
      makepmchain->FillPMClass(ientry, pmrecon);
      otree->Fill();
    }

  fout->cd();
  otree->Write();
  fout->Close();

  
}
