//Standard
#include <iostream>
#include <stdio.h>

//MyInc
#include "DataSanity.cpp"
#include "BSDApply.cpp"

//MyLib
#include "BMBasicRecon.hpp"
#include "BMBeaminfo.hpp"

#include <TString.h>
#include <TApplication.h>
#include <TCanvas.h>

using namespace std;

int main( int argc, char **argv )
{
  //Set Parameters
  int sunix, eunix;
  int startdate = 0;
  int enddate = 31;
  int startrun = 0;
  int endrun = 6;
  double accumlated_pot=0;
  double recorded_pot=0;
  FileStat_t info;

  TString bmdirpath, bmfilename;
  bmdirpath.Form("./process/3-BMBSD");
  TChain* bmchain = new TChain("tree","tree");

  //Set Classes
  DataSanity *datasanity = new DataSanity();
  BSDApply* bsdapply = new BSDApply();
  BMBSD *bmbsd = new BMBSD();

  bsdapply->ReadBSDfile();

  for(int idate=startdate; idate<enddate; idate++)
    {
      for(int irun=startrun; irun<endrun; irun++)
        {
          bmfilename.Form("%s/BMBSD_%d_Nov_%d.root", bmdirpath.Data(), idate, irun);
          if (gSystem->GetPathInfo(bmfilename.Data(), info)!=0)
            {
              continue;
            }else{
            bmchain->Add(bmfilename);
          }
        }//isub
    }//irun
  bmchain->SetBranchAddress("BMBSD", &bmbsd);
  cout << "Baby MIND entries = " << bmchain->GetEntries() <<'\n';
  
  bmchain->GetEntry(0);
  sunix = bmbsd->unixtime;
  bmchain->GetEntry(bmchain->GetEntries()-1);
  eunix = bmbsd->unixtime;

  cout << "sunix= " << sunix << " eunix= " << eunix << '\n';

  TFile* fout = new TFile("./result/BSD/Accumlated_pot.root", "recreate");

  TH2D *bsd_accumlated_plot = new TH2D("bsd_accumlated_plot", "", 500, sunix, eunix, 500, 0, 2.0);
  TH2D *bm_accumlated_plot = new TH2D("bm_accumlated_plot", "", 500, sunix, eunix, 500, 0, 2.0);
  char ytitle[128] = "Accumlated P.O.T (10^{20})";
  datasanity->SetHistLabel(bsd_accumlated_plot, "Data Taking Efficiency", ytitle);
  datasanity->SetHistLabel(bm_accumlated_plot, "Data Taking Efficiency", ytitle);
  bm_accumlated_plot->SetMarkerColor(2);

  for(int ientry=0; ientry<bmchain->GetEntries(); ientry++)
    {
      bmchain->GetEntry(ientry);
      recorded_pot += bmbsd->pot/pow(10, 20);
      bm_accumlated_plot->Fill(bmbsd->unixtime, recorded_pot);
    }

  for(int ientry=0; ientry<bsdapply->bsdchain->GetEntries(); ientry++)
    {
      bsdapply->bsdchain->GetEntry(ientry);
      if(bsdapply->trg_sec[2]<sunix || bsdapply->trg_sec[2]>eunix) continue;
      accumlated_pot += bsdapply->ct_np[4][0]/pow(10, 20);
      bsd_accumlated_plot->Fill(bsdapply->trg_sec[2], accumlated_pot);
    }

  cout << "BM= " << recorded_pot << " BSD= " << accumlated_pot << '\n';
  cout << "Data Taking Efficiency= " << recorded_pot/accumlated_pot << '\n';

  fout->cd();
  bsd_accumlated_plot->Write();
  bm_accumlated_plot->Write();
  fout->Close();

  bmchain->Delete();
  bsdapply->KillAll();
  return 0;
  
}//main
