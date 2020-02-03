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
  dimension->get_pos_bm_FC(6, view, pln, ch, &x, &y, &z);
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
  dimension->get_pos_bm_FC(6, view, pln, ch, &x, &y, &z);
  TArc *arc = new TArc(z+offsetz,y+offsety,r);
  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(2);
  arc->Draw("SAME");
}

void MakeHitDisp::pmxhit(double pln, double ch, double r, double bunch){
  double X,Y,R;
  double offsetx = -2000;
  double offsety = -1500;

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
      offsety= -550;

  if(view==1)
      offsety= -1500;

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

void MakeHitDisp::wgyhit(double dif, double chip, double chan, double r, double bunch)
{
  double x, y, z;
  int modid = dif/2-2;
  double offsetx[2][2]={{-2300,-2300},{-350,-350}};//{{mod0view0, mod0view1}, {mod1view0, mod1view1}}
  double offsety[2][2]={{-100,-900},{-100,-600}};//{{mod0view0, mod0view1}, {mod1view0, mod1view1}}
  dimension->get_pos_wg_FC(dif, chip, chan, &x, &y, &z);
  cout << dif << " " << chip << " " << chan << " " << x << " " << y << " " << z << '\n';
  TArc *arc = new TArc(z+offsetx[modid][0],y+offsety[modid][0],r);
  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(2);
  arc->Draw("SAME");
}

void MakeHitDisp::wgxhit(double dif, double chip, double chan, double r, double bunch)
{
  double x, y, z;
  int modid = dif/2-2;
  double offsetx[2][2]={{-2300,-2300},{-350,-350}};//{{mod0view0, mod0view1}, {mod1view0, mod1view1}}
  double offsety[2][2]={{-100,-900},{-100,-600}};//{{mod0view0, mod0view1}, {mod1view0, mod1view1}}
  dimension->get_pos_wg_FC(dif, chip, chan, &x, &y, &z);
  cout << dif << " " << chip << " " << chan << " " << x << " " << y << " " << z << '\n';
  TArc *arc = new TArc(z+offsetx[modid][1],x+offsety[modid][1],r);
  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(2);
  arc->Draw("SAME");
}

void MakeHitDisp::wmhit(double dif, double chip, double chan, double r, double bunch)
{
  double x, y, z;
  int modid = dif/2;
  double offsetx[2]={-2000,-1700};//{{mod0view0, mod0view1}, {mod1view0, mod1view1}}
  double offsety[2]={-2200,+700};//{{mod0view0, mod0view1}, {mod1view0, mod1view1}}
  dimension->get_pos_wm_FC(dif, chip, chan, &x, &y, &z);
  cout << dif << " " << chip << " " << chan << " " << x << " " << y << " " << z << '\n';
  TArc *arc = new TArc(z+offsetx[modid],x+offsety[modid], r);
  ColorScale(&color, (int)bunch);
  arc->SetFillColor(color);
  arc->SetLineColor(2);
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

void MakeHitDisp::DrawWGHit(BMDisp* bmdisp, int VIEW, int MOD)
{
  nhit = bmdisp->pln.size();
  for(int ihit=0; ihit<nhit; ihit++)
    {
      mod = bmdisp->mod.at(ihit);
      dif = bmdisp->view.at(ihit);
      chip = bmdisp->pln.at(ihit);
      chan = bmdisp->channel.at(ihit);
      bunch = bmdisp->bunch.at(ihit);
      
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

void MakeHitDisp::DrawWMHit(BMDisp* bmdisp, int MOD)
{
  nhit = bmdisp->pln.size();
  for(int ihit=0; ihit<nhit; ihit++)
    {
      mod = bmdisp->mod.at(ihit);
      dif = bmdisp->view.at(ihit);
      chip = bmdisp->pln.at(ihit);
      chan = bmdisp->channel.at(ihit);
      bunch = bmdisp->bunch.at(ihit);
      
      if(mod==MOD && mod==3)
	{
	  if(dif==0 || dif==1)
	    wmhit(dif, chip, chan, r, bunch);

	  cout << "mod:" << mod << " dif:" << dif << " chip:" << chip << " chan:" 
	       << chan << " bunch:" << bunch << '\n';
	  
	}

      if(mod==MOD && mod==4)
	{
	  if(dif==2 || dif==3)
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
