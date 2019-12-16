#include <iostream>
#include <stdio.h>

#include "BMDisp.hpp"

using namespace std;

BMDisp::BMDisp()
{
  mod.clear();
  view.clear();
  pln.clear();
  channel.clear();
  Htime.clear();
  timedif.clear();
  bunch.clear();

  bm_event=-1;
  entry=-1;
  spillnum=-1;
  unixtime=-1;
}


BMDisp::~BMDisp()
{
}

