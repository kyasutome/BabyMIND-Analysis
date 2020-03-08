#include <iostream>
#include <stdio.h>

#include "DetHitCluster.cpp"
#include "DetHitClusters.hpp"

using namespace std;

DetHitClusters::DetHitClusters()
{
  
  cluster.clear();
  posz=-1.;
  posxy=-1.;

}

DetHitClusters::~DetHitClusters()
{
}

void DetHitClusters::Clear()
{

  cluster.clear();
  posz=-1.;
  posxy=-1.;

}
