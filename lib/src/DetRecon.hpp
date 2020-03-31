#ifndef _INC_DETRECON
#define _INC_DETRECON

#include <iostream>
#include <vector>

#include "BMConst.hpp"

class DetRecon
{
  
private:

public:

  double charge[6][2][9][20][1000];
  double per[6][2][9][20][1000];
  double pel[6][2][9][20][1000];
  double pet[6][2][9][20][1000];
  double hittime[6][2][9][20][1000];
  double posx[6][2][9][20][1000];
  double posy[6][2][9][20][1000];
  double posz[6][2][9][20][1000];

  double iposx[6][2][9][20];
  double iposy[6][2][9][20];
  double iposz[6][2][9][20];
  double fposx[6][2][9][20];
  double fposy[6][2][9][20];
  double fposz[6][2][9][20];

  int bunch[6][2][9][20];
  int Nhit[6][2][9][20];
  int trackid[6][2][9][20];
  int fvflag[6][2][9][20];
  int fcflag[6][2][9][20];

  int Ntrack[6][2][9];
  int entry;

  double nuvertex[6][2][3];
    
  DetRecon();
  ~DetRecon(); 

  void Clear();

};

#endif
