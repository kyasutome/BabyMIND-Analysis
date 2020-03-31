#include <iostream>
#include <fstream>
#include <vector>

#include "PickSignal.hpp"
#include "DataReader.hpp"

using namespace std;
//#define debug

PickSignal::PickSignal()
{
  GTrigTagCoins.clear();

  leftindex[0] = 0;
  leftindex[1] = 0;
  rightindex[0] = 0;
  rightindex[1] = 0;
  topindex[0] = 0;
  topindex[1] = 0;
  yasuindex[0] = 0;
  yasuindex[1] = 0;
}

PickSignal::~PickSignal()
{
}


void PickSignal::YASUSignalCreation(int ientry, BMdata* bmbranch[NUMBEROFFEB], BMBasicRecon* bmbasicrecon, DataReader* dreader,
				    vector<double> commonspill, int id)
{  
  for(int ifeb=0; ifeb<2; ifeb++)
    {
      spillnum = commonspill.at(ientry);
      auto spillit = find(dreader->febspill[id][yasufeb[ifeb]].begin(), dreader->febspill[id][yasufeb[ifeb]].end(), spillnum);
      spillnum = spillit - dreader->febspill[id][yasufeb[ifeb]].begin();
      dreader->FEBtree[yasufeb[ifeb]]->GetEntry(spillnum);

      MakeGTrigCoins(bmbranch[yasufeb[ifeb]], &GTrigTagCoins, 0);

      for(int index=0; index<GTrigTagCoins.size(); index++)
        {
	  auto boundyasu = equal_range(bmbranch[yasufeb[ifeb]]->GTrigTag->begin(), bmbranch[yasufeb[ifeb]]->GTrigTag->end(), 
				       GTrigTagCoins.at(index));
	  yasuindex[0] = boundyasu.first - bmbranch[yasufeb[ifeb]]->GTrigTag->begin();
	  yasuindex[1] = boundyasu.second - bmbranch[yasufeb[ifeb]]->GTrigTag->begin();

          for(int Coinsyasu=yasuindex[0]; Coinsyasu<yasuindex[1]; Coinsyasu++)
            {
              bool firstfill=true;
	      if(CheckYASUCoincidence(Coinsyasu, bmbranch[yasufeb[ifeb]], &yasumod))
		if(ChannelCorr(bmbranch[yasufeb[ifeb]]->hitsChannel->at(Coinsyasu))<=13)
		  //Fill to BasicRecon Class		
		  FillYASUBasicReconClass(yasumod, ifeb, firstfill, Coinsyasu, bmbasicrecon, bmbranch[yasufeb[ifeb]]);
	      firstfill = false;
	      
	    }//Coinsyasu loop 
	}//index

    }//ifeb loop

}

void PickSignal::SignalCreation(int ientry, BMdata* bmbranch[NUMBEROFFEB], BMBasicRecon* bmbasicrecon, DataReader* dreader, 
				vector<double> commonspill, int id) 
{
  for(int imod=1; imod<NUMBEROFMODULE+1; imod++)
  //for(int imod=1; imod<5; imod++)
    {
      for(int ifeb=0; ifeb<3; ifeb++)
	{
	  febid[ifeb] = dreader->MapCon[ifeb+1][imod];
	  spillnum = commonspill.at(ientry);
	  auto spillit = find(dreader->febspill[id][febid[ifeb]].begin(), dreader->febspill[id][febid[ifeb]].end(), spillnum);
	  spillnum = spillit - dreader->febspill[id][febid[ifeb]].begin() + 20000*id;
	  dreader->FEBtree[febid[ifeb]]->GetEntry(spillnum);
	}//ifeb loop
      
      topch = dreader->MapCon[4][imod];
      MakeGTrigCoins(bmbranch[0], &GTrigTagCoins, 2);
      
      for(int index=0; index<GTrigTagCoins.size(); index++)
	{
	  MakeThreeBounds(GTrigTagCoins.at(index), bmbranch[febid[0]], bmbranch[febid[1]], bmbranch[febid[2]]);
	  
	  for(int CoinsLeft=leftindex[0]; CoinsLeft<leftindex[1]; CoinsLeft++)
	    {
	      bool firstfill=true;
	      for(int CoinsRight=rightindex[0]; CoinsRight<rightindex[1]; CoinsRight++)
		if(CheckHorCoincidence(CoinsLeft, CoinsRight, bmbranch[febid[0]], bmbranch[febid[1]]))			
		  for(int CoinsTop=topindex[0]; CoinsTop<topindex[1]; CoinsTop++)
		    if(CheckVerCoincidence(topch, CoinsLeft, CoinsTop, bmbranch[febid[0]], bmbranch[febid[2]]))
		      {
			//Fill to BasicRecon Class
			FillBasicReconClass(imod,firstfill,CoinsLeft,CoinsRight,CoinsTop,
					    bmbasicrecon, bmbranch[febid[0]], bmbranch[febid[1]], bmbranch[febid[2]]);
			firstfill = false;
			
		      }
	    }//CoinsLeft loop
	  
	}//CoinsRight loop
      
    }//imod loop    
}

void PickSignal::MakeGTrigCoins(BMdata* bmbranch, vector<double>* GTrigTagCoins, int range)
{
  GTrigTagCoins->clear();
  Ndata = bmbranch->GTrigTag->size();

#ifdef debug
  cout << "Ndata= " << Ndata << '\n';
#endif 

  if(Ndata>1)
    {
      for(int icoin=0; icoin<Ndata-range; icoin++)
	{
	  if(bmbranch->GTrigTag->at(icoin) == bmbranch->GTrigTag->at(icoin+range))
	    GTrigTagCoins->push_back(bmbranch->GTrigTag->at(icoin));
	}
    }

  if(GTrigTagCoins->size()!=0)
    {
      DataReader::DuplicateCut(GTrigTagCoins);
    }

}

void PickSignal::MakeThreeBounds(int ACoin, BMdata* bmbranch_l, BMdata* bmbranch_r, BMdata* bmbranch_t)
{
  auto boundleft = equal_range(bmbranch_l->GTrigTag->begin(), bmbranch_l->GTrigTag->end(), ACoin);
  leftindex[0] = boundleft.first - bmbranch_l->GTrigTag->begin();
  leftindex[1] = boundleft.second - bmbranch_l->GTrigTag->begin();
 
  auto boundright = equal_range(bmbranch_r->GTrigTag->begin(), bmbranch_r->GTrigTag->end(), ACoin);
  rightindex[0] = boundright.first - bmbranch_r->GTrigTag->begin();
  rightindex[1] = boundright.second - bmbranch_r->GTrigTag->begin();

  auto boundtop = equal_range(bmbranch_t->GTrigTag->begin(), bmbranch_t->GTrigTag->end(), ACoin);
  topindex[0] = boundtop.first - bmbranch_t->GTrigTag->begin();
  topindex[1] = boundtop.second - bmbranch_t->GTrigTag->begin();

#ifdef debug
  cout << "leftindex= " << leftindex[0] << " " << leftindex[1] << '\n';
  cout << "rightindex= " << rightindex[0] << " " << rightindex[1] << '\n';
  cout << "topindex= " << topindex[0] << " " << topindex[1] << '\n';
#endif 

}

bool PickSignal::CheckHorCoincidence(int CoinsLeft, int CoinsRight, BMdata* bmbranch_l, BMdata* bmbranch_r)
{
  bool coincidencecheck = false;
  double timecut = 30;
  double timedifcut = 7;
  if(bmbranch_l->hitsChannel->at(CoinsLeft) == bmbranch_r->hitsChannel->at(CoinsRight))
    if(fabs(bmbranch_l->hitLeadTime->at(CoinsLeft) - bmbranch_r->hitLeadTime->at(CoinsRight))<timecut)	
      if(bmbranch_l->hitTimeDif->at(CoinsLeft)>timedifcut && bmbranch_r->hitTimeDif->at(CoinsRight)>timedifcut)
	coincidencecheck = true;

  return coincidencecheck;
    
}

 bool PickSignal::CheckVerCoincidence(int topch, int CoinsLeft, int CoinsTop, BMdata* bmbranch_l, BMdata* bmbranch_t)
 {
   bool coincidencecheck = false;
   double timecut = 30;
   double timedifcut= 4;
   if(bmbranch_t->hitsChannel->at(CoinsTop)>=32*topch && bmbranch_t->hitsChannel->at(CoinsTop)<32*(1+topch))
     if(fabs(bmbranch_l->hitLeadTime->at(CoinsLeft) - bmbranch_t->hitLeadTime->at(CoinsTop))<timecut)	
       if(bmbranch_t->hitTimeDif->at(CoinsTop)>timedifcut)
	 coincidencecheck = true;
   
   return coincidencecheck;    
 }
 
bool PickSignal::CheckYASUCoincidence(int Coinsyasu, BMdata* bmbranch, int* yasumod)
{
  bool coincidencecheck = false;
  double timedifcut= 0;
  
  if(bmbranch->hitTimeDif->at(Coinsyasu)>timedifcut)
    coincidencecheck = true;

  if(bmbranch->hitsChannel->at(Coinsyasu) < 10) *yasumod=19;
  if(bmbranch->hitsChannel->at(Coinsyasu) > 30) *yasumod=20;
  
  return coincidencecheck;    
  
}
 
double PickSignal::Findbunch(double hittime)
{
  double bunch;
  int lbound[8] = {40600, 41250, 41850, 42400, 42950, 43550, 44150, 44800};
  int ubound[8] = {41100, 41750, 42300, 42750, 43500, 44100, 44650, 45100};
  bool beambunch = false;

  for(int i=0; i<8; i++)
    {
      if(hittime*2.5>lbound[i] && hittime*2.5<ubound[i])
        {
          bunch = i+1;
          beambunch = true;
          break;
        }
    }

  if(!beambunch) bunch = -1;
  return bunch;
}

void PickSignal::FillBasicReconClass(int imod, bool firstfill, int CoinsLeft, int CoinsRight, int CoinsTop,
				     BMBasicRecon* bmbasicrecon, BMdata* bmbranch_l, BMdata* bmbranch_r, BMdata* bmbranch_t)
{
  //for horiontal
  lchannel = bmbranch_l->hitsChannel->at(CoinsLeft);
  rchannel = bmbranch_r->hitsChannel->at(CoinsRight);
  tchannel = bmbranch_t->hitsChannel->at(CoinsTop);
  lgain = gain[febid[0]].at(lchannel);
  rgain = gain[febid[1]].at(rchannel);
  tgain = gain[febid[2]].at(tchannel);
 

  if(firstfill)
    {
      beambunch = Findbunch(bmbranch_l->hitTimefromSpill->at(CoinsLeft));
      bmbasicrecon->mod.push_back(5); // PM:0, WG1:1, WG2:2, WMS:3, WMN:4, BM:5, BM-Y:6
      bmbasicrecon->view.push_back(0);
      bmbasicrecon->pln.push_back(imod);
      bmbasicrecon->channel.push_back(bmbranch_l->hitsChannel->at(CoinsLeft));
      bmbasicrecon->HG.push_back(bmbranch_l->hitAmpl->at(CoinsLeft));
      bmbasicrecon->LHG.push_back(bmbranch_l->hitAmpl->at(CoinsLeft));
      bmbasicrecon->RHG.push_back(bmbranch_r->hitAmpl->at(CoinsRight));
      //bmbasicrecon->THG.push_back(bmbranch_t->hitAmpl->at(CoinsTop));
      bmbasicrecon->THG.push_back(-1);

      bmbasicrecon->Lgain.push_back(lgain);
      bmbasicrecon->Rgain.push_back(rgain);
      bmbasicrecon->Tgain.push_back(-1);

      bmbasicrecon->LG.push_back(bmbranch_l->hitLGAmpl->at(CoinsLeft));
      bmbasicrecon->Ltime.push_back(bmbranch_l->hitLeadTime->at(CoinsLeft));
      bmbasicrecon->Ftime.push_back(bmbranch_l->hitTrailTime->at(CoinsLeft));
      bmbasicrecon->Htime.push_back(bmbranch_l->hitTimefromSpill->at(CoinsLeft)*2.5);
      bmbasicrecon->bunch.push_back(beambunch);
      bmbasicrecon->timedif.push_back(bmbranch_l->hitTimeDif->at(CoinsLeft));

    }
  //for vertical
  int verch = (int)(bmbranch_t->hitsChannel->at(CoinsTop))%32;
  //verch = verch/2;
  beambunch = Findbunch(bmbranch_t->hitTimefromSpill->at(CoinsTop));
  if(imod==2 || imod==11 || imod==13 || imod==17 || imod==18)
    verch = verch;
  else
    verch = 31-verch;

      bmbasicrecon->mod.push_back(5); // PM:0, WG1:1, WG2:2, WMS:3, WMN:4, BM:5, BM-Y:6
      bmbasicrecon->view.push_back(1);
      bmbasicrecon->pln.push_back(imod);
      bmbasicrecon->channel.push_back(verch);
      bmbasicrecon->HG.push_back(bmbranch_t->hitAmpl->at(CoinsTop));
      //bmbasicrecon->LHG.push_back(bmbranch_l->hitAmpl->at(CoinsLeft));
      //bmbasicrecon->RHG.push_back(bmbranch_r->hitAmpl->at(CoinsRight));
      bmbasicrecon->LHG.push_back(-1);
      bmbasicrecon->RHG.push_back(-1);
      bmbasicrecon->THG.push_back(bmbranch_t->hitAmpl->at(CoinsTop));
      bmbasicrecon->LG.push_back(bmbranch_t->hitLGAmpl->at(CoinsTop));

      bmbasicrecon->Lgain.push_back(-1);
      bmbasicrecon->Rgain.push_back(-1);
      bmbasicrecon->Tgain.push_back(tgain);

      bmbasicrecon->Ltime.push_back(bmbranch_t->hitLeadTime->at(CoinsTop));
      bmbasicrecon->Ftime.push_back(bmbranch_t->hitTrailTime->at(CoinsTop));
      bmbasicrecon->Htime.push_back(bmbranch_t->hitTimefromSpill->at(CoinsTop)*2.5);
      bmbasicrecon->bunch.push_back(beambunch);
      bmbasicrecon->timedif.push_back(bmbranch_t->hitTimeDif->at(CoinsTop)); 

}

void PickSignal::FillYASUBasicReconClass(int imod, int ifeb, 
					 bool firstfill, int Coinsyasu, BMBasicRecon* bmbasicrecon, BMdata* bmbranch)
{

  lchannel = bmbranch->hitsChannel->at(Coinsyasu);
  lchannel = ChannelCorr(lchannel);
  
  lgain = gain[yasufeb[ifeb]].at(lchannel);

  if(firstfill)
    {
      beambunch = Findbunch(bmbranch->hitTimefromSpill->at(Coinsyasu));
      bmbasicrecon->mod.push_back(6); // PM:0, WG1:1, WG2:2, WMS:3, WMN:4, BM:5, BM-Y:6
      bmbasicrecon->view.push_back(0);
      bmbasicrecon->pln.push_back(imod);

      if(imod==19 && ifeb==0)
	bmbasicrecon->channel.push_back(ChannelCorr(bmbranch->hitsChannel->at(Coinsyasu)));
      if(imod==19 && ifeb==1)
	bmbasicrecon->channel.push_back(ChannelCorr(bmbranch->hitsChannel->at(Coinsyasu))+7);

      if(imod==20 && ifeb==0)
	bmbasicrecon->channel.push_back(ChannelCorr(bmbranch->hitsChannel->at(Coinsyasu))-7);
      if(imod==20 && ifeb==1)
	bmbasicrecon->channel.push_back(ChannelCorr(bmbranch->hitsChannel->at(Coinsyasu)));

      bmbasicrecon->HG.push_back(bmbranch->hitAmpl->at(Coinsyasu));
      bmbasicrecon->LHG.push_back(bmbranch->hitAmpl->at(Coinsyasu));
      bmbasicrecon->RHG.push_back(-1);
      bmbasicrecon->THG.push_back(-1);
      bmbasicrecon->LG.push_back(bmbranch->hitLGAmpl->at(Coinsyasu));

      bmbasicrecon->Lgain.push_back(lgain);
      bmbasicrecon->Rgain.push_back(-1);
      bmbasicrecon->Tgain.push_back(-1);

      bmbasicrecon->Ltime.push_back(bmbranch->hitLeadTime->at(Coinsyasu));
      bmbasicrecon->Ftime.push_back(bmbranch->hitTrailTime->at(Coinsyasu));
      bmbasicrecon->Htime.push_back(bmbranch->hitTimefromSpill->at(Coinsyasu)*2.5);
      bmbasicrecon->bunch.push_back(beambunch);
      bmbasicrecon->timedif.push_back(bmbranch->hitTimeDif->at(Coinsyasu));
    }

}

double PickSignal::ChannelCorr(double channel)
{
  double corrchannel;
  if(channel<=2)
    corrchannel = channel;
  if(channel>=4 && channel<=7)
    corrchannel = channel-1;
  if(channel>=32)
    corrchannel = channel-25;
    
  return corrchannel;
}

void PickSignal::PickGain()
{
  TString filename;
  int NSlot[8] = {6, 6, 6, 6, 5, 5, 6, 6};
  double dummy;
  double thegain;
  int feb;

  finnch.open("./data/nfebchannel.txt");
  for(int ifeb=0; ifeb<64; ifeb++)
    {
      finnch >> dummy >> Nchannel[ifeb];
    }

  for(int imcr=0; imcr<8; imcr++)
    {
      for(int ifile=0; ifile<NSlot[imcr]; ifile++)
	{
	  filename.Form("./data/BMCalib_1204_2020/MCR_%d_Slot_%d_gain.txt", imcr, ifile);
	  feb = imcr*8 + ifile;
	  fin[feb].open(filename.Data());
	 
	  for(int ich=0; ich<Nchannel[feb]; ich++)
	    {
	      fin[feb] >> dummy >> thegain;
	      gain[feb].push_back(thegain);
	    }
	}
    }
 
  cout << "Read gain data..." << '\n';

}

void PickSignal::Error(int error)
{
  cout << Form("Error level %d", error) << '\n';
}

void PickSignal::EventProcess(int events, int ientry)
{
  if(ientry%events==0)
  cout << Form("Current Process : %d", ientry) << '\n';
}
