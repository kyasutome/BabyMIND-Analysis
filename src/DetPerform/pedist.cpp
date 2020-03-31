//Standard
#include <iostream>
#include <stdio.h>

//MyInc
#include "BSDApply.cpp"
#include "babymind.cpp"

//MyLib
#include "BMBasicRecon.hpp"
#include "BMBeaminfo.hpp"
#include "BMBSD.hpp"

#include <TString.h>


using namespace std;

int main( int argc, char **argv )
{

  //Usage
  if(argc < 1)
    {
      cout << "usage" << '\n';
      cout << "pedist [filepath]" << '\n';
      exit(0);
    }

  //Set Parameters
  
  std::string name = string(argv[1]);
  TString filepath(name);

  //Set Classes
  BMBasicRecon *bmbasicrecon = new BMBasicRecon();
  BMBeaminfo *bmbeaminfo = new BMBeaminfo();
  BabyMIND *babymind = new BabyMIND();

  TString ofilepath;
  //ofilepath.Form("./result/DetPerform/BM_pedist_Jan_30_31.root");
  ofilepath.Form("${processdir}/result/DetPerform/BM_pedist_Feb_1_2.root");
  TFile* fout = new TFile(ofilepath, "recreate");
  TTree* otree = new TTree("tree", "tree");
  double ope_hor[18][96][2];
  otree->Branch("pe_hor", ope_hor, "pe_hor[18][96][2]/D");
  double ope_ver[18][32];
  otree->Branch("pe_ver", ope_ver, "pe_ver[18][32]/D");
  double ope_yasu[2][14];
  otree->Branch("pe_yasu", ope_yasu, "pe_yasu[2][14]/D");
  
  babymind->FillADCDist(filepath, bmbasicrecon, bmbeaminfo);
  babymind->CalcPEMean();
    
  fout->cd();

  for(int imod=0; imod<18; imod++)
    {
      for(int ihor=0; ihor<96; ihor++)
        for(int iread=0; iread<2; iread++)
	  {
	    babymind->adcdist_hor[imod][ihor][iread]->Write();
	    ope_hor[imod][ihor][iread] = babymind->pe_hor[imod][ihor][iread];
	  }
      
      for(int iver=0; iver<32; iver++)
	{
	  babymind->adcdist_ver[imod][iver]->Write();
	  ope_ver[imod][iver] = babymind->pe_ver[imod][iver];
	}
    }

  for(int imod=0; imod<2; imod++)
    for(int iyasu=0; iyasu<14; iyasu++)
      {
	babymind->adcdist_yasu[imod][iyasu]->Write();
	ope_yasu[imod][iyasu] = babymind->pe_yasu[imod][iyasu];
      }

  babymind->adcdist_hor_left_total->Write();
  babymind->adcdist_hor_right_total->Write();
  babymind->adcdist_ver_total->Write();
  babymind->adcdist_yasu_total->Write();

  otree->Fill();
  otree->Write();
  fout->Close();
  
  
}//main
