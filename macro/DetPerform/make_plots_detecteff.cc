#include <iostream>

using namespace std;

void make_plots_detecteff()
{
  TCanvas *c1 = new TCanvas("c1", "c1", 1400, 1200);

  TFile *fin = new TFile("${processdir}/result/DetPerform/detecteff.root", "READ");
  TTree *tree = (TTree*)fin->Get("tree");

  double numerator_origin[2][19];
  tree->SetBranchAddress("numerator_origin",numerator_origin);
  double denomenator_origin[2][19];
  tree->SetBranchAddress("denomenator_origin",denomenator_origin);
  double numerator_yasu[2][2];
  tree->SetBranchAddress("numerator_yasu",numerator_yasu);
  double denomenator_yasu[2][2];
  tree->SetBranchAddress("denomenator_yasu",denomenator_yasu);

  double detecteff[2][16];
  double planeid[2][16];
  double yerr[2][16];
  double xerr[2][16];

  double detecteff_yasu[2][2];
  double planeid_yasu[2][2];
  double yerr_yasu[2][2];
  double xerr_yasu[2][2];
  double x, y, sum;

  tree->GetEntry(0);
  
  for(int iview=0; iview<2; iview++)
    for(int i=0; i<16; i++)
      {
	detecteff[iview][i] = numerator_origin[iview][i+2]/denomenator_origin[iview][i+2];
	planeid[iview][i] = i+2;
	xerr[iview][i] = 0.5;
	
	x = numerator_origin[iview][i+2];
	y = denomenator_origin[iview][i+2]-numerator_origin[iview][i+2];
	sum = denomenator_origin[iview][i+2]; 

	tree->GetEntry(0);
	
	yerr[iview][i] = sqrt(x*x+y*y)/(sum*sum);
	cout << "i= " << i << " planeid= " << planeid[iview][i]  << " detecteff[iview][i+2]= " << detecteff[iview][i+2] << '\n';
      }

  tree->GetEntry(0);

  for(int iview=0; iview<2; iview++)
    for(int i=0; i<2; i++)
      {
	detecteff_yasu[iview][i] = numerator_yasu[i][iview]/denomenator_yasu[i][iview];
	planeid_yasu[iview][i] = i+19;
	xerr_yasu[iview][i] = 0.5;

	x = numerator_origin[iview][i];
	y = denomenator_origin[iview][i]-numerator_origin[iview][i];
	sum = denomenator_origin[iview][i]; 

	yerr_yasu[iview][i] = sqrt(x*x+y*y)/(sum*sum);
      }

  cout << "after" << '\n';
  cout << detecteff_yasu[0][0] << " " << numerator_yasu[0][0] << " " << denomenator_yasu[0][0]  << '\n';
  cout << detecteff_yasu[0][1] << " " << numerator_yasu[1][0] << " " << denomenator_yasu[1][0]  << '\n';
  cout << detecteff_yasu[1][0] << " " << numerator_yasu[0][1] << " " << denomenator_yasu[0][1]  << '\n';
  cout << detecteff_yasu[1][1] << " " << numerator_yasu[1][1] << " " << denomenator_yasu[1][1]  << '\n';
  
  TGraphErrors* detecteff_side = new TGraphErrors(16, planeid[0], detecteff[0], xerr[0], yerr[0]);
  TGraphErrors* detecteff_top = new TGraphErrors(16, planeid[1], detecteff[1], xerr[1], yerr[1]);
  TGraphErrors* detecteff_yasu_right = new TGraphErrors(2, planeid_yasu[0], detecteff_yasu[0], xerr_yasu[0], yerr_yasu[0]);
  TGraphErrors* detecteff_yasu_left = new TGraphErrors(2, planeid_yasu[1], detecteff_yasu[1], xerr_yasu[1], yerr_yasu[1]);

  c1->cd();
  detecteff_side->Draw("AP");
  detecteff_side->SetMarkerStyle(21);
  detecteff_side->SetMarkerColor(4);
  detecteff_side->SetMinimum(0.9);
  detecteff_side->SetMaximum(1.0);
  detecteff_side->SetTitle("Detection Efficiency;Module ID;Efficiency");
  detecteff_side->GetXaxis()->SetLimits(0, 21);

  detecteff_top->Draw("P, same");
  detecteff_top->SetMarkerStyle(21);
  detecteff_top->SetMarkerColor(2);
  detecteff_top->SetMinimum(0.4);
  detecteff_top->SetTitle("Detection Efficiency (Top);Module ID;Efficiency");

  detecteff_yasu_right->Draw("P, same");
  detecteff_yasu_right->SetMarkerStyle(21);
  detecteff_yasu_right->SetMarkerColor(6);
  detecteff_yasu_right->SetMinimum(0.4);
  detecteff_yasu_right->SetTitle("Detection Efficiency (Top);Module ID;Efficiency");

  detecteff_yasu_left->Draw("P, same");
  detecteff_yasu_left->SetMarkerStyle(21);
  detecteff_yasu_left->SetMarkerColor(3);
  detecteff_yasu_left->SetMinimum(0.4);
  detecteff_yasu_left->SetTitle("Detection Efficiency (Top);Module ID;Efficiency");

  TLegend *legend = new TLegend(0.1, 0.1, 0.4, 0.4);
  legend->AddEntry(detecteff_side, "Hor.", "p");
  legend->AddEntry(detecteff_top, "Ver.", "p");
  legend->AddEntry(detecteff_yasu_right, "Yasu. Right", "p");
  legend->AddEntry(detecteff_yasu_left, "Yasu. Left", "p");
  legend->Draw("");
  
}
