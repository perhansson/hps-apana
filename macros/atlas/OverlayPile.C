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
//#include "TFitResult.h"

#include "Util.cpp"

using namespace Utils;

void OverlayPile()
{ 

  TString inFileName = "/afs/slac/g/atlas/work/data1/dans/AnaOut/periodDslim.susy001.danV2.root";

  TString outFileName = "/afs/slac/g/atlas/work/data1/dans/AnaOut/plots/OverlayPile/test.root";

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
  plots[0] = (TH1F*)f->Get("dan1PV_J0JVF");
  plots[1] = (TH1F*)f->Get("dan2PV_J0JVF");
  plots[2] = (TH1F*)f->Get("dan3PV_J0JVF");
  plots[3] = (TH1F*)f->Get("dan_J0JVF");
  plots[4] = (TH1F*)f->Get("dansusyCuts_J0JVF");
  */




  plots[0] = (TH1F*)f->Get("dan1PV_JVfrac");
  plots[1] = (TH1F*)f->Get("dan2PV_JVfrac");
  plots[2] = (TH1F*)f->Get("dan3PV_JVfrac");
  plots[3] = (TH1F*)f->Get("dan_JVfrac");



  /*    
  plots[0] = (TH1F*)f->Get("dan1PV_J0pt");
  plots[1] = (TH1F*)f->Get("dan2PV_J0pt");
  plots[2] = (TH1F*)f->Get("dan3PV_J0pt");
  plots[3] = (TH1F*)f->Get("dansusyCuts_J0pt");
  */

  /*
  plots[0] = (TH1F*)f->Get("dansusyCuts_1PV_Met");
  plots[1] = (TH1F*)f->Get("dansusyCuts_2PV_Met");
  plots[2] = (TH1F*)f->Get("dansusyCuts_3PV_Met");
  */


  /*
  plots[0] = (TH1F*)f->Get("dan1PV_nj");
  plots[1] = (TH1F*)f->Get("dan2PV_nj");
  plots[2] = (TH1F*)f->Get("dan3PV_nj");
  plots[3] = (TH1F*)f->Get("dansusyCuts_nj");
  */

  /*  
  plots[0] = (TH1F*)f->Get("dan1PV_nj");
  plots[1] = (TH1F*)f->Get("dan1PV_njJVF99");
  plots[2] = (TH1F*)f->Get("dan1PV_njJVF75");
  plots[3] = (TH1F*)f->Get("dan1PV_njJVF50");
  */

  /*  
  plots[0] = (TH1F*)f->Get("dan_SV0_w");
  plots[1] = (TH1F*)f->Get("dan_SV0_wJVF99");
  plots[2] = (TH1F*)f->Get("dan_SV0_wJVF75");
  plots[3] = (TH1F*)f->Get("dan_SV0_wJVF50");
  */

  
  /*
  plots[0] = (TH1F*)f->Get("dansusyCuts_1PV_nj");
  plots[1] = (TH1F*)f->Get("dansusyCuts_2PV_nj");
  plots[2] = (TH1F*)f->Get("dansusyCuts_3PV_nj");
  plots[2] = (TH1F*)f->Get("dansusyCuts_4PV_nj");
  plots[3] = (TH1F*)f->Get("dansusyCuts_nj");
  */


  /*  
  plots[0] = (TH1F*)f->Get("dansusyCuts_nj");
  plots[1] = (TH1F*)f->Get("dansusyCuts_njJVF99");
  plots[2] = (TH1F*)f->Get("dansusyCuts_njJVF75");
  plots[3] = (TH1F*)f->Get("dansusyCuts_njJVF50");
  */

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
    // plots[0]->Draw();
    // plots[1]->Draw("SAME");

  }
    
    vector<TString> tags2;
    tags2.push_back("1PV");
    tags2.push_back("2PV");
    tags2.push_back("3PV");
    tags2.push_back("all events");
    //tags2.push_back("susy cuts");
    //tags2.push_back("JVF>.99");
    //tags2.push_back("JVF>.75");
    //tags2.push_back("JVF>.5");


	canvas =
        PlotAll(plots,
                4,
                tags2,
                "jet vertex fraction",
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
                "PileUp"
               );

}
