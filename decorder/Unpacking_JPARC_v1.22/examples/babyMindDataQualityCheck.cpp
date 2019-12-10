#include <stdio.h>
#include <string.h>
#include <exception>
#include <fstream>
#include <vector>
#include "TFile.h"
#include <TTree.h>
#include <iostream>
#include <sstream>
#include "TH1.h"
#include "TDirectory.h"

using namespace std;

string GetLocation(string str)
{
     
    int i = str.rfind("_Slot_");
    string way = str.substr(0,i);  
    return way;
}

struct vectorsTree
{
  vector<double> *FEBSN;
  vector<double> *SpillNum;
  vector<double> *SpillTime;
  vector<double> *SpillTimeGTrig;
  vector<double> *GTrigTag;
  vector<double> *GTrigTime;
  vector<double> *hitsChannel;
  vector<double> *hitAmpl;
  vector<double> *hitLGAmpl;
  vector<double> *hitLeadTime;
  vector<double> *hitTrailTime;
  vector<double> *hitTimeDif;
  vector<double> *hitTimefromSpill;
  vector<double> *SpillTrailTime;
  vector<double> *AsicTemperature;
  vector<double> *FPGATemperature;
  vector<double> *GlobalHV;
  vector<double> *BoardTemperature;
  vector<double> *BoardHumidity;
};

int main ()
{
    int NumberOfFEB=64;
    
    vector<string> vFileNames;
    string sFileName;
    ifstream fList("febs_files_list.list");
    while (!fList.eof()) {
        fList >> sFileName;
        vFileNames.push_back(sFileName);
    }
    string rootFileInput=GetLocation(vFileNames[0].c_str());
    string rootFileOutput=GetLocation (vFileNames[0].c_str());
    rootFileInput+="_all.root";
    rootFileOutput+="_Data_Quality.root";
    cout << rootFileInput<<endl;
    cout << rootFileOutput<<endl;
    TFile *FileInput = new TFile(rootFileInput.c_str());
    
    vectorsTree FEB[NumberOfFEB];
    
    for (Int_t i=0;i<NumberOfFEB;i++){
        FEB[i].FEBSN=0;
        FEB[i].SpillNum=0;
        FEB[i].SpillTime=0;
        FEB[i].SpillTimeGTrig=0;
        FEB[i].GTrigTag=0;
        FEB[i].GTrigTime=0;
        FEB[i].hitsChannel=0;
        FEB[i].hitAmpl=0;
        FEB[i].hitLGAmpl=0;
        FEB[i].hitLeadTime=0;
        FEB[i].hitTrailTime=0;
        FEB[i].hitTimeDif=0;
        FEB[i].hitTimefromSpill=0;
        FEB[i].SpillTrailTime=0;
        FEB[i].AsicTemperature=0;
        FEB[i].FPGATemperature=0;
        FEB[i].GlobalHV=0;
        FEB[i].BoardTemperature=0;
        FEB[i].BoardHumidity=0;
    }

    TTree *FEBtree[NumberOfFEB];
    vector<int> FEBnumbers;
    FEBnumbers.clear();
    Long64_t nentries[NumberOfFEB];

    ostringstream sFEBnum;
    string sFEB;
    for (Int_t ih=0; ih<NumberOfFEB; ih++) {
        sFEBnum.str("");
        sFEBnum << ih;
        sFEB = "FEB_"+sFEBnum.str();
        FEBtree[ih] = (TTree*)FileInput->Get(sFEB.c_str());
        if ((TTree*)FileInput->Get(sFEB.c_str())){
            FEBnumbers.push_back(ih);
            std::cout<<sFEB<<" ";
            FEBtree[ih]->SetBranchAddress((sFEB+"_SN").c_str(),&FEB[ih].FEBSN);
            FEBtree[ih]->SetBranchAddress((sFEB+"_SpillTag").c_str(),&FEB[ih].SpillNum);
            FEBtree[ih]->SetBranchAddress((sFEB+"_SpillTime").c_str(),&FEB[ih].SpillTime);
			FEBtree[ih]->SetBranchAddress((sFEB+"_SpillTimeGTrig").c_str(),&FEB[ih].SpillTimeGTrig);
            FEBtree[ih]->SetBranchAddress((sFEB+"_GTrigTag").c_str(),&FEB[ih].GTrigTag);
            FEBtree[ih]->SetBranchAddress((sFEB+"_GTrigTime").c_str(),&FEB[ih].GTrigTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitsChannel").c_str(),&FEB[ih].hitsChannel);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitAmpl").c_str(),&FEB[ih].hitAmpl);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLGAmpl").c_str(),&FEB[ih].hitLGAmpl);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLeadTime").c_str(),&FEB[ih].hitLeadTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTrailTime").c_str(),&FEB[ih].hitTrailTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTimeDif").c_str(),&FEB[ih].hitTimeDif);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTimefromSpill").c_str(),&FEB[ih].hitTimefromSpill);
            FEBtree[ih]->SetBranchAddress((sFEB+"_SpillTrailTime").c_str(),&FEB[ih].SpillTrailTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_AsicTemperature").c_str(),&FEB[ih].AsicTemperature);
            FEBtree[ih]->SetBranchAddress((sFEB+"_FPGATemperature").c_str(),&FEB[ih].FPGATemperature);
            FEBtree[ih]->SetBranchAddress((sFEB+"_GlobalHV").c_str(),&FEB[ih].GlobalHV);
            FEBtree[ih]->SetBranchAddress((sFEB+"_BoardTemperature").c_str(),&FEB[ih].BoardTemperature);
            FEBtree[ih]->SetBranchAddress((sFEB+"_BoardHumidity").c_str(),&FEB[ih].BoardHumidity);
            
            nentries[ih] = FEBtree[ih]->GetEntries();
            std::cout << "Number of Spills = " <<nentries[ih]<<std::endl;
        }
  	}
  
  	TFile wfile(rootFileOutput.c_str(), "recreate");

  	TH1F *NumberOfSpills = new TH1F("Number of Spills per FEB","Number of Spills per FEB",NumberOfFEB+1,0,NumberOfFEB);
  	for (int ih=0; ih<FEBnumbers.size();ih++){
  		NumberOfSpills->Fill(FEBnumbers.at(ih),nentries[FEBnumbers.at(ih)]);
  	}
  	NumberOfSpills->GetYaxis()->SetTitle("Number of Spills");
    NumberOfSpills->GetXaxis()->SetTitle("FEB");
  	NumberOfSpills->Write();
    NumberOfSpills->Delete();

    TH1F *ChannelsCheck[FEBnumbers.size()];
    TDirectory *ChCheck = wfile.mkdir("Channel Check");

    vector<double> SpillTimeGTrigCheck[NumberOfFEB];
    vector<double> SpillNumCheck[NumberOfFEB];

    TH1F *NumMissedSpills = new TH1F("Number of missed Spills","Number of missed Spills",NumberOfFEB+1,0,NumberOfFEB);
    NumMissedSpills->GetYaxis()->SetTitle("Number of Spills");
    NumMissedSpills->GetXaxis()->SetTitle("FEB");

    for (Int_t iFEB=0; iFEB < FEBnumbers.size();iFEB++){
        sFEBnum.str("");            
        sFEBnum << FEBnumbers.at(iFEB);
        sFEB =  "FEB_" + sFEBnum.str()+" number of events per ch";
        ChannelsCheck[FEBnumbers.at(iFEB)]=new TH1F(sFEB.c_str(),sFEB.c_str(),96,0,95);
    
    	cout<<"FEB "<<FEBnumbers.at(iFEB)<<" is in process."<<endl;
    	SpillTimeGTrigCheck[FEBnumbers.at(iFEB)].clear();
    	SpillNumCheck[FEBnumbers.at(iFEB)].clear();
    	for (int in =0; in < nentries[FEBnumbers.at(iFEB)]; in++){
    		FEBtree[FEBnumbers.at(iFEB)]->GetEntry(in);
            //cout<<in<< " " <<FEB[FEBnumbers.at(iFEB)].SpillNum->back()<<endl;
    		SpillTimeGTrigCheck[FEBnumbers.at(iFEB)].push_back(FEB[FEBnumbers.at(iFEB)].SpillTimeGTrig->front());
    		SpillNumCheck[FEBnumbers.at(iFEB)].push_back(FEB[FEBnumbers.at(iFEB)].SpillNum->back());
    		for (int i=0;i<FEB[FEBnumbers.at(iFEB)].hitsChannel->size(); i++){
    			ChannelsCheck[FEBnumbers.at(iFEB)]->Fill(FEB[FEBnumbers.at(iFEB)].hitsChannel->at(i),1);
    		}
    		
    		
    	}

    	ChCheck->cd();
    	ChannelsCheck[FEBnumbers.at(iFEB)]->GetYaxis()->SetTitle("Number of events");
    	ChannelsCheck[FEBnumbers.at(iFEB)]->GetXaxis()->SetTitle("Channel");
    	ChannelsCheck[FEBnumbers.at(iFEB)]->Write();
    	ChannelsCheck[FEBnumbers.at(iFEB)]->Delete();
    }

    for (int ih=0;ih<SpillTimeGTrigCheck[0].size();ih++){
    	for (Int_t iFEB=1; iFEB < FEBnumbers.size();iFEB++){ 
    		if (SpillNumCheck[0].at(ih)!=SpillNumCheck[FEBnumbers.at(iFEB)].at(ih)){
    			cout<<SpillNumCheck[0].at(ih)<<" FEB_"<<FEBnumbers.at(iFEB)<<" "<<SpillNumCheck[FEBnumbers.at(iFEB)].at(ih)<<endl;
    		}
    		if (SpillTimeGTrigCheck[FEBnumbers.at(iFEB)].at(ih)!=SpillTimeGTrigCheck[0].at(ih) && SpillTimeGTrigCheck[FEBnumbers.at(iFEB)].at(ih)!=-1){
                if (SpillTimeGTrigCheck[FEBnumbers.at(iFEB)].at(ih)!=-1){
                    //cout<<FEBnumbers.at(iFEB)<<" "<<SpillNumCheck[FEBnumbers.at(iFEB)].at(ih)<<" "<<SpillTimeGTrigCheck[FEBnumbers.at(iFEB)].at(ih)<<"!="<<SpillTimeGTrigCheck[0].at(ih)<<endl;
                } else {
                    NumMissedSpills->Fill(FEBnumbers.at(iFEB),1);
                    cout<<FEBnumbers.at(iFEB)<<" "<<SpillNumCheck[FEBnumbers.at(iFEB)].at(ih)<<" "<<SpillTimeGTrigCheck[FEBnumbers.at(iFEB)].at(ih)<<"!="<<SpillTimeGTrigCheck[0].at(ih)<<endl;
                }
    		}
    	}
    }
    wfile.cd();
    NumMissedSpills->Write();
    NumMissedSpills->Delete();
  	FileInput->Close();
  	wfile.Close();
  	return 0;
}

