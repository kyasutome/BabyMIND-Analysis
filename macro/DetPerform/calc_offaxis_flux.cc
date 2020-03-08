#include <iostream>
#include <fstream>

using namespace std;

void calc_offaxis_flux()
{
  TString filedir;
  filedir.Form("/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/fluxfile");
  TString filename;

  double Sum[2];
  TChain* fluxchain = new TChain("h3002", "h3002");
 
  TH1D *fluxhist[2];     

  for(int ifile=1; ifile<2; ifile++)
    {
      fluxchain->Add(Form("%s/fluka_flux_run_*.root",filedir.Data()));
      int idfd;
      fluxchain->SetBranchAddress("idfd", &idfd);
      float Enu;
      fluxchain->SetBranchAddress("Enu", &Enu);
      float norm;
      fluxchain->SetBranchAddress("norm", &norm);
      
      cout << fluxchain->GetEntries() << '\n';
      fluxhist[0] = new TH1D("northflux", "", 100, 0, 5); 
      fluxhist[0]->SetLineColor(2);
      fluxhist[0]->SetStats(0);
      fluxhist[0]->SetTitle("Flux Difference;Enu (GeV);arbitrary unit");
      fluxhist[1] = new TH1D("southflux", "", 100, 0, 5); 
      fluxhist[1]->SetLineColor(4);
      
      double evtweight;
      
      for(int ientry=0; ientry<fluxchain->GetEntries(); ientry++)
	{
	  fluxchain->GetEntry(ientry);
	  if(idfd==8)
	    {
	      evtweight = norm;
	      fluxhist[0]->Fill(Enu, evtweight);
	    }
	  
	  if(idfd==9)
	    {
	      evtweight = norm;
	      fluxhist[1]->Fill(Enu, evtweight);
	    }
	}
    }

  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 500);
  c1->Draw();
  fluxhist[0]->Draw("hist");
  fluxhist[1]->Draw("hist, same");

  TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
  legend->AddEntry(fluxhist[0], "north (1.7 degree)", "l");
  legend->AddEntry(fluxhist[1], "south (1.3 degree)", "l");
  legend->Draw("");
  

  Sum[0] = fluxhist[0]->Integral();
  Sum[1] = fluxhist[1]->Integral();

  cout << "Sum[0]= " << Sum[0] << " Sum[1]= " << Sum[1] << '\n';
  cout << "Ratio= " << Sum[1]/Sum[0] << '\n';
}
