#include <iostream>

using namespace std;

void make_plots_eventtiming()
{
  TCanvas *canvas[7];
  TString filename;
  filename.Form("${processdir}/result/DetPerform/eventtiming.root");
  TFile *fin = new TFile(filename, "READ");
  TH1D *hist_eventtiming[7];
  TString histname;
  TString canvasname;

  TLegend *legend[7];
  TString modname[7] = {"Proton Module", "Upstream WAGASCI", "Downstream WAGASCI", "North WallMRD",
			"South WallMRD", "Baby MIND", "YASU"};

  for(int imod=0; imod<7; imod++)
    {
      canvasname.Form("canvas%d", imod);
      canvas[imod] = new TCanvas(canvasname, canvasname, 1000, 1000);
      histname.Form("hist_eventtiming_mod%d", imod);
      hist_eventtiming[imod] = (TH1D*)fin->Get(histname);
      hist_eventtiming[imod]->SetTitle(";Time(ns);Nhits");      
      hist_eventtiming[imod]->SetFillColor(4);
      hist_eventtiming[imod]->SetStats(0);
    }
 
  for(int imod=0; imod<7; imod++)
    {
      legend[imod] = new TLegend(0.6, 0.8, 0.9, 0.9);
      legend[imod]->AddEntry(hist_eventtiming[imod], modname[imod],"f");
      canvas[imod]->cd();
      //canvas[imod]->SetLogy();
      hist_eventtiming[imod]->Draw("");      
      legend[imod]->Draw("");
    }
  
}
