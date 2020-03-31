#include <iostream>
#include <stdio.h>

#include "DetHitCluster.hpp"

using namespace std;

DetHitCluster::DetHitCluster()
{
  mod=-1;
  view=-1;
  pln=-1;
  channel=-1;
  posx=-1.;
  posy=-1.;
  posz=-1.;
  dposx=-1.;
  dposy=-1.;
  dposz=-1.;
  HG=-1;
  per=-1.;
  pel=-1.;
  pet=-1.;
  Htime=-1;
  hitid=-1;
}

DetHitCluster::~DetHitCluster()
{
}

void DetHitCluster::Clear()
{
  mod=-1;
  view=-1;
  pln=-1;
  channel=-1;
  posx=-1.;
  posy=-1.;
  posz=-1.;
  dposx=-1.;
  dposy=-1.;
  dposz=-1.;
  HG=-1;
  per=-1.;
  pel=-1.;
  pet=-1.;
  Htime=-1;
  hitid=-1;
}
