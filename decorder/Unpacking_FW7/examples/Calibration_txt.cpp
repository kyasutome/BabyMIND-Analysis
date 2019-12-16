#include <stdio.h>
#include <string.h>
#include <exception>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;


string GetLocation(string str)
{
     
    int i = str.rfind("_Slot_");
    string way = str.substr(0,i);  
    return way;
}



int main ()
{
    
    int FEBs[46] = {0,1,2,3,4,5,8,9,10,11,12,13,16,17,18,19,20,21,24,25,26,27,28,29,32,33,34,35,36,40,41,42,43,44,48,49,50,51,52,53,56,57,58,59,60,61};
    
    string rootFileOutput;
    ostringstream sFEBnum;
    ostringstream sMCRnum;
    ostringstream sSlotnum;
    string sFEB;
    string oFEB;
    
    int Slot;
    int MCR;
    
    
    vector<double> vgain[96];

    
    
    for (int iFEB = 0; iFEB<46; iFEB++) {
      for (int i = 0; i < 96; ++i){
        vgain[i].clear();
    }
        Slot = FEBs[iFEB] % 8;
        MCR = FEBs[iFEB] / 8;
        //cout << MCR<< " "<<Slot<<endl;
        sFEBnum.str("");
        sMCRnum.str("");
        sSlotnum.str("");
        sFEBnum << FEBs[iFEB];
        sMCRnum << MCR;
        sSlotnum << Slot;
        sFEB = "PE_HG_calib/in/MCR_"+ sMCRnum.str() + "_Slot_" + sSlotnum.str() + "_gain.txt";
        ifstream gain(sFEB.c_str());
        cout << "Taking fit parrameters at "<< sFEB <<endl;
        
        if (gain.good()){
          int ch=0;
          string str;
          while(getline(gain, str)) {
            istringstream ss(str);
            double num;
            while(ss >> num){
              vgain[ch].push_back(num);;
              //cout<< vgain[ch].back()<< " ";
            }
            ch++;
            //cout<<endl;
          }
        }
        gain.close();
        oFEB = "PE_HG_calib/MCR_"+ sMCRnum.str() + "_Slot_" + sSlotnum.str() + "_gain.txt";
        cout << "Printing fit parrameters in "<< oFEB <<endl;
        ofstream outGain(oFEB.c_str());
        for (int ch = 0; ch < 96; ch++){
          if (vgain[ch].size())
            outGain<< vgain[ch].at(0) << " " << vgain[ch].at(1) << " " << vgain[ch].at(2) << " " << vgain[ch].at(2) - 2 *  vgain[ch].at(1) <<endl;
        }
        outGain.close();

  }
  return 0;
}
