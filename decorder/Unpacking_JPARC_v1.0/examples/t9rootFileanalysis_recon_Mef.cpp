#include <stdio.h>
#include <string.h>
#include <exception>
#include <fstream>
#include <vector>
#include "TFile.h"
#include "TDirectory.h"
#include "TH1D.h"
#include "TSystem.h"
#include "TMacro.h"
#include <TTree.h>
#include <iostream>
#include <sstream>
#include "TH2.h"
#include "TH1.h"
#include "TH3.h"
#include <iterator>
#include <algorithm>
#include "TF1.h"



using namespace std;

double min(double x, double y){
    if ( x < y ) {
        return x;
    } else {
        return y;
    }
}


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
  vector<double> *GTrigTag;
  vector<double> *GTrigTime;
  vector<double> *hitsChannel;
  vector<double> *hitAmpl;
  vector<double> *hitLGAmpl;
  vector<double> *hitLeadTime;
  vector<double> *hitTrailTime;
  vector<double> *hitTimeDif;
  
  vector<double> *hitAmplRec;
  vector<double> *hitLGAmplRec;
  vector<double> *hitHG_pe;
  vector<double> *hitLG_pe;
  vector<double> *hitToT_pe;
  vector<double> *hitCharge_pe;
  vector<double> *hitTimefromSpill;
  
};

int main ()
{
    int NumberOfEB=65;
    int NumberOfMod = 18;
    int NumberofEventsMonitor = 4000;
    int firstModule = 0;
    
    vector<string> vFileNames;
    string sFileName;
    ifstream fList("febs_files_list.list");
    while (!fList.eof()) {
        fList >> sFileName;
        vFileNames.push_back(sFileName);
    }
    string rootFileInput=GetLocation(vFileNames[0].c_str());
    rootFileInput+="_all_reconstructed.root";
    cout << rootFileInput<<endl;
    
    TFile *FileInput = new TFile(rootFileInput.c_str());
    
    ifstream fmap("connection.map");
    int MapCon[5][19];
    int temp=firstModule;
    while (!fmap.eof()) {
        fmap >> MapCon[0][temp] >> MapCon[1][temp] >>MapCon[2][temp] >>MapCon[3][temp] >>MapCon[4][temp] ;
        //cout<<MapCon[0][temp]<<" "<<MapCon[1][temp]<<" "<<MapCon[2][temp]<<" "<<MapCon[3][temp]<<" "<<MapCon[4][temp]<<endl;
        temp++;
    }
    fmap.close();
    
    ifstream horizontalgeometry("v1_horizontal_from_center.txt");
    double geomHor[5][95];
    temp = 0;
    while (!horizontalgeometry.eof()){
        horizontalgeometry >> geomHor[0][temp] >> geomHor[1][temp] >> geomHor[2][temp] >> geomHor[3][temp] >> geomHor[4][temp] ;
        //cout << geomHor[0][temp]<<" " << geomHor[1][temp]<<" " << geomHor[2][temp]<<" " << geomHor[3][temp]<<" " << geomHor[4][temp] << endl;
        temp++;
    }
    horizontalgeometry.close();
    
     ifstream verticalgeometry("v1_vertical_from_center.txt");
    double geomVer[5][32];
    temp = 0;
    while (!verticalgeometry.eof()){
        verticalgeometry >> geomVer[0][temp] >> geomVer[1][temp] >> geomVer[2][temp] >> geomVer[3][temp] >> geomVer[4][temp] ;
        //cout << geomVer[0][temp]<<" " << geomVer[1][temp]<<" " << geomVer[2][temp]<<" " << geomVer[3][temp]<<" " << geomVer[4][temp] << endl;
        temp++;
    }
    verticalgeometry.close();
    
    
    ifstream ScinModPos("Scin_Mod_position.txt");
    double ModPos[4][19];
    temp = firstModule;
    while(!ScinModPos.eof()){
        ScinModPos >> ModPos[0][temp] >> ModPos[1][temp] >> ModPos[2][temp] >> ModPos[3][temp];
        //cout << ModPos[0][temp] <<" " << ModPos[1][temp] <<" " << ModPos[2][temp] <<" " << ModPos[3][temp] << endl;
        temp++;
    }
    ScinModPos.close();
    
    ifstream AidaTop("AIDA_horizontal_top.txt"); 
    double AidaGeomTop[2][96];
    temp = 0;
    while (!AidaTop.eof()){
        AidaTop >> temp >> AidaGeomTop[0][temp] >> AidaGeomTop[1][temp];
        //cout << temp <<" " << AidaGeomTop[0][temp] << " " << AidaGeomTop[1][temp]<< endl;;
    }
    AidaTop.close();
    
    ifstream AidaSide("AIDA_vertical_side.txt"); 
    double AidaGeomSide[2][96];
    temp = 0;
    while (!AidaSide.eof()){
        AidaSide >> temp >> AidaGeomSide[0][temp] >> AidaGeomSide[1][temp];
        //cout << temp <<" " << AidaGeomSide[0][temp] << " " << AidaGeomSide[1][temp]<<endl;
    }
    AidaSide.close();
    
    ifstream EnergyDep("EnegyDep.txt"); 
    double EnDep[6][19];
    temp = 0;
    while (!EnergyDep.eof()){
        EnergyDep >> temp >> EnDep[0][temp] >> EnDep[1][temp] >> EnDep[2][temp] >> EnDep[3][temp] >> EnDep[4][temp] >> EnDep[5][temp];
        //cout << temp << " " <<EnDep[0][temp] << " "<< EnDep[1][temp] << " " << EnDep[2][temp] << " " << EnDep[3][temp] << " " << EnDep[4][temp] << " " << EnDep[5][temp] << endl;
    }
    EnergyDep.close();

    vectorsTree FEB[NumberOfEB];
    
    for (Int_t i=0;i<NumberOfEB;i++){
        FEB[i].FEBSN=0;
        FEB[i].SpillNum=0;
        FEB[i].SpillTime=0;
        FEB[i].hitsChannel=0;
        FEB[i].hitAmpl=0;
        FEB[i].hitLeadTime=0;
        FEB[i].GTrigTag=0;
        FEB[i].GTrigTime=0;
        FEB[i].hitLGAmpl=0;
        FEB[i].hitTrailTime=0;
        FEB[i].hitTimeDif=0;
        
        FEB[i].hitAmplRec=0;
        FEB[i].hitLGAmplRec=0;
        FEB[i].hitHG_pe=0;
        FEB[i].hitLG_pe=0;
        FEB[i].hitToT_pe=0;
        FEB[i].hitCharge_pe=0;
        FEB[i].hitTimefromSpill=0;
        
    }
    
    TTree *FEBtree[NumberOfEB];
    Long64_t nentries[64];
    std::fill(nentries, nentries + 64, 0);
    vector<int> FEBnumbers;
    FEBnumbers.clear();
    
    ostringstream sFEBnum;
    string sFEB;
    for (Int_t ih=0; ih<NumberOfEB; ih++) {
        sFEBnum.str("");
        sFEBnum << ih;
        sFEB = "FEB_"+sFEBnum.str();
        FEBtree[ih] = (TTree*)FileInput->Get(sFEB.c_str());
        if ((TTree*)FileInput->Get(sFEB.c_str())){
            FEBnumbers.push_back(ih);
            //std::cout<<sFEB<<" ";
            FEBtree[ih]->SetBranchAddress((sFEB+"_SN").c_str(), &FEB[ih].FEBSN);
            FEBtree[ih]->SetBranchAddress((sFEB+"_SpillTag").c_str(), &FEB[ih].SpillNum);
            FEBtree[ih]->SetBranchAddress((sFEB+"_SpillTime").c_str(), &FEB[ih].SpillTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_GTrigTag").c_str(), &FEB[ih].GTrigTag);
            FEBtree[ih]->SetBranchAddress((sFEB+"_GTrigTime").c_str(), &FEB[ih].GTrigTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitsChannel").c_str(), &FEB[ih].hitsChannel);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitAmpl").c_str(), &FEB[ih].hitAmpl);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLGAmpl").c_str(), &FEB[ih].hitLGAmpl);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLeadTime").c_str(), &FEB[ih].hitLeadTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTrailTime").c_str(), &FEB[ih].hitTrailTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTimeDif").c_str(), &FEB[ih].hitTimeDif);
            
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitAmplRecon").c_str(), &FEB[ih].hitAmplRec);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLGAmplRecon").c_str(), &FEB[ih].hitLGAmplRec);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTimefromSpill").c_str(), &FEB[ih].hitTimefromSpill);
        
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitHG_pe").c_str(), &FEB[ih].hitHG_pe);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLG_pe").c_str(), &FEB[ih].hitLG_pe);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitToT_pe").c_str(), &FEB[ih].hitToT_pe);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitCharge_pe").c_str(), &FEB[ih].hitCharge_pe);
           
            nentries[ih] = FEBtree[ih]->GetEntries();
        }
  }
 
 
    double minEn = nentries[0];
    for(int i = 0; i < 64; i++){
        if(nentries[i] < minEn && nentries[i]>0){
            minEn = nentries[i];
        }
    }
    cout << "Number of spills " << minEn << endl;
     
     bool SpillMised = false;
     ostringstream sRootOut;
     int SpillInFile = 50;
    //for (Int_t DecSpillNumber = 0 ; DecSpillNumber < 100; DecSpillNumber+=SpillInFile){
    for (Int_t DecSpillNumber = 1 ; DecSpillNumber < minEn - 1 ; DecSpillNumber+=SpillInFile){
      string rootFileOutput=GetLocation (vFileNames[0].c_str());
      sRootOut.str("");
      sRootOut << DecSpillNumber;
      rootFileOutput= rootFileOutput+ "_Spill_" + sRootOut.str() + "_histo.root";
      cout << rootFileOutput<<endl;
      TFile wfile(rootFileOutput.c_str(), "recreate");
      
      TDirectory *eventsD = wfile.mkdir("eventsDispHor");
      TDirectory *eventsTime = wfile.mkdir("eventsDispTime");
      TDirectory *events3D = wfile.mkdir("events3D");  
      
      TH2F *EventsMap = new TH2F("All_events_map","All_events_map",  198, -2200, 5720, 95, -986.2, 986.2);
      TH3D *EventsMap3D = new TH3D ("All_events_map_3D","All_events_map_3D", 198, -2200, 5720, 16, -1420.5, 1420.5, 95,  -986.2, 986.2);
      
      TH2F *SingleEvent[NumberofEventsMonitor];
      TH1F *SingleEventTime[NumberofEventsMonitor];
      TH3F *SingleEvent3D[NumberofEventsMonitor];
      
      TH1F *LostEnergy = new TH1F("Energy_deposit","Energy_deposit",  440, -2200, 2200);
    
      for (Int_t subSpill = 0; subSpill<SpillInFile; subSpill++) {
      //for (Int_t subSpill = 0; subSpill<10; subSpill++) {  
      Int_t SpillNumber = DecSpillNumber + subSpill;
        if ( SpillNumber == minEn ) break; //error!!!
        
        cout << "Getting Spill Number " << SpillNumber << endl;
        for (int ik=0; ik<FEBnumbers.size(); ik++){
            //cout<<FEBnumbers.at(ik)<<endl;
            FEBtree[FEBnumbers.at(ik)]->GetEntry(SpillNumber - 1);
            if (FEB[FEBnumbers.at(ik)].SpillNum->back() != SpillNumber){
                cout << "Problems with spill number" <<endl;
            }
            if (FEB[FEBnumbers.at(ik)].SpillNum->size() < 2 ){
                cout << "NULL"<<endl;
                SpillMised = true;
                break;
            } else {
                SpillMised = false;
            }
        }
        if (!SpillMised){
        
        Int_t numberevents = 0;
        vector <double> GTrigTagCoins;
        GTrigTagCoins.clear();

        Int_t AIDAindex[2]={0,0};
       
        for (Int_t i =0; i < (FEB[0].GTrigTag->size() - 2); i++){
            if (FEB[0].GTrigTag->at(i) == FEB[0].GTrigTag->at(i+1)) {
                auto boundsAIDA=std::equal_range (FEB[8].GTrigTag->begin(), FEB[8].GTrigTag->end(), FEB[0].GTrigTag->at(i));
                AIDAindex[0] = boundsAIDA.first - FEB[8].GTrigTag->begin();
                AIDAindex[1] = boundsAIDA.second - FEB[8].GTrigTag->begin();
                if ( AIDAindex[1] - AIDAindex[0] >=1){
                    GTrigTagCoins.push_back(FEB[0].GTrigTag->at(i));
                    numberevents++;
                }
            }
        }
     
        cout << numberevents<<" "<< GTrigTagCoins.size()<<" "<<GTrigTagCoins[0]<<" "<<GTrigTagCoins.back()<<endl;
        auto last = std::unique(GTrigTagCoins.begin(),GTrigTagCoins.end());
        GTrigTagCoins.erase(last, GTrigTagCoins.end()); 
        cout << numberevents<<" "<< GTrigTagCoins.size()<<" "<<GTrigTagCoins[0]<<" "<<GTrigTagCoins.back()<<endl;
     
        NumberofEventsMonitor = min (NumberofEventsMonitor,GTrigTagCoins.size());
        ostringstream sEventnum;
        string sEvent;
        string sEventTime;
        string sEvent3D;
        for (Int_t ih=0; ih <= NumberofEventsMonitor;ih++){
            sEventnum.str("");
            sEventnum << ih;
            sEventnum << "Spill_";
            sEventnum << SpillNumber;
            sEvent = "Event_"+sEventnum.str();
            sEventTime = sEvent + "_Time_in_2.5ns";
            sEvent3D =  sEvent + "_3D";
            SingleEvent[ih] = new TH2F(sEvent.c_str(),sEvent.c_str(),  198, -2200, 5720, 95, -986.2, 986.2);
            SingleEventTime[ih] = new TH1F(sEventTime.c_str(),sEventTime.c_str(), 4096, 0, 4096);
            SingleEvent3D[ih] = new TH3F(sEvent3D.c_str(),sEvent3D.c_str(),  198, -2200, 5720, 16, -1420.5, 1420.5, 95,  -986.2, 986.2);
        }
   
        Int_t leftindex[2]={0,0};
        Int_t rightindex[2]={0,0};
        Int_t topindex[2]={0,0};
        Int_t AIDAindex0[2]={0,0};
        Int_t AIDAindex8[2]={0,0};
        Int_t eventNumber=0;
        Double_t EventTimeFromSpill=0;
        
        int AllModulesExist[19][GTrigTagCoins.size()];
        for (int i=0; i < 19; i++){
            for (int j=0; j < GTrigTagCoins.size(); j++){
                AllModulesExist[i][j]=0;
            }
        }
        
        for (Int_t index=0; index <= GTrigTagCoins.size(); index++) {
            
            for (Int_t mod = 0; mod<=NumberOfMod;mod++){
                if (mod == 0){
                    auto boundsAIDA0=std::equal_range (FEB[0].GTrigTag->begin(), FEB[0].GTrigTag->end(), GTrigTagCoins[index]);
                    AIDAindex0[0] = boundsAIDA0.first - FEB[0].GTrigTag->begin();
                    AIDAindex0[1] = boundsAIDA0.second - FEB[0].GTrigTag->begin();
             
                    auto boundsAIDA8=std::equal_range (FEB[8].GTrigTag->begin(), FEB[8].GTrigTag->end(), GTrigTagCoins[index]);
                    AIDAindex8[0] = boundsAIDA8.first - FEB[8].GTrigTag->begin();
                    AIDAindex8[1] = boundsAIDA8.second - FEB[8].GTrigTag->begin();
             
                    for (Int_t CoinsAIDA0 = AIDAindex0[0]; CoinsAIDA0 < AIDAindex0[1]; CoinsAIDA0++){
                        for (Int_t CoinsAIDA8 = AIDAindex8[0]; CoinsAIDA8 < AIDAindex8[1]; CoinsAIDA8++){
                            if ( abs(FEB[0].hitTimefromSpill->at(CoinsAIDA0) - FEB[8].hitTimefromSpill->at(CoinsAIDA8)) < 20 && FEB[0].hitAmpl->at(CoinsAIDA0)>300 && FEB[8].hitAmpl->at(CoinsAIDA8)>300){
                                 if (eventNumber<NumberofEventsMonitor){
                                    AllModulesExist[mod][eventNumber]=1;
                                    SingleEvent[eventNumber] -> Fill(AidaGeomSide[1][(int)FEB[0].hitsChannel->at(CoinsAIDA0)],AidaGeomSide[0][(int)FEB[0].hitsChannel->at(CoinsAIDA0)],1); 
                                    SingleEventTime[eventNumber] -> Fill(FEB[0].hitLeadTime->at(CoinsAIDA0));
                                    SingleEventTime[eventNumber] -> Fill(FEB[8].hitLeadTime->at(CoinsAIDA8));
                                    
                                    EventTimeFromSpill = FEB[0].hitLeadTime->at(CoinsAIDA0);
                                 }
                            }
                        }
                    }
                }
                else{
                
                 auto boundsleft=std::equal_range (FEB[MapCon[1][mod]].GTrigTag->begin(), FEB[MapCon[1][mod]].GTrigTag->end(), GTrigTagCoins[index]);
                 leftindex[0] = boundsleft.first - FEB[MapCon[1][mod]].GTrigTag->begin();
                 leftindex[1] = boundsleft.second - FEB[MapCon[1][mod]].GTrigTag->begin();
                 
                 auto boundsright=std::equal_range (FEB[MapCon[2][mod]].GTrigTag->begin(), FEB[MapCon[2][mod]].GTrigTag->end(), GTrigTagCoins[index]);
                 rightindex[0] = boundsright.first - FEB[MapCon[2][mod]].GTrigTag->begin();
                 rightindex[1] = boundsright.second - FEB[MapCon[2][mod]].GTrigTag->begin();
                 
                 auto boundstop = std::equal_range (FEB[MapCon[3][mod]].GTrigTag->begin(), FEB[MapCon[3][mod]].GTrigTag->end(), GTrigTagCoins[index]);
                 topindex[0] = boundstop.first - FEB[MapCon[3][mod]].GTrigTag->begin();
                 topindex[1] = boundstop.second - FEB[MapCon[3][mod]].GTrigTag->begin();
                 
                  if (leftindex[0]>0 && rightindex[0]>0){
                        for (Int_t CoinsLeft = leftindex[0]; CoinsLeft < leftindex[1]; CoinsLeft++){
                          for (Int_t CoinsRight = rightindex[0]; CoinsRight < rightindex[1]; CoinsRight++){
                              if (FEB[MapCon[1][mod]].hitsChannel->at(CoinsLeft) == FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight) && 
                                  abs(FEB[MapCon[1][mod]].hitLeadTime->at(CoinsLeft) - EventTimeFromSpill) < 40 && 
                                  abs(FEB[MapCon[2][mod]].hitLeadTime->at(CoinsRight) - EventTimeFromSpill) < 40){
                                  
                                  if (FEB[MapCon[1][mod]].hitAmpl->at(CoinsLeft) > 500 && FEB[MapCon[2][mod]].hitAmpl->at(CoinsRight)>500) {
                                      if (eventNumber<NumberofEventsMonitor){
                                        
                                        AllModulesExist[mod][eventNumber]=1;
                                        
                                        SingleEvent[eventNumber]->Fill(ModPos[3][mod],geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)],1) ; 
                                        SingleEventTime[eventNumber] -> Fill(FEB[MapCon[1][mod]].hitLeadTime->at(CoinsLeft));
                                        SingleEventTime[eventNumber] -> Fill(FEB[MapCon[2][mod]].hitLeadTime->at(CoinsRight));
                                        for (Int_t CoinsTop = topindex[0]; CoinsTop < topindex[1]; CoinsTop++){
                                            for (Int_t CoinsTop2 = CoinsTop; CoinsTop2 < topindex[1]; CoinsTop2++) {
                                                if ((int)(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop2)) == (int)(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop))){
                                                    if (FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop)>=32*MapCon[4][mod] && FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop)<32*(1+MapCon[4][mod])){
                                                        if (FEB[MapCon[3][mod]].hitAmpl->at(CoinsTop) > 200){
                                                            SingleEventTime[eventNumber] -> Fill(FEB[MapCon[3][mod]].hitLeadTime->at(CoinsTop));
                                                            if(mod == 2 || mod == 4 || mod == 14 || mod == 16 || mod == 18){
                                                                SingleEvent3D[eventNumber]->Fill(ModPos[3][mod],-geomVer[4][(int)(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop))%32],geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)],1);
                                                            }
                                                            else{
                                                                SingleEvent3D[eventNumber]->Fill(ModPos[3][mod],geomVer[4][(int)(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop))%32],geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)],1);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                      }
                                      
                                      EventsMap->Fill(ModPos[3][mod],geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)],1);
                                      
                                      for (Int_t CoinsTop = topindex[0]; CoinsTop < topindex[1]; CoinsTop++){
                                           for (Int_t CoinsTop2 = CoinsTop; CoinsTop2 < topindex[1]; CoinsTop2++) {
                                                if (FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop)>=32*MapCon[4][mod] && FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop)<32*(1+MapCon[4][mod])){
                                                    if (FEB[MapCon[3][mod]].hitAmpl->at(CoinsTop) > 200){
                                                        if(mod == 2 || mod == 4 || mod == 14 || mod == 16 || mod == 18){
                                                            EventsMap3D->Fill(ModPos[3][mod],-geomVer[4][(int)(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop))%32],geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)],1);
                                                        }
                                                        else{
                                                            EventsMap3D->Fill(ModPos[3][mod],geomVer[4][(int)(FEB[MapCon[3][mod]].hitsChannel->at(CoinsTop))%32],geomHor[4][(int)FEB[MapCon[2][mod]].hitsChannel->at(CoinsRight)],1);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                }
                              }
                          }
                        }
                  }
            }
            }
            eventNumber++;
        }
        GTrigTagCoins.clear();

        eventsD->cd();
        
        for (Int_t ih=0; ih < NumberofEventsMonitor;ih++){
            if (SingleEvent[ih]->GetEntries()>5 ) {
                int NumberOfModEx = 0;
                int LastFiredMod = 0;
                Double_t ReconLostEnergy = 0;
                for (int mod=0; mod < 18; mod++){
                    if (AllModulesExist[mod][ih]==1){ 
                        NumberOfModEx++;
                        LastFiredMod=mod;
                    }
                }
                if (NumberOfModEx>3){
                
                    TF1 *f[18];
                    Double_t par[36];
                    std::fill(par, par + 36, 0);
                    ostringstream sFitNum;
                    string sFit;
                    for (int th=0; th<18;th++){
                        sFit = sEventnum.str();
                       // f[th] = new TF1(sFit.c_str(),"pol1",ModPos[1][th],ModPos[2][th+1]);
                        //cout<< "Real event:"<<SpillNumber<<" "<< ih <<" fit"<< " "<< th <<" mod:" <<th<<" ModEx"<<AllModulesExist[th][ih]<<" ModPos:"<< ModPos[1][th]<< " " <<ModPos[2][th+1]<<endl;
                        if (AllModulesExist[th][ih]==1){
                            if (AllModulesExist[th+1][ih]==1) {
                                sFitNum.str("");
                                sFitNum << th;
                                sFitNum << "f";
                                sFit = sEventnum.str();
                                f[th] = new TF1(sFit.c_str(),"pol1",ModPos[1][th],ModPos[2][th+1]);
                               // cout<< ih<<"            fit:"<<SpillNumber<<" "<< th <<" mod:" <<th<<" ModEx"<<AllModulesExist[th][ih]<<" ModPos:"<< ModPos[1][th]<< " " <<ModPos[2][th+1]<<endl;
                                SingleEvent[ih]->Fit(f[th],"MQWR+");
                                //SingleEvent[ih]->Fit(f[th],"MWR+");
                                f[th]->GetParameters(&par[2*th]);
                                //cout<<"Fit parameters "<<par[2*th]<< " "<<par[2*th+1]<<endl;
                            } else {
                                int fitStart=th;
                                for (int nextMod = 1; nextMod + th <18; nextMod++ ){
                                    if (AllModulesExist[nextMod + th][ih]==1) {
                                        th = th+nextMod;
                                        sFitNum.str("");
                                        sFitNum << th;
                                        sFitNum << "f";
                                        sFit = sEventnum.str();
                                        f[th] = new TF1(sFit.c_str(),"pol1",ModPos[1][fitStart],ModPos[2][th]);
                                        //cout<< ih<<"            fit:"<<SpillNumber<<" "<< th <<" mod:" <<th<<" ModEx"<<AllModulesExist[th][ih]<<" ModPos:"<< ModPos[1][fitStart]<< " " <<ModPos[2][th]<<endl;
                                        SingleEvent[ih]->Fit(f[th],"MQWR+");
                                        f[th]->GetParameters(&par[2*th]);
                                        th--;
                                        break;
                                    }
                                }
                            }
                        } 
                    }
                    
                    SingleEvent[ih]->GetYaxis()->SetTitle("vertical position [mm]");
                    SingleEvent[ih]->GetXaxis()->SetTitle("horizontal position [mm]");
                    SingleEvent[ih]->SetMarkerStyle(2);
                    SingleEvent[ih]->Write();
                    //cout << "Fitting done ";
                    
                    for (int th=0; th<LastFiredMod;th++){
                        if(par[2*th] != 0 || par[2*th+1] != 0){
                            ReconLostEnergy += (EnDep[3][th]) * sqrt( 1 + par[2*th+1]*par[2*th+1]);
                            //cout << th << ": " << par[2*th] << " "<< par[2*th+1] << endl;
                        } else {
                            //cout << 0 << endl;
                            for (int ith=0; th - ith > 0; ith++){
                                if(par[2*(th - ith)] != 0 || par[2*(th - ith)+1] != 0){
                              //      cout << th << ": " << par[2*(th - ith)] << " "<< par[2*(th - ith)+1] << endl;
                                    ReconLostEnergy += (EnDep[3][th]) * sqrt( 1 + par[2*th+1]*par[2*th+1]);
                                    break;
                                }
                            }
                        }
                    }
                    
                    LostEnergy->Fill(ReconLostEnergy,1);
                }
            }
        delete SingleEvent[ih];
        }
     
        events3D->cd();
        for (Int_t ih=0; ih < NumberofEventsMonitor;ih++){
            if (SingleEvent3D[ih]->GetEntries()>5) {
                SingleEvent3D[ih]->GetYaxis()->SetTitle("X position [mm]");
                SingleEvent3D[ih]->GetXaxis()->SetTitle("Z position [mm]");  
                SingleEvent3D[ih]->GetZaxis()->SetTitle("Y position [mm]");  
                SingleEvent3D[ih]->Write();
            }
        delete SingleEvent3D[ih];
        }
     
        eventsTime->cd();
        for (Int_t ih=0; ih < NumberofEventsMonitor;ih++){
            if (SingleEventTime[ih]->GetEntries()>5) {
                SingleEventTime[ih]->GetYaxis()->SetTitle("Number of events");
                SingleEventTime[ih]->GetXaxis()->SetTitle("Hit time [2.5ns]");
                SingleEventTime[ih]->Write();
            }
        delete SingleEventTime[ih];
        }
           
        for (Int_t i=0;i<NumberOfEB;i++){
            //std::vector<double>().swap(FEB[i].FEBSN&);
            //for (int j = 0 ; j< FEB[i].FEBSN->size();j++)
            
            free (FEB[i].FEBSN);
            free (FEB[i].SpillNum);
            free (FEB[i].SpillTime);
            free (FEB[i].hitsChannel);
            free (FEB[i].hitAmpl);
            free (FEB[i].hitLeadTime);
            free (FEB[i].GTrigTag);
            free (FEB[i].GTrigTime);
            free (FEB[i].hitLGAmpl);
            free (FEB[i].hitTrailTime);
            free (FEB[i].hitTimeDif);
            
            free (FEB[i].hitAmplRec);
            free (FEB[i].hitLGAmplRec);
            free (FEB[i].hitHG_pe);
            free (FEB[i].hitLG_pe);
            free (FEB[i].hitToT_pe);
            free (FEB[i].hitCharge_pe);
            free (FEB[i].hitTimefromSpill);
            
            FEB[i].FEBSN=0;
            FEB[i].SpillNum=0;
            FEB[i].SpillTime=0;
            FEB[i].hitsChannel=0;
            FEB[i].hitAmpl=0;
            FEB[i].hitLeadTime=0;
            FEB[i].GTrigTag=0;
            FEB[i].GTrigTime=0;
            FEB[i].hitLGAmpl=0;
            FEB[i].hitTrailTime=0;
            FEB[i].hitTimeDif=0;
            
            FEB[i].hitAmplRec=0;
            FEB[i].hitLGAmplRec=0;
            FEB[i].hitHG_pe=0;
            FEB[i].hitLG_pe=0;
            FEB[i].hitToT_pe=0;
            FEB[i].hitCharge_pe=0;
            FEB[i].hitTimefromSpill=0;
        }
    }
    }
   
     wfile.cd();
     EventsMap->GetYaxis()->SetTitle("Y [mm]");
     EventsMap->GetXaxis()->SetTitle("Z [mm]");           
     EventsMap->Write();
     delete  EventsMap;
     
     EventsMap3D->GetYaxis()->SetTitle("X position [mm]");
     EventsMap3D->GetXaxis()->SetTitle("Z position [mm]");  
     EventsMap3D->GetZaxis()->SetTitle("Y position [mm]");  
     EventsMap3D->Write();
     delete EventsMap3D;
     
     LostEnergy->Write();
     delete LostEnergy;
     
    wfile.Close();
    wfile.Clear();
    wfile.Delete();
}
    FileInput->Close();
    vFileNames.clear();
    fList.close();
    return 0;
}
