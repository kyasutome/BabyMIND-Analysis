#include <iostream>
#include <stdio.h>

#include "MCTrue.hpp"

using namespace std;

MCTrue::MCTrue()
{

  for(int ipar=0; ipar<20; ipar++)
    {
      pdg[ipar]=-1;
      for(int imom=0; imom<4; imom++)
	{
	  ipos[imom][ipar]=-9999.;
	  fpos[imom][ipar]=-9999.;
	  momentum[imom][ipar]=-9999.;
	}
    }

  inttype=-1;
  nutype=-1;
  npar=-1;

  totcrsne = -1.;
  norm = -1.;
  nuE = -1.;
  xnu = -1.;
  ynu = -1.;
  znu = -1.;
  
  for(int imom=0; imom<3; imom++)
    Pnu[imom] = -1.;
}


MCTrue::~MCTrue()
{
}

void MCTrue::Clear()
{

  for(int ipar=0; ipar<20; ipar++)
    {
      pdg[ipar]=-1;
      for(int imom=0; imom<4; imom++)
	{
	  ipos[imom][ipar]=-9999.;
	  fpos[imom][ipar]=-9999.;
	  momentum[imom][ipar]=-9999.;
	}
    }

  inttype=-1;
  nutype=-1;
  npar=-1;

  totcrsne = -1.;
  norm = -1.;
  nuE = -1.;
  xnu = -1.;
  ynu = -1.;
  znu = -1.;
  
  for(int imom=0; imom<3; imom++)
    Pnu[imom] = -1.;

}

