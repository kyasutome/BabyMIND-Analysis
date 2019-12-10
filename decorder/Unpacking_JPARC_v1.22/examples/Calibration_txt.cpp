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
#include "TH3.h"
#include "TF1.h"
#include "TCanvas.h"
#include <iterator>
#include <algorithm>
#include "TImage.h"
#include "TStyle.h"



using namespace std;


string GetLocation(string str)
{
     
    int i = str.rfind("_Slot_");
    string way = str.substr(0,i);  
    return way;
}



int main ()
{
    
    int NumberOfEB = 64;
    int FEBs[44] = {0,1,2,3,4,5,8,9,10,11,12,13,16,17,18,19,20,24,25,26,27,32,33,34,35,36,37,40,41,42,43,44,48,49,50,51,52,53,56,57,58,59,60,61};
    
    string rootFileOutput;
    rootFileOutput="../root_Calibration_txt.root";
    ostringstream sFEBnum;
    ostringstream sMCRnum;
    ostringstream sSlotnum;
    string sFEB;
    
    int Slot;
    int MCR;
    
    
    TH1F *TypeI = new TH1F("TypeI","TypeI",400,0,80);
    TH1F *TypeII = new TH1F("TypeII","TypeII",400,0,280);
    
    Double_t ChannelGain[28][3][96];
    for (int iFEB = 0; iFEB<44; iFEB++) {
        Slot = FEBs[iFEB] % 8;
        MCR = FEBs[iFEB] / 8;
        //cout << MCR<< " "<<Slot<<endl;
        sFEBnum.str("");
        sMCRnum.str("");
        sSlotnum.str("");
        sFEBnum << FEBs[iFEB];
        sMCRnum << MCR;
        sSlotnum << Slot;
        sFEB = "PE_HG_calib/MCR_"+ sMCRnum.str() + "_Slot_" + sSlotnum.str() + "_gain.txt";
        ofstream gain(sFEB.c_str());
        int temp=0;
        cout << "Taking fit parrameters at "<< sFEB <<endl;
        while (temp<96) {
            gain << temp << " " << 47.79 << " " << 37.0438 <<" "<< 47.79<<endl;
            //cout<<temp<<" "<<" "<<ChannelGain[FEBs[iFEB]][1][temp]<< " " << ChannelGain[FEBs[iFEB]][2][temp]<<endl;
            temp++;
        }
        gain.close(); 
            
  }
  
  TFile wfile(rootFileOutput.c_str(), "recreate");
  cout<<rootFileOutput<<endl;
  ostringstream sEventnum;
  string sEvent;
  Int_t globalCh=0;
  
  TF1 *f = new TF1("f","gaus",45,50);
  Double_t fitPar[3];
  
  TH1F *event_LY[18][96];
  for (Int_t ik = 0; ik < 18; ik++){
    for (Int_t ih=0; ih < 96;ih++){
        sEventnum.str("");
        globalCh = 96*FEBs[ik] + ih;
        sEventnum << globalCh;
        sEvent = "ChannelLY"+sEventnum.str();
        event_LY[ik][ih] = new TH1F(sEvent.c_str(),sEvent.c_str(), 200,0,200);
    }
  }

  TCanvas *c1 = new TCanvas("c1","c1", 1480, 1160);
 

    
    wfile.cd();
     TypeI  ->Fit("f","MER");
    
    
    TypeI->GetYaxis()->SetTitle("");
    TypeI->GetXaxis()->SetTitle("Gain [ADC]");
    
   
                
   
    TypeI-> Write();
   TypeII-> Write();
     wfile.Close();
     return 0;
}
