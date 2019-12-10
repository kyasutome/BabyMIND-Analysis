#include <iostream>
#include <stdio.h>

#include "DataReader.cpp"
#include "BMData.cpp"

using namespace std;

int main( int argc, char **argv )
{

  if(argc < 2)
    {
      cout << "usage" << '\n';
      cout << "MakeCalib [filepath]" << '\n';
      exit(0);
    }

  std::string name = string(argv[1]);
  TString filepath(name);

  DataReader *dreader = new DataReader();
  BMdata* bmbranch[NUMBEROFFEB];
  
  for(int i=0; i<NUMBEROFFEB; i++)
    {
      bmbranch[i] = new BMdata();
    }

  //test
  dreader->ReadTree(filepath, bmbranch);  
  
  //for(int ientry=0; ientry<dreader->Nentry[0]; ientry++)
  for(int ientry=0; ientry<10; ientry++)
    {
      dreader->FEBtree[0]->GetEntry(ientry);
    }

  
}
