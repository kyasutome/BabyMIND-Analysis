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

Dimension *dimension = new Dimension();

void MakeHitDisp::bmxhit(double pln, double ch, double r, double bunch)
{
  double x, y, z;
  int offsety = 0;
  int offsetz = -15;
  dimension->get_pos_bm_FC(5, 1, pln-1, ch, &x, &y, &z);
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
  dimension->get_pos_bm_FC(5, 0, pln-1, ch, &x, &y, &z);
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
  dimension->get_pos_bm_FC(5, view, pln, ch, &x, &y, &z);
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
  dimension->get_pos_bm_FC(5, view, pln, ch, &x, &y, &z);
  TArc *arc = new TArc(z+offsetz,y+offsety,r);
  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(2);
  arc->Draw("SAME");
}

void MakeHitDisp::pmxhit(double pln, double ch, double r, double bunch){
  double X,Y,R;
  double offsetx = -2000;
  double offsety = -1050;

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

  X = X+offsetx;
  Y = Y+offsety;

  TArc *arc=new TArc(X,Y,R);
  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(kRed);
  arc->Draw("SAME");

}

void MakeHitDisp::pmyhit(double pln, double ch, double r, double bunch){
  double X,Y,R;
  double offsetx = -2000;
  double offsety = -550;

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

  X = X+offsetx;
  Y = Y+offsety;

  TArc *arc=new TArc(X,Y,R);
  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(kRed);
  arc->Draw("SAME");
}

void MakeHitDisp::pmvhit(double pln, double ch, double view, double r, double bunch)
{
  double X,Y,R;
  double offsetx = -2000;
  double offsety;
  if(view==0)
      offsety= -500;

  if(view==1)
      offsety= -1000;

  if(pln==0)Y=-55;
  else Y=1255;
  X=5+9.5+ch*50;
  if(r<2)R=0;
  else R=sqrt(r-2)*3;
  X = X+offsetx;
  Y = Y+offsety;
  TArc *arc=new TArc(X,Y,R);
  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(kRed);
  arc->Draw("SAME");
}


void MakeHitDisp::DrawBMHit(BMDisp* bmdisp, int VIEW)
{
  nhit = bmdisp->pln.size();  
  cout << "hitsize= " << nhit << '\n';
  for(int ihit=0; ihit<nhit; ihit++)
    {
      mod = bmdisp->mod.at(ihit);
      view = bmdisp->view.at(ihit);
      pln = bmdisp->pln.at(ihit);
      ch = bmdisp->channel.at(ihit);
      bunch = bmdisp->bunch.at(ihit);

      cout << "mod:" << mod << " view:" << view << " pln:" << pln << " ch:" << ch << " bunch:" << bunch << '\n';
       
      if(mod==5)
	{
	  if(view==VIEW && view==0)
	    {
	      bmyhit(pln, ch, r, bunch);
	      yasuyhit(view, pln, ch, r, bunch);
	    }
	  
	  if(view==VIEW && view==1)
	    {
	      bmxhit(pln, ch, r, bunch);
	      yasuxhit(view, pln, ch, r, bunch);
	    }
	}
    }//ihit loop
}

void MakeHitDisp::DrawPMHit(BMDisp* bmdisp, int VIEW)
{
  nhit = bmdisp->pln.size();
  
  for(int ihit=0; ihit<nhit; ihit++)
    {
      mod = bmdisp->mod.at(ihit);
      view = bmdisp->view.at(ihit);
      pln = bmdisp->pln.at(ihit);
      ch = bmdisp->channel.at(ihit);
      bunch = bmdisp->bunch.at(ihit);

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

void MakeHitDisp::ColorScale(int *color, int bunch)
{
  *color = bunch+1;
}
