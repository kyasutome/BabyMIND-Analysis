#include <iostream>
#include <stdio.h>
#include <vector>

#include <TString.h>
#include <TTree.h>
#include <TFile.h>
#include <TApplication.h>
#include <TGraphErrors.h>
#include <TLegend.h>

//include
#include "BSDApply.cpp"
#include "MakeMonitor.cpp"
#include "EasyRecon.cpp"
#include "wagasci.cpp"

//library
#include "EVTCluster.hpp"
#include "BMDisp.hpp"
#include "BasicRecon.hpp"

using namespace std;
//#define display
//#define eventtiming
#define eventrate

int main( int argc, char **argv )
{
  std::string name = string(argv[1]);
  TString filename(name);
  TString histname;
  TString CanvasName;

  TApplication app("app", 0, 0, 0, 0);

  TH1D *hist_eventtiming[7];
  double xmin[7] = {2000, 13000, 13000, 13000, 13000, 40000, 40000};
  double xmax[7] = {8000, 20000, 20000, 20000, 20000, 46000, 46000};
  for(int imod=0; imod<7; imod++)
    {
      histname.Form("hist_eventtiming_mod%d", imod);
      hist_eventtiming[imod] = new TH1D(histname, histname, 500, xmin[imod], xmax[imod]);
    }

  TH1D* hist_evtrate;
  TGraphErrors* graph_evtrate[7];
  int num = 19;
  histname.Form("neutrino event rate");
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
  hist_evtrate->SetMaximum(0.30);
  hist_evtrate->GetXaxis()->SetLabelSize(0.08);
  hist_evtrate->SetTitle("EventRate (neutrino);;(/10^{16} P.O.T)");
  hist_evtrate->SetStats(0);

  int premon, predate, prehour; // startdate: 1/30                                                                      
  time_t preunixtime;
  int mon, date, hour; // startdate: 1/29                                                                               
  time_t theunixtime;
  int modcolor[7] = {2, 3, 4, 6, 1, 5, 14};
  int datecount=0;

  int startdate = 25;
  int Mon, Date, Hour;
  const int Ndate=100;
  double neutrinorate[6][Ndate];
  double error_rate[6][Ndate];
  double dateid[Ndate];
  double error_date[Ndate];

  for(int idate=0; idate<Ndate; idate++)
    {
      double offset=0.5;
      dateid[idate] = idate+offset;
      error_date[idate] = 0.5;
      for(int imod=0; imod<6; imod++)
	neutrinorate[imod][idate]=0;
    }
  
  double POT=0;
  double TPOT=0;
  double norm=pow(10, 16);

  vector<int> ataribunch;
  vector<double> posxy[2];
  vector<double> posz[2];  
  vector<double>hittime[2][7];
  int targetmod;

  double ifposz[2];
  double ifposxy[2];

  BSDApply* bsdapply = new BSDApply();
  EVTCluster* inputcluster = new EVTCluster();
  EVTCluster* targetcluster = new EVTCluster();
  EasyRecon* easyrecon = new EasyRecon();
  BasicRecon* basicrecon[9];
  for(int i=0; i<9; i++)
    basicrecon[i] = new BasicRecon();
  MakeMonitor* makemonitor = new MakeMonitor();
  WAGASCI* wagasci = new WAGASCI();

  TFile *fin = new TFile(filename, "Read");
  TTree *tree = (TTree*)fin->Get("tree");
  tree->SetBranchAddress("EVTCluster", &inputcluster);
  cout << tree->GetEntries() << '\n';

  TFile *fout = new TFile("./result/DetPerform/eventtiming.root", "RECREATE");

  for(int imod=0; imod<3; imod++)
    {
      targetmod = imod;
      datecount=0;
      double POT=0;
      double TPOT=0;

      for(int ientry=0; ientry<tree->GetEntries(); ientry++)
      //for(int ientry=0; ientry<200000; ientry++)
    {
      targetcluster->Clear();

      bool track = false;;
      bool neutrino[2] = {false, false};

      for(int i=0; i<2; i++)
	{
	  posxy[i].clear();
	  posz[i].clear();

	  for(int j=0; j<7; j++)
	    hittime[i][j].clear();
	}

	  int targetbunch=0;
	  int view;
	  int mod;
	  int nofposxy[2]={0, 0};
	  int nofposz[2]={0, 0};
      
	  ataribunch.clear();
	  tree->GetEntry(ientry);

#ifdef eventrate

      theunixtime = inputcluster->unixtime;
      bsdapply->GetMonDateHour(theunixtime, &mon, &date, &hour);

      if(datecount>=1)
	if(date!=predate)
	  {
	    neutrinorate[targetmod][datecount] = neutrinorate[targetmod][datecount]/POT*norm;
	    TPOT=inputcluster->totalpot;
	    datecount++;
	  }//datecount>=1                                                                                               
      
      if(datecount==0)
	if(date!=startdate)
	  {
	    neutrinorate[targetmod][datecount] = neutrinorate[targetmod][datecount]/POT*norm;
	    TPOT=inputcluster->totalpot;
	    datecount++;
	  }  

#endif
	  
      easyrecon->Recon(inputcluster, basicrecon);
      if(easyrecon->NHCheck(targetmod, 0, basicrecon[targetmod], &ataribunch))
	targetbunch = ataribunch.at(0);
      
      for(int ihit=0; ihit<inputcluster->mod.size(); ihit++)
	{
	  if(inputcluster->bunch.at(ihit)!=targetbunch)
	    continue;
	  
	  mod = inputcluster->mod.at(ihit);
	  if(mod==0 || mod==5 || mod==6)
	    view = inputcluster->view.at(ihit);
	  if(mod==1 || mod==2)
	    view = fabs((int)inputcluster->view.at(ihit)%2-1);
	  if(mod==3 || mod==4)
	    view = 1;
	  
	  if(view==0)
	    {
	      targetcluster->mod.push_back(mod);
	      targetcluster->view.push_back(inputcluster->view.at(ihit));
	      targetcluster->pln.push_back(inputcluster->pln.at(ihit));
	      targetcluster->posy.push_back(inputcluster->posy.at(ihit));
	      targetcluster->posz.push_back(inputcluster->posz.at(ihit));
	      targetcluster->posx.push_back(-1);
	      targetcluster->bunch.push_back(targetbunch);
	      targetcluster->unixtime = inputcluster->unixtime;
	      
	      hittime[0][mod].push_back(inputcluster->Htime.at(ihit));
	    }
	  
	  if(view==1)
	    {
	      targetcluster->mod.push_back(mod);
	      targetcluster->view.push_back(inputcluster->view.at(ihit));
	      targetcluster->pln.push_back(inputcluster->pln.at(ihit));
	      targetcluster->posx.push_back(inputcluster->posx.at(ihit));
	      targetcluster->posz.push_back(inputcluster->posz.at(ihit));
	      targetcluster->posy.push_back(-1);
	      targetcluster->bunch.push_back(targetbunch);  	
	      targetcluster->unixtime = inputcluster->unixtime;  
	      
	      hittime[1][mod].push_back(inputcluster->Htime.at(ihit));
	    }
	  
	  if(inputcluster->mod.at(ihit)!=targetmod)
	    continue;	  	  
	  
	  if(view==0)
	    {
	      posxy[0].push_back(inputcluster->dposy.at(ihit));
	      posz[0].push_back(inputcluster->dposz.at(ihit));
	      
	    }
	  
	  if(view==1)
	    {
	      posxy[1].push_back(inputcluster->dposx.at(ihit));
	      posz[1].push_back(inputcluster->dposz.at(ihit));	
	    }
	  
	  track = true;
	}
      
      if(track)
	{
	  for(int iview=0; iview<2; iview++)
	    {
	      sort(posxy[iview].begin(), posxy[iview].end());
	      sort(posz[iview].begin(), posz[iview].end());
	      auto last = unique(posxy[iview].begin(), posxy[iview].end());
	      posxy[iview].erase(last, posxy[iview].end());
	      last = unique(posz[iview].begin(), posz[iview].end());
	      posz[iview].erase(last, posz[iview].end());
	      
	      nofposz[iview] = posz[iview].size();
	      nofposxy[iview] = posxy[iview].size();
	      
	      if(nofposz[iview]>=1 && nofposxy[iview]>=1)
		{
		  ifposxy[0] = posxy[iview].at(0);
		  ifposxy[1] = posxy[iview].at(nofposxy[iview]-1);
		  ifposz[0] = posz[iview].at(0);
		  ifposz[1] = posz[iview].at(nofposz[iview]-1);
		  
		  //cout << ifposxy[0] << " " << ifposxy[1] << '\n';
		  //cout << ifposz[0] << " " << ifposz[1] << '\n';
		  //cout << "neutrino= " << easyrecon->SFVCheck(targetmod, iview, ifposxy, ifposz) << '\n';
		  
		  if(easyrecon->SFVCheck(targetmod, iview, ifposxy, ifposz))
		    neutrino[iview] = true;
		}
	    }
	}//track
      
      if(track && neutrino[0] && neutrino[1])
	{
	  
#ifdef display
	  cout << "ientry= " << ientry << '\n'; 
	  makemonitor->Display(targetcluster);
	  CanvasName.Form("./plots/EvtDisp/EvtDisp_0220/EvtDisp_spill_%d.png", inputcluster->spillnum);
	  makemonitor->monitor->Print(CanvasName);
	  makemonitor->timeinfo->Delete();
	  makemonitor->spillinfo->Delete();
#endif
	  
#ifdef eventtiming
	  cout << "ientry= " << ientry << '\n'; 
	  int evenodd = fabs(targetbunch%2-1);
	  int corrtime;
	  for(int imod=0; imod<7; imod++)
	    for(int iview=0; iview<2; iview++)
	      for(int ihit=0; ihit<hittime[iview][imod].size(); ihit++)
		{
		  int HitTime = hittime[iview][imod].at(ihit);
		  if(imod>=1 && imod<=4)
		    {
		      wagasci->TDCtoHittime(evenodd, HitTime, &corrtime, targetbunch);
		      HitTime = corrtime;
		    }
		  hist_eventtiming[imod]->Fill(HitTime);
		}
	  
#endif
	  
#ifdef eventrate
	  
	  time_t theunixtime = inputcluster->unixtime;
	  //POT = inputcluster->totalpot - TPOT;
	  //cout << "ientry= " << ientry  << " unixtime = " << theunixtime << '\n';
	  neutrinorate[targetmod][datecount]++;
#endif
      
	}//track, nuetrino
      
#ifdef eventrate
      POT = inputcluster->totalpot - TPOT;
      preunixtime = inputcluster->unixtime;
      bsdapply->GetMonDateHour(preunixtime, &premon, &predate, &prehour);
#endif
            
    }//ientry
 
      neutrinorate[targetmod][datecount] = neutrinorate[targetmod][datecount]/POT*norm;

    }//mod
 
  fout->cd();
  for(int imod=0; imod<7; imod++)
    hist_eventtiming[imod]->Write();
  fout->Close();
  
#ifdef eventrate
  TCanvas* c1 = new TCanvas("c1", "c1", 1800, 600);
  
  for(int imod=0; imod<3; imod++)
    {
      targetmod=imod;
      if(imod==1 || imod==2)
	neutrinorate[targetmod][4] = 0;
      
      for(int i=0; i<datecount+1; i++)
	{
	  cout << "i= " << i << " neutrino= "  << neutrinorate[targetmod][i] << '\n';
	}
      
      graph_evtrate[targetmod] = new TGraphErrors(num, dateid, neutrinorate[targetmod], error_date, error_rate[targetmod]);
      graph_evtrate[targetmod]->SetMarkerStyle(21);
      graph_evtrate[targetmod]->SetMarkerColor(modcolor[targetmod]);
    }
  
  c1->cd();
  hist_evtrate->Draw("");
  graph_evtrate[0]->Draw("P,same");
  graph_evtrate[1]->Draw("P,same");
  graph_evtrate[2]->Draw("P,same");
  c1->Update();

  TLegend *legend = new TLegend(0.70, 0.50, 0.90, 0.80);
  legend->AddEntry(graph_evtrate[0], "Proton Module", "P");
  legend->AddEntry(graph_evtrate[1], "WAGASCI Upstream", "P");
  legend->AddEntry(graph_evtrate[2], "WAGASCI Downstream", "P");
  legend->Draw("");

  app.Run();
#endif
  
  
  return 0;
  
}
