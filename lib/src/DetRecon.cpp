#include <iostream>
#include <stdio.h>

#include "DetRecon.hpp"

using namespace std;

DetRecon::DetRecon()
{

  for(int imod=0; imod<6; imod++)
    {
      for(int iview=0; iview<2; iview++)
	{
	  for(int ibunch=0; ibunch<9; ibunch++)
	    {
	      for(int itrack=0; itrack<20; itrack++)
		{	      
		  for(int ihit=0; ihit<1000; ihit++)
		    {
		      posx[imod][iview][ibunch][itrack][ihit]=-9999.;
		      posy[imod][iview][ibunch][itrack][ihit]=-9999.;
		      posz[imod][iview][ibunch][itrack][ihit]=-9999.;
		      charge[imod][iview][ibunch][itrack][ihit]=-9999.;
		      per[imod][iview][ibunch][itrack][ihit]=-9999.;
		      pel[imod][iview][ibunch][itrack][ihit]=-9999.;
		      pet[imod][iview][ibunch][itrack][ihit]=-9999.;
		      hittime[imod][iview][ibunch][itrack][ihit]=-9999.;
		    }
		  
		  bunch[imod][iview][ibunch][itrack]=-1;
		  Nhit[imod][iview][ibunch][itrack]=-1;
		  trackid[imod][iview][ibunch][itrack]=-1;
		  fcflag[imod][iview][ibunch][itrack]=-1;
		  fvflag[imod][iview][ibunch][itrack]=-1;
		  
		  iposx[imod][iview][ibunch][itrack]=-1.;
		  iposy[imod][iview][ibunch][itrack]=-1.;
		  iposz[imod][iview][ibunch][itrack]=-1.;
		  fposx[imod][iview][ibunch][itrack]=-1.;
		  fposy[imod][iview][ibunch][itrack]=-1.;
		  fposz[imod][iview][ibunch][itrack]=-1.;
		}
	      
	      Ntrack[imod][iview][ibunch]=0;
		
	    }//ibunch

	  for(int i=0; i<3; i++)
	    nuvertex[imod][iview][i] = -1.;
	
	}//iview
      
    }//imod
  
  entry=-1;
}

DetRecon::~DetRecon()
{
}

void DetRecon::Clear()
{

  for(int imod=0; imod<6; imod++)
    {
      for(int iview=0; iview<2; iview++)
	{
	  for(int ibunch=0; ibunch<9; ibunch++)
	    {
	      for(int itrack=0; itrack<20; itrack++)
		{	      
		  for(int ihit=0; ihit<1000; ihit++)
		    {
		      posx[imod][iview][ibunch][itrack][ihit]=-9999.;
		      posy[imod][iview][ibunch][itrack][ihit]=-9999.;
		      posz[imod][iview][ibunch][itrack][ihit]=-9999.;
		      charge[imod][iview][ibunch][itrack][ihit]=-9999.;
		      per[imod][iview][ibunch][itrack][ihit]=-9999.;
		      pel[imod][iview][ibunch][itrack][ihit]=-9999.;
		      pet[imod][iview][ibunch][itrack][ihit]=-9999.;
		      hittime[imod][iview][ibunch][itrack][ihit]=-9999.;
		    }
		  
		  bunch[imod][iview][ibunch][itrack]=-1;
		  Nhit[imod][iview][ibunch][itrack]=-1;
		  trackid[imod][iview][ibunch][itrack]=-1;
		  fcflag[imod][iview][ibunch][itrack]=-1;
		  fvflag[imod][iview][ibunch][itrack]=-1;
		  
		  iposx[imod][iview][ibunch][itrack]=-1.;
		  iposy[imod][iview][ibunch][itrack]=-1.;
		  iposz[imod][iview][ibunch][itrack]=-1.;
		  fposx[imod][iview][ibunch][itrack]=-1.;
		  fposy[imod][iview][ibunch][itrack]=-1.;
		  fposz[imod][iview][ibunch][itrack]=-1.;
		}
	      
	      Ntrack[imod][iview][ibunch]=0;
		
	    }//ibunch

	  for(int i=0; i<3; i++)
	    nuvertex[imod][iview][i] = -1.;
	
	}//iview
    }//imod
  
  entry=-1;

}

