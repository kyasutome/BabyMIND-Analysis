#include <iostream>
#include <stdio.h>

//include
#include "matching.cpp"
#include "wallmrd.cpp"
#include "protonmodule.cpp"

//library
#include "EVTCluster.hpp"

#include "TApplication.h"
#include "TCanvas.h"
#include "TStyle.h"

using namespace std;

int main( int argc, char **argv )
{
  std::string name = string(argv[1]);
  TString filename(name);

  TApplication app("app", 0, 0, 0, 0);
  TCanvas *c1= new TCanvas("c1", "c1", 1000, 600);
  
  EVTCluster *evtcluster = new EVTCluster();
  WallMRD *wallmrd = new WallMRD();
  ProtonModule *protonmodule = new ProtonModule();
  Matching *matching = new Matching();
  BasicRecon *basicrecon = new BasicRecon();

  TFile* fin = new TFile(filename, "READ");
  TTree* tree = (TTree*)fin->Get("tree");
  tree->SetBranchAddress("EVTCluster", &evtcluster);
  int NEntry = tree->GetEntries();


  for(int ientry=0; ientry<2000; ientry++)
    {
      basicrecon->Clear();
      tree->GetEntry(ientry);

      protonmodule->EasyRecon(evtcluster, basicrecon);      
      //protonmodule->fithist->Draw("box");
      //c1->Update();
      //gSystem->ProcessEvents();
      //sleep(1);
      
      if(fabs(basicrecon->angle[1])>50)
	cout << "ientry= " << ientry  << " scattering angle = "  << basicrecon->angle[1] << '\n';
    }

  //app.Run();
  
}
