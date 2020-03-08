#include <iostream>
#include <stdio.h>

#include "MCRecon.hpp"

using namespace std;

MCRecon::MCRecon()
{
  mod.clear();
  view.clear();
  pln.clear();
  channel.clear();
  charge.clear();
  dposx.clear();
  dposy.clear();
  dposz.clear();
  posx.clear();
  posy.clear();
  posz.clear();

}


MCRecon::~MCRecon()
{
}

void MCRecon::Clear()
{

  mod.clear();
  view.clear();
  pln.clear();
  channel.clear();
  charge.clear();
  dposx.clear();
  dposy.clear();
  dposz.clear();
  posx.clear();
  posy.clear();
  posz.clear();

}

