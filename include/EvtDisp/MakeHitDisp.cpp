#include <iostream>
#include <fstream>
#include <vector>

#include "MakeHitDisp.hpp"
#include "Dimension.cpp"

using namespace std;
//#define debug
#define MC
//#define beam

MakeHitDisp::MakeHitDisp()
{
  r = 50;
}

MakeHitDisp::~MakeHitDisp()
{ 
}

Dimension *fdimension = new Dimension();

void MakeHitDisp::Hit(double z, double xy, double r, double bunch)
{

  TArc *arc = new TArc(z,xy,r);
  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(2);
  arc->Draw("SAME");
  cout << "z= " << z << " xy= " << xy << '\n';
}

void MakeHitDisp::DrawHit(EVTCluster* evtcluster, int VIEW)
{
  nhit = evtcluster->pln.size();
  
  for(int ihit=0; ihit<nhit; ihit++)
    {
      mod = evtcluster->mod.at(ihit);
      view = evtcluster->view.at(ihit);
      posz = evtcluster->posz.at(ihit);
      posx = evtcluster->posx.at(ihit);
      posy = evtcluster->posy.at(ihit);
      bunch = evtcluster->bunch.at(ihit);

#ifdef beam
      if(mod == 3 || mod == 4)
	view = 1;
      if(mod == 1 || mod == 2)
	view = fabs(view%2-1);
#endif
      
      if(view==VIEW && view==0)
	Hit(posz, posy, r, bunch);
      
      if(view==VIEW && view==1)
	Hit(posz, posx, r, bunch);
    }//ihit loop
}

void MakeHitDisp::ColorScale(int *color, int bunch)
{
  *color = bunch+1;
}


