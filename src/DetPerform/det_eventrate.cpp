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

#define finer
//#define normal

int main( int argc, char **argv )
{
  std::string name = string(argv[1]);
  TString filename(name);
  TString histname;

  TApplication app("app", 0, 0, 0, 0);
  TCanvas *c1 = new TCanvas("c1", "c1", 1800, 500);

  TH1D* hist_evtrate;
  TGraphErrors* graph_evtrate[7];

  int startdate = 25;
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

  const int Ndate=100;
  double sandmuonrate[6][Ndate];
  double error_rate[6][Ndate];
  double dateid[Ndate];
  double error_date[Ndate];
  for(int idate=0; idate<Ndate; idate++)
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
  int hourcount=0;

  vector<int> ataribunch;

  //for(int ientry=0; ientry<NEntry; ientry++)
  for(int ientry=0; ientry<300000; ientry++)
    {
      ataribunch.clear();
      tree->GetEntry(ientry);
      theunixtime = evtcluster->unixtime;
      bsdapply->GetMonDateHour(theunixtime, &mon, &date, &hour);

#ifdef finer
      if(datecount>=1)
	if(hour!=prehour)
	  {
	    hourcount++;
	    if(hourcount==6)
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
		hourcount=0;
	      }
	  }//datecount>=1

      if(datecount==0)
	if(date!=startdate)
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
#endif 

#ifdef normal
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
	    hourcount=0;
	  }//datecount>=1

      if(datecount==0)
	if(date!=startdate)
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
#endif 

      easyrecon->Recon(evtcluster, basicrecon);
      
      if(easyrecon->NHCheck(0, 0, basicrecon[0], &ataribunch) && easyrecon->NHCheck(0, 1, basicrecon[0], &ataribunch))
	if(!easyrecon->FVCheck(0, 0) || !easyrecon->FVCheck(0, 1))
	//if(easyrecon->FVCheck(0, 0) && easyrecon->FVCheck(0, 1))
	  {
	    sandmuonrate[0][datecount]++;
	    //if(date==9)
	    //cout << "ProtonModule"  << "ientry= " << ientry << '\n';
	  } 

      if(easyrecon->NHCheck(1, 0, basicrecon[1], &ataribunch) && easyrecon->NHCheck(1, 1, basicrecon[1], &ataribunch))
	if(!easyrecon->FVCheck(1, 0) || !easyrecon->FVCheck(1, 1))
	//if(easyrecon->FVCheck(1, 0) || easyrecon->FVCheck(1, 1))
	  {
	    sandmuonrate[1][datecount]++;
	    //cout << "WAGASCI upstream " << "ientry= " << ientry << '\n';
	  } 

      if(easyrecon->NHCheck(2, 0, basicrecon[2], &ataribunch) && easyrecon->NHCheck(2, 1, basicrecon[2], &ataribunch))
	if(!easyrecon->FVCheck(2, 0) || !easyrecon->FVCheck(2, 1))
	  {
	    sandmuonrate[2][datecount]++;
	    //cout << "WAGASCI downstream" << "ientry= " << ientry << '\n';
	  } 

      if(easyrecon->NHCheck(3, 1, basicrecon[3], &ataribunch))
	if(!easyrecon->FVCheck(3, 1))
	  {
	    sandmuonrate[3][datecount]++;
	    //cout << "WallMRD north " << "ientry= " << ientry << '\n';
	  } 

      if(easyrecon->NHCheck(4, 1, basicrecon[4], &ataribunch))
	if(!easyrecon->FVCheck(4, 1))
	  {
	    sandmuonrate[4][datecount]++;
	    //if(date==9)
	    //cout << "WallMRD south " << "ientry= " << ientry << '\n';
	  } 

      if(easyrecon->NHCheck(5, 0, basicrecon[5],&ataribunch) && easyrecon->NHCheck(5, 1, basicrecon[5], &ataribunch))
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
      graph_evtrate[imod] = new TGraphErrors(num, dateid, sandmuonrate[imod], error_date, error_rate[imod]);
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
