#include <iostream>
#include <stdio.h>

//include
#include "DataReader.cpp"
#include "EvtFormat.cpp"

//library
#include "MCRecon.hpp"
#include "MCTrue.hpp"
#include "EVTCluster.hpp"


using namespace std;

int main( int argc, char **argv )
{
  std::string name = string(argv[1]);
  int wgrun = std::atoi(argv[2]);
  TString commondir(name);  

  MCRecon *mcrecon = new MCRecon();
  MCTrue *mctrue = new MCTrue();

  EVTCluster *evtcluster = new EVTCluster();
  EvtFormat *evtformat = new EvtFormat();
  
  TFile *fout = new TFile(Form("./process/3-MCEVT/Evt_%d.root", wgrun),"recreate");
  TTree *otree = new TTree("tree","tree");
  otree->Branch("EVTCluster","EVTCluster",&evtcluster,32000,2);  
  otree->Branch("MCTrue","MCTrue",&mctrue,32000,2);

  evtformat->ReadMCChain(commondir, mctrue, mcrecon, otree, evtcluster);
  
  fout->cd();
  otree->Write();
  fout->Close();

  
}
