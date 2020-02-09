#ifndef _INC_BASCIRECON
#define _INC_BASCIRECON

#include <iostream>
#include <vector>

#include "BMConst.hpp"

class BasicRecon
{
  
private:

public:

  double angle[2];
  double ipos[2][3];
  double fpos[2][3];
  


  BasicRecon();
  ~BasicRecon(); 

  void Clear();

};

#endif
