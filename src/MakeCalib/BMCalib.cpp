//Standard
#include <iostream>
#include <stdio.h>

//MyInc
#include "BMData.cpp"
#include "DataReader.cpp"
#include "PickSignal.cpp"

//MyLib
#include "BMBasicRecon.hpp"
#include "BMBeaminfo.hpp"


using namespace std;

int main( int argc, char **argv )
{

  //Usage
  if(argc < 5)
    {
      cout << "usage" << '\n';
      cout << "MakeCalib [filepath][date][month][run]" << '\n';
      exit(0);
    }

  //Set Parameters
  std::string name = string(argv[1]);
  std::string date = string(argv[2]);
  std::string month = string(argv[3]);
  std::string run = string(argv[4]);
  TString filepath(name);
  TString outputfilename;
  vector<double> commonspill[3];

  //Set Classes
  BMdata* bmbranch[NUMBEROFFEB];
  DataReader *dreader = new DataReader();
  PickSignal *picksignal = new PickSignal();
  BMBasicRecon *bmbasicrecon = new BMBasicRecon();
  BMBeaminfo *bmbeaminfo = new BMBeaminfo();

  //Set output file
  TFile *fout;
  TTree *tree;

  outputfilename.Form("${processdir}/process/1-BMCalib/BMCalib_%s%s_%s.root", 
		      date.c_str(), month.c_str(), run.c_str());
  fout = new TFile(outputfilename, "recreate");
  tree = new TTree("tree", "tree");
  tree->Branch("BMBasicRecon","BMBasicRecon", &bmbasicrecon, 32000, 2);
  tree->Branch("BMBeaminfo","BMBeaminfo", &bmbeaminfo, 32000, 2);

  //Initialize a class
  for(int i=0; i<NUMBEROFFEB; i++)
      bmbranch[i] = new BMdata();

  //Read tree
  dreader->ReadTree(filepath, bmbranch);  
  dreader->BMSpillMatch(commonspill);
  picksignal->PickGain();

  cout << "spill= " << commonspill[0].size() << '\n';
  cout << "spill= " << commonspill[1].size() << '\n';
  cout << "spill= " << commonspill[2].size() << '\n';

  for(int i=0; i<3; i++)
    {
      for(int ientry=0; ientry<commonspill[i].size(); ientry++)
	//for(int ientry=30000; ientry<35000; ientry++)
	//for(int ientry=0; ientry<100; ientry++)
	{
	  bmbasicrecon->Clear();
	  bmbasicrecon->bm_event = ientry+20000*i;
	  picksignal->SignalCreation(ientry, bmbranch, bmbasicrecon, dreader, commonspill[i], i);
	  picksignal->YASUSignalCreation(ientry, bmbranch, bmbasicrecon, dreader, commonspill[i], i);
	  bmbeaminfo->spillnum = (int)(bmbranch[0]->SpillTag->at(0))&0x7fff;
	  //cout << bmbeaminfo->spillnum << '\n';
	  tree->Fill();
	  picksignal->EventProcess(1000, ientry);
	}
    }

  fout->cd();
  tree->Write();
  fout->Close();

}//main
