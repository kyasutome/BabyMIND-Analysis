#include <iostream>
#include <stdio.h>
#include <vector>

#include <TString.h>
#include <TTree.h>
#include <TFile.h>
#include <TApplication.h>

//include
#include "babymind.cpp"
#include "tracking.cpp"

//library
#include "EVTCluster.hpp"
#include "DetRecon.hpp"
#include "BMDisp.hpp"
#include "MCRecon.hpp"
#include "MCTrue.hpp"

using namespace std;
//#define display

int main( int argc, char **argv )
{
  std::string name = string(argv[1]);
  TString filename(name);
  TString histname;

#ifdef display
  TApplication theapp("theapp", 0, 0, 0, 0);
#endif

  EVTCluster* evtcluster = new EVTCluster();
  DetRecon* detrecon = new DetRecon();
  MCTrue* mctrue = new MCTrue();
  BabyMIND* babymind = new BabyMIND();
  Matching* matching = new Matching();
  Tracking* tracking = new Tracking();

  TFile *fin = new TFile(filename, "Read");
  TTree *tree = (TTree*)fin->Get("tree");
  tree->SetBranchAddress("EVTCluster", &evtcluster);
  tree->SetBranchAddress("DetRecon", &detrecon);
  tree->SetBranchAddress("MCTrue", &mctrue);
  cout << tree->GetEntries() << '\n';

  TFile *fout = new TFile("${processdir}/result/DetPerform/trackmatching_mc.root", "RECREATE");
  TTree *otree = new TTree("tree", "tree");
  double numerator[10];
  otree->Branch("numerator", numerator, "numerator[10]/D");
  double denomenator[10];
  otree->Branch("denomenator", denomenator, "denomenator[10]/D");

  vector<int> particlelist;
  int inttype;
  double totcrsne, norm, nuE;
  vector<double>ipos[4], fpos[4], momentum[4];
  vector<double>absmomentum;

  vector<int>matchingtrack;
  vector<int>nomatchingtrack;

  bool fvcut[6][2];
  bool fccut[6][2];

  int fvfcevent = 0;
  int trackingeff = 0;

  double finalposxy[2][20];
  vector<double> finalposxy_candidate[2][20];
  double finalposz[2];
  double extrapolatexy[2];
  vector<double> trueextrapolatexy[2];

  int pmntrack[2];
  int bmntrack[2];
  double angle[2];
  double d[3];
  double scattering;

  int trackmatching[10];
  for(int i=0; i<10; i++)
    trackmatching[i] = 0;

  int Tmatching[10];
  for(int i=0; i<10; i++)
    Tmatching[i] = 0;

  double dangle = 1/10.;
 
  matchingtrack.clear();
  nomatchingtrack.clear();

  for(int ientry=0; ientry<34000; ientry++)
    {
      bool bmflag[2] ={false, false};
      bool bmmatchflag[2] ={false, false};
      bool bmhitmatchflag[2] ={false, false};

      for(int imod=0; imod<6; imod++)
	for(int iview=0; iview<2; iview++)
	  {
	    fvcut[imod][iview]=false;
	    fccut[imod][iview]=false;
	  }

      for(int i=0; i<4; i++)
	{
	  ipos[i].clear();
	  fpos[i].clear();
	  momentum[i].clear();
	}

      absmomentum.clear();
      particlelist.clear();
      tree->GetEntry(ientry);
      inttype = mctrue->inttype;

      for(int iview=0; iview<2; iview++)
	{
	  bmntrack[iview] = detrecon->Ntrack[5][iview][1];
	  pmntrack[iview] = detrecon->Ntrack[0][iview][1];

	  trueextrapolatexy[iview].clear();
	  for(int itrack=0; itrack<20; itrack++)
	    {
	      finalposxy_candidate[iview][itrack].clear();	      
	      finalposxy[iview][itrack]=0;
	    }
	}
      
      tracking->SearchParticle(13, mctrue, &particlelist);
      //cout << "ientry= " << ientry << " "  << particlelist.size() << " inttype= " << inttype  << '\n';

      for(int ipar=0; ipar<particlelist.size(); ipar++)
	{
	  for(int i=0; i<3; i++)
	    {
	      int parid = particlelist.at(ipar);
	      ipos[i].push_back(mctrue->ipos[i][parid]*10);
	      fpos[i].push_back(mctrue->fpos[i][parid]*10);
	      momentum[i].push_back(mctrue->momentum[i][parid]*1000);
	    }
	  absmomentum.push_back(sqrt( pow(momentum[0].at(0),2)+pow(momentum[1].at(0),2)+pow(momentum[2].at(0),2) ));
	}

      if(ipos[0].size()==1)
	{
	  /*
	  cout << "ipos[2]= " << ipos[2].at(0) << " fpos[2]= " << fpos[2].at(0) 
	       << " Pmu= " << momentum[0].at(0) << " " << momentum[1].at(0) << " "  << momentum[2].at(0) 
	       << " AbsPmu= " << absmomentum.at(0) << '\n';
	  */
	  
	  for(int iview=0; iview<2; iview++)
	    {
	      if(iview==0)
		{
		  fvcut[0][0]=tracking->FVcut(0, iview, ipos[2].at(0), ipos[1].at(0));
		  //cout << "ientry=" << ientry  << " ipos[2]= " << ipos[2].at(0) 
		  //   << " ipos[1]= " << ipos[1].at(0) << " " << fvcut[0][iview]  << '\n';
		  fccut[5][0]=tracking->FCcut(5, iview, fpos[2].at(0), fpos[1].at(0));
		  //cout << "FC "  << "fpos[2]= " << fpos[2].at(0) << " fpos[1]= " << fpos[1].at(0) << " " << fccut[5][iview]  << '\n';
		}
	      if(iview==1)
		{
		  fvcut[0][1]=tracking->FVcut(0, iview, ipos[2].at(0), ipos[0].at(0));
		  //cout << "ientry=" << ientry  << " ipos[2]= " << ipos[2].at(0) 
		  //   << " ipos[1]= " << ipos[0].at(0) << " " << fvcut[0][iview]  << '\n';
		  fccut[5][1]=tracking->FCcut(5, iview, fpos[2].at(0), fpos[0].at(0));
		  //cout << "FC " << "fpos[2]= " << fpos[2].at(0) << " fpos[0]= " << fpos[0].at(0) << " " << fccut[5][iview]  << '\n';
		}
	    }//iview
	}

      if(fvcut[0][0] && fvcut[0][1] && fccut[5][0] && fccut[5][1])
	{
	  cout << "ientry= " << ientry << '\n';
	  fvfcevent++;

	  //Matching Check
	  int targetmod = 0;
	  int bunch = 1;

	  for(int iview=0; iview<2; iview++)
	    {
	      double posz, posxy;
	      for(int itrack=0; itrack<pmntrack[iview]; itrack++)
		{
		  int nhit = detrecon->Nhit[targetmod][iview][bunch][itrack];
		  for(int ihit=0; ihit<nhit; ihit++)
		    {
		      posz = detrecon->posz[targetmod][iview][bunch][itrack][ihit];
		      if(iview==0)
			posxy = detrecon->posy[targetmod][iview][bunch][itrack][ihit];
		      if(iview==1)
			posxy = detrecon->posx[targetmod][iview][bunch][itrack][ihit];
		
		      // cout << "posxy= " << posxy << '\n';
		      if(fabs(posz-matching->posfinalpln[targetmod][iview])<300)
			finalposxy_candidate[iview][itrack].push_back(posxy);
		      
		    }//ihit
		}//itrack 

	      //Track loop
	      cout << "iview= " << iview  << " pmntrack= " << pmntrack[iview] << '\n';
	      for(int itrack=0; itrack<pmntrack[iview]; itrack++)
		{
		  if(iview==0)
		    matching->CalcSlope(targetmod, iview, detrecon->posz[targetmod][iview][bunch][itrack],
					detrecon->posy[targetmod][iview][bunch][itrack]);
		  if(iview==1)
		    matching->CalcSlope(targetmod, iview, detrecon->posz[targetmod][iview][bunch][itrack],
					detrecon->posx[targetmod][iview][bunch][itrack]);

		  for(int i=0; i<finalposxy_candidate[iview][itrack].size(); i++)
		    {
		      finalposxy[iview][itrack]
			+= finalposxy_candidate[iview][itrack].at(i)/finalposxy_candidate[iview][itrack].size();
		    }
		  
		  matching->Extrapolation(targetmod, iview, finalposxy[iview][itrack], &extrapolatexy[iview]);
		  
		  cout << "finalposxy= " << finalposxy[iview][itrack] << " extrapolate= " << extrapolatexy[iview]  << '\n';

		  /*
		  if(matching->InBM(targetmod, iview, extrapolatexy[iview]))
		    {
		    }
		  */

		  bmflag[iview] = true;
		  trueextrapolatexy[iview].push_back(extrapolatexy[iview]);
		}//itrack

	      cout << "bmntrack= " << bmntrack[iview] << '\n';

	      for(int jtrack=0; jtrack<trueextrapolatexy[iview].size(); jtrack++)
		{
		  for(int itrack=0; itrack<bmntrack[iview]; itrack++)
		    {
		      if(iview==0)
			{
			  if(matching->Matchingbm(iview, itrack, trueextrapolatexy[iview].at(jtrack),
						  detrecon->posz[5][iview][bunch][itrack],
						  detrecon->posy[5][iview][bunch][itrack]))
			    
			    bmmatchflag[iview] = true;
			}
		      
		      if(iview==1)
			{
			  if(matching->Matchingbm(iview, itrack, trueextrapolatexy[iview].at(jtrack),
						  detrecon->posz[5][iview][bunch][itrack],
						  detrecon->posx[5][iview][bunch][itrack]))
			    bmmatchflag[iview] = true;			  
			}
		    }

		  angle[iview] = TMath::Tan(matching->slope[0][iview]);

		  }//jitrack
	    }//iview

	  if(bmmatchflag[0] && bmmatchflag[1])
	    {
	      trackingeff++;
	      matchingtrack.push_back(ientry);
	      d[0] = angle[1];
	      d[1] = angle[0];
	      d[2] = 1;
	      scattering = 1/sqrt(d[0]*d[0]+d[1]*d[1]+d[2]*d[2]);
	      cout << "True Angle="  << TMath::ACos(scattering)*180/3.14 << '\n';
	      cout << "True Angle="  << scattering << '\n';

	      for(int i=0; i<20; i++)
		{
		  if(dangle*i< scattering && scattering<=dangle*(i+1))
		    {
		      trackmatching[i] ++;
		      Tmatching[i] ++;
		      break;
		    }
		}
	    }

	  if(!bmmatchflag[0] || !bmmatchflag[1])
	    {
	      nomatchingtrack.push_back(ientry);
	      for(int i=0; i<20; i++)
		{
		  if(dangle*i< scattering && scattering<=dangle*(i+1))
		    {
		      Tmatching[i] ++;
		      break;
		    }
		}
	    }
	  
	}//fv & fc
    }

  for(int i=0; i<nomatchingtrack.size(); i++)
    {
      cout << "ientry= " << nomatchingtrack.at(i) << '\n';
    }
  /*
  cout << "TrackingEff= " << trackingeff << "/" << fvfcevent << " = " 
       << trackingeff/(double)fvfcevent*100 << "%"  << '\n';
  */

  for(int i=0; i<10; i++)
    {
      cout << "TrackingEff= " << trackmatching[i] << "/" << Tmatching[i] << " = " 
	   << trackmatching[i]/(double)Tmatching[i]*100 << "%"  << '\n';
      numerator[i] =  trackmatching[i];
      denomenator[i] =  Tmatching[i];
    }

  fout->cd();
  otree->Fill();
  otree->Write();
  fout->Close();
  fin->Close();
   
#ifdef display
  theapp.Run();
#endif 

  return 0;
  
}


