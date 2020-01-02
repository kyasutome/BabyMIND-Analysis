//Standard
#include <iostream>
#include <stdio.h>

#include <TString.h>

#include "cellautomation.hpp"
#include "BMDisp.hpp"

using namespace std;

int main( int argc, char **argv )
{

  if(argc < 5)
    {
      cout << "usage" << '\n';
      cout << "TrackRecon [filepath][date][month][run][ientry]" << '\n';
      exit(0);
    }
  
  std::string name = string(argv[1]);
  std::string date = string(argv[2]);
  std::string month = string(argv[3]);
  std::string run = string(argv[4]);
  int targetentry = atoi(argv[5]);
  TString filepath(name);

  TApplication app("app", 0, 0, 0, 0);
  BMDisp *bmdisp = new BMDisp();
  TFile* file = new TFile(filepath, "read");
  TTree* tree = (TTree*)file->Get("tree");
  tree->SetBranchAddress("BMDisp",&bmdisp);

  for(int ientry=0; ientry<tree->GetEntries(); ientry++)
    {
      if(ientry!=targetentry) continue;
      tree->GetEntry(targetentry);
    }

  //app.Run();
  return 0;


  
}//main
