#include <iostream>
#include <stdio.h>

//include
#include "MCData.cpp"

//library
#include "EVTCluster.hpp"

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

  EVTCluster* evtcluster = new EVTCluster();
  MCRecon* mcrecon = new MCRecon();
  MCTrue* mctrue = new MCTrue();
  MCdata* mcdata = new MCdata();

  TFile *fout = new TFile(Form("${processdir}/process/1-MCCalib/MCCalib_%d.root", runnumber), "RECREATE");
  TTree *otree = new TTree("tree", "tree");
  otree->Branch("MCRecon","MCRecon",&mcrecon,32000,2);
  otree->Branch("MCTrue","MCTrue",&mctrue,32000,2);

  mcdata->ReadMCdata(filedir, otree, mcrecon, mctrue);  
  fout->cd();
  otree->Write();

  fout->Close();
  
  return 0;
}
