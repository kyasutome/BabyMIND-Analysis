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
     
    int i = str.rfind("_Spill_");
    string way = str.substr(0,i);  
    return way;
}

int main ()
{
    int NumberOfMod = 18;
    int firstModule = 0;
    int temp=firstModule;
    
    vector<string> vFileNames;
    string sFileName;
    ifstream fList("reconstruction_files_list.list");
    while (!fList.eof()) {
        fList >> sFileName;
        vFileNames.push_back(sFileName);
    }
    vFileNames.pop_back();
    string rootFileOutput=GetLocation(vFileNames[0].c_str());
    rootFileOutput+="_reconstructed.root";
    cout << rootFileOutput <<endl;
    TFile wfile(rootFileOutput.c_str(), "recreate");
    
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
  
    for (int i = 0; i< vFileNames.size();i++){
      cout << vFileNames.at(i)<<endl;
      TFile *FileInput = new TFile(vFileNames.at(i).c_str());
      FileInput->cd("eventsDispHor");
      
      //TH2F * Event_1Spill_101 = new TH2F("Event_1Spill_101","Event_1Spill_101" ,198, -2200, 5720, 95, -986.2, 986.2);
      TH2F *h = (TH2F*)FileInput->Get("Event_1Spill_101");
      //FileInput->ls();
      //for (Int_t i; i< 50;i++){
          //int N_points = h->GetN();
      //}
      if(h->GetEntries()>5)
      { h->Draw();
      h->Write();}
      FileInput->Close();
    }
    wfile.Write();
    fList.close();
}
