#include <iostream>
#include <stdio.h>
#include <vector>

#include <TString.h>
#include <TTree.h>
#include <TFile.h>
#include <TApplication.h>

//include
#include "babymind.cpp"
#include "matching.cpp"
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

  vector<int> particlelist;
  int inttype;
  double totcrsne, norm, nuE;
  vector<double>ipos[4], fpos[4], momentum[4];
  vector<double>absmomentum;

  bool fvcut[6][2];
  bool fccut[6][2];

  int fvfcevent = 0;
  int trackingeff = 0;

  double finalposxy[2];
  double finalposz[2];
  double extrapolatexy[2];
  vector<double> trueextrapolatexy[2];

  int pmntrack[2];
  int bmntrack[2];

  for(int ientry=0; ientry<200; ientry++)
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
	      //Track loop
	      cout << "pmntrack= " << pmntrack[iview] << '\n';
	      for(int itrack=0; itrack<pmntrack[iview]; itrack++)
		{
		  if(iview==0)
		    matching->CalcSlope(targetmod, iview, detrecon->posz[targetmod][iview][bunch][itrack],
					detrecon->posy[targetmod][iview][bunch][itrack]);
		  if(iview==1)
		    matching->CalcSlope(targetmod, iview, detrecon->posz[targetmod][iview][bunch][itrack],
					detrecon->posx[targetmod][iview][bunch][itrack]);
		  
		  matching->Extrapolation(targetmod, iview, finalposxy[iview], &extrapolatexy[iview]);
		  
		  if(matching->InBM(targetmod, iview, extrapolatexy[iview]))
		    {
		      bmflag[iview] = true;
		      trueextrapolatexy[iview].push_back(extrapolatexy[iview]);
		    }
		}//itrack

	      for(int jtrack=0; jtrack<trueextrapolatexy[iview].size(); jtrack++)
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
		  }//jitrack
	    }//iview

	  if(bmmatchflag[0] && bmmatchflag[1])
	    trackingeff++;
	  
	}//fv & fc
    }


  cout << "TrackingEff= " << trackingeff << "/" << fvfcevent << '\n';

   
#ifdef display
  theapp.Run();
#endif 

  return 0;
  
}


