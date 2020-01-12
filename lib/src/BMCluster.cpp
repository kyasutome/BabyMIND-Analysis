#include <iostream>
#include <stdio.h>

#include "BMCluster.hpp"

using namespace std;

BMCluster::BMCluster()
{
  mod.clear();
  view.clear();
  pln.clear();
  channel.clear();
  HG.clear();
  timedif.clear();
  Htime.clear();
  bunch.clear();
}

BMCluster::~BMCluster()
{
}

void BMCluster::Clear()
{
  mod.clear();
  view.clear();
  pln.clear();
  channel.clear();
  HG.clear();
  timedif.clear();
  Htime.clear();
  bunch.clear();
}
