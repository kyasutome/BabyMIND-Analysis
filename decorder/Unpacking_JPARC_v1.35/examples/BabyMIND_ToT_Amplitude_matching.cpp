#include <stdio.h>
#include <string.h>
#include <exception>
#include <fstream>
#include <vector>
#include "TFile.h"
#include "TDirectory.h"
#include "TSystem.h"
#include "TMacro.h"
#include <TTree.h>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cmath>

using namespace std;


string GetLocation(string str){    
    int i = str.rfind("_Slot_");
    string way = str.substr(0,i);  
    return way;
}

struct vectorsTree{
  vector<double> *FEBSN;
  vector<double> *SpillNum;
  vector<double> *SpillTime;
  vector<double> *SpillTimeGTrig;
  vector<double> *GTrigTag;
  vector<double> *GTrigTime;
  vector<double> L1HoldNumber;
  vector<double> *hitsChannel;
  vector<double> *hitAmpl;
  vector<double> hitAmplMatched;
  vector<double> *hitLGAmpl;
  vector<double> hitLGAmplMatched;
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

int main (){   
    int NumberOfFEB=65;
    
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
    rootFileOutput+="_all_matching.root";
    cout << rootFileInput<<endl;
    cout << rootFileOutput<<endl;
    TFile *FileInput = new TFile(rootFileInput.c_str());
    
    TFile wfile(rootFileOutput.c_str(), "recreate");
    TTree* FEBtreer[65];
    
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
    Long64_t nentries[64];
    FEBnumbers.clear();
    
    ostringstream sFEBnum;
    string sFEB;
    for (Int_t ih=0; ih<NumberOfFEB; ih++){
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
            cout<< "Number of spills "<< nentries[ih] <<endl;

            cout <<"FEB " <<ih<<" in process."<<endl;
            sFEBnum.str("");
            sFEBnum << ih;
            sFEB = "FEB_"+sFEBnum.str();
        
            FEBtreer[ih] = new TTree(sFEB.c_str(),sFEB.c_str()); 
    
            FEBtreer[ih]->Branch((sFEB+"_SN").c_str(),"vector<double>",&FEB[ih].FEBSN);
            FEBtreer[ih]->Branch((sFEB+"_SpillTag").c_str(),"vector<double>",&FEB[ih].SpillNum);
            FEBtreer[ih]->Branch((sFEB+"_SpillTime").c_str(),"vector<double>",&FEB[ih].SpillTime);
            FEBtreer[ih]->Branch((sFEB+"_SpillTimeGTrig").c_str(),"vector<double>",&FEB[ih].SpillTimeGTrig);
            FEBtreer[ih]->Branch((sFEB+"_GTrigTag").c_str(),"vector<double>",&FEB[ih].GTrigTag);
            FEBtreer[ih]->Branch((sFEB+"_GTrigTime").c_str(),"vector<double>",&FEB[ih].GTrigTime);
            FEBtreer[ih]->Branch((sFEB+"_L1HoldNumber").c_str(),"vector<double>",&FEB[ih].L1HoldNumber);
            FEBtreer[ih]->Branch((sFEB+"_hitsChannel").c_str(),"vector<double>",&FEB[ih].hitsChannel);
            FEBtreer[ih]->Branch((sFEB+"_hitAmpl").c_str(),"vector<double>",&FEB[ih].hitAmpl);
            FEBtreer[ih]->Branch((sFEB+"_hitAmplMatched").c_str(),"vector<double>",&FEB[ih].hitAmplMatched);
            FEBtreer[ih]->Branch((sFEB+"_hitLGAmpl").c_str(),"vector<double>",&FEB[ih].hitLGAmpl);
            FEBtreer[ih]->Branch((sFEB+"_hitLGAmplMatched").c_str(),"vector<double>",&FEB[ih].hitLGAmplMatched);
            FEBtreer[ih]->Branch((sFEB+"_hitLeadTime").c_str(),"vector<double>",&FEB[ih].hitLeadTime);
            FEBtreer[ih]->Branch((sFEB+"_hitTrailTime").c_str(),"vector<double>",&FEB[ih].hitTrailTime);
            FEBtreer[ih]->Branch((sFEB+"_hitTimeDif").c_str(),"vector<double>",&FEB[ih].hitTimeDif);
            FEBtreer[ih]->Branch((sFEB+"_hitTimefromSpill").c_str(),"vector<double>",&FEB[ih].hitTimefromSpill);
            FEBtreer[ih]->Branch((sFEB+"_SpillTrailTime").c_str(),"vector<double>",&FEB[ih].SpillTrailTime);
            FEBtreer[ih]->Branch((sFEB+"_AsicTemperature").c_str(),"vector<double>",&FEB[ih].AsicTemperature);
            FEBtreer[ih]->Branch((sFEB+"_FPGATemperature").c_str(),"vector<double>",&FEB[ih].FPGATemperature);
            FEBtreer[ih]->Branch((sFEB+"_GlobalHV").c_str(),"vector<double>",&FEB[ih].GlobalHV);
            FEBtreer[ih]->Branch((sFEB+"_BoardTemperature").c_str(),"vector<double>",&FEB[ih].BoardTemperature);
            FEBtreer[ih]->Branch((sFEB+"_BoardHumidity").c_str(),"vector<double>",&FEB[ih].BoardHumidity);
        
            std::vector<double> HitAmplForMathing[96];
            std::vector<double> HitLGAmplForMathing[96];
            std::vector<double> HitTimeForMathing[2];
            std::vector<double> HitToTForMathing[96][20][3];
            for (int ik = 0; ik < nentries[ih]; ik++){
                for (int ich = 0; ich < 96; ++ich){
                    HitAmplForMathing[ich].clear();
                    HitLGAmplForMathing[ich].clear();
                    for (int im=0; im<20;im++){
                        HitToTForMathing[ich][im][0].clear();
                        HitToTForMathing[ich][im][1].clear();
                        HitToTForMathing[ich][im][2].clear();
                    }
                }
                for (int num = 0 ; num<2 ;num++){
                    HitTimeForMathing[num].clear();
                }
                
                FEBtree[ih]->GetEntry(ik);
                if (FEB[ih].SpillTimeGTrig->back()!=-1){
                    for ( Int_t iev=0; iev < FEB[ih].FEBSN->size(); iev++){
                        HitToTForMathing[(int)FEB[ih].hitsChannel->at(iev)][HitAmplForMathing[(int)FEB[ih].hitsChannel->at(iev)].size()][0].push_back(FEB[ih].hitTimeDif->at(iev));
                        HitTimeForMathing[0].push_back(FEB[ih].hitsChannel->at(iev));
                        HitTimeForMathing[1].push_back(HitAmplForMathing[(int)FEB[ih].hitsChannel->at(iev)].size());

                        FEB[ih].L1HoldNumber.push_back( HitAmplForMathing[(int)FEB[ih].hitsChannel->at(iev)].size());
                        if (FEB[ih].hitAmpl->at(iev)>0){
                            HitAmplForMathing[(int)FEB[ih].hitsChannel->at(iev)].push_back(FEB[ih].hitAmpl->at(iev));
                            HitLGAmplForMathing[(int)FEB[ih].hitsChannel->at(iev)].push_back(FEB[ih].hitLGAmpl->at(iev));
                        }
                    }
                    int Dum = 0;
                    for (int ich = 0; ich < 96; ++ich){
                        for (int im = 0; im < 15; ++im){
                            Dum+=HitToTForMathing[ich][im][0].size();
                        }
                    }
                    if (FEB[ih].FEBSN->size() != Dum ){
                        cout<<"Error "<<FEB[ih].FEBSN->size()<<" != "<<Dum<<endl;
                        return -1;
                    }

                    for (int ich = 0; ich < 96; ++ich){
                        for (int im = 0; im < HitAmplForMathing[ich].size() + 1; ++im){
                            if ( im < HitAmplForMathing[ich].size() ){
                                auto it = max_element(std::begin(HitToTForMathing[ich][im][0]), std::end(HitToTForMathing[ich][im][0]));
                                //cout << *it << " -- max " << std::distance(std::begin(HitToTForMathing[ich][im][0]), it)<<" -- position ";
                                for (int i = 0; i < HitToTForMathing[ich][im][0].size(); ++i){
                                    //cout << HitToTForMathing[ich][im][0].at(i)<< " ";
                                    if ( i == std::distance(std::begin(HitToTForMathing[ich][im][0]), it)){
                                        //FEB[ih].hitAmplMatched.push_back(HitAmplForMathing[ich].at(im));
                                        HitToTForMathing[ich][im][1].push_back(HitAmplForMathing[ich].at(im));
                                        HitToTForMathing[ich][im][2].push_back(HitLGAmplForMathing[ich].at(im));
                                        //cout<<"here ";
                                    } else {
                                        //FEB[ih].hitAmplMatched.push_back(0);
                                        HitToTForMathing[ich][im][1].push_back(0);
                                        HitToTForMathing[ich][im][2].push_back(0);
                                    }
                                    //FEB[ih].hitLGAmplMatched.push_back(HitToTForMathing[ich][im][0].at(i));
                                }
                            //cout <<" ---- ch"<< ich <<" Amp:"<<HitAmplForMathing[ich].at(im)<< " ToT:"<<HitToTForMathing[ich][im][0].size() <<endl;
                            } else {
                                for (int i = 0; i < HitToTForMathing[ich][im][0].size(); ++i){
                                    //FEB[ih].hitAmplMatched.push_back(0);
                                    //FEB[ih].hitLGAmplMatched.push_back(HitToTForMathing[ich][im][0].at(i));
                                    HitToTForMathing[ich][im][1].push_back(0);
                                    HitToTForMathing[ich][im][2].push_back(0);
                                }
                            }
                        }
                    } 
                    for (int in = 0; in < FEB[ih].FEBSN->size(); in++){
                        int ch = (int)HitTimeForMathing[0].at(in);
                        int L1Hold = (int)HitTimeForMathing[1].at(in);
                        FEB[ih].hitAmplMatched.push_back( HitToTForMathing[ch][L1Hold][1].front());
                        FEB[ih].hitLGAmplMatched.push_back( HitToTForMathing[ch][L1Hold][2].front());
                        HitToTForMathing[ch][L1Hold][1].erase(HitToTForMathing[ch][L1Hold][1].begin());
                        HitToTForMathing[ch][L1Hold][2].erase(HitToTForMathing[ch][L1Hold][2].begin());
                        
                    }

                } else {
                    FEB[ih].hitLGAmplMatched.push_back(-1);
                    FEB[ih].hitAmplMatched.push_back(-1);
                    FEB[ih].L1HoldNumber.push_back(-1);
                }

                FEBtreer[ih]->Fill();
        
                FEB[ih].FEBSN->clear();
                FEB[ih].SpillNum->clear();
                FEB[ih].SpillTime->clear();
                FEB[ih].SpillTimeGTrig->clear();
                FEB[ih].L1HoldNumber.clear();
                FEB[ih].hitsChannel->clear();
                FEB[ih].hitAmpl->clear();
                FEB[ih].hitAmplMatched.clear();
                FEB[ih].hitLeadTime->clear();
                FEB[ih].hitTrailTime->clear();
                FEB[ih].hitTimeDif->clear();
                FEB[ih].GTrigTag->clear();
                FEB[ih].GTrigTime->clear();
                FEB[ih].hitLGAmpl->clear();
                FEB[ih].hitLGAmplMatched.clear();
                FEB[ih].hitTimefromSpill->clear();
                FEB[ih].SpillTrailTime->clear();
                FEB[ih].AsicTemperature->clear();
                FEB[ih].FPGATemperature->clear();
                FEB[ih].GlobalHV->clear();
                FEB[ih].BoardTemperature->clear();
                FEB[ih].BoardHumidity->clear();
            }
            //cout << FEBtree[ih]->GetEntries()<<endl;
            FEBtreer[ih]-> Write("",TObject::kOverwrite);
            FEBtreer[ih]->Delete();

        }
    }
    FileInput->Close();
    wfile.Close();
    return 0;
}
