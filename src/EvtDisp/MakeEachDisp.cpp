#include <iostream>
#include <stdio.h>

//include
#include "MakeEachMonitor.cpp"

//library
#include "WGRecon.hpp"

//ROOT
#include "TApplication.h"
#include "BMDisp.hpp"

using namespace std;

int main( int argc, char **argv )
{
    
  if(argc < 2)
    {
      cout << "usage" << '\n';
      cout << "MakeWGWMClass [filepath] [targetentry]" << '\n';
      exit(0);
    }

  TApplication app("app", 0, 0, 0, 0);

  std::string name = string(argv[1]);
  int targetentry = std::atoi(argv[2]);
  TString filedir(name);
  TString filepath;
  TFile* fin;
  TTree* tree;
  WGRecon *wgrecon = new WGRecon();
  BMDisp *bmdisp = new BMDisp();
  MakeEachMonitor *makeeachmonitor = new MakeEachMonitor();
  
  filepath.Form("./process/9-WGWMClass/WGWMClass.root");
  
  fin = new TFile(filepath, "read");
  tree = (TTree*)fin->Get("tree");
  tree->SetBranchAddress("WGRecon", &wgrecon);

  for(int ientry=0; ientry<tree->GetEntries(); ientry++)
    {
      if(ientry!=targetentry) continue;
      tree->GetEntry(ientry);
      for(int idata=0; idata<wgrecon->mod.size(); idata++)
	{
	  bmdisp->mod.push_back(wgrecon->mod.at(idata));
	  bmdisp->view.push_back(wgrecon->view.at(idata));
	  bmdisp->pln.push_back(wgrecon->pln.at(idata));
	  bmdisp->channel.push_back(wgrecon->channel.at(idata));
	  bmdisp->bunch.push_back(wgrecon->bunch.at(idata));	  
	}

      makeeachmonitor->Display(bmdisp);

    }

  app.Run();  
  return 0;
}
