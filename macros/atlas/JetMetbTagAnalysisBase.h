//*****************************************************
// Class   : JetMetbTagAnalysisBase
// 
// Purpose : Common calculation and plot tools
//                      
// Author  : D.W. Miller, P. Hansson
//
// Date    : 24-July-2008 : Creation of class
//*****************************************************
#ifndef JetMetbTagAnalysisBase_h
#define JetMetbTagAnalysisBase_h

//#include "SlimJetMetbTriggerTree.h"
//#include "SlimSlimJetMetbTagTriggerTree.h"
#include "TF1.h"
#include "TH1D.h"
#include "TTree.h"
#include "TGraphErrors.h"
#include "TLorentzVector.h"


class JetMetbTagAnalysisBase 
//class JetMetbTagAnalysisBase : public SlimJetMetbTriggerTree
//class JetMetbTagAnalysisBase : public SlimSlimJetMetbTriggerTree
{

public:

  /// default constructor
      JetMetbTagAnalysisBase(TTree *tree=0, bool isDebug = false);

  /// destructor
  virtual ~JetMetbTagAnalysisBase();
  
  ///---------------------
  /// Set options
  ///---------------------
  void SetPlotPathAndExt(std::string runType, std::string lumiFlag);   
  void SetPlotTypeAndLumi(TString plotType = ".pdf", TString lumiString = "verylow");
  void SetOutputDirectory(TString outDir = "/Users/fizisist/Work/ATLAS/TopMet/Plots/");
  void SetOutputRootFile(TString outFile = "OffsetAnalysisPlots.root");
  void SetTurnOffErrors(bool turnoff=true) { 
     std::cout << "Turning off errrors!" << std::endl;
     m_turnofferrors=turnoff;
  }
  bool TurnOffErrors() { return m_turnofferrors;}
      
  TH1* FindObjectInFile(TString filepath,TString plotNames);
      


  void SetEventCounter(Long64_t counter = 10000);
  void SetMaxEvents(Long64_t maxEvents = -1);
  TString StripFileName(TString str);


  void SetRebin(Int_t rebin) { m_rebin = rebin; }

 
  void makeCombinedPlots(TString filePath,
                         TString plotNames[30], 
                         TString titles[30], 
                         Int_t NPlots = 30, 
                         TString xAxis = "",
                         TString yAxis = "",
                         TString name  = "",
                         Float_t YMin = -1,  Float_t YMax = -1,
                         bool drawNorm = kFALSE,
                         bool logx = kFALSE, bool logy = kFALSE,
                         Float_t XMin = -1,  Float_t XMax = -1,
                         bool drawMean = false, TString opt = "",Int_t dataIndex=-1,
                         TString newLabel="");       
 

void makeCombinedFilePlots(TString filePath[30],
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
                           TString newLabel,bool plotMore,bool lineOnly);


 void makeCombinedWeightPlots(TString filePath[30],
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
			    TString newLabel,bool plotMore,bool lineOnly);


 void makeCombinedStackPlots(TString filePath[30],
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
			      TString newLabel,bool plotMore,bool lineOnly);



 // void makeCombinedFilePlots(TString filePath[30],
//                          TString plotNames, 
//                          TString titles[30], 
//                          Int_t NPlots = 30, 
//                          TString xAxis = "",
//                          TString yAxis = "",
//                          TString name  = "",
//                          Float_t YMin = -1,  Float_t YMax = -1,
//                          bool drawNorm = kFALSE,
//                          bool logx = kFALSE, bool logy = kFALSE,
//                          Float_t XMin = -1,  Float_t XMax = -1,
//                             bool drawMean = false, TString opt = "",Int_t dataIndex=-1);       
  void makeRatioPlotsPelle(TString filePath[30], 
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
                                                 bool drawMean);
  void makeRatioPlots(TString plotNames1[30], 
                      TString plotNames2[30], 
                      TString legend[30], 
                      Int_t NPlots, 
                      TString xAxis = "",
                      TString yAxis = "",
                      TString name  = "",
                      Float_t YMin = -1,  Float_t YMax = -1,
                      bool logx = kFALSE, bool logy = kFALSE,
                      Float_t XMin = -1,  Float_t XMax = -1,
                      bool drawMean = false);
  
      TGraph* TaggerPerformance(TString lightJetTagsFile,TString bJetTagsFile,TString lightJetTags,TString bJetTags, Float_t xMin, Float_t xMax);
      TGraph* TaggerPerformance(TString lightJetTagsFile,TString bJetTagsFile,TString lightJetTags,TString bJetTags, Float_t xMin, Float_t xMax,Float_t rejPoint, Float_t effpoint, Float_t& cut);
      TGraphErrors* RatePerformance(TString rateFile, TString signalFile,TString rateHisto,TString signalHisto, bool plotRates, Float_t conv, Float_t scaleSignal[2], Float_t scaleRate[2], Float_t xMin = 0., Float_t xMax= 100., bool useCut=false, Float_t cut=-1. );
      void GetScaleFactorFromRatio(float[2],
                                   TString numFile,
                                   TString denFile,
                                   TString numHist,
                                   TString denHist); 
      TF1* Get_f_ip_direct(TF1* ftwogausfit,TString name,double xmin,double xmax);
      TF1* Get_f_ip(TH1F* histo,TString name,double xmin,double xmax);
      //TF1* Get_f_ip_twogaus(TH1F* histo,TString name,double xmin,double xmax);
      //TF1* Get_f_ip_twogaus(TH1F* histo,TString name,double xmin,double xmax, double p0=1000.,double p1=100000.,double p2= -2.,double p3= 10.,double p4= 200000,double p5= 0.,double p6=2.);
      TF1* Get_f_ip_twogaus(TH1F* histo,TString name,double xmin,double xmax,
                            double p0,double p1,double p2,double p3,double p4,double p5,double p6, bool fixmean=false);

      TH1D* Get_cumulative_twogaus(TF1* f,TString name); //,double xmin,double xmax) {

      
  
public:

  
private:

  std::string  fRunType;
  TString      plotpath;
  TString      outRootFile;
  TString      plotext;
  TString      lumi;
  bool         m_fDebug;  
  Long64_t     m_eventCounter;
  Long64_t     m_maxEvents;
  Int_t        m_rebin;
  bool         m_turnofferrors;
  
  
};

#endif /* JetMetbTagAnalysisBase */


