#include <iostream>
#include <fstream>
#include <vector>

#include "babymind.hpp"

using namespace std;
//#define debug

BabyMIND::BabyMIND()
{
  bmchain = new TChain("tree", "tree");
  
  for(int imod=0; imod<18; imod++)
    {
      for(int ihor=0; ihor<96; ihor++)	
	for(int iread=0; iread<2; iread++)
	  {
	    histname.Form("adcdist_hor_%d_%d_%d", imod, ihor, iread);
	    adcdist_hor[imod][ihor][iread] = new TH1D(histname, histname, 200, 100, 4096);
	  }
      
      for(int iver=0; iver<32; iver++)
	{
	  histname.Form("adcdist_ver_%d_%d", imod, iver);
	  adcdist_ver[imod][iver] = new TH1D(histname, histname, 200, 100, 4096);
	}

    }

  for(int imod=0; imod<2; imod++)
    {
      for(int iver=0; iver<14; iver++)
	{
	  histname.Form("adcdist_yasu_%d_%d", imod, iver);
	  adcdist_yasu[imod][iver] = new TH1D(histname, histname, 200, 100, 4096);
	}
    }

  adcdist_hor_left_total = new TH1D("adcdist_hor_left_total", "", 200, 100, 4096);
  adcdist_hor_right_total = new TH1D("adcdist_hor_right_total", "", 200, 100, 4096);
  adcdist_ver_total = new TH1D("adcdist_ver_total", "", 200, 100, 4096);
  adcdist_yasu_total = new TH1D("adcdist_yasu_total", "", 200, 100, 4096);

  landau = new TF1("landau", "landau", 100, 4000);
  landau->SetParameters(0, 0, 0);

  ped=50;

  int position[19]={-9999, -20, 203, 407, 517, 627, 879, 1057, 1362, 1541, 1848, 2141, 2347, 2571, 2775, 3220, 3550, 3964, 4074};
  for(int i=0; i<19; i++)
    {
      planepos[i] = position[i];
    }
}

BabyMIND::~BabyMIND()
{
}

void BabyMIND::FillADCDist(TString filedir, BMBasicRecon* bmbasicrecon, BMBeaminfo* bmbeaminfo)
{
  cout << "Start reading BM chain..." << '\n';
  AddBMChain(filedir);
  bmchain->SetBranchAddress("BMBasicRecon", &bmbasicrecon);
  bmchain->SetBranchAddress("BMBeaminfo", &bmbeaminfo);
  nbmdata = bmchain->GetEntries();

  cout << nbmdata << '\n';

  for(int ientry=0; ientry<nbmdata; ientry++)
    {
      bmchain->GetEntry(ientry);
      for(int ihit=0; ihit<bmbasicrecon->mod.size(); ihit++)
	{
	  mod = bmbasicrecon->mod.at(ihit);
	  view = bmbasicrecon->view.at(ihit);
	  pln = bmbasicrecon->pln.at(ihit)-1;
	  channel = bmbasicrecon->channel.at(ihit);
	  LHG = bmbasicrecon->LHG.at(ihit);
	  RHG = bmbasicrecon->RHG.at(ihit);
	  THG = bmbasicrecon->THG.at(ihit);
 
	  lgain = bmbasicrecon->Lgain.at(ihit);
	  rgain = bmbasicrecon->Rgain.at(ihit);
	  tgain = bmbasicrecon->Tgain.at(ihit); 

	  //cout << "mod= " << mod << " view= " << view << " pln= " << pln << " channel= " << channel << '\n'; 

	  if(mod==5)
	    {
	      if(view==0)
		{
		  adcdist_hor[pln][channel][0]->Fill(LHG);
		  adcdist_hor[pln][channel][1]->Fill(RHG);
		  adcdist_hor_left_total->Fill(LHG);
		  adcdist_hor_right_total->Fill(RHG);

		  gain_hor[pln][channel][0] = lgain;
		  gain_hor[pln][channel][1] = rgain;
		}

	      if(view==1)
		{
		  adcdist_ver[pln][channel]->Fill(THG);		  
		  adcdist_ver_total->Fill(THG);

		  gain_ver[pln][channel] = tgain;
		}

	    }//mod==5

	  if(mod==6)
	    {
	      if(view==0)
		{
		  pln = pln-18;
		  adcdist_yasu[pln][channel]->Fill(LHG);
		  adcdist_yasu_total->Fill(LHG);
		  gain_yasu[pln][channel] = lgain;
		}
	    }//mod==6
	}
      
      if(ientry%500==0)
	cout << "ientry= " << ientry << '\n';
    }//ientry

}

void BabyMIND::AddBMChain(TString filedir)
{
  //bmchain->Add(Form("%s/BMCalib_29Jan_3.root",filedir.Data()));
  //bmchain->Add(Form("%s/BMCalib_30Jan_1.root",filedir.Data()));
  //bmchain->Add(Form("%s/BMCalib_31Jan_1.root",filedir.Data()));
  bmchain->Add(Form("%s/BMCalib_1Feb_1.root",filedir.Data()));
  bmchain->Add(Form("%s/BMCalib_2Feb_1.root",filedir.Data()));
  //bmchain->Add(Form("%s/BMCalib_3Feb_1.root",filedir.Data()));
  //bmchain->Add(Form("%s/BMCalib_5Feb_1.root",filedir.Data()));
  //bmchain->Add(Form("%s/BMCalib_6Feb_1.root",filedir.Data()));
  //bmchain->Add(Form("%s/BMCalib_7Feb_1.root",filedir.Data()));
  //bmchain->Add(Form("%s/BMCalib_8Feb_1.root",filedir.Data()));
  //bmchain->Add(Form("%s/BMCalib_9Feb_1.root",filedir.Data()));
  //bmchain->Add(Form("%s/BMCalib_10Feb_1.root",filedir.Data()));
}

void BabyMIND::CalcPEMean()
{
  for(int imod=0; imod<18; imod++)
    {
      for(int ihor=0; ihor<96; ihor++)
        for(int iread=0; iread<2; iread++)
	  {
	    adcdist_hor[imod][ihor][iread]->Fit(landau,"Q");
	    pe = (landau->GetParameter(1)-ped)/gain_hor[imod][ihor][iread];
	    pe_hor[imod][ihor][iread] = pe;
	  }
      
      for(int iver=0; iver<32; iver++)
	{
	  adcdist_ver[imod][iver]->Fit(landau, "Q");
	  pe = (landau->GetParameter(1)-ped)/gain_ver[imod][iver];
	  pe_ver[imod][iver] = pe;
	}
    }   

  for(int imod=0; imod<2; imod++)
    for(int iyasu=0; iyasu<14; iyasu++)
      {
	adcdist_yasu[imod][iyasu]->Fit(landau, "Q");
	pe = (landau->GetParameter(1)-ped)/gain_yasu[imod][iyasu];
	pe_yasu[imod][iyasu] = pe;
      }
  
}


bool BabyMIND::ConverttoPln(vector<int> activepln)
{
  plane.clear();
  for(int ihit=0; ihit<activepln.size(); ihit++)
    {
      int theposition = activepln.at(ihit);
      int refposition;
      int theplane;
      for(int iref=1; iref<=18; iref++)
	{
	  refposition = planepos[iref];
	  if(fabs(theposition-refposition)<=30)
	    {
	      theplane = iref;
	      break;
	    }
	}//iref

      plane.push_back(theplane);
      //cout << "theplane= " << theplane << '\n';
    }//ihit

  auto last =unique(plane.begin(), plane.end());
  plane.erase(last, plane.end());
}

bool BabyMIND::SearchCoinPlns(int Plane)
{
  bool findtheplns = false;
  int coinbefore = Plane-1;
  int coinafter = Plane+1;

  bool beforeflag = false;
  bool afterflag = false;

  if(find(plane.begin(), plane.end(), coinbefore)!=plane.end())
    beforeflag = true;

  if(find(plane.begin(), plane.end(), coinafter)!=plane.end())
    afterflag = true;

  if(beforeflag&&afterflag)
    findtheplns = true;

  return findtheplns;
}

bool BabyMIND::SearchThePln(int Plane)
{
  bool findthepln = false;
  if(find(plane.begin(), plane.end(), Plane)!=plane.end())
    findthepln = true;
  
  return findthepln;
}

void BabyMIND::CalcDetEff(int Plane, vector<int> activepln, int* counttotal, int* counteff)
{
  ConverttoPln(activepln);
  if(SearchCoinPlns(Plane))
    {
      *counttotal = *counttotal+1;
      if(SearchThePln(Plane))
	{
	  *counteff = *counteff+1;
	}
      /*
      if(!SearchThePln(Plane))
	{
	  if(Plane==16)
	    cout << "top out" << '\n';
	}
      */
    }
}

int BabyMIND::JudgeLeftRight(double posx[])
{
  int leftright;
  double aveposx = 0;
  int count = 0;

  for(int ihit=0; ihit<300; ihit++)
    {
      if(posx[ihit]<=-2000) continue;
      aveposx += posx[ihit];
      //cout << "aveposx= " << aveposx << '\n';
      count++;
    }

  aveposx = aveposx/(double)count;
  if(aveposx>+200) 
    leftright = +1;

  else if(aveposx<-200) 
    leftright = -1;
  
  else
    leftright = 0;
  
  //cout << "aveposx= " << aveposx << '\n';
  return leftright;
}

bool BabyMIND::SearchYasuHit(int leftright, double avehittime, vector<int>yasuhittime, vector<int>yasuchannel)
{
  bool findyasuhit = false;
  if(leftright==-1)
    {
      for(int ihit=0; ihit<yasuhittime.size(); ihit++)
	{
	  int theyasuchannel = yasuchannel.at(ihit);
	  if(theyasuchannel<=6) continue;
	  //cout << "leftright= " << leftright << '\n';
	  int theyasutime = yasuhittime.at(ihit);
	  //cout << theyasutime << " " << avehittime << '\n';
	  if(fabs(theyasutime-avehittime)<30)
	    findyasuhit = true;
	}
    }

  if(leftright==1)
    {
      for(int ihit=0; ihit<yasuhittime.size(); ihit++)
	{
	  int theyasuchannel = yasuchannel.at(ihit);
	  if(theyasuchannel>=7) continue;
	  //cout << "leftright= " << leftright << '\n';
	  int theyasutime = yasuhittime.at(ihit);
	  //cout << theyasutime << " " << avehittime << '\n';
	  if(fabs(theyasutime-avehittime)<30)
	    findyasuhit = true;
	}
    }

  return findyasuhit;
}

bool BabyMIND::JudgeFV(double posy[], double posz[])
{
  bool fv = false;
  double aveposy = 0;
  int count = 0;

  for(int ihit=0; ihit<300; ihit++)
    {
      if(posy[ihit]<=-2000) continue;
      if(posz[ihit]>=300) continue;
      aveposy += posy[ihit];
      //cout << "aveposx= " << aveposx << '\n';
      count++;
    }

  aveposy = aveposy/(double)count;
  if(aveposy>=-600 && aveposy<=600)
    fv = true;
  //cout << "aveposx= " << aveposx << '\n';
  return fv;
}
