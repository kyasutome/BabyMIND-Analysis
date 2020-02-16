#include <iostream>
#include <stdio.h>

#include "TGraph.h"
#include "TGraphErrors.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TLegend.h"

//include
#include "easyrecon.cpp"
#include "wallmrd.cpp"
#include "BSDApply.cpp"

//library
#include "BasicRecon.hpp"

using namespace std;

int main( int argc, char **argv )
{
  std::string name = string(argv[1]);
  TString filename(name);
  TString histname;

  TApplication app("app", 0, 0, 0, 0);
  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 500);

  TH1D* hist_evtrate;
  TGraphErrors* graph_evtrate[7];

  histname.Form("evtrate");
  hist_evtrate= new TH1D(histname, "", 15, 0, 15);
  hist_evtrate->GetXaxis()->SetBinLabel(1,"1/29");
  hist_evtrate->GetXaxis()->SetBinLabel(2,"1/30");
  hist_evtrate->GetXaxis()->SetBinLabel(3,"1/31");
  hist_evtrate->GetXaxis()->SetBinLabel(4,"2/1");
  hist_evtrate->GetXaxis()->SetBinLabel(5,"2/2");
  hist_evtrate->GetXaxis()->SetBinLabel(6,"2/3");
  hist_evtrate->GetXaxis()->SetBinLabel(7,"2/4");
  hist_evtrate->GetXaxis()->SetBinLabel(8,"2/5");
  hist_evtrate->GetXaxis()->SetBinLabel(9,"2/6");
  hist_evtrate->GetXaxis()->SetBinLabel(10,"2/7");
  hist_evtrate->GetXaxis()->SetBinLabel(11,"2/8");
  hist_evtrate->GetXaxis()->SetBinLabel(12,"2/9");
  hist_evtrate->GetXaxis()->SetBinLabel(13,"2/10");
  hist_evtrate->GetXaxis()->SetBinLabel(14,"2/11");
  hist_evtrate->GetXaxis()->SetBinLabel(15,"2/12");
  
  hist_evtrate->SetMaximum(0.30);
  hist_evtrate->GetXaxis()->SetLabelSize(0.08);
  hist_evtrate->SetTitle("EventRate (sand muons);;(/10^{14} P.O.T)");
  hist_evtrate->SetStats(0);

  EVTCluster* evtcluster = new EVTCluster();
  EasyRecon* easyrecon = new EasyRecon();
  BSDApply* bsdapply = new BSDApply();
  BasicRecon* basicrecon[7];
  for(int i=0; i<7; i++)
    basicrecon[i] = new BasicRecon();
  
  TFile* fin = new TFile(filename, "READ");
  TTree* tree = (TTree*)fin->Get("tree");
  tree->SetBranchAddress("EVTCluster", &evtcluster);
  int NEntry = tree->GetEntries();
  
  double sandmuonrate[6][31];
  double error_rate[6][31];
  double dateid[31];
  double error_date[31];
  for(int idate=0; idate<31; idate++)
    {
      double offset=0.5;
      dateid[idate] = idate+offset;
      error_date[idate] = 0.5;
      for(int imod=0; imod<6; imod++)
	sandmuonrate[imod][idate]=0;
    }

  double POT=0;
  double TPOT=0;
  double norm=pow(10, 14);

  int premon, predate, prehour; // startdate: 1/30
  time_t preunixtime;
  int mon, date, hour; // startdate: 1/29
  time_t theunixtime;
  int modcolor[7] = {2, 3, 4, 6, 1, 5, 14};
  int datecount=0;

  for(int ientry=0; ientry<NEntry; ientry++)
    //for(int ientry=0; ientry<20000; ientry++)
    {
      tree->GetEntry(ientry);
      theunixtime = evtcluster->unixtime;
      bsdapply->GetMonDateHour(theunixtime, &mon, &date, &hour);

      if(datecount>=1)
	if(date!=predate)
	  {
	    //cout << date << " " << predate << '\n';
	    cout << mon << "/" << date << '\n';
	    cout << sandmuonrate[0][datecount] << " " << sandmuonrate[1][datecount] << " " << sandmuonrate[2][datecount] << " "
		 << sandmuonrate[3][datecount] << " " << sandmuonrate[4][datecount] << " " << sandmuonrate[5][datecount] 
		 << " POT= " << POT << '\n';

	    for(int imod=0; imod<6; imod++)
	      sandmuonrate[imod][datecount] = sandmuonrate[imod][datecount]/POT*norm;
	    TPOT=evtcluster->totalpot;
	    datecount++;
	  }

      if(datecount==0)
	if(date!=29)
	  {
	    cout << mon << "/" << date << '\n';
	    cout << sandmuonrate[0][0] << " " << sandmuonrate[1][0] << " " << sandmuonrate[2][0] << " "
		 << sandmuonrate[3][0] << " " << sandmuonrate[4][0] << " " << sandmuonrate[5][0] 
		 <<  " POT= " << POT << '\n';

	    for(int imod=0; imod<6; imod++)
	      sandmuonrate[imod][datecount] = sandmuonrate[imod][datecount]/POT*norm;
	    
	    TPOT=evtcluster->totalpot;
	    datecount++;
	  }

      easyrecon->Recon(evtcluster, basicrecon);
      
      if(easyrecon->NHCheck(0, 0, basicrecon[0]) && easyrecon->NHCheck(0, 1, basicrecon[0]))
	if(!easyrecon->FVCheck(0, 0) || !easyrecon->FVCheck(0, 1))
	//if(easyrecon->FVCheck(0, 0) && easyrecon->FVCheck(0, 1))
	  {
	    sandmuonrate[0][datecount]++;
	    //if(date==9)
	    //cout << "ProtonModule"  << "ientry= " << ientry << '\n';
	  } 

      if(easyrecon->NHCheck(1, 0, basicrecon[1]) && easyrecon->NHCheck(1, 1, basicrecon[1]))
	if(!easyrecon->FVCheck(1, 0) || !easyrecon->FVCheck(1, 1))
	//if(easyrecon->FVCheck(1, 0) || easyrecon->FVCheck(1, 1))
	  {
	    sandmuonrate[1][datecount]++;
	    //cout << "WAGASCI upstream " << "ientry= " << ientry << '\n';
	  } 

      if(easyrecon->NHCheck(2, 0, basicrecon[2]) && easyrecon->NHCheck(2, 1, basicrecon[2]))
	if(!easyrecon->FVCheck(2, 0) || !easyrecon->FVCheck(2, 1))
	  {
	    sandmuonrate[2][datecount]++;
	    //cout << "WAGASCI downstream" << "ientry= " << ientry << '\n';
	  } 

      if(easyrecon->NHCheck(3, 1, basicrecon[3]))
	if(!easyrecon->FVCheck(3, 1))
	  {
	    sandmuonrate[3][datecount]++;
	    //cout << "WallMRD north " << "ientry= " << ientry << '\n';
	  } 

      if(easyrecon->NHCheck(4, 1, basicrecon[4]))
	if(!easyrecon->FVCheck(4, 1))
	  {
	    sandmuonrate[4][datecount]++;
	    //if(date==9)
	    //cout << "WallMRD south " << "ientry= " << ientry << '\n';
	  } 

      if(easyrecon->NHCheck(5, 0, basicrecon[5]) && easyrecon->NHCheck(5, 1, basicrecon[5]))
	if(!easyrecon->FVCheck(5, 0) || !easyrecon->FVCheck(5, 1))
	  {
	    sandmuonrate[5][datecount]++;
	    //if(date==9)
	    //cout << "BabyMIND " << "ientry= " << ientry << '\n';
	  } 

      POT = evtcluster->totalpot - TPOT;
      preunixtime = evtcluster->unixtime;
      bsdapply->GetMonDateHour(preunixtime, &premon, &predate, &prehour);
      
    }//ientry

  for(int imod=0; imod<6; imod++)
    sandmuonrate[imod][datecount] = sandmuonrate[imod][datecount]/POT*norm;  

  for(int icount=0; icount<=datecount; icount++)
    {
      cout << sandmuonrate[0][icount] << '\n';
      cout << sandmuonrate[1][icount] << '\n';
      cout << sandmuonrate[2][icount] << '\n';
      cout << sandmuonrate[3][icount] << '\n';
      cout << sandmuonrate[4][icount] << '\n';
      cout << sandmuonrate[5][icount] << '\n';
      cout << '\n';

      for(int imod=0; imod<6; imod++)
	error_rate[imod][icount] = 0;
    }  

  for(int imod=0; imod<6; imod++)
    {
      //hist_evtrate[imod]->Fill(icount+1, sandmuonrate[icount][imod]);
      graph_evtrate[imod] = new TGraphErrors(14, dateid, sandmuonrate[imod], error_date, error_rate[imod]);
      graph_evtrate[imod]->SetMarkerStyle(21);
      graph_evtrate[imod]->SetMarkerColor(modcolor[imod]);
    }

  c1->cd();
  hist_evtrate->Draw("");
  graph_evtrate[0]->Draw("P,same");
  graph_evtrate[1]->Draw("P,same");
  graph_evtrate[2]->Draw("P,same");
  graph_evtrate[3]->Draw("P,same");
  graph_evtrate[4]->Draw("P,same");
  graph_evtrate[5]->Draw("P,same");

  TLegend *legend = new TLegend(0.70, 0.50, 0.90, 0.80);
  legend->AddEntry(graph_evtrate[0], "Proton Module", "P");
  legend->AddEntry(graph_evtrate[1], "WAGASCI Upstream", "P");
  legend->AddEntry(graph_evtrate[2], "WAGASCI Downstream", "P");
  legend->AddEntry(graph_evtrate[3], "WallMRD North", "P");
  legend->AddEntry(graph_evtrate[4], "WallMRD South", "P");
  legend->AddEntry(graph_evtrate[5], "Baby MIND", "P");
  //legend->Draw();

  c1->Update();
  app.Run();
  
  return 0;
  
}
