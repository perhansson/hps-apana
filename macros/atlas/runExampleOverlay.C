#include <vector>

runExampleOverlay()
{

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);

  //gSystem->AddIncludePath(" -I../../../../RootUtils/");
  gSystem->AddIncludePath(" -I${HOME}/RootUtils/");
  

  gSystem->CompileMacro ("${HOME}/RootUtils/trunk/Util.cpp", "k");  
  //gROOT->ProcessLine(".L Util.cpp+");

  //gSystem->CompileMacro ("OverlayPile.C", "k");
  gSystem->CompileMacro ("OverlayPlots.C", "k");

  OverlayPlots();
  //OverlayPile();

}
