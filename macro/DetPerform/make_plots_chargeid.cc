#include <iostream>

using namespace std;

void make_plots_chargeid()
{
  TCanvas *c1 = new TCanvas("c1", "c1", 1400, 1200);

  TFile *fin = new TFile("${processdir}/result/DetPerform/chargeid.root", "READ");
  TTree *tree = (TTree*)fin->Get("tree");

  double numerator_pmu[15];
  tree->SetBranchAddress("numerator_pmu",numerator_pmu);
  double denomenator_pmu[15];
  tree->SetBranchAddress("denomenator_pmu",denomenator_pmu);

  double charge[15];
  double planeid[15];
  double yerr[15];
  double xerr[15];
  double x, y, sum;

  tree->GetEntry(0);
  
    for(int i=0; i<15; i++)
      {
	cout << numerator_pmu[i] << " " << denomenator_pmu[i] << '\n';
	charge[i] = numerator_pmu[i]/denomenator_pmu[i];
	planeid[i] = 100+i*200;
	
	x = numerator_pmu[i];
	y = denomenator_pmu[i]-numerator_pmu[i];
	sum = denomenator_pmu[i]; 
	
	xerr[i] = 100;
	yerr[i] = sqrt(x*x+y*y)/(sum*sum);
      }
  
  TGraphErrors* chargeeff = new TGraphErrors(15, planeid, charge, xerr, yerr);

  c1->cd();
  chargeeff->Draw("AP");
  chargeeff->SetMarkerStyle(21);
  chargeeff->SetMarkerColor(4);
  chargeeff->SetMinimum(0.4);
  chargeeff->SetMaximum(1.0);
  chargeeff->SetTitle("Charge ID Efficiency;P_{#mu} (MeV/c);Efficiency");
  chargeeff->GetXaxis()->SetLimits(0, 3000);
  
}
