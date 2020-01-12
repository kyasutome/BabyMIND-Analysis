#include <iostream>
#include <fstream>

using namespace std;
void make_gain_plots()
{
  ifstream fin("./data/yasugain.txt");
  double yasugain[4][7];
  for(int idata=0; idata<7; idata++)
    fin >> yasugain[0][idata] >> yasugain[1][idata] >> yasugain[2][idata] >> yasugain[3][idata];

  THStack *gainstack = new THStack("gainstack", "Gain (YASU)");
  TH1D* yasugainplot[4];
  TString histname;
  
  for(int ihist=0; ihist<4; ihist++)
    {
      histname.Form("yasugainplot_%d", ihist);
      yasugainplot[ihist] = new TH1D(histname, histname, 10, 30, 40);
      yasugainplot[ihist]->SetFillColor(ihist+2);

      for(int idata=0; idata<7; idata++)
	yasugainplot[ihist]->Fill(yasugain[ihist][idata]);

      gainstack->Add(yasugainplot[ihist]);
    }

  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 600);
  c1->cd();
  gainstack->Draw("");

  TLegend *legend = new TLegend(0.60, 0.60, 0.90, 0.90);
  legend->AddEntry(yasugainplot[0], "Left Upstream (7)", "f");
  legend->AddEntry(yasugainplot[1], "Left Downstream (7)", "f");
  legend->AddEntry(yasugainplot[2], "Right Upstream (7)", "f");
  legend->AddEntry(yasugainplot[3], "Right Downpstream (7)", "f");
  legend->Draw("");
}
