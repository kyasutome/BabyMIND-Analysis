#include <iostream>
#include <stdio.h>

//include
#include "wallmrd.cpp"

//library
#include "EVTCluster.hpp"

using namespace std;

int main( int argc, char **argv )
{
  std::string name = string(argv[1]);
  TString filename(name);
  
  EVTCluster *evtcluster = new EVTCluster();
  WallMRD *wallmrd = new WallMRD();

  TFile* fin = new TFile(filename, "READ");
  TTree* tree = (TTree*)fin->Get("tree");
  tree->SetBranchAddress("EVTCluster", &evtcluster);
  int NEntry = tree->GetEntries();

  int count[2] = {0, 0};
  int dif[4] = {0, 0, 0, 0};

  for(int ientry=0; ientry<20; ientry++)
    {
      //cout << "ientry= " << ientry << '\n';
      tree->GetEntry(ientry);
      wallmrd->Nhit(evtcluster, count, dif);
    }

  
}
