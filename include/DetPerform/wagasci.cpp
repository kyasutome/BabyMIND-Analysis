#include <iostream>
#include <fstream>
#include <vector>

#include "wagasci.hpp"

using namespace std;
//#define debug

WAGASCI::WAGASCI()
{
  TDCmax = 4081;
  slope[0] = -8.2;//[TDC/ns]
  slope[1] = 8.6;//[TDC/ns]
  bcidwidth = 580; //[ns]

}

WAGASCI::~WAGASCI()
{
}

void WAGASCI::TDCtoHittime( int oddeven, int TDC, int *htime, int bunch)
{
  int timeoffset = 580*(bunch+24-1);
  if(oddeven==0)//even
    {
      szone = 4081/fabs(slope[0]);
      dzone = (bcidwidth-szone)/2;
      *htime = (TDC-(4096-slope[0]*dzone))/slope[0] + timeoffset;
    }

  if(oddeven==1)//odd
    {
      szone = 4081/fabs(slope[1]);
      dzone = (bcidwidth-szone)/2;
      *htime = (TDC-(15-slope[1]*dzone))/slope[1] + timeoffset;
    }

}
