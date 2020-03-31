#ifndef _INC_CELLAUTOMATION
#define _INC_CELLAUTOMATION

#include <iostream>
#include <vector>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <TMath.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TApplication.h>

#include "BMConst.hpp"
#include "DetRecon.hpp"
#include "EVTCluster.hpp"
#include "DetCluster.hpp"
#include "DetClusters.hpp"
#include "DetHitCluster.hpp"
#include "DetHitClusters.hpp"
#include "Cell.hpp"

class CellAutomation
{
  
private:
  
  TString histname;
  int basecell;
  int nextcell;
  int unifiedview;
  int safetycount=0;
  int cellcount=0;
  int totalhit=0;
  int totalreconhit[3]={0, 0, 0};
  int counttrack=0;
  int maxstate;
  int currentstate;
  const static int ncell=4000;

  double mindist[6];
  double maxdist[6];
  double clusterxy[2][6];
  double clusterz[2][6];
  double epsilon;
  double Chithreshold[6][2];

  vector<int> stategroup_sort;
  vector<int> maxstatecell;
  vector<int> stategroup;
  vector<int> idcardgroup;
  vector<int> eliminategroup;
  vector<int> eliminatesubgroup;
  vector<int> eliminatehitgroup;

  TF1* linear;
  TH1D *fitpaper;
  TGraph *fitgraph;
  double graposz[3], graposxy[3];

  clock_t start, end;

  Cell* cell[2][9][ncell];
  DetHitCluster* dethitcluster[2][2][5000];
  DetCluster* testcluster[2][9][6];
  DetClusters* detclusters[2][9][6];

public:
  TH2D *beforerecon[2][9];
  TH2D *midrecon[2][9];
  TH2D *afterrecon[2][9];
  DetCluster* reconcluster[2][9][6][30];
  int Ntrack[2][9];
  int countbunchhit[2][9];
  vector<int>ataribunch[2];

public:

  CellAutomation();
  ~CellAutomation();

  void ReadData(int targetmod, int targetview, EVTCluster* evtcluster, int repeat);
  void CellAutomaton(int targetmod, int view, EVTCluster* evtcluster, vector<int> reject[]);
  void Fillbeforerecon(int bunch, int targetmod, int view);
  void Clustering(int bunch, int targetmod, int view);
  bool MakeCell(int bunch, int targetmod, int view);
  void SearchNeiborCell(int bunch, int view, int mod);
  void UpdateCellState(int bunch, int view, int repeat);
  bool Reconstruction(int bunch, int targetmod, int view, int repeat);
  void RejectTracks(int view, int bunch, int targetmod, int ntrack, vector<int> *reject);
  bool SearchCommonCell(Cell* cell1, Cell* cell2);
  double GetChisquare(double posz1[], double posz2[], double posxy1[], double posxy2[]);
  void SetTime();
  void ShowTime();

  void Clear();
 
};

#endif
