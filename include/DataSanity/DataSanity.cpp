#include <iostream>
#include <fstream>
#include <vector>

#include <DataSanity.hpp>

using namespace std;
//#define debug

DataSanity::DataSanity()
{
  bmdirpath.Form("./process/3-BMBSD");
  bmchain = new TChain("tree","tree");
  startdate=0;
  enddate=31;
  startrun=0;
  startrun=5;
}

DataSanity::~DataSanity()
{
  bmchain->Delete();
}

void DataSanity::ReadBMfile()
{
  for(int idate=startdate; idate<enddate; idate++)
    {
      for(int irun=startrun; irun<endrun; irun++)
        {
          bmfilename.Form("%s/BMBSD_%d_Nov_%d.root", bmdirpath.Data(), idate, irun);
          if (gSystem->GetPathInfo(bmfilename.Data(), info)!=0)
            {
              continue;
            }else{
            bmchain->Add(bmfilename);
	    bmchain->SetBranchAddress("BMBSD", &bmbsd);
          }
        }//isub                                                                                                        
    }//irun   

  cout << "Baby MIND entries = " << bmchain->GetEntries() <<'\n';
}

void DataSanity::SetHistLabel(TH2F* h, const char* title, char* ytitle)
{
  h->GetXaxis()->SetLabelSize(0.04);
  h->GetYaxis()->SetLabelSize(0.04);
  h->SetTitle(title);
  h->SetTitleOffset(-0.03);
  h->GetXaxis()->SetTimeDisplay(1);
  h->GetXaxis()->SetTimeFormat("#splitline{%d, %b.}{  %H:%M}%F1970-01-01 00:00:00");
  h->GetXaxis()->SetLabelOffset(0.04);  
  h->GetXaxis()->SetNdivisions(307);
  h->SetMarkerStyle(8);
  h->SetMarkerSize(0.6);
  h->SetLineWidth(1.0);
  h->SetLineColor(1);
  h->GetYaxis()->SetTitle(ytitle);
  h->SetStats(0);
}

void DataSanity::KillAll()
{
  bmchain->Delete();
}
