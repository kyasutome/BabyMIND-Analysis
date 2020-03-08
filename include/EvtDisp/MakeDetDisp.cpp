#include <iostream>
#include <fstream>
#include <vector>

#include "MakeDetDisp.hpp"
//#include "Dimension.cpp"

using namespace std;

MakeDetDisp::MakeDetDisp()
{
}

MakeDetDisp::~MakeDetDisp()
{
}

//Dimension *fdimension = new Dimension();

void MakeDetDisp::DetModule(double x1, double y1, double x2, double y2)
{
  TBox *b1 = new TBox(x1, y1, x2, y2);
  Int_t trans_blue = TColor::GetColorTransparent(kBlue, 0.8);
  b1->SetLineColor(1);
  b1->SetFillColor(trans_blue);
  b1->SetLineWidth(3);
  b1->SetFillStyle(1001);
  b1->Draw("SAME");
}

void MakeDetDisp::MagModule(double x1, double y1, double x2, double y2){
  TBox *b1 = new TBox(x1, y1, x2, y2);
  Int_t trans_orange = TColor::GetColorTransparent(kOrange, 0.8);
  b1->SetLineColor(trans_orange);
  b1->SetFillColor(trans_orange);
  b1->SetLineWidth(2);
  b1->SetFillStyle(1001);
  b1->Draw("SAME");
}

void MakeDetDisp::YASUModule(double x1, double y1, double x2, double y2){
  TBox *b1 = new TBox(x1, y1, x2, y2);
  Int_t trans_blue = TColor::GetColorTransparent(kBlue, 0.6);
  b1->SetLineColor(1);
  b1->SetFillColor(trans_blue);
  b1->SetLineWidth(3);
  b1->SetFillStyle(1001);
  b1->Draw("SAME");
}


void MakeDetDisp::IngSci(double x,double y,double x1,double y1,int view){

  double posx1, posx2, posy1, posy2;
  posx1 = x+fdimension->offset[view][0][0];
  posx2 = x1+fdimension->offset[view][0][0];
  posy1 = y+fdimension->offset[view][1][0];
  posy2 = y1+fdimension->offset[view][1][0];

  TBox *b1=new TBox(posx1,posy1,posx2,posy2);
  Int_t trans_blue = TColor::GetColorTransparent(kBlue, 0.05);
  b1->SetLineColor(trans_blue);
  b1->SetLineWidth(0.5);
  b1->SetFillStyle(0);
  b1->Draw("SAME");
}


void MakeDetDisp::ParSci(double x,double y,double x1,double y1,int view){

  double posx1, posx2, posy1, posy2;
  posx1 = x+fdimension->offset[view][0][0];
  posx2 = x1+fdimension->offset[view][0][0];
  posy1 = y+fdimension->offset[view][1][0];
  posy2 = y1+fdimension->offset[view][1][0];

  TBox *b1=new TBox(posx1,posy1,posx2,posy2);
  Int_t trans_blue = TColor::GetColorTransparent(kBlue, 0.05);
  b1->SetLineColor(trans_blue);
  b1->SetLineWidth(1);
  b1->SetFillStyle(0);
  b1->Draw("SAME");
}

void MakeDetDisp::SciSci(double x,double y,double x1,double y1,int view){

  double posx1, posx2, posy1, posy2;
  posx1 = x+fdimension->offset[view][0][0];
  posx2 = x1+fdimension->offset[view][0][0];
  posy1 = y+fdimension->offset[view][1][0];
  posy2 = y1+fdimension->offset[view][1][0];

  Int_t trans_blue = TColor::GetColorTransparent(kBlue, 0.3);
  TBox *b1=new TBox(posx1,posy1,posx2,posy2);
  b1->SetLineColor(trans_blue);
  b1->SetLineWidth(1);
  b1->SetFillStyle(0);
  b1->Draw("SAME");
}

void MakeDetDisp::VetoSci(double x,double y,double x1,double y1, int view){

  double posx1, posx2, posy1, posy2;
  posx1 = x+fdimension->offset[view][0][0];
  posx2 = x1+fdimension->offset[view][0][0];
  posy1 = y+fdimension->offset[view][1][0];
  posy2 = y1+fdimension->offset[view][1][0];

  TBox *b1=new TBox(posx1,posy1,posx2,posy2);
  Int_t trans_blue = TColor::GetColorTransparent(kBlue, 0.8);
  b1->SetLineColor(trans_blue);
  b1->SetLineWidth(2);
  b1->SetFillStyle(0);
  b1->Draw("SAME");
}

void MakeDetDisp::PlnSci(int mod, int view, double x, double y){
  double planey = 24.5/2;
  double planez = 3.0/2;
  double posx1, posx2, posy1, posy2;

  posx1 = x-planez+fdimension->offset[view][0][mod];
  posx2 = x+planez+fdimension->offset[view][0][mod];
  posy1 = y-planey+fdimension->offset[view][1][mod];
  posy2 = y+planey+fdimension->offset[view][1][mod];

  TBox *b1 = new TBox(posx1, posy1, posx2, posy2);
  Int_t trans_blue = TColor::GetColorTransparent(kBlue, 0.8);
  b1->SetLineColor(trans_blue);
  b1->SetFillColor(trans_blue);
  b1->SetLineWidth(2);
  b1->SetFillStyle(1001);
  b1->Draw("SAME");
};

void MakeDetDisp::GridSci(int mod, int view, double x, double y){
  double gridy = 3.0/2;
  double gridz = 24.5/2;

  double posx1, posx2, posy1, posy2;

  posx1 = x-gridz+fdimension->offset[view][0][mod];
  posx2 = x+gridz+fdimension->offset[view][0][mod];
  posy1 = y-gridy+fdimension->offset[view][1][mod];
  posy2 = y+gridy+fdimension->offset[view][1][mod];

  TBox *b1 = new TBox(posx1, posy1, posx2, posy2);
  Int_t trans_blue = TColor::GetColorTransparent(kBlue, 0.6);
  b1->SetLineColor(trans_blue);
  b1->SetFillColor(trans_blue);
  b1->SetLineWidth(2);
  b1->SetFillStyle(1001);
  b1->Draw("SAME");
};

void MakeDetDisp::WaterTank(int mod, int view)
{
  double posx1, posx2, posy1, posy2;
  double size_yoko = 550;
  double size_tate = 1100;
  posx1 = fdimension->offset[view][0][mod];
  posy1 = fdimension->offset[view][1][mod];
  posx2 = fdimension->offset[view][0][mod]+size_yoko;
  posy2 = fdimension->offset[view][1][mod]+size_tate;
  TBox *b1 = new TBox(posx1, posy1, posx2, posy2);
  Int_t trans_blue = TColor::GetColorTransparent(kCyan, 0.3);
  b1->SetLineColor(kBlack);
  b1->SetFillColor(trans_blue);
  b1->SetLineWidth(1);
  b1->SetFillStyle(1001);
  b1->Draw("SAME");
}

void MakeDetDisp::SciModule(int mod, double x1, double y1, double x2, double y2)
{
  double posx1, posx2, posy1, posy2;
  posx1 = x1+fdimension->offset[1][0][mod];
  posx2 = x2+fdimension->offset[1][0][mod];
  posy1 = y1+fdimension->offset[1][1][mod];
  posy2 = y2+fdimension->offset[1][1][mod];

  TBox *b1=new TBox(posx1, posy1, posx2, posy2);

  Int_t trans_blue = TColor::GetColorTransparent(kBlue, 0.6);
  b1->SetLineColor(trans_blue);
  b1->SetLineWidth(2);
  b1->SetFillStyle(0);
  b1->Draw("SAME");
}

void MakeDetDisp::IronModule(int mod, double x1, double y1, double x2, double y2)
{
  double posx1, posx2, posy1, posy2;
  posx1 = x1+fdimension->offset[1][0][mod];
  posx2 = x2+fdimension->offset[1][0][mod];
  posy1 = y1+fdimension->offset[1][1][mod];
  posy2 = y2+fdimension->offset[1][1][mod];
  
  TBox *b1=new TBox(posx1, posy1, posx2, posy2);

  Int_t trans_orange = TColor::GetColorTransparent(kOrange, 0.6);
  b1->SetLineColor(trans_orange);
  b1->SetLineWidth(2);
  b1->SetFillStyle(0);
  b1->Draw("SAME");
}

void MakeDetDisp::DrawBabyMIND(int view)
{
  //double Scin_thickness = 40; //cm
  double Iron_thickness = 40; //cm 
  double YASU_width = 1800; //mm
  double YASU_height = 200; //mm 
  double YASU_thick = 10; //mm  

  if(view==0)
    {
      for(int i=0; i<NUMBEROFHORMOD; i++)
	{
	  if(i%2==0)
	    {
	      dhorl[i/2] = fdimension->sciposy[i]-15;
	      uhorl[i/2] = fdimension->sciposy[i]+15;
	    }
	  if(i%2==1)
	    {
	      dhorr[i/2] = fdimension->sciposy[i]-15;
	      uhorr[i/2] = fdimension->sciposy[i]+15;
	    }
	}

      for(int i=1; i<=NUMBEROFMODULE; i++)
	{
	  for(int j=0; j<48; j++)
	    DetModule(fdimension->sciposz[i]-10, dhorl[j], fdimension->sciposz[i], uhorl[j]);
	  for(int j=0; j<47; j++)
	    DetModule(fdimension->sciposz[i], dhorr[j], fdimension->sciposz[i]+10, uhorr[j]);
	}
	  
      for(int i=0; i<33; i++)
	MagModule(fdimension->ironposz[i]-Iron_thickness/2-130, -986.2, 
		  fdimension->ironposz[i]+Iron_thickness/2-130, 986.2);


      //YASU Trackers
      for(int i=0; i<14; i++)
	{
	  YASUModule(fdimension->yasuposz[0][i]-YASU_thick/2.,fdimension->yasuposy[0][i]-YASU_height/2.,
		     fdimension->yasuposz[0][i]+YASU_thick/2.,fdimension->yasuposy[0][i]+YASU_height/2.);
	}      
    }//view==0

  if(view==1)
    {
      for(int i=0; i<16; i++)
	{
	  if(i%2==0)
	    {
	      dverl[i/2] = fdimension->sciposx[i]-100;
	      uverl[i/2] = fdimension->sciposx[i]+100;
	    }
	  if(i%2==1)
	    {
	      dverr[i/2] = fdimension->sciposx[i]-100;
	      uverr[i/2] = fdimension->sciposx[i]+100;
	    }
	}

      for(int i=1; i<=18; i++)
	{
	  for(int j=0; j<8; j++)
	    DetModule(fdimension->sciposz[i]-35, dverl[j], fdimension->sciposz[i]-15, uverl[j]);
	  for(int j=0; j<8; j++)
	    DetModule(fdimension->sciposz[i]-5, dverr[j], fdimension->sciposz[i]+15, uverr[j]);
	}

      for(int i=0; i<33; i++)
	MagModule(fdimension->ironposz[i]-Iron_thickness/2-130, -1750, 
		  fdimension->ironposz[i]+Iron_thickness/2-130, 1750);

      YASUModule(fdimension->yasuposz[0][0]-YASU_thick/2.,fdimension->yasuposx[0][0]-YASU_width/2.,
		 fdimension->yasuposz[0][0]+YASU_thick/2.,fdimension->yasuposx[0][0]+YASU_width/2.);

      YASUModule(fdimension->yasuposz[0][0]-YASU_thick/2.,fdimension->yasuposx[1][0]-YASU_width/2.,
		 fdimension->yasuposz[0][0]+YASU_thick/2.,fdimension->yasuposx[1][0]+YASU_width/2.);

      YASUModule(fdimension->yasuposz[0][7]-YASU_thick/2.,fdimension->yasuposx[0][0]-YASU_width/2.,
		 fdimension->yasuposz[0][7]+YASU_thick/2.,fdimension->yasuposx[0][0]+YASU_width/2.);

      YASUModule(fdimension->yasuposz[0][7]-YASU_thick/2.,fdimension->yasuposx[1][0]-YASU_width/2.,
		 fdimension->yasuposz[0][7]+YASU_thick/2.,fdimension->yasuposx[1][0]+YASU_width/2.);

    }//view==1


}


void MakeDetDisp::DrawProtonModule(int view)
{
  if(view==0)
    {
      int k,j;

      for(j=0;j<24;j++)
	{
	  IngSci(23,j*50,33,j*50+50,0);
	  ParSci(0,0,10,1200,0);
	}

      for(k=0;k<17;k++)
	{
	  for(j=0;j<8;j++)
	    IngSci(73+46*k,j*50,83+46*k,j*50+50,0);
	  for(j=16;j<24;j++)
	    IngSci(73+46*k,j*50,83+46*k,j*50+50,0);
	  for(j=0;j<16;j++)
	    {
	      SciSci(71.5+46*k,400+j*25,84.5+46*k,j*25+425,0);
	      ParSci(50+46*k,0,60+46*k,1200,0);
	    }
	}
      for(j=0;j<17;j++)
	  VetoSci(-15.5+50*j,-60,34.5+50*j,-50,0);
      for(j=0;j<17;j++)
	  VetoSci(-15.5+50*j,1250,34.5+50*j,1260,0);
    }

  if(view==1)
    {
      int k,j;
      for(j=0;j<24;j++)
	{
	  IngSci(23,j*50,33,j*50+50,1);
	  ParSci(0,0,10,1200,1);
	}


      for(k=0;k<17;k++)
	{
	  for(j=0;j<8;j++)
	      IngSci(73+46*k,j*50,83+46*k,j*50+50,1);
	  for(j=16;j<24;j++)
	      IngSci(73+46*k,j*50,83+46*k,j*50+50,1);
	  for(j=0;j<16;j++)
	    {
	      SciSci(71.5+46*k,400+j*25,84.5+46*k,j*25+425,1);
	      ParSci(50+46*k,0,60+46*k,1200,1);
	    }
	}
      for(j=0;j<17;j++)
	  VetoSci(-15.5+50*j,-60,34.5+50*j,-50,1);
      for(j=0;j<17;j++)
	  VetoSci(-15.5+50*j,1250,34.5+50*j,1260,1);
    }

}

void MakeDetDisp::DrawWAGASCI(int mod, int view)
{

  WaterTank(mod+5, view);

  if(mod==1 && view==0)
    for(int pln=0; pln<24; pln++)
      {
	if(pln%3==1 || pln%3==2) nch = 20;
	if(pln%3==0) nch = 40;
	
	for(int ch=0; ch<nch; ch++)
	  {
	    fdimension->get_wgdet_pos(mod, view, pln, ch, &tempz, &tempxy);
	    if(pln%3==1 || pln%3==2)
	      {
		GridSci(mod, view, tempxy, tempz);
	      }
	    if(pln%3==0)
	      {
		PlnSci(mod, view, tempxy, tempz);
	      }
	  }
      }

  if(mod==1 && view==1)
    for(int pln=0; pln<24; pln++)
      {
	if(pln%3==0 || pln%3==2) nch = 20;
	if(pln%3==1) nch = 40;
	
	for(int ch=0; ch<nch; ch++)
	  {
	    fdimension->get_wgdet_pos(mod, view, pln, ch, &tempz, &tempxy);
	    if(pln%3==0 || pln%3==2)
	      {
		GridSci(mod, view, tempxy, tempz);
	      }
	    if(pln%3==1)
	      {
		PlnSci(mod, view, tempxy, tempz);
	      }
	  }
      }

  if(mod==2 && view==0)
    for(int pln=0; pln<24; pln++)
      {
	if(pln%3==1 || pln%3==2) nch = 20;
	if(pln%3==0) nch = 40;
	
	for(int ch=0; ch<nch; ch++)
	  {
	    fdimension->get_wgdet_pos(mod, view, pln, ch, &tempz, &tempxy);
	    if(pln%3==1 || pln%3==2)
	      {
		GridSci(mod, view, tempxy, tempz);
	      }
	    if(pln%3==0)
	      {
		PlnSci(mod, view, tempxy, tempz);
	      }
	  }
      }

  if(mod==2 && view==1)
    for(int pln=0; pln<24; pln++)
      {
	if(pln%3==0 || pln%3==2) nch = 20;
	if(pln%3==1) nch = 40;
	
	for(int ch=0; ch<nch; ch++)
	  {
	    fdimension->get_wgdet_pos(mod, view, pln, ch, &tempz, &tempxy);
	    if(pln%3==0 || pln%3==2)
	      {
		GridSci(mod, view, tempxy, tempz);
	      }
	    if(pln%3==1)
	      {
		PlnSci(mod, view, tempxy, tempz);
	      }
	  }
      }

}

void MakeDetDisp::DrawWallMRD(int mod)
{
  double centerz[8]={100, 300, 500, 700, 900, 1100, 1300, 1500};
  double centerx[10]={36.5, 79.5, 122.5, 165.5, 208.5, 251.5, 294.5, 337.5, 380.5, 423.5};
  double zwidth = 100;
  double xwidth = 7;
  double ironoffset = 20;

  for(int iz=0; iz<8; iz++)
    for(int ix=0; ix<10; ix++)
      {
	SciModule(mod, centerz[iz]-zwidth, centerx[ix]-xwidth, centerz[iz]+zwidth, centerx[ix]+xwidth);
	IronModule(mod, centerz[iz]-zwidth+ironoffset, centerx[ix]-xwidth+ironoffset,
		   centerz[iz]+zwidth+ironoffset, centerx[ix]+xwidth+ironoffset);
      }
  


}




