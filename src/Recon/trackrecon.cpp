//Standard
#include <iostream>
#include <stdio.h>

#include <TString.h>
#include <TCanvas.h>

#include "cellautomation.cpp"
#include "yasutomethod.cpp"
#include "mestimation.cpp"
#include "chargeid.cpp"
#include "TrackMatching.cpp"

#include "BMCluster.hpp"

using namespace std;

//#define Continuous
#define Single

int main( int argc, char **argv )
{

  if(argc < 5)
    {
      cout << "usage" << '\n';
      cout << "TrackRecon [filepath][date][month][run][ientry]" << '\n';
      exit(0);
    }
  
  std::string name = string(argv[1]);
  std::string date = string(argv[2]);
  std::string month = string(argv[3]);
  std::string run = string(argv[4]);
  int targetentry = atoi(argv[5]);
  TString filepath(name);

  TApplication app("app", 0, 0, 0, 0);
  BMDisp *bmdisp = new BMDisp();
  CellAutomation *cellauto = new CellAutomation();
  Yasutomethod *yasutomethod = new Yasutomethod();
  Mestimation *mestimation = new Mestimation();
  Chargeid *chargeid = new Chargeid();
  TrackMatching *trackmatching = new TrackMatching();
  BMCluster *bmcluster[100];
  for(int i=0; i<100; i++)
    bmcluster[i]= new BMCluster();
  //BMCluster *bmcluster = new BMCluster();

  TFile* file = new TFile(filepath, "read");
  TTree* tree = (TTree*)file->Get("tree");
  tree->SetBranchAddress("BMDisp",&bmdisp);

  vector<int> matchingevent;
  matchingevent.clear();
  double count_numu=0;
  double count_numubar=0;
  int minimumlimit=5;

  double number_of_numu=0;
  double number_of_numubar=0;

#ifdef Single

  TCanvas *canvas1 = new TCanvas("canvas1", "canvas1", 1000, 600);
  TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 1000, 600);
  TCanvas *canvas3 = new TCanvas("canvas3", "canvas3", 1000, 600);
  TCanvas *canvas4 = new TCanvas("canvas4", "canvas4", 1000, 600);
  TCanvas *canvas5 = new TCanvas("canvas5", "canvas5", 1000, 600);

  for(int ientry=0; ientry<tree->GetEntries(); ientry++)
    {
      if(ientry!=targetentry) continue;
      tree->GetEntry(targetentry);
      if(bmdisp->mod.size()==0) 
	{
	  cout << "Nohit in this event" << '\n';
	  break;
	}
      cout << "startFill" << '\n';
      cellauto->FillBeforeFit(bmdisp);
      yasutomethod->ystmethod(bmdisp, bmcluster);
      //chargeid->algorithm_A(bmcluster, count_numu, count_numubar, minimumlimit);
      //cout << "count_numu: " << count_numu << " count_numubar: " << count_numubar << '\n';
      cout << "Matching " << trackmatching->Matching_pmbm(bmdisp, bmcluster) << '\n';
    }

  cout << "Draw" << '\n';

  canvas1->cd();
  cellauto->beforefit[0][0]->Draw("box");
  canvas1->Update();
  canvas2->cd();
  trackmatching->pmdisp_corr->Draw("box");
  canvas2->Update();
  canvas3->cd();
  yasutomethod->recondisp->Draw("box");
  canvas3->Update();
  canvas4->cd();
  trackmatching->pmdisp->Draw("box");
  canvas4->Update();
  canvas5->cd();
  trackmatching->bmdisp_corr->Draw("box");
  canvas5->Update();

  app.Run();

#endif

#ifdef Continuous
  //for(int ientry=0; ientry<tree->GetEntries(); ientry++)
  for(int ientry=0; ientry<20; ientry++)
    {    
      cout << "ientry= " << ientry << '\n';
      for(int i=0; i<100; i++)
	bmcluster[i]->clear();
      bmdisp->Clear();
      tree->GetEntry(ientry);
      yasutomethod->ystmethod(bmdisp, bmcluster);
      //if(bmcluster->mod.size()<4) continue;
      //chargeid->algorithm_A(bmcluster, count_numu, count_numubar, minimumlimit);
      //cout << "count_numu: " << count_numu << " count_numubar: " << count_numubar << '\n';
      //if(trackmatching->Matching_pmbm(bmdisp, bmcluster))
      //matchingevent.push_back(ientry);
      //cout << "Matching " << trackmatching->Matching_pmbm(bmdisp, bmcluster) << '\n';
      // chargeid->CountMuon(count_numu, count_numubar, number_of_numu, number_of_numubar);      
    }
  
  cout << "Mu Neutrino = " << number_of_numu << '\n'; 
  cout << "Anti Mu Neutrino = " << number_of_numubar << '\n'; 
  cout << "Ratio = " << number_of_numu/(number_of_numu+number_of_numubar) << '\n';

  cout << "MATCH" << '\n';
  for(int i=0; i<matchingevent.size(); i++)
    cout << matchingevent.at(i) << '\n';

#endif

  return 0;

  
}//main
