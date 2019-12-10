#include <iostream>
#include <stdio.h>

#include "TCanvas.h"
#include "TApplication.h"

#include "test.hpp"
#include "testlib.hpp"

using namespace std;

int main( int argc, char **argv ) 
{

  TApplication app("app", 0, 0, 0, 0);
  cout << "This is the first time to use Cmake in order to compile my codes" << '\n';
  cout << "First link to ROOT with cmake!!!" << '\n';

  error();
  Hello();

  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 600);
  c1->cd();
  
  app.Run();
  return 0;
}
