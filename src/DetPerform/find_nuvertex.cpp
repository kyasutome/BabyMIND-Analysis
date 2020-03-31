#include <iostream>
#include <stdio.h>
#include <vector>

#include <TString.h>
#include <TTree.h>
#include <TFile.h>
#include <TApplication.h>
#include <TH1D.h>

//include
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
  TCanvas*canvas[2];
  canvas[0]= new TCanvas("canvasside", "canvasside", 1000, 1000);
  canvas[1]= new TCanvas("canvastop", "canvastop", 1000, 1000);
#endif

  EVTCluster* evtcluster = new EVTCluster();
  DetRecon* detrecon = new DetRecon();
  MCTrue* mctrue = new MCTrue();
  Tracking* tracking = new Tracking();

  TFile *fin = new TFile(filename, "Read");
  TTree *tree = (TTree*)fin->Get("tree");
  tree->SetBranchAddress("EVTCluster", &evtcluster);
  tree->SetBranchAddress("DetRecon", &detrecon);
  tree->SetBranchAddress("MCTrue", &mctrue);
  cout << tree->GetEntries() << '\n';

  TFile *fout = new TFile(Form("${processdir}/result/DetPerform/vertex.root"), "RECREATE");
  TH1D* vertex[3][3];
  for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
      vertex[i][j]= new TH1D(Form("vertex_track%d_pos%d", i, j), "", 100, -1000, 1000);
  double vertexdif[3];
  int trackcount[3] = {0, 0, 0};
  vector<int>svertex[3];

  bool fvcut[6][2], fccut[6][2];
  vector<double> ipos[4], fpos[4], momentum[4];
  int inttype;
  int pmntrack[2];
  vector<int>particlelist;
  double estimatevertex[2][2];
  vector<double> trackposz[2][20];
  vector<double> trackposxy[2][20];

  //int targetentry=1744;
  for(int ientry=0; ientry<50; ientry++)
  //for(int ientry=0; ientry<tree->GetEntries(); ientry++)
    {

#ifdef display
      if(ientry!=targetentry)
	continue;
#endif
      
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

      particlelist.clear();
      tree->GetEntry(ientry);
      inttype = mctrue->inttype;

      for(int iview=0; iview<2; iview++)
        {
          pmntrack[iview] = detrecon->Ntrack[0][iview][1];
	  for(int itrack=0; itrack<20; itrack++)
	    {
	      trackposz[iview][itrack].clear();
	      trackposxy[iview][itrack].clear();
	      for(int ihit=0; ihit<detrecon->Nhit[0][iview][1][itrack]; ihit++)
		{

		  trackposz[iview][itrack].push_back(detrecon->posz[0][iview][1][itrack][ihit]);
		  if(iview==0)
		    trackposxy[iview][itrack].push_back(detrecon->posy[0][iview][1][itrack][ihit]);
		  if(iview==1)
		    trackposxy[iview][itrack].push_back(detrecon->posx[0][iview][1][itrack][ihit]);

		}//ihit
	    }//itrack
        }//iview

      if(pmntrack[0]>=20 || pmntrack[1]>=20)
	continue;
      if(pmntrack[0]==0 || pmntrack[1]==0)
	continue;

      tracking->SearchParticle(13, mctrue, &particlelist);

      for(int ipar=0; ipar<particlelist.size(); ipar++)
        {
          for(int i=0; i<3; i++)
            {
              int parid = particlelist.at(ipar);
              ipos[i].push_back(mctrue->ipos[i][parid]*10);
              fpos[i].push_back(mctrue->fpos[i][parid]*10);
              momentum[i].push_back(mctrue->momentum[i][parid]*1000);
            }
        }//ipar

      if(ipos[0].size()==1)
        {
	  for(int iview=0; iview<2; iview++)
            {
              if(iview==0)
                {
                  fvcut[0][0]=tracking->FVcut(0, iview, ipos[2].at(0), ipos[1].at(0));
		  fccut[5][0]=tracking->FCcut(5, iview, fpos[2].at(0), fpos[1].at(0));		  
                }

              if(iview==1)
                {
                  fvcut[0][1]=tracking->FVcut(0, iview, ipos[2].at(0), ipos[0].at(0));
		  fccut[5][1]=tracking->FCcut(5, iview, fpos[2].at(0), fpos[0].at(0));
                }
	      //cout << "fvcut= " << fvcut[0][0] << " " << fvcut[0][1] << '\n';
	    }
	}//ipos

      if(fvcut[0][0] && fvcut[0][1] && fccut[5][0] && fccut[5][1])
	{
	  cout << "ientry= " << ientry << '\n';
	  cout << "True Nu Vertex" << '\n';
	  cout << "xnu= " << mctrue->xnu*10+950 << " ynu= " << mctrue->ynu*10+600
	       << " znu= " << mctrue->znu*10+1200 << '\n';

	  for(int iview=0; iview<2; iview++)
	    {
	      if(iview==0)
	      	tracking->SearchNuVertex(0, iview, pmntrack[iview], trackposz[iview], 
	      				 trackposxy[iview], estimatevertex[iview]);

	      if(iview==1)
		tracking->SearchNuVertex(0, iview, pmntrack[iview], trackposz[iview], 
					 trackposxy[iview], estimatevertex[iview]);
	      
#ifdef display
	      if(pmntrack[iview]>=3)
		{
		  canvas[iview]->cd();
		  for(int itrack=0; itrack<pmntrack[iview]; itrack++)
		    {
		      if(itrack==0)
			tracking->reconfit[itrack]->Draw("AP");
		      else if(itrack>=1)
			tracking->reconfit[itrack]->Draw("P,same");
		      
		      tracking->linear[itrack]->Draw("same");
		      
		      tracking->optpoint->Draw("same");
		    }
		}//pmntrack
#endif
	      
	    }

	  cout << "Estimate Nu Vertex" << '\n';
	  cout <<  "xnu= " << estimatevertex[1][1] << " ynu= " << estimatevertex[0][1] << " znu= " 
	       << estimatevertex[0][0] << '\n';	  

	  vertexdif[0] = (mctrue->xnu*10+950 - estimatevertex[1][1]);
	  vertexdif[1] = (mctrue->ynu*10+600 - estimatevertex[0][1]);
	  vertexdif[2] = (mctrue->znu*10+1200 - estimatevertex[0][0]);

	  if(vertexdif[0]>400)
	    svertex[0].push_back(ientry);
	  if(vertexdif[1]>400)
	    svertex[1].push_back(ientry);
	  if(vertexdif[2]>400 || vertexdif[2]<-400)
	    svertex[2].push_back(ientry);
	  
	  if(pmntrack[0]==1)
	    vertex[0][1]->Fill(vertexdif[1]);
	  if(pmntrack[0]==2)
	    vertex[1][1]->Fill(vertexdif[1]);
	  if(pmntrack[0]>=3)
	    vertex[2][1]->Fill(vertexdif[1]);
	  
	  if(pmntrack[1]==1)
	    vertex[0][0]->Fill(vertexdif[0]);
	  if(pmntrack[1]==2)
	    vertex[1][0]->Fill(vertexdif[0]);
	  if(pmntrack[1]>=3)
	    vertex[2][0]->Fill(vertexdif[0]);

	  if(pmntrack[0]==1)
	    vertex[0][2]->Fill(vertexdif[2]);
	  if(pmntrack[0]==2)
	    vertex[1][2]->Fill(vertexdif[2]);
	  if(pmntrack[0]>=3)
	    vertex[2][2]->Fill(vertexdif[2]);

	  if(pmntrack[0]==1)
	    trackcount[0]++;
	  if(pmntrack[0]==2)
	    trackcount[1]++;
	  if(pmntrack[0]>=3)
	    trackcount[2]++;
	    	  
	}//fvcut
    }//ientry

  cout << "vertex0" << '\n';
  for(int i=0; i<svertex[0].size(); i++)
    {
      cout << "ientry= " << svertex[0].at(i) << '\n';
    }

  cout << "vertex1" << '\n';
  for(int i=0; i<svertex[1].size(); i++)
    {
      cout << "ientry= " << svertex[1].at(i) << '\n';
    }

  cout << "vertex2" << '\n';
  for(int i=0; i<svertex[2].size(); i++)
    {
      cout << "ientry= " << svertex[2].at(i) << '\n';
    }

  cout << trackcount[0] << " " << trackcount[1] << " " << trackcount[2] << '\n';

  fout->cd();
  for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
      {
	vertex[i][j]->Write();
      }
  
   
#ifdef display
  canvas[0]->Update();
  canvas[1]->Update();
  theapp.Run();
#endif 

  return 0;
  
}


