#include <iostream>
#include <fstream>
#include <vector>

#include "MakeHitDisp.hpp"
#include "Dimension.cpp"

using namespace std;
//#define debug

MakeHitDisp::MakeHitDisp()
{
  r = 20;
}

MakeHitDisp::~MakeHitDisp()
{ 
}

Dimension *fdimension = new Dimension();

void MakeHitDisp::bmxhit(double pln, double ch, double r, double bunch)
{
  double x, y, z;
  int offsety = 0;
  int offsetz = -15;
  fdimension->get_pos_bm_FC(5, 1, pln-1, ch, &x, &y, &z);
  TArc *arc = new TArc(z+offsetz,x+offsety,r);
  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(2);
  arc->Draw("SAME");
}

void MakeHitDisp::bmyhit(double pln, double ch, double r, double bunch)
{
  double x, y, z;
  int offsety = 0;
  int offsetz = -20;
  fdimension->get_pos_bm_FC(5, 0, pln-1, ch, &x, &y, &z);
  TArc *arc = new TArc(z+offsetz,y+offsety,r);
  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(2);
  arc->Draw("SAME");
}

void MakeHitDisp::yasuxhit(double view, double pln, double ch, double r, double bunch)
{
  double x, y, z;
  int offsety = 0;
  int offsetz = 0;
  fdimension->get_pos_bm_FC(6, view, pln, ch, &x, &y, &z);
  TArc *arc = new TArc(z+offsetz,x+offsety,r);
  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(2);
  arc->Draw("SAME");
}

void MakeHitDisp::yasuyhit(double view, double pln, double ch, double r, double bunch)
{
  double x, y, z;
  int offsety = 0;
  int offsetz = 0;
  fdimension->get_pos_bm_FC(6, view, pln, ch, &x, &y, &z);
  TArc *arc = new TArc(z+offsetz,y+offsety,r);
  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(2);
  arc->Draw("SAME");
}

void MakeHitDisp::pmxhit(double pln, double ch, double r, double bunch){
  double X,Y,R;

  if(pln==0)X=5;
  else X=46*pln+9;
  if(pln==0)Y=ch*50+25;
  else{
    if(ch<8)Y=ch*50+25;
    else if(ch<24)Y=412.5+(ch-8)*25;
    else Y=(ch-8)*50+25;
  }
  if(r<2)R=0;
  else R=sqrt(r-2)*3;

  X = X+fdimension->offset[1][0][0];
  Y = Y+fdimension->offset[1][1][0];

  TArc *arc=new TArc(X,Y,R);
  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(kRed);
  arc->Draw("SAME");

}

void MakeHitDisp::pmyhit(double pln, double ch, double r, double bunch){
  double X,Y,R;

  if(pln==0)X=28;
  else X=46*pln+32;
  if(pln==0)Y=ch*50+25;
  else{
    if(ch<8)Y=ch*50+25;
    else if(ch<24)Y=412.5+(ch-8)*25;
    else Y=(ch-8)*50+25;
  }
  if(r<2)R=0;
  else R=sqrt(r-2)*3;

  X = X+fdimension->offset[0][0][0];
  Y = Y+fdimension->offset[0][1][0];

  TArc *arc=new TArc(X,Y,R);
  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(kRed);
  arc->Draw("SAME");
}

void MakeHitDisp::pmvhit(double pln, double ch, double view, double r, double bunch)
{
  double X,Y,R;

  if(pln==0)Y=-55;
  else Y=1255;
  X=5+9.5+ch*50;
  if(r<2)R=0;
  else R=sqrt(r-2)*3;
  X = X+fdimension->offset[(int)view][0][0];
  Y = Y+fdimension->offset[(int)view][1][0];
  TArc *arc=new TArc(X,Y,R);
  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(kRed);
  arc->Draw("SAME");
}

void MakeHitDisp::wgyhit(double dif, double chip, double chan, double r, double bunch)
{
  double x, y, z;
  int modid = dif/2-1;
  fdimension->get_pos_wg_FC(dif, chip, chan, &x, &y, &z);
  //cout << dif << " " << chip << " " << chan << " " << x << " " << y << " " << z << '\n';
  TArc *arc = new TArc(z+fdimension->offset[0][0][modid],y+fdimension->offset[0][1][modid],r);
  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(2);
  arc->Draw("SAME");
}

void MakeHitDisp::wgxhit(double dif, double chip, double chan, double r, double bunch)
{
  double x, y, z;
  int modid = dif/2-1;
  fdimension->get_pos_wg_FC(dif, chip, chan, &x, &y, &z);
  cout << dif << " " << chip << " " << chan << " " << x << " " << y << " " << z << '\n';
  TArc *arc = new TArc(z+fdimension->offset[1][0][modid],x+fdimension->offset[1][1][modid],r);
  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(2);
  arc->Draw("SAME");
}

void MakeHitDisp::wmhit(double dif, double chip, double chan, double r, double bunch)
{
  double x, y, z;
  int modid = dif/2+3;
  fdimension->get_pos_wm_FC(dif, chip, chan, &x, &y, &z);
  cout << dif << " " << chip << " " << chan << " " << x << " " << y << " " << z << '\n';
  TArc *arc = new TArc(z+fdimension->offset[1][0][modid],x+fdimension->offset[1][1][modid],r);

  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(2);
  arc->Draw("SAME");
}


void MakeHitDisp::DrawBMHit(EVTCluster* evtcluster, int VIEW)
{
  nhit = evtcluster->pln.size();  
  cout << "hitsize= " << nhit << '\n';
  for(int ihit=0; ihit<nhit; ihit++)
    {
      mod = evtcluster->mod.at(ihit);
      view = evtcluster->view.at(ihit);
      pln = evtcluster->pln.at(ihit);
      ch = evtcluster->channel.at(ihit);
      bunch = evtcluster->bunch.at(ihit);

      cout << "mod:" << mod << " view:" << view << " pln:" << pln << " ch:" << ch << " bunch:" << bunch << '\n';
       
      if(mod==5)
	{
	  if(view==VIEW && view==0)
	    {
	      bmyhit(pln, ch, r, bunch);
	    }
	  
	  if(view==VIEW && view==1)
	    {
	      bmxhit(pln, ch, r, bunch);
	    }
	}

      
      if(mod==6)
	{
	  if(view==VIEW && view==0)
	    {
	      yasuyhit(view, pln, ch, r, bunch);
	    }
	  
	  if(view==VIEW && view==1)
	    {
	      yasuxhit(view, pln, ch, r, bunch);
	    }
	}
      
    }//ihit loop
}

void MakeHitDisp::DrawPMHit(EVTCluster* evtcluster, int VIEW)
{
  nhit = evtcluster->pln.size();
  
  for(int ihit=0; ihit<nhit; ihit++)
    {
      mod = evtcluster->mod.at(ihit);
      view = evtcluster->view.at(ihit);
      pln = evtcluster->pln.at(ihit);
      ch = evtcluster->channel.at(ihit);
      bunch = evtcluster->bunch.at(ihit);

      cout << "mod:" << mod << " view:" << view << " pln:" << pln << " ch:" << ch << " bunch:" << bunch << '\n';
      
      if(mod==0)
	{
	  if(view==VIEW && view==0)
	    pmyhit(pln, ch, r, bunch);
	  
	  if(view==VIEW && view==1)
	    pmxhit(pln, ch, r, bunch);
	}
    }//ihit loop
}

void MakeHitDisp::DrawWGHit(EVTCluster* evtcluster, int VIEW, int MOD)
{
  nhit = evtcluster->pln.size();
  for(int ihit=0; ihit<nhit; ihit++)
    {
      mod = evtcluster->mod.at(ihit);
      dif = evtcluster->view.at(ihit);
      chip = evtcluster->pln.at(ihit);
      chan = evtcluster->channel.at(ihit);
      bunch = evtcluster->bunch.at(ihit);
      
      if(mod==MOD && mod==1)
	{
	  if(VIEW==1 && dif==4)
	    {
	      wgxhit(dif, chip, chan, r, bunch);
	    }
	  
	  if(VIEW==0 && dif==5)
	    {
	      wgyhit(dif, chip, chan, r, bunch);
	    }
	}

      if(mod==MOD && mod==2)
	{
	  if(VIEW==1 && dif==6)
	    {
	      wgxhit(dif, chip, chan, r, bunch);
	    }
	  
	  if(VIEW==0 && dif==7)
	    {
	      wgyhit(dif, chip, chan, r, bunch);
	    }
	}

    }//ihit loop
}

void MakeHitDisp::DrawWMHit(EVTCluster* evtcluster, int MOD)
{
  nhit = evtcluster->pln.size();
  for(int ihit=0; ihit<nhit; ihit++)
    {
      mod = evtcluster->mod.at(ihit);
      dif = evtcluster->view.at(ihit);
      chip = evtcluster->pln.at(ihit);
      chan = evtcluster->channel.at(ihit);
      bunch = evtcluster->bunch.at(ihit);
      
      if(mod==MOD && mod==3)
	{
	  if(dif==0 || dif==1)
	  //if(dif==1)
	    wmhit(dif, chip, chan, r, bunch);

	  cout << "mod:" << mod << " dif:" << dif << " chip:" << chip << " chan:" 
	       << chan << " bunch:" << bunch << '\n';
	  
	}

      if(mod==MOD && mod==4)
	{
	  if(dif==2 || dif==3)
	  //if(dif==3)
	    wmhit(dif, chip, chan, r, bunch);

	  cout << "mod:" << mod << " dif:" << dif << " chip:" << chip << " chan:" 
	       << chan << " bunch:" << bunch << '\n';
	  
	}

    }//ihit loop
}


void MakeHitDisp::ColorScale(int *color, int bunch)
{
  *color = bunch+1;
}
