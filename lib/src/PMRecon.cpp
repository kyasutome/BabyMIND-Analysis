#include <iostream>
#include <stdio.h>

#include "PMRecon.hpp"

using namespace std;

PMRecon::PMRecon()
{
  mod=0;
  view=0;
  pln=0;
  channel=0;
  charge=0;
  time=0;
  bunch=0;
  
  spill=-1;
  unixtime=-1;
}


PMRecon::~PMRecon()
{
}

void PMRecon::Clear()
{
  mod=0;
  view=0;
  pln=0;
  channel=0;
  charge=0;
  time=0;
  bunch=0;
  
  spill=-1;
  unixtime=-1;
}

