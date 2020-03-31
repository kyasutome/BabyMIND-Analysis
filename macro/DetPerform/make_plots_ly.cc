#include <iostream>

using namespace std;

void make_plots_ly()
{
  TCanvas *c1 = new TCanvas("c1", "c1", 1400, 1200);
  
  TString filename;
  filename.Form("${processdir}/result/DetPerform/lightyield.root");
  TFile *fin = new TFile(filename, "READ");

  TH1D* pehorr_total = (TH1D*)fin->Get("pehorr_total");
  TH1D* pehorl_total = (TH1D*)fin->Get("pehorl_total");
  TH1D* pehor_total = (TH1D*)fin->Get("pehor_total");
  TH1D* pever_total = (TH1D*)fin->Get("pever_total");
  TH1D* peyasu_total = (TH1D*)fin->Get("peyasu_total"); 

  double scalefactor[5];
  
  c1->cd();
  pehorr_total->Draw("");
  pehorr_total->SetLineColor(2);
  pehorr_total->SetTitle("Light Yield for MIP;Light Yield(p.e.); events");
  //pehorr_total->SetTitle("Horizontal Modules Right;Light Yield(p.e.); events");
  pehorr_total->SetMaximum(9000);
  pehorr_total->SetStats(0);

  pehorl_total->Draw("same, hist");
  pehorl_total->SetLineColor(4);
  pehorl_total->SetTitle("Horizontal Modules Left;Light Yield(p.e.); events");
  scalefactor[0] = pehorr_total->Integral()/pehorl_total->Integral();
  pehorl_total->Scale(scalefactor[0]);

  pehor_total->Draw("same, hist");
  pehor_total->SetLineColor(6);
  pehor_total->SetTitle("Horizontal Modules Right+Left;Light Yield(p.e.); events");
  scalefactor[1] = pehorr_total->Integral()/pehor_total->Integral();
  pehor_total->Scale(scalefactor[1]);

  pever_total->Draw("same, hist");
  pever_total->SetLineColor(3);
  pever_total->SetTitle("Vertical Modules;Light Yield(p.e.); events");
  scalefactor[2] = pehorr_total->Integral()/pever_total->Integral();
  pever_total->Scale(scalefactor[2]);

  peyasu_total->Draw("same, hist");
  peyasu_total->SetLineColor(7);
  peyasu_total->SetTitle("YASU Modules;Light Yield(p.e.); events");
  scalefactor[3] = pehorr_total->Integral()/peyasu_total->Integral();
  peyasu_total->Scale(scalefactor[3]);

  TLegend *legend = new TLegend(0.6, 0.6, 0.9, 0.9);
  legend->AddEntry(pehorr_total, "Hor. Right","l");
  legend->AddEntry(pehorl_total, "Hor. Left","l");
  legend->AddEntry(pehor_total, "Hor. Right+Left","l");
  legend->AddEntry(pever_total, "Ver. Top or Bottom","l");
  legend->AddEntry(peyasu_total, "YASU.","l");
  legend->SetFillStyle(0);
  legend->Draw("");
  
}
