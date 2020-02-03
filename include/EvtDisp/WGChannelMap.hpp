#ifndef _INC_WGCHANNELMAP
#define _INC_WGCHANNELMAP

#include <iostream>
#include <vector>
#include <time.h>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TChain.h>

#include "BMConst.hpp"

struct map_cell {
  int plane;
  int channel;
  float x;
  float y;
  float z;
} mapcell;

struct map_cell **load_mapping(char *filename,int nb_chips,int nb_chans,int dif);
void free_mapping(struct map_cell **mapping,int nb_chips);

#endif
