#ifndef _INC_MCTRUE
#define _INC_MCTRUE

#include <iostream>
#include <vector>

#include "BMConst.hpp"

class MCTrue
{
  
private:

public:

  double pdg[20];
  double ipos[4][20];
  double fpos[4][20];
  double momentum[4][20];

  int inttype;
  int nutype;
  int npar;
  
  double totcrsne;
  double norm;
  double nuE;
  double xnu;
  double ynu;
  double znu;
  double Pnu[3];  


  MCTrue();
  ~MCTrue(); 

  void Clear();

};

#endif
