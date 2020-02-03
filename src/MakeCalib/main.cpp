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
  vector<double> commonspill;

  //Set Classes
  BMdata* bmbranch[NUMBEROFFEB];
  DataReader *dreader = new DataReader();
  PickSignal *picksignal = new PickSignal();
  BMBasicRecon *bmbasicrecon = new BMBasicRecon();
  BMBeaminfo *bmbeaminfo = new BMBeaminfo();

  //Set output file
  TFile *fout[2];
  TTree *tree[2];
  int filecount=0;

  for(int ifile=0; ifile<1; ifile++)
    {
      outputfilename.Form("./process/6-YASU/BMCalib_%s%s_%s-%d.root", date.c_str(), month.c_str(), run.c_str(), filecount);
      fout[ifile] = new TFile(outputfilename, "recreate");
      tree[ifile] = new TTree("tree", "tree");
      tree[ifile]->Branch("BMBasicRecon","BMBasicRecon", &bmbasicrecon, 32000, 2);
      tree[ifile]->Branch("BMBeaminfo","BMBeaminfo", &bmbeaminfo, 32000, 2);
    }

  //Initialize a class
  for(int i=0; i<NUMBEROFFEB; i++)
      bmbranch[i] = new BMdata();

  //Read tree
  dreader->ReadTree(filepath, bmbranch);  
  dreader->BMSpillMatch(&commonspill);

  for(int ientry=0; ientry<commonspill.size(); ientry++)
  //for(int ientry=0; ientry<100; ientry++)
    {
      bmbasicrecon->Clear();
      bmbasicrecon->bm_event = ientry;
      picksignal->SignalCreation(ientry, bmbranch, bmbasicrecon, dreader, commonspill);
      picksignal->YASUSignalCreation(ientry, bmbranch, bmbasicrecon, dreader, commonspill);
      bmbeaminfo->spillnum = (int)(bmbranch[0]->SpillTag->at(0))&0x7fff;
      //bmbeaminfo->spillnum = (int)(bmbranch[49]->SpillTag->at(0))&0x7fff;
      tree[filecount]->Fill();
      picksignal->EventProcess(1000, ientry);      

      if(ientry==25000-1)
	{
	  fout[0]->cd();
	  tree[0]->Write();
	  fout[0]->Close();
	  filecount++;

	  outputfilename.Form("./process/6-YASU/BMCalib_%s%s_%s-%d.root", date.c_str(), month.c_str(), run.c_str(), filecount);
	  fout[1] = new TFile(outputfilename, "recreate");
	  tree[1] = new TTree("tree", "tree");
	  tree[1]->Branch("BMBasicRecon","BMBasicRecon", &bmbasicrecon, 32000, 2);
	  tree[1]->Branch("BMBeaminfo","BMBeaminfo", &bmbeaminfo, 32000, 2);      
	}
    }

  if(filecount==1)
    {
      fout[1]->cd();
      tree[1]->Write();
      fout[1]->Close();
    }

}//main
