#include <iostream>

using namespace std;

void make_plots_pmureso()
{
  TCanvas *c1 = new TCanvas("c1", "c1", 1400, 1200);

  TFile *fin = new TFile("${processdir}/result/DetPerform/pmureso.root", "READ");
  TTree *tree = (TTree*)fin->Get("tree");

  TH1D* pmureso[2];

  pmureso[0] = (TH1D*)fin->Get("pmuresolution_c");
  pmureso[1] = (TH1D*)fin->Get("pmuresolution_r");

  c1->cd();  
  pmureso[0]->Draw("");
  pmureso[0]->SetTitle("P_{#mu} Resolution;Recon-True (MeV/c); events");
  pmureso[0]->SetLineColor(2);
  pmureso[0]->SetLineWidth(2);
  pmureso[0]->SetStats(0);
  pmureso[0]->SetMaximum(35);
  pmureso[0]->GetXaxis()->SetLimits(-1000, 1000);
  pmureso[1]->Draw("same");
  pmureso[1]->SetLineColor(4);
  pmureso[1]->SetLineWidth(2);
  
  TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
  legend->AddEntry(pmureso[0], "Curvature", "l");
  legend->AddEntry(pmureso[1], "Range", "l");
  legend->Draw("");
  
  
}
