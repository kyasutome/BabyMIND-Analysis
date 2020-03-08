#include <iostream>
#include <stdio.h>
#include <vector>

#include <TString.h>
#include <TTree.h>
#include <TFile.h>
#include <TApplication.h>

//include
#include "babymind.cpp"

//library
#include "EVTCluster.hpp"
#include "DetRecon.hpp"
#include "BMDisp.hpp"

using namespace std;

int main( int argc, char **argv )
{
  std::string name = string(argv[1]);
  TString filename(name);
  TString histname;

  vector<int> activepln[2][9];

  EVTCluster* evtcluster = new EVTCluster();
  DetRecon* detrecon = new DetRecon();
  BabyMIND* babymind = new BabyMIND();

  for(int iview=0; iview<2; iview++)
    for(int ibunch=0; ibunch<9; ibunch++)
      {
	activepln[iview][ibunch].clear();
      }

  int counttotal[2][20];
  int counteff[2][20];

  int countyasutotal[2][2];
  int countyasueff[2][2];

  vector<int> yasu_hittime[2][9];
  vector<int> yasu_channel[2][9];
  double originalhittime[2][9];

  for(int iview=0; iview<2; iview++)
    for(int ipln=0; ipln<20; ipln++)
      {
	counttotal[iview][ipln]=0;
	counteff[iview][ipln]=0;
      }

  TFile *fin = new TFile(filename, "Read");
  TTree *tree = (TTree*)fin->Get("tree");
  tree->SetBranchAddress("EVTCluster", &evtcluster);
  tree->SetBranchAddress("DetRecon", &detrecon);
  cout << tree->GetEntries() << '\n';

  int tracksample[20];
  //for(int ientry=0; ientry<3000; ientry++)
  for(int ientry=0; ientry<tree->GetEntries(); ientry++)
    {
      for(int iview=0; iview<2; iview++)
	for(int ibunch=0; ibunch<9; ibunch++)
	  {
	    activepln[iview][ibunch].clear();
	    yasu_hittime[iview][ibunch].clear();
	    yasu_channel[iview][ibunch].clear();
	    originalhittime[iview][ibunch]=0;
	  }

      tree->GetEntry(ientry);
      
      int targetmod = 5;
      int ntrack;
      int bunch;
      int nhit;
      vector<int> ataribunch[2];
      ataribunch[0].clear();
      ataribunch[1].clear();

      for(int ihit=0; ihit<evtcluster->mod.size(); ihit++)
	{
	  int yasubunch = evtcluster->bunch.at(ihit);
	  if(yasubunch<=0) continue;
	  int yasumod = evtcluster->mod.at(ihit);
	  if(yasumod!=6) continue;
	  int yasuchannel = evtcluster->channel.at(ihit);
	  int yasuhittime = evtcluster->Htime.at(ihit);
	  int yasuplane = evtcluster->pln.at(ihit)-19;

	  //cout << "yasubunch= " << yasubunch << " yasumod= " << yasumod
	  //   << " yasupln= " << yasupln << " yasuchannel= " << yasuchannel << " hittime= " << yasuhittime  << '\n';

	  yasu_hittime[yasuplane][yasubunch].push_back(yasuhittime);
	  yasu_channel[yasuplane][yasubunch].push_back(yasuchannel);
	}

      for(int ibunch=1; ibunch<9; ibunch++)
	for(int iview=0; iview<2; iview++)
	  {
	    double posxy, posz;
	    ntrack = detrecon->Ntrack[targetmod][iview][ibunch];
	    if(ntrack>=0)
	      tracksample[ntrack]++;
	    if(ntrack!=1) continue;

	    nhit = detrecon->Nhit[targetmod][iview][ibunch][0];
	    //cout << "ientry= " << ientry  << " ibunch= " << ibunch  << " Nhit= " << nhit << '\n';
	    ataribunch[iview].push_back(ibunch);
	    
	    for(int ihit=0; ihit<nhit; ihit++)
	      {
		bool fillflag = true;
		posz = detrecon->posz[targetmod][iview][ibunch][0][ihit];
		originalhittime[iview][ibunch] += (detrecon->hittime[targetmod][iview][ibunch][0][ihit])/nhit;

		//cout << "ibunch= " << ibunch << " originalhittime= " << originalhittime[iview][ibunch] << '\n';

		for(int jhit=0; jhit<activepln[iview][ibunch].size(); jhit++)
		  {
		    double ref = activepln[iview][ibunch].at(jhit);
		    if(fabs(posz-ref)<=35)
		      {
			fillflag = false;
			break;
		      }
		  }

		if(fillflag)
		  {
		    activepln[iview][ibunch].push_back(posz);
		    //cout << "ihit= " << ihit << " posz= " << posz << '\n';
		  }
	      }//ihit

	    std::sort(activepln[iview][ibunch].begin(), activepln[iview][ibunch].end());
	    auto last =  std::unique(activepln[iview][ibunch].begin(),activepln[iview][ibunch].end());
	    activepln[iview][ibunch].erase(last, activepln[iview][ibunch].end());
	    if(activepln[iview][ibunch].size()>=18)
	      {
		//cout << "#ofpln= " << activepln[iview][ibunch].size() << '\n';
		for(int ihit=0; ihit<activepln[iview][ibunch].size(); ihit++)
		  {
		    //cout << activepln[iview][ibunch].at(ihit) << '\n';
		  }
	      }

	    for(int ibunch=0; ibunch<ataribunch[iview].size(); ibunch++)
	      {
		int thebunch = ataribunch[iview].at(ibunch);
		if(activepln[iview][thebunch].size()<=10) continue;
		
		for(int iplane=2; iplane<=17; iplane++)
		  {
		    babymind->CalcDetEff(iplane, activepln[iview][thebunch], 
					 &counttotal[iview][iplane], &counteff[iview][iplane]);
		  }
	      }      

	  }//iview           

      
      //YASU Detection Efficiency
      
      if(ataribunch[0].size()==ataribunch[1].size())
	for(int ibunch=0; ibunch<ataribunch[0].size(); ibunch++)
	  {
	    int sidebunch = ataribunch[0].at(ibunch);
	    int topbunch = ataribunch[1].at(ibunch);
	    
	    if(sidebunch==topbunch)
	      {
		
		int lr = babymind->JudgeLeftRight(detrecon->posx[targetmod][1][topbunch][0]);
		
		//cout << "LeftRight= " << babymind->JudgeLeftRight(detrecon->posx[targetmod][1][topbunch][0]) << '\n';
		//cout << "ientry= " << ientry << " ibunch= " << topbunch << '\n';
		
		babymind->ConverttoPln(activepln[0][sidebunch]);
		//cout << "plane size= " << babymind->plane.size() << '\n';
		for(int iyasu=0; iyasu<2; iyasu++)
		  {
		    if(babymind->SearchThePln(1) && babymind->SearchThePln(2))
		      {
			if(babymind->JudgeFV(detrecon->posy[targetmod][0][sidebunch][0], 
					     detrecon->posz[targetmod][0][sidebunch][0]))
			  {
			    if(lr==-1)
			      countyasutotal[iyasu][0]++;
			    if(lr==1)
			      countyasutotal[iyasu][1]++;
			    
			    if(babymind->SearchYasuHit(lr, originalhittime[0][sidebunch], 
						       yasu_hittime[iyasu][sidebunch], yasu_channel[iyasu][sidebunch]))
			      {
				if(lr==-1)
				  countyasueff[iyasu][0]++;
				if(lr==1)
				  countyasueff[iyasu][1]++;
				//cout << "ientry= " << ientry << '\n';
			      }
			  }

		      }
		  }
	      }
	  }//ibunch YASU

    }//ientry


  cout << "side view" << '\n';
  for(int iplane=2; iplane<=17; iplane++)
    {
      cout << "pln#= " << iplane << " "  << counteff[0][iplane] << "/" << counttotal[0][iplane] << " = " 
	   << counteff[0][iplane]/(double)counttotal[0][iplane]*100 << "%" << '\n';
    }

  cout << "top view" << '\n';
  for(int iplane=2; iplane<=17; iplane++)
    {
      cout << "pln#= " << iplane << " "  << counteff[1][iplane] << "/" << counttotal[1][iplane] << " = " 
	   << counteff[1][iplane]/(double)counttotal[1][iplane]*100 << "%" << '\n';
    }


  cout << "Left Module" << '\n';
  for(int iplane=0; iplane<=1; iplane++)
    {
      cout << "pln#= " << iplane+19 << " "  << countyasueff[iplane][0] << "/" << countyasutotal[iplane][0] << " = " 
	   << countyasueff[iplane][0]/(double)countyasutotal[iplane][0]*100 << "%" << '\n';
    }

  cout << "Right Module" << '\n';
  for(int iplane=0; iplane<=1; iplane++)
    {
      cout << "pln#= " << iplane+19 << " "  << countyasueff[iplane][1] << "/" << countyasutotal[iplane][1] << " = " 
	   << countyasueff[iplane][1]/(double)countyasutotal[iplane][1]*100 << "%" << '\n';
    }
  
  
  return 0;
  
}
