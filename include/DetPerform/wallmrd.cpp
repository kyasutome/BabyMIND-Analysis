#include <iostream>
#include <fstream>
#include <vector>

#include "wallmrd.hpp"

using namespace std;
//#define debug

WallMRD::WallMRD()
{

}

WallMRD::~WallMRD()
{
}

void WallMRD::Nhit(EVTCluster* evtcluster, int count[], int dif[])
{
  for(int i=0; i<2; i++)
    count[i]=0;

  for(int i=0; i<4; i++)
    {
      chip[i].clear();
      chan[i].clear();
      bunch[i].clear();
      posx[i].clear();
      posz[i].clear();
      dif[i]=0;
    }
  
  for(int ihit=0; ihit<evtcluster->mod.size(); ihit++)
    {
      if(evtcluster->mod.at(ihit)==3)
	{
	  count[0]++;
	  if(evtcluster->view.at(ihit)==0)
	    {
	      chip[0].push_back(evtcluster->pln.at(ihit));
	      chan[0].push_back(evtcluster->channel.at(ihit));
	      bunch[0].push_back(evtcluster->bunch.at(ihit));
	      posx[0].push_back(evtcluster->dposx.at(ihit));
	      posz[0].push_back(evtcluster->dposz.at(ihit));

	      dif[0]++;
	    }
	  if(evtcluster->view.at(ihit)==1)
	    {
	      chip[1].push_back(evtcluster->pln.at(ihit));
	      chan[1].push_back(evtcluster->channel.at(ihit));
	      bunch[1].push_back(evtcluster->bunch.at(ihit));
	      posx[1].push_back(evtcluster->dposx.at(ihit));
	      posz[1].push_back(evtcluster->dposz.at(ihit));

	      dif[1]++;
	    }
	}

      if(evtcluster->mod.at(ihit)==4)
	{
	  count[1]++;
	  if(evtcluster->view.at(ihit)==2)
	    {
	      chip[2].push_back(evtcluster->pln.at(ihit));
	      chan[2].push_back(evtcluster->channel.at(ihit));
	      bunch[2].push_back(evtcluster->bunch.at(ihit));
	      posx[2].push_back(evtcluster->dposx.at(ihit));
	      posz[2].push_back(evtcluster->dposz.at(ihit));

	      dif[2]++;
	    }
	  if(evtcluster->view.at(ihit)==3)
	    {
	      chip[3].push_back(evtcluster->pln.at(ihit));
	      chan[3].push_back(evtcluster->channel.at(ihit));
	      bunch[3].push_back(evtcluster->bunch.at(ihit));
	      posx[3].push_back(evtcluster->dposx.at(ihit));
	      posz[3].push_back(evtcluster->dposz.at(ihit));

	      dif[3]++;	  
	    }
	}
    }//ihit

#ifdef debug
  cout << "DIF0" << '\n';
  for(int ihit=0; ihit<chip[0].size(); ihit++)
    {
      cout << "chip:" << chip[0].at(ihit) << " chan:" << chan[0].at(ihit) << " bunch:" << bunch[0].at(ihit)
	   << " posx:" << posx[0].at(ihit) << " posz:" << posz[0].at(ihit) << '\n';
    }

  cout << "DIF1" << '\n';
  for(int ihit=0; ihit<chip[1].size(); ihit++)
    {
      cout << "chip:" << chip[1].at(ihit) << " chan:" << chan[1].at(ihit) << " bunch:" << bunch[1].at(ihit)
	   << " posx:" << posx[1].at(ihit) << " posz:" << posz[1].at(ihit) << '\n';
    }

  cout << "DIF2" << '\n';
  for(int ihit=0; ihit<chip[2].size(); ihit++)
    {
      cout << "chip:" << chip[2].at(0) << " chan:" << chan[2].at(0) << " bunch:" << bunch[2].at(ihit)
	   << " posx:" << posx[2].at(0) << " posz:" << posz[2].at(0) << '\n';
    }

  cout << "DIF3" << '\n';
  for(int ihit=0; ihit<chip[3].size(); ihit++)
    {
      cout << "chip:" << chip[3].at(0) << " chan:" << chan[3].at(0) << " bunch:" << bunch[3].at(ihit)
	   << " posx:" << posx[3].at(0) << " posz:" << posz[3].at(0) << '\n';
    }

#endif debug

}
