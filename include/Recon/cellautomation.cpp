#include <iostream>
#include <stdio.h>
#include <time.h>


//#include "DetCluster.cpp"
//#include "DetHitCluster.cpp"
#include "Cell.cpp"
#include "cellautomation.hpp"

using namespace std;

//#define debug
//#define beam
#define MC

CellAutomation::CellAutomation()
{ 
  //maxdist      : Range while making cells
  //clusterz(xy) : Range while making clusters

  //Proton Module
  mindist[0] = 20;
  maxdist[0] = 180;
  clusterz[0][0] = 30;
  clusterz[1][0] = 30;
  clusterxy[0][0] = 30;
  clusterxy[1][0] = 30;

  //WAGASCI (upstream)
  mindist[1] = 10;
  maxdist[1] = 130;
  clusterz[0][1] = 30;
  clusterz[1][1] = 30;
  clusterxy[0][1] = 20;
  clusterxy[1][1] = 20;

  //WAGASCI (downstream)
  mindist[2] = 10;
  maxdist[2] = 130;
  clusterz[0][2] = 30;
  clusterz[1][2] = 30;
  clusterxy[0][2] = 20;
  clusterxy[1][2] = 20;

  //WallMRD (north)
  mindist[3] = 50;
  maxdist[3] = 450;
  clusterz[0][3] = 10;
  clusterz[1][3] = 10;
  clusterxy[0][3] = 100;
  clusterxy[1][3] = 100;

  //WallMRD (south)
  mindist[4] = 50;
  maxdist[4] = 450;
  clusterz[1][4] = 10;
  clusterxy[1][4] = 100;

  //Baby MIND
  mindist[5] = 50;
  maxdist[5] = 950;
  clusterz[0][5] = 100;
  clusterz[1][5] = 100;
  clusterxy[0][5] = 70;
  clusterxy[1][5] = 250;
  
  for(int imod=0; imod<5; imod++)
    {
      Chithreshold[imod][0] = 500.;
      Chithreshold[imod][1] = 500.;
    }  

  Chithreshold[5][0] = 1500.;
  Chithreshold[5][1] = 8000.;
  epsilon = 0.01;

  linear= new TF1("linear", "[0]+[1]*x", -500, 4500);
  linear->SetParameters(0, 0);
  fitpaper = new TH1D("fitpaper", "", 500, -500, 4500);

  for(int iview=0; iview<2; iview++)
    for(int ibunch=0; ibunch<9; ibunch++)
      {
	TString histname;
	histname.Form("beforerecon_view%d_bunch%d", iview, ibunch);
	beforerecon[iview][ibunch]  = new TH2D(histname, "", 500, -500, 4500, 200, -1500, 1500);
	histname.Form("midrecon_view%d_bunch%d", iview, ibunch);
	midrecon[iview][ibunch] = new TH2D(histname, "", 500, -500, 4500, 200, -1500, 1500);
	histname.Form("afterrecon_view%d_bunch%d", iview, ibunch);
	afterrecon[iview][ibunch] = new TH2D(histname, "", 500, -500, 4500, 200, -1500, 1500);
	
	Ntrack[iview][ibunch]=0;
	countbunchhit[iview][ibunch]=0;
	
	for(int i=0; i<ncell; i++)
	  cell[iview][ibunch][i] = new Cell();
	
	for(int imod=0; imod<6; imod++)
	  {
	    testcluster[iview][ibunch][imod]= new DetCluster();
	    detclusters[iview][ibunch][imod]= new DetClusters();
	    for(int itrack=0; itrack<30; itrack++)
	      reconcluster[iview][ibunch][imod][itrack] = new DetCluster();
	  }
	
	for(int i=0; i<5000; i++)
	  dethitcluster[iview][i] = new DetHitCluster();

	ataribunch[iview].clear();
	
      }//ibunch
    
}

CellAutomation::~CellAutomation()
{
}

void CellAutomation::CellAutomaton(int targetmod, int view)
{
  for(int ibunch=1; ibunch<9; ibunch++)
    {
      if(countbunchhit[view][ibunch]<=3) continue;
      
      Fillbeforerecon(ibunch, targetmod, view);
      cout << "Clustering" << '\n';
      SetTime();
      Clustering(ibunch, targetmod, view);
      ShowTime();
      for(int icluster=0; icluster<detclusters[view][ibunch][targetmod]->cluster.size(); icluster++)
	{
	  double posz= detclusters[view][ibunch][targetmod]->cluster.at(icluster)->posz;
	  double posy= detclusters[view][ibunch][targetmod]->cluster.at(icluster)->posxy;
	  midrecon[view][ibunch]->Fill(posz, posy);
	}
      cout << "MakeCell" << '\n';
      SetTime();
      if(!MakeCell(ibunch, targetmod, view))
	{
	  cout << "No cell is created." << '\n';
	  continue;
	}
      ShowTime();

      cout << "Search" << '\n';
      SetTime();
      SearchNeiborCell(ibunch, view, targetmod);
      ShowTime();

      cout << "Update" << '\n';      
      SetTime();
      UpdateCellState(ibunch, view);
      ShowTime();
 
      cout << "Recon" << '\n';           
      SetTime();
      Reconstruction(ibunch, targetmod, view);
      ShowTime();

      if(Ntrack[view][ibunch]>=1)
	{
	  ataribunch[view].push_back(ibunch);
	  cout << "view=" << view << '\n';
	}
    }
}

void CellAutomation::ReadData(int targetmod, int targetview, EVTCluster* evtcluster)
{
  for(int ihit=0; ihit<evtcluster->mod.size(); ihit++)
    {
      bool timeclustering = false;
      double posx = evtcluster->dposx.at(ihit);
      double posy = evtcluster->dposy.at(ihit);
      double posz = evtcluster->dposz.at(ihit);
      //double charge = evtcluster->charge.at(ihit);
      //double hittime = evtcluster->Htime.at(ihit);
      double charge = -1.;
      double hittime = -1.;
      int mod = evtcluster->mod.at(ihit);
      int view = evtcluster->view.at(ihit);
      int bunch = evtcluster->bunch.at(ihit);

      
      if(bunch==-1) continue;

#ifdef beam
      if(mod==0 || mod==5)
	unifiedview=targetview;
      if(mod==1 || mod==2)
	unifiedview=fabs(targetview%2-1);
      if(mod==3 || mod==4)
	unifiedview=1;

      if(mod>=1 && mod<=4)
	if(charge<700) continue;
#endif

#ifdef MC
	unifiedview=targetview;
#endif

      if(mod==targetmod && view==targetview)
	{	  
	  dethitcluster[unifiedview][ihit]->posz = posz;
	  dethitcluster[unifiedview][ihit]->posx = posx;
	  dethitcluster[unifiedview][ihit]->posy = posy;
	  dethitcluster[unifiedview][ihit]->HG = charge;
	  dethitcluster[unifiedview][ihit]->Htime = hittime;

	  // cout << "targetview= " << targetview << " posx= " << posx << " posz= " << posz << '\n';

	  /*
	  if(targetmod==5 && view==1)
	    for(int ielement=0; ielement<testcluster[unifiedview][bunch][targetmod]->cluster.size(); ielement++)
	      {
		double reftime = testcluster[unifiedview][bunch][targetmod]->cluster.at(0)->Htime;
		if(fabs(hittime - reftime) < 15)
		  {
		    cout << "reftime= " << reftime << " hittime= " << hittime << '\n';
		    timeclustering = true;
		    break;
		  }
	      }//ielement 

	    if(testcluster[unifiedview][bunch][targetmod]->cluster.size()==0)
	      timeclustering = true;

	    if(targetmod==5 && view==1 && !timeclustering)
	      continue;
	  */
	    
	    testcluster[unifiedview][bunch][targetmod]->cluster.push_back(dethitcluster[unifiedview][ihit]);
	    countbunchhit[unifiedview][bunch]++;
	}  
    }
 
  //for(int bunch=1; bunch<=8; bunch++)
  // cout << "countbunchhit[bunch]= " << countbunchhit[unifiedview][bunch] << '\n';
}

void CellAutomation::Fillbeforerecon(int bunch, int targetmod, int view)
{
  double posxy;
  for(int ihit=0; ihit<testcluster[view][bunch][targetmod]->cluster.size(); ihit++)
    {
      double posz = testcluster[view][bunch][targetmod]->cluster.at(ihit)->posz;
      if(view==0)
	posxy = testcluster[view][bunch][targetmod]->cluster.at(ihit)->posy;
      if(view==1)
	posxy = testcluster[view][bunch][targetmod]->cluster.at(ihit)->posx;
      beforerecon[view][bunch]->Fill(posz, posxy);
    }
}

void CellAutomation::Clustering(int bunch, int targetmod, int view)
{
  DetHitClusters* dethitclusters[1000];
  for(int i=0; i<1000; i++)
    dethitclusters[i] = new DetHitClusters();
  int clustercount=0;
  double refposxy;
  double posxy;
  
  for(int ihit=0; ihit<testcluster[view][bunch][targetmod]->cluster.size(); ihit++)
    {
      bool clustering = false;
      double posz = testcluster[view][bunch][targetmod]->cluster.at(ihit)->posz;
      double trytime = testcluster[view][bunch][targetmod]->cluster.at(ihit)->Htime;

      if(view==0)
	posxy = testcluster[view][bunch][targetmod]->cluster.at(ihit)->posy;
      if(view==1)
	posxy = testcluster[view][bunch][targetmod]->cluster.at(ihit)->posx;

      if(ihit==0)
	{
	  dethitclusters[0]->cluster.push_back(testcluster[view][bunch][targetmod]->cluster.at(ihit));
	  clustercount++;
	}
	
      if(ihit>=1)
	{
	  for(int icluster=0; icluster<clustercount; icluster++)
	    {
	      for(int ielement=0; ielement<dethitclusters[icluster]->cluster.size(); ielement++)
		{
		  double refposz = dethitclusters[icluster]->cluster.at(ielement)->posz;
		  double reftime = dethitclusters[icluster]->cluster.at(ielement)->Htime;
		  if(view==0)
		    refposxy = dethitclusters[icluster]->cluster.at(ielement)->posy;
		  if(view==1)
		    refposxy = dethitclusters[icluster]->cluster.at(ielement)->posx;
		  
		  if((fabs(posz-refposz) < clusterz[view][targetmod]) && (fabs(posxy-refposxy)<clusterxy[view][targetmod]))
		    {		      
		      clustering = true;
		      break;
		    }
		}//ielement

	      if(clustering && ihit>=1)
		{
		  dethitclusters[icluster]->cluster.push_back(testcluster[view][bunch][targetmod]->cluster.at(ihit));
		  break;
		}
	    }//icluster
	}//ihit condition

      if(!clustering && ihit>=1)
	{
	  dethitclusters[clustercount]->cluster.push_back(testcluster[view][bunch][targetmod]->cluster.at(ihit));
	  clustercount++;
	}
    }//ihit

  for(int icluster=0; icluster<clustercount; icluster++)
    {
      double avez=0;
      double avexy=0;
      int Nelement = dethitclusters[icluster]->cluster.size();
      for(int ielement=0; ielement<Nelement; ielement++)
	{
	  avez += dethitclusters[icluster]->cluster.at(ielement)->posz/Nelement;
	  if(view==0)
	    avexy += dethitclusters[icluster]->cluster.at(ielement)->posy/Nelement;
	  if(view==1)
	    avexy += dethitclusters[icluster]->cluster.at(ielement)->posx/Nelement;
	}

      dethitclusters[icluster]->posz = avez;
      dethitclusters[icluster]->posxy = avexy;
      detclusters[view][bunch][targetmod]->cluster.push_back(dethitclusters[icluster]);
    }//icluster  
}

bool CellAutomation::MakeCell(int bunch, int targetmod, int view)
{
  bool makecell = false;
  cellcount=0;
  for(int icell=0; icell<ncell; icell++)
      cell[view][bunch][icell]->Clear();
  
  for(int ihit1=0; ihit1<detclusters[view][bunch][targetmod]->cluster.size()-1; ihit1++)
    for(int ihit2=ihit1+1; ihit2<detclusters[view][bunch][targetmod]->cluster.size(); ihit2++)
      if(fabs(detclusters[view][bunch][targetmod]
	      ->cluster.at(ihit1)->posz-detclusters[view][bunch][targetmod]->cluster.at(ihit2)->posz)<maxdist[targetmod] &&
	 fabs(detclusters[view][bunch][targetmod]
	      ->cluster.at(ihit1)->posz-detclusters[view][bunch][targetmod]->cluster.at(ihit2)->posz)>mindist[targetmod])
	{
	  cell[view][bunch][cellcount]->dethitclusters[0] = detclusters[view][bunch][targetmod]->cluster.at(ihit1);	 
	  cell[view][bunch][cellcount]->dethitclusters[1] = detclusters[view][bunch][targetmod]->cluster.at(ihit2);
	  cell[view][bunch][cellcount]->state=0;
	  cell[view][bunch][cellcount]->idcard=cellcount;
	  
	  cell[view][bunch][cellcount]->meanposz 
	    = (detclusters[view][bunch][targetmod]->cluster.at(ihit1)->posz 
	       + detclusters[view][bunch][targetmod]->cluster.at(ihit2)->posz)/2;
	  
	  cell[view][bunch][cellcount]->meanposxy 
	    = (detclusters[view][bunch][targetmod]->cluster.at(ihit1)->posxy 
	       + detclusters[view][bunch][targetmod]->cluster.at(ihit2)->posxy)/2;

	  //cout << "meanposz= " << cell[view][bunch][cellcount]->meanposz << " meanposy = " << cell[view][bunch][cellcount]->meanposxy << '\n';

	  cellcount++;
	}
      
  cout << "cellcount= " << cellcount << '\n';
  if(cellcount>0)
    makecell = true;

  /*
  for(int i=0; i<cellcount; i++)
    {
      cout << cell[view][bunch][i]->dethitclusters[0]->posz << " " << cell[view][bunch][i]->dethitclusters[1]->posz  << '\n';
      cout << cell[view][bunch][i]->state << '\n';
      cout << cell[view][bunch][i]->idcard << '\n';
      cout << cell[view][bunch][i]->meanposz << '\n';
      cout << cell[view][bunch][i]->meanposxy << '\n';
    }
  */
 
 
#ifdef debug
  for(int i=0; i<cellcount; i++)
    {
      cout << cell[view][bunch][i]->dethitclusters[0]->posz << " " << cell[view][bunch][i]->dethitclusters[1]->posz  << '\n';
      cout << cell[view][bunch][i]->state << '\n';
      cout << cell[view][bunch][i]->idcard << '\n';
      cout << cell[view][bunch][i]->meanposz << '\n';
      cout << cell[view][bunch][i]->meanposxy << '\n';
    }
#endif 

  return makecell;
}

void CellAutomation::SearchNeiborCell(int bunch, int view, int mod)
{
  double posxy1[2], posxy2[2], posz1[2], posz2[2];
  for(int icell1=0; icell1<cellcount-1; icell1++)
    for(int icell2=icell1+1; icell2<cellcount; icell2++)
      {
	for(int i=0; i<2; i++)
	  {
	    int icell;
	    if(i==0) icell = icell1;
	    if(i==1) icell = icell2;

	    posxy1[i] = cell[view][bunch][icell]->dethitclusters[0]->posxy;
	    posxy2[i] = cell[view][bunch][icell]->dethitclusters[1]->posxy;
	    posz1[i]  = cell[view][bunch][icell]->dethitclusters[0]->posz;
	    posz2[i]  = cell[view][bunch][icell]->dethitclusters[1]->posz;
	  }       

	//cout << "icell1= " << icell1 << " icell2= " << icell2 << '\n';
	
	if(!SearchCommonCell(cell[view][bunch][icell1], cell[view][bunch][icell2]))
	   continue;

	//cout << "Chi= " << GetChisquare(posz1, posz2, posxy1, posxy2) << '\n';

	if(GetChisquare(posz1, posz2, posxy1, posxy2)<Chithreshold[mod][view])
	  {
	    if(cell[view][bunch][icell1]->meanposz > cell[view][bunch][icell2]->meanposz)
	      {
		cell[view][bunch][icell1]->upneibor.push_back(cell[view][bunch][icell2]->idcard);
		cell[view][bunch][icell2]->downneibor.push_back(cell[view][bunch][icell1]->idcard);
	      }

	    if(cell[view][bunch][icell1]->meanposz <= cell[view][bunch][icell2]->meanposz)
	      {
		cell[view][bunch][icell1]->downneibor.push_back(cell[view][bunch][icell2]->idcard);
		cell[view][bunch][icell2]->upneibor.push_back(cell[view][bunch][icell1]->idcard);
	      }
	  }
      }//icell

  fitpaper->Clear();
  
#ifdef debug
  for(int i=0; i<cellcount; i++)
    {
      if(cell[view][bunch][i]->downneibor.size()>=1)
	{
	  cout << "i= " << i << " " << cell[view][bunch][i]->meanposz << " " << cell[view][bunch][i]->downneibor.size() << " " 
	       << cell[view][bunch][i]->upneibor.size() << " downneibor= " << cell[view][bunch][i]->downneibor.at(0)  << '\n';
	  cout << cell[view][bunch][i]->dethitclusters[0]->posxy << " " << cell[view][bunch][i]->dethitclusters[1]->posxy << '\n';
	}
    }
#endif 
}

double CellAutomation::GetChisquare(double posz1[], double posz2[], double posxy1[], double posxy2[])
{
  
  double chi;
  vector<double> posz[2], posxy[2];
  double meanposz[2];
  for(int i=0; i<2; i++)
    {
      posz[i].push_back(posz1[i]);
      posz[i].push_back(posz2[i]);
      posxy[i].push_back(posxy1[i]);
      posxy[i].push_back(posxy2[i]);
      meanposz[i] = (posz1[i]+posz2[i])/2.;
      //graposz[0+i*2] = posz1[i];
      //graposz[1+i*2] = posz2[i];
      //graposxy[0+i*2] = posxy1[i];
      //graposxy[1+i*2] = posxy2[i];
    }

  if(meanposz[0] >= meanposz[1])
    {
      auto minit = std::min_element(posz[0].begin(), posz[0].end());
      auto maxit = std::max_element(posz[0].begin(), posz[0].end());
      int minid1 = minit - posz[0].begin();
      int maxid1 = maxit - posz[0].begin();
      minit = std::min_element(posz[1].begin(), posz[1].end());
      int minid2 = minit - posz[1].begin();

      graposz[0] = posz[1].at(minid2);
      graposz[1] = posz[0].at(minid1);
      graposz[2] = posz[0].at(maxid1);      

      graposxy[0] = posxy[1].at(minid2);
      graposxy[1] = posxy[0].at(minid1);
      graposxy[2] = posxy[0].at(maxid1);      
    }

  if(meanposz[0] < meanposz[1])
    {
      auto minit = std::min_element(posz[1].begin(), posz[1].end());
      auto maxit = std::max_element(posz[1].begin(), posz[1].end());
      int minid1 = minit - posz[1].begin();
      int maxid1 = maxit - posz[1].begin();
      minit = std::min_element(posz[0].begin(), posz[0].end());
      int minid2 = minit - posz[0].begin();

      graposz[0] = posz[0].at(minid2);
      graposz[1] = posz[1].at(minid1);
      graposz[2] = posz[1].at(maxid1);      

      graposxy[0] = posxy[0].at(minid2);
      graposxy[1] = posxy[1].at(minid1);
      graposxy[2] = posxy[1].at(maxid1);     
    }

  //cout << graposz[0] << " " << graposz[1] << " " << graposz[2] << '\n';
  //cout << graposxy[0] << " " << graposxy[1] << " " << graposxy[2] << '\n';  

  fitgraph = new TGraph(3, graposz, graposxy);
  fitgraph->Fit(linear, "Q");
  chi=linear->GetChisquare();
  return chi;
}

bool CellAutomation::SearchCommonCell(Cell* cell1, Cell* cell2)
{
  bool commoncell = false;
  vector<double> position1, position3;
  vector<double> position2, position4;
  position1.clear();
  position2.clear();
  position3.clear();
  position4.clear();
  double minz, maxz;
  int minzid, maxzid;
  double minxy, maxxy;

  if(cell1->meanposz > cell2->meanposz)
    {
      position1.push_back(cell1->dethitclusters[0]->posz);
      position1.push_back(cell1->dethitclusters[1]->posz);      
      position2.push_back(cell2->dethitclusters[0]->posz);
      position2.push_back(cell2->dethitclusters[1]->posz);
      minz = *std::min_element(position1.begin(), position1.end());
      maxz = *std::max_element(position2.begin(), position2.end());
      auto minzit = std::min_element(position1.begin(), position1.end());
      minzid = minzit - position1.begin();
      auto maxzit = std::max_element(position2.begin(), position2.end());
      maxzid = maxzit - position2.begin();

      position3.push_back(cell1->dethitclusters[0]->posxy);
      position3.push_back(cell1->dethitclusters[1]->posxy);      
      position4.push_back(cell2->dethitclusters[0]->posxy);
      position4.push_back(cell2->dethitclusters[1]->posxy);
      minxy = position3.at(minzid);
      maxxy = position4.at(maxzid);
    }

  if(cell1->meanposz <= cell2->meanposz)
    {
      position1.push_back(cell1->dethitclusters[0]->posz);
      position1.push_back(cell1->dethitclusters[1]->posz);      
      position2.push_back(cell2->dethitclusters[0]->posz);
      position2.push_back(cell2->dethitclusters[1]->posz);
      minz = *std::min_element(position2.begin(), position2.end());
      maxz = *std::max_element(position1.begin(), position1.end());
      auto minzit = std::min_element(position2.begin(), position2.end());
      minzid = minzit - position2.begin();
      auto maxzit = std::max_element(position1.begin(), position1.end());
      maxzid = maxzit - position1.begin();

      position3.push_back(cell1->dethitclusters[0]->posxy);
      position3.push_back(cell1->dethitclusters[1]->posxy);      
      position4.push_back(cell2->dethitclusters[0]->posxy);
      position4.push_back(cell2->dethitclusters[1]->posxy);
      maxxy = position3.at(maxzid);
      minxy = position4.at(minzid);
    }

  

  //cout << "minz= " << minz << " maxz= " << maxz << '\n';
  //cout << "minxy= " << minxy << " maxxy= " << maxxy << '\n';
  
  if(fabs(maxz-minz) < epsilon && fabs(maxxy-minxy) < epsilon)
  //if(fabs(maxz-minz) < epsilon)
    commoncell = true;  
      
      return commoncell;
}


void CellAutomation::UpdateCellState(int bunch, int view)
{
  vector<int> successcell;
  stategroup_sort.clear();
  stategroup.clear();
  idcardgroup.clear();
  bool breakflag = false;
  
  for(int istep=0; istep<50; istep++)
    {
      successcell.clear();
      for(int icell=0; icell<cellcount; icell++)
	{
	  int thestate = cell[view][bunch][icell]->state;
	  for(int inei=0; inei<cell[view][bunch][icell]->downneibor.size(); inei++)
	    {
	      int neiboring = cell[view][bunch][icell]->downneibor.at(inei);
	      int neiborstate = cell[view][bunch][neiboring]->state;
	      if(thestate==neiborstate)
		successcell.push_back(neiboring);
	    }//inei
	}

      std::sort(successcell.begin(), successcell.end());
      auto last = std::unique(successcell.begin(), successcell.end());
      successcell.erase(last, successcell.end());

      if(successcell.size()==0)
	breakflag = true;
      
      for(int icell=0; icell<successcell.size(); icell++)
	{
	  cell[view][bunch][successcell.at(icell)]->state++;	    
	}
      
#ifdef debug
      for(int icell=0; icell<cellcount; icell++)
	{
	  cout << "icell= " << icell << " state= " << cell[view][bunch][icell]->state
	       << " posz= " << cell[view][bunch][icell]->dethitclusters[0]->posz 
	       << " posz= " << cell[view][bunch][icell]->dethitclusters[1]->posz 
	       << " posy= " << cell[view][bunch][icell]->dethitclusters[0]->posxy 
	       << " posy= " << cell[view]bunch][icell]->dethitclusters[1]->posxy 
	       << " upsize= " << cell[view][bunch][icell]->upneibor.size()
	       << " downsize= " << cell[view][bunch][icell]->downneibor.size()
	       << " StateSize= " << stategroup.size() << '\n'; 
	}
#endif 

      if(breakflag) break;
    }//istep


/*
  for(int icell=0; icell<cellcount; icell++)
    {     
       
      cout << "icell= " << icell << " state= " << cell[view][bunch][icell]->state
	   << " posz= " << cell[view][bunch][icell]->dethitclusters[0]->posz 
	   << " posz= " << cell[view][bunch][icell]->dethitclusters[1]->posz 
	   << " posxy= " << cell[view][bunch][icell]->dethitclusters[0]->posxy 
	   << " posxy= " << cell[view][bunch][icell]->dethitclusters[1]->posxy 
	   << " upsize= " << cell[view][bunch][icell]->upneibor.size()
	   << " downsize= " << cell[view][bunch][icell]->downneibor.size() << '\n';
         
      for(int inei=0; inei<cell[view][bunch][icell]->upneibor.size(); inei++)
	cout << "Upneibor= " << cell[view][bunch][icell]->upneibor.at(inei) << '\n';      
    }
*/


  for(int icell=0; icell<cellcount; icell++)  
    {
      stategroup_sort.push_back(cell[view][bunch][icell]->state);
      stategroup.push_back(cell[view][bunch][icell]->state);
      idcardgroup.push_back(cell[view][bunch][icell]->idcard);
    }
}


void CellAutomation::Reconstruction(int bunch, int targetmod, int view)
{
  int counttrack=0;
  eliminategroup.clear();
  safetycount=0;

  while(1)
    {
      stategroup_sort.clear();      
      //Eliminate
      for(int icell=0; icell<cellcount; icell++)
	{
	  int num = idcardgroup.at(icell);
	  auto it = std::find(eliminategroup.begin(), eliminategroup.end(), num);
	  if( it == eliminategroup.end())
	    {
	      stategroup_sort.push_back(stategroup.at(icell));
	    }
	}
      
      maxstatecell.clear();
      
      std::sort(stategroup_sort.begin(), stategroup_sort.end());
      auto last = std::unique(stategroup_sort.begin(), stategroup_sort.end());
      stategroup_sort.erase(last, stategroup_sort.end());
      maxstate = *std::max_element(stategroup_sort.begin(), stategroup_sort.end());
      cout << "maxstate= " << maxstate << '\n';
      if(maxstate<=2) break;
      
      for(int icell=0; icell<cellcount; icell++)
	{
	  int num = idcardgroup.at(icell);
	  auto it = std::find(eliminategroup.begin(), eliminategroup.end(), num);
	  if( it == eliminategroup.end())
	    if(cell[view][bunch][icell]->state == maxstate)
	      maxstatecell.push_back(cell[view][bunch][icell]->idcard);
	}
      
      if(maxstatecell.size()>=1)
	{
	  for(int imaxstate=0; imaxstate<maxstatecell.size(); imaxstate++)
	    {	  
	      eliminatesubgroup.clear();
	      int iprocess=0;
	      eliminategroup.push_back(maxstatecell.at(imaxstate));
	      while(1)
		{
		  if(iprocess==0) 
		    {
		      basecell = maxstatecell.at(imaxstate);
		    }
		  if(iprocess>=1) 
		    {
		      basecell = nextcell;
		    }
		  
		  currentstate = cell[view][bunch][basecell]->state;
		  
		  //cout << "iprocess= " << iprocess << " basecell= " << basecell << " currentstate= " << currentstate  << '\n';
		  
		  vector<double> position1;
		  position1.clear();
		  position1.push_back(cell[view][bunch][basecell]->dethitclusters[0]->posz);
		  position1.push_back(cell[view][bunch][basecell]->dethitclusters[1]->posz);
		  double minposz = *std::min_element(position1.begin(), position1.end());
		  auto basecellit = std::max_element(position1.begin(), position1.end());
		  int basecellid = basecellit - position1.begin();
		  
		  int ncell = cell[view][bunch][basecell]->upneibor.size();

		  //cout << "ncell= " << ncell << '\n';
		  
		  if(ncell==0)
		    {
		      reconcluster[view][bunch][targetmod][counttrack]->cluster.clear();
		      break;
		    }
		  
		  vector<double> position2;
		  position2.clear();
		  
		  for(int icell=0; icell<ncell; icell++)
		    {
		      vector<double> temp;
		      temp.clear();
		      int thecell = cell[view][bunch][basecell]->upneibor.at(icell);
		      eliminatesubgroup.push_back(cell[view][bunch][thecell]->idcard);
		      if(cell[view][bunch][thecell]->state != currentstate-1)
			{
			  //cout << "state unmatching" << '\n';
			  position2.push_back(9999);
			  continue;
			}
		      
		      auto it = std::find(eliminategroup.begin(), eliminategroup.end(), thecell);
		      if( it != eliminategroup.end() && cell[view][bunch][thecell]->state >=1)
			//if( it != eliminategroup.end())
			{
			  //cout << "eliminate" << '\n';
			  position2.push_back(9999);
			  continue;
			}
		  
		      //cout << "thecell= " << thecell << '\n';
		      temp.push_back(cell[view][bunch][thecell]->dethitclusters[0]->posz);
		      temp.push_back(cell[view][bunch][thecell]->dethitclusters[1]->posz);
		      
		      double thecellz = minposz - *std::min_element(temp.begin(), temp.end());
		      auto posit = find(position2.begin(), position2.end(), thecellz);
		      /*
		      for(int i=0; i<position2.size(); i++)
			{
			  cout << thecellz  << " "  << position2.at(i) << '\n';
			}
		      */
		      
		      if(posit != position2.end())
			{
			  int pos = posit - position2.begin();
			  int anothercell = cell[view][bunch][basecell]->upneibor.at(pos);
			  //cout << "find the same z position" << '\n';
			  double posytrydif = fabs(cell[view][bunch][thecell]->meanposxy - cell[view][bunch][basecell]->meanposxy);
			  double posyrefdif = fabs(cell[view][bunch][anothercell]->meanposxy - cell[view][bunch][basecell]->meanposxy);
			  if(posytrydif < posyrefdif)
			    {
			      /*
			      cout << "comparison "  << posytrydif << " " << posyrefdif << '\n';
			      cout << "cell[thecell]= " << cell[view][bunch][thecell]->meanposxy 
				   << "cell[anothercell]= " << cell[view][bunch][anothercell]->meanposxy 
				   << " cell[basecell]= " << cell[view][bunch][basecell]->meanposxy << '\n';
			      */
			      *posit = 9999;
			    }
			  
			  if(posytrydif >= posyrefdif)
			    {
			      /*
			      cout << "comparison "  << posytrydif << " " << posyrefdif << '\n';
			      cout << "cell[bunch][thecell]= " << cell[view][bunch][thecell]->meanposxy 
				   << "cell[bunch][anothercell]= " << cell[view][bunch][anothercell]->meanposxy 
				   << " cell[bunch][basecell]= " << cell[view][bunch][basecell]->meanposxy << '\n';
			      */			      
			      thecellz = 9999;
			    }
			}
		      
		      position2.push_back(thecellz);
		    }//icell
	      
	      ncell = cell[view][bunch][basecell]->downneibor.size();
	      for(int icell=0; icell<ncell; icell++)
		{
		  int thecell = cell[view][bunch][basecell]->downneibor.at(icell);
		  eliminatesubgroup.push_back(cell[view][bunch][thecell]->idcard);
		}
	      
	      auto trycellit = std::min_element(position2.begin(), position2.end());
	      int trycellid = trycellit - position2.begin();
	      int trycell = cell[view][bunch][basecell]->upneibor.at(trycellid);
	      
	      //cout << "trycell= " << trycell <<  " position= "  << *trycellit  << '\n';
	      
	      if(*trycellit==9999)
		{
		  reconcluster[view][bunch][targetmod][counttrack]->cluster.clear();
		  break;
		}
	      
	      vector<double> position3;
	      position3.clear();
	      position3.push_back(cell[view][bunch][trycell]->dethitclusters[0]->posz);
	      position3.push_back(cell[view][bunch][trycell]->dethitclusters[1]->posz);
	      double maxposz = *std::max_element(position3.begin(), position3.end());
	      
	      //cout << "minposz= " << minposz << " maxposz= " << maxposz << '\n';
	      
	      if(fabs(minposz-maxposz)<epsilon)
		{
		  nextcell = cell[view][bunch][basecell]->upneibor.at(trycellid);
		  //cout << "nextcell= " << nextcell << " cell[bunch][nextcell]->state"  
		  //<< cell[view][bunch][nextcell]->state  <<  '\n';
		  if(cell[view][bunch][nextcell]->state != cell[view][bunch][basecell]->state-1)
		    {
		      reconcluster[view][bunch][targetmod][counttrack]->cluster.clear();
		      break;
		    }

		  if(cell[view][bunch][nextcell]->state==0)
		    {
		      for(int i=0; i<cell[view][bunch][basecell]->dethitclusters[basecellid]->cluster.size(); i++)
			reconcluster[view][bunch][targetmod][counttrack]
			  ->cluster.push_back(cell[view][bunch][basecell]->dethitclusters[basecellid]->cluster.at(i));
		      for(int i=0; i<cell[view][bunch][nextcell]->dethitclusters[0]->cluster.size(); i++)
			reconcluster[view][bunch][targetmod][counttrack]
			  ->cluster.push_back(cell[view][bunch][nextcell]->dethitclusters[0]->cluster.at(i));
		      for(int i=0; i<cell[view][bunch][nextcell]->dethitclusters[1]->cluster.size(); i++)
			reconcluster[view][bunch][targetmod][counttrack]
			  ->cluster.push_back(cell[view][bunch][nextcell]->dethitclusters[1]->cluster.at(i));
		      //cout << "CLUSTER SIZE= " << reconcluster[view][bunch][targetmod][counttrack]->cluster.size() 
		      //	   << "******************************************************" << '\n';
  		      counttrack++;
		      for(int i=0; i<eliminatesubgroup.size(); i++)
			{
			  eliminategroup.push_back(eliminatesubgroup.at(i));
			  //cout << "Eliminate " << eliminatesubgroup.at(i) << '\n';
			}
		      break;
		    }
		  
		  for(int i=0; i<cell[view][bunch][basecell]->dethitclusters[basecellid]->cluster.size(); i++)
		    {
		      //cout << "i= " << i << " " << cell[view][bunch][basecell]->dethitclusters[basecellid]->cluster.size() << '\n';
		      //cout << "bunch= " << bunch << " targetmod= " << targetmod << '\n';
		      //cout << "value= " << cell[view][bunch][basecell]->dethitclusters[basecellid]->cluster.at(i)->posz << '\n';
		      reconcluster[view][bunch][targetmod][counttrack]
			->cluster.push_back(cell[view][bunch][basecell]->dethitclusters[basecellid]->cluster.at(i));
		    }

		}//fabs condition
	      
	      iprocess++;
	      if(iprocess>=100)
		break;
	      
	    }//while
	}//imaxstate
    }//maxstatesize
      
#ifdef debug
      for(int i=0; i<eliminategroup.size(); i++)
	cout << "Eliminate List : " <<  eliminategroup.at(i) << '\n';
#endif
      
      safetycount++;
      if(safetycount>=1000)
	{
	  cout << "something wrong with this event" << '\n';
	  break;
	}
    }//while
  
  Ntrack[view][bunch] = counttrack;
  cout << "Ntrack= " << Ntrack[view][bunch] << '\n';
}

void CellAutomation::SetTime()
{
  start = clock();
}
void CellAutomation::ShowTime()
{
  end = clock();
  const double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
  printf("time %lf[ms]\n", time);
}

void CellAutomation::Clear()
{
  for(int iview=0; iview<2; iview++)
    {
      for(int ibunch=0; ibunch<9; ibunch++)
	{
	  beforerecon[iview][ibunch]->Reset();
	  midrecon[iview][ibunch]->Reset();
	  afterrecon[iview][ibunch]->Reset();
	  
	  Ntrack[iview][ibunch]=0;
	  countbunchhit[iview][ibunch]=0;
	  
	  for(int i=0; i<ncell; i++)
	    cell[iview][ibunch][i]->Clear();
	  
	  for(int imod=0; imod<6; imod++)
	    {
	      testcluster[iview][ibunch][imod]->Clear();
	      detclusters[iview][ibunch][imod]->Clear();
	      for(int itrack=0; itrack<30; itrack++)
		reconcluster[iview][ibunch][imod][itrack]->Clear();
	    }
	  
	}//ibunch

      for(int i=0; i<5000; i++)
	dethitcluster[iview][i]->Clear();
      
      ataribunch[iview].clear();

    }//iview

}
