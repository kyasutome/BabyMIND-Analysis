#include <iostream>
#include <fstream>
#include <vector>

#include "Dimension.hpp"
#include "WGChannelMap.cpp"

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
  fin[6].open("./data/udwagasci_xy_side.txt");
  fin[7].open("./data/udwagasci_z_side.txt");
  fin[8].open("./data/udwagasci_xy_top.txt");
  fin[9].open("./data/udwagasci_z_top.txt");

  nfile = 10;

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

  for(int idif=0; idif<8; idif++)
    {
      if(idif<4) NCHIPS = 3;
      if(idif>=4) NCHIPS = 20;
      mapping[idif] = load_mapping(file, NCHIPS, NCHANNELS, idif);
    }

  int count_grid=0;
  int count_pln=0;

  for(int i=0; i<60; i++)
    {
      if(i%3==1)
        {
          fin[6] >> uwgposy_grid[count_grid] >> dwgposy_grid[count_grid];
          fin[8] >> uwgposx_grid[count_grid] >> dwgposx_grid[count_grid];
          count_grid++;
        }

      if(i%3!=1)
        {
          fin[6] >> uwgposy_pln[count_pln] >> dwgposy_pln[count_pln];
          fin[8] >> uwgposx_pln[count_pln] >> dwgposx_pln[count_pln];
          count_pln++;
        }
    }

  for(int i=0; i<24; i++)
    {
      fin[7] >> uwgpossz[i] >> dwgpossz[i];
      fin[9] >> uwgpostz[i] >> dwgpostz[i];
    }

  cout << "Read Dimension Files for WAGASCI&WallMRD" << '\n';

  

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

  if(mod==6)
    {
      *posx = yasuposx[view][7*(pln-19)+(int)ch];
      *posy = yasuposy[view][7*(pln-19)+(int)ch];
      *posz = yasuposz[view][7*(pln-19)+(int)ch];
    }

  else if(mod==5)
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

bool Dimension::get_pos_pm_FC(int mod, int view, int pln, double ch, double *posx, double *posy, double *posz)
{

  double X, Y;
  double offsetx[2] = {-2000, -2000};
  double offsety[2] = {-550, -1500};

  if(view==0)
    {
      if(pln==0)X=28;
      else X=46*pln+32;
      if(pln==0)Y=ch*50+25;
      else{
	if(ch<8)Y=ch*50+25;
	else if(ch<24)Y=412.5+(ch-8)*25;
	else Y=(ch-8)*50+25;
      }

      *posx = -1;
      *posz = X+offsetx[view];
      *posy = Y+offsety[view];
    }

  if(view==1)
    {
      if(pln==0)X=5;
      else X=46*pln+9;
      if(pln==0)Y=ch*50+25;
      else{
	if(ch<8)Y=ch*50+25;
	else if(ch<24)Y=412.5+(ch-8)*25;
	else Y=(ch-8)*50+25;
      }

      *posy = -1;
      *posz = X+offsetx[view];
      *posx = Y+offsety[view];
    }

  return true;
}

bool Dimension::get_pos_wm_FC(int dif, int chip, int chan, double *posx, double *posy, double *posz)
{
  *posx = mapping[dif][chip][chan].x;
  *posy = mapping[dif][chip][chan].y;
  *posz = mapping[dif][chip][chan].z;

  return true;
}

bool Dimension::get_pos_wg_FC(int dif, int chip, int chan, double *posx, double *posy, double *posz)
{
  *posx = mapping[dif][chip][chan].x;
  *posy = mapping[dif][chip][chan].y;
  *posz = mapping[dif][chip][chan].z;

  return true;
}

bool Dimension::get_wgdet_pos(int ud, int view, int zid, int xyid, double *posxy, double *posz)
{
  if(ud==0)
    {
      if(view==0)
        {
          if(zid%3==1||zid%3==2)
            {
              *posxy = uwgposy_grid[xyid];
              *posz = uwgpossz[zid];
            }
          if(zid%3==0)
            {
              *posxy = uwgposy_pln[xyid];
              *posz = uwgpossz[zid];
            }
        }
      if(view==1)
        {
          if(zid%3==0||zid%3==2)
            {
              *posxy = uwgposx_grid[xyid];
              *posz = uwgpostz[zid];
            }
          if(zid%3==1)
            {
              *posxy = uwgposx_pln[xyid];
              *posz = uwgpostz[zid];
            }
        }
    }

  if(ud==1)
    {

      if(view==0)
        {
          if(zid%3==1||zid%3==2)
            {
              *posxy = dwgposy_grid[xyid];
              *posz = dwgpossz[zid];
            }
          if(zid%3==0)
            {
              *posxy = dwgposy_pln[xyid];
              *posz = dwgpossz[zid];
            }
        }
      if(view==1)
        {
          if(zid%3==0||zid%3==2)
            {
              *posxy = dwgposx_grid[xyid];
              *posz = dwgpostz[zid];
            }
          if(zid%3==1)
            {
              *posxy = dwgposx_pln[xyid];
              *posz = dwgpostz[zid];
            }

        }

    }

  return true;

}




