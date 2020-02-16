#include <iostream>
#include <stdio.h>

#include <TString.h>
#include <TTree.h>
#include <TFile.h>

//include

//library
#include "EVTCluster.hpp"
#include "BMDisp.hpp"

using namespace std;

int main( int argc, char **argv )
{
  std::string name = string(argv[1]);
  TString filename(name);
  TString histname;

  EVTCluster* evtcluster = new EVTCluster();
  BMDisp* bmdisp[8];
  for(int ibunch=0; ibunch<8; ibunch++)
    bmdisp[ibunch] = new BMDisp();

  TFile *fin = new TFile(filename, "Read");
  TTree *tree = (TTree*)fin->Get("tree");
  tree->SetBranchAddress("EVTCluster", &evtcluster);
  cout << tree->GetEntries() << '\n';

  //for(int ientry=0; ientry<tree->GetEntries(); ientry++)
  for(int ientry=0; ientry<10; ientry++)
    {
      for(int ibunch=0; ibunch<8; ibunch++)
	bmdisp[ibunch]->Clear();
      tree->GetEntry(ientry);
     
      for(int ihit=0; ihit<evtcluster->mod.size(); ihit++)
	{
	  int bunch = evtcluster->bunch.at(ihit) - 1;
	  int mod = evtcluster->mod.at(ihit) - 1;
	  if(bunch !=-2 && mod==5)
	    {
	      bmdisp[bunch]->bunch.push_back(evtcluster->bunch.at(ihit));
	      bmdisp[bunch]->mod.push_back(evtcluster->mod.at(ihit));
	      bmdisp[bunch]->view.push_back(evtcluster->view.at(ihit));
	      bmdisp[bunch]->pln.push_back(evtcluster->pln.at(ihit));
	      bmdisp[bunch]->channel.push_back(evtcluster->channel.at(ihit));
	      bmdisp[bunch]->Htime.push_back(evtcluster->Htime.at(ihit));
	    }
	}
      
      

    }

  
  return 0;
  
}
