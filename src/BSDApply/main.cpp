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
      cout << "BSDAppply [filepath][date][month][run][bmmon][bmdate][bmhour]" << '\n';
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
  ofilepath.Form("./process/3-BMBSD/BMBSD_%s_%s_%s.root", date.c_str(), month.c_str(), run.c_str());
  TFile* fout = new TFile(ofilepath, "recreate");
  TTree* otree = new TTree("tree", "tree");  
  otree->Branch("BMBasicRecon","BMBasicRecon", &bmbasicrecon, 32000, 2);
  otree->Branch("BMBeaminfo","BMBeaminfo", &bmbeaminfo, 32000, 2);
  otree->Branch("BMBSD", "BMBSD", &bmbsd, 32000, 2);

  tree->GetEntry(0);
  int bmfirstspill = bmbeaminfo->spillnum;
  int subfile=0;

  for(int ientry=0; ientry<tree->GetEntries(); ientry++)
    {
      tree->GetEntry(ientry);
      bsdapply->bmspill.push_back(bmbeaminfo->spillnum);
      if(ientry<bsdapply->nsubdata*(subfile+1) && ientry>=bsdapply->nsubdata*subfile)
        bsdapply->bmgroup[subfile][0].push_back(bmbeaminfo->spillnum);

      if(ientry==bsdapply->nsubdata*(subfile+1)-1)
        subfile++;
    }

  cout << "BMSpillSize= " << tree->GetEntries() << " subfile= " << subfile+1  << '\n';
  bsdapply->ReadBSDfile();
  bsdapply->FindFirstSpill(bmfirstspill, bmmon, bmdate, bmhour);
  for(int isub=0; isub<subfile+1; isub++)
    {
      bsdapply->MakeBeamGroup(isub);
      bsdapply->SpillMatch(isub);
      bsdapply->FillBSD(tree, otree, bmbsd);
    }

  fout->cd();
  otree->Write();
  fout->Close();
  fin->Close();
  
}//main
