#include <iostream>
#include <stdio.h>

#include "yasutomethod.hpp"

using namespace std;

//#define debug
Yasutomethod::Yasutomethod()
{ 
  for(int i=0; i<2; i++)
    {
      recontrack[i].clear();
      {
	for(int j=0; j<20; j++)
	  {
	    hitpln[i][j].clear();
	    hitclpln[i][j].clear();
	  }
      }
    }
  for(int i=0; i<Ntrack; i++)
    track[i].clear();
  
  ReconTrack.clear();
  temp.clear();

for(int i=0; i<1000; i++)
  {
    bmhit[i] = new BMHitCluster();
    bmclhit[i] = new BMHitCluster();
  }

 recondisp = new TH2D("recondisp", "recondisp", 18, 0, 18, 100, 0, 100);
  
}


Yasutomethod::~Yasutomethod()
{
}

void Yasutomethod::ystmethod(BMDisp* bmdisp, BMCluster* bmcluster[100])
{
  Clear();
  for(int ihit=0; ihit<bmdisp->mod.size(); ihit++)
    {
      mod = bmdisp->mod.at(ihit);
      view = bmdisp->view.at(ihit);
      pln = bmdisp->pln.at(ihit);
      channel = bmdisp->channel.at(ihit);
      htime = bmdisp->Htime.at(ihit);

      bmhit[ihit]->mod = mod;
      bmhit[ihit]->view = view;
      bmhit[ihit]->pln = pln;
      bmhit[ihit]->channel = channel;
      bmhit[ihit]->Htime = htime;

      if(mod==5)
	hitpln[view][pln].push_back(bmhit[ihit]);
    }

  Clustering(hitpln, hitclpln);

  for(int i_can=0; i_can<hitclpln[0][firstpln].size(); i_can++)
    {
      cutflag = false;
      temp.clear();
      temp.push_back(firstpln);
      temp.push_back(hitclpln[0][firstpln].at(i_can)->channel);
      temp.push_back(hitclpln[0][firstpln].at(i_can)->Htime);
      track[i_can].push_back(temp);

      for(int i_layer=1+firstpln; i_layer<=18; i_layer++)
	{
	  cont = false;
	  temp.clear();
	  if(!cutflag)
	      center = track[i_can].at(prelayer).at(1);
 
	  if(cutflag)
	    {
	      tempz_pre = track[i_can].at(prelayer).at(0);
	      tempy_pre = track[i_can].at(prelayer).at(1);
	      if(prelayer>=1)
		{
		  double tempz_prepre = track[i_can].at(prelayer-1).at(0);
		  double tempy_prepre = track[i_can].at(prelayer-1).at(1);
		  center = tempy_pre + (double)(tempy_pre-tempy_prepre)/(double)(tempz_pre-tempz_prepre)*count_non;
		}

	      if(prelayer==0)
		{
		  center = tempy_pre;
		  cut = cut_default*count_non;
		}

	    }

	  for(int i_data=0; i_data<hitclpln[0][i_layer].size(); i_data++)
	    {
	      double tryy = hitclpln[0][i_layer].at(i_data)->channel;
	      cluster_time = hitclpln[0][i_layer].at(i_data)->Htime;
	      
	      if(fabs(tryy-center)<cut)
		{
		  temp.push_back(i_layer);
		  temp.push_back(tryy);
		  cont = true;
		}
	    }

	  if(cont)
	    {
	      double cluster_value = temp.at(1);
	      findflag = false;
	      if(track[i_can].size()<=1)
		{
		  cluster_value = temp.at(1);
		  for(int i_cluster=0; i_cluster<temp.size()/2; i_cluster++)
		    {
		      double trydif = fabs(temp.at(2*i_cluster+1)-center);
		      double refdif = fabs(cluster_value-center);
		      if(trydif <= refdif)
			{
			  findflag = true;
			  cluster_value = temp.at(2*i_cluster+1);
			}
		    }
		}

	      if(track[i_can].size()>=2)
		{

		  int n = track[i_can].size();
		  double prey = track[i_can].at(n-1).at(1);
		  double preprey = track[i_can].at(n-2).at(1);
		  double prez = track[i_can].at(n-1).at(0);
		  double preprez = track[i_can].at(n-2).at(0);

		  double slope = (preprey-prey)/(preprez-prez);
		  double estimation = (i_layer-prez)*slope + prey;

		  for(int i_cluster=0; i_cluster<temp.size()/2; i_cluster++)
		    {
		      double trydif = fabs(temp.at(2*i_cluster+1)-estimation);
		      double refdif = fabs(cluster_value-estimation);
		      if(trydif <= refdif && trydif < cut)
			{
			  findflag = true;
			  cluster_value = temp.at(2*i_cluster+1);
			}
		    }
		}

	      if(!findflag)
		{
		  goto next;
		}

	      temp.clear();
	      temp.push_back(i_layer);
	      temp.push_back(cluster_value);
	      temp.push_back(cluster_time);
	      track[i_can].push_back(temp);
	      
	      cutflag = false;
	      prelayer = i_layer - (firstpln) - count_non_total;
	      count_non = 0;
	    }//cont

	  if(!cont)
	    {
	    next:
	      count_non++;
	      count_non_total++;
	      prelayer = i_layer - (firstpln)  - count_non_total;
	      cutflag = true;
	      if(count_non!=2) continue;
	      if(count_non==2) break;
	    }

	  cut = cut_default;
	  
	}//i_layer

      count_non = 0;
      count_non_total = 0;
      prelayer = 0;
      cut = cut_default;

    }//i_can
      
  //ChooseTrack(track, &ReconTrack);

  for(int itrack=0; itrack<hitclpln[0][firstpln].size(); itrack++)
    for(int i=0; i<track[itrack].size(); i++)
      {
	bmcluster[itrack]->mod.push_back(5);
	bmcluster[itrack]->view.push_back(0);
	bmcluster[itrack]->pln.push_back(track[itrack].at(i).at(0));
	bmcluster[itrack]->channel.push_back(track[itrack].at(i).at(1));
	bmcluster[itrack]->Htime.push_back(track[itrack].at(i).at(2));
	recondisp->Fill(track[itrack].at(i).at(0), track[itrack].at(i).at(1));
      }

  
#ifdef debug
  for(int ipln=0; ipln<20; ipln++)
    for(int ihit=0; ihit<hitclpln[0][ipln].size(); ihit++)
      cout << "ipln=" << ipln << " ch=" << hitclpln[0][ipln].at(ihit)->channel << '\n';

  cout << "track candidates" << '\n';
  for(int itrack=0; itrack<3; itrack++)
    for(int ipln=0; ipln<track[itrack].size(); ipln++)
      {
	cout << "pln= " << ipln << " channel= " << track[itrack].at(ipln).at(1) << '\n'; 
      }

  cout << "longest track" << '\n';
  for(int ipln=0; ipln<ReconTrack.size(); ipln++)
    cout << "pln= " << ipln << " channel= " << ReconTrack.at(ipln).at(1) << '\n'; 
  
#endif

}

void Yasutomethod::Clustering(vector<BMHitCluster*> hitpln[2][20], vector<BMHitCluster*> hitclpln[2][20])
{
  bool clusterflag = false;
  int refch, trych;
  double ave;
  icount=0;
  
  for(int ipln=0; ipln<20; ipln++)
    if(hitpln[0][ipln].size()>=1)
      for(int i=0; i<hitpln[0][ipln].size(); i++)
	{
	  clusterflag = false;
	  bmclhit[icount]->mod = hitpln[0][ipln].at(i)->mod;
	  bmclhit[icount]->view = hitpln[0][ipln].at(i)->view;
	  bmclhit[icount]->pln = hitpln[0][ipln].at(i)->pln;
	  bmclhit[icount]->Htime = hitpln[0][ipln].at(i)->Htime;

	  refch = hitpln[0][ipln].at(i)->channel;
	  for(int j=i+1; j<hitpln[0][ipln].size(); j++)
	    {
	      trych = hitpln[0][ipln].at(j)->channel;
	      if(fabs(trych-refch)<=1)
		{
		  ave = (refch+trych)/2.;
		  bmclhit[icount]->channel = ave;
		  hitclpln[0][ipln].push_back(bmclhit[icount]);
		  clusterflag = true; 
		  i=j;
		  icount++;
		  break;
		}
	    }
	  if(!clusterflag)
	    {
	      bmclhit[icount]->channel = refch;
	      hitclpln[0][ipln].push_back(bmclhit[icount]);
	      icount++;
	    }
	}
}

void Yasutomethod::ChooseTrack(vector<vector<double> >track[], vector<vector<double> >*ReconTrack)
{
  int id = 0;
  
  for(int i=1; i<10; i++)
    {
      if(track[i].size()<=2)
	continue;
      
      if(track[i].size() > track[id].size())
	id = i;
      if(track[i].size() == track[id].size())
        {
          double diftry = fabs(track[i].at(0).at(1) - track[i].at(1).at(1));
          double difref = fabs(track[id].at(0).at(1) - track[id].at(1).at(1));
          if(diftry < difref)
	    id = i;
        }
    }
  
  int N=track[id].size();
  
  for(int i=0; i<N; i++)
    {
      vector <double> temp;
      temp.clear();
      temp.push_back(track[id].at(i).at(0));
      temp.push_back(track[id].at(i).at(1));
      temp.push_back(track[id].at(i).at(2));
      ReconTrack->push_back(temp);
      recondisp->Fill(track[id].at(i).at(0), track[id].at(i).at(1));
    }
}

void Yasutomethod::Clear()
{
  for(int i=0; i<1000; i++)
    {
      bmhit[i]->Clear();
      bmclhit[i]->Clear();
    }  
  
  for(int i=0; i<2; i++)
    {
      recontrack[i].clear();
      {
	for(int j=0; j<20; j++)
	  {
	    hitpln[i][j].clear();
	    hitclpln[i][j].clear();
	  }
      }
    }
  for(int i=0; i<Ntrack; i++)
    track[i].clear();
  
  ReconTrack.clear();

}
