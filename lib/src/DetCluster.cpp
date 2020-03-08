#include <iostream>
#include <stdio.h>

#include "DetHitCluster.cpp"
#include "DetCluster.hpp"

using namespace std;

DetCluster::DetCluster()
{
  
  cluster.clear();

}

DetCluster::~DetCluster()
{
}

void DetCluster::Clear()
{
  cluster.clear();

}
