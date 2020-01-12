#ifndef _INC_DIMENSION
#define _INC_DIMENSION

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

class Dimension
{

private:
  ifstream fin[10];
  int nfile;
  double correction[19];

public:
  double sciposx[16];
  double sciposy[95];
  double sciposz[19];
  double ironposz[33];
  double yasuposx[2][14];
  double yasuposy[2][14];
  double yasuposz[2][14];

private:
public:
  bool get_pos_bm_FC(int mod, int view, int pln, double ch, double *posx, double *posy, double *posz);
  bool get_pos_pm_FC(int mod, int view, int pln, double ch, double *posx, double *posy, double *posz);

  Dimension();
  ~Dimension();
  
  
};

#endif
