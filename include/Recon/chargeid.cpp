#include <iostream>
#include <stdio.h>

#include "chargeid.hpp"

using namespace std;

Chargeid::Chargeid()
{ 
}


Chargeid::~Chargeid()
{
}

void Chargeid::algorithm_A(BMCluster* bmcluster, double &count_numu, double &count_numubar,
			   int minimumlimit)
{
  vector<vector<double> >dividetrackz;
  vector<vector<double> >dividetracky;
  vector<int> trackregion;

  dividetracky.clear();
  dividetrackz.clear();
  trackregion.clear();

  int last = bmcluster->mod.size();
  int count_track = 0;
  vector <double> temptracky;
  vector <double> temptrackz;
  temptracky.clear();
  temptrackz.clear();

  count_numu = 0;
  count_numubar = 0;

  double weight;
  double distance = 0;
  double Ndata = last;
  double D = bmcluster->pln.at(Ndata-1) - bmcluster->pln.at(0);

  cout << "Ndata= " << Ndata << " D= " << D << '\n';

  for(int i_datapoint=0; i_datapoint<last; i_datapoint++)
    {
      double datay = bmcluster->channel.at(i_datapoint);
      double dataz = bmcluster->pln.at(i_datapoint);

      if(i_datapoint==0)
        {
          temptracky.push_back(datay);
          temptrackz.push_back(dataz);
          trackregion.push_back(positioncheck(datay));
        }
      if(i_datapoint!=0)
        {
          if(positioncheck(datay)==trackregion.at(count_track))
            {
              temptracky.push_back(datay);
              temptrackz.push_back(dataz);
            }
          else if(positioncheck(datay)!=trackregion.at(count_track))
            {
              if(temptracky.size()!=0)
		{
                  dividetracky.push_back(temptracky);
                  dividetrackz.push_back(temptrackz);
                  temptracky.clear();
                  temptrackz.clear();
                }
              count_track++;
              temptracky.push_back(datay);
              temptrackz.push_back(dataz);
              trackregion.push_back(positioncheck(datay));
            }
        }
    }// idatapoint loop

  if(temptracky.size()!=0)
    {
      dividetracky.push_back(temptracky);
      dividetrackz.push_back(temptrackz);
    }

  int NofTrack = trackregion.size();
  vector <vector<double> > currenttrack;
  vector <double> temptrack;

  for(int i=0; i<NofTrack; i++)
    {
      currenttrack.clear();
      hitcount_under = 0;
      hitcount_over = 0;

      if(dividetracky.at(i).size()<=minimumlimit)
	continue;

      for(int i_data=0; i_data<dividetracky.at(i).size(); i_data++)
        {
          temptrack.clear();
          double z = dividetrackz.at(i).at(i_data);
          double y = dividetracky.at(i).at(i_data);
          temptrack.push_back(z);
          temptrack.push_back(y);
          currenttrack.push_back(temptrack);
        }

      int N_neighborhood = currenttrack.size()-1;

      for(int i_line=0; i_line<N_neighborhood; i_line++)
        {
          double z1 = currenttrack.at(i_line).at(0);
          double z2 = currenttrack.at(i_line+1).at(0);
          double y1 = currenttrack.at(i_line).at(1);
          double y2 = currenttrack.at(i_line+1).at(1);

          double slope = (y1-y2)/(z1-z2);
          double intercept = y1 - slope*z1;

          int N_others = currenttrack.size();

          for(int j_line=0; j_line<N_others; j_line++)
            {
              if(j_line==i_line || j_line==i_line+1)                
		continue;                

              double tryz = currenttrack.at(j_line).at(0);
              double tryy = currenttrack.at(j_line).at(1);
              double judge = (tryy - (slope*tryz+intercept));

              if(judge<0)
		hitcount_under += fabs(judge);
	      
              if(judge>=0)
		hitcount_over += fabs(judge);

            }//j_line loop                    
        }//iline loop 

      if(trackregion.at(i) == 0)
        {
          cout << "trackregion= " << trackregion.at(i) << '\n';
          count_numu_tmp += hitcount_under;
          count_numubar_tmp += hitcount_over;  
        }

      else
        {
          cout << "trackregion= " << trackregion.at(i) << '\n';
          count_numu_tmp += hitcount_over;
          count_numubar_tmp += hitcount_under;
        }

      cout << "i= " << i << '\n';
      for(int k=0; k<currenttrack.size(); k++)
	cout << "z= " << currenttrack.at(k).at(0) <<  " y= " << currenttrack.at(k).at(1) << '\n';

    }//NofTrack(i) loop  

  count_numu_tmp = count_numu_tmp/(Ndata*D);
  count_numubar_tmp = count_numubar_tmp/(Ndata*D);

  count_numu = count_numu_tmp;
  count_numubar = count_numubar_tmp;

}


int Chargeid::positioncheck(double y)
{
  int check;
  if(y<27)
    {
      check = -1;
    }
  
  if(y>=27 && y<=67)
    {
      check = 0;
    }
  
  if(y>67)
    {
      check = +1;
    }
  
  return check;

}

void Chargeid::CountMuon(double count_numu, double count_numubar,
                         double& number_of_numu, double& number_of_numubar)
{

  if(count_numu>count_numubar)
    number_of_numu++;

  if(count_numu<count_numubar)
    number_of_numubar++;

}
