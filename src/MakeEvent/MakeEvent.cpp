#include <iostream>
#include <stdio.h>

//include
#include "DataReader.cpp"
#include "BMData.cpp"
#include "EvtFormat.cpp"
#include "BSDApply.cpp"

//library
#include "BMBasicRecon.hpp"
#include "BMBeaminfo.hpp"
#include "EVTCluster.hpp"
#include "PMRecon.hpp"
#include "WGRecon.hpp"


using namespace std;

int main( int argc, char **argv )
{
  std::string name = string(argv[1]);
  int wgrun = std::atoi(argv[2]);
  TString commondir(name);
  

  BMBasicRecon *bmbasicrecon = new BMBasicRecon();
  BMBeaminfo *bmbeaminfo = new BMBeaminfo();
  BMBSD *bmbsd_bm = new BMBSD();
  BMBSD *bmbsd_pm = new BMBSD();
  BMBSD *bmbsd_wg[8];
  WGRecon *wgrecon[8];

  for(int idif=0; idif<8; idif++)
    {
      bmbsd_wg[idif] = new BMBSD();
      wgrecon[idif] = new WGRecon();
    }

  EVTCluster *evtcluster = new EVTCluster();
  PMRecon *pmrecon = new PMRecon();
  EvtFormat *evtformat = new EvtFormat();
  BSDApply *bsdapply = new BSDApply();

  int sunixtimeentry;
  int theunixtimeentry;
  int thebaseunixtime;

  int detunixtime[2][3];

  vector<int> baseunixtime;
  baseunixtime.clear();
  vector<double> basepot;
  basepot.clear();
  
  TFile *fout = new TFile(Form("./process/3-EVT/Evt_%d.root", wgrun),"recreate");
  TTree *otree = new TTree("tree","tree");
  otree->Branch("EVTCluster","EVTCluster",&evtcluster,32000,2);

  bsdapply->ReadBSDfile();
  evtformat->ReadBMChain(name, bmbasicrecon, bmbeaminfo, bmbsd_bm, &detunixtime[0][0], &detunixtime[1][0]);
  evtformat->ReadPMChain(name, pmrecon, bmbsd_pm, &detunixtime[0][1], &detunixtime[1][1]);
  evtformat->ReadWGChain(name, wgrecon, bmbsd_wg, &detunixtime[0][2], &detunixtime[1][2]);

  cout << "bmunix= " << detunixtime[0][0] << " " << detunixtime[1][0] << '\n';
  cout << "pmunix= " << detunixtime[0][1] << " " << detunixtime[1][1] << '\n';
  cout << "wgunix= " << detunixtime[0][2] << " " << detunixtime[1][2] << '\n';

  for(int ientry=0; ientry<bsdapply->bsdchain->GetEntries(); ientry++)
    {
      bsdapply->bsdchain->GetEntry(ientry);
      baseunixtime.push_back(bsdapply->trg_sec[2]);
      basepot.push_back(bsdapply->ct_np[4][0]);
    }

  auto theunixit = find(baseunixtime.begin(), baseunixtime.end(), detunixtime[0][1]);
  sunixtimeentry = theunixit - baseunixtime.begin();  
  
  evtformat->FillEvtClass(otree, sunixtimeentry, baseunixtime, basepot, 
			  bmbasicrecon, pmrecon, wgrecon, evtcluster, name);
  
  
  fout->cd();
  otree->Write();
  fout->Close();

  evtformat->DeleteChain();
  bsdapply->bsdchain->Delete();
  
}
