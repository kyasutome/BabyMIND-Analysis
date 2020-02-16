#ifndef _INC_EVTFORMAT
#define _INC_EVTFORMAT

#include <iostream>
#include <vector>
#include <time.h>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TChain.h>

#include "BMData.hpp"
#include "BMBasicRecon.hpp"
#include "BMBeaminfo.hpp"
#include "EVTCluster.hpp"
#include "PMRecon.hpp"
#include "WGRecon.hpp"
#include "BMBSD.hpp"

class EvtFormat
{
  //parameter
private:

  int Nentry;

public:
  TChain* bmchain;
  TChain* pmchain;
  TChain* wgchain[8];
  int nbmdata;
  int npmdata;
  int nwgdata[8];
  int theunixtimeentry;
  int theunixtime;
  int spillnum;
  double thepot;
  double totalpot;

  bool bmfillflag;
  bool pmfillflag;
  bool wgfillflag[8];

  int bmentry;
  int pmentry;
  int wgentry[8];

  vector <int> bmunix;
  vector <int> pmunix;
  vector <int> wgunix[8];

  int mod, view, pln, channel;
  double dposx, dposy, dposz;
  double posx, posy, posz;

  /*
  vector <int> bmpot;
  vector <int> pmpot;
  vector <int> wgpot[8];
  */

  //function
public:
  EvtFormat();
  ~EvtFormat();

  void ReadBMChain(TString filepath, BMBasicRecon* bmbasicrecon, BMBeaminfo* bmbeaminfo, 
		   BMBSD* bmbsd, int *sunixtime, int *eunixtime);
  void ReadPMChain(TString filepath, PMRecon* pmrecon, BMBSD* bmbsd, int *sunixtime, int *eunixtime);
  void ReadWGChain(TString filepath, WGRecon* wgrecon[], BMBSD* bmbsd[], int *sunixtime, int *eunixtime);
  bool FillEvtClass(TTree* otree, int sunixtimeentry, int eunixtimeentry, vector <int> baseunixtime, vector <double> basepot, 
		    BMBasicRecon* bmbasicrecon, BMBeaminfo* bmbeaminfo, PMRecon* pmrecon,
		    WGRecon* wgrecon[8], EVTCluster* evtcluster, TString filepath);

  void AddBMChain(TString filepath);
  void AddPMChain(TString filepath);
  void AddWGChain(TString filepath, int idif);

  void PrintTime(time_t unixtime);
  void DeleteChain();
  
};

#endif

