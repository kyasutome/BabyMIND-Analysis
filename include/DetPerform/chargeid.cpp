#include <iostream>
#include <fstream>
#include <vector>

#include "chargeid.hpp"

using namespace std;
//#define debug

ChargeID::ChargeID()
{
  for(int i=0; i<19; i++)
    detector_module_z[i] = detector_module_z[i]*10;

  for(int i=0; i<33; i++)
    iron_module_z[i] = iron_module_z[i]*10;

  gap[0] = 0;
  gap[1] = 0;
  gap[2] = (detector_module_z[3]-detector_module_z[2])*cm;
  gap[3] = 0;
  gap[4] = 0;
  gap[5] = (detector_module_z[6]-iron_module_z[5])*cm;
  gap[6] = 0;
  gap[7] = (detector_module_z[8]-iron_module_z[9])*cm;
  gap[8] = 0;
  gap[9] = (detector_module_z[10]-iron_module_z[13])*cm;
  gap[10] = 0;
  gap[11] = (detector_module_z[12]-detector_module_z[11])*cm;
  gap[12] = 0;
  gap[13] = (detector_module_z[14]-detector_module_z[13])*cm;
  gap[14] = (detector_module_z[15]-iron_module_z[24])*cm;
  gap[15] = 0;
  gap[16] = (iron_module_z[29]-detector_module_z[16])*cm;
  gap[17] = 0;

  for(int i=0; i<18; i++)
    {
      if(i==0)
	B[0]=-1;
      if(1<=i && i<=16)
	//B[i] = (magnet[i]*31)/(magnet[i]*31 + gap[i] + (magnet[i]-1)*10)*B_default;
	B[i] = (magnet[i]*31)/(magnet[i]*31 + gap[i])*B_default;
	//B[i] = (magnet[i]*31)/(magnet[i]*31 + (magnet[i]-1)*10)*B_default;
      if(i==17)
	B[17] = 0;
      cout << "B" << i << " = " << B[i] << '\n'; 
    }

  for(int ipln=0; ipln<19; ipln++)
    {
      refposz[ipln]=planeposition[ipln];
    }

  linear = new TF1("linear", "[0]+[1]*x", 0, 4000);
  linear->SetParameters(0, 0);
  
}

ChargeID::~ChargeID()
{
}

void ChargeID::MCEST(double posz[], double posy[], double mcest[])
{
  minchi[0] = 9999;
  minchi[1] = 9999;

  centerslope = (Hitposy[2]-Hitposy[1])/(Hitposz[2]-Hitposz[1]);
  centerposy = Hitposy[1];
  cout << "centerslope= " << centerslope << " centerposy= " << centerposy << '\n';    

  minslope = -bin_slope*dslope/2 + centerslope;
  maxslope = bin_slope*dslope/2 + centerslope;

  minposy = -bin_posy*dposy/2 + centerposy;
  maxposy = bin_posy*dposy/2 + centerposy;

  minradius = 1000;
  maxradius = 10000;

  for(int ic=0; ic<=1; ic++)
    for(int ia=0; ia<bin_slope; ia++)
      for(int iy=0; iy<bin_posy; iy++)
	for(int ir=0; ir<bin_radius; ir++)
	  {
	    //cout << ic << " " << ia << " " << iy << " " << ir << '\n'; 
	    slope = dslope * ia + minslope;
	    positiony = dposy * iy + minposy;
	    radius = dradius * ir + minradius;
	    momentum = 0.3*B[1]*radius;

	    //cout << "initial condition" << '\n';
	    //cout << slope << " " << positiony << " " << radius << " " << momentum << '\n';

	    testradius[1] = radius;
	    testposy[1] = positiony;
	    testslope[1] = slope;
	    testmomentum[1] = momentum;

	    for(int ipln=1; ipln<lastmodule; ipln++)
	      {
		double distz, disty;
		double tempslope, tempradius, tempposy, tempmomentum;
		bfield = Bfield(testposy[ipln]);
		dE = dEdX(ipln, magnet, testmomentum[ipln]);

		//cout << "ipln= " << ipln << " dE= " << dE << '\n';
		
		distz = refposz[ipln+1]-refposz[ipln];
		disty = testposy[ipln]-testposy[ipln-1];

		if(ipln==1)
		  tempslope = slope;
		if(ipln>=2)
		  tempslope = disty/distz;

		if(magnetflag[ipln])
		  tempradius = testmomentum[ipln]/(0.3*B[ipln]);
		if(!magnetflag[ipln])
		  tempradius = -1.;
				
		tempposy = testposy[ipln] + Delta(magnetflag[ipln], distz, tempradius, tempslope, bfield, ic);
		tempmomentum = testmomentum[ipln] - dE;

		//cout << tempslope << " " << tempposy << " " << tempradius << " " << tempmomentum << '\n';
		
		testradius[ipln+1] = tempradius;
		testposy[ipln+1] = tempposy;
		testslope[ipln+1] = tempslope;
		testmomentum[ipln+1] = tempmomentum;

		if(tempmomentum < 0)
		  {
		    break;
		  }
	      }//ipln loop   

	    double chi2 = CalcChi2();
	    //cout << "chisquare= " << chi2 << '\n';
	    if(chi2 < minchi[ic])
	      {
		optslope[ic] = slope;
		optposy[ic] = positiony;
		optradius[ic] = radius;
		optmomentum[ic] = 0.3*B[1]*radius;
		minchi[ic] = chi2;
		for(int i=1; i<=lastmodule; i++)
		  {
		    estimateposy[ic][i] = testposy[i];
		  }
	      }  	    
	  }//for loop

  cout << "################ Chisqure #################" << '\n';
  cout << '\n';
  cout << "charge = -1 : " << minchi[0] << " charge = +1 : " << minchi[1] << '\n';
  cout << "!!!   " << "a= " << optslope[0] << "  Y= " << optposy[0] << " R= " << optradius[0]  
       << " P= " << optmomentum[0]  <<  "   !!!" << '\n';
  cout << "!!!   " << "a= " << optslope[1] << "  Y= " << optposy[1] << " R= " << optradius[1]  
       << " P= " << optmomentum[1]  <<  "   !!!" << '\n';
  cout << '\n';
  cout << "###########################################" << '\n';

  if(minchi[0]>minchi[1])
    {
      mcest[0] = 1;
      mcest[1] = optmomentum[1];
    }

  if(minchi[0]<=minchi[1])
    {
      mcest[0] = 0;
      mcest[1] = optmomentum[0];
    }

}


bool ChargeID::MakePlnPos(double posz[], double posy[])
{
  double aveposy;
  for(int i=0; i<19; i++)
    Hitpositiony[i].clear();

  bool firstpln = false;
  vector<int>lastpln;
  lastpln.clear();
  for(int ipln=0; ipln<19; ipln++)
    {
      Hitposz[ipln] = -9999;
      Hitposy[ipln] = -9999;
    }

  for(int ihit=0; ihit<300; ihit++)
    {
      for(int ipln=0; ipln<19; ipln++)
	if(fabs(posz[ihit]-planeposition[ipln])<30)
	  {
	    Hitpositiony[ipln].push_back(posy[ihit]);
	    Hitposz[ipln] = posz[ihit];
	    //Hitposy[ipln] = posy[ihit];
	    lastpln.push_back(ipln);
	    break;
	  }      
    }//ihit

  for(int ipln=0; ipln<19; ipln++)
    {
      aveposy=0;
      for(int ihit=0; ihit<Hitpositiony[ipln].size(); ihit++)
	{
	  aveposy += Hitpositiony[ipln].at(ihit)/(double)Hitpositiony[ipln].size();
	}
      if(Hitpositiony[ipln].size()>=1)
	Hitposy[ipln] = aveposy;
    }


  for(int ipln=0; ipln<19; ipln++)
    {
      cout << "Hitposz = " << Hitposz[ipln] << " Hitposy= " << Hitposy[ipln] << '\n';
      testposz[ipln] = Hitposz[ipln];
    }

  if(Hitposz[1]!=-9999 && Hitposz[2]!=-9999)
    firstpln=true;

  sort(lastpln.begin(), lastpln.end());

  cout << "lastpln= " << lastpln.at(lastpln.size()-1) << '\n';
  lastmodule = lastpln.at(lastpln.size()-1);

  return firstpln;
}

int ChargeID::Bfield(double posy)
{
  int bfield=0;
  if(posy <= -500 || posy >= 500)
    bfield = +1;
  if(posy > -500 && posy < 500)
    bfield = -1;

  return bfield;
}

double ChargeID::dEdX(int ipln, double magnet[], double momentum)
{
  double dE;
  double a;

  double x[21] = {0, 1.025, 1.854, 3.437, 6.812, 10.91, 31.78, 43.82, 69.50, 109.9,
                  178.7, 247.2, 512.4, 640.2, 888.5, 1248, 1825, 2383, 4509, 5532, 7524};
  double y[21] = {0, 47.04, 56.16, 68.02, 85.09, 100.3, 152.7, 176.4, 221.8, 286.8, 391.7,
		  494.5, 899.5, 1101, 1502, 2103, 3104, 4104, 8105, 10110, 14110};

  for(int i=0; i<21; i++)
    {
      if(momentum >= y[i] && momentum <= y[i+1])
        {
          a = (y[i+1]-y[i])/(x[i+1] - x[i]);
          break;
        }
    }

  double drange = magnet[ipln]*iron_len*rho_iron + layer_len*rho_sci;
  dE = drange * a;

  //cout << "momentum= " << momentum  << " drange= " << drange << " a= " << a << '\n';

  return dE;
}

double ChargeID::Delta(bool magnetflag, double distz, double radius, double slope, int bfield, int charge)
{
  double theta_i = TMath::ATan(slope);
  double theta = TMath::ASin((distz+radius*TMath::Sin(theta_i))/radius) - theta_i;
  double delta;

  if(magnetflag)
    {
      if(charge==0)
	delta = distz*TMath::Tan(theta_i + bfield*theta/2); 
      if(charge==1)
	delta = distz*TMath::Tan(theta_i - bfield*theta/2); 
    }

  if(!magnetflag)
    delta = distz*slope;  
  
  //cout << "distz= " << distz << " slope= " << slope  << " delta= " << delta << '\n';
  return delta;
}

double ChargeID::CalcChi2()
{
  double chi2=0;
  double tempy, tempY;
  int N = 18;
  int count=0;

  for(int i=1; i<=N; i++)
    {
      if(Hitposy[i]!=-9999)
	{
	  tempy = testposy[i];
	  tempY = Hitposy[i];
	  if(tempY!=0)
	    chi2 += (tempy-tempY)*(tempy-tempY)/fabs(tempY);
	  count++;
	}
    }

  chi2 = chi2/(double)count;
  //cout << "chisquare= " << chi2 << '\n';
  return chi2;

}

void ChargeID::RangeCalc(double posz_side[], double posy[], double posz_top[], double posx[], double *rangemom)
{
  double totaldE;
  double magdE;
  double scidE;
  double mipdE = 2;
  double maglen = 3.1;
  double scilen = 4.0;

  double Posz, Posx, Posy;
  int count0=0;
  double nofmagnet = 0;
  for(int ihit=0; ihit<1000; ihit++)
    {
      Posz = posz_side[ihit];
      Posy = posy[ihit];      
      if(Posy!=-9999)
	{
	  graposz0[count0] = Posz;
	  graposy[count0] = Posy;
	  count0++;
	}
    }

  int count1=0;
  for(int ihit=0; ihit<1000; ihit++)
    {
      Posz = posz_top[ihit];
      Posx = posx[ihit];      
      if(Posx!=-9999)
	{
	  graposz1[count1] = Posz;
	  graposx[count1] = Posx;
	  count1++;
	}
    }

  fitgraph[0] = new TGraph(count0, graposz0, graposy);
  fitgraph[1] = new TGraph(count1, graposz1, graposx);

  fitgraph[0]->Fit(linear);
  double slope0 = linear->GetParameter(1);
  fitgraph[1]->Fit(linear);
  double slope1 = linear->GetParameter(1);
  double d[3];
  d[0] = slope1;
  d[1] = slope0;
  d[2] = 1;
  
  double angle = d[2]/sqrt(d[0]*d[0]+d[1]*d[1]+d[2]*d[2]);
  cout << "slope0= " << slope0 << " slope1= " << slope1 << '\n';

  for(int i=0; i<lastmodule; i++)
    {
      nofmagnet += magnet[i];
    }
  
  magdE = nofmagnet*maglen*rho_iron*mipdE/angle;
  scidE = lastmodule*scilen*rho_sci*mipdE/angle;

  totaldE = magdE + scidE;
  *rangemom = totaldE;
  cout << "angle = " << angle << " nofmagnet= " << nofmagnet << '\n';
  cout << "nofmagnet= " << nofmagnet << " magdE= " << magdE << " scidE= " << scidE << " totaldE= " << totaldE  << '\n';

}
