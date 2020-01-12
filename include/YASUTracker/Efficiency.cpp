#include <iostream>
#include <stdio.h>

#include "Efficiency.hpp"
#include "Calibration.hpp"

using namespace std;
//#define debug

Calibration* calibration = new Calibration();


Efficiency::Efficiency()
{ 
  for(int i=0; i<2; i++)
    for(int j=0; j<100; j++)
      timecluster[i][j] = new BMCluster();
 
  leadingtime.clear();
  plnstock.clear();
  yasucluster = new BMCluster();

  for(int i=0; i<2; i++)
    for(int j=0; j<2; j++)
      {
	totaldetectionefficiency[i][j] = 0;
	Ncount[i][j] = 0;
      }

  yasumip = new TH1D("yasumip", "yasumip", 200, 1, 4096);
  yasumip_pe = new TH1D("yasumip_pe", "yasumip_pe", 200, 1, 100);
}

Efficiency::~Efficiency()
{
}


void Efficiency::TimeClustering(BMBasicRecon* bmbasicrecon)
{
  Clear();
  for(int idata=0; idata<bmbasicrecon->mod.size(); idata++)
    {
      bool pushflag = false;
      mod = bmbasicrecon->mod.at(idata);
      view = bmbasicrecon->view.at(idata);
      pln = bmbasicrecon->pln.at(idata);
      channel = bmbasicrecon->channel.at(idata);
      htime = bmbasicrecon->Htime.at(idata);
      timedif = bmbasicrecon->timedif.at(idata);
      HG = bmbasicrecon->HG.at(idata);

      if(mod==5)
	{
	  for(int i=0; i<leadingtime.size(); i++)
	    {
	      if(fabs(htime-leadingtime.at(i)) <= 15)
		{
		  timecluster[view][i]->Htime.push_back(htime);
		  timecluster[view][i]->mod.push_back(mod);
		  timecluster[view][i]->view.push_back(view);
		  timecluster[view][i]->pln.push_back(pln);
		  timecluster[view][i]->channel.push_back(channel);
		  timecluster[view][i]->timedif.push_back(timedif);
		  timecluster[view][i]->HG.push_back(HG);
		  pushflag = true;
		}
	    }
	  
	  if(!pushflag)
	    {
	      leadingtime.push_back(htime);
	      timecluster[view][leadingtime.size()]->Htime.push_back(htime);
	      timecluster[view][leadingtime.size()]->mod.push_back(mod);
	      timecluster[view][leadingtime.size()]->view.push_back(view);
	      timecluster[view][leadingtime.size()]->pln.push_back(pln);
	      timecluster[view][leadingtime.size()]->channel.push_back(channel);
	      timecluster[view][leadingtime.size()]->timedif.push_back(timedif);
	      timecluster[view][leadingtime.size()]->HG.push_back(HG);
	    }
	}//mod==5

      if(mod==6)
	{
	  yasucluster->Htime.push_back(htime);
	  yasucluster->mod.push_back(mod);
	  yasucluster->view.push_back(view);
	  yasucluster->pln.push_back(pln);
	  yasucluster->channel.push_back(channel);
	  yasucluster->timedif.push_back(timedif);
	  yasucluster->HG.push_back(HG);
	}//mod==6
    }

      for(int icluster=0; icluster<leadingtime.size(); icluster++)
	{
	  bool firstcount[2]={false, false};
	  if(GetNpln(timecluster[0][icluster])>=15 && VectorFind(plnstock, 1)
	     && VectorFind(plnstock, 2))
	    {
	      LR=LeftRightModule(timecluster[1][icluster]);
	      if(LR==-1) continue;
	      Ncount[0][LR]++;
	      Ncount[1][LR]++;
	      for(int ihit=0; ihit<yasucluster->mod.size(); ihit++)
		{
		  if(fabs(yasucluster->Htime.at(ihit)-leadingtime.at(icluster)<=20) && !firstcount[0])
		    if(YASUplnSearch(yasucluster)==1 || YASUplnSearch(yasucluster)==11 )
		      {
			totaldetectionefficiency[0][LR]++;
			firstcount[0]=true;
			
			if(LR==0 && yasucluster->channel.at(ihit)<=6 && yasucluster->pln.at(ihit)==19)
			  {
			    yasumip->Fill(yasucluster->HG.at(ihit));
			    calibration->CalcGain(&gain);
			    yasumip_pe->Fill(yasucluster->HG.at(ihit)/gain);
			  }
			if(LR==1 && yasucluster->channel.at(ihit)>=7 && yasucluster->pln.at(ihit)==19)
			  {
			    yasumip->Fill(yasucluster->HG.at(ihit));
			    calibration->CalcGain(&gain);
			    yasumip_pe->Fill(yasucluster->HG.at(ihit)/gain);
			  }
		      }

		  if(fabs(yasucluster->Htime.at(ihit)-leadingtime.at(icluster)<=20) && !firstcount[1])
		    if(YASUplnSearch(yasucluster)==10 || YASUplnSearch(yasucluster)==11 )
		      {
			totaldetectionefficiency[1][LR]++;
			firstcount[1]=true;

			if(LR==0 && yasucluster->channel.at(ihit)<=6 && yasucluster->pln.at(ihit)==20)
			  {
			    yasumip->Fill(yasucluster->HG.at(ihit));
			    calibration->CalcGain(&gain);
			    yasumip_pe->Fill(yasucluster->HG.at(ihit)/gain);
			  }
			if(LR==1 && yasucluster->channel.at(ihit)>=7 && yasucluster->pln.at(ihit)==20)
			  {
			    yasumip->Fill(yasucluster->HG.at(ihit));
			    calibration->CalcGain(&gain);
			    yasumip_pe->Fill(yasucluster->HG.at(ihit)/gain);
			  }
		      }

		}
	      
#ifdef debug
	      cout << "top view" << '\n';
	      for(int ihit=0; ihit<timecluster[1][icluster]->pln.size(); ihit++)
		{
		  cout << "pln:" << timecluster[1][icluster]->pln.at(ihit) 
		       << " ch:" << timecluster[1][icluster]->channel.at(ihit) << '\n';
		}

	      cout << "side view" << '\n';
	      for(int ihit=0; ihit<timecluster[0][icluster]->pln.size(); ihit++)
		{
		  cout << "pln:" << timecluster[0][icluster]->pln.at(ihit) 
		       << " ch:" << timecluster[0][icluster]->channel.at(ihit) << '\n';
		}
#endif 
	      
	    }
	}
}

void Efficiency::Clear()
{ 
  for(int i=0; i<2; i++)
    for(int j=0; j<100; j++)
      timecluster[i][j]->Clear();
  leadingtime.clear();
  yasucluster->Clear();
}

int Efficiency::GetNpln(BMCluster* bmcluster)
{
  plnstock.clear();
  plnstock.insert(plnstock.end(), bmcluster->pln.begin(), bmcluster->pln.end());
  auto last = unique(plnstock.begin(), plnstock.end());
  plnstock.erase(last, plnstock.end());

  return plnstock.size();
}

int Efficiency::VectorFind(vector<int> vec, int number)
{
  auto itr = std::find(vec.begin(), vec.end(), number);
  size_t index = std::distance( vec.begin(), itr );
  if (index != vec.size()) {
    return 1;
  }
  else {
    return 0;
  }
}

int Efficiency::LeftRightModule(BMCluster* bmcluster)
{
  int leftright=0;
  int count=0;
  double averagetopchannel=0;
  
  for(int ihit=0; ihit<bmcluster->channel.size(); ihit++)
    {
      if(bmcluster->pln.at(ihit)==1 || bmcluster->pln.at(ihit)==2)
	{
	  count++;
	  averagetopchannel += (bmcluster->channel.at(ihit));
	}
    }

  averagetopchannel = averagetopchannel/count;

  if(averagetopchannel<=5) leftright=1;
  else if(averagetopchannel>=9) leftright=0;
  else leftright = -1;

  return leftright;
}


void Efficiency::GetEfficiency()
{
  cout << "FrontLeft: "  << totaldetectionefficiency[0][0] << "/" << Ncount[0][0] << " " 
       << totaldetectionefficiency[0][0]/(double)Ncount[0][0]  << '\n';
  cout << "FrontRight: " << totaldetectionefficiency[0][1] << "/" << Ncount[0][1] << " " 
       << totaldetectionefficiency[0][1]/(double)Ncount[0][1]  << '\n';
  cout << "BackLeft: " << totaldetectionefficiency[1][0] << "/" << Ncount[1][0] << " "
       << totaldetectionefficiency[1][0]/(double)Ncount[1][0]  << '\n';
  cout << "BackRight: " << totaldetectionefficiency[1][1] << "/" << Ncount[1][1] << " "
       << totaldetectionefficiency[1][1]/(double)Ncount[1][1]  << '\n';
}

int Efficiency::YASUplnSearch(BMCluster* bmcluster)
{
  int result=0;
  yasupln.clear();

  yasupln.insert(yasupln.end(), bmcluster->pln.begin(), bmcluster->pln.end());  
  if(VectorFind(yasupln, 19)) result=result+1;
  if(VectorFind(yasupln, 20)) result=result+10;

  return result;
}
