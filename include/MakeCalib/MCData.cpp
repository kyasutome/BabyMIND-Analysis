#include <iostream>
#include <stdio.h>

#include "MCData.hpp"
#include "Dimension.cpp"

using namespace std;
//#define debug

MCdata::MCdata()
{

  bmod=0;
  bview=0;
  bpln=0;
  bchannel=0;
  bcharge=0;
  bdposx=0;
  bdposy=0;
  bdposz=0;  

  mod=0;
  view=0;
  pln=0;
  channel=0;
  charge=0;
  dposx=0;
  dposy=0;
  dposz=0;
  
}


MCdata::~MCdata()
{
}

void MCdata::ReadMCdata(TString filedir, TTree *otree, MCRecon *mcrecon, MCTrue *mctrue)
{
  Dimension *fdimension = new Dimension();
  fin = new TFile(filedir, "read");
  tree = (TTree*)fin->Get("tree");
  Nentry = tree->GetEntries();
  cout << "Nentry= " << Nentry << '\n';
  
  tree->SetBranchAddress("npar", &npar);
  tree->SetBranchAddress("nutype", &nutype);
  tree->SetBranchAddress("inttype", &inttype);
  tree->SetBranchAddress("pdg", pdg);

  tree->SetBranchAddress("ipos", ipos);
  tree->SetBranchAddress("fpos", fpos);
  tree->SetBranchAddress("momentum", momentum);

  tree->SetBranchAddress("nuE", &nuE);
  tree->SetBranchAddress("xnu", &xnu);
  tree->SetBranchAddress("ynu", &ynu);
  tree->SetBranchAddress("znu", &znu);
  tree->SetBranchAddress("numomentum", numomentum);
  tree->SetBranchAddress("totcrsne", &totcrsne);
  tree->SetBranchAddress("norm", &norm);
  
  tree->SetBranchAddress("mod", &mod, &bmod);
  tree->SetBranchAddress("view", &view, &bview);
  tree->SetBranchAddress("pln", &pln, &bpln);
  tree->SetBranchAddress("channel", &channel, &bchannel);
  tree->SetBranchAddress("charge", &charge, &bcharge);
  tree->SetBranchAddress("dposx", &dposx, &bdposx);
  tree->SetBranchAddress("dposy", &dposy, &bdposy);
  tree->SetBranchAddress("dposz", &dposz, &bdposz);
  tree->SetBranchAddress("posx", &posx, &bposx);
  tree->SetBranchAddress("posy", &posy, &bposy);
  tree->SetBranchAddress("posz", &posz, &bposz);

  for(int ientry=0; ientry<tree->GetEntries(); ientry++)
    {
      mctrue->Clear();
      mcrecon->Clear();

      tree->GetEntry(ientry);
      tentry = tree->LoadTree(ientry);
      bmod->GetEntry(tentry);
      bview->GetEntry(tentry);
      bpln->GetEntry(tentry);
      bchannel->GetEntry(tentry);
      bcharge->GetEntry(tentry);
      bdposx->GetEntry(tentry);
      bdposy->GetEntry(tentry);
      bdposz->GetEntry(tentry);
      bposx->GetEntry(tentry);
      bposy->GetEntry(tentry);
      bposz->GetEntry(tentry);

      mctrue->npar = npar;
      mctrue->nutype = nutype;
      mctrue->inttype = inttype;
      mctrue->totcrsne = totcrsne;
      mctrue->norm = norm;
      mctrue->nuE = nuE;
      mctrue->xnu = xnu;
      mctrue->ynu = ynu;
      mctrue->znu = znu;

      for(int imom=0; imom<3; imom++)
	mctrue->Pnu[imom] = numomentum[imom];
      
      for(int ipar=0; ipar<20; ipar++)
	{
	  //if(pdg[ipar]!=0)
	  mctrue->pdg[ipar]=pdg[ipar];
	  for(int imom=0; imom<4; imom++)
	    {
	      mctrue->ipos[imom][ipar]=ipos[imom][ipar];
	      mctrue->fpos[imom][ipar]=fpos[imom][ipar];
	      mctrue->momentum[imom][ipar]=momentum[imom][ipar];
	    }
	}//ipar

      for(int ihit=0; ihit<mod->size(); ihit++)
	{
	  mcrecon->mod.push_back(mod->at(ihit));
	  mcrecon->view.push_back(view->at(ihit));
	  mcrecon->pln.push_back(pln->at(ihit));
	  mcrecon->channel.push_back(channel->at(ihit));
	  mcrecon->charge.push_back(charge->at(ihit));
	  mcrecon->dposx.push_back(dposx->at(ihit));
	  mcrecon->dposy.push_back(dposy->at(ihit));
	  mcrecon->dposz.push_back(dposz->at(ihit));

	  MOD = mod->at(ihit);
	  VIEW = view->at(ihit);

	  if(VIEW==0)
	    {
	      POSZ = dposz->at(ihit)+fdimension->offset[VIEW][0][MOD];
	      POSY = dposy->at(ihit)+fdimension->offset[VIEW][1][MOD];
	    }

	  if(VIEW==1)
	    {
	      POSZ = dposz->at(ihit)+fdimension->offset[VIEW][0][MOD];
	      POSX = dposx->at(ihit)+fdimension->offset[VIEW][1][MOD];
	    }

	  mcrecon->posx.push_back(POSX);
	  mcrecon->posy.push_back(POSY);
	  mcrecon->posz.push_back(POSZ);
	}

      otree->Fill();
    }//ientry

  
  fin->Close();

#ifdef debug
  tree->GetEntry(0);
  tentry = tree->LoadTree(0);

  bmod->GetEntry(tentry);
  bview->GetEntry(tentry);
  bpln->GetEntry(tentry);
  bchannel->GetEntry(tentry);
  bcharge->GetEntry(tentry);
  bdposx->GetEntry(tentry);
  bdposy->GetEntry(tentry);
  bdposz->GetEntry(tentry);

  cout << "npar= " << npar << '\n';
  cout << "nutype= " << nutype << '\n';
  cout << "inttype= " << inttype << '\n';
  cout << "pdg= " << pdg[0] << '\n';

  for(int i=0; i<4; i++)
    {
      cout << ipos[i][0] << " " << fpos[i][0] << " " << momentum[i][0] << '\n';
    }

  cout << "nuE= " << nuE << " xnu= " << xnu << " ynu= " << ynu << " znu= " << znu << '\n';
  cout << "Pnu= " << numomentum[0] << " totcrsne= " << totcrsne << " norm= " << norm << '\n';
  
  for(int i=0; i<mod->size(); i++)
    {
      cout << "mod= " << mod->at(i) << " view= " << view->at(i) << " pln= " << pln->at(i) << " channel= " << channel->at(i)
	   << " charge= " << charge->at(i) << " posx= " << dposx->at(i) << " posy= " << dposy->at(i) << " posz= " << dposz->at(i) << '\n'; 
    }
  
  fin->Close();

#endif

}
