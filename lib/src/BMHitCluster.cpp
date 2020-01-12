#include <iostream>
#include <stdio.h>

#include "BMHitCluster.hpp"

using namespace std;

BMHitCluster::BMHitCluster()
{
  mod=-1;
  view=-1;
  pln=-1;
  channel=-1;
  HG=-1;
  timedif=-1;
  Htime=-1;
}

BMHitCluster::~BMHitCluster()
{
}

void BMHitCluster::Clear()
{
  mod=-1;
  view=-1;
  pln=-1;
  channel=-1;
  HG=-1;
  timedif=-1;
  Htime=-1;
}
