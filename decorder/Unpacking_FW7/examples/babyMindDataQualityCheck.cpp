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
#include "TH2.h"
#include "TDirectory.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TPaveText.h"


using namespace std;

string GetLocation(string str)
{
     
    int i = str.rfind("_Slot_");
    string way = str.substr(0,i);  
    return way;
}

std::vector<double> GetRealGTrig(int i, vector<double> GTrigCheck[]){
    std::vector<double> v;
    for (int j=0;j<GTrigCheck[0].size();j++){
        for (int ih = 0; ih < i; ++ih)
        {
            if (GTrigCheck[ih].size()>0 && GTrigCheck[ih].at(j)!=-1){
                v.push_back(GTrigCheck[ih].at(j));
                break;
            } else {
                if (ih == i-1)
                    v.push_back(-1);
            }
        }
    }
   // std::cout<<v.size()<<" "<<GTrigCheck[0].size();
    return v;
}

bool ChannelExist(int FEBnum, int chNum){
    bool ChEx = false;
    if (FEBnum == 5 || FEBnum == 53){
        ChEx = true;
    } else if (FEBnum == 13 || FEBnum == 20 || FEBnum == 28 || FEBnum == 36 || FEBnum == 44 || FEBnum == 61 ){
        if ( chNum <64 ) {
            ChEx = true;
        }
    } else if (FEBnum == 21 || FEBnum == 29) {
        if ( (chNum < 8 && chNum != 3) || (chNum > 31 && chNum < 39)){
            ChEx = true;
        }
    } else {
        if ( chNum < 95 ){
            ChEx = true;
        }
    }
    return ChEx;
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
    //Long64_t nentries[NumberOfFEB];
    std::vector<int> nentries;

    ostringstream sFEBnum;
    string sFEB;
    for (Int_t ih=0; ih<NumberOfFEB; ih++) {
        sFEBnum.str("");
        sFEBnum << ih;
        sFEB = "FEB_"+sFEBnum.str();
        FEBtree[ih] = (TTree*)FileInput->Get(sFEB.c_str());
        if ((TTree*)FileInput->Get(sFEB.c_str())){
            FEBnumbers.push_back(ih);
            //std::cout<<sFEB<<" ";
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
            
            nentries.push_back(FEBtree[ih]->GetEntries());
            //std::cout << "Number of Spills = " <<nentries.back()<<std::endl;
        }
  	}
  
  	TFile wfile(rootFileOutput.c_str(), "recreate");

    TDirectory *SummaryPlots = wfile.mkdir("Summary Plots");
    TDirectory *ChCheck = wfile.mkdir("Channel Check");
    TDirectory *SynchCheck = wfile.mkdir("Synchronization Check");
    TDirectory *NumEvatSpillFEB = wfile.mkdir("Number Of Events at FEB per Spill");
    TDirectory *NumEvatSpillFEBwHG = wfile.mkdir("Number Of Events at FEB with HG per Spill");
    TDirectory *PerHitsFebRunWithHG = wfile.mkdir("Percent Of Events at FEB with HG per Spill");
    TDirectory *NumHitsPerCh = wfile.mkdir("Number Of hits per channel at FEB");
    TDirectory *NumHitsPerChWithHG = wfile.mkdir("Number Of hits per channel with HG at FEB");
    TDirectory *NumHitsPerFEB = wfile.mkdir("Number Of hits per FEB");
    TDirectory *NumHitsPerFEBWithHG = wfile.mkdir("Number Of hits with HG per FEB");
    TDirectory *HitTfSpillStart = wfile.mkdir("Hit Time from Spill Start");
    TDirectory *HitTfSpillStartHG = wfile.mkdir("Hit Time from Spill Start with HG");

  	TH1F *NumberOfSpills = new TH1F("Number of Spills per FEB","Number of Spills per FEB",NumberOfFEB+1,0,NumberOfFEB);
  	for (int ih=0; ih<FEBnumbers.size();ih++){
  		NumberOfSpills->Fill(FEBnumbers.at(ih),nentries.at(ih));
  	}

    SummaryPlots->cd();
  	NumberOfSpills->GetYaxis()->SetTitle("Number of Spills");
    NumberOfSpills->GetXaxis()->SetTitle("FEB");
    NumberOfSpills->SetOption("hist");  // Change the default drawing option for "h"
  	NumberOfSpills->Write();
    NumberOfSpills->Delete();

    TCanvas *c = new TCanvas("Channels Check summary","Channels Check summary",1500,1000);
    //c->Divide(2,2);
    TH1I *ChannelsCheck[FEBnumbers.size()];
    TH1I *SpillTimeGTrigFEB[FEBnumbers.size()];
    TH1I *AverageNumHitsFebRun[FEBnumbers.size()];
    TH1I *AverageNumHitsFebRunWithHG[FEBnumbers.size()];
    TH1D *PercentHitsFebRunWithHG[FEBnumbers.size()];
    TH1I *NumberOfHitsPerCh[FEBnumbers.size()];
    TH1I *NumberOfHitsPerChWithHG[FEBnumbers.size()];
    TH1I *NumOfHitsPerFEB[FEBnumbers.size()];
    TH1I *NumOfHitsPerFEBWithHG[FEBnumbers.size()];
    TH1I *HitTimefromSpillStart[FEBnumbers.size()];
    TH1I *HitTimefromSpillStartHG[FEBnumbers.size()];

    TH1I *TotallNumberOfEvents = new TH1I( "Totall number of events per FEB", "Totall number of events per FEB",NumberOfFEB,0,NumberOfFEB);
    TotallNumberOfEvents->GetYaxis()->SetTitle("Number of events");
    TotallNumberOfEvents->GetXaxis()->SetTitle("FEB");
    TotallNumberOfEvents->SetOption("hist");

    TH1F *AverageNumberOfEventsFEB = new TH1F( "Average number of events at FEB per Spill", "Average number of events per FEB at spill",NumberOfFEB,0,NumberOfFEB);
    AverageNumberOfEventsFEB->GetYaxis()->SetTitle("Number of events");
    AverageNumberOfEventsFEB->GetXaxis()->SetTitle("FEB");
    AverageNumberOfEventsFEB->SetOption("hist");

    TH1F *AverageNumberOfEventsFEBWithHG = new TH1F( "Average number of events with HG at FEB per Spill", "Average number of events with HG per FEB at spill",NumberOfFEB,0,NumberOfFEB);
    AverageNumberOfEventsFEBWithHG->GetYaxis()->SetTitle("Number of events");
    AverageNumberOfEventsFEBWithHG->GetXaxis()->SetTitle("FEB");
    AverageNumberOfEventsFEBWithHG->SetOption("hist");
    
    TH1F *NumMissedSpills = new TH1F("Number of missed Spills","Number of missed Spills (Filled by -1)",NumberOfFEB,0,NumberOfFEB);
    NumMissedSpills->GetYaxis()->SetTitle("Number of Spills");
    NumMissedSpills->GetXaxis()->SetTitle("FEB");
    NumMissedSpills->SetOption("hist");

    TH1F *AverageNumberOfEventsRun = new TH1F( "Number of events at FEB during run", "Number of events per FEB during run",NumberOfFEB,0,NumberOfFEB);
    AverageNumberOfEventsRun->GetYaxis()->SetTitle("Average number of hits at FEB");
    AverageNumberOfEventsRun->GetXaxis()->SetTitle("FEB");
    AverageNumberOfEventsRun->SetOption("hist");

    TH1F *AverageNumberOfEventsRunWithHG = new TH1F( "Number of events with HG at FEB during run", "Number of events with HG per FEB during run",NumberOfFEB,0,NumberOfFEB);
    AverageNumberOfEventsRunWithHG->GetYaxis()->SetTitle("Average number of hits at FEB");
    AverageNumberOfEventsRunWithHG->GetXaxis()->SetTitle("FEB");
    AverageNumberOfEventsRunWithHG->SetOption("hist");

    TH1F *PercentOfEventsRunWithHG = new TH1F( "Percent of events with HG at FEB", "Percent of events with HG per FEB",NumberOfFEB,0,NumberOfFEB);
    PercentOfEventsRunWithHG->GetYaxis()->SetTitle("%");
    PercentOfEventsRunWithHG->GetXaxis()->SetTitle("FEB");
    PercentOfEventsRunWithHG->SetOption("hist");

    TH2F *HitTimefromSpillStartFEBs = new TH2F("Hit's Time from Spill Start", "Hit's Time from Spill Start",NumberOfFEB,0,NumberOfFEB,4000,0,80100);
    HitTimefromSpillStartFEBs->GetYaxis()->SetTitle("Time from spill start, [2.5 ns]");
    HitTimefromSpillStartFEBs->GetXaxis()->SetTitle("FEB");
    HitTimefromSpillStartFEBs->SetOption("colz");

    TH2F *HitTimefromSpillStartHGFEBs = new TH2F("Hit's Time from Spill Start With HG", "Hit's Time from Spill Start With HG",NumberOfFEB,0,NumberOfFEB,4000,0,80100);
    HitTimefromSpillStartHGFEBs->GetYaxis()->SetTitle("Time from spill start, [2.5 ns]");
    HitTimefromSpillStartHGFEBs->GetXaxis()->SetTitle("FEB");
    HitTimefromSpillStartHGFEBs->SetOption("colz");

    std::vector<double> SpillTimeGTrigCheck[NumberOfFEB];
    std::vector<double> SpillTimeGTrigReal;
    std::vector<double> SpillNumCheck[NumberOfFEB];
    std::vector<double> NumberOfEventsCh[NumberOfFEB][96];
    std::vector<double> NumberOfEventsChWithHG[NumberOfFEB][96];
    std::vector<double> AvNumHitsFebRun;
    std::vector<double> AvNumEventsRun;
    std::vector<double> AvNumEventsRunWithHG;
    ostringstream oSummaryText;
    std::vector<string> SummaryTextNoisy;
    std::vector<string> SummaryTextDead;
    std::vector<string> SummaryTextLessNoisy;

    for (Int_t iFEB=0; iFEB < FEBnumbers.size();iFEB++){
        sFEBnum.str("");            
        sFEBnum << FEBnumbers.at(iFEB);
        sFEB =  sFEBnum.str();
        ChannelsCheck[FEBnumbers.at(iFEB)]=new TH1I(("FEB_" + sFEB + " number of events per ch").c_str(),("FEB_" + sFEB + " number of events per ch").c_str(),96,0,95);
        SpillTimeGTrigFEB[FEBnumbers.at(iFEB)] = new TH1I(("FEB_" + sFEB +" Synchronization Check").c_str(),("FEB_" + sFEB+" Synchronization Check").c_str(),10000,-1,1000);
        AverageNumHitsFebRun[FEBnumbers.at(iFEB)] = new TH1I(("FEB_" + sFEB +" Number of hits per FEB per Spill").c_str(), ("FEB_" + sFEB +" Number Of Events at FEB per Spill at run").c_str(),1000, 0, 1000);
        AverageNumHitsFebRunWithHG[FEBnumbers.at(iFEB)] = new TH1I(("FEB_" + sFEB +" Number of hits with HG per FEB per Spill").c_str(), ("FEB_" + sFEB +" Number Of Events with HG at FEB per Spill at run").c_str(),1000, 0, 1000);
        PercentHitsFebRunWithHG[FEBnumbers.at(iFEB)] = new TH1D(("FEB_" + sFEB +" Percent of hits with HG per FEB per Spill").c_str(), ("FEB_" + sFEB +" Percent Of Events with HG at FEB per Spill at run").c_str(),30, 0, 100);
        NumberOfHitsPerCh[FEBnumbers.at(iFEB)] = new TH1I(("FEB_" + sFEB +" Number of hits at Channel per Spill").c_str(), ("FEB_" + sFEB +" Number of hits at Channel per Spill").c_str(), 100, 0,100);
        NumberOfHitsPerChWithHG[FEBnumbers.at(iFEB)] = new TH1I(("FEB_" + sFEB +" Number of hits at Channel per Spill with HG").c_str(), ("FEB_" + sFEB +" Number of hits at Channel per Spill with HG").c_str(), 100, 0,100);
        NumOfHitsPerFEB[FEBnumbers.at(iFEB)] = new TH1I(("FEB_" + sFEB +"Totall number of hits at Channel").c_str(),
            ("FEB_" + sFEB +"Totall number of hits at Channel").c_str(),1001,0,100000);
        NumOfHitsPerFEBWithHG[FEBnumbers.at(iFEB)] = new TH1I(("FEB_" + sFEB +"Totall number of hits with HG at Channel").c_str(),
            ("FEB_" + sFEB +"Totall number of hits with HG at Channel").c_str(),1001,0,100000);
        HitTimefromSpillStart[FEBnumbers.at(iFEB)] = new TH1I(("FEB_" + sFEB +"Hit's Time from Spill Start").c_str(), ("FEB_" + sFEB +"Hit's Time from Spill Start").c_str(), 80100,0,80100);
        HitTimefromSpillStartHG[FEBnumbers.at(iFEB)] = new TH1I( ("FEB_" + sFEB +"Hit's Time from Spill Start with HG").c_str(), ("FEB_" + sFEB +"Hit's Time from Spill Start with HG").c_str(), 80100,0,80100);

    	//cout<<"FEB "<<FEBnumbers.at(iFEB)<<" is in process."<<endl;
    	SpillTimeGTrigCheck[FEBnumbers.at(iFEB)].clear();
        SpillTimeGTrigReal.clear();
    	SpillNumCheck[FEBnumbers.at(iFEB)].clear();

        AvNumEventsRun.push_back(0);
        AvNumEventsRunWithHG.push_back(0);

    	for (int in =0; in < nentries.at(iFEB); in++){
    		FEBtree[FEBnumbers.at(iFEB)]->GetEntry(in);
            //cout<<in<< " " <<FEB[FEBnumbers.at(iFEB)].SpillNum->back()<<endl;
            
            for (int ch=0;ch<96;ch++){
                NumberOfEventsCh[FEBnumbers.at(iFEB)][ch].push_back(0);
                NumberOfEventsChWithHG[FEBnumbers.at(iFEB)][ch].push_back(0);
            }

    		SpillTimeGTrigCheck[FEBnumbers.at(iFEB)].push_back(FEB[FEBnumbers.at(iFEB)].SpillTimeGTrig->front());
            SpillNumCheck[FEBnumbers.at(iFEB)].push_back(FEB[FEBnumbers.at(iFEB)].SpillNum->back());
            SpillTimeGTrigFEB[FEBnumbers.at(iFEB)]->Fill(FEB[FEBnumbers.at(iFEB)].SpillTimeGTrig->front());

            if (FEB[FEBnumbers.at(iFEB)].hitsChannel->back()!=-1) {
                TotallNumberOfEvents->Fill(FEBnumbers.at(iFEB),FEB[FEBnumbers.at(iFEB)].hitsChannel->size());
                AverageNumHitsFebRun[FEBnumbers.at(iFEB)]->Fill(FEB[FEBnumbers.at(iFEB)].hitsChannel->size(),1);
                AvNumEventsRun.at(iFEB)+=FEB[FEBnumbers.at(iFEB)].hitsChannel->size();
            } else {
                AverageNumHitsFebRun[FEBnumbers.at(iFEB)]->Fill(0.,1);
            }

            int NumberAmplHG = 0;

    		for (int i=0;i<FEB[FEBnumbers.at(iFEB)].hitsChannel->size(); i++){
                if (FEB[FEBnumbers.at(iFEB)].hitsChannel->at(i)!=-1) {
                    NumberOfEventsCh[FEBnumbers.at(iFEB)][(int)FEB[FEBnumbers.at(iFEB)].hitsChannel->at(i)].back()++;
                    HitTimefromSpillStart[FEBnumbers.at(iFEB)]->Fill(FEB[FEBnumbers.at(iFEB)].hitTimefromSpill->at(i));
                    HitTimefromSpillStartFEBs->Fill(FEBnumbers.at(iFEB),FEB[FEBnumbers.at(iFEB)].hitTimefromSpill->at(i),1);
                    if (FEB[FEBnumbers.at(iFEB)].hitAmpl->at(i) > 0) {
                        NumberOfEventsChWithHG[FEBnumbers.at(iFEB)][(int)FEB[FEBnumbers.at(iFEB)].hitsChannel->at(i)].back()++;
                        AvNumEventsRunWithHG.back()++;
                        NumberAmplHG++;
                        HitTimefromSpillStartHG[FEBnumbers.at(iFEB)]->Fill(FEB[FEBnumbers.at(iFEB)].hitTimefromSpill->at(i));
                        HitTimefromSpillStartHGFEBs->Fill(FEBnumbers.at(iFEB),FEB[FEBnumbers.at(iFEB)].hitTimefromSpill->at(i),1);
                    }
                }
    			ChannelsCheck[FEBnumbers.at(iFEB)]->Fill(FEB[FEBnumbers.at(iFEB)].hitsChannel->at(i),1);
    		}
            AverageNumHitsFebRunWithHG[FEBnumbers.at(iFEB)]->Fill(NumberAmplHG,1);

            if (FEB[FEBnumbers.at(iFEB)].hitsChannel->size()>1) 
                    PercentHitsFebRunWithHG[FEBnumbers.at(iFEB)]->Fill(((double)NumberAmplHG/FEB[FEBnumbers.at(iFEB)].hitsChannel->size())*100,1);
    	}

        for (int ch=0;ch<96;ch++){
            int AverageNumHits = 0;
            int AverageNumHitsHG =0;
            for (int i=0; i<NumberOfEventsCh[FEBnumbers.at(iFEB)][ch].size(); i++){
                NumberOfHitsPerCh[FEBnumbers.at(iFEB)]->Fill(NumberOfEventsCh[FEBnumbers.at(iFEB)][ch].at(i),1);
                AverageNumHits += NumberOfEventsCh[FEBnumbers.at(iFEB)][ch].at(i);
            }
            for (int i=0; i<NumberOfEventsChWithHG[FEBnumbers.at(iFEB)][ch].size(); i++){
                NumberOfHitsPerChWithHG[FEBnumbers.at(iFEB)]->Fill(NumberOfEventsChWithHG[FEBnumbers.at(iFEB)][ch].at(i),1);
                AverageNumHitsHG+= NumberOfEventsChWithHG[FEBnumbers.at(iFEB)][ch].at(i);
            }
            //cout<< AverageNumHits<<endl;
            NumOfHitsPerFEB[FEBnumbers.at(iFEB)]->Fill(AverageNumHits,1);
            NumOfHitsPerFEBWithHG[FEBnumbers.at(iFEB)]->Fill(AverageNumHitsHG,1);
        }
        double FirstBin = 0;
        double LastBin = 0;

        NumHitsPerFEB->cd();
        FirstBin = NumOfHitsPerFEB[FEBnumbers.at(iFEB)]->FindFirstBinAbove(0);
        LastBin = NumOfHitsPerFEB[FEBnumbers.at(iFEB)]->FindLastBinAbove(0);
        NumOfHitsPerFEB[FEBnumbers.at(iFEB)]->GetYaxis()->SetTitle("Number of entries");
        NumOfHitsPerFEB[FEBnumbers.at(iFEB)]->GetXaxis()->SetTitle("Number of events at ch");
        NumOfHitsPerFEB[FEBnumbers.at(iFEB)]->GetXaxis()->SetRange(FirstBin,LastBin);
        NumOfHitsPerFEB[FEBnumbers.at(iFEB)]->Write();
        NumOfHitsPerFEB[FEBnumbers.at(iFEB)]->Delete();

        NumHitsPerFEBWithHG->cd();
        FirstBin = NumOfHitsPerFEBWithHG[FEBnumbers.at(iFEB)]->FindFirstBinAbove(0);
        LastBin = NumOfHitsPerFEBWithHG[FEBnumbers.at(iFEB)]->FindLastBinAbove(0);
        NumOfHitsPerFEBWithHG[FEBnumbers.at(iFEB)]->GetYaxis()->SetTitle("Number of entries");
        NumOfHitsPerFEBWithHG[FEBnumbers.at(iFEB)]->GetXaxis()->SetTitle("Number of events with HG at ch");
        NumOfHitsPerFEBWithHG[FEBnumbers.at(iFEB)]->GetXaxis()->SetRange(FirstBin,LastBin);
        NumOfHitsPerFEBWithHG[FEBnumbers.at(iFEB)]->Write();
        NumOfHitsPerFEBWithHG[FEBnumbers.at(iFEB)]->Delete();


        NumHitsPerCh->cd();
        FirstBin = NumberOfHitsPerCh[FEBnumbers.at(iFEB)]->FindFirstBinAbove(0);
        LastBin = NumberOfHitsPerCh[FEBnumbers.at(iFEB)]->FindLastBinAbove(0);
        TF1 *fitNumberOfHitsPerCh = new TF1("fitNumberOfHitsPerCh","gaus",0,LastBin);
        Double_t fitParNumberOfHitsPerCh[3];
        NumberOfHitsPerCh[FEBnumbers.at(iFEB)]->Fit("fitNumberOfHitsPerCh","QMER");
        fitParNumberOfHitsPerCh[0]=0;
        fitParNumberOfHitsPerCh[1]=0;
        fitParNumberOfHitsPerCh[2]=0;
        fitNumberOfHitsPerCh->GetParameters(&fitParNumberOfHitsPerCh[0]);
        NumberOfHitsPerCh[FEBnumbers.at(iFEB)]->GetYaxis()->SetTitle("Number of entries");
        NumberOfHitsPerCh[FEBnumbers.at(iFEB)]->GetXaxis()->SetTitle("Number of events at ch");
        NumberOfHitsPerCh[FEBnumbers.at(iFEB)]->GetXaxis()->SetRange(FirstBin,LastBin);
        NumberOfHitsPerCh[FEBnumbers.at(iFEB)]->Write();
        NumberOfHitsPerCh[FEBnumbers.at(iFEB)]->Delete();

        NumHitsPerChWithHG->cd();
        FirstBin = NumberOfHitsPerChWithHG[FEBnumbers.at(iFEB)]->FindFirstBinAbove(0);
        LastBin = NumberOfHitsPerChWithHG[FEBnumbers.at(iFEB)]->FindLastBinAbove(0);
        NumberOfHitsPerChWithHG[FEBnumbers.at(iFEB)]->GetYaxis()->SetTitle("Number of entries");
        NumberOfHitsPerChWithHG[FEBnumbers.at(iFEB)]->GetXaxis()->SetTitle("Number of events with HG at ch");
        NumberOfHitsPerChWithHG[FEBnumbers.at(iFEB)]->GetXaxis()->SetRange(FirstBin,LastBin);
        NumberOfHitsPerChWithHG[FEBnumbers.at(iFEB)]->Write();
        NumberOfHitsPerChWithHG[FEBnumbers.at(iFEB)]->Delete();

    	ChCheck->cd();
    	ChannelsCheck[FEBnumbers.at(iFEB)]->GetYaxis()->SetTitle("Number of events");
    	ChannelsCheck[FEBnumbers.at(iFEB)]->GetXaxis()->SetTitle("Channel");
    	ChannelsCheck[FEBnumbers.at(iFEB)]->Write();
    	ChannelsCheck[FEBnumbers.at(iFEB)]->Delete();

        SynchCheck->cd();
        SpillTimeGTrigFEB[FEBnumbers.at(iFEB)]->GetYaxis()->SetTitle("Number of entries");
        SpillTimeGTrigFEB[FEBnumbers.at(iFEB)]->GetXaxis()->SetTitle("Spill Time from GTRIG [10ns]");
        SpillTimeGTrigFEB[FEBnumbers.at(iFEB)]->Write();
        SpillTimeGTrigFEB[FEBnumbers.at(iFEB)]->Delete();

        NumEvatSpillFEB->cd();
        FirstBin = AverageNumHitsFebRun[FEBnumbers.at(iFEB)]->FindFirstBinAbove(0);
        LastBin = AverageNumHitsFebRun[FEBnumbers.at(iFEB)]->FindLastBinAbove(0);
        TF1 *fitAverageNumHitsFebRun = new TF1("fitAverageNumHitsFebRun","gaus",FirstBin, LastBin);
        Double_t fitParAverageNumHitsFebRun[3];
        AverageNumHitsFebRun[FEBnumbers.at(iFEB)]->Fit("fitAverageNumHitsFebRun","QMER");
        fitParAverageNumHitsFebRun[0]=0;
        fitParAverageNumHitsFebRun[1]=0;
        fitParAverageNumHitsFebRun[2]=0;
        fitAverageNumHitsFebRun->GetParameters(&fitParAverageNumHitsFebRun[0]);
        AverageNumberOfEventsFEB->Fill(FEBnumbers.at(iFEB),fitParAverageNumHitsFebRun[1]);
        AverageNumHitsFebRun[FEBnumbers.at(iFEB)]->GetYaxis()->SetTitle("Number of entries");
        AverageNumHitsFebRun[FEBnumbers.at(iFEB)]->GetXaxis()->SetTitle("Number of events per Spill at FEB");
        AverageNumHitsFebRun[FEBnumbers.at(iFEB)]->GetXaxis()->SetRange(FirstBin,LastBin);
        AverageNumHitsFebRun[FEBnumbers.at(iFEB)]->Write();
        AverageNumHitsFebRun[FEBnumbers.at(iFEB)]->Delete();
        fitAverageNumHitsFebRun->Delete();

        NumEvatSpillFEBwHG->cd();
        FirstBin = AverageNumHitsFebRunWithHG[FEBnumbers.at(iFEB)]->FindFirstBinAbove(0);
        LastBin = AverageNumHitsFebRunWithHG[FEBnumbers.at(iFEB)]->FindLastBinAbove(0);
        TF1 *fitAverageNumHitsFebRunWithHG = new TF1("fitAverageNumHitsFebRunWithHG","gaus",0, LastBin);
        Double_t fitParAverageNumHitsFebRunWithHG[3];
        AverageNumHitsFebRunWithHG[FEBnumbers.at(iFEB)]->Fit("fitAverageNumHitsFebRunWithHG","QMER");
        fitParAverageNumHitsFebRunWithHG[0]=0;
        fitParAverageNumHitsFebRunWithHG[1]=0;
        fitParAverageNumHitsFebRunWithHG[2]=0;
        fitAverageNumHitsFebRunWithHG->GetParameters(&fitParAverageNumHitsFebRunWithHG[0]);
        AverageNumberOfEventsFEBWithHG->Fill(FEBnumbers.at(iFEB),fitParAverageNumHitsFebRunWithHG[1]);
        AverageNumHitsFebRunWithHG[FEBnumbers.at(iFEB)]->GetYaxis()->SetTitle("Number of entries");
        AverageNumHitsFebRunWithHG[FEBnumbers.at(iFEB)]->GetXaxis()->SetTitle("Number of events with HG per Spill at FEB");
        AverageNumHitsFebRunWithHG[FEBnumbers.at(iFEB)]->GetXaxis()->SetRange(FirstBin,LastBin);
        AverageNumHitsFebRunWithHG[FEBnumbers.at(iFEB)]->Write();
        AverageNumHitsFebRunWithHG[FEBnumbers.at(iFEB)]->Delete();
        fitAverageNumHitsFebRunWithHG->Delete();

        PerHitsFebRunWithHG->cd();
        FirstBin = PercentHitsFebRunWithHG[FEBnumbers.at(iFEB)]->FindFirstBinAbove(0);
        LastBin = PercentHitsFebRunWithHG[FEBnumbers.at(iFEB)]->FindLastBinAbove(0);
        TF1 *fitPercentHitsFebRunWithHG = new TF1("fitPercentHitsFebRunWithHG","gaus",0, 80);
        Double_t fitParPercentHitsFebRunWithHG[3];
        PercentHitsFebRunWithHG[FEBnumbers.at(iFEB)]->Fit("fitPercentHitsFebRunWithHG","QMER");
        fitParPercentHitsFebRunWithHG[0]=0;
        fitParPercentHitsFebRunWithHG[1]=0;
        fitParPercentHitsFebRunWithHG[2]=0;
        fitPercentHitsFebRunWithHG->GetParameters(&fitParPercentHitsFebRunWithHG[0]);
        if (fitParPercentHitsFebRunWithHG[1]>0 && fitParPercentHitsFebRunWithHG[1]<100)
            PercentOfEventsRunWithHG->Fill(FEBnumbers.at(iFEB),fitParPercentHitsFebRunWithHG[1]);
        else
            PercentOfEventsRunWithHG->Fill(FEBnumbers.at(iFEB), PercentHitsFebRunWithHG[FEBnumbers.at(iFEB)]->GetMean());
        PercentHitsFebRunWithHG[FEBnumbers.at(iFEB)]->GetYaxis()->SetTitle("Number of entries");
        PercentHitsFebRunWithHG[FEBnumbers.at(iFEB)]->GetXaxis()->SetTitle("Percent of events with HG per Spill at FEB");
        PercentHitsFebRunWithHG[FEBnumbers.at(iFEB)]->GetXaxis()->SetRange(FirstBin,LastBin);
        PercentHitsFebRunWithHG[FEBnumbers.at(iFEB)]->Write();
        PercentHitsFebRunWithHG[FEBnumbers.at(iFEB)]->Delete();
        fitPercentHitsFebRunWithHG->Delete();

        HitTfSpillStart->cd();
        HitTimefromSpillStart[FEBnumbers.at(iFEB)]->GetYaxis()->SetTitle("Number of entries");
        HitTimefromSpillStart[FEBnumbers.at(iFEB)]->GetXaxis()->SetTitle("Hit Time from Spill Start [2.5 ns]");
        HitTimefromSpillStart[FEBnumbers.at(iFEB)]->Write();
        HitTimefromSpillStart[FEBnumbers.at(iFEB)]->Delete();

        HitTfSpillStartHG->cd();
        HitTimefromSpillStartHG[FEBnumbers.at(iFEB)]->GetYaxis()->SetTitle("Number of entries");
        HitTimefromSpillStartHG[FEBnumbers.at(iFEB)]->GetXaxis()->SetTitle("Hit Time from Spill Start [2.5 ns]");
        HitTimefromSpillStartHG[FEBnumbers.at(iFEB)]->Write();
        HitTimefromSpillStartHG[FEBnumbers.at(iFEB)]->Delete();


        if (FEBnumbers.at(iFEB) == 5 || FEBnumbers.at(iFEB) == 53){
            AvNumEventsRun.at(iFEB) = AvNumEventsRun.at(iFEB)/96;
            AvNumEventsRunWithHG.at(iFEB) = AvNumEventsRunWithHG.at(iFEB)/96;
        } else if (FEBnumbers.at(iFEB) == 13 || FEBnumbers.at(iFEB) == 20 || FEBnumbers.at(iFEB) == 28 || 
            FEBnumbers.at(iFEB) == 36 || FEBnumbers.at(iFEB) == 44 || FEBnumbers.at(iFEB) == 61 ){
            AvNumEventsRun.at(iFEB) = AvNumEventsRun.at(iFEB)/64;
            AvNumEventsRunWithHG.at(iFEB) = AvNumEventsRunWithHG.at(iFEB)/64;
        } else if (FEBnumbers.at(iFEB) == 21 || FEBnumbers.at(iFEB) == 29) {
            AvNumEventsRun.at(iFEB) = AvNumEventsRun.at(iFEB)/14;
            AvNumEventsRunWithHG.at(iFEB) = AvNumEventsRunWithHG.at(iFEB)/14;
        } else {
            AvNumEventsRun.at(iFEB) = AvNumEventsRun.at(iFEB)/95;
            AvNumEventsRunWithHG.at(iFEB) = AvNumEventsRunWithHG.at(iFEB)/95;
        }

        AverageNumberOfEventsRun->Fill(FEBnumbers.at(iFEB),AvNumEventsRun.at(iFEB));
        AverageNumberOfEventsRunWithHG->Fill(FEBnumbers.at(iFEB),AvNumEventsRunWithHG.at(iFEB));

        for (int ch=0;ch<96;ch++){
            int TotallNumOfHitsCh = 0;
            for (int i=0; i< NumberOfEventsCh[FEBnumbers.at(iFEB)][ch].size();i++) {
                TotallNumOfHitsCh +=NumberOfEventsCh[FEBnumbers.at(iFEB)][ch].at(i);
            }
            if (TotallNumOfHitsCh > 4*AvNumEventsRun.at(iFEB)) {
                cout <<"Noisy channel: FEB_"<< FEBnumbers.at(iFEB)<< " channel " <<ch<< " Totall Number of events "<<TotallNumOfHitsCh<<endl;
                oSummaryText.str("");
                oSummaryText<< "FEB_"<< FEBnumbers.at(iFEB)<< " channel " <<ch;
                SummaryTextNoisy.push_back(oSummaryText.str());
            } else if ((TotallNumOfHitsCh < 0.25 * AvNumEventsRun.at(iFEB)) && (TotallNumOfHitsCh > 0.3 * AvNumEventsRun.at(iFEB)) && ChannelExist(FEBnumbers.at(iFEB),ch)){
                cout <<"Less noisy channel: FEB_"<< FEBnumbers.at(iFEB)<< " channel " <<ch<< " Totall Number of events "<<TotallNumOfHitsCh<<endl;
                oSummaryText.str("");
                oSummaryText<< "FEB_"<< FEBnumbers.at(iFEB)<< " channel " <<ch;
                SummaryTextLessNoisy.push_back(oSummaryText.str());
            } else if ((TotallNumOfHitsCh < 0.1 * AvNumEventsRun.at(iFEB)) && ChannelExist(FEBnumbers.at(iFEB),ch)) {
                cout <<"Dead channel: FEB_"<< FEBnumbers.at(iFEB)<< " channel " <<ch<< " Totall Number of events "<<TotallNumOfHitsCh<<endl;
                oSummaryText.str("");
                oSummaryText<< "FEB_"<< FEBnumbers.at(iFEB)<< " channel " <<ch;
                SummaryTextDead.push_back(oSummaryText.str());
            }
        }
    }
    

    SpillTimeGTrigReal = GetRealGTrig(NumberOfFEB, SpillTimeGTrigCheck);

    for (int ih=0;ih<SpillTimeGTrigCheck[0].size();ih++){
    	for (Int_t iFEB=0; iFEB < FEBnumbers.size();iFEB++){ 
    		if (SpillNumCheck[0].at(ih)!=SpillNumCheck[FEBnumbers.at(iFEB)].at(ih)){
                cout<< "Spill Number ERROR : FEB_0 Spill Number ";
    			cout<<SpillNumCheck[0].at(ih)<<"!= FEB_"<<FEBnumbers.at(iFEB)<<" Spill Number "<<SpillNumCheck[FEBnumbers.at(iFEB)].at(ih)<<endl;
    		}
    		if ((SpillTimeGTrigCheck[FEBnumbers.at(iFEB)].at(ih)!=SpillTimeGTrigReal.at(ih)) || (SpillTimeGTrigReal.at(ih)==-1)){
                if (SpillTimeGTrigCheck[FEBnumbers.at(iFEB)].at(ih)!=-1){
                    cout<<"Synchronization ERROR :"<<FEBnumbers.at(iFEB)<<" "<<SpillNumCheck[FEBnumbers.at(iFEB)].at(ih)<<" "
                    <<SpillTimeGTrigCheck[FEBnumbers.at(iFEB)].at(ih)<<"!="<<SpillTimeGTrigCheck[0].at(ih)<<endl;
                } else {
                    NumMissedSpills->Fill(FEBnumbers.at(iFEB),1);
                }
    		}
    	}
    }


    SummaryPlots->cd();

    TPaveText *ptS = new TPaveText(.01,0.8,0.99,0.99);
    ptS->AddText("Channels check summary:");
    ptS->AddText("Total Number of channels - 4024");

    //c->cd(1);
    TPaveText *ptN = new TPaveText(.01,.01,.5,.8);
    ptN->AddText("Noisy Channels:");
    if (SummaryTextNoisy.size()){
        for (int i=0; i<SummaryTextNoisy.size();i++){
            ptN->AddText((SummaryTextNoisy.at(i)).c_str());
        }
    } else {
        ptN->AddText("0");
    }

    TPaveText *ptLN = new TPaveText(.5,.4,0.99,.8);
    ptLN->AddText("Less Noisy Channels:");
    if (SummaryTextLessNoisy.size()){
        for (int i=0; i<SummaryTextLessNoisy.size();i++){
            ptLN->AddText((SummaryTextLessNoisy.at(i)).c_str());
        }
    } else {
         ptLN->AddText("0");
    }

    //c->cd(2);
    TPaveText *ptD = new TPaveText(.5,.01,0.99,.4);
    ptD->AddText("Dead Channels:");
    if (SummaryTextDead.size()){
        for (int i=0; i<SummaryTextDead.size();i++){
            ptD->AddText((SummaryTextDead.at(i)).c_str());
        }
    } else {
         ptD->AddText("0");
    }
    //pt->AddLine(.0,.5,1.,.5);
    ptS->Draw();
    ptN->Draw();
    ptLN->Draw();
    ptD->Draw();
    c->Write();
    ptS->Delete();
    ptN->Delete();
    ptLN->Delete();
    ptD->Delete();

    c->Delete();

    NumMissedSpills->Write();
    NumMissedSpills->Delete();
    TotallNumberOfEvents->Write();
    TotallNumberOfEvents->Delete();
    AverageNumberOfEventsFEB->Write();
    AverageNumberOfEventsFEB->Delete();
    AverageNumberOfEventsFEBWithHG->Write();
    AverageNumberOfEventsFEBWithHG->Delete();
    AverageNumberOfEventsRun->Write();
    AverageNumberOfEventsRun->Delete();
    AverageNumberOfEventsRunWithHG->Write();
    AverageNumberOfEventsRunWithHG->Delete();
    PercentOfEventsRunWithHG->Write();
    PercentOfEventsRunWithHG->Delete();
    HitTimefromSpillStartFEBs->Write();
    HitTimefromSpillStartFEBs->Delete();
    HitTimefromSpillStartHGFEBs->Write();
    HitTimefromSpillStartHGFEBs->Delete();

    SpillTimeGTrigReal.clear();
    for (int ih = 0; ih<FEBnumbers.size();ih++) {
        SpillTimeGTrigCheck[NumberOfFEB].clear();
        SpillNumCheck[NumberOfFEB].clear();
    
        FEB[FEBnumbers.at(ih)].FEBSN->clear();
        FEB[FEBnumbers.at(ih)].SpillNum->clear();
        FEB[FEBnumbers.at(ih)].SpillTime->clear();
        FEB[FEBnumbers.at(ih)].SpillTimeGTrig->clear();
        FEB[FEBnumbers.at(ih)].GTrigTag->clear();
        FEB[FEBnumbers.at(ih)].GTrigTime->clear();
        FEB[FEBnumbers.at(ih)].hitsChannel->clear();
        FEB[FEBnumbers.at(ih)].hitAmpl->clear();
        FEB[FEBnumbers.at(ih)].hitLGAmpl->clear();
        FEB[FEBnumbers.at(ih)].hitLeadTime->clear();
        FEB[FEBnumbers.at(ih)].hitTrailTime->clear();
        FEB[FEBnumbers.at(ih)].hitTimeDif->clear();
        FEB[FEBnumbers.at(ih)].hitTimefromSpill->clear();
        FEB[FEBnumbers.at(ih)].SpillTrailTime->clear();
        FEB[FEBnumbers.at(ih)].AsicTemperature->clear();
        FEB[FEBnumbers.at(ih)].FPGATemperature->clear();
        FEB[FEBnumbers.at(ih)].GlobalHV->clear();
        FEB[FEBnumbers.at(ih)].BoardTemperature->clear();
        FEB[FEBnumbers.at(ih)].BoardHumidity->clear();
    }
  	FileInput->Close();
  	wfile.Close();
  	return 0;
}

