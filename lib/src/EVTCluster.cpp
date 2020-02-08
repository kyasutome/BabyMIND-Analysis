#include <iostream>
#include <stdio.h>

#include "EVTCluster.hpp"

using namespace std;

EVTCluster::EVTCluster()
{
  mod.clear();
  view.clear();
  pln.clear();
  channel.clear();
  charge.clear();
  Htime.clear();
  timedif.clear();
  bunch.clear();
  posx.clear();
  posy.clear();
  posz.clear();
  dposx.clear();
  dposy.clear();
  dposz.clear();

  pot=-1.;
  unixtime=-1;
  spillnum=-1;
  bm_event=-1;
  entry=-1;


}


EVTCluster::~EVTCluster()
{
}

void EVTCluster::Clear()
{
  mod.clear();
  view.clear();
  pln.clear();
  channel.clear();
  charge.clear();
  Htime.clear();
  timedif.clear();
  bunch.clear();
  posx.clear();
  posy.clear();
  posz.clear();
  dposx.clear();
  dposy.clear();
  dposz.clear();

  pot=-1.;
  unixtime=-1;
  spillnum=-1;
  bm_event=-1;
  entry=-1;


}
