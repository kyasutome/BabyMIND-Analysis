#include <iostream>

using namespace std;

void make_plots_vertex()
{
  TCanvas *c1 = new TCanvas("c1", "c1", 1500, 500);
  c1->Divide(3, 1);
  TCanvas *c2 = new TCanvas("c2", "c2", 1500, 500);
  c2->Divide(3, 1);
  TCanvas *c3 = new TCanvas("c3", "c3", 1500, 500);
  c3->Divide(3, 1);

  TFile* fin = new TFile("${processdir}/result/DetPerform/vertex.root", "READ");
  TH1D* vertex[3][3];

  for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
      {
	vertex[i][j]=(TH1D*)fin->Get(Form("vertex_track%i_pos%d", i, j));
	vertex[i][j]->SetTitle("vertex;pos[mm];events");
      }

  for(int i=0; i<3; i++)
    {
      c1->cd(i+1);
      if(i==0)
	vertex[0][i]->Draw("");
      else
	vertex[0][i]->Draw("same");
    }

  for(int i=0; i<3; i++)
    {
      c2->cd(i+1);
      if(i==0)
	vertex[1][i]->Draw("");
      else
	vertex[1][i]->Draw("same");
    }

  for(int i=0; i<3; i++)
    {
      c3->cd(i+1);
      if(i==0)
	vertex[2][i]->Draw("");
      else
	vertex[2][i]->Draw("same");
    }

}
