#include <iostream>
#include <fstream>

#include "DataReader.hpp"

using namespace std;

DataReader::DataReader()
{
  cout << "read required data file..." << '\n';

  ifstream fmap("./data/B2-connection.map");
  int temp = 1;
  if(!fmap.is_open()) 
    {
      cout << Form("File B2-connection.map does not exist.") << '\n';
      exit(0);
    }
  while(!fmap.eof()){
    fmap >> MapCon[0][temp] >> MapCon[1][temp] >> MapCon[2][temp]
         >> MapCon[3][temp] >> MapCon[4][temp];
    temp++;
  }
  fmap.close();
  cout << "B2-connection.map" << '\n';

  ifstream horizontalgeometry("./data/v1_horizontal_from_center.txt");
  temp=0;
  if(!horizontalgeometry.is_open()) 
    {
      cout << Form("File v1_horizontal_from_center.txt does not exist.") << '\n';
      exit(0);
    }
  while(!horizontalgeometry.eof()){
    horizontalgeometry >> geomHor[0][temp] >> geomHor[1][temp] >> geomHor[2][temp]
                       >> geomHor[3][temp] >> geomHor[4][temp];
    temp++;
  }
  horizontalgeometry.close();
  cout << "v1_horizontal_from_center.txt" << '\n';

  ifstream verticalgeometry("./data/v1_vertical_from_center.txt");
  temp=0;
  if(!verticalgeometry.is_open()) 
    {
      cout << Form("File v1_horizontal_from_center.txt does not exist.") << '\n';
      exit(0);
    }
  while(!verticalgeometry.eof()){
    verticalgeometry >> geomVer[0][temp] >> geomVer[1][temp] >> geomVer[2][temp]
                     >> geomVer[3][temp] >> geomVer[4][temp];
    temp++;
  }
  verticalgeometry.close();
  cout << "v1_vertical_from_center.txt" << '\n';

  ifstream ScinModPos("./data/Scin_Mod_position.txt");
  temp=1;
  if(!ScinModPos.is_open()) 
    {
      cout << Form("File Scin_Mod_position.txt does not exist.") << '\n';
      exit(0);
    }
  while(!ScinModPos.eof()){
    ScinModPos >> ModPos[0][temp] >> ModPos[1][temp] >> ModPos[2][temp]
               >> ModPos[3][temp];
    temp++;
  }
  ScinModPos.close();
  cout << "Scin_Mod_position" << '\n';

}

DataReader::~DataReader()
{
}

void DataReader::ReadTree(TString filename, BMdata* BMbranch[NUMBEROFFEB])
{  
  if (gSystem->GetPathInfo(filename.Data(), info)!=0)
    {
      cout << "File" << filename << " done not exist" << '\n';
      exit(0);
    }else{
    Fileinput = new TFile(filename, "READ");
    
    for(int itree=0; itree<NUMBEROFFEB; itree++)
      {
	treename.Form("FEB_%d", itree);
	if((TTree*)Fileinput->Get(treename))
	  {
	    FEBtree[itree] = (TTree*)Fileinput->Get(treename);
	    Nentry[itree] = FEBtree[itree]->GetEntries();
	    FEBtree[itree]
	      ->SetBranchAddress(Form("%s_SpillTag",treename.Data()), &BMbranch[itree]->SpillTag);
	    FEBtree[itree]
	      ->SetBranchAddress(Form("%s_SpillTime",treename.Data()), &BMbranch[itree]->SpillTime);
	    FEBtree[itree]
	      ->SetBranchAddress(Form("%s_SpillTimeGTrig",treename.Data()), &BMbranch[itree]->SpillTimeGTrig);
	    FEBtree[itree]
	      ->SetBranchAddress(Form("%s_GTrigTag",treename.Data()), &BMbranch[itree]->GTrigTag);
	    FEBtree[itree]
	      ->SetBranchAddress(Form("%s_GTrigTime",treename.Data()), &BMbranch[itree]->GTrigTime);
	    FEBtree[itree]
	      ->SetBranchAddress(Form("%s_hitsChannel",treename.Data()), &BMbranch[itree]->hitsChannel);
	    FEBtree[itree]
	      ->SetBranchAddress(Form("%s_hitAmpl",treename.Data()), &BMbranch[itree]->hitAmpl);
	    FEBtree[itree]
	      ->SetBranchAddress(Form("%s_hitLeadTime",treename.Data()), &BMbranch[itree]->hitLeadTime);
	    FEBtree[itree]
	      ->SetBranchAddress(Form("%s_hitTrailTime",treename.Data()), &BMbranch[itree]->hitTrailTime);
	    FEBtree[itree]
	      ->SetBranchAddress(Form("%s_hitTimeDif",treename.Data()), &BMbranch[itree]->hitTimeDif);
	    FEBtree[itree]
	      ->SetBranchAddress(Form("%s_hitTimefromSpill",treename.Data()), &BMbranch[itree]->hitTimefromSpill);
	    FEBtree[itree]
	      ->SetBranchAddress(Form("%s_SpillTrailTime",treename.Data()), &BMbranch[itree]->SpillTrailTime);
	    FEBtree[itree]
	      ->SetBranchAddress(Form("%s_AsicTemperature",treename.Data()), &BMbranch[itree]->AsicTemperature);
	    FEBtree[itree]
	      ->SetBranchAddress(Form("%s_FPGATemperature",treename.Data()), &BMbranch[itree]->FPGATemperature);
	    FEBtree[itree]
	      ->SetBranchAddress(Form("%s_BoardTemperature",treename.Data()), &BMbranch[itree]->BoardTemperature);
	    FEBtree[itree]
	      ->SetBranchAddress(Form("%s_BoardHumidity",treename.Data()), &BMbranch[itree]->BoardHumidity);
	    FEBtree[itree]
	      ->SetBranchAddress(Form("%s_GlobalHV",treename.Data()), &BMbranch[itree]->GlobalHV);
	  }
      }
    
  }//File Exist (else)

}
