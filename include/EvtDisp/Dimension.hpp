#ifndef _INC_DIMENSION
#define _INC_DIMENSION

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

#include "WGChannelMap.hpp"
//#include "WGChannelMap.cpp"

class Dimension
{

private:
  ifstream fin[10];
  int nfile;
  double correction[19];
  char file[300] = "./data/wagasci_mapping_table_2020_0130.txt";
  const unsigned NDIFS      = 8;
  unsigned NCHIPS     = 20;
  const unsigned NCHANNELS  = 32;

public:
  double sciposx[16];
  double sciposy[95];
  double sciposz[19];
  double ironposz[33];
  double yasuposx[2][14];
  double yasuposy[2][14];
  double yasuposz[2][14];

  double uwgposy_grid[20], uwgposx_grid[20];
  double dwgposy_grid[20], dwgposx_grid[20];
  double uwgposy_pln[40], uwgposx_pln[40];
  double dwgposy_pln[40], dwgposx_pln[40];
  double uwgpossz[24], dwgpossz[24];
  double uwgpostz[24], dwgpostz[24];

  map_cell **mapping[8];

private:
public:
  bool get_pos_bm_FC(int mod, int view, int pln, double ch, double *posx, double *posy, double *posz);
  bool get_pos_pm_FC(int mod, int view, int pln, double ch, double *posx, double *posy, double *posz);
  bool get_pos_wm_FC(int dif, int chip, int chan, double *posx, double *posy, double *posz);
  bool get_pos_wg_FC(int dif, int chip, int chan, double *posx, double *posy, double *posz);
  bool get_wgdet_pos(int ud, int view, int zid, int xyid, double *posxy, double *posz);

  Dimension();
  ~Dimension();
  
};

#endif
