#include <iostream>
#include <stdio.h>

//include
#include "WGChannelMap.cpp"

//library


using namespace std;

int main( int argc, char **argv )
{
  /*
  if(argc < 4)
    {
      cout << "usage" << '\n';
      cout << "MakeWGClass [date][month][run]" << '\n';
      exit(0);
    }
  */

  WGRecon *wgrecon = new WGRecon();
  WGChannelMap *wgchannelmap = new WGChannelMap();
  
  TFile *fout = new TFile(Form("./process/5-WGClass/WGClass_%d_%d_%d.root",pmrun,pmssub,pmesub),"recreate");
  TTree *otree = new TTree("tree","tree");
  otree->Branch("WGRecon","WGRecon",&wgrecon,32000,2);



  fout->cd();
  otree->Write();
  fout->Close();

  
}
