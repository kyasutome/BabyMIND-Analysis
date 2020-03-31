#include <iostream>
#include <stdio.h>

#include "TGraph.h"
#include "TGraphErrors.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"

//include
#include "easyrecon.cpp"
#include "wallmrd.cpp"
#include "BSDApply.cpp"
#include "BabyMIND.cpp"
#include "tracking.cpp"

//library
#include "EVTCluster.hpp"
#include "DetRecon.hpp"

using namespace std;

//#define finer
#define normal

int main( int argc, char **argv )
{

  TApplication app("app", 0, 0, 0, 0);
  TCanvas *c1 = new TCanvas("c1", "c1", 1800, 700);
  TCanvas *c2 = new TCanvas("c2", "c2", 1800, 700);

  TH1D* hist_evtrate;
  TGraphErrors* graph_evtrate[7];
  TGraphErrors* graph_evtrate_nu[7];

  //int startdate = 25;
  TString histname;
  histname.Form("evtrate");

  int num = 0;

  #ifdef finer
  num = 32;
  hist_evtrate= new TH1D(histname, "", num, 0, num);  
  hist_evtrate->GetXaxis()->SetBinLabel(1,"1/25");
  hist_evtrate->GetXaxis()->SetBinLabel(2,"1/26");
  hist_evtrate->GetXaxis()->SetBinLabel(3,"1/26");
  hist_evtrate->GetXaxis()->SetBinLabel(4,"1/26");
  hist_evtrate->GetXaxis()->SetBinLabel(5,"1/26");
  hist_evtrate->GetXaxis()->SetBinLabel(6,"1/27");
  hist_evtrate->GetXaxis()->SetBinLabel(7,"1/27");
  hist_evtrate->GetXaxis()->SetBinLabel(8,"1/27");
  hist_evtrate->GetXaxis()->SetBinLabel(9,"1/27");
  hist_evtrate->GetXaxis()->SetBinLabel(10,"1/28");
  hist_evtrate->GetXaxis()->SetBinLabel(11,"1/28");
  hist_evtrate->GetXaxis()->SetBinLabel(12,"1/28");
  hist_evtrate->GetXaxis()->SetBinLabel(13,"1/28");
  hist_evtrate->GetXaxis()->SetBinLabel(14,"1/29");
  hist_evtrate->GetXaxis()->SetBinLabel(15,"1/29");
  hist_evtrate->GetXaxis()->SetBinLabel(16,"1/30");
  hist_evtrate->GetXaxis()->SetBinLabel(17,"1/30");
  hist_evtrate->GetXaxis()->SetBinLabel(18,"1/30");
  hist_evtrate->GetXaxis()->SetBinLabel(19,"1/30");
  hist_evtrate->GetXaxis()->SetBinLabel(20,"1/31");
  hist_evtrate->GetXaxis()->SetBinLabel(21,"1/31");
  hist_evtrate->GetXaxis()->SetBinLabel(22,"1/31");
  hist_evtrate->GetXaxis()->SetBinLabel(23,"1/31");
  hist_evtrate->GetXaxis()->SetBinLabel(24,"2/1");
  hist_evtrate->GetXaxis()->SetBinLabel(25,"2/1");
  hist_evtrate->GetXaxis()->SetBinLabel(26,"2/1");
  hist_evtrate->GetXaxis()->SetBinLabel(27,"2/1");
  hist_evtrate->GetXaxis()->SetBinLabel(28,"2/2");
  hist_evtrate->GetXaxis()->SetBinLabel(29,"2/2");
  hist_evtrate->GetXaxis()->SetBinLabel(30,"2/2");
  hist_evtrate->GetXaxis()->SetBinLabel(31,"2/2");
  #endif

  #ifdef normal
  num = 20;
  hist_evtrate= new TH1D(histname, "", num, 0, num);
  hist_evtrate->GetXaxis()->SetBinLabel(1,"1/25");
  hist_evtrate->GetXaxis()->SetBinLabel(2,"1/26");
  hist_evtrate->GetXaxis()->SetBinLabel(3,"1/27");
  hist_evtrate->GetXaxis()->SetBinLabel(4,"1/28");
  hist_evtrate->GetXaxis()->SetBinLabel(5,"1/29");
  hist_evtrate->GetXaxis()->SetBinLabel(6,"1/30");
  hist_evtrate->GetXaxis()->SetBinLabel(7,"1/31");
  hist_evtrate->GetXaxis()->SetBinLabel(8,"2/1");
  hist_evtrate->GetXaxis()->SetBinLabel(9,"2/2");
  hist_evtrate->GetXaxis()->SetBinLabel(10,"2/3");
  hist_evtrate->GetXaxis()->SetBinLabel(11,"2/4");
  hist_evtrate->GetXaxis()->SetBinLabel(12,"2/5");
  hist_evtrate->GetXaxis()->SetBinLabel(13,"2/6");
  hist_evtrate->GetXaxis()->SetBinLabel(14,"2/7");
  hist_evtrate->GetXaxis()->SetBinLabel(15,"2/8");
  hist_evtrate->GetXaxis()->SetBinLabel(16,"2/9");
  hist_evtrate->GetXaxis()->SetBinLabel(17,"2/10");
  hist_evtrate->GetXaxis()->SetBinLabel(18,"2/11");
  hist_evtrate->GetXaxis()->SetBinLabel(19,"2/12");
  #endif 
  
  hist_evtrate->SetMaximum(0.40);
  hist_evtrate->GetXaxis()->SetLabelSize(0.08);
  hist_evtrate->SetTitle("EventRate;;(/10^{14} P.O.T)");
  hist_evtrate->SetStats(0);

  EVTCluster* evtcluster = new EVTCluster();
  DetRecon* detrecon = new DetRecon();
  EasyRecon* easyrecon = new EasyRecon();
  BSDApply* bsdapply = new BSDApply();
  BabyMIND* babymind = new BabyMIND();
  Tracking* tracking = new Tracking();

  TString datadir = "${processdir}/process/4-Recon";
  TString filename;
  TFile* fin;
  TTree* tree;
  int NEntry;

  const int Ndate=100;
  double sandmuon[6][Ndate];
  double sandmuonrate[6][Ndate];
  double error_rate[6][Ndate];

  double neutrino[6][Ndate];
  double neutrinorate[6][Ndate];
  double error_rate_nu[6][Ndate];

  double dateid[Ndate];
  double error_date[Ndate];
  for(int idate=0; idate<Ndate; idate++)
    {
      double offset=0.5;
      dateid[idate] = idate+offset;
      error_date[idate] = 0.5;
      for(int imod=0; imod<6; imod++)
	{
	  sandmuon[imod][idate]=0;
	  sandmuonrate[imod][idate]=0;
	}
    }

  double totalpot[Ndate];
  double norm=pow(10, 14);

  int modcolor[7] = {2, 3, 4, 6, 1, 5, 14};
  vector<int> mon =  {1,  1,  1,  1,  1,  1,  2, 2, 2, 2, 2, 2};
  vector<int> date = {26, 27, 28, 29, 30, 31, 1, 2, 3, 4, 5, 7};
  int nfile = mon.size();
  //int nfile = 1;

  vector<int> ataribunch;
  int ntrack;
  int nhit;
  vector<int> activepln[9][6][20];

  for(int ifile=0; ifile<nfile; ifile++)
    {
      filename.Form("%s/Recon_%d_%d.root", datadir.Data(), mon.at(ifile), date.at(ifile));
      fin = new TFile(filename, "READ");
      tree = (TTree*)fin->Get("tree");
      tree->SetBranchAddress("EVTCluster", &evtcluster);
      tree->SetBranchAddress("DetRecon", &detrecon);
      NEntry = tree->GetEntries();
      NEntry = 1000;
      totalpot[ifile]=0;

      for(int ientry=0; ientry<NEntry; ientry++)
	{
	  tree->GetEntry(ientry);
	  totalpot[ifile] += evtcluster->pot;
	  //for(int ientry=0; ientry<300000; ientry++)
	  for(int imod=5; imod<6; imod++)
	    for(int ibunch=1; ibunch<9; ibunch++)
	      { 
		ntrack = detrecon->Ntrack[imod][0][ibunch];
		for(int itrack=0; itrack<ntrack; itrack++)
		  {
		    activepln[ibunch][imod][itrack].clear();
		    nhit = detrecon->Nhit[imod][0][ibunch][itrack];
		    for(int ihit=0; ihit<nhit; ihit++)
		      {
			double posz = detrecon->posz[imod][0][ibunch][itrack][ihit];
			activepln[ibunch][imod][itrack].push_back(posz);
		      }

		    //For Neutrinos ******************
		    auto minid = min_element(activepln[ibunch][imod][itrack].begin(), 
					    activepln[ibunch][imod][itrack].end());
		    int min = minid - activepln[ibunch][imod][itrack].begin();
		    double posy = detrecon->posy[imod][0][ibunch][itrack][min];
		    double posz = detrecon->posz[imod][0][ibunch][itrack][min];
		    //cout << "posy= " << posy << " posz= " << posz << '\n';
		    //cout << tracking->FVcut(5, 0, posy, posz) << '\n';
		    if(tracking->FVcut(5, 0, posy, posz) ==1)
		      neutrino[imod][ifile]++;
		    //For Neutrinos ******************

		    //For Sand Muons *****************
		    sort(activepln[ibunch][imod][itrack].begin(), activepln[ibunch][imod][itrack].end());
		    auto last = unique(activepln[ibunch][imod][itrack].begin(), 
				       activepln[ibunch][imod][itrack].end());
		    activepln[ibunch][imod][itrack].erase(last, activepln[ibunch][imod][itrack].end());
		    //for(int i=0; i<activepln[ibunch][imod][itrack].size(); i++)
		    //  cout << "pln= " << activepln[ibunch][imod][itrack].at(i) << '\n'; 
		    babymind->ConverttoPln(activepln[ibunch][imod][itrack]);		    
		    //for(int i=0; i<babymind->plane.size(); i++)
		    //  cout << "pln= " << babymind->plane.at(i) << '\n';		    
		    if(nhit>=9 && babymind->SearchThePln(1))
		      sandmuon[imod][ifile]++;
		    //For Sand Muons *****************
		  }	
	      }

	  if(ientry%10==0)
	    cout << "ientry= " << ientry << '\n'; 
	}//ientry

    }//ifile

  for(int i=0; i<nfile; i++)
    {
      for(int imod=0; imod<6; imod++)
	{
	  dateid[i] = i+0.5;
	  error_date[i] = 0.5;

	  double x = sandmuon[imod][i];
	  double y = totalpot[i];

	  error_rate[imod][i] = sqrt(x)/y*norm;
	}      

      for(int imod=0; imod<6; imod++)
	{
	  dateid[i] = i+0.5;
	  error_date[i] = 0.5;

	  double x = neutrino[imod][i];
	  double y = totalpot[i];

	  error_rate_nu[imod][i] = sqrt(x)/y*norm;
	}      

      cout << "Sand muons" << '\n';
      sandmuonrate[5][i] = sandmuon[5][i]/totalpot[i]*norm;
      cout << "Total POT = " << totalpot[i] << '\n';
      cout << mon.at(i) << "/" << date.at(i)
	   << " the number = " << sandmuon[5][i]  
	   << " Rate= " << sandmuonrate[5][i] << " error= " << error_rate[5][i]  <<  '\n';

      cout << '\n';

      cout << "Neutrino" << '\n';
      neutrinorate[5][i] = neutrino[5][i]/totalpot[i]*norm;
      cout << "Total POT = " << totalpot[i] << '\n';
      cout << mon.at(i) << "/" << date.at(i)
	   << " the number = " << neutrino[5][i]  
	   << " Rate= " << neutrinorate[5][i] << " error= " << error_rate_nu[5][i]  <<  '\n';
    }
  
  for(int imod=0; imod<6; imod++)
    {
      graph_evtrate[imod] = new TGraphErrors(nfile, dateid, sandmuonrate[imod], error_date, error_rate[imod]);
      graph_evtrate[imod]->SetMarkerStyle(21);
      graph_evtrate[imod]->SetMarkerColor(modcolor[imod]);

      graph_evtrate_nu[imod]
	= new TGraphErrors(nfile, dateid, neutrinorate[imod], error_date, error_rate_nu[imod]);
      graph_evtrate_nu[imod]->SetMarkerStyle(21);
      graph_evtrate_nu[imod]->SetMarkerColor(modcolor[imod]);
    }

  c1->cd();
  hist_evtrate->Draw("");
  graph_evtrate[0]->Draw("P,same");
  graph_evtrate[1]->Draw("P,same");
  graph_evtrate[2]->Draw("P,same");
  graph_evtrate[3]->Draw("P,same");
  graph_evtrate[4]->Draw("P,same");
  graph_evtrate[5]->Draw("P,same");
  TF1 *linear = new TF1("linear", "[0]", 1, 17);
  linear->SetParameters(0, 0.35);
  gStyle->SetOptFit(1111);
  graph_evtrate[5]->Fit(linear, "", "", 0, 18);

  TLegend *legend = new TLegend(0.70, 0.50, 0.90, 0.80);
  legend->AddEntry(graph_evtrate[0], "Proton Module", "P");
  legend->AddEntry(graph_evtrate[1], "WAGASCI Upstream", "P");
  legend->AddEntry(graph_evtrate[2], "WAGASCI Downstream", "P");
  legend->AddEntry(graph_evtrate[3], "WallMRD North", "P");
  legend->AddEntry(graph_evtrate[4], "WallMRD South", "P");
  legend->AddEntry(graph_evtrate[5], "Baby MIND", "P");
  legend->SetFillStyle(0);
  legend->Draw();

  c2->cd();
  hist_evtrate->Draw("");
  graph_evtrate_nu[0]->Draw("P,same");
  graph_evtrate_nu[1]->Draw("P,same");
  graph_evtrate_nu[2]->Draw("P,same");
  graph_evtrate_nu[3]->Draw("P,same");
  graph_evtrate_nu[4]->Draw("P,same");
  graph_evtrate_nu[5]->Draw("P,same");
  TF1 *linear_nu = new TF1("linear_nu", "[0]", 1, 17);
  linear_nu->SetParameters(0, 0.35);
  gStyle->SetOptFit(1111);
  graph_evtrate_nu[5]->Fit(linear_nu, "", "", 0, 18);

  TLegend *legend_nu = new TLegend(0.70, 0.50, 0.90, 0.80);
  legend_nu->AddEntry(graph_evtrate_nu[0], "Proton Module", "P");
  legend_nu->AddEntry(graph_evtrate_nu[1], "WAGASCI Upstream", "P");
  legend_nu->AddEntry(graph_evtrate_nu[2], "WAGASCI Downstream", "P");
  legend_nu->AddEntry(graph_evtrate_nu[3], "WallMRD North", "P");
  legend_nu->AddEntry(graph_evtrate_nu[4], "WallMRD South", "P");
  legend_nu->AddEntry(graph_evtrate_nu[5], "Baby MIND", "P");
  legend_nu->SetFillStyle(0);
  legend_nu->Draw();

  c1->Update();
  c2->Update();
  app.Run();  
  return 0;
  
}
