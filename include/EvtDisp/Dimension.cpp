#include <iostream>
#include <fstream>
#include <vector>

#include "Dimension.hpp"

using namespace std;
//#define debug

inline Dimension::Dimension()
{
  double temp[5];
  fin[0].open("./data/v1_horizontal_from_center.txt");
  fin[1].open("./data/v1_vertical_from_center.txt");
  fin[2].open("./data/Scin_Mod_position.txt");
  fin[3].open("./data/Iron_Mod_position.txt");
  fin[4].open("./data/correction.txt");
  fin[5].open("./data/YASU_position.txt");
  nfile = 6;

  for(int i=0; i<95; i++)
    {
      fin[0] >> temp[0] >> temp[1] >> temp[2] >> temp[3] >> temp[4];
      sciposy[i] = temp[4];
    }

  for(int i=0; i<32; i++)
    {
      fin[1] >> temp[0] >> temp[1] >> temp[2] >> temp[3] >> temp[4];
      if(i%2==0)
        {
          sciposx[i/2] = temp[4];
        }
    }

  sciposz[0] = -20;
  for(int i=0; i<18; i++)
    {
      fin[2] >> temp[0] >> temp[1] >> temp[2] >> temp[3];
      sciposz[i] = temp[3];
    }

  for(int i=0; i<33; i++)
    {
      fin[3] >> temp[0] >> temp[1];
      ironposz[i] = temp[1];
    }

  for(int i=0; i<19; i++)
    {
      fin[4] >> temp[0] >> temp[1];
      correction[i] = temp[1];
    }

  for(int i=0; i<14; i++)
    {
      fin[5] >> temp[0] >> yasuposx[0][i] >> yasuposy[0][i] >> yasuposz[0][i]
           >> yasuposx[1][i] >> yasuposy[1][i] >> yasuposz[1][i];
    }

  cout << "Read Dimension Files for Baby MIND" << '\n';
  for(int ifile=0; ifile<nfile; ifile++)
    {
      fin[ifile].close();
    }

}

Dimension::~Dimension()
{
}

bool Dimension::get_pos_bm_FC(int mod, int view, int pln, double ch, double *posx, double *posy, double *posz)
{
  double epsilon = 0.1;

  if(pln==19 || pln==20)
    {
      *posx = yasuposx[view][7*(pln-19)+(int)ch];
      *posy = yasuposy[view][7*(pln-19)+(int)ch];
      *posz = yasuposz[view][7*(pln-19)+(int)ch];
    }

  else if(pln!=19 && pln!=20)
    {      
      if(view==0)
	{
	  int minch = ch;
	  if(fabs(minch-ch)<epsilon)
	    {
	      *posz = sciposz[pln] + (minch%2+1)*10 +10;
	      *posy = sciposy[minch] + correction[pln];
	    }
	  if(fabs(minch-ch)>=epsilon)
	    {
	      *posz = sciposz[pln] + 20;
	      *posy = (sciposy[minch] + sciposy[minch+1])/2 + correction[pln];
	    }
	}
      
      if(view==1)
	{
	  int minch = ch;
	  if(fabs(minch-ch)<epsilon)
	    {
	      *posz = sciposz[pln] + (minch%2)*30 +5;
	      *posx = sciposx[minch];
	    }
	  if(fabs(minch-ch)>=epsilon)
	    {
	      *posz = sciposz[pln] + 20;
	      *posx = (sciposx[minch] + sciposx[minch+1])/2;
	    }
	}
    }

  return true;
}     





