#include <iostream>

using namespace std;

void check_pedist_dif()
{
  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 600);
  TCanvas *c2 = new TCanvas("c2", "c2", 1000, 600);
  TCanvas *c3 = new TCanvas("c3", "c3", 1000, 600);
  
  TString filename;
  TFile *fin[2];
  TTree *tree[2];

  TH1D *adcdist_hor_left_total[2];
  TH1D *adcdist_hor_right_total[2];
  TH1D *adcdist_ver_total[2];

  for(int i=0; i<2; i++)
    {      
      if(i==0)
	filename.Form("${processdir}/result/DetPerform/BM_pedist_Jan_30_31.root");
      if(i==1)
	filename.Form("${processdir}/result/DetPerform/BM_pedist_Feb_1_2.root");
      fin[i] = new TFile(filename, "READ");
      tree[i] = (TTree*)fin[i]->Get("tree");
      adcdist_hor_left_total[i] = (TH1D*)fin[i]->Get("adcdist_hor_left_total");
      adcdist_hor_left_total[i]->SetLineColor(i+2);
      adcdist_hor_left_total[i]->SetStats(0);
      adcdist_hor_right_total[i] = (TH1D*)fin[i]->Get("adcdist_hor_right_total");
      adcdist_hor_right_total[i]->SetLineColor(i+2);
      adcdist_hor_right_total[i]->SetStats(0);
      adcdist_ver_total[i] = (TH1D*)fin[i]->Get("adcdist_ver_total");
      adcdist_ver_total[i]->SetLineColor(i+2);
      adcdist_ver_total[i]->SetStats(0);
    }

  adcdist_hor_left_total[0]->SetTitle("Horizontal bars Left;High Gain(ADC);events");
  adcdist_hor_right_total[0]->SetTitle("Horizontal bars Right;High Gain(ADC);events");
  adcdist_ver_total[0]->SetTitle("Vertical bars;High Gain(ADC);events");

  /*
  double pe_hor[18][96][2];
  tree[0]->SetBranchAddress("pe_hor", pe_hor);
  double pe_ver[18][32];
  tree[0]->SetBranchAddress("pe_ver", pe_ver);
  double pe_yasu[2][14];
  tree[0]->SetBranchAddress("pe_yasu", pe_yasu);
  TH1D* pedist_hor = new TH1D("pedist_hor", "pedist_hor", 120, 0, 60);
  pedist_hor->SetFillColor(2);
  TH1D* pedist_ver = new TH1D("pedist_ver", "pedist_ver", 120, 0, 60);
  pedist_ver->SetFillColor(3);
  TH1D* pedist_yasu = new TH1D("pedist_yasu", "pedist_yasu", 120, 0, 60);
  pedist_yasu->SetFillColor(4);
  */

  c1->cd();
  adcdist_hor_left_total[0]->Draw("");
  adcdist_hor_left_total[1]->Draw("same");
  TLegend* l1 = new TLegend(0.7, 0.7, 0.9, 0.9);
  l1->AddEntry(adcdist_hor_left_total[0], "30th, 31th. Jan","l");
  l1->AddEntry(adcdist_hor_left_total[1], "1st, 2nd. Feb","l");
  l1->Draw("");

  c2->cd();
  adcdist_hor_right_total[0]->Draw("");
  adcdist_hor_right_total[1]->Draw("same");
  TLegend* l2 = new TLegend(0.7, 0.7, 0.9, 0.9);
  l2->AddEntry(adcdist_hor_right_total[0], "30th, 31th. Jan","l");
  l2->AddEntry(adcdist_hor_right_total[1], "1st, 2nd. Feb","l");
  l2->Draw("");

  c3->cd();
  adcdist_ver_total[0]->Draw("");
  adcdist_ver_total[1]->Draw("same");
  TLegend* l3 = new TLegend(0.7, 0.7, 0.9, 0.9);
  l3->AddEntry(adcdist_ver_total[0], "30th, 31th. Jan","l");
  l3->AddEntry(adcdist_ver_total[1], "1st, 2nd. Feb","l");
  l3->Draw("");

  
}
