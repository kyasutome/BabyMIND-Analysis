#ifndef _INC_BMBASICRECON
#define _INC_BMBASICRECON

#include <iostream>
#include <vector>

#include "BMConst.hpp"

class BMBasicRecon
{
  
private:

public:
  
  //Baby MIND DATA STRUCTURE
  vector<double> mod;
  vector<double> view;
  vector<double> pln;
  vector<double> channel;
  vector<double> HG;
  vector<double> LHG;
  vector<double> RHG;
  vector<double> THG;
  vector<double> Lgain;
  vector<double> Rgain;
  vector<double> Tgain;
  vector<double> LG;
  vector<double> Ltime;
  vector<double> Ftime;
  vector<double> Htime;
  vector<double> timedif;
  vector<double> bunch;
  
  int bm_event;

  BMBasicRecon();
  ~BMBasicRecon(); 
  
  void Clear();
  void CopyClass(BMBasicRecon* bmbasicrecon1, BMBasicRecon* bmbasicrecon2);

};

#endif
