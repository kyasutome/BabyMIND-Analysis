#include <iostream>

using namespace std;

void make_plots_pedist()
{
  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 600);
  
  TString filename;
  filename.Form("${processdir}/result/DetPerform/BM_pedist.root");
  TFile *fin = new TFile(filename, "READ");
  TTree *tree = (TTree*)fin->Get("tree");

  double pe_hor[18][96][2];
  tree->SetBranchAddress("pe_hor", pe_hor);
  double pe_ver[18][32];
  tree->SetBranchAddress("pe_ver", pe_ver);
  double pe_yasu[2][14];
  tree->SetBranchAddress("pe_yasu", pe_yasu);

  TH1D* pedist_hor = new TH1D("pedist_hor", "pedist_hor", 120, 0, 60);
  pedist_hor->SetFillColor(2);
  TH1D* pedist_ver = new TH1D("pedist_ver", "pedist_ver", 120, 0, 60);
  pedist_ver->SetFillColor(3);
  TH1D* pedist_yasu = new TH1D("pedist_yasu", "pedist_yasu", 120, 0, 60);
  pedist_yasu->SetFillColor(4);

  tree->GetEntry(0);

  for(int imod=0; imod<18; imod++)
    {
      for(int ihor=0; ihor<96; ihor++)
        for(int iread=0; iread<2; iread++)
          {
            pedist_hor->Fill(pe_hor[imod][ihor][iread]);
          }

      for(int iver=0; iver<32; iver++)
        {
	  pedist_ver->Fill(pe_ver[imod][iver]);
        }
    }

  for(int imod=0; imod<2; imod++)
    for(int iyasu=0; iyasu<14; iyasu++)
      {
	pedist_yasu->Fill(pe_yasu[imod][iyasu]);
      }
   
  THStack *pestack = new THStack("pestack","pestack");
  pestack->SetTitle("MPV distribution for all MPPC;MPV in Landau;N of channles");
  pestack->Add(pedist_hor);
  pestack->Add(pedist_ver);
  pestack->Add(pedist_yasu);

  c1->cd();
  pestack->Draw("");

  TLegend* l1 = new TLegend(0.7, 0.7, 0.9, 0.9);
  l1->AddEntry(pedist_hor, "horizontal","f");
  l1->AddEntry(pedist_ver, "Vertical","f");
  l1->AddEntry(pedist_yasu, "YASU","f");
  l1->Draw("");
  
}
