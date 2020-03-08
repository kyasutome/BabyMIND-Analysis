//Standard
#include <iostream>
#include <stdio.h>

//MyInc
#include "DataSanity.cpp"
#include "BSDApply.cpp"

//MyLib
#include <WGRecon.hpp>

#include <TString.h>
#include <TApplication.h>
#include <TCanvas.h>

using namespace std;

int main( int argc, char **argv )
{

  if(argc < 3)
    {
      cout << "usage" << '\n';
      cout << "WGDataSanity [srun][erun]" << '\n';
      exit(0);
    }

  int srun = std::atoi(argv[1]);
  int erun = std::atoi(argv[2]);

  //Set Parameters
  int sunix, eunix;
  float accumlated_pot=0;
  float recorded_pot=0;
  FileStat_t info;

  TString wgdirpath, wgfilename;
  wgdirpath.Form("./process/0-WGnocut");
  TChain* wgchain = new TChain("tree","tree");

  //Set Classes
  DataSanity *datasanity = new DataSanity();
  BSDApply* bsdapply = new BSDApply();
  BMBSD *bmbsd = new BMBSD();

  bsdapply->ReadBSDfile();

  for(int irun=srun; irun<=erun; irun++)
    {
      wgfilename.Form("%s/WGBSD_%d_dif0.root", wgdirpath.Data(),irun);
      if (gSystem->GetPathInfo(wgfilename.Data(), info)!=0)
	{
	  continue;
	}else{
	wgchain->Add(wgfilename);
      }
    }//irun

  wgchain->SetBranchAddress("BMBSD", &bmbsd);
  cout << "WAGASCI entries = " << wgchain->GetEntries() <<'\n';
  
  wgchain->GetEntry(0);
  sunix = bmbsd->unixtime;
  wgchain->GetEntry(wgchain->GetEntries()-1);
  eunix = bmbsd->unixtime;

  cout << "sunix= " << sunix << " eunix= " << eunix << '\n';

  TFile* fout = new TFile("./result/BSD/WGAccumlated_pot.root", "recreate");
  TH2F *bsd_accumlated_plot = new TH2F("bsd_accumlated_plot", "", 100, sunix, eunix, 100, 0, 30);
  TH2F *wg_accumlated_plot = new TH2F("wg_accumlated_plot", "", 100, sunix, eunix, 100, 0, 30);
  char ytitle[128] = "Accumlated P.O.T (10^{19})";
  datasanity->SetHistLabel(bsd_accumlated_plot, "Data Taking Efficiency", ytitle);
  datasanity->SetHistLabel(wg_accumlated_plot, "Data Taking Efficiency", ytitle);
  wg_accumlated_plot->SetMarkerColor(2);

  for(int ientry=0; ientry<wgchain->GetEntries(); ientry++)
    {
      wgchain->GetEntry(ientry);
      recorded_pot += bmbsd->pot/pow(10, 19);

      wg_accumlated_plot->Fill(bmbsd->unixtime, recorded_pot);
    }

  for(int ientry=0; ientry<bsdapply->bsdchain->GetEntries(); ientry++)
    {
      bsdapply->bsdchain->GetEntry(ientry);
      if(bsdapply->trg_sec[2]<sunix || bsdapply->trg_sec[2]>eunix) continue;
      accumlated_pot += bsdapply->ct_np[4][0]/pow(10, 19);
      bsd_accumlated_plot->Fill(bsdapply->trg_sec[2], accumlated_pot);
    }

  cout << "WG= " << recorded_pot << " BSD= " << accumlated_pot << '\n';
  cout << "Data Taking Efficiency= " << recorded_pot/accumlated_pot << '\n';

  fout->cd();
  bsd_accumlated_plot->Write();
  wg_accumlated_plot->Write();
  fout->Close();

  wgchain->Delete();
  bsdapply->KillAll();
  return 0;
  
}//main
