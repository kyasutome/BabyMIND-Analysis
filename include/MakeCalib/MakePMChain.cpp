#include <iostream>
#include <fstream>
#include <vector>

#include "MakePMChain.hpp"

using namespace std;
//#define debug

MakePMChain::MakePMChain()
{
  pathtopm.Form("/Users/kenji/Dropbox/wagasci/proton_module/data/recon");
  pmchain = new TChain("tree", "tree");
  bmod=0;
  bview=0;
  bpln=0;
  bchannel=0;
  btime=0;
  bbunch=0;
}

MakePMChain::~MakePMChain()
{
}

void MakePMChain::ReadPMTree(int run, int ssub, int esub, PMRecon *pmrecon)
{
  cout << "Start reading PM tree..." << '\n';
  npmfile = esub-ssub;
  
  for(int isub=ssub; isub<esub; isub++)
    {
      pmfilename.Form("%s/ingrid_%d_%d_recon.root", pathtopm.Data(), run, isub);
      if (gSystem->GetPathInfo(pmfilename.Data(), info)!=0)
	{
	  cout << "File" << pmfilename << " done not exist" << '\n';
	  continue;
	}else{
	pmchain->Add(pmfilename);	
      }
    }

  pmchain->SetBranchAddress("mod",&pmrecon->mod,&bmod);
  pmchain->SetBranchAddress("view",&pmrecon->view,&bview);
  pmchain->SetBranchAddress("pln",&pmrecon->pln,&bpln);
  pmchain->SetBranchAddress("ch",&pmrecon->channel,&bchannel);
  pmchain->SetBranchAddress("time",&pmrecon->time,&btime);
  pmchain->SetBranchAddress("bunch",&pmrecon->bunch,&bbunch);
  pmchain->SetBranchAddress("spill",&pmrecon->spill);
  pmchain->SetBranchAddress("unixtime",&pmrecon->unixtime);

}

void MakePMChain::FillPMClass(int ientry, PMRecon* pmrecon)
{
  pmchain->GetEntry(ientry);
  tentry = pmchain->LoadTree(ientry);

  bmod->GetEntry(tentry);
  bview->GetEntry(tentry);
  bpln->GetEntry(tentry);
  bchannel->GetEntry(tentry);
  btime->GetEntry(tentry);
  bbunch->GetEntry(tentry);

}
