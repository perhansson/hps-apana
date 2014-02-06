#include <vector>
#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TLine.h"
#include "TEllipse.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TPad.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TPolyLine.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TLatex.h"
#include "TPaveStats.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TFile.h"
#include "TMath.h"
#include "THStack.h"
#include "TSystem.h"
#include "Util.cpp"

using namespace Utils;

void OverlayPlots()
{ 

  TString inFileName = "/afs/slac/g/atlas/work/data1/dans/AnaOut/jCOMB.exttrgmc008.jetmet.root";

  TString outFileName = "/afs/slac/g/atlas/work/data1/dans/AnaOut/plots/test.root";

  ///-----------------------
  /// Output
  ///-----------------------
  TFile *outfile = new TFile(TString(outFileName),"RECREATE");
  cout << endl << "Output file created " << outFileName;
  ///-----------------------
  /// Input
  ///-----------------------
  
  TFile *f = new TFile(inFileName,"READ");
  cout << endl << "Input file read " << inFileName;
  TH1F* plots[4];


  /*    
  plots[0] = (TH1F*)f->Get("jetmetbtag1PV_J0pt");
  plots[1] = (TH1F*)f->Get("jetmetbtag2PV_J0pt");
  plots[2] = (TH1F*)f->Get("jetmetbtag3PV_J0pt");
  plots[3] = (TH1F*)f->Get("jetmetbtagsusyCuts_J0pt");
  */

  /*
  plots[0] = (TH1F*)f->Get("jetmetbtagsusyCuts_1PV_Met");
  plots[1] = (TH1F*)f->Get("jetmetbtagsusyCuts_2PV_Met");
  plots[2] = (TH1F*)f->Get("jetmetbtagsusyCuts_3PV_Met");
  */



  plots[0] = (TH1F*)f->Get("jetmetbtagsusy0l3j5020_nj");
  plots[1] = (TH1F*)f->Get("jetmetbtagsusy0l3j5020L1_J5_nj");
  plots[2] = (TH1F*)f->Get("jetmetbtagsusy0l3j5020L1_J10_nj");
  plots[3] = (TH1F*)f->Get("jetmetbtag_nj");




  




  cout << endl << "Histograms found";

  ///-----------------------
  /// Starting output PS
  ///-----------------------
  // Canvas
  TCanvas *canvas = (TCanvas*)gROOT->FindObject("c1");
  if (canvas) {canvas->Clear();} 
  else {
    style();
    canvas = (TCanvas*)gROOT->FindObject("c1");

  }
    
    vector<TString> tags2;
    tags2.push_back("susy cuts");
    tags2.push_back("+L1_J5 trigger");
    tags2.push_back("+L1_J10 trigger");
    tags2.push_back("all events");


	canvas =
        PlotAll(plots,
                4,
                tags2,
                "xaxis title",
                "",
                (const char*)("/afs/slac/g/atlas/work/data1/dans/AnaOut/plots/plotname.png"),
                (const char*)("overlay_Mult"),
                outfile,
                0.0, 0.0,
                0.0, 0.0,
                true,
                false, false,
                false,
                false,
                true,
                false,
                false,
                "PlotTitle"
               );

}
