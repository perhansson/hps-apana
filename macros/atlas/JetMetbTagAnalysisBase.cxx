#include "JetMetbTagAnalysisBase.h"
#include "TMath.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TGraph.h"
#include "TArrow.h"
#include "TEllipse.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TH2.h"
#include "TTree.h"
#include "TBranch.h"
#include "TLorentzVector.h"
#include "TBox.h"
#include <string>
#include <vector>
#include <iostream>
#include "../../../RootUtils/trunk/Util.cpp"

using namespace std;


///===========================================///
///  CONSTRUCTOR
///===========================================///
JetMetbTagAnalysisBase::JetMetbTagAnalysisBase(TTree *tree, bool isDebug) 
                                              //JetMetbTagAnalysisBase::JetMetbTagAnalysisBase(TTree *tree, bool isDebug) : SlimJetMetbTriggerTree(tree)
//JetMetbTagAnalysisBase::JetMetbTagAnalysisBase(TTree *tree, bool isDebug) : SlimSlimJetMetbTriggerTree(tree)
{
  cout << endl;
  cout << endl;
  cout << "--------------------------------" << endl;
  cout << "Common Root Tuple Analysis "      << endl;
  if(tree)  
     cout << "   Number of events = "           << tree->GetEntries() << endl;
  else   
     cout << "   NO tree" << endl;
  cout << "--------------------------------" << endl << endl;
  
  TString baseDir("plots/");
  plotpath = TString(baseDir);
  plotext  = TString(".png");
  
  m_eventCounter = 10000;
  m_maxEvents    = -1;
  
  
  m_fDebug          = isDebug;
  
  m_rebin = -1;
}

///===========================================///
///  DESTRUCTOR
///===========================================///
JetMetbTagAnalysisBase::~JetMetbTagAnalysisBase() {
}

///=========================================
/// SetPlotPathAndExt
///=========================================
void JetMetbTagAnalysisBase::SetPlotPathAndExt(std::string runType, std::string lumiFlag) 
{
    cout << "In SetPlotPathAndExt()" << endl;

/// Set the output directory and file types accordingly
    TString baseDir("/Users/fizisist/Work/ATLAS/JetVtxAssoc/Plots/");
    plotpath = TString(baseDir + "misal1_mc12.005200.T1_McAtNlo_Jimmy/");
    lumi     = TString("_" + lumiFlag);
    plotext  = TString("" + lumi + ".png");
    
    if (runType == "note") {
      plotpath = TString(baseDir + "misal1_mc12.005200.T1_McAtNlo_Jimmy/");
      plotext  = TString("" + lumi + ".pdf");
    }
    else if (runType == "plots") {
      plotpath = TString(baseDir + "misal1_mc12.005200.T1_McAtNlo_Jimmy/");
      plotext  = TString("" + lumi + ".png");
    }
    
}

///=========================================
/// SetPlotTypeAndLumi
///=========================================
void JetMetbTagAnalysisBase::SetPlotTypeAndLumi(TString plotType, TString lumiString) 
{
/// Set the output directory and file types accordingly
    lumi = TString( "_" + lumiString);
    plotext  = TString(lumi + plotType);
    
    cout << "In SetPlotTypeAndLumi():   " << plotext << endl;

}

///=========================================
/// SetOutputDirectory
///=========================================
void JetMetbTagAnalysisBase::SetOutputDirectory(TString outDir) 
{
    cout << "SetOutputDirectory():      " << outDir << endl;
    plotpath  = outDir;
}

///=========================================
/// SetOutputRootFile
///=========================================
void JetMetbTagAnalysisBase::SetOutputRootFile(TString outFile) 
{
    cout << "SetOutputRootFile():       " << outFile << endl;
    outRootFile = outFile;
}

///=========================================
/// SetEventCounter
///=========================================
void JetMetbTagAnalysisBase::SetEventCounter(Long64_t counter)
{
   cout << "SetEventCounter():         Event counter = " << counter << endl;
   m_eventCounter = counter;
}


///=========================================
/// SetMaxEvents
///=========================================
void JetMetbTagAnalysisBase::SetMaxEvents(Long64_t maxEvents)
{
   cout << "SetMaxEvents():            Max events = " << maxEvents << endl;
   m_maxEvents = maxEvents;
}


TH1* JetMetbTagAnalysisBase::FindObjectInFile(TString filepath,TString plotNames) {
   cout << "In FindObject()" << endl;
   TFile* f = 0;
   f = (TFile*)gROOT->FindObject(filepath.Data());
   if(!f) {
      cout << "this file " << filepath << " was not open -> open it" << endl;
      f = new TFile(filepath.Data());      
   }
   
   f->cd();
   
   TH1* h=0;
   if(f->IsOpen()) {
      h=(TH1*)gROOT->FindObject((const char*)(plotNames));
   }
   else {
      cout << "Could not open file " << filepath << endl;
      //exit(-1);
   }
   if(!h) {
      cout << "Could not find histogram " << plotNames << endl;
      //exit(-1);      
   }
   return h;   
}


///=========================================
/// Combined Response plots
///=========================================
void JetMetbTagAnalysisBase::makeCombinedPlots(TString filePath,
                                               TString plotNames[60], 
                                               TString legend[60], 
                                               Int_t NPlots, 
                                               TString xAxis,
                                               TString yAxis,
                                               TString name,
                                               Float_t YMin,  Float_t YMax,
                                               bool drawNorm,
                                               bool logx, bool logy,
                                               Float_t XMin,  Float_t XMax,
                                               bool drawMean,TString opt,Int_t dataIndex,
                                               TString plotLabel)
{

  cout << "In makeCombinedPlots()" << endl;

  TFile *outfile = new TFile((const char*)(TString(plotpath + outRootFile)),"UPDATE");
  outfile->cd();
 
  /// Histograms
  TH1F *histo[60];
  bool found = true;
  for (Int_t iter = 0; iter < NPlots; iter++) {
     histo[iter] = (TH1F*)FindObjectInFile(filePath, plotNames[iter]);
     if (!histo[iter]) { cout << "Could not find histogram: " << plotNames[iter] << endl; found = false; }
     if(m_rebin>0) histo[iter]->Rebin(m_rebin);
  } 
  
  bool drawStats = drawMean;
  bool drawExtra = false;
  bool dataMCCompare = true;
  bool dataMCRatio = false;
  bool writeFile = true;
  TString newLabel = plotLabel;
  bool plotMore = false;
  bool lineOnly = false;
  bool nofill = false;
  
  std::vector<TString> tags;
  for (Int_t iter = 0; iter < NPlots; iter++) {
     tags.push_back(legend[iter]);
  } 
  
  TCanvas* canvas =
     Utils::PlotAll(histo,
                    NPlots,
                    tags,
                    xAxis,
                    yAxis,
                    (const char*)(TString(plotpath + name + plotext)),
                    (const char*)(TString(name + lumi)),
                    outfile,
                    XMin, XMax,
                    YMin, YMax,
                    drawNorm,
                    logx, logy,
                    drawStats,
                    drawExtra,
                    writeFile,
                    dataMCCompare,
                    dataMCRatio,
                    newLabel,
                    plotMore,
                    lineOnly,
                    nofill
        );

  
/*
  /// Plot the histograms
  //if (found) 
  Utils::PlotAllData(histo,
          NPlots,
          legend,
          xAxis,
          yAxis,
          (const char*)(TString(plotpath + name + plotext)),
          (const char*)(TString(name + lumi)),
          outfile,
          YMin, YMax,
          drawNorm,
          logx, logy,
          XMin, XMax,
          drawMean,opt,dataIndex);
*/
  outfile->Close();
  delete outfile;
  
}




///=========================================
/// Overlay using the Util.cpp
///=========================================
void JetMetbTagAnalysisBase::makeCombinedFilePlots(TString filePath[30],
                                                   TString plotNames, 
                                                   TString legend[30], 
                                                   Int_t NPlots, 
                                                   TString xAxis,
                                                   TString yAxis,
                                                   TString name,
                                                   Float_t YMin,  Float_t YMax,
                                                   bool drawNorm,
                                                   bool logx, bool logy,
                                                   Float_t XMin,  Float_t XMax,
                                                   bool drawStats,
                                                   bool drawExtra,
                                                   bool writeFile,
                                                   bool dataMCCompare,
                                                   bool dataMCRatio,
                                                   TString newLabel,
                                                   bool plotMore,
                                                   bool lineOnly)
//nTString opt,Int_t dataIndex)
{
   
   cout << "In makeCombinedFilePlots()" << endl;
   
   TFile *outfile = new TFile((const char*)(TString(plotpath + outRootFile)),"UPDATE");
   outfile->cd();
   
   /// Histograms
   TH1F *histo[30];
   for (Int_t iter = 0; iter < NPlots; iter++) {
      //histo[iter] = (TH1F*)gROOT->FindObject((const char*)(plotNames[iter]));
      histo[iter] = (TH1F*)FindObjectInFile(filePath[iter], plotNames);
      if (!histo[iter]) { cout << "Could not find histogram: " << plotNames << " in file " << filePath[iter]  << endl;}
      if(m_rebin>0) histo[iter]->Rebin(m_rebin);
   } 
   
   // Create a vector of strings for the legend
   
   std::vector<TString> tags;
   for (Int_t iter = 0; iter < NPlots; iter++) {
      tags.push_back(legend[iter]);
   } 
   
   
   // If drawn normalized and it is a data MC ratio, normalize against the last i.e. the one assumed to be data
   if(drawNorm && dataMCCompare) {
      double N = histo[NPlots-1]->Integral(-1,9999999);
      cout << "normalizing to " << N << " entries for histogram at " << histo[NPlots-1] << endl;
      for (Int_t iter = 0; iter < NPlots-1; iter++) {
         cout << "normalize scale factor for iter= " << iter << " is from n="<<histo[iter]->Integral(-1,9999999)<<" at "<<histo[iter] <<" c="<< (N/histo[iter]->Integral(-1,9999999)) << endl;         
         histo[iter]->Scale(N/histo[iter]->Integral(-1,9999999));
      }
      //Reset the flag to avoid another normalization later
      drawNorm=false;
   }
   
   /// Plot the histograms
   
   TCanvas* canvas =
      Utils::PlotAll(histo,
                     NPlots,
                     tags,
                     xAxis,
                     yAxis,
                     (const char*)(TString(plotpath + name + plotext)),
                     (const char*)(TString(name + lumi)),
//                 (const char*)(outDir + "overlay_" + plot1DList[i] + suffix.at(0) + plotType),
//                 (const char*)("overlay_" + plot1DList[i]),
                     outfile,
                     XMin, XMax,
                     YMin, YMax,
                     drawNorm,
                     logx, logy,
                     drawStats,
                     drawExtra,
                     writeFile,
                     dataMCCompare,
                     dataMCRatio,
                     newLabel,plotMore,lineOnly
         );

/*
  //if (found) 
  Utils::PlotAllData(histo,
              NPlots,
              legend,
              xAxis,
              yAxis,
              (const char*)(TString(plotpath + name + plotext)),
              (const char*)(TString(name + lumi)),
              outfile,
              YMin, YMax,
              drawNorm,
              logx, logy,
              XMin, XMax,
              drawExtra);
//,opt,dataIndex);
*/

  
  outfile->Close();
  delete outfile;
  
}


void JetMetbTagAnalysisBase::makeCombinedWeightPlots(TString filePath[30],
                                                   TString plotNames, 
                                                   TString legend[30], 
						   double histoWeights[30],
						   Int_t NPlots, 
                                                   TString xAxis,
                                                   TString yAxis,
                                                   TString name,
                                                   Float_t YMin,  Float_t YMax,
                                                   bool drawNorm,
                                                   bool logx, bool logy,
                                                   Float_t XMin,  Float_t XMax,
                                                   bool drawStats,
                                                   bool drawExtra,
                                                   bool writeFile,
                                                   bool dataMCCompare,
                                                   bool dataMCRatio,
                                                   TString newLabel,
                                                   bool plotMore,
                                                   bool lineOnly)
//nTString opt,Int_t dataIndex)
{
   
   cout << "In makeCombinedFilePlots()" << endl;
   
   TFile *outfile = new TFile((const char*)(TString(plotpath + outRootFile)),"UPDATE");
   outfile->cd();
   
   /// Histograms
   TH1F *histo[30];
   for (Int_t iter = 0; iter < NPlots; iter++) {
      histo[iter] = (TH1F*)FindObjectInFile(filePath[iter], plotNames);
      histo[iter]->Scale(histoWeights[iter]);
      if (!histo[iter]) { cout << "Could not find histogram: " << plotNames << " in file " << filePath[iter]  << endl;}
      if(m_rebin>0) histo[iter]->Rebin(m_rebin);
   } 
   
   // Create a vector of strings for the legend
   
   std::vector<TString> tags;
   for (Int_t iter = 0; iter < NPlots; iter++) {
      tags.push_back(legend[iter]);
   } 
   
   

   
   /// Plot the histograms
   
   TCanvas* canvas =
      Utils::PlotAll(histo,
                     NPlots,
                     tags,
                     xAxis,
                     yAxis,
                     (const char*)(TString(plotpath + name + plotext)),
                     (const char*)(TString(name + lumi)),
//                 (const char*)(outDir + "overlay_" + plot1DList[i] + suffix.at(0) + plotType),
//                 (const char*)("overlay_" + plot1DList[i]),
                     outfile,
                     XMin, XMax,
                     YMin, YMax,
                     drawNorm,
                     logx, logy,
                     drawStats,
                     drawExtra,
                     writeFile,
                     dataMCCompare,
                     dataMCRatio,
                     newLabel,plotMore,lineOnly
         );


  
  outfile->Close();
  delete outfile;
  
}


void JetMetbTagAnalysisBase::makeCombinedStackPlots(TString filePath[30],
                                                   TString plotNames, 
						    TString legend[30], 
						    double histoWeights[30],
						    Int_t NPlots, 
                                                   TString xAxis,
                                                   TString yAxis,
                                                   TString name,
                                                   Float_t YMin,  Float_t YMax,
                                                   bool drawNorm,
                                                   bool logx, bool logy,
                                                   Float_t XMin,  Float_t XMax,
                                                   bool drawStats,
                                                   bool drawExtra,
                                                   bool writeFile,
                                                   bool dataMCCompare,
                                                   bool dataMCRatio,
                                                   TString newLabel,
                                                   bool plotMore,
                                                   bool lineOnly)
//nTString opt,Int_t dataIndex)
{
   
   cout << "In makeCombinedFilePlots()" << endl;
   
   TFile *outfile = new TFile((const char*)(TString(plotpath + outRootFile)),"UPDATE");
   outfile->cd();
   
   //ASSUME DATA COMES IN LAST

   /// Histograms
   TH1F *histo[30];
   TH1F *dataHisto;
   for (Int_t iter = 0; iter < NPlots; iter++) {
      histo[iter] = (TH1F*)FindObjectInFile(filePath[iter], plotNames);
      histo[iter]->Scale(histoWeights[iter]);
      if (!histo[iter]) { cout << "Could not find histogram: " << plotNames << " in file " << filePath[iter]  << endl;}
      if(m_rebin>0) histo[iter]->Rebin(m_rebin);
   } 
   
   //   dataHisto =(TH1F*)FindObjectInFile(filePath[NPlots-1], plotNames);
 
  // Create a vector of strings for the legend
   
   std::vector<TString> tags;
   for (Int_t iter = 0; iter < NPlots; iter++) {
      tags.push_back(legend[iter]);
   } 
   
   

   
   /// Plot the histograms
   
   TCanvas* canvas =
      Utils::PlotStackPlus(histo,
                     NPlots,
			   //		   dataHisto,
                     tags,
                     xAxis,
                     yAxis,
                     (const char*)(TString(plotpath + name + plotext)),
                     (const char*)(TString(name + lumi)),
//                 (const char*)(outDir + "overlay_" + plot1DList[i] + suffix.at(0) + plotType),
//                 (const char*)("overlay_" + plot1DList[i]),
                     outfile,
		   YMin, YMax,
			   logx, logy,
			   XMin, XMax, newLabel
         );

/*
  //if (found) 
  Utils::PlotAllData(histo,
              NPlots,
              legend,
              xAxis,
              yAxis,
              (const char*)(TString(plotpath + name + plotext)),
              (const char*)(TString(name + lumi)),
              outfile,
              YMin, YMax,
              drawNorm,
              logx, logy,
              XMin, XMax,
              drawExtra);
//,opt,dataIndex);
*/

  
  outfile->Close();
  delete outfile;
  
}



std::vector<std::string> StringSplit(std::string str, std::string delim)
{
   std::vector<std::string> results;
   size_t cutAt;
   while( (cutAt = str.find_first_of(delim)) != str.npos )
   {
      if(cutAt > 0)
      {
         results.push_back(str.substr(0,cutAt));
      }
      str = str.substr(cutAt+1);
   }
   if(str.length() > 0)
   {
      results.push_back(str);
   }
   return results;
}

TString JetMetbTagAnalysisBase::StripFileName(TString str) {
   
   std::string name(str.Data());
   std::vector<std::string> v = StringSplit(name,"/");
   if(v.size()==0) return str;
   name = v[v.size()-1];
   v = StringSplit(name,".");
   if(v.size()==0) return str;
   TString s = v[0].c_str();
   return s;

}

///=========================================
/// Ratio plots
///=========================================
void JetMetbTagAnalysisBase::makeRatioPlotsPelle(TString filePath[30], 
                                                 TString plotName1, 
                                                 TString plotName2, 
                                                 TString legend[30], 
                                                 Int_t NPlots, 
                                                 TString xAxis,
                                                 TString yAxis,
                                                 TString name,
                                                 Float_t YMin,  Float_t YMax,
                                                 bool logx, bool logy,
                                                 Float_t XMin,  Float_t XMax,
                                                 bool drawMean)
{
   
   cout << "In makeRatioPlotsPelle()" << endl;
   
   TFile *outfile = new TFile((const char*)(TString(plotpath + outRootFile)),"UPDATE");
  outfile->cd();
  
  /// Histograms
  TH1F *histos_numer[30];
  TH1F *histos_denom[30];
  TH1F *h[30];
  bool found = true;
  for (Int_t iter = 0; iter < NPlots; iter++) {
     histos_numer[iter] = (TH1F*)FindObjectInFile(filePath[iter], plotName1);
     if (!histos_numer[iter]) { cout << "Could not find histogram: " << plotName1 << " in file " << filePath[iter]  << endl; found = false; }
     histos_denom[iter] = (TH1F*)FindObjectInFile(filePath[iter], plotName2);
     if (!histos_denom[iter]) { cout << "Could not find histogram: " << plotName1 << " in file " << filePath[iter]  << endl; found = false; }
  } 
  
  /// Plot the histograms separately
  if (found) {
     
     TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
     if (c1) {c1->Clear();} 
     else {
        Utils::style();
        c1 = (TCanvas*)gROOT->FindObject("c1");
     }
     c1->Clear();
     for (Int_t iter = 0; iter < NPlots; iter++) {
        if(m_rebin>0) {
           histos_numer[iter]->Rebin(m_rebin);
           histos_denom[iter]->Rebin(m_rebin);
        }
        histos_denom[iter]->SetLineColor(iter+1);
        histos_numer[iter]->SetLineColor(iter+1);
        histos_denom[iter]->SetMarkerColor(iter+1);
        histos_numer[iter]->SetMarkerColor(iter+1);
        histos_denom[iter]->SetMinimum(histos_numer[iter]->GetMinimum());
        histos_denom[iter]->Draw("hist,E");
        histos_numer[iter]->Draw("same");
        
        Utils::myText( 0.70,0.88,StripFileName(filePath[iter]).Data());
        
        //Contruct filename from filepath to distinguish them
        TString fname(name + "-ind-" + StripFileName(filePath[iter]));
        
        c1->SaveAs((const char*)(TString(plotpath + fname + plotext)));
        
        
//         Int_t nBins = histos_numer[iter]->GetNbinsX();
//         char integer[20];
//         sprintf(integer,"%d",iter);
           //new TH1F(TString(plotNames1[iter] + TString(integer)),"",nBins,histos_numer[iter]->GetBinLowEdge(1),histos_numer[iter]->GetBinLowEdge(nBins)+histos_numer[iter]->GetBinWidth(nBins));
        
        h[iter] = (TH1F*)histos_numer[iter]->Clone(TString::Format("%s_tagrate",histos_numer[iter]->GetName()));
        h[iter]->Reset();
        //h[iter]->Sumw2();
        h[iter]->Divide(histos_numer[iter],histos_denom[iter],1.,1.,"B");
        //h[iter]->Draw();
        cout << "Divided with result to Name: " << h[iter]->GetName() << endl;
     }
     

  double XMin = -1.;
  double XMax = -1.;
  bool drawStats = drawMean;
  bool drawExtra = false;
  bool dataMCCompare = false;
  bool dataMCRatio = false;
  bool writeFile = true;
  TString newLabel = "";
  bool lineOnly = false;

  std::vector<TString> tags;
  for (Int_t iter = 0; iter < NPlots; iter++) {
     tags.push_back(legend[iter]);
  } 

  TCanvas* canvas =
     Utils::PlotAll(h,
             NPlots,
             tags,
             xAxis,
             yAxis,
             (const char*)(TString(plotpath + name + plotext)),
             (const char*)(TString(name + lumi)),
//                 (const char*)(outDir + "overlay_" + plot1DList[i] + suffix.at(0) + plotType),
//                 (const char*)("overlay_" + plot1DList[i]),
             outfile,
             XMin, XMax,
             YMin, YMax,
             false,
             logx, logy,
             drawStats,
             drawExtra,
             writeFile,
             dataMCCompare,
             dataMCRatio,
                    newLabel,lineOnly
         );



/*

     Utils::PlotAllData(h,
                 NPlots,
                 legend,
                 xAxis,
                 yAxis,
                 (const char*)(TString(plotpath + name + plotext)),
                 (const char*)(TString(name + lumi)),
                 outfile,
                 YMin, YMax,
                 false,
                 logx, logy,
                 XMin, XMax,
                 drawMean);
*/
//       PlotDivided(histos_num[iter],
//                   histos_denom[iter],
//                   xAxis,
//                   yAxis,
//                   (const char*)(TString(plotpath + name + plotNames1[iter] + plotext)),
//                   (const char*)(TString(name + plotNames1[iter] + lumi)),
//                   outfile,
//                   YMin, YMax,
//                   logx, logy,
//                   XMin,XMax);
  }
   
 
  
  outfile->Close();
  delete outfile;
  
}



///=========================================
/// Ratio plots
///=========================================
void JetMetbTagAnalysisBase::makeRatioPlots(TString plotNames1[30], 
                                        TString plotNames2[30], 
                                        TString legend[30], 
                                        Int_t NPlots, 
                                        TString xAxis,
                                        TString yAxis,
                                        TString name,
                                        Float_t YMin,  Float_t YMax,
                                        bool logx, bool logy,
                                        Float_t XMin,  Float_t XMax,
                                        bool drawMean)
{

  cout << "In makeRatioPlots()" << endl;

  TFile *outfile = new TFile((const char*)(TString(plotpath + outRootFile)),"UPDATE");
  outfile->cd();
 
  /// Histograms
  TH1F *histos_numer[30];
  TH1F *histos_denom[30];
  TH1F *h[30];
  bool found = true;
  for (Int_t iter = 0; iter < NPlots; iter++) {
    histos_numer[iter] = (TH1F*)gROOT->FindObject((const char*)(plotNames1[iter]));
    if (!histos_numer[iter]) { cout << "Could not find histogram: " << plotNames1[iter] << endl; found = false; }
    
    histos_denom[iter] = (TH1F*)gROOT->FindObject((const char*)(plotNames2[iter]));
    if (!histos_denom[iter]) { cout << "Could not find histogram: " << plotNames2[iter] << endl; found = false; }
  } 
  
  /// Plot the histograms
  if (found) {
    for (Int_t iter = 0; iter < NPlots; iter++) {

      Int_t nBins = histos_numer[iter]->GetNbinsX();
  
      char integer[20];
      sprintf(integer,"%d",iter);
  
      h[iter] = new TH1F(TString(plotNames1[iter] + TString(integer)),"",nBins,histos_numer[iter]->GetBinLowEdge(1),histos_numer[iter]->GetBinLowEdge(nBins)+histos_numer[iter]->GetBinWidth(nBins));
      h[iter]->Sumw2();
      h[iter]->Divide(histos_numer[iter],histos_denom[iter],1.,1.,"B");
      h[iter]->Draw();
      cout << "Name: " << h[iter]->GetName() << endl;
    }

    
    double XMin = -1.;
    double XMax = -1.;
    bool drawStats = drawMean;
    bool drawExtra = false;
    bool dataMCCompare = false;
    bool dataMCRatio = false;
    bool writeFile = true;
    TString newLabel = "";
    bool lineOnly = false;
    
    std::vector<TString> tags;
    for (Int_t iter = 0; iter < NPlots; iter++) {
       tags.push_back(legend[iter]);
    } 
    
    TCanvas* canvas =
       Utils::PlotAll(h,
               NPlots,
               tags,
               xAxis,
               yAxis,
               (const char*)(TString(plotpath + name + plotext)),
               (const char*)(TString(name + lumi)),
//                 (const char*)(outDir + "overlay_" + plot1DList[i] + suffix.at(0) + plotType),
//                 (const char*)("overlay_" + plot1DList[i]),
               outfile,
               XMin, XMax,
               YMin, YMax,
               false,
               logx, logy,
               drawStats,
               drawExtra,
               writeFile,
               dataMCCompare,
               dataMCRatio,
                      newLabel,
                      lineOnly
          );
  /*

    Utils::PlotAll(h,
            NPlots,
            legend,
            xAxis,
            yAxis,
            (const char*)(TString(plotpath + name + plotext)),
            (const char*)(TString(name + lumi)),
            outfile,
            YMin, YMax,
            false,
            logx, logy,
            XMin, XMax,
            drawMean);
  
  */
//       PlotDivided(histos_num[iter],
//                   histos_denom[iter],
//                   xAxis,
//                   yAxis,
//                   (const char*)(TString(plotpath + name + plotNames1[iter] + plotext)),
//                   (const char*)(TString(name + plotNames1[iter] + lumi)),
//                   outfile,
//                   YMin, YMax,
//                   logx, logy,
//                   XMin,XMax);
   
  }
  
  outfile->Close();
  delete outfile;
  
  }


TGraph* JetMetbTagAnalysisBase::TaggerPerformance(TString lightJetTagsFile,
                                                  TString bJetTagsFile,
                                                  TString lightJetTags,
                                                  TString bJetTags,
                                                  Float_t xMin,Float_t xMax)
{
   Float_t cut = -1;
   Float_t rej=-1.; 
   Float_t eff=-1;
   
   TGraph* gr =  TaggerPerformance(lightJetTagsFile,
                                   bJetTagsFile,
                                   lightJetTags,
                                   bJetTags,
                                   xMin,xMax,
                                   rej,eff,cut);
   cout << "Not using the cut " << cut << ", rej="<<rej<<" and eff="<<eff<<endl;
   return gr;
   
}

///=========================================
/// TaggerPerformance
///=========================================
TGraph* JetMetbTagAnalysisBase::TaggerPerformance(TString lightJetTagsFile,
                                                  TString bJetTagsFile,
                                                  TString lightJetTags,
                                                  TString bJetTags,
                                                  Float_t xMin,Float_t xMax,
                                                  Float_t rejPoint, Float_t effPoint, Float_t& cut)
{
   
   cout << endl << "Using light jet tag file: " << lightJetTagsFile << endl;
   cout << endl << "Using b-jet tag file:     " << bJetTagsFile << endl;
   cout << endl << "[xMin,xMax]:  [" << xMin << "," << xMax << "]" << endl;
   bool findOpCut = false;
   if(rejPoint>=0. || effPoint >=0.) { 
      cout << endl << "Returning cut where rejection is:  "  << rejPoint << endl;
      cout << endl << "Returning cut where efficiency is: "  << effPoint << endl; 
      findOpCut= true;
   }
   
   if(rejPoint>=0. && effPoint >=0.) {cout << "ERROR! Cannot return cut for both rej and eff!" << endl; exit(-1);}
   

   TH1F* h1 = (TH1F*)FindObjectInFile(lightJetTagsFile,lightJetTags);
   if (!h1) { cout << "Could not find light quark jet tag distribution: " << lightJetTags << " . Quiting" << endl; return 0; }
   TH1F *hl = (TH1F*)h1->Clone("hl");
   
   TH1F* h2 = (TH1F*)FindObjectInFile(bJetTagsFile,bJetTags);
   if (!h2) { cout << "Could not find b-jet tag distribution: " << bJetTags << " . Quiting" << endl; return 0; }
   TH1F *hb = (TH1F*)h2->Clone("hb");
   
   int N = hl->GetNbinsX();
   if( N != hb->GetNbinsX() ) {
      cout << "Error in TaggerPerformance: histograms do not have same nr of bins!"
           << endl; exit(-1);
   }
   
   int N0 = hl->FindBin(xMin);
   int N1 = hl->FindBin(xMax);
   
   float Nl = hl->Integral(N0,N1);
   float Nb = hb->Integral(N0,N1);
      
   cout << "Nb = " << Nb << ", Nl = " << Nl << endl;
   
   TGraph* G = new TGraph;
   G->SetName("G"); G->SetFillColor(0);
   G->SetMarkerColor(kBlue); G->SetMarkerStyle(20); G->SetMarkerSize(1.3);
   
 char title[100],line[100];
 sprintf(title,"%10s | %10s | %10s | %10s | %10s ","Bin #","Bin index","Bin value","Eff","Rej");
 cout << endl << title << endl;
 cout << "----------------------------------------------------------------" << endl;

 float best = 999999999.;
 int n = 0;
 for(int i=N0; i<N1; i++) {
    float denom = (hl->Integral(i,N1)/Nl);
    float rej = denom > 0  ?  1./denom : 1./0.00000001;
    float eff = hb->Integral(i,N1)/Nb;
    float w   = hb->GetBinLowEdge(i);
    //if(eff<0.10) continue;
    sprintf(line,"%10d | %10d | %10f | %10f | %10f ",n,i,w,eff,rej);
    cout << line << endl;
    G->SetPoint(n, eff,rej);
    n++;
    
    //find the requested cut value
    if( findOpCut ) {
       if(effPoint>=0.) {
          if( fabs( eff-effPoint) < fabs( best-effPoint) ) { best=eff; cut = w;   }
       } else {
          if( fabs( rej-rejPoint) < fabs( best-rejPoint) ) { best=rej; cut = w;  }    
       }
    }
 }


 //gROOT->SetStyle("ATLAS");
 //gROOT->ForceUtils::style();


 TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
 if (c1) {c1->Clear();} 
 else {
   c1 = new TCanvas("c1","",650,600);
   c1->SetFillColor(0);
 } 
 gStyle->SetOptStat(0);
 gStyle->SetOptFit(0);
 c1->SetGrid();

 c1->SetLogy();

 TH2F* frame = new TH2F("frame","",2,0.0,1.0, 2,1.0,125.0);
 frame->SetXTitle("b-jet efficiency");
 frame->SetYTitle("light jet rejection");
 frame->GetXaxis()->SetTitleColor(1);
 frame->GetYaxis()->SetTitleOffset(1.2);
 frame->GetXaxis()->SetTitleOffset(1.13);
 frame->Draw();
 G->Draw("P");

 Utils::ATLAS_LABEL(0.20,0.80);
 //Utils::myText( 0.70,0.88,1,"Preliminary");

 return G;

}



///=========================================
/// Scale Factor for rates
///=========================================
void JetMetbTagAnalysisBase::GetScaleFactorFromRatio(float scale[2], 
                                                     TString numFile,
                                                     TString denFile,
                                                     TString numHist,
                                                     TString denHist) 
{
   
   cout << "Getting scalefactor from:\n" 
        << "numFile: " << numFile << "   numHist: " << numHist << "\n"
        << "denFile: " << denFile << "   denHist: " << denHist << endl;
   
   //Takes two histogram and calculates the ratio
   //This is used for example to get a scale factor for the 
   //rate/efficiency
   TH1F* hnum = (TH1F*)FindObjectInFile(numFile,numHist);
   TH1F* hden = (TH1F*)FindObjectInFile(denFile,denHist);
   
   if(!hnum || !hden) {
      cout << "Error: histograms not found in scale factor calculation"
           << " hnum="<<hnum<<" hden="<<hden<<endl;
      exit(-1);//return -1.;
   }
   
   if(hden->Integral(-1,99999999)<=0) {
      cout << "ERROR: denominator input with name "<< hden->GetName() <<" to rate has no entries in scale factor calculation" <<endl;
      exit(-1);//return -1.;
   }
   
   double num = hnum->Integral(-1,99999999);
   double den = hden->Integral(-1,99999999);
   scale[0] = num/den;
   scale[1] = Utils::CalcEffErr(hden->GetEntries(), hnum->GetEntries());
   cout << "Scale factor = "<< scale[0] << "+-" << scale[1] << " (Num="<<num << "/Entries="<<hnum->GetEntries()<<"   den=" << den << "/Entries="<<hnum->GetEntries()<<")" << endl;   
   cout << "Done." << endl;
   return;
   
}




///=========================================
/// RatePerformance
///=========================================
TGraphErrors* JetMetbTagAnalysisBase::RatePerformance(TString rateFile,
                                                      TString signalFile,
                                                      TString rateHisto,
                                                      TString signalHisto,
                                                      bool plotRates,
                                                      Float_t conv,
                                                      Float_t scaleSignal[2],
                                                      Float_t scaleRate[2],
                                                      Float_t xMin,
                                                      Float_t xMax,
                                                      bool useCut, Float_t cut)
{
   
   gStyle->SetPadGridX(kFALSE);
   gStyle->SetPadGridY(kFALSE);
   
   cout << endl << "Using rate file:         " << rateFile << endl;
   cout << endl << "Using signal file:       " << signalFile << endl;
   cout << endl << "Using rate histogram:    " << rateHisto << endl;
   cout << endl << "Using signal histogram:  " << signalHisto << endl;
   if(useCut) cout <<"Using cut at " << cut << endl;
   else cout <<"No cut used" <<endl;
   cout << endl << "Histogram xMin="<< xMin << ", xMax="<<xMax << endl;
   cout << endl << "scaleSignal = "<< scaleSignal[0] << "+-" << scaleSignal[1] << endl;
   cout << endl << "scaleRate = "<< scaleRate[0] << "+-" << scaleRate[1] << endl;
   
   TH1F* h1 = (TH1F*)FindObjectInFile(rateFile,rateHisto);
   if (!h1) { cout << "Could not find light quark jet tag distribution: " 
                   << rateHisto << " . Quiting" << endl; return 0; }
   TH1F *hl = (TH1F*)h1->Clone(TString::Format("hl_%s_%s",rateFile.Data(),rateHisto.Data()));
   
   TH1F* h2 = (TH1F*)FindObjectInFile(signalFile,signalHisto);
   if (!h2) { cout << "Could not find b-jet tag distribution: " 
                   << signalHisto << " . Quiting" << endl; return 0; }
   TH1F *hb = (TH1F*)h2->Clone(TString::Format("hb_%s_%s",signalFile.Data(),signalHisto.Data()));
   
   //int N = hl->GetNbinsX();
   
   int N0 = hl->FindBin(xMin);
   int N1 = hl->FindBin(xMax);

   int N_c = -1;
   if(useCut) 
      N_c = hl->FindBin(cut);
   
   cout << "N_firstbin = " << N0 << ", N_lastbin = " << N1 << endl;
   if(useCut) cout << " N_cutbin = "<< N_c <<  endl;
   
   //NOTE take into account OUflow in the denominator!!
   float Nl = hl->Integral(-1,99999999);
   float Nl_entries = hl->GetEntries();
   float Nb = hb->Integral(-1,99999999);
   float Nb_entries = hb->GetEntries();
   
   cout << endl
        << "Signal      : " << signalHisto << " (N events = " << Nb << " <--> entries = "<< Nb_entries << ")" << endl
        << "Background  : " << rateHisto << " (N events = " << Nl << " <--> entries = "<< Nl_entries << ")" << endl;


   TGraphErrors* G = new TGraphErrors;
   G->SetName("G"); G->SetFillColor(0);
   G->SetMarkerColor(1); G->SetMarkerStyle(21); G->SetMarkerSize(1.4);

   if(useCut) {
      float events = hl->Integral(N_c,N1);            
      float events_entries = events/Nl*Nl_entries;
      float events_signal = hb->Integral(N_c,N1);
      float events_signal_entries = events_signal/Nb*Nb_entries;      
      float eff = events_signal/Nb * scaleSignal[0];
      float ratio_error = Utils::CalcEffErr(Nb_entries,events_signal_entries);
      float eff_error = sqrt( (scaleSignal[0]*ratio_error)*(scaleSignal[0]*ratio_error) + (scaleSignal[1]*events_signal/Nb)*(scaleSignal[1]*events_signal/Nb) );
      float denom = events/Nl;
      float rej  = 0.0;
      float rate = -1.0;
      float denom_error = 0.0;
      float rate_error = 0.0;
      if(denom>0) {
         rej  = 1./denom;
         //Error calculation:
         //To get the correct binomial errors we need to use actual entries
         //Scale the entries above the cut
         denom_error = Utils::CalcEffErr(Nl_entries,events_entries);
         rate = conv / rej * scaleRate[0]; 
         rate_error = sqrt( (conv * scaleRate[0] * denom_error)*(conv * scaleRate[0] * denom_error) + (conv * denom * scaleRate[1])*(conv * denom * scaleRate[1]) ); 
      }
      
      cout << "Signal above cut = " <<  events_signal << " (entries: " << events_signal_entries << ") -> eff = " << eff << " +- " << eff_error << endl;
      cout << "Bkg above cut    = " << events << " (entries: " << events_entries << ")" << endl;
      cout << "denom="<<denom<<", rej="<<rej<<", rate="<<rate<<"+-"<<rate_error<<endl;
      G->SetPoint(0,rate,eff);
      G->SetPointError(0,(TurnOffErrors()?0.:rate_error),(TurnOffErrors()?0.:eff_error));
      return G;
   }
   
   
   int n = 0;
   char title[100],line[100];
   sprintf(title,"%10s | %10s | %10s | %10s | %10s | %10s | %10s | %10s | %10s | %10s | %10s | %10s | %10s ","Bin #","Bin index","Bin value","Eff","err Eff","Rej","Rate(Hz)","err Rate(Hz)","N BG evts","k(Rate)","err k(Rate)","k(Signal)","err k(Signal)");
   cout << endl << title << endl;
   cout << "--------------------------------------------------------------------------------------------------------" << endl;
   for(int i=N0; i<N1; i++) {
      float events = hl->Integral(i,N1);
      float events_entries = events/Nl*Nl_entries;
      float denom = events/Nl;
      float rej = 0.0;
      float rate = -1.0;
      float events_signal = hb->Integral(i,N1);
      float events_signal_entries = events_signal/Nb*Nb_entries;      
      float denom_error = 0.0;
      float rate_error = 0.0;
      if (denom > 0) { 
         rej = 1./denom;
         denom_error = Utils::CalcEffErr(Nl_entries,events_entries);
         rate = conv / rej * scaleRate[0]; 
         rate_error = sqrt( (conv * scaleRate[0] * denom_error)*(conv * scaleRate[0] * denom_error) + (conv * denom * scaleRate[1])*(conv * denom * scaleRate[1]) ); 
      }
      float eff = events_signal/Nb * scaleSignal[0];
      float ratio_error = Utils::CalcEffErr(Nb_entries,events_signal_entries);
      float eff_error = sqrt( (scaleSignal[0]*ratio_error)*(scaleSignal[0]*ratio_error) + (scaleSignal[1]*events_signal/Nb)*(scaleSignal[1]*events_signal/Nb) );
      float w   = hb->GetBinLowEdge(i);
      //if(eff<0.10) continue;
      sprintf(line,"%10d | %10d | %10f | %10f | %10f | %10f | %10f | %10f | %10f | %10f | %10f | %10f | %10f ",n,i,w,eff,eff_error,rej,rate,rate_error,events,scaleRate[0],scaleRate[1],scaleSignal[0],scaleSignal[1]);
      cout << line << endl;
      if (!plotRates) {
         G->SetPoint(n, eff,rej); G->SetPointError(n, 0.,(TurnOffErrors()?0.:0.)); 
      }
      else {
         G->SetPoint(n, rate, eff);  G->SetPointError(n, (TurnOffErrors()?0.:rate_error),(TurnOffErrors()?0.:eff_error)); 
      }
      n++;
   }
   
   
   //gROOT->SetStyle("ATLAS");
   //gROOT->ForceUtils::style();
   
   
   TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
   if (c1) {c1->Clear();} 
   else {
      c1 = new TCanvas("c1","",650,600);
      c1->SetFillColor(0);
   } 
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(0);
   c1->SetGrid(kFALSE);
   
   c1->SetLogy();
   
   TH2F* frame; 
   if (!plotRates) {
      frame = new TH2F("frame","",2,0.0,1.0, 2,1.0,125.0);
      frame->SetXTitle("Efficiency");
      frame->SetYTitle("Rejection");
   }
   else {
      c1->SetLogy(kFALSE);
      frame = new TH2F("frame","",2,0.0,5.0,2,0.0,1.0);
      frame->SetYTitle("Efficiency");
      frame->SetXTitle("Rate (Hz)");
   }   
   frame->GetXaxis()->SetTitleColor(1);
   frame->GetYaxis()->SetTitleOffset(1.2);
   frame->GetXaxis()->SetTitleOffset(1.13);
   frame->Draw();
   G->Draw("P");
   
   Utils::ATLAS_LABEL(0.75,0.85);
   //Utils::myText( 0.70,0.88,1,"Preliminary");
   
//    TString name = (const char*)(TString(plotpath + saveName + plotext));
//    c1->SaveAs(name.Data());

   return G;
   
}




double f_ip(Double_t *x, Double_t *par) {

 
   //  double m_par_L2Si0[4] = {6.63551e+02,9.76080e-01,1.63175e+01,5.89648};
   //  double m_par_L2Si1[4] = {1.56781e+03,9.74479e-01,1.71767e+01,3.44048};
   
   double* p = 0;
   p = &par[0];
   
   double y1  = p[2]*p[3]*erfc(fabs(x[0])/(sqrt(2)*p[3]));
   double y2  = p[0]*p[1]*erfc(fabs(x[0])/(sqrt(2)*p[1]));
   double y01 = p[2]*p[3];
   double y02 = p[0]*p[1];
   double res=(y1+y2)/(y01+y02);
   
   return res;
}

double f_ip_normopt(Double_t *x, Double_t *par) {

 
   //  double m_par_L2Si0[4] = {6.63551e+02,9.76080e-01,1.63175e+01,5.89648};
   //  double m_par_L2Si1[4] = {1.56781e+03,9.74479e-01,1.71767e+01,3.44048};
   
   double* p = 0;
   p = &par[0];
   
   double y1  = p[2]*erfc(fabs(x[0])/(sqrt(2)*p[3]));
   double y2  = p[0]*erfc(fabs(x[0])/(sqrt(2)*p[1]));
   double y01 = p[2];
   double y02 = p[0];
   double res=(y1+y2)/(y01+y02);
   
   return res;
}



TF1* JetMetbTagAnalysisBase::Get_f_ip_direct(TF1* ftwogausfit,TString name,double xmin,double xmax) {
   
   double m_par_L2Si0[4] = {ftwogausfit->GetParameter(1),ftwogausfit->GetParameter(3),ftwogausfit->GetParameter(4),ftwogausfit->GetParameter(6)};
   //double m_par_L2Si0[4] = {6.63551e+02,9.76080e-01,1.63175e+01,5.89648};
   //double m_par_L2Si1[4] = {1.56781e+03,9.74479e-01,1.71767e+01,3.44048};
   
   TF1* f = new TF1(name.Data(),f_ip,xmin,xmax,4);
   f->SetParameter(0,m_par_L2Si0[0]);
   f->SetParameter(1,m_par_L2Si0[1]);
   f->SetParameter(2,m_par_L2Si0[2]);
   f->SetParameter(3,m_par_L2Si0[3]);
   return f;
}


TF1* JetMetbTagAnalysisBase::Get_f_ip(TH1F* histo,TString name,double xmin,double xmax) {
   
   //Use online parameters as starting parameters
   double m_par_L2Si0[4] = {6.63551e+02,9.76080e-01,1.63175e+01,5.89648};
   //double m_par_L2Si1[4] = {1.56781e+03,9.74479e-01,1.71767e+01,3.44048};

   TF1* f = new TF1(name.Data(),f_ip,xmin,xmax,4);
   f->SetParameter(0,m_par_L2Si0[0]);
   f->SetParameter(1,m_par_L2Si0[1]);
   f->SetParameter(2,m_par_L2Si0[2]);
   f->SetParameter(3,m_par_L2Si0[3]);
   
   histo->Fit(f,"0R");
   return f;
}

TF1* JetMetbTagAnalysisBase::Get_f_ip_twogaus(TH1F* histo,TString name,double xmin,double xmax,
                                              double p0,double p1,double p2,double p3,double p4,double p5,double p6, bool fixmean) {
   //TF1* f = new TF1(name.Data(),f_ip,xmin,xmax,4);
   TF1 *f = new TF1(name.Data(), "[0] + gaus(1) + gaus(4)", xmin, xmax);
   f->SetParameters(p0,p1,p2,p3,p4,p5,p6);
   if(fixmean) {
      f->FixParameter(0,p0);
      f->FixParameter(2,p2);
      f->FixParameter(5,p5);
   }
   
//   f->SetParameters(1000., 100000., -2., 10., 200000, 0.,2.);
   //f->SetParameters(-2.0e9, 2.3e9,3.0e-1, 2., 5.0e9, 2.0e3, 1.0e3);
//    1  p0          -2.17559e+09   1.10644e+08   3.68094e+04  -5.92759e-10
//    2  p1           2.33155e+09   1.18510e+08  -3.92607e+04  -1.25019e-11
//    3  p2           3.75615e-01   1.17261e-01  -1.42003e-05  -1.72056e-03
//    4  p3           1.27567e+00   4.31322e-02  -3.66739e-06   2.87176e-05
//    5  p4           5.29246e+09   2.73485e+08  -8.20846e+04  -2.38105e-10
//    6  p5           1.88452e+03   2.13384e+02   1.93011e-02   1.13512e-03
//    7  p6           1.42081e+03   1.56786e+02   1.33372e-02  -1.51119e-03

   histo->Fit(f,"0R");
   return f;
}



TH1D* JetMetbTagAnalysisBase::Get_cumulative_twogaus(TF1* f,TString name) { //,double xmin,double xmax) {
   //Integrate the normalized functions
   TH1D* hnorm = (TH1D*) f->GetHistogram()->Clone(TString(f->GetName())+"_cumutmp");
   hnorm->Scale(1./hnorm->Integral());
   
   TH1D* hcumul = (TH1D*)hnorm->Clone((TString(f->GetName())+"_normcumul"));
   hcumul->Reset();
   for(int i=1;i!=hnorm->GetNbinsX()+1;++i) {
      hcumul->SetBinContent(i,hnorm->Integral(1,i));
      hcumul->SetBinError(i,hnorm->Integral(1,i)/10.0);
   }
   
   return hcumul;
}



