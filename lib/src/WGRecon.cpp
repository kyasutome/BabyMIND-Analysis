#include <iostream>
#include <stdio.h>

#include "WGRecon.hpp"

using namespace std;

WGRecon::WGRecon()
{
  /*
  mod=0;
  view=0;
  pln=0;
  channel=0;
  time=0;
  bunch=0;
  */

  mod.clear();
  view.clear();
  pln.clear();
  channel.clear();
  time.clear();
  bunch.clear();
  
  spill=-1;
  unixtime=-1;
}


WGRecon::~WGRecon()
{
}

void WGRecon::Clear()
{
  /*
  mod=0;
  view=0;
  pln=0;
  channel=0;
  time=0;
  bunch=0;
  */

  mod.clear();
  view.clear();
  pln.clear();
  channel.clear();
  time.clear();
  bunch.clear();
  
  spill=-1;
  unixtime=-1;
}

