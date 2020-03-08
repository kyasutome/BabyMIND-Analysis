#include <iostream>
#include <stdio.h>

#include "DetClusters.hpp"

using namespace std;

DetClusters::DetClusters()
{
  
  cluster.clear();

}

DetClusters::~DetClusters()
{
}

void DetClusters::Clear()
{
  cluster.clear();

}
