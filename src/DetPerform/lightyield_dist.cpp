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
  TCanvas* canvas1 = new TCanvas("canvas1", "canvas1", 1500, 500);
  canvas1->Divide(3, 1);
  TCanvas* canvas2 = new TCanvas("canvas2", "canvas2", 1000, 1000);
  TCanvas* canvas3 = new TCanvas("canvas3", "canvas3", 1000, 1000);
#endif

  EVTCluster* evtcluster = new EVTCluster();
  DetRecon* detrecon = new DetRecon();
  BabyMIND* babymind = new BabyMIND();

  TFile *fin = new TFile(filename, "Read");
  TTree *tree = (TTree*)fin->Get("tree");
  tree->SetBranchAddress("EVTCluster", &evtcluster);
  tree->SetBranchAddress("DetRecon", &detrecon);
  cout << tree->GetEntries() << '\n';

  vector<int> activepln[2][9];
  vector<int> yasu_hittime[2][9];
  vector<int> yasu_channel[2][9];
  vector<double> yasu_pel[2][9];
  double originalhittime[2][9];  

  TH1D* pehorr_total = new TH1D("pehorr_total", "", 100, 1, 100);
  TH1D* pehorl_total = new TH1D("pehorl_total", "", 100, 1, 100);
  TH1D* pehor_total = new TH1D("pehor_total", "", 100, 1, 200);
  TH1D* pever_total = new TH1D("pever_total", "", 100, 1, 50);
  TH1D* peyasu_total = new TH1D("peyasu_total", "", 100, 1, 50);

  TFile *fout = new TFile("${processdir}/result/DetPerform/lightyield.root", "RECREATE");

  //for(int ientry=8000; ientry<8500; ientry++)
  for(int ientry=8000; ientry<tree->GetEntries(); ientry++)
    {     
      for(int iview=0; iview<2; iview++)
	for(int ibunch=0; ibunch<9; ibunch++)
	  {
	    activepln[iview][ibunch].clear();
	    yasu_hittime[iview][ibunch].clear();
	    yasu_channel[iview][ibunch].clear();
	    originalhittime[iview][ibunch]=0;
	    yasu_pel[iview][ibunch].clear();
	  }
      
      tree->GetEntry(ientry);
      
      int targetmod = 5;
      int ntrack;
      int bunch;
      int nhit[9];
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
	  double yasupel = evtcluster->pel.at(ihit);

          yasu_hittime[yasuplane][yasubunch].push_back(yasuhittime);
          yasu_channel[yasuplane][yasubunch].push_back(yasuchannel);
	  yasu_pel[yasuplane][yasubunch].push_back(yasupel);
        }

      for(int ibunch=1; ibunch<9; ibunch++)
        for(int iview=0; iview<2; iview++)
          {
            double posxy, posz;
            ntrack = detrecon->Ntrack[targetmod][iview][ibunch];

            if(ntrack!=1) continue;

            nhit[ibunch] = detrecon->Nhit[targetmod][iview][ibunch][0];
            ataribunch[iview].push_back(ibunch);

            for(int ihit=0; ihit<nhit[ibunch]; ihit++)
              {
                bool fillflag = true;
                posz = detrecon->posz[targetmod][iview][ibunch][0][ihit];
                originalhittime[iview][ibunch] += (detrecon->hittime[targetmod][iview][ibunch][0][ihit])/nhit[ibunch];

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
                  }
              }//ihit  	    

	    std::sort(activepln[iview][ibunch].begin(), activepln[iview][ibunch].end());
            auto last =  std::unique(activepln[iview][ibunch].begin(),activepln[iview][ibunch].end());
            activepln[iview][ibunch].erase(last, activepln[iview][ibunch].end());

	    /*	    
            for(int ibunch=0; ibunch<ataribunch[iview].size(); ibunch++)
              {
                int thebunch = ataribunch[iview].at(ibunch);
                if(activepln[iview][thebunch].size()<=5) continue;
	    */

	    for(int ihit=0; ihit<nhit[ibunch]; ihit++)
	      {
		if(iview==0)
		  {
		    pehorr_total->Fill(detrecon->per[targetmod][iview][ibunch][0][ihit]);
		    pehorl_total->Fill(detrecon->pel[targetmod][iview][ibunch][0][ihit]);
		    pehor_total->Fill(detrecon->pel[targetmod][iview][ibunch][0][ihit]+
				      detrecon->per[targetmod][iview][ibunch][0][ihit]);
		    
		    //cout << detrecon->per[targetmod][iview][ibunch][0][ihit] << '\n';
		  }
		
		if(iview==1)
		  {
		    pever_total->Fill(detrecon->pet[targetmod][iview][ibunch][0][ihit]);
		  }
	      }
	    
          }//iviewibunch   

      if(ataribunch[0].size()==ataribunch[1].size())
        for(int ibunch=0; ibunch<ataribunch[0].size(); ibunch++)
          {
            int sidebunch = ataribunch[0].at(ibunch);
            int topbunch = ataribunch[1].at(ibunch);

            if(sidebunch==topbunch)
              {
                int lr = babymind->JudgeLeftRight(detrecon->posx[targetmod][1][topbunch][0]);
		
                babymind->ConverttoPln(activepln[0][sidebunch]);
                for(int iyasu=0; iyasu<2; iyasu++)
                  {
                    if(babymind->SearchThePln(1) && babymind->SearchThePln(2))
                      {
                        if(babymind->JudgeFV(detrecon->posy[targetmod][0][sidebunch][0],
                                             detrecon->posz[targetmod][0][sidebunch][0]))
                          {

			    if(lr==-1)
			      {
				for(int ihit=0; ihit<yasu_hittime[iyasu][sidebunch].size(); ihit++)
				  {
				    int theyasuchannel = yasu_channel[iyasu][sidebunch].at(ihit);
				    if(theyasuchannel<=6) continue;
				    int theyasutime = yasu_hittime[iyasu][sidebunch].at(ihit);
				    if(fabs(theyasutime-originalhittime[iyasu][sidebunch])<30)
				      {
					peyasu_total->Fill(yasu_pel[iyasu][sidebunch].at(ihit));
				      }
       				  }
			      }

			    if(lr==1)
			      {
				for(int ihit=0; ihit<yasu_hittime[iyasu][sidebunch].size(); ihit++)
				  {
				    int theyasuchannel = yasu_channel[iyasu][sidebunch].at(ihit);
				    if(theyasuchannel>=7) continue;
				    int theyasutime = yasu_hittime[iyasu][sidebunch].at(ihit);
				    if(fabs(theyasutime-originalhittime[iyasu][ibunch])<30)
				      {
					peyasu_total->Fill(yasu_pel[iyasu][sidebunch].at(ihit));	     			
				      }
				  }
			      }
    
                          }
                      }
                  }//iyasu
              }//sidebunch==topbunch
          }//ibunch YASU

    }//ientry

  cout << pehorr_total->GetEntries() << '\n';
  cout << pehorl_total->GetEntries() << '\n';
  cout << pehor_total->GetEntries() << '\n';

  fout->cd();
  pehorr_total->Write();
  pehorl_total->Write();
  pehor_total->Write();
  pever_total->Write();
  peyasu_total->Write();
  fout->Close();

#ifdef display
  canvas1->cd(1);
  pehorr_total->Draw("hist");
  canvas1->cd(2);
  pehorl_total->Draw("hist");
  canvas1->cd(3);
  pehor_total->Draw("hist");
  canvas1->Update();

  canvas2->cd();
  pever_total->Draw("hist");
  canvas2->Update();

  canvas3->cd();
  peyasu_total->Draw("hist");
  canvas3->Update();

  theapp.Run();
  
#endif 

  return 0;
  
}


