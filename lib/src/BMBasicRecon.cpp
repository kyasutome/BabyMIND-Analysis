#include <iostream>
#include <stdio.h>

#include "BMBasicRecon.hpp"

using namespace std;

BMBasicRecon::BMBasicRecon()
{
  mod.clear();
  view.clear();
  pln.clear();
  channel.clear();
  HG.clear();
  LHG.clear();
  RHG.clear();
  THG.clear();
  Lgain.clear();
  Rgain.clear();
  Tgain.clear();
  LG.clear();
  Ltime.clear();
  Ftime.clear();
  Htime.clear();
  timedif.clear();
  bunch.clear();

  bm_event=-1;
}


BMBasicRecon::~BMBasicRecon()
{
}

void BMBasicRecon::Clear()
{
  mod.clear();
  view.clear();
  pln.clear();
  channel.clear();
  HG.clear();
  LHG.clear();
  RHG.clear();
  THG.clear();
  Lgain.clear();
  Rgain.clear();
  Tgain.clear();
  LG.clear();
  Ltime.clear();
  Ftime.clear();
  Htime.clear();
  timedif.clear();
  bunch.clear();

  bm_event=-1;
}

void BMBasicRecon::CopyClass(BMBasicRecon* bmbasicrecon1, BMBasicRecon* bmbasicrecon2)
{
  bmbasicrecon2 = bmbasicrecon1;
}
