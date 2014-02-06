//*****************************************************
// file    : Util
// 
// Purpose : Utilities to make plots
//            
//          
// Author  : A. Schwartzman
//
// Date    : 15-May-2001 : Creation of class
//         : 05-Dec-2001 : Add PlotTagProb function
//         : 17-Jun-2002 : Add Util.h file - Pavel Demine
//         : 08-Oct-2002 : Add PlotTagRate method - Ariel Schwartzman
//         : 10-Oct-2002 : Add PlotLine method - Don Lincoln
//*****************************************************
#include "TLine.h"
#include "TEllipse.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TPad.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include <iostream>
#include "TPolyLine.h"
#include "style.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TLatex.h"
#include "TPaveStats.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TFile.h"
#include "TMath.h"

using namespace std;

///===================================================
/// ATLAS_LABEL
///===================================================
void ATLAS_LABEL(Double_t x,Double_t y,Int_t color=1) {

  TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize); 
  l.SetNDC();
  l.SetTextFont(72);
  l.SetTextColor(color);
  l.DrawLatex(x,y,"ATLAS");
}

///===================================================
/// myText
///===================================================
void myText(Double_t x,Double_t y,Color_t color,char *text) {

  //Double_t tsize=0.05;
  TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize); 
  l.SetNDC();
  l.SetTextColor(color);
  l.DrawLatex(x,y,text);
}
///===================================================
/// myText
///===================================================
void myText(Double_t x,Double_t y,Color_t color,const char *text) {

  //Double_t tsize=0.05;
  TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize); 
  l.SetNDC();
  l.SetTextColor(color);
  l.DrawLatex(x,y,text);
}

///===================================================
/// LEGO PLOT: 1 HISTO
///===================================================
void LegoPlot(TH2F* hist1, const char* title = "")
{
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  
  TPad* pad1 = new TPad("pad1","pad",0.02,0.02,0.96,0.98);
  pad1->Draw();
  pad1->cd();
  pad1->SetGrid();

  hist1->GetXaxis()->SetTitleSize(0.05);
  hist1->GetYaxis()->SetTitleSize(0.05);
  hist1->Draw("lego"); 

  if(title!="")
    c1->SaveAs(title);
}

///===================================================
/// LEGO PLOT: 1 HISTO
///===================================================
void ColzPlot(TH2F* hist1, const char* title = "")
{
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  
  TPad* pad1 = new TPad("pad1","pad",0.02,0.02,0.96,0.98);
  pad1->Draw();
  pad1->cd();
  pad1->SetGrid();

  hist1->GetXaxis()->SetTitleSize(0.05);
  hist1->GetYaxis()->SetTitleSize(0.05);
  hist1->Draw("colz"); 

  if(title!="")
    c1->SaveAs(title);
}

///===================================================
/// LEGO PLOT: 1 HISTO and SAVE IT
///===================================================
void ColzPlot(TH2D* hist1, 
              TFile *outfile, 
              const char* title = "",
              const char* histName = ""
             )
{
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  
  TPad* pad1 = new TPad("pad1","pad",0.02,0.02,0.96,0.98);
  pad1->Draw();
  pad1->cd();
  pad1->SetGrid();

  hist1->GetXaxis()->SetTitleSize(0.05);
  hist1->GetYaxis()->SetTitleSize(0.05);
  hist1->Draw("colz"); 

  if(title!="")
    c1->SaveAs(title);
    
  if (outfile) {
    outfile->cd();
    hist1->Write(histName,TObject::kOverwrite);
    c1->Write(TString(TString(histName)+"_canvas"),TObject::kOverwrite);
  }
}

///===================================================
/// LEGO PLOT: 2 HISTOS (2 PADs)
///===================================================
void LegoPlot(TH2F* hist1, TH2F* hist2, const char* title = "")
{
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  
  TPad* pad1 = new TPad("pad1","pad",0.02,0.52,0.98,0.98);
  pad1->Draw();
  
  TPad* pad2 = new TPad("pad2","pad",0.02,0.02,0.98,0.48);
  pad2->Draw();
  
  pad1->cd();
  pad1->SetGrid(); 

  hist1->GetXaxis()->SetTitleSize(0.05);
  hist1->GetYaxis()->SetTitleSize(0.05);
  hist1->Draw("lego"); 

  pad2->cd();
  pad2->SetGrid(); 
  hist2->GetXaxis()->SetTitleOffset(1.4);
  hist2->GetYaxis()->SetTitleOffset(1.4);
  hist2->Draw("lego"); 

  if(title!="")
    c1->SaveAs(title);
}

///===================================================
/// LEGO PLOT: 3 HISTOs (3 PADs)
///===================================================
void LegoPlot(TH2F* hist1, TH2F* hist2, TH2F* hist3, const char* title ="") 
{
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }

  TPad* pad1 = new TPad("pad1","pad",0.02,0.52,0.48,0.98);
  pad1->Draw();  

  TPad* pad2 = new TPad("pad2","pad",0.52,0.52,0.98,0.98);
  pad2->Draw();
  
  TPad* pad3 = new TPad("pad3","pad",0.02,0.02,0.98,0.48);
  pad3->Draw();
   
  pad1->cd();
  pad1->SetGrid(); 
  hist1->GetXaxis()->SetTitleSize(0.05);
  hist1->GetYaxis()->SetTitleSize(0.05);
  hist1->Draw();

  pad2->cd();
  pad2->SetGrid(); 
  hist1->GetXaxis()->SetTitleSize(0.05);
  hist1->GetYaxis()->SetTitleSize(0.05);
  hist2->Draw(); 

  pad3->cd();
  pad3->SetGrid(); 
  hist1->GetXaxis()->SetTitleSize(0.05);
  hist1->GetYaxis()->SetTitleSize(0.05);
  hist3->Draw(); 

  if(title!="")
    c1->SaveAs(title);
}

///===================================================
/// PLOT: 1 HISTO
///===================================================
void Plot(TH1* hist1, 
          const char* title = "", 
          Char_t* option = "",
          Bool_t logy = 0, Bool_t logx = 0, 
          Bool_t fit = 0, Char_t* formula = "gaus")
{
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->SetLogy(0);
  
  TPad* pad1 = new TPad("pad1","pad",0.02,0.02,0.96,0.98);
  pad1->Draw();
  if(logy) pad1->SetLogy(); if(logx) pad1->SetLogx();

  pad1->cd();
  pad1->SetGrid(0); 
  if(fit)  hist1->Fit(formula);
  hist1->GetXaxis()->SetTitleSize(0.05);
  hist1->Draw(option); 

  if (title != "") c1->SaveAs(title);
}

///===================================================
/// PLOT: 1 HISTO
///===================================================
void Plot(TH1* hist1, 
          TFile *outfile, 
          const char* title = "", 
          const char* histName = "",
          Char_t* option = "",
          Bool_t logy = 0, Bool_t logx = 0, 
          Bool_t fit = 0, Char_t* formula = "gaus")
{
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->SetLogy(0);
  
  TPad* pad1 = new TPad("pad1","pad",0.02,0.02,0.96,0.98);
  pad1->Draw();
  if(logy) pad1->SetLogy(); if(logx) pad1->SetLogx();

  pad1->cd();
  pad1->SetGrid(0); 
  if(fit)  hist1->Fit(formula);
  hist1->GetXaxis()->SetTitleSize(0.05);
  hist1->Draw(option); 

  if(title!="")
    c1->SaveAs(title);
    
  if (outfile) {
    outfile->cd();
    hist1->Write(histName,TObject::kOverwrite);
    c1->Write(TString(TString(histName)+"_canvas"),TObject::kOverwrite);
  }
}


///===================================================
/// PLOT: 2 HISTOs
///===================================================
void Plot(TH1* hist1, TH1* hist2, const char* title = "",
	  Char_t* option = "", Bool_t logy = 0, Bool_t logx = 0, 
	  Bool_t fit = 0, Char_t* formula = "gaus")
{
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->SetLogy(0);
  
  TPad* pad1 = new TPad("pad1","pad",0.02,0.52,0.98,0.98);
  pad1->Draw(); 
  if(logy) pad1->SetLogy(); if(logx) pad1->SetLogx();

  TPad* pad2 = new TPad("pad2","pad",0.02,0.02,0.98,0.48);
  pad2->Draw();
  if(logy) pad2->SetLogy(); if(logx) pad2->SetLogx();

  pad1->cd();
  pad1->SetGrid(); 
  if(fit)  hist1->Fit(formula);
  hist1->GetXaxis()->SetTitleOffset(0.9);
  hist1->GetXaxis()->SetTitleSize(0.05);
  hist1->Draw(option); 

  pad2->cd();
  pad2->SetGrid(); 
  if(fit)  hist2->Fit(formula);
  hist2->GetXaxis()->SetTitleOffset(0.9);
  hist2->GetXaxis()->SetTitleSize(0.05);
  hist2->Draw(option); 

  if(title!="")
    c1->SaveAs(title);
}

///===================================================
/// PLOT: 4 HISTOs
///===================================================
void Plot(TH1* hist1, TH1* hist2, TH1* hist3, TH1* hist4, 
	  const char* title = "", Char_t* option = "", Bool_t logy = 0, 
	  Bool_t logx = 0, Bool_t fit = 0, Char_t* formula = "gaus",
	  Axis_t xmin = 0, Axis_t xmax = 0)
{
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->SetLogy(0);

  TPad* pad1 = new TPad("pad1","pad",0.02,0.52,0.48,0.98);
  pad1->Draw();
  if(logy) pad1->SetLogy(); if(logx) pad1->SetLogx();
  
  TPad* pad2 = new TPad("pad2","pad",0.52,0.52,0.98,0.98);
  pad2->Draw();
  if(logy) pad2->SetLogy(); if(logx) pad2->SetLogx();

  TPad* pad3 = new TPad("pad3","pad",0.02,0.02,0.48,0.48);
  pad3->Draw();
  if(logy) pad3->SetLogy(); if(logx) pad3->SetLogx();

  TPad* pad4 = new TPad("pad4","pad",0.52,0.02,0.98,0.48);
  pad4->Draw();
  if(logy) pad4->SetLogy(); if(logx) pad4->SetLogx();


  pad1->cd();
  pad1->SetGrid(); 
  if(fit)  hist1->Fit(formula,"","",xmin,xmax);
  hist1->GetXaxis()->SetTitleOffset(0.9);
  hist1->GetXaxis()->SetTitleSize(0.05);
  hist1->Draw(option); 
  
  pad2->cd();
  pad2->SetGrid(); 
  if(fit)  hist2->Fit(formula,"","",xmin,xmax);
  hist2->GetXaxis()->SetTitleOffset(0.9);
  hist2->GetXaxis()->SetTitleSize(0.05);
  hist2->Draw(option); 
  
  pad3->cd();
  pad3->SetGrid(); 
  if(fit)  hist3->Fit(formula,"","",xmin,xmax);
  hist3->GetXaxis()->SetTitleOffset(0.9);
  hist3->GetXaxis()->SetTitleSize(0.05);
  hist3->Draw(option); 

  pad4->cd();
  pad4->SetGrid(); 
  if(fit)  hist4->Fit(formula,"","",xmin,xmax);
  hist4->GetXaxis()->SetTitleOffset(0.9);
  hist4->GetXaxis()->SetTitleSize(0.05);
  hist4->Draw(option); 

  if(title!="")
    c1->SaveAs(title);
}


///===================================================
/// PLOT: 3 HISTOs
///===================================================
void Plot(TH1* hist1, TH1* hist2, TH1* hist3, const char* title = "")
{
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  
  TPad* pad1 = new TPad("pad1","pad",0.02,0.62,0.98,0.98);
  pad1->Draw();
  
  TPad* pad2 = new TPad("pad3","pad",0.02,0.32,0.98,0.58);
  pad2->Draw();
  
  TPad* pad3 = new TPad("pad3","pad",0.02,0.02,0.98,0.28);
  pad3->Draw();
  
 
  pad1->cd();
  pad1->SetGrid(); 
  hist1->GetXaxis()->SetTitleOffset(0.9);
  hist2->GetXaxis()->SetTitleSize(0.05);
  hist1->Draw(); 


  pad2->cd();
  pad2->SetGrid(); 
  hist2->GetXaxis()->SetTitleOffset(0.9);
  hist2->GetXaxis()->SetTitleSize(0.05);
  hist2->Draw(); 


  pad3->cd();
  pad3->SetGrid(); 
  hist3->GetXaxis()->SetTitleOffset(0.9);
  hist2->GetXaxis()->SetTitleSize(0.05);
  hist3->Draw(); 

  if(title!="")
    c1->SaveAs(title);
}

///===================================================
/// PLOT: 3 HISTOs w/ FITS
///===================================================
void Plot3ii(TH1* hist1, TH1* hist2, TH1* hist3, const char* title ="", 
	     Char_t* option = "", Bool_t logy = 0, Bool_t logx = 0, 
	     bool fit1 = 0, bool fit2 = 0, bool fit3 = 0,
	     Char_t* formula = "gaus")
{
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->SetLogy(0);

  TPad* pad1 = new TPad("pad1","pad",0.02,0.52,0.48,0.98);
  pad1->Draw();  
  if(logy) pad1->SetLogy(); if(logx) pad1->SetLogx();

  TPad* pad2 = new TPad("pad2","pad",0.52,0.52,0.98,0.98);
  pad2->Draw();
  if(logy) pad2->SetLogy(); if(logx) pad2->SetLogx();
  
  TPad* pad3 = new TPad("pad3","pad",0.02,0.02,0.98,0.48);
  pad3->Draw();
  if(logy) pad3->SetLogy(); if(logx) pad3->SetLogx();
   
  pad1->cd();
  pad1->SetGrid(); 
  hist1->GetXaxis()->SetTitleOffset(0.9);
  hist1->GetXaxis()->SetTitleSize(0.05);
  hist1->Draw(option);
  if(fit1) hist1->Fit(formula);

  pad2->cd();
  pad2->SetGrid(); 
  hist2->GetXaxis()->SetTitleOffset(0.9);
  hist2->GetXaxis()->SetTitleSize(0.05);
  hist2->Draw(option); 
  if(fit2) hist2->Fit(formula);

  pad3->cd();
  pad3->SetGrid(); 
  hist3->GetXaxis()->SetTitleOffset(0.9);
  hist3->GetXaxis()->SetTitleSize(0.05);
  hist3->Draw(option); 
  if(fit3) hist3->Fit(formula);

  if(title!="")
    c1->SaveAs(title);
}


///===================================================
/// PLOT: 3 HISTOs w/ FITS
///===================================================
void Plot3iii(TH1* hist1, TH1* hist2, TH1* hist3, const char* title ="", 
	     Char_t* option = "", Bool_t logy1 = 0, Bool_t logy2 = 0, 
	      Bool_t logy3 = 0, bool fit = 0, Char_t* formula = "gaus")
{
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->SetLogy(0);

  TPad* pad1 = new TPad("pad1","pad",0.02,0.52,0.48,0.98);
  pad1->Draw();  
  if(logy1) pad1->SetLogy(); 

  TPad* pad2 = new TPad("pad2","pad",0.52,0.52,0.98,0.98);
  pad2->Draw();
  if(logy2) pad2->SetLogy(); 
  
  TPad* pad3 = new TPad("pad3","pad",0.02,0.02,0.98,0.48);
  pad3->Draw();
  if(logy3) pad3->SetLogy(); 
   
  pad1->cd();
  pad1->SetGrid(); 
  hist1->GetXaxis()->SetTitleOffset(0.9);
  hist1->GetXaxis()->SetTitleSize(0.05);
  hist1->Draw(option);
  if(fit) hist1->Fit(formula);

  pad2->cd();
  pad2->SetGrid(); 
  hist2->GetXaxis()->SetTitleOffset(0.9);
  hist2->GetXaxis()->SetTitleSize(0.05);
  hist2->Draw(option); 
  if(fit) hist2->Fit(formula);

  pad3->cd();
  pad3->SetGrid(); 
  hist3->GetXaxis()->SetTitleOffset(0.9);
  hist3->GetXaxis()->SetTitleSize(0.05);
  hist3->Draw(option); 
  if(fit) hist3->Fit(formula);

  if(title!="")
    c1->SaveAs(title);
}


///===================================================
/// PLOT: 6 HISTOs w/ FITS
///===================================================
void Plot(TH1* hist1, TH1* hist2, TH1* hist3, TH1* hist4, TH1* hist5, 
	  TH1* hist6, const char* title = "", Char_t* option = "", 
	  Bool_t logy = 0, Bool_t logx = 0, Bool_t fit = 0)
{
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->SetLogy(0);
  c1->Divide(2,3);
  c1->cd(1);
  hist1->Draw(option);
  if(fit) hist1->Fit("gaus");

  c1->cd(2);
  hist2->Draw(option);
  if(fit) hist2->Fit("gaus");

  c1->cd(3);
  hist3->Draw(option);
  if(fit) hist3->Fit("gaus");

  c1->cd(4);
  hist4->Draw(option);
  if(fit) hist4->Fit("gaus");

  c1->cd(5);
  hist5->Draw(option);
  if(fit) hist5->Fit("gaus");

  c1->cd(6);
  hist6->Draw(option);
  if(fit) hist6->Fit("gaus");

  if(logy) gPad->SetLogy();
  if(logx) gPad->SetLogx();


  if(title!="")
    c1->SaveAs(title);
}

///===================================================
/// Plot an array of histograms
///===================================================
void PlotAll(TH1F* h1[],
             Int_t NPlots,
             vector<TString> plotNames,
             TString xAxisLabel,
             TString yAxisLabel,
             const char* name,
             const char* histName,
             TFile *outfile,
             Float_t YMin,  Float_t YMax,
             bool drawNorm = kFALSE,
             bool logx = kFALSE, bool logy = kFALSE)
{
  // Canvas
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->Clear();
  c1->SetLogy(logy);
  c1->SetLogx(logx);
  
  // Colors
  Color_t colors[] = {kRed,kBlue,kGreen,kCyan,kMagenta,kViolet,kBlack,
                      kRed,kBlue,kGreen,kCyan,kMagenta,kViolet,kBlack,
                      kRed,kBlue,kGreen,kCyan,kMagenta,kViolet,kBlack,
                      kRed,kBlue,kGreen,kCyan,kMagenta,kViolet,kBlack};
  
  // Legend
  TLegend *legend = new TLegend(0.54,0.62,0.89,0.89);
  legend->SetFillStyle(0);
  TLegendEntry *entry;

  // Plot name
  char plotName[500];

  /// Loop on plots
  for (Int_t plotItr = 0; plotItr < NPlots; plotItr++) {
    h1[plotItr]->GetXaxis()->SetTitle(xAxisLabel);
    h1[plotItr]->GetYaxis()->SetTitle(yAxisLabel);
    h1[plotItr]->SetMarkerStyle(plotItr+20);
    h1[plotItr]->SetMarkerSize(1.7);
    h1[plotItr]->SetMarkerColor(colors[plotItr+1]);
    h1[plotItr]->SetStats(kFALSE);
    if (drawNorm) {
      if (plotItr != 0) h1[plotItr]->DrawNormalized("psame",1E5);
      else h1[plotItr]->DrawNormalized("p",1E5);
      if (YMin != YMax) h1[plotItr]->GetYaxis()->SetRangeUser(YMin,YMax);
      h1[plotItr]->DrawNormalized("esame",1E5);
    }
    else {
      if (plotItr != 0) h1[plotItr]->Draw("psame");
      else h1[plotItr]->Draw("ep");
      //h1[plotItr]->Draw("esame");
    }
    if (YMin != YMax) h1[plotItr]->GetYaxis()->SetRangeUser(YMin,YMax);
    c1->Update();  
   
    outfile->cd();
    sprintf(plotName,"%s_index_%d",histName,plotItr);
    h1[plotItr]->Write(plotName,TObject::kOverwrite);
   
    entry = legend->AddEntry(h1[plotItr],plotNames.at(plotItr),"p");
    entry->SetTextAlign(12);
    entry->SetTextColor(1);
  }
  legend->Draw();
  c1->Update();   
  c1->SaveAs(name);
  outfile->cd();
  c1->Write(histName,TObject::kOverwrite);

  delete legend;

}

///===================================================
/// Plot an array of histograms
///===================================================
void PlotAll(TH1F* h1[],
             Int_t NPlots,
             TString plotNames[30],
             TString xAxisLabel,
             TString yAxisLabel,
             const char* name,
             const char* histName,
             TFile *outfile,
             Float_t YMin,  Float_t YMax,
             bool drawNorm = kFALSE,
             bool logx = kFALSE, bool logy = kFALSE,
             Float_t XMin = -1, Float_t XMax = -1,
             bool drawMean = false) 
{
  // Canvas
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->Clear();
  c1->SetLogy(logy);
  c1->SetLogx(logx);
  
  // Colors
  Color_t colors[] = {kRed,kBlue,kGreen,kCyan,kMagenta,kViolet,kBlack,
                      kRed,kBlue,kGreen,kCyan,kMagenta,kViolet,kBlack,
                      kRed,kBlue,kGreen,kCyan,kMagenta,kViolet,kBlack,
                      kRed,kBlue,kGreen,kCyan,kMagenta,kViolet,kBlack};
  
  Style_t marker[] = {20,21,24,25,22,26,23,27,28,29,30,
                      20,21,24,25,22,26,23,27,28,29,30,
                      20,21,24,25,22,26,23,27,28,29,30};                    
  
  // Legend
  TLegend *legend = new TLegend(0.5,0.68,0.91,0.91);
  legend->SetFillColor(0);
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  TLegendEntry *entry;

  // Plot name
  char plotName[500];


  /// Loop on plots
  for (Int_t plotItr = 0; plotItr < NPlots; plotItr++) {
    if( !h1[plotItr] ) continue;
    h1[plotItr]->SetXTitle(xAxisLabel);
    h1[plotItr]->SetYTitle(yAxisLabel);
    if (YMin != YMax) h1[plotItr]->GetYaxis()->SetRangeUser(YMin,YMax);
    if (XMin != XMax) h1[plotItr]->GetXaxis()->SetRangeUser(XMin,XMax);
    h1[plotItr]->SetMarkerStyle(marker[plotItr]);
    h1[plotItr]->SetMarkerSize(1.3);
    h1[plotItr]->SetMarkerColor(colors[plotItr+1]);
    h1[plotItr]->SetLineColor(colors[plotItr+1]);
    h1[plotItr]->SetStats(kFALSE);
    h1[plotItr]->GetXaxis()->SetTitleSize(0.05);
    h1[plotItr]->GetYaxis()->SetTitleSize(0.05);    
    if (drawNorm) {
      if (plotItr != 0) h1[plotItr]->DrawNormalized("psame",1E4);
      else h1[plotItr]->DrawNormalized("p",1E4);
      h1[plotItr]->DrawNormalized("esame",1E4);
      if (YMin != YMax) h1[plotItr]->GetYaxis()->SetRangeUser(YMin,YMax);
      if (XMin != XMax) h1[plotItr]->GetXaxis()->SetRangeUser(XMin,XMax);
    }
    else {
      if (plotItr != 0) h1[plotItr]->Draw("psame");
      else h1[plotItr]->Draw("ep");
      //h1[plotItr]->Draw("esame");
    }
    c1->Update();  
    
    TLatex* tex;
    Char_t info[300];
    if (drawMean) {
      sprintf(info,"Mean = %1.2f; RMS = %1.2f",h1[plotItr]->GetMean(),h1[plotItr]->GetRMS());
      Float_t texY = 0.63-(plotItr*0.032);
      tex = new TLatex(0.60,texY,info); 
      tex->SetNDC();  
      tex->SetTextSize(0.03); 
      tex->SetTextColor(colors[plotItr+1]);
      tex->Draw();
    }
   
    outfile->cd();
    sprintf(plotName,"%s_index_%d",histName,plotItr);
    h1[plotItr]->Write(plotName,TObject::kOverwrite);
   
    entry = legend->AddEntry(h1[plotItr],plotNames[plotItr],"p");
    entry->SetTextAlign(12);
    entry->SetTextColor(1);
  }
  legend->Draw();
  c1->Update();   
  c1->SaveAs(name);
  outfile->cd();
  c1->Write(histName,TObject::kOverwrite);

  delete legend;

}



///===================================================
/// Find the histograms with maximum value
///===================================================
Double_t FindMaxVal(TH1F* h1[], Int_t NPlots, bool norm) {
   Double_t max = -1.;
   for(int i=0;i!=NPlots;++i) {
      TH1F* h = (TH1F*)h1[i]->Clone(TString::Format("%s_tmp",h1[i]->GetName()));
      if(norm) {
         h->Scale(1./h->Integral(1,h->GetNbinsX()));
         if(h->GetMaximum()>max) max = h->GetMaximum();
      } else {
         if(h->GetMaximum()>max) max = h->GetMaximum();         
      }
      delete h;
   }
   return max;   
}

///===================================================
/// Find the histograms with minimum value
///===================================================
Double_t FindMinVal(TH1F* h1[], Int_t NPlots, bool norm) {
   Double_t min = 999999999.9;
   for(int i=0;i!=NPlots;++i) {
      TH1F* h = (TH1F*)h1[i]->Clone(TString::Format("%s_tmpformin",h1[i]->GetName()));
      if(norm) {
         h->Scale(1./h->Integral(1,h->GetNbinsX()));
         if(h->GetMinimum()<min) min = h->GetMinimum();
      } else {
         if(h->GetMinimum()<min) min = h->GetMinimum();         
      }
      delete h;
   }
   return min;   
}

///===================================================
/// Find the histograms with minimum value NOT zerp
///===================================================
Double_t FindMinValNotZero(TH1F* h1[], Int_t NPlots, bool norm) {
   Double_t min = 999999999.9;
   for(int i=0;i!=NPlots;++i) {
      TH1F* h = (TH1F*)h1[i]->Clone(TString::Format("%s_tmpformin",h1[i]->GetName()));
      if(norm) {
         h->Scale(1./h->Integral(1,h->GetNbinsX()));
         for(int ibin=1;ibin!=h->GetNbinsX()+1;++ibin) {
            if(h->GetBinContent(ibin)<min && h->GetBinContent(ibin)!=0) min = h->GetBinContent(ibin);
         }
      } else {
         for(int ibin=1;ibin!=h->GetNbinsX()+1;++ibin) {
            if(h->GetBinContent(ibin)<min && h->GetBinContent(ibin)!=0) min = h->GetBinContent(ibin);
         }
      }
      delete h;
   }
   return min;   
}

///===================================================
/// Plot an array of histograms
///===================================================
void PlotAllData(TH1F* h1[],
                 Int_t NPlots,
                 TString plotNames[30],
                 TString xAxisLabel,
                 TString yAxisLabel,
                 const char* name,
                 const char* histName,
                 TFile *outfile,
                 Float_t YMin,  Float_t YMax,
                 bool drawNorm = kFALSE,
                 bool logx = kFALSE, bool logy = kFALSE,
                 Float_t XMin = -1, Float_t XMax = -1,
                 bool drawMean = false, TString opt="", Int_t dataIndex=-1) 
{
  // Canvas
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->Clear();
  c1->SetLogy(logy);
  c1->SetLogx(logx);
  
  // Colors
  Color_t colors[] = {kRed,kBlue,kGreen,kCyan,kMagenta,36,kBlack,
                      kRed+2,kBlue+2,kGreen+2,kCyan+2,kMagenta+2,36+2,kBlack+2,
                      kRed,kBlue,kGreen,kCyan,kMagenta,36,kBlack,
                      kRed,kBlue,kGreen,kCyan,kMagenta,36,kBlack};
//   Color_t colors[] = {kRed,kBlue,kGreen,kCyan,kMagenta,kViolet,kBlack,
//                       kRed,kBlue,kGreen,kCyan,kMagenta,kViolet,kBlack,
//                       kRed,kBlue,kGreen,kCyan,kMagenta,kViolet,kBlack,
//                       kRed,kBlue,kGreen,kCyan,kMagenta,kViolet,kBlack};
  
  Style_t marker[] = {20,21,24,25,22,26,23,27,28,29,30,
                      20,21,24,25,22,26,23,27,28,29,30,
                      20,21,24,25,22,26,23,27,28,29,30};                    
  
  // Legend
  Float_t legCoord[4];
  if(NPlots<7) {legCoord[0]= 0.55; legCoord[1]=0.68;legCoord[2]=0.91;legCoord[3]=0.91;}
  else         {legCoord[0]= 0.55; legCoord[1]=0.58;legCoord[2]=0.94;legCoord[3]=0.91;}
  TLegend *legend = new TLegend(legCoord[0],legCoord[1],legCoord[2],legCoord[3]);  
  //TLegend *legend = new TLegend(0.5,0.68,0.91,0.91);
  legend->SetFillColor(0);
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  TLegendEntry *entry;

  // Plot name
  char plotName[500];

  //Find the max/min value for histograms
  Double_t max_val = FindMaxVal(h1, NPlots, drawNorm);
  Double_t min_val = FindMinVal(h1, NPlots, drawNorm);
  Double_t min_val_not_zero = FindMinValNotZero(h1, NPlots, drawNorm);
  
  /// Loop on plots
  for (Int_t plotItr = 0; plotItr < NPlots; plotItr++) {
     if( !h1[plotItr] ) continue;
     h1[plotItr]->SetXTitle(xAxisLabel);
     h1[plotItr]->SetYTitle(yAxisLabel);
     if (YMin != YMax) h1[plotItr]->GetYaxis()->SetRangeUser(YMin,YMax);
     else{
        //use that "tallest" one
        //cout << "USING TALLEST " << max_val << "and SMALLEST" << min_val << endl;
        cout << "USING TALLEST " << max_val << endl;
        h1[plotItr]->SetMaximum(max_val*1.1);
        if(logy&&min_val==0) h1[plotItr]->SetMinimum(min_val_not_zero);
        else h1[plotItr]->SetMinimum(min_val);
     }
    if (XMin != XMax) h1[plotItr]->GetXaxis()->SetRangeUser(XMin,XMax);
    h1[plotItr]->SetMarkerStyle(marker[plotItr]);
    h1[plotItr]->SetMarkerSize(1.3);
    h1[plotItr]->SetMarkerColor(colors[plotItr]);
    h1[plotItr]->SetLineColor(colors[plotItr]);
    h1[plotItr]->SetStats(kFALSE);
    h1[plotItr]->GetXaxis()->SetTitleSize(0.05);
    h1[plotItr]->GetYaxis()->SetTitleSize(0.05);    
    if(drawNorm) {
       h1[plotItr]->Scale(1.0/h1[plotItr]->Integral(1,h1[plotItr]->GetNbinsX()));
    }
    
    TString drawOpt="p";
    if(opt!="") {
       drawOpt=opt;
    }
    //points for data!
    if(dataIndex==plotItr) {
       drawOpt = "p";
    }
//     if (drawNorm) {
//       if (plotItr != 0) h1[plotItr]->DrawNormalized(drawOpt+"same",1E4);
//       else h1[plotItr]->DrawNormalized(drawOpt,1E4);
//       //h1[plotItr]->DrawNormalized("esame",1E4);
//       if (YMin != YMax) h1[plotItr]->GetYaxis()->SetRangeUser(YMin,YMax);
//       else{
//          //use that "tallest" one
//          h1[plotItr]->SetMaximum(max_val);
//       }
//       if (XMin != XMax) h1[plotItr]->GetXaxis()->SetRangeUser(XMin,XMax);
//     }
//    else {
    if (plotItr != 0) h1[plotItr]->Draw(drawOpt+"same");
    else h1[plotItr]->Draw(drawOpt);
    //h1[plotItr]->Draw("esame");
    if (YMin != YMax) h1[plotItr]->GetYaxis()->SetRangeUser(YMin,YMax);
    else{
       //use that "tallest" one
       h1[plotItr]->SetMaximum(max_val*1.1);
    }
    if (XMin != XMax) h1[plotItr]->GetXaxis()->SetRangeUser(XMin,XMax);

      //  }
    
    c1->Update();  
    
    TLatex* tex;
    Char_t info[300];
    if (drawMean) {
      sprintf(info,"Mean = %1.2f; RMS = %1.2f",h1[plotItr]->GetMean(),h1[plotItr]->GetRMS());
      Float_t texY = 0.63-(plotItr*0.032);
      tex = new TLatex(0.60,texY,info); 
      tex->SetNDC();  
      tex->SetTextSize(0.03); 
      tex->SetTextColor(colors[plotItr]);
      tex->Draw();
    }
   
    outfile->cd();
    TString plotNamesFixed(plotNames[plotItr]);
    plotNamesFixed.ReplaceAll(".","_");plotNamesFixed.ReplaceAll("#","");
    plotNamesFixed.ReplaceAll(" ","_");
    plotNamesFixed.ReplaceAll("{",""); plotNamesFixed.ReplaceAll("}","");
    plotNamesFixed.ReplaceAll("(",""); plotNamesFixed.ReplaceAll(")","");
    plotNamesFixed.ReplaceAll("-","_"); 
    sprintf(plotName,"%s_index_%s",histName,plotNamesFixed.Data());
    h1[plotItr]->Write(plotName,TObject::kOverwrite);
    
    TString legMarker = "p";
    if(drawOpt.Contains("hist")) legMarker="l";
    entry = legend->AddEntry(h1[plotItr],plotNames[plotItr],legMarker);
    entry->SetTextAlign(12);
    entry->SetTextColor(1);
  }
  legend->Draw();
  c1->Update();   
  c1->SaveAs(name);
  outfile->cd();
  c1->Write(histName,TObject::kOverwrite);

  delete legend;

}

///===================================================
/// Plot an array of graphs
///===================================================
void PlotAll(TGraphErrors* g[],
             Int_t NPlots,
             vector<TString> plotNames,
             TString xAxisLabel,
             TString yAxisLabel,
             const char* name,
             const char* histName,
             TFile *outfile,
             Float_t YMin,  Float_t YMax,
             bool logx = kFALSE, bool logy = kFALSE) 
{
  // Canvas
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->Clear();
  c1->SetLogy(logy);
  c1->SetLogx(logx);
  
  // Colors
  Color_t colors[] = {kRed,kBlue,kGreen,kCyan,kMagenta,kViolet,kBlack,
                      kRed,kBlue,kGreen,kCyan,kMagenta,kViolet,kBlack,
                      kRed,kBlue,kGreen,kCyan,kMagenta,kViolet,kBlack,
                      kRed,kBlue,kGreen,kCyan,kMagenta,kViolet,kBlack};
  
  // Legend
  TLegend *legend = new TLegend(0.54,0.62,0.89,0.89);
  legend->SetFillColor(0);
  TLegendEntry *entry;

  // Plot name
  char plotName[500];

  /// Loop on plots
  for (Int_t plotItr = 0; plotItr < NPlots; plotItr++) {
    if( !g[plotItr] ) continue;
    g[plotItr]->GetXaxis()->SetTitle(xAxisLabel);
    g[plotItr]->GetYaxis()->SetTitle(yAxisLabel);
    if (YMin != YMax) g[plotItr]->GetYaxis()->SetRangeUser(YMin,YMax);
    g[plotItr]->SetMarkerStyle(plotItr+20);
    g[plotItr]->SetMarkerSize(1.7);
    g[plotItr]->SetTitle("");
    g[plotItr]->SetMarkerColor(colors[plotItr+1]);
    if (plotItr != 0) g[plotItr]->Draw("psame");
    else g[plotItr]->Draw("ap");
    c1->Update();  
   
    outfile->cd();
    sprintf(plotName,"%s_index_%d",histName,plotItr);
    g[plotItr]->Write(plotName,TObject::kOverwrite);
   
    entry = legend->AddEntry(g[plotItr],plotNames.at(plotItr),"p");
    entry->SetTextAlign(12);
    entry->SetTextColor(1);
  }
  legend->Draw();
  c1->Update();   
  c1->SaveAs(name);
  outfile->cd();
  c1->Write(histName,TObject::kOverwrite);

  delete legend;

}

///===================================================
/// Plot 2D histo profile
///===================================================
void PlotProfile(TH2* h2,
                 TString xAxisLabel,
                 TString yAxisLabel,
                 const char* name,
                 const char* histName,
                 TFile *outfile,
                 Float_t YMin,  Float_t YMax,
                 Float_t XMin = -1,  Float_t XMax = -1,
                 bool logx = kFALSE, bool logy = kFALSE) 
{
  // Canvas
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->Clear();
  c1->SetLogy(logy);
  c1->SetLogx(logx);

  TH1F *h2Prof = (TH1F*)h2->ProfileX();
  h2Prof->GetXaxis()->SetTitle(xAxisLabel);
  h2Prof->GetYaxis()->SetTitle(yAxisLabel);
  h2Prof->GetYaxis()->SetRangeUser(YMin,YMax);
  if (XMin != XMax) h2Prof->GetXaxis()->SetRangeUser(XMin,XMax);
  h2Prof->Draw();
  Plot(h2Prof,name,"",logx,logy);
  
  outfile->cd();
  c1->Write(histName,TObject::kOverwrite);
   
}

///===================================================
/// Plot both a 1D and 2D histogram
///===================================================
void Plot1DAnd2D(TH2F* hist, 
                 const char* Title2D, 
                 const char* Name2D,
                 const char* Title1D, 
                 const char* Name1D,
                 TFile *outfile,
                 Float_t YMin,  Float_t YMax,
                 TString XTitle = "", 
                 TString YTitle = "")
{
  hist->SetXTitle(XTitle);
  hist->SetYTitle(YTitle);
  ColzPlot(hist,Title2D);
  outfile->cd();
  hist->Write(Name2D,TObject::kOverwrite);
  PlotProfile(hist,
              XTitle,
              YTitle,
              Title1D,
              Name1D,
              outfile,
              YMin,YMax);
}


///===================================================
/// Plot 2D histo profile
///===================================================
void PlotDivided(TH1F* h1,TH1F* h2,
                 TString xAxisLabel,
                 TString yAxisLabel,
                 const char* name,
                 const char* histName,
                 TFile *outfile,
                 Float_t YMin = -1,  Float_t YMax = -1,
                 bool logx = kFALSE, bool logy = kFALSE,
                 Float_t XMin = -1,  Float_t XMax = -1) 
{
  //+++++++++++
  // Canvas
  //+++++++++++
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->Clear();
  c1->SetLogy(logy);
  c1->SetLogx(logx);
   
  Int_t nBins = h1->GetNbinsX();
  
  TH1F *h = new TH1F(histName,"",nBins,h1->GetBinLowEdge(1),h1->GetBinLowEdge(nBins)+h1->GetBinWidth(nBins));
  h->Sumw2();
  h1->Sumw2();
  h2->Sumw2();
  h->Divide(h1,h2,1.,1.,"B");
  h->SetLineColor(1);
  h->SetLineWidth(1);
  h->GetXaxis()->SetTitle(xAxisLabel);
  h->GetYaxis()->SetTitle(yAxisLabel);
  if (XMin != XMax) h->GetXaxis()->SetRangeUser(XMin,XMax);
  if (YMin != YMax) h->GetYaxis()->SetRangeUser(YMin,YMax);
  h->SetMarkerSize(1.7);
  h->SetMarkerStyle(21);
  h->SetMarkerColor(kBlue);
  h->SetStats(kFALSE);
  h->GetXaxis()->SetLabelSize(0.05);
  h->Draw("");
  h->Draw("e1same");  
  c1->Update();
  c1->SaveAs(name);
  outfile->cd();
  c1->Write(histName,TObject::kOverwrite); 
  
  delete h;
}

///===================================================
/// Plot 2D histo profile
///===================================================
void PlotBinnedProfile(TH2D* h2,
                       TGraphErrors *result,
                       TString xAxisLabel,
                       TString yAxisLabel,
                       const char* name,
                       const char* histName,
                       TFile *outfile,
                       Float_t binSize,
                       Float_t YMin,  Float_t YMax,
                       Float_t FitYMin = -1.,  Float_t FitYMax = -1.,
                       bool logx = kFALSE, bool logy = kFALSE, 
                       bool saveAsSigma = kFALSE) 
{

  //+++++++++++
  // Canvas
  //+++++++++++
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->Clear();
  c1->SetLogy(logy);
  c1->SetLogx(logx);

  //+++++++++++
  // Graph bins
  //+++++++++++
  Int_t nBins = h2->GetNbinsX();
  Double_t *x  = new Double_t[nBins];
  Double_t *y  = new Double_t[nBins];
  Double_t *ex = new Double_t[nBins];
  Double_t *ey = new Double_t[nBins];
  
  Double_t *sigx  = new Double_t[nBins];
  Double_t *sigy  = new Double_t[nBins];
  Double_t *sigex = new Double_t[nBins];
  Double_t *sigey = new Double_t[nBins];
      
  //+++++++++++
  // Histo Loop
  //+++++++++++
  TH1D *hp;
  char binPlotName[200];
  for (Int_t binX=1; binX <= nBins; binX++) {

    // Project histo
    c1->Clear();
    hp = h2->ProjectionY("",binX,binX);
    
    // Draw
    c1->cd();
    hp->Draw();
    c1->Update();

    // Fit the projection
    if (FitYMin == FitYMax) hp->Fit("gaus","q");
    else hp->Fit("gaus","q","",FitYMin,FitYMax);
    c1->Update();
    
    // Save the projected distribution
    sprintf(binPlotName,"%s_HistBin_%d",histName,binX);
    hp->SetXTitle(yAxisLabel);
    //Plot(hp,outfile);
    outfile->cd();
    hp->Write(binPlotName,TObject::kOverwrite);
    
    x[binX-1]   = (binSize*binX)-(binSize/2.);
    ex[binX-1]  = binSize/2.;
    y[binX-1]   = hp->GetFunction("gaus")->GetParameter(1);
    ey[binX-1]  = hp->GetFunction("gaus")->GetParError(1);
    
    sigx[binX-1]   = (binSize*binX)-(binSize/2.);
    sigex[binX-1]  = binSize/2.;
    sigy[binX-1]   = hp->GetFunction("gaus")->GetParameter(2)/y[binX-1];
    sigey[binX-1]  = hp->GetFunction("gaus")->GetParError(2)/y[binX-1];
    
    //cout << " x["<<binX-1<<"] =  " << x[binX-1] << endl;
    //cout << "ex["<<binX-1<<"] =  " << ex[binX-1] << endl;
    //cout << " y["<<binX-1<<"] =  " << y[binX-1] << endl;
    //cout << "ey["<<binX-1<<"] =  " << ey[binX-1] << endl;
    
  }
  
  //+++++++++++
  // Draw Graph
  //+++++++++++
  char graphName[200];
  sprintf(graphName,"%s_graph",histName);
  c1->Clear();
  result = new TGraphErrors(nBins,x,y,ex,ey);
  result->GetXaxis()->SetTitle(xAxisLabel);
  result->GetYaxis()->SetTitle(yAxisLabel);
  result->GetYaxis()->SetRangeUser(YMin,YMax);
  result->Draw("ap");
  c1->Update();
  if (!saveAsSigma) c1->SaveAs(name);
  outfile->cd();
  result->Write(graphName,TObject::kOverwrite);
  sprintf(graphName,"%s_canvas",histName);
  c1->Write(graphName,TObject::kOverwrite);
  
  sprintf(graphName,"%s_sig_graph",histName);
  c1->Clear();
  result = new TGraphErrors(nBins,sigx,sigy,sigex,sigey);
  result->GetXaxis()->SetTitle(xAxisLabel);
  result->GetYaxis()->SetTitle(yAxisLabel);
  //result->GetYaxis()->SetRangeUser(YMin,YMax);
  result->Draw("ap");
  c1->Update();
  if (saveAsSigma) c1->SaveAs(name);
  outfile->cd();
  result->Write(graphName,TObject::kOverwrite);
  sprintf(graphName,"%s_sig_canvas",histName);
  c1->Write(graphName,TObject::kOverwrite);
}


///===================================================
/// PLOT SAME: 2 HISTOS
///===================================================
void PlotSame(TH1F* h1, TH1F* h2, const char* name,
	      Char_t* legend1, Char_t* legend2, bool logy = kFALSE, bool logx = kFALSE)
{
  //plot
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->Clear();
  c1->SetLogy(logy);
  c1->SetLogx(logx);
  c1->SetBorderSize(2);
  //c1->SetGridx();
  //c1->SetGridy();

  //float max = 1.2*h1->GetMaximum();
  //h1->SetMaximum(max);
  //h1->SetMarkerStyle(22); h1->SetMarkerColor(2); h1->SetMarkerSize(1.2);
  h1->SetLineWidth(2); h2->SetLineWidth(2); 
  h1->SetLineColor(kRed); h2->SetLineColor(kBlue);
  h1->SetLineStyle(1); h2->SetLineStyle(2);
  h1->SetMarkerStyle(20); h2->SetMarkerStyle(22);
  h1->SetMarkerColor(kRed); h2->SetMarkerColor(kBlue);

  if(h1->GetMaximum()>h2->GetMaximum()) {
    h1->Draw("");
    h1->Draw("psame");
    h2->Draw("same");
    h2->Draw("psame");
    if(!h1->GetFillColor()) h1->Draw("same");
  } else {
    h2->Draw("");
    h2->Draw("psame");
    h1->Draw("same");
    h1->Draw("psame");
    if(!h2->GetFillColor()) h2->Draw("same");
  }


  //TLegend *leg=new TLegend(0.531609,0.497902,0.882184,0.594056,NULL,"brNDC");
  //TLegend *leg=new TLegend(0.172414,0.73951,0.522989,0.835664,NULL,"brNDC");
  TLegend *leg = new TLegend(0.531609,0.73951,0.882184,0.835664,NULL,"brNDC");
  //leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->AddEntry(h1,legend1);
  leg->AddEntry(h2,legend2);
  leg->Draw();
 
  if(name!="")
    c1->SaveAs(name);
}

///===================================================
/// PLOT SAME: 2 HISTOS
///===================================================
void PlotSame(TH1F* h1, 
              TH1F* h2, 
              TFile *outfile, 
              const char* name,
              const char* histName,
              Char_t* legend1, 
              Char_t* legend2, 
              bool logy = kFALSE, 
              bool logx = kFALSE,
              Float_t YMin = -1,  Float_t YMax = -1,
              Char_t* option = ""
   )
{
  //plot
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->Clear();
  c1->SetLogy(logy);
  c1->SetLogx(logx);
  c1->SetBorderSize(2);
  //c1->SetGridx();
  //c1->SetGridy();

  //float max = 1.2*h1->GetMaximum();
  //h1->SetMaximum(max);
  //h1->SetMarkerStyle(22); h1->SetMarkerColor(2); h1->SetMarkerSize(1.2);
  h1->SetLineWidth(2); h2->SetLineWidth(2); 
  h1->SetLineColor(kRed); h2->SetLineColor(kBlue);

  //Draw options
  TString drawOptFirst(option);
  TString drawOptSame = drawOptFirst == "" ? "same" : TString::Format("%s,same",option);
  
  if(h1->GetMaximum()>h2->GetMaximum()) {
    h1->Draw(drawOptFirst);
    if (YMin != YMax) h1->GetYaxis()->SetRangeUser(YMin,YMax);
    h2->Draw(drawOptSame);
    if(!h1->GetFillColor()) h1->Draw(drawOptSame);
  } else {
    h2->Draw(drawOptFirst);
    if (YMin != YMax) h2->GetYaxis()->SetRangeUser(YMin,YMax);
    h1->Draw(drawOptSame);
    if(!h2->GetFillColor()) h2->Draw(drawOptSame);
  }

  TLegend *leg = new TLegend(0.54,0.62,0.89,0.89);
  leg->SetLineStyle(1);
  leg->SetBorderSize(0);
  leg->SetLineWidth(1);
  leg->SetLineStyle(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->AddEntry(h1,legend1);
  leg->AddEntry(h2,legend2);
  leg->Draw();
 
  if(name!="") c1->SaveAs(name);
    
  if (outfile) {
    outfile->cd();
    c1->Write(TString(TString(histName)),TObject::kOverwrite);
  }
}

///===================================================
/// PLOT SAME: 2 HISTOS
///===================================================
void PlotSame(TH1F* h1, 
              TH1F* h2, 
              TH1F* h3,
              TFile *outfile, 
              const char* name,
              const char* histName,
              Char_t* legend1, 
	            Char_t* legend2, 
	            Char_t* legend3, 
	            bool logy = kFALSE, 
	            bool logx = kFALSE,
	            Float_t YMin = -1,  Float_t YMax = -1,
	            Char_t* option = ""
	           )
{
  //plot
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->Clear();
  c1->SetLogy(logy);
  c1->SetLogx(logx);
  c1->SetBorderSize(2);

  h1->SetLineWidth(2); h2->SetLineWidth(2); h3->SetLineWidth(2);  
  h1->SetLineColor(kRed); h2->SetLineColor(kBlue); h3->SetLineColor(kBlack);

  //Draw options
  TString drawOptFirst(option);
  TString drawOptSame = drawOptFirst == "" ? "same" : TString::Format("%s,same",option);
  
  if (h1->GetMaximum()>h2->GetMaximum()) {
    h1->Draw(drawOptFirst);
    if (YMin != YMax) h1->GetYaxis()->SetRangeUser(YMin,YMax);
    h2->Draw(drawOptSame); h3->Draw(drawOptSame);
    if(!h1->GetFillColor()) h1->Draw(drawOptSame);
  } else if (h2->GetMaximum() > h3->GetMaximum()) {
    h2->Draw(""); 
    if (YMin != YMax) h2->GetYaxis()->SetRangeUser(YMin,YMax);
    h1->Draw(drawOptSame); h3->Draw(drawOptSame);
    if(!h2->GetFillColor()) h2->Draw(drawOptSame);
  } else {
    h3->Draw("");
    if (YMin != YMax) h2->GetYaxis()->SetRangeUser(YMin,YMax);
    h1->Draw(drawOptSame); h2->Draw(drawOptSame);
    if(!h2->GetFillColor()) h2->Draw(drawOptSame);
  }

  TLegend *leg = new TLegend(0.54,0.62,0.89,0.89);
  leg->SetLineStyle(1);
  leg->SetBorderSize(0);
  leg->SetLineWidth(1);
  leg->SetLineStyle(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->AddEntry(h1,legend1);
  leg->AddEntry(h2,legend2);
  leg->AddEntry(h3,legend3);
  leg->Draw();
 
  if(name!="") c1->SaveAs(name);
    
  if (outfile) {
    outfile->cd();
    c1->Write(TString(TString(histName)),TObject::kOverwrite);
  }
}

///===================================================
/// PLOT SAME: 3 HISTOS
///===================================================
void PlotSame(TH1F* h1, TH1F* h2, TH1F* h3, const char* name = "",
        Char_t* legend1 = "1", Char_t* legend2 = "2", Char_t* legend3 = "3", 
        Char_t* xtitle = "", Char_t* ytitle = "",
        bool logy = "kFALSE")
{
  //plot
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->Clear();
  //c1->SetLogy(logy);
  c1->SetBorderSize(2);
  //c1->SetGridx();
  //c1->SetGridy();

  //float max = 1.2*h1->GetMaximum();
  //h1->SetMaximum(max);
  //h1->SetMarkerStyle(22); h1->SetMarkerColor(2); h1->SetMarkerSize(1.2);
  h1->SetLineWidth(2); h2->SetLineWidth(2); h3->SetLineWidth(2); 
  h1->SetLineColor(kRed); h2->SetLineColor(kBlue); h3->SetLineColor(kBlack); 

  TH1F* first; TH1F* second; TH1F* third;
  
  if ( (h1->GetMaximum() > h2->GetMaximum()) && 
       (h1->GetMaximum() > h3->GetMaximum()) ) {
       first=h1;
       if (h2->GetMaximum()>h3->GetMaximum()) {second=h2; third=h3;}
       else {second=h3; third=h2;}
  }
  else if (h1->GetMaximum() > h3->GetMaximum()) {first=h2; second=h1; third=h3;}
  else if (h1->GetMaximum() > h2->GetMaximum()) {first=h3; second=h1; third=h2;}
  else if (h2->GetMaximum() > h3->GetMaximum()) {first=h2; second=h3; third=h1;}
  else                                          {first=h3; second=h2; third=h1;}
  
  first->SetXTitle(xtitle);
  first->SetXTitle(ytitle);
  second->SetXTitle(xtitle);
  second->SetXTitle(ytitle);
  third->SetXTitle(xtitle);
  third->SetXTitle(ytitle);
  
  first->Draw("");
  second->Draw("same");
  third->Draw("same");

  //TLegend *leg=new TLegend(0.531609,0.497902,0.882184,0.594056,NULL,"brNDC");
  //TLegend *leg=new TLegend(0.172414,0.73951,0.522989,0.835664,NULL,"brNDC");
  TLegend *leg = new TLegend(0.531609,0.73951,0.882184,0.835664,NULL,"brNDC");
  //leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->AddEntry(h1,legend1);
  leg->AddEntry(h2,legend2);
  leg->AddEntry(h3,legend3);
  leg->Draw();

  if(logy) gPad->SetLogy();

  if(name!="")
    c1->SaveAs(name);
}


///===================================================
/// PLOT TAG RATE FUNCTION
///===================================================
void PlotTRF(TH1F* hp_tag, TH1F* hp_pred, TH1F* hp_spred)
{
  TH1F* pred = new TH1F(*hp_pred); pred->SetName("pred");
  pred->SetFillColor(5);
  hp_tag->SetMarkerSize(1.3);hp_tag->SetMarkerStyle(22);

  for(int i=1; i<=pred->GetNbinsX(); i++) {
    float s = TMath::Sqrt(hp_spred->GetBinContent(i));
    pred->SetBinError(i,s);
  }
  
  //plot
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if(!c1) {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->SetLogy(0);
  c1->Clear();

  hp_tag->Draw("e1");
  pred->Draw("e2same"); hp_tag->Draw("e1same");

}

///===================================================
/// PLOT CHI SQUARE TEST
///===================================================
void Chi2Test(TH1F* h1, TH1F* h2, double& chi2, double& prob, int& ndof)
{
  chi2 = 0;
  float v1,v2,e1,e2;
  for(int i=1; i<=h1->GetNbinsX(); i++) {
    v1 = h1->GetBinContent(i); e1 = h1->GetBinError(i);
    v2 = h2->GetBinContent(i); e2 = h2->GetBinError(i);
    float d = v1-v2;
    float s2 = e1*e1+e2*e2;
    if(s2!=0) chi2 += (d*d)/s2;
  }
  ndof = h1->GetNbinsX();
  prob = TMath::Prob(chi2,ndof);
}

///===================================================
/// GET EFFICIENCY
///===================================================
void getEff(TH1F* montecarlo, TH1F* reconstructed)
{
  TH1F* output = new TH1F("mm1","",
			  montecarlo->GetNbinsX(),
			  montecarlo->GetBinLowEdge(1),
			  montecarlo->GetBinLowEdge(static_cast<int>
						    (montecarlo->
						     GetBinLowEdge(1)+1)));
  
  Float_t v1,v2;
  for(int i=1; i<=montecarlo->GetNbinsX(); i++) {
    v1 = montecarlo->GetBinContent(i);
    v2 = reconstructed->GetBinContent(i);
    if(v1!=0) {
      float y = v2/float(v1);
      output->SetBinContent(i,y);
      output->SetBinError(i,TMath::Sqrt(y*(1-y)/v1));
    }
  }
  output->Fit("pol1","","",0,15);
}

///===================================================
/// GET b-TAG EFFICIENCY
///===================================================
void getBtagEff(char* name, TH1F* h_tag, TH1F* h_b, TH1F* h_c, TH1F* h_qcd,
		 TH1F* result)
{
  Float_t tags,b,c,qcd;
  for(int i=1; i<=h_tag->GetNbinsX(); i++) {
    tags = h_tag->GetBinContent(i);
    qcd = h_qcd->GetBinContent(i);
    b = h_b->GetBinContent(i);
    c = h_c->GetBinContent(i);
    if(tags!=0) {
      float y = (tags-qcd)/float(b+c);
      result->SetBinContent(i,y);
      result->SetBinError(i,TMath::Sqrt(y*(1-y)/(b+c)));
    }
  }
  result->SetName(name);
}



///===================================================
/// PLOT EFFICIENCY
///===================================================
/// This method asumes the "reconstructed" histogram has the montecarlo bins
/// matched so that the division is alway lees than 1.
void PlotEff(TH1F* montecarlo, TH1F* reconstructed, const char* title="", 
	     Char_t* xtitle="", Char_t* ytitle="", const char* name="", bool logy = 0,
	     float yMin = 0, float yMax = 0,
	     Char_t* formula = 0,float r1 = 0, float r2 = 0, 
	     TF1* overlaid = 0, char* label = 0)
{
  //Int_t nbins1 = montecarlo ->GetNbinsX();
  //Int_t nbins2 = reconstructed->GetNbinsX();
  Int_t nbins1 = montecarlo ->GetXaxis()->GetLast();
  Int_t nbins2 = reconstructed->GetXaxis()->GetLast();
  if(nbins1!=nbins2) {
    cout << "ERROR, both histograms must have the same number of bins" << endl;
    cout << endl;
    return;
  } 
  const Int_t n = nbins1; 
  
  montecarlo->SetStats(kFALSE);
  reconstructed->SetStats(kFALSE);

  Float_t *x = new Float_t[n];
  Float_t *y = new Float_t[n];
  Float_t *ex = new Float_t[n];
  Float_t *ey = new Float_t[n];

  Float_t v1,v2;
  Float_t xBin = montecarlo->GetBinLowEdge(1) + 
    (montecarlo->GetBinWidth(1))/2;
  for(int i=1; i<=nbins1; i++) {
    v1 = montecarlo->GetBinContent(i);
    v2 = reconstructed->GetBinContent(i);
    if(v1!=0) {
      x[i-1] = xBin;
      y[i-1]  = v2/float(v1);
      ex[i-1] = montecarlo->GetBinWidth(i)/2;
      ey[i-1] = sqrt(y[i-1]*(1-y[i-1])/v1);
    } else {
      x[i-1] = xBin;
      y[i-1] = 0;
      ex[i-1] = 0;
      ey[i-1] = 0;
    }
    xBin += montecarlo->GetBinWidth(i);
  }
  //define graph
  TGraphErrors * result = new TGraphErrors(n,x,y,ex,ey);
  result->SetMarkerStyle(20);
  result->SetMarkerColor(kBlue);
  //result->SetMarkerSize(0.5);

  //define frame
  float xd = x[n-1]-x[0];
  float xmin = x[0] - 0.1*xd;
  float xmax = x[n-1] + 0.1*xd;

  //calculate y limit.
  // if it is not provided in the constructor, take 20 percent above
  // the maximum value.
  float ymax = 0;
  float ymin = 1000;
  if(yMax) {
    ymax = yMax;
  } else {
    for(int u=0; u<n;u++) {
      if(y[u]>ymax) ymax = y[u];
    }
    for(int u=0; u<n;u++) {
      if(y[u]<ymin) ymin = y[u];
    }
    float yd = ymax-ymin;
    ymin -= 0.1*yd;
    ymax += 0.2*yd;
  }
  

  TH2F* frame = new TH2F("frame","",2,xmin,xmax,2,yMin,ymax);
  frame->SetXTitle(xtitle);
  frame->SetYTitle(ytitle);
  frame->SetTitle(title);
  frame->SetStats(kFALSE);
  
  //plot
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if(!c1) {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->SetLogy(0);
  c1->Clear();
  c1->SetBorderSize(2);
  c1->SetGridx(kFALSE);
  c1->SetGridy();
  if(logy) c1->SetLogy(1);
 
    
  //draw frame
  frame->Draw();
  c1->Modified();

  if(label) {
    TLatex* tex = new TLatex(0.2,0.85,label); tex->SetNDC();
    tex->SetTextSize(0.04); tex->SetTextColor(2); tex->SetLineWidth(2); 
    tex->Draw();
  }

  //draw eff.
  result->Draw("P");
  if(formula) {
    if(r1==0 && r2==0) 
      result->Fit(formula);
    else
      result->Fit(formula,"","",r1,r2);
  }
  if(overlaid) overlaid->Draw("same");

  if(name!="")
    c1->SaveAs(name);
}

///===================================================
/// PLOT EFFICIENCY
///===================================================
void PlotEff(TH1F* montecarlo, TH1F* reconstructed1, TH1F* reconstructed2,
	     const char* title="", 
	     const char* xtitle="", Char_t* ytitle="", const char* name="", bool logy = 0,
	     float yMin = 0, float yMax = 0,
	     Char_t* formula = 0, 
	     TF1* overlaid = 0, 
	      const char* legend1 = "Track-Jet",  const char* legend2 = "Cal-Jet")
{
  Int_t nbins1 = montecarlo->GetNbinsX();
  Int_t nbins2 = reconstructed1->GetNbinsX();
  if(nbins1!=nbins2) {
    cout << "ERROR, both histograms must have the same number of bins" << endl;
    cout << endl;
    return;
  } 
  const Int_t n = nbins1; 
  
  montecarlo->SetStats(kFALSE);
  reconstructed1->SetStats(kFALSE);
  reconstructed2->SetStats(kFALSE);

  Float_t *x = new Float_t[n];
  Float_t *y_1 = new Float_t[n];
  Float_t *y_2 = new Float_t[n];
  //Float_t *y_3 = new Float_t[n];
  Float_t *ex = new Float_t[n];
  Float_t *ey_1 = new Float_t[n];
  Float_t *ey_2 = new Float_t[n];
  //Float_t *ey_3 = new Float_t[n];

  Float_t v1,v2_1, v2_2;//, v2_3;
  Float_t xBin = montecarlo->GetBinLowEdge(1);
  for(int i=1; i<=nbins1; i++) {
    v1 = montecarlo->GetBinContent(i);
    v2_1 = reconstructed1->GetBinContent(i);
    v2_2 = reconstructed2->GetBinContent(i);
    //v2_3 = reconstructed3->GetBinContent(i);
    xBin += montecarlo->GetBinWidth(i);
    if(v1!=0) {
      x[i-1] = xBin;
      y_1[i-1]  = v2_1/float(v1);
      y_2[i-1]  = v2_2/float(v1);
      //y_3[i-1]  = v2_3/float(v1);
      ex[i-1] = montecarlo->GetBinWidth(i)/2;
      ey_1[i-1] = sqrt(y_1[i-1]*(1-y_1[i-1])/v1);
      ey_2[i-1] = sqrt(y_2[i-1]*(1-y_2[i-1])/v1);
      //ey_3[i-1] = sqrt(y_3[i-1]*(1-y_3[i-1])/v1);
    } else {
      x[i-1] = xBin;
      y_1[i-1] = 0;
      y_2[i-1] = 0;
      //y_3[i-1] = 0;
      ex[i-1] = 0;
      ey_1[i-1] = 0;
      ey_2[i-1] = 0;
      //ey_3[i-1] = 0;
    }
  }
  //define graphs
  TGraphErrors * result1 = new TGraphErrors(n,x,y_1,ex,ey_1);
  result1->SetMarkerStyle(20);
  result1->SetMarkerColor(kBlue);
  //result->SetMarkerSize(0.5);
  TGraphErrors * result2 = new TGraphErrors(n,x,y_2,ex,ey_2);
  result2->SetMarkerStyle(24);
  result2->SetMarkerColor(kRed);
  //result->SetMarkerSize(0.5);
  //TGraphErrors * result3 = new TGraphErrors(n,x,y_3,ex,ey_3);
  //result3->SetMarkerStyle(21);
  //result3->SetMarkerColor(kGreen);
  //result->SetMarkerSize(0.5);



  //define frame
  float xd = x[n-1]-x[0];
  float xmin = x[0] - 0.1*xd;
  float xmax = x[n-1] + 0.1*xd;

  //calculate y limit.
  // if it is not provided in the constructor, take 20 percent above
  // the maximum value.
  float ymax = 0;
  float ymin = 1000;
  if(yMax) {
    ymax = yMax;
  } else {
    for(int u=0; u<n;u++) {
      if(y_1[u]>ymax) ymax = y_1[u];
    }
    for(int u=0; u<n;u++) {
      if(y_1[u]<ymin) ymin = y_1[u];
    }
    float yd = ymax-ymin;
    ymin -= 0.1*yd;
    ymax += 0.2*yd;
  }
  

  TH2F* frame = new TH2F("frame","",2,xmin,xmax,2,yMin,ymax);
  frame->SetXTitle(xtitle);
  frame->SetYTitle(ytitle);
  frame->SetTitle(title);
  frame->SetStats(kFALSE);

  //plot
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->SetLogy(0);
  c1->Clear();
  c1->SetBorderSize(2);
  c1->SetGridx();
  c1->SetGridy();
  if(logy) c1->SetLogy();
  
  //draw frame
  frame->Draw();
  c1->Modified();

  //draw eff.
  result1->Draw("P");
  result1->SetFillStyle(0);
  result1->SetFillColor(0);

  result2->Draw("P");
  result2->SetFillStyle(0);
  result2->SetFillColor(0);
  //result3->Draw("P");

  TLegend *leg=new TLegend(0.52,0.65,0.88,0.88,NULL,"brNDC");
  //TLegend *leg = new TLegend(0.17,0.78,0.42,0.88,NULL,"brNDC");
  //leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->AddEntry(result1,legend1);
  leg->AddEntry(result2,legend2);
  //leg->AddEntry(result3,"Run I cone 0.7");
  leg->Draw();
 
  
  if(formula) result1->Fit(formula);

  if(overlaid) overlaid->Draw("same");

  if(name!="")
    c1->SaveAs(name);
}

///===================================================
/// PLOT EFFICIENCY
///===================================================
void PlotEff(TH1F* montecarlo, TH1F* reconstructed1, TH1F* reconstructed2, TH1F* reconstructed3,
	     const char* title="", 
	     const char* xtitle="", const char* ytitle="", const char* name="", bool logy = 0,
	     float yMin = 0, float yMax = 0,
	     Char_t* formula = 0, 
	     TF1* overlaid = 0, 
	     const char* legend1 = "Track-Jet",  
	     const char* legend2 = "Cal-Jet",
	     const char* legend3 = "Cal-Jet")
{
  Int_t nbins1 = montecarlo->GetNbinsX();
  Int_t nbins2 = reconstructed1->GetNbinsX();
  if(nbins1!=nbins2) {
    cout << "ERROR, both histograms must have the same number of bins" << endl;
    cout << endl;
    return;
  } 
  const Int_t n = nbins1; 
  
  montecarlo->SetStats(kFALSE);
  reconstructed1->SetStats(kFALSE);
  reconstructed2->SetStats(kFALSE);
  reconstructed3->SetStats(kFALSE);

  Float_t *x = new Float_t[n];
  Float_t *y_1 = new Float_t[n];
  Float_t *y_2 = new Float_t[n];
  Float_t *y_3 = new Float_t[n];
  Float_t *ex = new Float_t[n];
  Float_t *ey_1 = new Float_t[n];
  Float_t *ey_2 = new Float_t[n];
  Float_t *ey_3 = new Float_t[n];

  Float_t v1,v2_1, v2_2, v2_3;
  Float_t xBin = montecarlo->GetBinLowEdge(1);
  for(int i=1; i<=nbins1; i++) {
    v1 = montecarlo->GetBinContent(i);
    v2_1 = reconstructed1->GetBinContent(i);
    v2_2 = reconstructed2->GetBinContent(i);
    v2_3 = reconstructed3->GetBinContent(i);
    xBin += montecarlo->GetBinWidth(i);
    if(v1!=0) {
      x[i-1] = xBin;
      y_1[i-1]  = v2_1/float(v1);
      y_2[i-1]  = v2_2/float(v1);
      y_3[i-1]  = v2_3/float(v1);
      ex[i-1] = montecarlo->GetBinWidth(i)/2;
      ey_1[i-1] = sqrt(y_1[i-1]*(1-y_1[i-1])/v1);
      ey_2[i-1] = sqrt(y_2[i-1]*(1-y_2[i-1])/v1);
      ey_3[i-1] = sqrt(y_3[i-1]*(1-y_3[i-1])/v1);
    } else {
      x[i-1] = xBin;
      y_1[i-1] = 0;
      y_2[i-1] = 0;
      y_3[i-1] = 0;
      ex[i-1] = 0;
      ey_1[i-1] = 0;
      ey_2[i-1] = 0;
      ey_3[i-1] = 0;
    }
  }
  //define graphs
  TGraphErrors * result1 = new TGraphErrors(n,x,y_1,ex,ey_1);
  result1->SetMarkerStyle(20);
  result1->SetMarkerColor(kBlue);
  //result->SetMarkerSize(0.5);
  TGraphErrors * result2 = new TGraphErrors(n,x,y_2,ex,ey_2);
  result2->SetMarkerStyle(24);
  result2->SetMarkerColor(kRed);
  //result->SetMarkerSize(0.5);
  TGraphErrors * result3 = new TGraphErrors(n,x,y_3,ex,ey_3);
  result3->SetMarkerStyle(21);
  result3->SetMarkerColor(kGreen);
  //result->SetMarkerSize(0.5);



  //define frame
  float xd = x[n-1]-x[0];
  float xmin = x[0] - 0.1*xd;
  float xmax = x[n-1] + 0.1*xd;

  //calculate y limit.
  // if it is not provided in the constructor, take 20 percent above
  // the maximum value.
  float ymax = 0;
  float ymin = 1000;
  if(yMax) {
    ymax = yMax;
  } else {
    for(int u=0; u<n;u++) {
      if(y_1[u]>ymax) ymax = y_1[u];
    }
    for(int u=0; u<n;u++) {
      if(y_1[u]<ymin) ymin = y_1[u];
    }
    float yd = ymax-ymin;
    ymin -= 0.1*yd;
    ymax += 0.2*yd;
  }
  

  TH2F* frame = new TH2F("frame","",2,xmin,xmax,2,yMin,ymax);
  frame->SetXTitle(xtitle);
  frame->SetYTitle(ytitle);
  frame->SetTitle(title);
  frame->SetStats(kFALSE);

  //plot
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->SetLogy(0);
  c1->Clear();
  c1->SetBorderSize(2);
  c1->SetGridx();
  c1->SetGridy();
  if(logy) c1->SetLogy();
  
  //draw frame
  frame->Draw();
  c1->Modified();

  //draw eff.
  result1->Draw("P");
  result1->SetFillStyle(0);
  result1->SetFillColor(0);

  result2->Draw("P");
  result2->SetFillStyle(0);
  result2->SetFillColor(0);
  result3->Draw("P");

  TLegend *leg=new TLegend(0.62,0.35,0.88,0.50,NULL,"brNDC");
  //TLegend *leg = new TLegend(0.17,0.78,0.42,0.88,NULL,"brNDC");
  //leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->AddEntry(result1,legend1,"p");
  leg->AddEntry(result2,legend2,"p");
  leg->AddEntry(result3,legend3,"p");
  leg->Draw();
 
  
  if(formula) result1->Fit(formula);

  if(overlaid) overlaid->Draw("same");

  if(name!="")
    c1->SaveAs(name);
}

void PlotTagProb(TH1F* jets, TH1F* positiveTags, TH1F* negativeTags,
		 const char* title="", Char_t* xtitle="", Char_t* name="",
		 float yMin = 0, float yMax = 0, TF1* fp = 0, TF1* fn = 0, 
		 TF1* overlaid = 0)
{
  Int_t nbins1 = jets->GetNbinsX();
  Int_t nbins2 = positiveTags->GetNbinsX();
  Int_t nbins3 = negativeTags->GetNbinsX();
  if(nbins1!=nbins2 || nbins1!=nbins3) {
    cout << "ERROR, all histograms must have the same number of bins" << endl;
    cout << endl;
    return;
  } 
  const Int_t n = nbins1; 

  Float_t *x = new Float_t[n];
  Float_t *y_1 = new Float_t[n];
  Float_t *y_2 = new Float_t[n];
  Float_t *ex = new Float_t[n];
  Float_t *ey_1 = new Float_t[n];
  Float_t *ey_2 = new Float_t[n];

  Float_t v1,v2_1, v2_2;
  Float_t xBin = jets->GetBinLowEdge(1);
  for(int i=1; i<=nbins1; i++) {
    v1 = jets->GetBinContent(i);
    v2_1 = positiveTags->GetBinContent(i);
    v2_2 = negativeTags->GetBinContent(i);
    
    xBin += jets->GetBinWidth(i);
    if(v1!=0) {
      //x[i-1] = xBin;
      x[i-1] = jets->GetBinCenter(i);
      y_1[i-1]  = v2_1/float(v1);
      y_2[i-1]  = v2_2/float(v1);

      ex[i-1] = jets->GetBinWidth(i)/2;
      ey_1[i-1] = sqrt(y_1[i-1]*(1-y_1[i-1])/v1);
      ey_2[i-1] = sqrt(y_2[i-1]*(1-y_2[i-1])/v1);

    } else {
      //x[i-1] = xBin;
      x[i-1] = jets->GetBinCenter(i);
      y_1[i-1] = 0;
      y_2[i-1] = 0;

      ex[i-1] = 0;
      ey_1[i-1] = 0;
      ey_2[i-1] = 0;
    }
  }
  //define graphs
  TGraphErrors * result1 = new TGraphErrors(n,x,y_1,ex,ey_1);
  result1->SetMarkerStyle(21);
  result1->SetMarkerColor(kBlue);
  result1->SetFillStyle(0);
  result1->SetFillColor(0);

  TGraphErrors * result2 = new TGraphErrors(n,x,y_2,ex,ey_2);
  result2->SetMarkerStyle(25);
  result2->SetMarkerColor(kRed);
  result2->SetFillStyle(0);
  result2->SetFillColor(0);


  //define frame
  float xd = x[n-1]-x[0];
  float xmin = x[0] - 0.1*xd;
  float xmax = x[n-1] + 0.1*xd;

  //calculate y limit.
  // if it is not provided in the constructor, take 20 percent above
  // the maximum value.
  float ymax = 0;
  float ymin = 1000;
  if(yMax) {
    ymax = yMax;
  } else {
    for(int u=0; u<n;u++) {
      if(y_1[u]>ymax) ymax = y_1[u];
    }
    for(int u=0; u<n;u++) {
      if(y_1[u]<ymin) ymin = y_1[u];
    }
    float yd = ymax-ymin;
    ymin -= 0.1*yd;
    ymax += 0.2*yd;
  }
  
  TH2F* frame = new TH2F("frame","",2,xmin,xmax,2,yMin,ymax);
  frame->SetXTitle(xtitle);
  frame->SetTitle(title);

  //plot
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->Clear();
  c1->SetBorderSize(2);
  c1->SetGridx();
  c1->SetGridy();
  
  //draw frame
  frame->Draw();
  c1->Modified();

  //draw eff.
  result1->Draw("P");
  result2->Draw("P");

  TLegend *leg = new TLegend(0.2,0.75,0.5,0.85,NULL,"brNDC");
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->SetTextSizePixels(20);
  leg->AddEntry(result1,"positive");
  leg->AddEntry(result2,"negative");
  leg->Draw();


  if(fp) {
    gStyle->SetOptFit(111);
    result1->Fit("fp"); 
    c1->Update();
    TPaveStats *stats1 = (TPaveStats*)(gPad->GetPrimitive("stats"));
    if(stats1) {
      stats1->SetName("stats1");
      stats1->SetX1NDC(0.60);
      stats1->SetX2NDC(0.90);
      stats1->SetY1NDC(0.80);
      stats1->SetY2NDC(0.90);
      stats1->SetLineColor(4);
      stats1->SetTextColor(4);
    }
  }

  if(fn) {
    result2->Fit("fn","RE+");
    c1->Update();
    TPaveStats *stats2 = (TPaveStats*)(gPad->GetPrimitive("stats"));
    if(stats2) {
      stats2->SetName("stats2");
      stats2->SetX1NDC(0.60);
      stats2->SetX2NDC(0.90);
      stats2->SetY1NDC(0.70);
      stats2->SetY2NDC(0.80);
      stats2->SetLineColor(2);
      stats2->SetTextColor(2);
    }
    gStyle->SetOptFit(0);
  }

  
  
  if(overlaid) overlaid->Draw("same");
  
  if(name!="")
    c1->SaveAs(name);
}






/// Plots efficiency
void PlotTagRate(TH2F* ALL, TH2F* TAGGED, const char* title="", 
                 Char_t* xtitle="", Char_t* name="")
{
  
   Int_t nbins1x = ALL ->GetXaxis()->GetLast();
   Int_t nbins2x = TAGGED->GetXaxis()->GetLast();
   Int_t nbins1y = ALL ->GetYaxis()->GetLast();
   if(nbins1x!=nbins2x) {
      cout << "ERROR, both histograms must have the same number of bins" << endl;
      cout << endl;
      return;
   } 
   TString title_compact = TString::Format("%s;%s;%s",title,xtitle,name);
   //TH2F* TagRate = new TH2F("TagRate",nbins1x,nbins1y,);
   TH2F* TagRate = new TH2F("TagRate",title_compact,9,1.5,10.5,15,-2,2);
   
   Float_t v1,v2;
   for(int i=1; i<=nbins1x; i++) {
      for(int j=1; j<=nbins1y; j++) {
         v1 = ALL->GetBinContent(i,j);
         v2 = TAGGED->GetBinContent(i,j);
         
         if(v1!=0) {
            TagRate->SetBinContent(i,j,v2/float(v1));
         }  else {
            TagRate->SetBinContent(i,j,0);
         }
      }
   }
   

  //define graph

  //plot
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->SetLogy(0);
  c1->Clear();
  c1->SetBorderSize(2);
  c1->SetGridx();
  c1->SetGridy();
  TagRate->Draw("LEGO2");

  c1->SaveAs(name);
}





//----------------------------------------------
// Resolutions
//----------------------------------------------
void PlotResolutionMean(TH2F* hist, const char* title="", 
			Char_t* xtitle="", Char_t* name="",
			Char_t* formula = "pol1")
{
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->SetGrid();

  TH2F* h = (TH2F*) hist->Clone();
  h->SetName("h");
  h->FitSlicesY();
  
 
  TH1D *h_1 = (TH1D*)gDirectory->Get("h_1");
  h_1->SetMarkerStyle(20);
  h_1->SetMarkerColor(2);
  h_1->SetTitle(title);
  h_1->SetXTitle(xtitle);
  h_1->Fit(formula);
  h_1->Draw();

  if(name!="")
    c1->SaveAs(name);
}


//----------------------------------------------
// Resolutions
//----------------------------------------------
void PlotResolutionSigma(TH2F* hist, const char* title="", 
			 Char_t* xtitle="", Char_t* name="",
			 Char_t* formula = "pol1")
{
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }
  c1->SetGrid();

  TH2F* h = (TH2F*) hist->Clone();
  h->SetName("h");
  h->FitSlicesY();
  
  
  TH1D *h_2 = (TH1D*)gDirectory->Get("h_2");
  h_2->SetMarkerStyle(20);
  h_2->SetMarkerColor(4);
  h_2->SetTitle(title);
  h_2->SetXTitle(xtitle);
  h_2->Fit(formula);
  h_2->Draw();

  if(name!="")
    c1->SaveAs(name);
}

void PlotResolution2(TH2F* hist, const char* title="", 
		     Char_t* xtitle="", Char_t* name="",
		     Char_t* formula = "pol1")
{
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear();} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
  }

  TH2F* h = (TH2F*) hist->Clone();
  h->SetName("h");
  h->FitSlicesY();
  
 
  TH1D *h_1 = (TH1D*)gDirectory->Get("h_1");
  h_1->SetMarkerStyle(20);
  h_1->SetMarkerColor(2);
  h_1->SetTitle(title);
  h_1->SetXTitle("xtitle");

  TH1D *h_2 = (TH1D*)gDirectory->Get("h_2");
  h_2->SetMarkerStyle(20);
  h_2->SetMarkerColor(4);
  h_2->SetTitle(title);
  h_2->SetXTitle(xtitle);

  TPad* pad1 = new TPad("pad1","pad",0.02,0.52,0.98,0.98);
  pad1->Draw(); 

  TPad* pad2 = new TPad("pad2","pad",0.02,0.02,0.98,0.48);
  pad2->Draw();
  
  pad1->cd();
  pad1->SetGrid(); 
  h_1->Fit(formula);
  h_1->Draw();
  
  pad2->cd();
  pad2->SetGrid(); 
  h_2->Fit(formula);
  h_2->Draw();

  if(name!="")
    c1->SaveAs(name);
}




//----------------------------------------------
// D0Track
//----------------------------------------------
void PlotTrack(Float_t p1, Float_t p2, Float_t p3, Float_t p4, Float_t p5, 
	       Int_t color = 4, Int_t style = 1, Float_t dim = 1)
{
  
  Float_t CLIGHT = 2.99792458e10;
  Float_t BFAC = 1.0e-13 * CLIGHT;

  Double_t phi_dir = p3;
  Double_t xp =  p1 * sin(phi_dir);
  Double_t yp = -p1 * cos(phi_dir);
  Double_t BMAG = -2.0;            // magnetic field is reversed...
  Double_t CONSB = BFAC * BMAG;    // BFAC = 1.0e-13*CLIGHT (trfutil/TRFMath.h)
  Double_t  r =  1./p5/CONSB;
  Double_t x0 = xp + r*sin(phi_dir);
  Double_t y0 = yp - r*cos(phi_dir);
  Double_t R = -r;

 
  Float_t sign = -1.;

  Float_t range;
  if(TMath::Abs(1/p5)<4) {
    range = TMath::Abs(1/p5)/4*dim/TMath::Abs(R);}
  else { range = dim/TMath::Abs(R);}
   
  Double_t x[100],y[100]; //z[100];   
  for (Int_t i=0; i<100; i++) {
    x[i] = x0 + R*TMath::Sin((i-50)*sign*range/50.0+phi_dir);
    y[i] = y0 - R*TMath::Cos((i-50)*sign*range/50.0+phi_dir);
    //z[i] = z0 + R*p4*(-i*range/100.0+phi_dir);
  }

  TPolyLine* track = new TPolyLine(100, x, y);
  track->SetLineWidth(1);
  track->SetLineColor(color);
  track->SetLineStyle(style);
  track->Draw();
}


void PlotTrackZ(float z, float pz, float px, int color = 4, int style = 1)
//float dim = 1)
{
  TLine* l = new TLine(z,0,z+pz,px/2);
  l->SetLineStyle(style);
  l->SetLineWidth(2);
  l->SetLineColor(color);
  l->Draw();
}



//----------------------------------------------
// D0Track
//----------------------------------------------
void PlotLinealTrack(Float_t p1, Float_t p2, Float_t p3, Float_t p4, 
		     Float_t p5, Int_t color = 4, Int_t style = 1)
{
  Float_t xdca = p1*sin(p3);
  Float_t ydca = -p1*cos(p3);
  
  Float_t CLIGHT = 2.99792458e10;
  Float_t BFAC = 1.0e-13 * CLIGHT;
  Float_t c = (-2*BFAC*p5);
  Float_t b = tan(p3) - 2*c*xdca;
  Float_t a = ydca - c*xdca*xdca-b*xdca;
  
  TF1 *track = new TF1("track","[2]*x*x+[1]*x+ [0]",-100,100);
  track->SetParameter(0,a);
  track->SetParameter(1,b);      
  track->SetParameter(2,c);      
  track->SetLineWidth(2);
  track->SetLineColor(color);
  track->SetLineStyle(style);
  track->DrawCopy("LSAME");
}

//----------------------------------------------
// D0Track
//----------------------------------------------
void PlotLinealTrack(Float_t* p, Int_t color = 4, Int_t style = 1)
{
  PlotLinealTrack(p[0],p[1],p[2],p[3],p[4],color,style);
}



//-----------------------------------------------------------
// D0Vertex
//-----------------------------------------------------------
void PlotVertex(Float_t x, Float_t y, Float_t fraction = 20, Int_t color = 2, 
		Int_t style = 1, Float_t dim = 1.)
{
  Float_t radius = dim/fraction;
  TEllipse* vertex = new TEllipse(x,y,radius);
  vertex->SetLineWidth(1);
  vertex->SetLineStyle(style);
  vertex->SetLineColor(color);
  vertex->SetFillColor(color);
  vertex->Draw();
}

//-----------------------------------------------------------
// D0Vertex
//-----------------------------------------------------------
void PlotVertex(Float_t* x, Float_t fraction = 20, Int_t color = 2, 
		Int_t style = 1, Float_t dim = 1.)
{
  PlotVertex(x[0],x[1],fraction,color,style,dim);
}

//-----------------------------------------------------------
// D0Track
//-----------------------------------------------------------
void PlotLine(float x0, float y0, float x1, float y1, 
	      Int_t color = 2, Int_t style = 1, Float_t width = 1.0, 
	      Float_t dim = 1.)
{

  //float xmax = TMath::Abs(dim/2*cos(phi));
  TLine* l1 = new TLine(x0,y0,x1,y1);
  l1->SetLineColor(color);
  l1->SetLineStyle(style);
  l1->SetLineWidth(static_cast<Int_t>(width));
  l1->Draw(); 
}

//-----------------------------------------------------------
// JET
//-----------------------------------------------------------
void PlotJet(Float_t phi, Float_t pt, Int_t color = 2,
	     Int_t style = 1, Float_t dim = 1.)
{
  /*
  Float_t x0,y0,x1,y1,x_limit;
  x0 = 0.;
  y0 = 0;

  float xmax = TMath::Abs(dim/2*cos(phi));

  //if(pt<=80) {
  //x_limit = (pt/80)*xmax;} 
  //else {x_limit = xmax;}
  x_limit = xmax;


  if(phi>(3*TMath::Pi()/2) || phi<TMath::Pi()/2) {x1 = x_limit;} 
  else {x1 = -x_limit;}
  y1 = tan(phi)*x1;
  
  TLine* l1 = new TLine(x0,y0,x1,y1);
  l1->SetLineColor(color);
  l1->SetLineStyle(style);
  l1->SetLineWidth(3);
  l1->Draw(); 
  */

  float x = TMath::Sqrt(dim*dim/(1+TMath::Tan(phi)*TMath::Tan(phi)));
  float y = TMath::Tan(phi)*x;

  if(phi>=TMath::Pi()/2 && phi< TMath::Pi()) {x = -1*x; y=-1*y;}
  if(phi>= -TMath::Pi() && phi<-TMath::Pi()/2) {x = -1*x; y=-1*y;}
  float s = dim/40*(pt/20);
  TBox* cir = new TBox(x-s,y-s,x+s,y+s);
  cir->SetLineWidth(2);
  cir->SetLineColor(color);
  cir->SetFillColor(color);
  cir->Draw();


}


//-----------------------------------------------------------
// JET
//-----------------------------------------------------------
void PlotMuon(Float_t phi, Float_t pt, Int_t color = 3,
	     Int_t style = 1, Float_t dim = 1.)
{

  float x = TMath::Sqrt(dim*dim/(1+TMath::Tan(phi)*TMath::Tan(phi)))*1.1;
  float y = TMath::Tan(phi)*x;
  if(phi>=TMath::Pi()/2 && phi< TMath::Pi()) {x = -1*x; y=-1*y;}
  if(phi>= -TMath::Pi() && phi<-TMath::Pi()/2) {x = -1*x; y=-1*y;}
  float s = dim/40;
  TBox* cir = new TBox(x-s,y-s,x+s,y+s);
  cir->SetLineStyle(style);
  cir->SetLineWidth(2);
  cir->SetLineColor(color);
  cir->SetFillColor(color);
  cir->Draw();


}


//-----------------------------------------------------------
// Detector
//-----------------------------------------------------------
void DisplayDetector(const char* title, Float_t x1, Float_t y1, 
		     Float_t x2, Float_t y2, int color = 0, bool circle = 1)
{
  //Canvas
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear(); c1->SetFillColor(color);} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
    c1->SetFillColor(color);
  }  

  //define the canvas range
  TH2F *hr = (TH2F*)gROOT->FindObject("hr");
  if (hr) {
	  delete hr;
	  hr = 0;
  }
  hr = new TH2F("hr",title,2,x1,x2,2,y1,y2);
  hr->SetXTitle("x [cm]");
  hr->SetYTitle("y [cm]");
  hr->GetXaxis()->SetTitleSize(0.05);
  hr->GetYaxis()->SetTitleSize(0.05);
  hr->SetNdivisions(6,"X");
  hr->SetNdivisions(6,"Y");

  hr->GetXaxis()->SetAxisColor(1);
  hr->GetXaxis()->SetLabelColor(1);
  hr->GetXaxis()->SetTitleColor(1);
  hr->GetYaxis()->SetAxisColor(1);
  hr->GetYaxis()->SetLabelColor(1);
  hr->GetYaxis()->SetTitleColor(1);

  hr->Draw();
  float x_c = x1 + (x2-x1)/2;
  float y_c = y1 + (y2-y1)/2;

  if(circle) {
    TEllipse* cir = new TEllipse(x_c,y_c,x2-x_c, y2-y_c);
    cir->SetLineWidth(2);
    cir->SetLineColor(1);
    cir->Draw();
  }
}

//-----------------------------------------------------------
// Detector
//-----------------------------------------------------------
void DisplayDetector(const char* title, Float_t dim = 50, int color = 0, 
		     bool circle = 1)
{
  DisplayDetector(title,-dim,-dim,dim,dim,color,circle);
}


//-----------------------------------------------------------
// Detector
//-----------------------------------------------------------
void Detector(const char* title, Float_t x1 = -50, Float_t y1 = -50, 
	      Float_t x2 = 50, Float_t y2 = 50, int color = 0, 
	      bool circle = 1) 
{
  //Canvas
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) {c1->Clear(); c1->SetFillColor(color);} 
  else {
    style();
    c1 = (TCanvas*)gROOT->FindObject("c1");
    c1->SetFillColor(color);
  }  

  DisplayDetector(title,x1,y1,x2,y2,color,circle);
}


//-----------------------------------------------------------
// Detector
//-----------------------------------------------------------
void Detector(Float_t dim = 50, int color = 0, bool circle = 1) 
{
  Detector("",-dim,-dim,dim,dim,color,circle);
}


//-----------------------------------------------------------
// Detector
//-----------------------------------------------------------
void CalDetector()
{
  //define the canvas range
  TH2F *hr = new TH2F("hr","Calorimeter cells",2,-4,4,2,0,20);
  hr->SetXTitle("phi");
  hr->SetYTitle("layer");
  hr->GetXaxis()->SetTitleSize(0.05);
  hr->GetYaxis()->SetTitleSize(0.05);
  hr->SetNdivisions(10,"X");
  hr->SetNdivisions(10,"Y");
  hr->Draw();
}
