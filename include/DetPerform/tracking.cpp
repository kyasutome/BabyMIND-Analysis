#include <iostream>
#include <fstream>
#include <vector>

#include "tracking.hpp"

using namespace std;
//#define debug

Tracking::Tracking()
{
  
  //Proton Module
  minfvz[0][0] = -300-800;
  minfvz[0][1] = -300-800;
  maxfvz[0][0] = 200-800;
  maxfvz[0][1] = 200-800;
  
  minfvxy[0][0] = -500-350;
  minfvxy[0][1] = -500-350;
  maxfvxy[0][0] = 500-350;
  maxfvxy[0][1] = 500-350;


  //BabyMIND
  minfcz[5][0] = 1500;
  minfcz[5][1] = 1500;
  maxfcz[5][0] = 3700;
  maxfcz[5][1] = 3700;
  
  minfcxy[5][0] = -700;
  minfcxy[5][1] = -1000+450;
  maxfcxy[5][0] = 700;
  maxfcxy[5][1] = 1000+450;

  
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
    if(posxy>minfcxy[mod][view] && posxy<maxfcxy[mod][view])	
      fccut = true;

  if(mod==5)
    if(posz>=4000)
      if(posxy>minfcxy[mod][view]-1000 && posxy<maxfcxy[mod][view]+1000)
	fccut = true;
    

  return fccut;

}
