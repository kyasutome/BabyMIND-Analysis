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

//library
#include "EVTCluster.hpp"
#include "DetRecon.hpp"
#include "BMDisp.hpp"

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
  BabyMIND* babymind = new BabyMIND();
  Matching* matching = new Matching();

  TFile *fin = new TFile(filename, "Read");
  TTree *tree = (TTree*)fin->Get("tree");
  tree->SetBranchAddress("EVTCluster", &evtcluster);
  tree->SetBranchAddress("DetRecon", &detrecon);
  cout << tree->GetEntries() << '\n';

  int tracksample[20];
  for(int itrack=0; itrack<20; itrack++)
    tracksample[itrack]=0;
  vector<int> activepln[2][9];
  double finalposxy[2][9];
  double finalposz[2][9];
  vector<double> finalposxy_candidate[2][9];
  double extrapolatexy[2][9];
  vector<double> pmposz[2][9];
  vector<double> pmposxy[2][9];

  int bmntrack[2][9];
  int wgntrack[2][9];
  double startxyatbm[2][20];

  vector<double> bmposz[2][9];
  vector<double> bmposxy[2][9];

  int matching_total[6]={0, 0, 0, 0, 0, 0};
  int matching_eff[6]={0, 0, 0, 0, 0, 0};

  vector<int> trackmatching[2];
  vector<int> notrackhitmatching[2];
  vector<int> notrackmatching[2];

  for(int i=0; i<2; i++)
    {
      trackmatching[i].clear();
      notrackhitmatching[i].clear();
      notrackmatching[i].clear();
    }

  //for(int ientry=0; ientry<tree->GetEntries(); ientry++)
  for(int ientry=0; ientry<14300; ientry++)
    {
      tree->GetEntry(ientry);

      for(int iview=0; iview<2; iview++)
        for(int ibunch=0; ibunch<9; ibunch++)
          {
            activepln[iview][ibunch].clear();
	    pmposz[iview][ibunch].clear();
	    pmposxy[iview][ibunch].clear();
	    finalposxy_candidate[iview][ibunch].clear();
	    finalposxy[iview][ibunch]=0;
	    extrapolatexy[iview][ibunch]=0;
	  
	    bmposz[iview][ibunch].clear();
	    bmposxy[iview][ibunch].clear();
          }

      int targetmod = 0;
      int thebunch = -1;
      int ntrack;
      int bunch;
      int nhit;
      vector<int> ataribunch[2];
      ataribunch[0].clear();
      ataribunch[1].clear();
      
      for(int ibunch=1; ibunch<9; ibunch++)
	{

	  bool penflag[2] ={false, false};
	  bool bmflag[2] ={false, false};
	  bool bmmatchflag[2] ={false, false};
	  bool bmhitmatchflag[2] ={false, false};

	  for(int iview=0; iview<2; iview++)
	    {
	      double posxy, posz;
	      ntrack = detrecon->Ntrack[targetmod][iview][ibunch];
	      if(ntrack>=0)
		tracksample[ntrack]++;
	      if(ntrack!=1) continue;

	      for(int ihit=0; ihit<evtcluster->mod.size(); ihit++)
		{
		  int bmbunch = evtcluster->bunch.at(ihit);
		  int bmmod = evtcluster->mod.at(ihit);
		  int bmview = evtcluster->view.at(ihit);
		  double bmxpos = evtcluster->dposx.at(ihit);
		  double bmypos = evtcluster->dposy.at(ihit);
		  double bmzpos = evtcluster->dposz.at(ihit);
		  if(bmbunch!=ibunch) continue;
		  if(bmmod!=5) continue;

		  bmposz[bmview][bmbunch].push_back(bmzpos);
		  if(bmview==0)
		    bmposxy[bmview][bmbunch].push_back(bmypos);
		  if(bmview==1)
		    bmposxy[bmview][bmbunch].push_back(bmxpos);

		}

	      nhit = detrecon->Nhit[targetmod][iview][ibunch][0];
	      ataribunch[iview].push_back(ibunch);
	      thebunch = ibunch;
	      bmntrack[iview][ibunch] = detrecon->Ntrack[5][iview][ibunch];
	      wgntrack[iview][ibunch] = detrecon->Ntrack[2][iview][ibunch];

	      if(nhit<=10 || wgntrack[iview][ibunch]==0)
		continue;	      

	      for(int ihit=0; ihit<nhit; ihit++)
		{
		  bool fillflag = true;
		  posz = detrecon->posz[targetmod][iview][ibunch][0][ihit];
		  if(iview==0)
		    posxy = detrecon->posy[targetmod][iview][ibunch][0][ihit];
		  if(iview==1)
		    posxy = detrecon->posx[targetmod][iview][ibunch][0][ihit];
		  //cout << "posz= " << posz << '\n';
		  activepln[iview][ibunch].push_back(posz);
		  
		  if(fabs(posz-matching->posfinalpln[targetmod][iview])<20)
		    finalposxy_candidate[iview][ibunch].push_back(posxy);
		  
		}//ihit 

	    std::sort(activepln[iview][ibunch].begin(), activepln[iview][ibunch].end());
            auto last =  std::unique(activepln[iview][ibunch].begin(),activepln[iview][ibunch].end());
            activepln[iview][ibunch].erase(last, activepln[iview][ibunch].end());
	    //cout << "#ofpln= " << activepln[iview][ibunch].size() << '\n';
	    finalposz[iview][ibunch] = activepln[iview][ibunch].at(activepln[iview][ibunch].size()-1);
	    //cout << "finalpos= " << finalposz[iview][ibunch] << '\n';

	    if(matching->JudgePenetrate(targetmod, iview, finalposz[iview][ibunch]))
	      {
		penflag[iview] = true;
		for(int i=0; i<finalposxy_candidate[iview][ibunch].size(); i++)
		  {
		    finalposxy[iview][ibunch] 
		      += finalposxy_candidate[iview][ibunch].at(i)/finalposxy_candidate[iview][ibunch].size();
		  }

		if(iview==0)
		  matching->CalcSlope(targetmod, iview, detrecon->posz[targetmod][iview][ibunch][0],
				      detrecon->posy[targetmod][iview][ibunch][0]);
		if(iview==1)
		  matching->CalcSlope(targetmod, iview, detrecon->posz[targetmod][iview][ibunch][0],
				      detrecon->posx[targetmod][iview][ibunch][0]);

		//cout << "finalposz = " <<finalposz[iview][ibunch] << " finalposxy[iview][ibunch]= "
		//   << finalposxy[iview][ibunch] << '\n';

		matching->Extrapolation(targetmod, iview, finalposxy[iview][ibunch], &extrapolatexy[iview][ibunch]);
		//cout << "Extrapolate= " << extrapolatexy[iview][ibunch] << '\n';
		
	      }//if penetrate
	    
	  }//iview

      if(thebunch!=-1 && penflag[0] && penflag[1])
	{
	  for(int iview=0; iview<2; iview++)
	    {	      
	      if(matching->InBM(targetmod, iview, extrapolatexy[iview][thebunch]))
		bmflag[iview] = true;

	      if(!matching->InBM(targetmod, iview, extrapolatexy[iview][thebunch]))
		continue;
	      
	      for(int itrack=0; itrack<bmntrack[iview][thebunch]; itrack++)
		{		
		  cout << "ientry= " << ientry << " iview= " << iview << " ibunch= " << thebunch << '\n';
		  if(iview==0)
		    {
		      if(matching->Matchingbm(iview, itrack, extrapolatexy[iview][thebunch], 
					      detrecon->posz[5][iview][thebunch][itrack],
					      detrecon->posy[5][iview][thebunch][itrack]))
			  bmmatchflag[iview] = true;
		    }		  
		  
		  if(iview==1)
		    {
		      if(matching->Matchingbm(iview, itrack, extrapolatexy[iview][thebunch], 
					      detrecon->posz[5][iview][thebunch][itrack],
					      detrecon->posx[5][iview][thebunch][itrack]))
			bmmatchflag[iview] = true;	
		      
		    }			
		}

	      if(iview==0)
		if(bmmatchflag[iview]==false)		    
		  if(matching->SearchMatchHit(iview, thebunch, extrapolatexy[iview][thebunch],
					      bmposz[iview][thebunch], bmposxy[iview][thebunch]))
		    bmhitmatchflag[iview] = true;
	      
	      if(iview==1)
		if(bmmatchflag[iview]==false)		    
		  if(matching->SearchMatchHit(iview, thebunch, extrapolatexy[iview][thebunch], 
					      bmposz[iview][thebunch], bmposxy[iview][thebunch]))
		    bmhitmatchflag[iview] = true;
	      
	    }
	  
	  if(bmflag[0] && bmflag[1])
	    {
	      matching_total[targetmod]++;

	      if(!((bmmatchflag[0] || bmhitmatchflag[0]) && (bmmatchflag[1] || bmhitmatchflag[1])))
		{
		 
		  cout << "ientry= " << ientry << " ibunch= " << ibunch  << '\n';
		  cout << "finalposz = " <<finalposz[0][thebunch] << " finalposxy[iview][ibunch]= "
		       << finalposxy[0][thebunch] << '\n';
		  cout << "finalposz = " <<finalposz[1][thebunch] << " finalposxy[iview][ibunch]= "
		       << finalposxy[1][thebunch] << '\n';
		  cout << "Extrapolate= " << extrapolatexy[0][thebunch] << " " << extrapolatexy[1][thebunch]  << '\n';
		  cout << "bmntrack= " << bmntrack[0][thebunch] << " " << bmntrack[1][thebunch] << '\n';

		  for(int iview=0; iview<2; iview++)
		    {
		      for(int itrack=0; itrack<bmntrack[iview][ibunch]; itrack++)
			cout << "iview= " << iview  << " itrack= " << itrack  
			     << " aveposxy= " << matching->aveposxy[iview][itrack] << '\n';
		    }
		  cout << '\n';

		  notrackmatching[0].push_back(ientry);
		  notrackmatching[1].push_back(bunch);
		  
		}
	    }
	  
	  if( bmmatchflag[0] && bmmatchflag[1] )
	    {
	      matching_eff[targetmod]++;
	      trackmatching[0].push_back(ientry);
	      trackmatching[1].push_back(bunch);
	    }

	  else if( (bmmatchflag[0] || bmhitmatchflag[0]) && (bmmatchflag[1] || bmhitmatchflag[1]) )
	    {
	      matching_eff[targetmod]++;
	      notrackhitmatching[0].push_back(ientry);
	      notrackhitmatching[1].push_back(bunch);
	    }
	    
	}//bmflag[0][1]

	}//ibunch
     
    }//ientry

  for(int i=0; i<notrackmatching[0].size(); i++)
    {
      cout << notrackmatching[0].at(i) << '\n';
    }
  
  cout << "1 track sample= " << tracksample[1] << '\n';
  cout << "Total Matching Candidates= " 
       <<  trackmatching[0].size()+notrackhitmatching[0].size()+notrackmatching[0].size() << '\n';
  cout << "trackmatching= " << trackmatching[0].size() << '\n';
  cout << "notrack hitmatching= " << notrackhitmatching[0].size() << '\n';
  cout << "notrackmatching= " << notrackmatching[0].size() << '\n';
  
  
  cout << "matching/total= " << matching_eff[0] << "/"  << matching_total[0]
       << " matching efficiency= " << (double)matching_eff[0]/matching_total[0]*100 << "%" << '\n';
  
   
#ifdef display
  theapp.Run();
#endif 

  return 0;
  
}


