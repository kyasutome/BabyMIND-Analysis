#include <iostream>
#include <fstream>
#include <vector>

#include <BSDApply.hpp>

using namespace std;
//#define debug

BSDApply::BSDApply()
{
  //bsddir.Form("./bsd/t2krun10"); // BSD
  bsddir.Form("../Beamdata/qsd/t2krun10"); // QSD
  bsdchain = new TChain("bsd", "bsd");
  //startrun = 830115;
  //endrun = 830493;
  startrun = 840003;
  endrun = 840162;
  startsub = 0;
  endsub = 50;

  for(int i=0; i<2; i++)
    for(int j=0; j<100; j++)
      {
	bmgroup[j][i].clear();
	pmgroup[j][i].clear();
	wggroup[j][i].clear();
      }
  
  for(int i=0; i<3; i++)
    beamgroup[i].clear();

  baseunixtime.clear();
  matchingspill.clear(); 
  bmspill.clear();
  pmspill.clear();
  wgspill.clear();
}

BSDApply::~BSDApply()
{
}

void BSDApply::ReadBSDfile()
{
  for(int irun=startrun; irun<endrun; irun++)
    {
      for(int isub=startsub; isub<endsub; isub++)
        {
	  //filename.Form("%s/bsd_run%07d_%02dv01.root", bsddir.Data(), irun, isub);//BSD
          filename.Form("%s/bsd_run%07d_%02dp06.root", bsddir.Data(), irun, isub); // QSD
          if (gSystem->GetPathInfo(filename.Data(), info)!=0)
            {
              continue;
            }else{
            bsdchain->Add(filename);
          }
        }//isub 
    }//irun

  bsdchain->SetBranchAddress("spillnum", &spillnum);
  bsdchain->SetBranchAddress("trg_sec", trg_sec);
  bsdchain->SetBranchAddress("ct_np", ct_np);

  cout << "BSD entries = " << bsdchain->GetEntries() << '\n';
}

void BSDApply::GetMonDateHour(time_t unixtime, int* Mon, int* Date, int* Hour)
{
  timer = localtime(&unixtime);
  *Mon = timer->tm_mon+1;
  *Date = timer->tm_mday;
  *Hour = timer->tm_hour;
  //cout << *Mon << " " << *Date << " " << *Hour << '\n';
}

void BSDApply::FindFirstSpill(int *detfirstspill, int detmon, int detdate, int dethour, int mod)
{
  bool firstcheck = false;
  bool finish = false;
  int Mon, Date, Hour;

  firstcheck = CheckMainteDay(detmon, detdate, detfirstspill, mod);
    
  for(int ibsd=0; ibsd<bsdchain->GetEntries(); ibsd++)
    {
      bsdchain->GetEntry(ibsd);
      thebeamtime = trg_sec[2];
      thebeamspill = spillnum & 0x7fff;
      GetMonDateHour(thebeamtime, &Mon, &Date, &Hour);
      if(Mon!=detmon || Date!=detdate || Hour!=dethour)
	continue;
      else if(!firstcheck && Mon==detmon && Date==detdate && Hour==dethour)
	firstcheck = true;
      else if(firstcheck && Mon==detmon && Date==detdate && Hour==dethour)
	{
	  cout << "beamspill= " << thebeamspill << '\n';
	  if(CheckDetSpill(*detfirstspill, thebeamspill))
	    {
	      firstmatchspillentry = ibsd;
	      finish = true;
	      break;
	    }
	  
	}
    }
  cout << "firstmatchspillentry= " << firstmatchspillentry << '\n';
  cout << "FirstMatchSpill= " << thebeamspill << " = " << *detfirstspill << '\n';
}

void BSDApply::MakeBeamGroup(int isub)
{
  for(int i=0; i<3; i++)
    beamgroup[i].clear();

  //int startentry = firstmatchspillentry + isub*nsubdata;
  int startentry = firstmatchspillentry + isub*900;
  for(int ibsd=startentry; ibsd<startentry+dayspill; ibsd++)
    {
      bsdchain->GetEntry(ibsd);
      thebeamspill = spillnum & 0x7fff;
      beamgroup[0].push_back(thebeamspill);
      beamgroup[1].push_back(trg_sec[2]);
      beamgroup[2].push_back(ct_np[4][0]);
    }
}

void BSDApply::SpillMatch(int isub, int mod)
{
  matchingspill.clear();
  vector<double> beamgroup_s = beamgroup[0];
  vector<double> detgroup_s;

  if(mod==0) detgroup_s = pmgroup[isub][0];  
  if(mod==1) detgroup_s = wggroup[isub][0];  
  if(mod==5) detgroup_s = bmgroup[isub][0];

  sort(beamgroup_s.begin(), beamgroup_s.end());
  sort(detgroup_s.begin(), detgroup_s.end());
  set_intersection(detgroup_s.begin(), detgroup_s.end(),
                   beamgroup_s.begin(), beamgroup_s.end(),
                   inserter(matchingspill, matchingspill.end()));

}

void BSDApply::FillBSD(TTree* tree, TTree* otree, BMBSD* bmbsd, int mod)
{
  for(int ispill=0; ispill<matchingspill.size(); ispill++)
    {
      thebeamspill = matchingspill.at(ispill);
      auto thespillit = find(beamgroup[0].begin(), beamgroup[0].end(), thebeamspill);
      thebeamspill = thespillit - beamgroup[0].begin();
      bmbsd->unixtime = beamgroup[1].at(thebeamspill);
      bmbsd->pot = beamgroup[2].at(thebeamspill);   

      if(mod==0)
	{
	  thebeamspill = matchingspill.at(ispill);
	  thespillit = find(pmspill.begin(), pmspill.end(), thebeamspill);
	  thepmspill = thespillit - pmspill.begin();
	  tree->GetEntry(thepmspill);
	}

      if(mod==1)
	{
	  thebeamspill = matchingspill.at(ispill);
	  thespillit = find(wgspill.begin(), wgspill.end(), thebeamspill);
	  thewgspill = thespillit - wgspill.begin();
	  tree->GetEntry(thewgspill);
	}

      if(mod==5)
	{
	  thebeamspill = matchingspill.at(ispill);
	  thespillit = find(bmspill.begin(), bmspill.end(), thebeamspill);
	  thebmspill = thespillit - bmspill.begin();
	  tree->GetEntry(thebmspill);
	}

      otree->Fill();
    }

}


bool BSDApply::CheckDetTime(time_t unixtime, int mon, int date, int hour)
{
  bool matching = false;

  int Mon, Date, Hour;
  GetMonDateHour(unixtime, &Mon, &Date, &Hour);
  if(Mon==mon && Date==date && Hour==hour)
    matching = true;

  return matching;
}


bool BSDApply::CheckDetSpill(int detectorspill, int beamspill)
{
  bool matching = false;
  if(detectorspill == beamspill)
    matching = true;

  return matching;
}

bool BSDApply::CheckMainteDay(int Mon, int Date, int *detfirstspill, int mod)
{
  bool maintecheck = false;
  
  if(Mon==12 && Date==4) 
    {
      *detfirstspill = 12347;
      maintecheck = true;
    }

  if(Mon==1 && Date==29 && mod==5) 
    {
      *detfirstspill = 20350;
      maintecheck = true;
    }

  return maintecheck;

}

void BSDApply::KillAll()
{
  bsdchain->Delete();
}
