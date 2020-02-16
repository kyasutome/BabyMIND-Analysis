#include <iostream>
#include <stdio.h>

//include
#include "matching.cpp"
#include "wallmrd.cpp"
#include "easyrecon.cpp"

//library
#include "EVTCluster.hpp"

#include "TApplication.h"
#include "TCanvas.h"
#include "TStyle.h"

using namespace std;
//#define fitting

int main( int argc, char **argv )
{
  std::string name = string(argv[1]);
  TString filename(name);
  
  EVTCluster *evtcluster = new EVTCluster();
  EasyRecon *easyrecon = new EasyRecon();
  Matching *matching = new Matching();
  BasicRecon *basicrecon[7];
  for(int i=0; i<7; i++)
    basicrecon[i] = new BasicRecon();

  TFile* fin = new TFile(filename, "READ");
  TTree* tree = (TTree*)fin->Get("tree");
  tree->SetBranchAddress("EVTCluster", &evtcluster);
  int NEntry = tree->GetEntries();


  for(int ientry=0; ientry<2000; ientry++)
    {
      basicrecon[0]->Clear();
      tree->GetEntry(ientry);

      easyrecon->Recon(evtcluster, basicrecon);

      if(fabs(basicrecon[0]->angle[1])>50)
	cout << "ientry= " << ientry  << " scattering angle = "  << basicrecon[0]->angle[1] << '\n';

#ifdef fitting
      TApplication app("app", 0, 0, 0, 0);
      TCanvas *c1= new TCanvas("c1", "c1", 1000, 600);
      easyrecon->fithist->Draw("box");
      c1->Update();
      gSystem->ProcessEvents();
      sleep(1);
      app.Run();
#endif fitting
      
    }
  
}
