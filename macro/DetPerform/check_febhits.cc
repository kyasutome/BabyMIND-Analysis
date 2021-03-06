#include <iostream>

using namespace std;

void check_febhits()
{
  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 600);
  
  double febhits_jan[46] ={2007971, 2047505, 1453177, 2387643, 2334672, 4535069, 1951707, 3258421,
			   2192530, 1391204, 1300310, 2116870, 1706510, 1628623, 3077835, 198516,
			   2202219, 1519801, 1931110, 2145983, 2776017, 203619, 1600895, 1144972,
			   1762387, 1440985, 2492202, 2111749, 2541286, 2148585, 1784258, 2680424,
			   2178742, 1981773, 2362961, 3147260, 3037299, 4668756, 2594871, 3374859,
			   2807148, 2510128, 4802976, 3212166};

  double febhits_feb[46] ={};

  int nspill[2] = {32388, 38076};
  c1->cd();
  pestack->Draw("");

  TLegend* l1 = new TLegend(0.7, 0.7, 0.9, 0.9);
  l1->AddEntry(hist_jan, "30.Jan","f");
  l1->AddEntry(hist_feb, "1.Feb","f");
  l1->Draw("");
  
}
