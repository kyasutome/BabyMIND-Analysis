#include <iostream>
#include <stdio.h>

#include "DetHitClusters.cpp"
#include "Cell.hpp"

using namespace std;

Cell::Cell()
{
  for(int i=0; i<2; i++)
    dethitclusters[i] = new DetHitClusters();
  //dethitcluster[i].Clear();
  //dethitcluster1->Clear();
  //dethitcluster2->Clear();

  state=0;
  idcard=-1;
  upneibor.clear();
  downneibor.clear();
  meanposz=-1.;
  meanposxy=-1.;

}

Cell::~Cell()
{
}

void Cell::Clear()
{
  for(int i=0; i<2; i++)
    dethitclusters[i]->Clear();
  //dethitcluster[i].Clear();
  //dethitcluster1->Clear();
  //dethitcluster2->Clear();
  
  state=0;
  idcard=-1;
  upneibor.clear();
  downneibor.clear();
  meanposz=-1.;
  meanposxy=-1.;
}
