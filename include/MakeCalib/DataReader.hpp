#ifndef _INC_DATAREADER
#define _INC_DATAREADER

#include <iostream>
#include <vector>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>

#include "BMConst.hpp"
#include "BMData.hpp"

class DataReader
{
  //parameter
private:
  TFile* Fileinput;
  TString treename;
  FileStat_t info;
  vector<double> intersection[NUMBEROFFEB];

public:
  Int_t Nentry[NUMBEROFFEB];
  TTree* FEBtree[NUMBEROFFEB];  
  Int_t MapCon[5][19];
  Double_t geomHor[5][95];
  Double_t geomVer[5][32];
  Double_t ModPos[4][19];
  vector<double> febspill[NUMBEROFFEB];
  
  //function
public:
  DataReader();
  ~DataReader();

  void ReadTree(TString filename, BMdata* BMbranch[NUMBEROFFEB]);
  void BMSpillMatch(vector<double> *commonspill);
  static void DuplicateCut(vector<double> *vec);


};

#endif
