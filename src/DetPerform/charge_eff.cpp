#include <iostream>
#include <stdio.h>
#include <vector>

#include <TString.h>
#include <TTree.h>
#include <TFile.h>
#include <TApplication.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH2D.h>

//include
#include "chargeid.cpp"
#include "Tracking.cpp"

//library
#include "EVTCluster.hpp"
#include "DetRecon.hpp"
#include "BMDisp.hpp"

//#define display
//#define chargeID_neutrino
//#define chargeID_anti
#define pmureso

using namespace std;

int main( int argc, char **argv )
{
  std::string name = string(argv[1]);
  int targetentry = atoi(argv[3]);
  TString filename(name);
  TString histname;

  EVTCluster* evtcluster = new EVTCluster();
  DetRecon* detrecon = new DetRecon();
  MCTrue* mctrue = new MCTrue();
  ChargeID* chargeid = new ChargeID();
  Tracking* tracking = new Tracking();

  TFile *fin = new TFile(filename, "Read");
  TTree *tree = (TTree*)fin->Get("tree");
  tree->SetBranchAddress("EVTCluster", &evtcluster);
  tree->SetBranchAddress("DetRecon", &detrecon);
  tree->SetBranchAddress("MCTrue", &mctrue);
  cout << tree->GetEntries() << '\n';

#ifdef pmureso
  TFile *fout = new TFile(Form("${processdir}/result/DetPerform/pmureso_alpha.root"), "RECREATE");
#endif
#ifdef chargeID_neutrino
  TFile *fout = new TFile(Form("${processdir}/result/DetPerform/chargeid_nu_3.root"), "RECREATE");
#endif
#ifdef chargeID_anti
  TFile *fout = new TFile(Form("${processdir}/result/DetPerform/chargeid_anti_1.root"), "RECREATE");
#endif
  TTree *otree = new TTree("tree", "tree");
  double numerator_ang[10], denomenator_ang[10];
  double numerator_pmu[15], denomenator_pmu[15];
  for(int i=0; i<10; i++)
    {
      numerator_ang[i] = 0;
      denomenator_ang[i] = 0;
    }
  for(int i=0; i<15; i++)
    {
      numerator_pmu[i] = 0;
      denomenator_pmu[i] = 0;
    }
  otree->Branch("numerator_pmu", numerator_pmu, "numerator_pmu[15]/D");
  otree->Branch("denomenator_pmu", denomenator_pmu, "numerator_pmu[15]/D");
  otree->Branch("numerator_ang", numerator_ang, "numerator_ang[10]/D");
  otree->Branch("denomenator_ang", denomenator_ang, "numerator_ang[10]/D");

  TTree *ctree = new TTree("ctree", "ctree");
  double chi2[2];
  double weight;
  double Pmu;
#ifdef chargeID_anti
  int mutype = -13;
  ctree->Branch("weight", &weight, "weight/D");
  ctree->Branch("mutype", &mutype, "mutype/I");
  ctree->Branch("Pmu", &Pmu, "Pmu/D");
  ctree->Branch("chi2", chi2, "chi[2]/D");
#endif
#ifdef chargeID_neutrino
  int mutype = 13;
  ctree->Branch("weight", &weight, "weight/D");
  ctree->Branch("mutype", &mutype, "mutype/I");
  ctree->Branch("Pmu", &Pmu, "Pmu/D");
  ctree->Branch("chi2", chi2, "chi[2]/D");
#endif
#ifdef pmureso
  int mutype = 13;
#endif


  double dangle = 1/10.;
  double dpmu = 3000/15.;
  TH1D* pmuresolution_c = new TH1D("pmuresolution_c", "", 100, -2000, 2000);
  TH1D* pmuresolution_r = new TH1D("pmuresolution_r", "", 100, -2000, 2000);
  TH2D* pmucomparison = new TH2D("pmucomparison", "", 100, 0, 2000, 100, 0, 2000);
  double pmudif[2];

  int bmntrack;
  int pmntrack[2];
  double mcest[2];
  double rangemom;
  int muminus=0;
  int muplus=0;
  
  bool fccut[6][2];
  vector<int>particlelist;
  vector<double>ipos[4], fpos[4], momentum[4];
  vector<double>absmomentum;
  vector<int>muminusentry, muplusentry;
  double d[3];
  double scattering;
  //targetentry=142;
  for(int ientry=0; ientry<tree->GetEntries(); ientry++)
  //for(int ientry=0; ientry<500; ientry++)
    {

#ifdef display
      if(ientry!=targetentry)
	continue;
#endif

      particlelist.clear();
      absmomentum.clear();
      for(int i=0; i<4; i++)
        {
          ipos[i].clear();
          fpos[i].clear();
          momentum[i].clear();
        }

      tree->GetEntry(ientry);

      weight = mctrue->totcrsne*pow(10, -38)*mctrue->norm*6.0*pow(10, 23)*300*pow(10, 3)/(144*144);

      for(int imod=0; imod<6; imod++)
        for(int iview=0; iview<2; iview++)
	  fccut[imod][iview]=false;

      tracking->SearchParticle(mutype, mctrue, &particlelist);
      
      for(int ipar=0; ipar<particlelist.size(); ipar++)
        {
          for(int i=0; i<3; i++)
            {
              int parid = particlelist.at(ipar);
              ipos[i].push_back(mctrue->ipos[i][parid]*10);
              fpos[i].push_back(mctrue->fpos[i][parid]*10);
              momentum[i].push_back(mctrue->momentum[i][parid]*1000);
	      d[i] = mctrue->momentum[i][parid];
            }
          absmomentum.push_back(sqrt( pow(momentum[0].at(0),2)+pow(momentum[1].at(0),2)+pow(momentum[2].at(0),2) ));
        }

      for(int iview=0; iview<2; iview++)	
	{
	  if(ipos[0].size()==1)
	    {
	      if(iview==0)
		fccut[5][0]=tracking->FCcut(5, iview, fpos[2].at(0), fpos[1].at(0));
	      if(iview==1)
		fccut[5][1]=tracking->FCcut(5, iview, fpos[2].at(0), fpos[0].at(0));
	    }

	  pmntrack[iview] = detrecon->Ntrack[0][iview][1];
	}
      
      if(!fccut[5][0] || !fccut[5][1])
	continue;    
      
      bmntrack = detrecon->Ntrack[5][0][1];
      if(bmntrack!=1)
	continue;

      if(chargeid->MakePlnPos(detrecon->posz[5][0][1][0], detrecon->posy[5][0][1][0]))
	{

#ifdef chargeID
	  if(chargeid->lastmodule < 4)
	    continue;
#endif
#ifdef pmureso
	  if(chargeid->lastmodule < 8)
	    continue;
#endif
	}
      
      scattering = d[2]/sqrt(d[0]*d[0]+d[1]*d[1]+d[2]*d[2]);
      double initpos = ipos[2].at(0)+1200;
      double initdE = tracking->CalcdE(initpos, scattering);
      cout << "scattering= " << scattering << " initpos= " << initpos << " initdE= " << initdE << '\n';
      
      chargeid->MCEST(detrecon->posz[5][0][1][0], detrecon->posy[5][0][1][0], mcest);
      chargeid->RangeCalc(detrecon->posz[5][0][1][0], detrecon->posy[5][0][1][0], 
			  detrecon->posz[5][1][1][0], detrecon->posx[5][1][1][0], &rangemom);
      chi2[0] = chargeid->minchi[0];
      chi2[1] = chargeid->minchi[1];
      Pmu = absmomentum.at(0);
      ctree->Fill();
      
      cout << "ientry= " << ientry  << " estimate information" << '\n';
      cout << "mu momentum= " << absmomentum.at(0) << " rangemom= " << rangemom  << '\n';
      for(int ic=0; ic<=1; ic++)
	{
	  cout << "ic= " << ic << '\n';
	  for(int i=1; i<=18; i++)
	    {
	      cout << "posz= "  << chargeid->refposz[i] << " posy= " << chargeid->estimateposy[ic][i]
		   << " data= " << chargeid->Hitposy[i] << '\n';	      
	  }
	}

      if(mcest[0]==0)
	{
	  muminus++;
	  muminusentry.push_back(ientry);
	  
	  pmudif[0] = (mcest[1]+initdE)-absmomentum.at(0);
	  pmudif[1] = (rangemom+initdE)-absmomentum.at(0);
	  cout << "pmudif= " << pmudif[0] << " pmudif= " << pmudif[1]  << '\n';
	  pmuresolution_c->Fill(pmudif[0]);
	  pmuresolution_r->Fill(pmudif[1]);
	  pmucomparison->Fill(mcest[1]+initdE, absmomentum.at(0));

	  for(int i=0; i<10; i++)
	    {
	      if(dangle*i< scattering && scattering<=dangle*(i+1))
		{
#ifdef chargeID_neutrino
		  numerator_ang[i] ++;
#endif
		  denomenator_ang[i] ++;
		  break;
		}
	    }

	  for(int i=0; i<15; i++)
	    {
	      if(dpmu*i< absmomentum.at(0) && absmomentum.at(0)<=dpmu*(i+1))
		{
#ifdef chargeID_neutrino
		  numerator_pmu[i] ++;
#endif
		  denomenator_pmu[i] ++;
		  break;
		}
	    }
	  
	}//mcest[0]==0

      if(mcest[0]==1)
	{
	  muplus++;
	  muplusentry.push_back(ientry);

	  for(int i=0; i<10; i++)
	    {
	      if(dangle*i< scattering && scattering<=dangle*(i+1))
		{
#ifdef chargeID_anti
		  numerator_ang[i] ++;
#endif
		  denomenator_ang[i] ++;
		  break;
		}
	    }

	  for(int i=0; i<15; i++)
	    {
	      if(dpmu*i< absmomentum.at(0) && absmomentum.at(0)<=dpmu*(i+1))
		{
#ifdef chargeID_anti
		  numerator_pmu[i] ++;
#endif
		  denomenator_pmu[i] ++;
		  break;
		}
	    }

	}//mcest[0]==1
    }//ientry

#ifdef chargeID_neutrino
  cout << "chargeid= " << muminus << "/" << (muminus+muplus) << "=" << muminus/(double)(muminus+muplus)  << '\n';
#endif

#ifdef chargeID_anti
  cout << "chargeid= " << muplus << "/" << (muminus+muplus) << "=" << muplus/(double)(muminus+muplus)  << '\n';
#endif

  /*
  for(int i=0; i<10; i++)
    {
      cout << "ChargeIDEff= " << numerator[i] << "/" << denomenator[i] << " = "
           << numerator[i]/(double)denomenator[i]*100 << "%"  << '\n';
    }
  */

  cout << "Angle" << '\n';

  for(int i=0; i<10; i++)
    {
      cout << "ChargeIDEff= " << numerator_ang[i] << "/" << denomenator_ang[i] << " = "
           << numerator_ang[i]/(double)denomenator_ang[i]*100 << "%"  << '\n';
    }

  cout << '\n';

  cout << "Pmu" << '\n';

  for(int i=0; i<15; i++)
    {
      cout << "ChargeIDEff= " << numerator_pmu[i] << "/" << denomenator_pmu[i] << " = "
           << numerator_pmu[i]/(double)denomenator_pmu[i]*100 << "%"  << '\n';
    }

  for(int ientry=0; ientry<muplusentry.size(); ientry++)
    {
      cout << "muplusentry= " << muplusentry.at(ientry) << '\n';
    }
  
  fout->cd();
  pmuresolution_c->Write();
  pmuresolution_r->Write();
  pmucomparison->Write();

  otree->Fill();
  otree->Write();
  ctree->Write();

#ifdef display
  TApplication app("app", 0, 0, 0, 0);
  TCanvas *canvas = new TCanvas("canvas", "canvas", 1000, 600);
  TGraph* truegraph = new TGraph(19, chargeid->refposz, chargeid->estimateposy[0]);
  truegraph->SetMarkerStyle(8);
  truegraph->SetMarkerColor(4);
  truegraph->GetXaxis()->SetLimits(-50.,4100.);
  truegraph->SetMinimum(-1000);
  truegraph->SetMaximum(+1000);
  truegraph->SetTitle("Fitting Example;Zpos[mm];Ypos[mm]");
  TGraph* falsegraph = new TGraph(19, chargeid->refposz, chargeid->estimateposy[1]);
  falsegraph->SetMarkerStyle(8);
  falsegraph->SetMarkerColor(2);

  truegraph->SetTitle("Fitting Example;Zpos[mm];Ypos[mm]");
  TGraph* recongraph = new TGraph(19, chargeid->refposz, chargeid->Hitposy);
  recongraph->SetMarkerStyle(8);
  recongraph->SetMarkerColor(1);

  canvas->cd();
  truegraph->Draw("APL");
  falsegraph->Draw("PL,same");
  recongraph->Draw("PL,same");

  TLegend* legend = new TLegend(0.10, 0.70, 0.40, 0.90);
  legend->AddEntry(truegraph, "#mu^{-}", "p");
  legend->AddEntry(falsegraph, "#mu^{+}", "p");
  legend->AddEntry(recongraph, "MC data position", "p");
  legend->SetFillStyle(0);
  legend->Draw("");

  canvas->Update();
  app.Run();
#endif
  
  return 0;
  
}
