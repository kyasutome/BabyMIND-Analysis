//Standard
#include <iostream>
#include <stdio.h>

//MyInc
#include "BSDApply.cpp"

//MyLib
#include "BMBasicRecon.hpp"
#include "BMBeaminfo.hpp"
#include "BMBSD.hpp"

#include <TString.h>


using namespace std;

int main( int argc, char **argv )
{

  //Usage
  if(argc < 8)
    {
      cout << "usage" << '\n';
      cout << "BSDAppply_BM [filepath][date][month][run][bmmon][bmdate][bmhour]" << '\n';
      exit(0);
    }

  //Set Parameters
  
  std::string name = string(argv[1]);
  std::string date = string(argv[2]);
  std::string month = string(argv[3]);
  std::string run = string(argv[4]);
  int bmmon = atoi(argv[5]);
  int bmdate = atoi(argv[6]);
  int bmhour = atoi(argv[7]);
  TString filepath(name);

  //Set Classes
  BMBasicRecon *bmbasicrecon = new BMBasicRecon();
  BMBeaminfo *bmbeaminfo = new BMBeaminfo();
  BMBSD *bmbsd = new BMBSD();
  BSDApply *bsdapply = new BSDApply();

  TFile* fin = new TFile(filepath, "read");
  TTree* tree = (TTree*)fin->Get("tree");
  tree->SetBranchAddress("BMBasicRecon",&bmbasicrecon);
  tree->SetBranchAddress("BMBeaminfo",&bmbeaminfo);

  TString ofilepath;
  ofilepath.Form("${processdir}/process/2-BMBSD/BMBSD_BM_%s_%s_%s.root", 
		 date.c_str(), month.c_str(), run.c_str());
  TFile* fout = new TFile(ofilepath, "recreate");
  TTree* otree = new TTree("tree", "tree");  
  otree->Branch("BMBasicRecon","BMBasicRecon", &bmbasicrecon, 64000, 2);
  otree->Branch("BMBeaminfo","BMBeaminfo", &bmbeaminfo, 64000, 2);
  otree->Branch("BMBSD", "BMBSD", &bmbsd, 64000, 2);

  tree->GetEntry(0);
  int bmfirstspill = bmbeaminfo->spillnum;
  int subfile=0;
  int icount=0;
  bool firstcheck = false;

  bsdapply->ReadBSDfile();
  bsdapply->FindFirstSpill(&bmfirstspill, bmmon, bmdate, bmhour, 5);

  cout << "bmfirstspill= " << bmfirstspill << '\n';

  for(int ientry=0; ientry<tree->GetEntries(); ientry++)
    {
      tree->GetEntry(ientry);
      bsdapply->bmspill.push_back(bmbeaminfo->spillnum);

      if(bmbeaminfo->spillnum < bmfirstspill && !firstcheck) continue;
      else if(bmbeaminfo->spillnum == bmfirstspill) firstcheck=true;

      bsdapply->bmgroup[subfile][0].push_back(bmbeaminfo->spillnum);
      icount++;
      if(icount%1000==999)
	{
	  subfile++;
	  icount=0;
	}
    }

  cout << "BMSpillSize= " << tree->GetEntries() << " subfile= " << subfile+1  << '\n';

  for(int isub=0; isub<subfile+1; isub++)
    {
      bsdapply->MakeBeamGroup(isub);
      bsdapply->SpillMatch(isub, 5);
      bsdapply->FillBSD(tree, otree, bmbsd, 5, bmbasicrecon, bmbeaminfo);
    }

  fout->cd();
  otree->Write();
  fout->Close();
  fin->Close();
  
}//main
