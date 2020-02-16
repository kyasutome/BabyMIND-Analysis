#include <iostream>
#include <stdio.h>

#include "BasicRecon.hpp"

using namespace std;

BasicRecon::BasicRecon()
{
  for(int i=0; i<2; i++)
    {
      angle[i]=-1;
      for(int j=0; j<3; j++)
	{
	  ipos[i][j]=-1;
	  fpos[i][j]=-1;
	}

      for(int j=0; j<9; j++)
	Nhit[i][j]=-1;

    }



}


BasicRecon::~BasicRecon()
{
}

void BasicRecon::Clear()
{

  for(int i=0; i<2; i++)
    {
      angle[i]=-1;
      for(int j=0; j<3; j++)
	{
	  ipos[i][j]=-1;
	  fpos[i][j]=-1;
	}

      for(int j=0; j<9; j++)
	Nhit[i][j]=-1;
    }




}
