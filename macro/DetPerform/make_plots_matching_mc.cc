#include <iostream>

using namespace std;

void make_plots_matching_mc()
{
  TCanvas *c1 = new TCanvas("c1", "c1", 1400, 1200);

  TFile *fin = new TFile("${processdir}/result/DetPerform/trackmatching_mc.root", "READ");
  TTree *tree = (TTree*)fin->Get("tree");

  double numerator[10];
  tree->SetBranchAddress("numerator",numerator);
  double denomenator[10];
  tree->SetBranchAddress("denomenator",denomenator);

  double detect[10];
  double planeid[10];
  double yerr[10];
  double xerr[10];
  double x, y, sum;

  tree->GetEntry(0);
  
    for(int i=0; i<10; i++)
      {
	detect[i] = numerator[i]/denomenator[i];
	planeid[i] = 0.05+i*0.1;
	
	x = numerator[i];
	y = denomenator[i]-numerator[i];
	sum = denomenator[i]; 
	
	xerr[i] = 0.05;
	yerr[i] = sqrt(x*x+y*y)/(sum*sum);
      }
  
  TGraphErrors* detecteff = new TGraphErrors(10, planeid, detect, xerr, yerr);

  c1->cd();
  detecteff->Draw("AP");
  detecteff->SetMarkerStyle(21);
  detecteff->SetMarkerColor(4);
  detecteff->SetMinimum(0.9);
  detecteff->SetMaximum(1.0);
  detecteff->SetTitle("Track Matching Efficiency;cos#theta;Efficiency");
  detecteff->GetXaxis()->SetLimits(0, 1);

  /*
  TLegend *legend = new TLegend(0.1, 0.1, 0.4, 0.4);
  legend->AddEntry(detecteff_side, "Hor.", "p");
  legend->AddEntry(detecteff_top, "Ver.", "p");
  legend->AddEntry(detecteff_yasu_right, "Yasu. Right", "p");
  legend->AddEntry(detecteff_yasu_left, "Yasu. Left", "p");
  legend->Draw("");
  */
  
}
