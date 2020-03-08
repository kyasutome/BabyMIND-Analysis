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

using namespace std;

//#define Continuous
//#define Single
//#define display
//#define ProtonModule
//#define WAGASCIup
//#define WAGASCIdown
//#define WallMRDnorth
//#define WallMRDsouth
#define BabyMIND

int main( int argc, char **argv )
{

  if(argc < 3)
    {
      cout << "usage" << '\n';
      cout << "TrackRecon [filepath][run]" << '\n';
      exit(0);
    }
  
  std::string name = string(argv[1]);
  std::string run = string(argv[2]);
  int targetentry = atoi(argv[3]);
  TString filepath(name);

  CellAutomation *cellauto = new CellAutomation();
  EVTCluster* evtcluster = new EVTCluster();
  DetRecon* detrecon = new DetRecon();
  
  //ReadFile
  TString filename = "./process/4-Recon/Recon_92.root";
  TFile *fin = new TFile(filename, "READ");
  TTree *tree = (TTree*)fin->Get("tree");
  tree->SetBranchAddress("EVTCluster",&evtcluster);
  tree->SetBranchAddress("DetRecon",&detrecon);

  int Nentry = tree->GetEntries();
  cout << "Nentry= " << Nentry << '\n';

  //for(int ientry=targetentry; ientry<targetentry+1; ientry++)
  for(int ientry=0; ientry<tree->GetEntries(); ientry++)
    {
      tree->GetEntry(ientry);
      for(int ibunch=1; ibunch<=8; ibunch++)
	{

	  
#ifdef ProtonModule
	  if(detrecon->Ntrack[0][0][ibunch]>=2 || detrecon->Ntrack[0][1][ibunch]>=2)
	    {
	      cout << "ientry= " << ientry << '\n';
	      cout << "Ntrack[0][ibunch]= " <<detrecon->Ntrack[0][0][ibunch] << '\n';

	      
	      for(int itrack=0; itrack<detrecon->Ntrack[0][0][ibunch]; itrack++)
		{
		  //cout << "itrack= " << itrack << '\n';
 		  for(int ihit=0; ihit<detrecon->Nhit[0][0][itrack]; ihit++)
		    {
		      //cout << "ihit= " << ihit << '\n';
		      //cout << "htime= " << detrecon->hittime[0][0][itrack][ihit] << '\n';
		    }
		}

	    }
#endif
	  
	  
#ifdef WAGASCIup
	  //if(detrecon->Ntrack[1][0][ibunch]>=2 || detrecon->Ntrack[1][1][ibunch]>=2)
	  if(detrecon->Ntrack[1][0][ibunch]>=1 && detrecon->Ntrack[1][1][ibunch]>=1)
	    {
	      cout << "ientry= " << ientry << '\n';
	      cout << "Ntrack[1][ibunch]= " <<detrecon->Ntrack[1][0][ibunch] << '\n';
      
	      for(int itrack=0; itrack<detrecon->Ntrack[1][0][ibunch]; itrack++)
		{
		  //cout << "itrack= " << itrack << '\n';
 		  for(int ihit=0; ihit<detrecon->Nhit[1][0][itrack]; ihit++)
		    {
		      //cout << "ihit= " << ihit << '\n';
		      //cout << "htime= " << detrecon->hittime[1][0][itrack][ihit] << '\n';
		    }
		}

	    }
#endif	  
	  
	
#ifdef WAGASCIdown  
	  if(detrecon->Ntrack[2][0][ibunch]>=2 || detrecon->Ntrack[2][1][ibunch]>=2)
	    {
	      cout << "ientry= " << ientry << '\n';
	      cout << "Ntrack[2][ibunch]= " <<detrecon->Ntrack[2][0][ibunch] << '\n';

	      
	      for(int itrack=0; itrack<detrecon->Ntrack[2][0][ibunch]; itrack++)
		{
		  cout << "itrack= " << itrack << '\n';
 		  for(int ihit=0; ihit<detrecon->Nhit[2][0][itrack]; ihit++)
		    {
		      cout << "ihit= " << ihit << '\n';
		      cout << "htime= " << detrecon->hittime[2][0][itrack][ihit] << '\n';
		    }
		}

	    }
#endif


#ifdef WallMRDnorth	  
	  if(detrecon->Ntrack[3][1][ibunch]>=2)
	    {
	      cout << "ientry= " << ientry << '\n';
	      cout << "Ntrack[3][ibunch]= " <<detrecon->Ntrack[3][0][ibunch] << '\n';
      
	      for(int itrack=0; itrack<detrecon->Ntrack[3][0][ibunch]; itrack++)
		{
		  cout << "itrack= " << itrack << '\n';
 		  for(int ihit=0; ihit<detrecon->Nhit[3][0][itrack]; ihit++)
		    {
		      cout << "ihit= " << ihit << '\n';
		      cout << "htime= " << detrecon->hittime[3][0][itrack][ihit] << '\n';
		    }
		}

	    }
#endif
	
#ifdef WallMRDsouth  
	  if(detrecon->Ntrack[4][1][ibunch]>=2)
	    {
	      cout << "ientry= " << ientry << '\n';
	      cout << "Ntrack[4][ibunch]= " <<detrecon->Ntrack[4][0][ibunch] << '\n';
      
	      for(int itrack=0; itrack<detrecon->Ntrack[4][0][ibunch]; itrack++)
		{
		  cout << "itrack= " << itrack << '\n';
 		  for(int ihit=0; ihit<detrecon->Nhit[4][0][itrack]; ihit++)
		    {
		      cout << "ihit= " << ihit << '\n';
		      cout << "htime= " << detrecon->hittime[4][0][itrack][ihit] << '\n';
		    }
		}

	    }
#endif
	  
#ifdef BabyMIND
	  if(detrecon->Ntrack[5][0][ibunch]>=3 && detrecon->Ntrack[5][1][ibunch]>=2)
	    {
	      cout << "ientry= " << ientry << '\n';
	      cout << "Ntrack[5][ibunch]= " <<detrecon->Ntrack[5][0][ibunch] << '\n';
      
	      for(int itrack=0; itrack<detrecon->Ntrack[5][0][ibunch]; itrack++)
		{
		  //cout << "itrack= " << itrack << '\n';
 		  for(int ihit=0; ihit<detrecon->Nhit[5][0][ibunch][itrack]; ihit++)
		    {
		      //cout << "ihit= " << ihit << '\n';
		      //cout << "htime= " << detrecon->hittime[5][0][itrack][ihit] << '\n';
		    }
		}

	    }
#endif
	  
	}

    }

  return 0;
  
}//main
