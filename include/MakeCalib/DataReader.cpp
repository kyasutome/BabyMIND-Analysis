#include <iostream>
#include <fstream>

#include "DataReader.hpp"
#include "BMData.hpp"

using namespace std;

DataReader::DataReader()
{

  for(int ifeb=0; ifeb<NUMBEROFFEB; ifeb++)
    {
      intersection[ifeb].clear();
      febspill[ifeb].clear();
    }

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
  cout << "[B2-connection.map]" << '\n';

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
  cout << "[v1_horizontal_from_center.txt]" << '\n';

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
  cout << "[v1_vertical_from_center.txt]" << '\n';

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
  cout << "[Scin_Mod_position]" << '\n';

}

DataReader::~DataReader()
{
}

void DataReader::ReadTree(TString filename, BMdata* BMbranch[NUMBEROFFEB])
{  
  cout << "Start reading FEB tree..." << '\n';
  if (gSystem->GetPathInfo(filename.Data(), info)!=0)
    {
      cout << "File" << filename << " done not exist" << '\n';
      exit(0);
    }else{
    Fileinput = new TFile(filename, "READ");
    
    for(int itree=0; itree<NUMBEROFFEB; itree++)
    //for(int itree=0; itree<10; itree++)
      {
	int totalhits=0;
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
	      ->SetBranchAddress(Form("%s_hitLGAmpl",treename.Data()), &BMbranch[itree]->hitLGAmpl);
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

	    for(int ientry=0; ientry<FEBtree[itree]->GetEntries(); ientry++)
	      {
		FEBtree[itree]->GetEntry(ientry);
		for(int idata=0; idata<BMbranch[itree]->SpillTag->size(); idata++)
		  {
		    febspill[itree].push_back(BMbranch[itree]->SpillTag->at(idata));
		  }		
		totalhits += BMbranch[itree]->SpillTag->size();
	      }

	    //cout << "FEB:" << itree << " the number of FEB events= " << totalhits  << '\n';
	    cout <<  totalhits  << '\n';
	  }
	DuplicateCut(&febspill[itree]);
      }
    
  }//File Exist (else)

  cout << "****************** Read Summary ******************"  << '\n';
  cout << "Total Number of Spills = " << febspill[0].size() << '\n';

}

void DataReader::DuplicateCut(vector<double> *vec)
{
  auto last = unique(vec->begin(), vec->end());
  vec->erase(last, vec->end());
}


void DataReader::BMSpillMatch(vector<double> *commonspill)
{
  set_intersection(febspill[0].begin(), febspill[0].end(),
		   febspill[1].begin(), febspill[1].end(),
		   inserter(intersection[0], intersection[0].end()));

  for(int ifeb=1; ifeb<62; ifeb++)
    {
      if(febspill[ifeb].size()!=0)
	{
	  set_intersection(febspill[ifeb-1].begin(), febspill[ifeb-1].end(),
			   febspill[ifeb].begin(), febspill[ifeb].end(),
			   inserter(intersection[ifeb], intersection[ifeb].end()));
	}

      if(febspill[ifeb].size()==0)
	{
	  set_intersection(febspill[ifeb-1].begin(), febspill[ifeb-1].end(),
			   febspill[ifeb-1].begin(), febspill[ifeb-1].end(),
			   inserter(intersection[ifeb], intersection[ifeb].end()));

	}

    }

  
  for(int i=0; i<intersection[61].size(); i++)
    commonspill->push_back(intersection[61].at(i));
  

  cout << "Total Number of Common Spills = " << febspill[0].size() << '\n';

}
