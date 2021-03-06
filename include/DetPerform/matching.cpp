#include <iostream>
#include <fstream>
#include <vector>

#include "matching.hpp"

using namespace std;
//#define debug
#define MC
//#define beam
Matching::Matching()
{
  fdimension = new Dimension();

#ifdef beam
  posfinalpln[0][0] = 814;
#endif

#ifdef MC
  posfinalpln[0][0] = 786;
#endif
  moddisttobm[0][0] = 1200;

#ifdef beam
  posfinalpln[0][1] = 791;
#endif
#ifdef MC
  posfinalpln[0][1] = 809;
#endif
  moddisttobm[0][1] = 1200;

  epsilon = 5;

  linear = new TF1("linear", "[0]+[1]*x", 0, 1000);
  linear->SetParameters(0, 0);

  dist[0] = 400;
  dist[1] = 500;
}

Matching::~Matching()
{
}

bool Matching::JudgePenetrate(int mod, int view, double finalpos)
{
  bool penetrate = false;
  if(fabs(finalpos-posfinalpln[mod][view]) < epsilon)
    penetrate = true;
     
  return penetrate;
}


void Matching::CalcSlope(int mod, int view, double posz[], double posxy[])
{
  double dposz[1000], dposxy[1000];
  int nhit = 0;

  for(int ihit=0; ihit<1000; ihit++)
    {
      if(posz[ihit]>=-1000 && posxy[ihit]>=-1000)
	{
	  dposz[nhit] = posz[ihit];
	  dposxy[nhit] = posxy[ihit];
	  nhit++;
	}
    }
  
  fitgraph[mod][view] = new TGraph(nhit, dposz, dposxy);
  fitgraph[mod][view]->SetMarkerStyle(21);
  fitgraph[mod][view]->Fit(linear, "Q");
  //fitgraph[mod][view]->Draw("AP");

  slope[mod][view] = linear->GetParameter(1);
  intercept[mod][view] = linear->GetParameter(0);
  cout << "slope= " << slope[mod][view] << " intercept= " << intercept[mod][view]   <<  '\n';
}

void Matching::Extrapolation(int mod, int view, double finalposxy, double* extrapolatexy)
{
  double estimation;
  double delta;
  delta = moddisttobm[mod][view]*slope[mod][view];
  estimation = finalposxy + delta;

  *extrapolatexy = estimation + fdimension->offset[view][1][mod];
}

bool Matching::InBM(int mod, int view, double extrapolatexy)
{
  bool inbm = false;

  if(view==0)
    if(extrapolatexy < 600 && extrapolatexy >=-600)
    //if(extrapolatexy < 980 && extrapolatexy > -980)
      inbm = true;

  if(view==1)
    if(extrapolatexy < 700 && extrapolatexy >=-700)
    //if(extrapolatexy < 1350 && extrapolatexy > -1350)
      inbm = true;
 
  return inbm;
}

bool Matching::Matchingbm(int view, int itrack, double extrapolatexy, double posz[], double posxy[])
{
  bool matching = false;
  aveposxy[view][itrack]=0;

  int count=0;

  //cout << "view= " << view << " itrack= " << itrack << " start" << '\n';

  if(view==0)
    for(int ihit=0; ihit<1000; ihit++)
      {
	if(posz[ihit]!=-9999)
	  //cout << "posz= " << posz[ihit] << '\n';
	if(posz[ihit] <= 300 && posz[ihit]>=-1000)
	  {
	    aveposxy[view][itrack] += posxy[ihit];
	    count++;
	  }
      }

  if(view==1)
    for(int ihit=0; ihit<1000; ihit++)
      {
	if(posz[ihit]!=-9999)
	  //cout << "posz= " << posz[ihit] << '\n';
	if(posz[ihit] <= 500 && posz[ihit]>=-1000)
	  {
	    aveposxy[view][itrack] += posxy[ihit];
	    count++;
	  }
      }

  aveposxy[view][itrack] = aveposxy[view][itrack]/(double)count;

  //cout << "aveposxy= " << aveposxy[view][itrack] << '\n';
  
  if(fabs(aveposxy[view][itrack]-extrapolatexy)<dist[view])
    matching = true;

  cout << "aveposxy= " << aveposxy[view][itrack] << " extrapolatexy= " << extrapolatexy << " matching= " << matching  << '\n';

  return matching;
}

bool Matching::SearchMatchHit(int view, int bunch, double extrapolatexy, vector<double>posz, vector<double>posxy)
{
  bool matchinghit = false;

  vector<int> starthits;
  starthits.clear();
  for(int ihit=0; ihit<posz.size(); ihit++)
    {
      double xypos = posxy.at(ihit);
      double zpos = posz.at(ihit);

      if(zpos<=100)
	{
	  starthits.push_back(xypos);
	  //cout << "xypos= " << xypos << '\n';
	}
    }

  for(int i=0; i<starthits.size(); i++)
    {
      if(fabs(starthits.at(i) - extrapolatexy)<350)
	matchinghit = true;

      //cout << "shits= " << starthits.at(i) << " extrapolate= " << extrapolatexy << '\n';
    }

  return matchinghit;
}
