#include <iostream>

using namespace std;

void make_plots_chargeid_dist()
{
  TCanvas *c1 = new TCanvas("c1", "c1", 1400, 1200);

  TH1D *chidist[2];
  int colormap[2] = {4, 2};
  for(int i=0; i<2; i++)
    {
      //chidist[i] = new TH1D(Form("chidist_%d", i), "", 100, -1, 1);
      chidist[i] = new TH1D(Form("chidist_%d", i), "", 200, -1, 1);
      chidist[i]->SetFillColor(colormap[i]);
      chidist[i]->SetStats(0);
    }

  const int Nnu = 3;
  const int Nanti = 1;
  TFile *fin_nu[Nnu];
  TTree *tree_nu[Nnu];
  TFile *fin_anti[Nanti];
  TTree *tree_anti[Nanti];

  double weight_nu[Nnu];
  int mutype_nu[Nnu];
  double chi2_nu[Nnu][2];
  double Pmu_nu[Nnu];

  double Asymchi;

  for(int i=1; i<=Nnu; i++)
    {
      fin_nu[i] = new TFile(Form("${processdir}/result/DetPerform/chargeid_nu_%d.root", i), "READ");
      tree_nu[i] = (TTree*)fin_nu[i]->Get("ctree");
      tree_nu[i]->SetBranchAddress("weight", &weight_nu[i]);
      tree_nu[i]->SetBranchAddress("mutype", &mutype_nu[i]);
      tree_nu[i]->SetBranchAddress("chi2", chi2_nu[i]);
      tree_nu[i]->SetBranchAddress("Pmu", &Pmu_nu[i]);

      for(int ientry=0; ientry<tree_nu[i]->GetEntries(); ientry++)
	{
	  tree_nu[i]->GetEntry(ientry);
	  Asymchi = (1/chi2_nu[i][1]-1/chi2_nu[i][0])/(1/chi2_nu[i][1]+1/chi2_nu[i][0]);
	  chidist[0]->Fill(Asymchi, weight_nu[i]);
	}
    }
  

  double weight_anti[Nanti];
  int mutype_anti[Nanti];
  double chi2_anti[Nanti][2];
  double Pmu_anti[Nanti];
  for(int i=1; i<=Nanti; i++)
    {
      fin_anti[i] = new TFile(Form("${processdir}/result/DetPerform/chargeid_anti_%d.root", i), "READ");
      tree_anti[i] = (TTree*)fin_anti[i]->Get("ctree");
      tree_anti[i]->SetBranchAddress("weight", &weight_anti[i]);
      tree_anti[i]->SetBranchAddress("mutype", &mutype_anti[i]);
      tree_anti[i]->SetBranchAddress("chi2", chi2_anti[i]);
      tree_anti[i]->SetBranchAddress("Pmu", &Pmu_anti[i]);

      for(int ientry=0; ientry<tree_anti[i]->GetEntries(); ientry++)
	{
	  tree_anti[i]->GetEntry(ientry);
	  //Asymchi = (1/chi2_anti[i][1]-1/chi2_anti[i][0])/(1/chi2_anti[i][1]+1/chi2_anti[i][0]);
	  Asymchi = (1/chi2_anti[i][1]-1/chi2_anti[i][0]);
	  chidist[1]->Fill(Asymchi, weight_anti[i]);
	}
    }
  
  c1->cd();
  chidist[0]->Draw("hist");
  chidist[0]->SetTitle("Purity;#frac{1}{#chi(#mu^{+})}-#frac{1}{#chi(#mu^{-})};events");
  chidist[0]->GetXaxis()->SetTitleSize(0.03);
  chidist[0]->GetXaxis()->SetTitleOffset(1.3);
  chidist[0]->SetMaximum(1200);
  chidist[1]->Draw("same,hist");

  double muplus = 0;
  double muminus = 0;
  for(int i=1; i<200; i++)
    {
      if(i<=100)
	{
	  muplus += chidist[1]->GetBinContent(i);
	  muminus += chidist[0]->GetBinContent(i);
	}
    }

  cout << muminus << "/" << muplus+muminus << "=" << muminus/(double)(muplus+muminus) << '\n';

  TLegend* legend = new TLegend(0.7, 0.8, 0.9, 0.9);
  legend->AddEntry(chidist[0], "#nu_{#mu} MC", "f");
  legend->AddEntry(chidist[1], "#bar{#nu}_{#mu} MC", "f");
  legend->SetFillStyle(0);
  legend->Draw("");
  
}
