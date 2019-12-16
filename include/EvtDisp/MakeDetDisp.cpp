#include <iostream>
#include <fstream>
#include <vector>

#include "MakeDetDisp.hpp"

using namespace std;

MakeDetDisp::MakeDetDisp()
{
}

MakeDetDisp::~MakeDetDisp()
{
}

void MakeDetDisp::DetModule(double x1, double y1, double x2, double y2)
{
  TBox *b1 = new TBox(x1, y1, x2, y2);
  Int_t trans_blue = TColor::GetColorTransparent(kBlue, 0.6);
  b1->SetLineColor(1);
  b1->SetFillColor(trans_blue);
  b1->SetLineWidth(3);
  b1->SetFillStyle(1001);
  b1->Draw("SAME");
}

void MakeDetDisp::MagModule(double x1, double y1, double x2, double y2){
  TBox *b1 = new TBox(x1, y1, x2, y2);
  Int_t trans_orange = TColor::GetColorTransparent(kOrange, 0.6);
  b1->SetLineColor(trans_orange);
  b1->SetFillColor(trans_orange);
  b1->SetLineWidth(2);
  b1->SetFillStyle(1001);
  b1->Draw("SAME");
}

void MakeDetDisp::YASUModule(double x1, double y1, double x2, double y2){
  TBox *b1 = new TBox(x1, y1, x2, y2);
  Int_t trans_green = TColor::GetColorTransparent(kGreen, 0.6);
  b1->SetLineColor(1);
  b1->SetFillColor(trans_green);
  b1->SetLineWidth(3);
  b1->SetFillStyle(1001);
  b1->Draw("SAME");
}


void MakeDetDisp::IngSci(double x,double y,double x1,double y1,int view){

  double offsetx = -2000;
  double offsety;

  if(view==0)  offsety= -550;
  if(view==1)  offsety= -1050;

  TBox *b1=new TBox(x+offsetx,y+offsety,x1+offsetx,y1+offsety);
  b1->SetLineColor(kGreen);
  b1->SetLineWidth(2);
  b1->SetFillStyle(0);
  b1->Draw("SAME");
}


void MakeDetDisp::ParSci(double x,double y,double x1,double y1,int view){

  double offsetx = -2000;
  double offsety;

  if(view==0)  offsety= -550;
  if(view==1)  offsety= -1050;

  TBox *b1=new TBox(x+offsetx,y+offsety,x1+offsetx,y1+offsety);
  b1->SetLineColor(kYellow);
  b1->SetLineWidth(2);
  b1->SetFillStyle(0);
  b1->Draw("SAME");
}

void MakeDetDisp::SciSci(double x,double y,double x1,double y1,int view){

  double offsetx = -2000;
  double offsety;

  if(view==0)  offsety= -550;
  if(view==1)  offsety= -1050;

  TBox *b1=new TBox(x+offsetx,y+offsety,x1+offsetx,y1+offsety);
  b1->SetLineColor(kGreen+2);
  b1->SetLineWidth(2);
  b1->SetFillStyle(0);
  b1->Draw("SAME");
}

void MakeDetDisp::VetoSci(double x,double y,double x1,double y1, int view){

  double offsetx = -2000;
  double offsety;

  if(view==0)  offsety= -550;
  if(view==1)  offsety= -1050;

  TBox *b1=new TBox(x+offsetx,y+offsety,x1+offsetx,y1+offsety);

  b1->SetLineColor(kBlue);
  b1->SetLineWidth(2);
  b1->SetFillStyle(0);
  b1->Draw("SAME");
}

void MakeDetDisp::DrawBabyMIND(int view)
{
  double Scin_thickness = 40; //cm                                                                                   
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
	      dhorl[i/2] = dimension->sciposy[i]-15;
	      uhorl[i/2] = dimension->sciposy[i]+15;
	    }
	  if(i%2==1)
	    {
	      dhorr[i/2] = dimension->sciposy[i]-15;
	      uhorr[i/2] = dimension->sciposy[i]+15;
	    }
	}

      for(int i=0; i<NUMBEROFMODULE; i++)
	{
	  for(int j=0; j<48; j++)
	    DetModule(dimension->sciposz[i]-10, dhorl[j], dimension->sciposz[i], uhorl[j]);
	  for(int j=0; j<47; j++)
	    DetModule(dimension->sciposz[i], dhorr[j], dimension->sciposz[i]+10, uhorr[j]);
	}
	  
      for(int i=0; i<33; i++)
	MagModule(dimension->ironposz[i]-Iron_thickness/2-130, -986.2, 
		  dimension->ironposz[i]+Iron_thickness/2-130, 986.2);


      //YASU Trackers
      for(int i=0; i<14; i++)
	{
	  YASUModule(dimension->yasuposz[0][i]-YASU_thick/2.,dimension->yasuposy[0][i]-YASU_height/2.,
		     dimension->yasuposz[0][i]+YASU_thick/2.,dimension->yasuposy[0][i]+YASU_height/2.);
	}      
    }//view==0

  if(view==1)
    {
      for(int i=0; i<16; i++)
	{
	  if(i%2==0)
	    {
	      dverl[i/2] = dimension->sciposx[i]-100;
	      uverl[i/2] = dimension->sciposx[i]+100;
	    }
	  if(i%2==1)
	    {
	      dverr[i/2] = dimension->sciposx[i]-100;
	      uverr[i/2] = dimension->sciposx[i]+100;
	    }
	}

      for(int i=0; i<18; i++)
	{
	  for(int j=0; j<8; j++)
	    DetModule(dimension->sciposz[i]-20, dverl[j], dimension->sciposz[i]-10, uverl[j]);
	  for(int j=0; j<8; j++)
	    DetModule(dimension->sciposz[i]+10, dverr[j], dimension->sciposz[i]+20, uverr[j]);
	}

      for(int i=0; i<33; i++)
	MagModule(dimension->ironposz[i]-Iron_thickness/2-130, -1750, 
		  dimension->ironposz[i]+Iron_thickness/2-130, 1750);

      YASUModule(dimension->yasuposz[0][0]-YASU_thick/2.,dimension->yasuposx[0][0]-YASU_width/2.,
		 dimension->yasuposz[0][0]+YASU_thick/2.,dimension->yasuposx[0][0]+YASU_width/2.);

      YASUModule(dimension->yasuposz[0][0]-YASU_thick/2.,dimension->yasuposx[1][0]-YASU_width/2.,
		 dimension->yasuposz[0][0]+YASU_thick/2.,dimension->yasuposx[1][0]+YASU_width/2.);

      YASUModule(dimension->yasuposz[0][7]-YASU_thick/2.,dimension->yasuposx[0][0]-YASU_width/2.,
		 dimension->yasuposz[0][7]+YASU_thick/2.,dimension->yasuposx[0][0]+YASU_width/2.);

      YASUModule(dimension->yasuposz[0][7]-YASU_thick/2.,dimension->yasuposx[1][0]-YASU_width/2.,
		 dimension->yasuposz[0][7]+YASU_thick/2.,dimension->yasuposx[1][0]+YASU_width/2.);

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






