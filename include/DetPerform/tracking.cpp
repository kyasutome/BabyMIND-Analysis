#include <iostream>
#include <fstream>
#include <vector>

#include "tracking.hpp"
#include "matching.cpp"

using namespace std;
//#define debug
//#define chargeID

Tracking::Tracking()
{  
  //Proton Module
  minfvz[0][0] = -300-800;
  minfvz[0][1] = -300-800;
  maxfvz[0][0] = 100-800;
  maxfvz[0][1] = 100-800;
  
  minfvxy[0][0] = -400;
  minfvxy[0][1] = -400-350;
  maxfvxy[0][0] = 400;
  maxfvxy[0][1] = 400-350;

  moduleboxz[0] = 800;
  moduleboxx[0] = 1200;
  moduleboxy[0] = 1200;

  //BabyMIND

  minfvz[5][0] = 300;
  minfvz[5][1] = 300;
  maxfvz[5][0] = 900;
  maxfvz[5][1] = 900;
  
  minfvxy[5][0] = -500;
  minfvxy[5][1] = -800;
  maxfvxy[5][0] = 500;
  maxfvxy[5][1] = 800;

  minfcz[5][0] = 1500;
  minfcz[5][1] = 1500;
  maxfcz[5][0] = 3700;
  maxfcz[5][1] = 3700;
  
  minfcxy[5][0] = -700;
  minfcxy[5][1] = -1000+450;
  maxfcxy[5][0] = 700;
  maxfcxy[5][1] = 1000+450;

  for(int itrack=0; itrack<20; itrack++)
    {
      linear[itrack]=new TF1(Form("linear%d",itrack), "[0]+[1]*x", 0, 800);
    }

}

Tracking::~Tracking()
{
}

void Tracking::SearchParticle(int pdg, MCTrue* mctrue, vector<int>* particlelist)
{
  for(int ipar=0; ipar<20; ipar++)
    {
      if(mctrue->pdg[ipar]!=pdg)
	continue;

      if(mctrue->pdg[ipar]==pdg)
	particlelist->push_back(ipar);
    }
  
}

bool Tracking::FVcut(int mod, int view, double posz, double posxy)
{
  bool fvcut = false;

  if(posz>minfvz[mod][view] && posz<maxfvz[mod][view])
    if(posxy>minfvxy[mod][view] && posz<maxfvxy[mod][view])	
      fvcut = true;

  return fvcut;

}

bool Tracking::FCcut(int mod, int view, double posz, double posxy)
{
  bool fccut = false;
  
  if(posz>minfcz[mod][view] && posz<maxfcz[mod][view])
    if(posxy<=minfcxy[mod][view] || posxy>=maxfcxy[mod][view])	
      fccut = true;


#ifdef chargeID
  if(mod==5)
    if(posz>=4000)
      if(posxy>minfcxy[mod][view]-1000 && posxy<maxfcxy[mod][view]+1000)
	fccut = true; 
#endif
    

  return fccut;

}

void Tracking::SearchNuVertex(int mod, int view, int ntrack,  
			      vector<double> posz[], vector<double> posxy[], double estimatevertex[])
{

  Matching* matching = new Matching();

  vector<double> positionz[20], positionxy[20];
  vector<double> spositionz[20];
  double aveposz, aveposxy;
  aveposz=0;
  aveposxy=0;
  int count=0;

  double reconposz[20][1000], reconposxy[20][1000];

  for(int itrack=0; itrack<20; itrack++)
    {
      positionz[itrack].clear();
      positionxy[itrack].clear();
      spositionz[itrack].clear();

      for(int ihit=0; ihit<1000; ihit++)
	{
	  Nhit[itrack] = posz[itrack].size();
	  if(ihit<posz[itrack].size())
	    {
	      reconposz[itrack][ihit] = posz[itrack].at(ihit);
	      reconposxy[itrack][ihit] = posxy[itrack].at(ihit);
	      cout << "itrack= " << itrack  << " posz= " << posz[itrack].at(ihit) << " posxy= " << posxy[itrack].at(ihit) << '\n';
	      graphz[itrack][ihit] = posz[itrack].at(ihit);
	      graphxy[itrack][ihit] = posxy[itrack].at(ihit);
	    }

	  if(ihit>=posz[itrack].size())
	    {
	      reconposz[itrack][ihit] = -9999;
	      reconposxy[itrack][ihit] = -9999;
	      graphz[itrack][ihit] = -9999;
	      graphxy[itrack][ihit] = -9999;
	    }	  
	}//ihit
    }//itrack

  cout << "ntrack= " << ntrack << '\n';

  if(ntrack==1)
    {
      for(int ihit=0; ihit<posz[0].size(); ihit++)
	{
	  positionz[0].push_back(posz[0].at(ihit));
	  positionxy[0].push_back(posxy[0].at(ihit));
	  spositionz[0].push_back(posz[0].at(ihit));
	}//ihit
            
      std::sort(spositionz[0].begin(), spositionz[0].end());
      auto last = unique(spositionz[0].begin(), spositionz[0].end());      
      spositionz[0].erase(last, spositionz[0].end());
      cout << "minimum= " << spositionz[0].at(0) << '\n';

      matching->CalcSlope(0, view, reconposz[0], reconposxy[0]);
      double Slope = matching->slope[0][view];
      double Intercept = matching->intercept[0][view];

      aveposz = spositionz[0].at(0);
      aveposxy = Slope*aveposz+Intercept;
            
      /*
      for(int ihit=0; ihit<posz[0].size(); ihit++)
	{
	  if(posz[0].at(ihit)==spositionz[0].at(0))
	    {
	      aveposxy += posxy[0].at(ihit);
	      count++;
	    }
	}//ihit
      aveposxy = aveposxy/(double)count;
      aveposz = spositionz[0].at(0);
      */     

      estimatevertex[0] = aveposz;
      estimatevertex[1] = aveposxy;
      
      //cout << estimatevertex[0] << " " << estimatevertex[1] << '\n';

    }//ntrack==1

  else if(ntrack==2)
    {
      for(int itrack=0; itrack<ntrack; itrack++)
	{
	  matching->CalcSlope(0, view, reconposz[itrack], reconposxy[itrack]);
	  slope[itrack] = matching->slope[0][view];
	  intercept[itrack] = matching->intercept[0][view];
	}
      
      if(fabs(slope[0]-slope[1]) < 0.01)
	{
	  for(int ihit=0; ihit<posz[0].size(); ihit++)
	    {
	      positionz[0].push_back(posz[0].at(ihit));
	      positionxy[0].push_back(posxy[0].at(ihit));
	      spositionz[0].push_back(posz[0].at(ihit));
	    }//ihit
	  
	  std::sort(spositionz[0].begin(), spositionz[0].end());
	  auto last = unique(spositionz[0].begin(), spositionz[0].end());
	  spositionz[0].erase(spositionz[0].end(), last);
	  cout << "minimum= " << spositionz[0].at(0) << '\n'; 
	  
	  for(int ihit=0; ihit<posz[0].size(); ihit++)
	    {
	      if(posz[0].at(ihit)==spositionz[0].at(0))
		{
		  aveposxy += posxy[0].at(ihit);
		}
	    }//ihit
	  
	  aveposxy = aveposxy/(double)posxy[0].size();
	  aveposz = spositionz[0].at(0);
	  
	  estimatevertex[0] = aveposz;
	  if(view==1)
	    estimatevertex[1] = aveposxy;
	  if(view==0)
	    estimatevertex[1] = aveposxy;
	 
	}//slope condition

      else if(fabs(slope[0]-slope[1])>=0.01)
	{
	  estimatevertex[0] = (intercept[1]-intercept[0])/(slope[0]-slope[1]);
	  aveposxy = (slope[0]*intercept[1]-slope[1]*intercept[0])/(slope[0]-slope[1]);
	  if(view==1)
	    estimatevertex[1] = aveposxy;
	  if(view==0)
	    estimatevertex[1] = aveposxy;	  
	}//slope condition
    }//ntrack==2

  else if(ntrack>=3)
    {
      for(int itrack=0; itrack<ntrack; itrack++)
	{
	  matching->CalcSlope(0, view, reconposz[itrack], reconposxy[itrack]);
	  slope[itrack] = matching->slope[0][view];
	  intercept[itrack] = matching->intercept[0][view];	  
	}

      SearchIntersection(0, view, ntrack, slope, intercept);
      SetDisplay(view, ntrack);

      estimatevertex[0] = intersection[0];
      estimatevertex[1] = intersection[1];

    }//ntrack>=3
   
}

void Tracking::SearchIntersection(int mod, int view, int ntrack, double slope[], double intercept[])
{
  double dxy, dz;
  double optxy, optz;
  double K = 100;
  double mindistance = 99999;

  if(view==0)
    dxy = moduleboxy[mod]/K;
  if(view==1)
    dxy = moduleboxx[mod]/K;

  dz = moduleboxz[mod]/K;

  for(int iz=0; iz<K; iz++)
    for(int ixy=0; ixy<K; ixy++)
      {
	double thexy = ixy*dxy;
	double thez = iz*dz;
	double distance = 0;

	for(int itrack=0; itrack<ntrack; itrack++)
	  {
	    distance += CalcDist(thexy, thez, slope[itrack], intercept[itrack]);
	  }

	if(distance < mindistance)
	  {
	    mindistance = distance;
	    optxy = thexy;
	    optz = thez;
	    //cout << "xy= " << optxy  << " z= " << optz << '\n';
	  }
      }
  
  //cout << "mindistance= " << mindistance << '\n';
  cout << "xy= " << optxy  << " z= " << optz << '\n';
  intersection[0] = optz;
  intersection[1] = optxy;
 
}

double Tracking::CalcDist(double thexy, double thez, double slope, double intercept)
{
  double dist;
  dist = fabs(slope*thez-1*thexy+intercept)/sqrt(slope*slope+1);

  return dist;
}

void Tracking::SetDisplay(int view, int ntrack)
{
  for(int itrack=0; itrack<ntrack; itrack++)
    {
      linear[itrack]->SetParameters(intercept[itrack], slope[itrack]);      
      reconfit[itrack] = new TGraph(Nhit[itrack], graphz[itrack], graphxy[itrack]);
      reconfit[itrack]->SetMarkerStyle(20);
      reconfit[itrack]->SetMarkerColor(2+itrack);
      reconfit[itrack]->SetMaximum(1200);
      reconfit[itrack]->SetMinimum(0);
    }

  optpoint = new TArc(intersection[0],intersection[1],10);
  optpoint->SetFillColor(7);
  optpoint->SetLineColor(5);  

}

double Tracking::CalcdE(double initpos, double angle)
{
  double totalloss;
  double moduleloss[2];
  double mipdE = 2; //MeV/cm

  double protonlen = 2; //cm/layer
  double wagascilen = 50; //cm/module

  double minz[17], maxz[17];
  int thelayer, thenumberofrest;
  for(int i=0; i<17; i++)
    {
      minz[i] = 50+i*46-23;
      maxz[i] = 50+i*46+23;

      if(initpos>=minz[i] && initpos<maxz[i])
	{
	  thelayer = i;
	  break;
	}
    }

  cout << "thelayer= " << thelayer << '\n';
  thenumberofrest = 16-thelayer;
  moduleloss[0] = protonlen*thenumberofrest*mipdE/angle;
  moduleloss[1] = wagascilen*mipdE/angle;

  cout << "moduleloss[0]= " << moduleloss[0] << " moduleloss[1]= " << moduleloss[1] << '\n';
  
  totalloss = moduleloss[0]+moduleloss[1];
  return totalloss;
}
