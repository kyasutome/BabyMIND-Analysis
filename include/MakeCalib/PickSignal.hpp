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
  int Ndata;
  int febid[3];
  int spillnum;
  int beambunch;
  double topch;
  int leftindex[2], rightindex[2], topindex[2];
  vector<double>GTrigTagCoins;

public:

  //function
public:
  PickSignal();
  ~PickSignal();

  void SignalCreation(int ientry, BMdata* bmbranch[NUMBEROFFEB], BMBasicRecon* bmbasicrecon, DataReader* dreader,
		      vector<double> commonspill);
  void MakeGTrigCoins(BMdata* bmbranch, vector<double>* GTrigTagCoins);
  void MakeThreeBounds(int ACoin, BMdata* bmbranch_l, BMdata* bmbranch_r, BMdata* bmbranch_t);
  void FillBasicReconClass(int imod, bool firstfill, int CoinsLeft, int CoinsTop, 
			   BMBasicRecon* bmbasicrecon, BMdata* bmbranch_l, BMdata* bmbranch_t);
  bool CheckHorCoincidence(int CoinsLeft, int CoinsRight, BMdata* bmbranch_l, BMdata* bmbranch_r);
  bool CheckVerCoincidence(int topch, int CoinsLeft, int CoinsTop, BMdata* bmbranch_l, BMdata* bmbranch_t);
  double Findbunch(double hittime);
  void Error(int error);
  void EventProcess(int events, int ientry);
  
};

#endif
