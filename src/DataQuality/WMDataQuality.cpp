#include <iostream>
#include <stdio.h>

//include
#include "WGChannelMap.cpp"
#include "WMDQCheck.cpp"

//library
#include "WGRecon.hpp"

#include "TApplication.h"
#include "TCanvas.h"


using namespace std;

int main( int argc, char **argv )
{
  if(argc < 2)
    {
      cout << "usage" << '\n';
      cout << "MakeWMClass [filepath]" << '\n';
      exit(0);
    }

  std::string name = string(argv[1]);
  TString filepath(name);
  TApplication theapp("theapp", 0, 0, 0, 0);

  TCanvas* c1 = new TCanvas("c1", "WM DQ Check", 1500, 1200);
  TPad *pad11 = new TPad("pad11","This is pad11",0.03,0.65,0.33,0.93);
  TPad *pad12 = new TPad("pad12","This is pad12",0.35,0.65,0.65,0.93);
  TPad *pad13 = new TPad("pad13","This is pad13",0.67,0.65,0.97,0.93);
  TPad *pad21 = new TPad("pad21","This is pad21",0.03,0.35,0.33,0.63);
  TPad *pad22 = new TPad("pad22","This is pad22",0.35,0.35,0.65,0.63);
  TPad *pad23 = new TPad("pad23","This is pad23",0.67,0.35,0.97,0.63);
  TPad *pad31 = new TPad("pad31","This is pad31",0.03,0.05,0.33,0.33);
  TPad *pad32 = new TPad("pad32","This is pad32",0.35,0.05,0.65,0.33);
  TPad *pad33 = new TPad("pad33","This is pad33",0.67,0.05,0.97,0.33);

  pad11->SetFillColor(11);
  pad12->SetFillColor(11);
  pad13->SetFillColor(11);
  pad21->SetFillColor(11);
  pad22->SetFillColor(11);
  pad23->SetFillColor(11);
  pad31->SetFillColor(11);
  pad32->SetFillColor(11);
  pad33->SetFillColor(11);

  pad11->Draw();
  pad12->Draw();
  pad13->Draw();
  pad21->Draw();
  pad22->Draw();
  pad23->Draw();
  pad31->Draw();
  pad32->Draw();
  pad33->Draw();

  
  TCanvas* c2 = new TCanvas("c2", "WM DQ Check Channel", 1500, 1200);
  TPad *pad211 = new TPad("pad211","This is pad211",0.03,0.65,0.33,0.93);
  TPad *pad212 = new TPad("pad212","This is pad212",0.35,0.65,0.65,0.93);
  TPad *pad213 = new TPad("pad213","This is pad213",0.67,0.65,0.97,0.93);
  TPad *pad221 = new TPad("pad221","This is pad221",0.03,0.35,0.33,0.63);
  TPad *pad222 = new TPad("pad222","This is pad222",0.35,0.35,0.65,0.63);
  TPad *pad223 = new TPad("pad223","This is pad223",0.67,0.35,0.97,0.63);
  TPad *pad231 = new TPad("pad231","This is pad231",0.03,0.05,0.33,0.33);
  TPad *pad232 = new TPad("pad232","This is pad232",0.35,0.05,0.65,0.33);
  TPad *pad233 = new TPad("pad233","This is pad233",0.67,0.05,0.97,0.33);

  pad211->SetFillColor(11);
  pad212->SetFillColor(11);
  pad213->SetFillColor(11);
  pad221->SetFillColor(11);
  pad222->SetFillColor(11);
  pad223->SetFillColor(11);
  pad231->SetFillColor(11);
  pad232->SetFillColor(11);
  pad233->SetFillColor(11);

  pad211->Draw();
  pad212->Draw();
  pad213->Draw();
  pad221->Draw();
  pad222->Draw();
  pad223->Draw();
  pad231->Draw();
  pad232->Draw();
  pad233->Draw();


  TCanvas* c3 = new TCanvas("c3", "WM DQ Check Channel", 1500, 1200);
  TPad *pad311 = new TPad("pad311","This is pad211",0.03,0.65,0.33,0.93);
  TPad *pad312 = new TPad("pad312","This is pad212",0.35,0.65,0.65,0.93);
  TPad *pad313 = new TPad("pad313","This is pad213",0.67,0.65,0.97,0.93);
  TPad *pad321 = new TPad("pad321","This is pad221",0.03,0.35,0.33,0.63);
  TPad *pad322 = new TPad("pad322","This is pad222",0.35,0.35,0.65,0.63);
  TPad *pad323 = new TPad("pad323","This is pad223",0.67,0.35,0.97,0.63);
  TPad *pad331 = new TPad("pad331","This is pad231",0.03,0.05,0.33,0.33);
  TPad *pad332 = new TPad("pad332","This is pad232",0.35,0.05,0.65,0.33);
  TPad *pad333 = new TPad("pad333","This is pad233",0.67,0.05,0.97,0.33);

  pad311->SetFillColor(11);
  pad312->SetFillColor(11);
  pad313->SetFillColor(11);
  pad321->SetFillColor(11);
  pad322->SetFillColor(11);
  pad323->SetFillColor(11);
  pad331->SetFillColor(11);
  pad332->SetFillColor(11);
  pad333->SetFillColor(11);

  pad311->Draw();
  pad312->Draw();
  pad313->Draw();
  pad321->Draw();
  pad322->Draw();
  pad323->Draw();
  pad331->Draw();
  pad332->Draw();
  pad333->Draw();


  TCanvas* c4 = new TCanvas("c4", "WM DQ Check Channel", 1500, 1200);
  TPad *pad411 = new TPad("pad411","This is pad211",0.03,0.65,0.33,0.93);
  TPad *pad412 = new TPad("pad412","This is pad212",0.35,0.65,0.65,0.93);
  TPad *pad413 = new TPad("pad413","This is pad213",0.67,0.65,0.97,0.93);
  TPad *pad421 = new TPad("pad421","This is pad221",0.03,0.35,0.33,0.63);
  TPad *pad422 = new TPad("pad422","This is pad222",0.35,0.35,0.65,0.63);
  TPad *pad423 = new TPad("pad423","This is pad223",0.67,0.35,0.97,0.63);
  TPad *pad431 = new TPad("pad431","This is pad231",0.03,0.05,0.33,0.33);
  TPad *pad432 = new TPad("pad432","This is pad232",0.35,0.05,0.65,0.33);
  TPad *pad433 = new TPad("pad433","This is pad233",0.67,0.05,0.97,0.33);

  pad411->SetFillColor(11);
  pad412->SetFillColor(11);
  pad413->SetFillColor(11);
  pad421->SetFillColor(11);
  pad422->SetFillColor(11);
  pad423->SetFillColor(11);
  pad431->SetFillColor(11);
  pad432->SetFillColor(11);
  pad433->SetFillColor(11);

  pad411->Draw();
  pad412->Draw();
  pad413->Draw();
  pad421->Draw();
  pad422->Draw();
  pad423->Draw();
  pad431->Draw();
  pad432->Draw();
  pad433->Draw();

  TCanvas* c5 = new TCanvas("c5", "WM DQ Check Channel", 1500, 1200);
  TPad *pad511 = new TPad("pad511","This is pad211",0.03,0.65,0.33,0.93);
  TPad *pad512 = new TPad("pad512","This is pad212",0.35,0.65,0.65,0.93);
  TPad *pad513 = new TPad("pad513","This is pad213",0.67,0.65,0.97,0.93);
  TPad *pad521 = new TPad("pad521","This is pad221",0.03,0.35,0.33,0.63);
  TPad *pad522 = new TPad("pad522","This is pad222",0.35,0.35,0.65,0.63);
  TPad *pad523 = new TPad("pad523","This is pad223",0.67,0.35,0.97,0.63);
  TPad *pad531 = new TPad("pad531","This is pad231",0.03,0.05,0.33,0.33);
  TPad *pad532 = new TPad("pad532","This is pad232",0.35,0.05,0.65,0.33);
  TPad *pad533 = new TPad("pad533","This is pad233",0.67,0.05,0.97,0.33);

  TCanvas* c6 = new TCanvas("c6", "WM DQ Check Channel", 1500, 1200);

  pad511->SetFillColor(11);
  pad512->SetFillColor(11);
  pad513->SetFillColor(11);
  pad521->SetFillColor(11);
  pad522->SetFillColor(11);
  pad523->SetFillColor(11);
  pad531->SetFillColor(11);
  pad532->SetFillColor(11);
  pad533->SetFillColor(11);

  pad511->Draw();
  pad512->Draw();
  pad513->Draw();
  pad521->Draw();
  pad522->Draw();
  pad523->Draw();
  pad531->Draw();
  pad532->Draw();
  pad533->Draw();
  

  /*
  TCanvas* c3 = new TCanvas("c3", "WM DQ Check Channel", 1500, 1200);
  TPad *pad311 = new TPad("pad311","This is pad211",0.03,0.65,0.33,0.93);
  TPad *pad312 = new TPad("pad312","This is pad212",0.35,0.65,0.65,0.93);
  TPad *pad313 = new TPad("pad313","This is pad213",0.67,0.65,0.97,0.93);
  TPad *pad321 = new TPad("pad321","This is pad221",0.03,0.35,0.33,0.63);
  TPad *pad322 = new TPad("pad322","This is pad222",0.35,0.35,0.65,0.63);
  TPad *pad323 = new TPad("pad323","This is pad223",0.67,0.35,0.97,0.63);
  TPad *pad331 = new TPad("pad331","This is pad231",0.03,0.05,0.33,0.33);
  TPad *pad332 = new TPad("pad332","This is pad232",0.35,0.05,0.65,0.33);
  TPad *pad333 = new TPad("pad333","This is pad233",0.67,0.05,0.97,0.33);

  pad311->SetFillColor(11);
  pad312->SetFillColor(11);
  pad313->SetFillColor(11);
  pad321->SetFillColor(11);
  pad322->SetFillColor(11);
  pad323->SetFillColor(11);
  pad331->SetFillColor(11);
  pad332->SetFillColor(11);
  pad333->SetFillColor(11);

  pad311->Draw();
  pad312->Draw();
  pad313->Draw();
  pad321->Draw();
  pad322->Draw();
  pad323->Draw();
  pad331->Draw();
  pad332->Draw();
  pad333->Draw();
  */

  //WGChannelMap *wgchannelmap = new WGChannelMap();
  WMDQCheck *wmdqcheck = new WMDQCheck();
  WMDQData *wmdqdata = new WMDQData();
  
  TFile *fout = new TFile(Form("${processdir}/process/8-WMDQCHECK/WMDQCHECK.root"), "recreate");
  TTree *otree = new TTree("tree","tree");
  otree->Branch("WMDQData","WMDQData",&wmdqdata,32000,2);

  int DIF=0;
  int ID=0;

  //TEST CODES
  wmdqcheck->ReadTree(filepath, DIF);
  for(int ientry=0; ientry<wmdqcheck->GetTEntry(DIF); ientry++)
  //for(int ientry=0; ientry<5000; ientry++)
    {
      //cout << "ientry=" << ientry << '\n';
      wmdqdata->Clear();
      if(wmdqcheck->SignalCreation(ientry, DIF, wmdqdata))
	otree->Fill();
    }

  fout->cd();
  otree->Write();
  fout->Close();


  c1->cd();  
  pad11->cd();
  wmdqcheck->bcid_hist[DIF][0]->Draw("");
  pad12->cd();
  wmdqcheck->bcid_hist[DIF][1]->Draw("");
  pad13->cd();
  wmdqcheck->bcid_hist[DIF][2]->Draw("");

  pad21->cd();
  wmdqcheck->channel_adc_nohit[DIF][0]->Draw("colz");
  pad22->cd();
  wmdqcheck->channel_adc_nohit[DIF][1]->Draw("colz");
  pad23->cd();
  wmdqcheck->channel_adc_nohit[DIF][2]->Draw("colz");

  pad31->cd();
  wmdqcheck->channel_adc_hit[DIF][0]->Draw("colz");
  pad32->cd();
  wmdqcheck->channel_adc_hit[DIF][1]->Draw("colz");
  pad33->cd();
  wmdqcheck->channel_adc_hit[DIF][2]->Draw("colz");
  c1->Update();

  
  c2->cd();  
  pad211->cd();
  wmdqcheck->charge_hist[DIF][ID][0]->Draw("");
  pad212->cd();
  wmdqcheck->charge_hist[DIF][ID][1]->Draw("");
  pad213->cd();
  wmdqcheck->charge_hist[DIF][ID][2]->Draw("");
  pad221->cd();
  wmdqcheck->charge_hist[DIF][ID][3]->Draw("");
  pad222->cd();
  wmdqcheck->charge_hist[DIF][ID][4]->Draw("");
  pad223->cd();
  wmdqcheck->charge_hist[DIF][ID][5]->Draw("");
  pad231->cd();
  wmdqcheck->charge_hist[DIF][ID][6]->Draw("");
  pad232->cd();
  wmdqcheck->charge_hist[DIF][ID][7]->Draw("");
  pad233->cd();
  wmdqcheck->charge_hist[DIF][ID][8]->Draw("");
  c2->Update();

  c3->cd();  
  pad311->cd();
  wmdqcheck->charge_hist[DIF][ID][9]->Draw("");
  pad312->cd();
  wmdqcheck->charge_hist[DIF][ID][10]->Draw("");
  pad313->cd();
  wmdqcheck->charge_hist[DIF][ID][11]->Draw("");
  pad321->cd();
  wmdqcheck->charge_hist[DIF][ID][12]->Draw("");
  pad322->cd();
  wmdqcheck->charge_hist[DIF][ID][13]->Draw("");
  pad323->cd();
  wmdqcheck->charge_hist[DIF][ID][14]->Draw("");
  pad331->cd();
  wmdqcheck->charge_hist[DIF][ID][15]->Draw("");
  pad332->cd();
  wmdqcheck->charge_hist[DIF][ID][16]->Draw("");
  pad333->cd();
  wmdqcheck->charge_hist[DIF][ID][17]->Draw("");
  c3->Update();

  c4->cd();  
  pad411->cd();
  wmdqcheck->charge_hist[DIF][ID][18]->Draw("");
  pad412->cd();
  wmdqcheck->charge_hist[DIF][ID][19]->Draw("");
  pad413->cd();
  wmdqcheck->charge_hist[DIF][ID][20]->Draw("");
  pad421->cd();
  wmdqcheck->charge_hist[DIF][ID][21]->Draw("");
  pad422->cd();
  wmdqcheck->charge_hist[DIF][ID][22]->Draw("");
  pad423->cd();
  wmdqcheck->charge_hist[DIF][ID][23]->Draw("");
  pad431->cd();
  wmdqcheck->charge_hist[DIF][ID][24]->Draw("");
  pad432->cd();
  wmdqcheck->charge_hist[DIF][ID][25]->Draw("");
  pad433->cd();
  wmdqcheck->charge_hist[DIF][ID][26]->Draw("");
  c4->Update();

  c5->cd();  
  pad511->cd();
  wmdqcheck->charge_hist[DIF][ID][27]->Draw("");
  pad512->cd();
  wmdqcheck->charge_hist[DIF][ID][28]->Draw("");
  pad513->cd();
  wmdqcheck->charge_hist[DIF][ID][29]->Draw("");
  pad521->cd();
  wmdqcheck->charge_hist[DIF][ID][30]->Draw("");
  pad522->cd();
  //wmdqcheck->charge_hist[DIF][ID][22]->Draw("");
  pad523->cd();
  //wmdqcheck->charge_hist[DIF][ID][23]->Draw("");
  pad531->cd();
  //wmdqcheck->charge_hist[DIF][ID][24]->Draw("");
  pad532->cd();
  //wmdqcheck->charge_hist[DIF][ID][25]->Draw("");
  pad533->cd();
  //wmdqcheck->charge_hist[DIF][ID][26]->Draw("");
  c5->Update();
  

  theapp.Run();
  return 0;
}
