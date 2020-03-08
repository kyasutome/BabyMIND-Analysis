//Standard
#include <iostream>
#include <stdio.h>

//ROOT
#include <TString.h>
#include <TCanvas.h>
#include <TGraph.h>

//Include
#include "cellautomation.cpp"

//Library
#include "MCTrue.hpp"

using namespace std;

#define Continuous
//#define Single
//#define beam
#define MC

int main( int argc, char **argv )
{

  if(argc < 5)
    {
      cout << "usage" << '\n';
      cout << "TrackRecon [filepath][run][ientry][targetmod]" << '\n';
      exit(0);
    }
  
  std::string name = string(argv[1]);
  std::string run = string(argv[2]);
  int targetentry = atoi(argv[3]);
  int targetmod = atoi(argv[4]);
  TString filepath(name);

  int modselection[6] = {0, 1, 2, 3, 4, 5};

  TApplication app("app", 0, 0, 0, 0);
  CellAutomation *cellauto = new CellAutomation();
  EVTCluster* evtcluster = new EVTCluster();
  DetRecon* detrecon = new DetRecon();

  TGraph* recontrack[2][9][30];
  double reconposz[2][9][30][300];
  double reconposxy[2][9][30][300];
  int Nhit[2][9][20];

#ifdef beam
  int viewselection[6][2] = {{0, 1}, {5, 4}, {7, 6}, {0, 1}, {2, 3}, {0, 1}};
  //ReadFile
  TFile* file = new TFile(filepath, "read");
  TTree* tree = (TTree*)file->Get("tree");
  tree->SetBranchAddress("EVTCluster",&evtcluster);
#endif

#ifdef MC
  int viewselection[6][2] = {{0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}};
  MCTrue* mctrue = new MCTrue();
  //ReadFile
  TFile* file = new TFile(filepath, "read");
  TTree* tree = (TTree*)file->Get("tree");
  tree->SetBranchAddress("EVTCluster",&evtcluster);
  tree->SetBranchAddress("MCTrue",&mctrue);
#endif

  
  //Initialize
  for(int iview=0; iview<2; iview++)
    for(int ibunch=0; ibunch<9; ibunch++)
      for(int itrack=0; itrack<20; itrack++)
	{
	  Nhit[iview][ibunch][itrack]=0;
	  for(int ihit=0; ihit<300; ihit++)
	    {
	      reconposz[iview][ibunch][itrack][ihit]=0;
	      reconposxy[iview][ibunch][itrack][ihit]=0;	  
	    }//ibunch
	}//iview

#ifdef Single
  for(int ientry=0; ientry<tree->GetEntries(); ientry++)
    {
      int themod, theview;
      if(ientry != targetentry)
	continue;

      cellauto->Clear();
      detrecon->Clear();

      double dposx, dposy, dposz;
      double charge, hittime;
      int trackid, NHit;

      for(int iview=0; iview<2; iview++)
	{
	  themod = modselection[targetmod];
	  theview = viewselection[targetmod][iview];
	  cout << "themod= " << themod << " theview= " << theview << '\n';	
  
	  tree->GetEntry(ientry);
	  cellauto->ReadData(themod, theview, evtcluster);
	  cellauto->CellAutomaton(themod, iview);

	  for(int ibunch=0; ibunch<cellauto->ataribunch[iview].size(); ibunch++)
	    {
	      int thebunch = cellauto->ataribunch[iview].at(ibunch);
	      cout << "bunch= " << thebunch  << " Ntrack[iview][thebunch] = " << cellauto->Ntrack[iview][thebunch] << '\n';

	      detrecon->Ntrack[targetmod][iview][thebunch] = cellauto->Ntrack[iview][thebunch];
	      cout << "Ntrack= " << cellauto->Ntrack[iview][thebunch] <<'\n';
	    }//ibunch


	}//iview

    }//ientry

#endif

#ifdef Continuous

#ifdef beam
  TFile* fout = new TFile(Form("./process/4-Recon/Recon_%s.root",run.c_str()), "RECREATE");
  TTree* otree = new TTree("tree", "tree");
  otree->Branch("EVTCluster", "EVTCluster", &evtcluster, 32000, 2);
  otree->Branch("DetRecon", "DetRecon", &detrecon, 32000, 2);
#endif

#ifdef MC
  TFile* fout = new TFile(Form("./process/4-Recon/Recon_%s.root",run.c_str()), "RECREATE");
  TTree* otree = new TTree("tree", "tree");
  otree->Branch("EVTCluster", "EVTCluster", &evtcluster, 32000, 2);
  otree->Branch("DetRecon", "DetRecon", &detrecon, 32000, 2);
  otree->Branch("MCTrue", "MCTrue", &mctrue, 32000, 2);
#endif

  clock_t start = clock();

  for(int ientry=0; ientry<200; ientry++)
    {    
      int themod, theview;
      cellauto->Clear();
      detrecon->Clear();

      double dposx, dposy, dposz;
      double charge, hittime;
      int trackid, NHit;

      cout << "ientry= " << ientry << '\n';
      tree->GetEntry(ientry);

      for(int imod=0; imod<=5; imod++)
	{
	  cellauto->Clear();
	  
	  for(int iview=0; iview<2; iview++)	    
	    {
	      themod = modselection[imod];
	      theview = viewselection[imod][iview];
	      
	      cellauto->ReadData(themod, theview, evtcluster);
	      cellauto->CellAutomaton(themod, iview);

	  for(int ibunch=0; ibunch<cellauto->ataribunch[iview].size(); ibunch++)
	    {
	      int thebunch = cellauto->ataribunch[iview].at(ibunch);
	      cout << "bunch= " << thebunch  << " Ntrack[iview][thebunch] = " << cellauto->Ntrack[iview][thebunch] << '\n';
	      for(int itrack=0; itrack<cellauto->Ntrack[iview][thebunch]; itrack++)
		{
		  trackid = itrack;
		  NHit = cellauto->reconcluster[iview][thebunch][themod][itrack]->cluster.size();
		  
		  for(int ihit=0; ihit<cellauto->reconcluster[iview][thebunch][themod][itrack]->cluster.size(); ihit++) 
		    {
		      dposx = cellauto->reconcluster[iview][thebunch][themod][itrack]->cluster.at(ihit)->posx;
		      dposy = cellauto->reconcluster[iview][thebunch][themod][itrack]->cluster.at(ihit)->posy;
		      dposz = cellauto->reconcluster[iview][thebunch][themod][itrack]->cluster.at(ihit)->posz;
		      charge = cellauto->reconcluster[iview][thebunch][themod][itrack]->cluster.at(ihit)->HG;
		      hittime = cellauto->reconcluster[iview][thebunch][themod][itrack]->cluster.at(ihit)->Htime;

		      cout << "posx= " << dposx << " posy= " << dposy << " posz= " << dposz << " bunch= " << thebunch  
			   << "charge= " << charge << " hittime= " << hittime  << '\n';
		      
		      detrecon->posx[imod][iview][thebunch][itrack][ihit]=dposx;
		      detrecon->posy[imod][iview][thebunch][itrack][ihit]=dposy;
		      detrecon->posz[imod][iview][thebunch][itrack][ihit]=dposz;
		      detrecon->charge[imod][iview][thebunch][itrack][ihit]=charge;
		      detrecon->hittime[imod][iview][thebunch][itrack][ihit]=hittime;

		      if(ihit==0)
			{
			  detrecon->iposx[imod][iview][thebunch][itrack]=dposx;
			  detrecon->iposy[imod][iview][thebunch][itrack]=dposy;
			  detrecon->iposz[imod][iview][thebunch][itrack]=dposz;
			}

		      if(ihit==cellauto->reconcluster[iview][thebunch][themod][itrack]->cluster.size()-1)
			{
			  detrecon->fposx[imod][iview][thebunch][itrack]=dposx;
			  detrecon->fposy[imod][iview][thebunch][itrack]=dposy;
			  detrecon->fposz[imod][iview][thebunch][itrack]=dposz;
			}

		    }//ihit

		  detrecon->bunch[imod][iview][thebunch][itrack]=thebunch;
		  detrecon->trackid[imod][iview][thebunch][itrack]=trackid;
		  detrecon->Nhit[imod][iview][thebunch][itrack]=NHit;

		}//itrack

	      detrecon->Ntrack[imod][iview][thebunch] = cellauto->Ntrack[iview][thebunch];
	      cout << "Ntrack= " << cellauto->Ntrack[iview][thebunch] <<'\n';
	    }//ibunch
	    }//iview	  
	}//mod
      
      detrecon->entry=ientry;
      otree->Fill();
    }//ientry

  otree->Write();
  fout->Close();

  clock_t end = clock();
  const double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
  printf("Running Time %lf[s]\n", time/1000.);
#endif

#ifdef Single

  const int ncanvas[2] = {(int)cellauto->ataribunch[0].size(), (int)cellauto->ataribunch[1].size()};
  TCanvas *canvas_side[ncanvas[0]];
  TCanvas *canvas_top[ncanvas[1]];

  for(int iview=0; iview<2; iview++)
    {
      cout << "ataribunch[0]= " << cellauto->ataribunch[0].size() << '\n';
      cout << "ataribunch[1]= " << cellauto->ataribunch[1].size() << '\n';

      if(ncanvas[iview]==0)
	{
	  cout << "No bunch " << '\n'; 
	  continue;
	}
      
      for(int ican=0; ican<ncanvas[iview]; ican++)
	{
	  TString canvasname;
	  if(iview==0)
	    {
	      canvasname.Form("canvasside_%d_%d",iview, ican);
	      canvas_side[ican] = new TCanvas(canvasname, canvasname, 1500, 500);
	      canvas_side[ican]->Divide(3, 1);
	    }
	  if(iview==1)
	    {
	      canvasname.Form("canvastop_%d_%d",iview, ican);
	      canvas_top[ican] = new TCanvas(canvasname, canvasname, 1500, 500);
	      canvas_top[ican]->Divide(3, 1);
	    }
	  
	  int thebunch = cellauto->ataribunch[iview].at(ican);
	  
	  for(int itrack=0; itrack<cellauto->Ntrack[iview][thebunch]; itrack++)
	    {
	      Nhit[iview][thebunch][itrack] = cellauto->reconcluster[iview][thebunch][targetmod][itrack]->cluster.size();
	      cout << "bunch= " << thebunch  << " Nhit[itrack]= " << Nhit[iview][thebunch][itrack] << '\n';
	      for(int ihit=0; ihit<Nhit[iview][thebunch][itrack]; ihit++)
		{
		  if(iview==0)
		    reconposxy[iview][thebunch][itrack][ihit] 
		      = cellauto->reconcluster[iview][thebunch][targetmod][itrack]->cluster.at(ihit)->posy;

		  if(iview==1)
		    reconposxy[iview][thebunch][itrack][ihit] 
		      = cellauto->reconcluster[iview][thebunch][targetmod][itrack]->cluster.at(ihit)->posx;

		  reconposz[iview][thebunch][itrack][ihit] 
		    = cellauto->reconcluster[iview][thebunch][targetmod][itrack]->cluster.at(ihit)->posz;
		  cout << "ihit= " << ihit << " " << reconposxy[iview][thebunch][itrack][ihit] 
		       << " " << reconposz[iview][thebunch][itrack][ihit]  
		       << " " << cellauto->reconcluster[iview][thebunch][targetmod][itrack]->cluster.at(ihit)->Htime
		       << '\n'; 
		}

	      recontrack[iview][thebunch][itrack] = new TGraph(Nhit[iview][thebunch][itrack], 
							       reconposz[iview][thebunch][itrack], 
							       reconposxy[iview][thebunch][itrack]);
	      recontrack[iview][thebunch][itrack]->SetMaximum(1500);
	      recontrack[iview][thebunch][itrack]->SetMinimum(-1500);
	      recontrack[iview][thebunch][itrack]->GetXaxis()->SetLimits(-500.,4500);
	      recontrack[iview][thebunch][itrack]->SetMarkerColor(itrack+2);
	      recontrack[iview][thebunch][itrack]->SetMarkerSize(1.0);
	      recontrack[iview][thebunch][itrack]->SetMarkerStyle(22);
	    }

	  if(iview==0)
	    {
	      canvas_side[ican]->cd(1);
	      cellauto->beforerecon[iview][thebunch]->Draw("box");
	      
	      canvas_side[ican]->cd(2);
	      cellauto->midrecon[iview][thebunch]->Draw("box");
	  
	      canvas_side[ican]->cd(3);
	      for(int itrack=0; itrack<cellauto->Ntrack[iview][thebunch]; itrack++)
		{   
		  if(itrack==0)
		    recontrack[iview][thebunch][itrack]->Draw("AP");
		  if(itrack>=1)
		    recontrack[iview][thebunch][itrack]->Draw("P,same");
		}
	      canvas_side[ican]->Update();
	    }

	  if(iview==1)
	    {
	      canvas_top[ican]->cd(1);
	      cellauto->beforerecon[iview][thebunch]->Draw("box");
	      
	      canvas_top[ican]->cd(2);
	      cellauto->midrecon[iview][thebunch]->Draw("box");
	  
	      canvas_top[ican]->cd(3);
	      for(int itrack=0; itrack<cellauto->Ntrack[iview][thebunch]; itrack++)
		{   
		  if(itrack==0)
		    recontrack[iview][thebunch][itrack]->Draw("AP");
		  if(itrack>=1)
		    recontrack[iview][thebunch][itrack]->Draw("P,same");
		}
	      canvas_top[ican]->Update();
	    }

	}//ican
      cout << "NBunch= " << cellauto->ataribunch[iview].size() << '\n';
    }//iview
  
  app.Run();
#endif


  return 0;
  
}//main
