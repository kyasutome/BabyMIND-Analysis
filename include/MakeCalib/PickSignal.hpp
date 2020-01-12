#ifndef _INC_PICKSIGNAL
#define _INC_PICKSIGNAL

#include <iostream>
#include <vector>

#include "BMData.hpp"
#include "BMBasicRecon.hpp"

class PickSignal
{
  //parameter
private:
  int yasufeb[2]={21, 29};
  int yasumod;
  int Ndata;
  int febid[3];
  int spillnum;
  int beambunch;
  double topch;
  int leftindex[2], rightindex[2], topindex[2];
  int yasuindex[2];
  vector<double>GTrigTagCoins;

public:

  //function
public:
  PickSignal();
  ~PickSignal();

  void SignalCreation(int ientry, BMdata* bmbranch[NUMBEROFFEB], BMBasicRecon* bmbasicrecon, DataReader* dreader,
		      vector<double> commonspill);
  void YASUSignalCreation(int ientry, BMdata* bmbranch[NUMBEROFFEB], BMBasicRecon* bmbasicrecon, DataReader* dreader,
			  vector<double> commonspill);
  void MakeGTrigCoins(BMdata* bmbranch, vector<double>* GTrigTagCoins, int range);
  void MakeThreeBounds(int ACoin, BMdata* bmbranch_l, BMdata* bmbranch_r, BMdata* bmbranch_t);
  void FillBasicReconClass(int imod, bool firstfill, int CoinsLeft, int CoinsTop, 
			   BMBasicRecon* bmbasicrecon, BMdata* bmbranch_l, BMdata* bmbranch_t);
  void FillYASUBasicReconClass(int imod, int ifeb, bool firstfill, int Coinsyasu, BMBasicRecon* bmbasicrecon, BMdata* bmbranch);
  bool CheckHorCoincidence(int CoinsLeft, int CoinsRight, BMdata* bmbranch_l, BMdata* bmbranch_r);
  bool CheckVerCoincidence(int topch, int CoinsLeft, int CoinsTop, BMdata* bmbranch_l, BMdata* bmbranch_t);
  bool CheckYASUCoincidence(int Coinsyasu, BMdata* bmbranch, int* yasumod);
  double Findbunch(double hittime);
  double ChannelCorr(double channel);
  void Error(int error);
  void EventProcess(int events, int ientry);
  
};

#endif
