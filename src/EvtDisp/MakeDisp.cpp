#include <iostream>
#include <stdio.h>

//include
#include <TString.h>

//library
#include "EVTCluster.hpp"
#include "MakeMonitor.cpp"

using namespace std;

int main( int argc, char **argv )
{
  if(argc < 4)
    {
      cout << "usage" << '\n';
      cout << "MakeDisp [filepath][wgrun][ientry]" << '\n';
      exit(0);
    }

  std::string name = string(argv[1]);
  std::string run = string(argv[2]);
  int targetentry = atoi(argv[3]);
  TString filepath(name);
  TString CanvasName;

  TApplication app("app", 0, 0, 0, 0);
  EVTCluster *evtcluster = new EVTCluster();
  TFile* file = new TFile(filepath, "read");
  TTree* tree = (TTree*)file->Get("tree");
  tree->SetBranchAddress("EVTCluster",&evtcluster);
  MakeMonitor *makemonitor = new MakeMonitor();
  
  for(int ientry=0; ientry<tree->GetEntries(); ientry++)
    {
      if(ientry!=targetentry) continue;
      {
	tree->GetEntry(targetentry);
	cout << "size= " << evtcluster->pln.size() << '\n';
	makemonitor->Display(evtcluster);
	//CanvasName.Form("./plots/EvtDisp/EvtDisp_spill_%d.pdf", bmdisp->spillnum);
	//makemonitor->monitor->Print(CanvasName);
	makemonitor->timeinfo->Delete();
	makemonitor->spillinfo->Delete();
      }
    }
  
  app.Run();
  return 0;
  
}
