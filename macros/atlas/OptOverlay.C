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
#include "TFitResult.h"

#include "Util.cpp"

using namespace Utils;

void OptOverlay(Int_t NOverlay,
                        TString outFileName,
                        vector<TString> fileNames, 
                        vector<TString> prefix, 
                        vector<TString> suffix, 
                        vector<TString> tags,
                        vector<TString> outstrings,
                        vector<TString> plotDir, 
                        vector<double> weights,
                        vector<bool> signal,
                        TString outDir = "./", 
                        TString psFile = "TowerDPD_JetRec_JetValidation",
                        TString plotType = ".png",
                        bool dataMCCompare = true,
                        bool dataMCRatio = true,
                        TString newLabel = "",
                        bool writeFile = true,
                        bool doLogY = false,
                        bool doLogZ = false)
{ 
  cout << "----------------------------------------------" << endl;
  cout << "Starting plot overlay for jets" << endl;
  cout << "   N overlay = " << NOverlay << endl;
  cout << "----------------------------------------------" << endl;
  
  ///-----------------------
  /// Output
  ///-----------------------
  TFile *outfile = new TFile(TString(outDir + outFileName),"RECREATE");
  
  ///-----------------------
  /// Input
  ///-----------------------
  vector<TFile*> files;   
  for (Int_t fileItr=0; fileItr < NOverlay; fileItr++) {
    cout << "Adding file: " << fileNames.at(fileItr) << endl;
    TFile *f = new TFile(fileNames.at(fileItr),"READ");
    if (f->IsOpen()) files.push_back(f);
    else cout << "Problem opening file: " << fileNames.at(fileItr) << endl;
  }
  cout << "Done Adding files. Size = " << files.size() << endl;
  cout << "Validity check: #1" << (files.at(0))->GetName() << endl;
 
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
  canvas->Print(TString(psFile + ".ps["));
 
  ///-----------------------
  /// Plot list
  ///-----------------------
  //Int_t n1DPlots = 14;
  bool special = false;

  int binz = 100;
 

  //TString myLabel = "2j(150,40),met60,btag,J55";
  TString myLabel = "3j60,met60,btag,3J10";
  Int_t n1DPlots = 1;
  TString plot1DList[40] = {
  			    	
    //"jetmetbtag_single_0l2j15040tagL1J55met60_j2pt",
     "jetmetbtag_multi_0l3j60tagsL13J10met60_j2pt",  

                           };
                           
  Int_t nBtagPlots = 1;
  TString plotBtagSignificanceList[40] = {

    //"jetmetbtag_single_0l2j15040tagL1J55met60_j2pt",
    "jetmetbtag_multi_0l3j60tagsL13J10met60_j2pt", 
                           };                           
                       
  
  ///-----------------------                      
  /// 1D Plots   
  ///-----------------------
  cout << "Plotting 1D plots" << endl;
  for (Int_t i=0; i<n1DPlots; i++) {
    TH1F* plots[50];
    double max = 0.0;
    double min = 0.0;
    for (Int_t fileItr=(NOverlay-1); fileItr > -1; fileItr--) {
      cout << "Reading fileItr = " << fileItr << endl;
      TH1F *h = (TH1F*)((files.at(fileItr))->Get(TString(plotDir.at(fileItr) + prefix.at(fileItr) + plot1DList[i] + suffix.at(fileItr))));
      if (h) cout << "Got histogram: " << TString(plotDir.at(fileItr) + prefix.at(fileItr) + plot1DList[i] + suffix.at(fileItr)) << endl;
      else cout << "Did not get histogram: " << TString(plotDir.at(fileItr) + prefix.at(fileItr) + plot1DList[i] + suffix.at(fileItr)) << endl;
      h->SetName(TString(plot1DList[i] + Form("_%d",fileItr)));
      float tempmax = 1.3*h->GetBinContent(h->GetMaximumBin());
      
      if (tempmax>max) max = tempmax;
    
      plots[fileItr] = h;
    }
  
    bool drawNorm = kTRUE; //kFALSE;
    bool logx = kFALSE;
    bool logy = kFALSE;//doLogY;
    bool doFit = kFALSE;
    bool drawStats = kFALSE;
    bool drawExtra = kTRUE;
    
    if (plot1DList[i].Contains("sv0") ) 
      logy = true;
    else 
      logy = false;
    
    
    canvas =
        PlotAll(plots,
                NOverlay,
                tags,
                "",
                "",
                (const char*)(outDir + "overlay_" + plot1DList[i] + suffix.at(0) + plotType),
                (const char*)("overlay_" + plot1DList[i]),
                outfile,
                0.0, 0.0,
                min, max,
                drawNorm,
                logx, logy,
                drawStats,
                drawExtra,
                writeFile,
                dataMCCompare,
                dataMCRatio,
                myLabel,
                false,
                true  //line-only
               );
               
    PlotAll(plots,
	    NOverlay,
	    tags,
	    "",
	    "",
	    (const char*)(outDir + "overlay_logy" + plot1DList[i] + suffix.at(0) + plotType),
	    (const char*)("overlay_logy" + plot1DList[i]),
	    outfile,
	    0.0, 0.0,
	    min, max,
	    drawNorm,
	    logx, true,
	    drawStats,
	    drawExtra,
	    writeFile,
	    dataMCCompare,
	    dataMCRatio,
	    myLabel,
	    false,
	    true  //line-only
	    );


    //    canvas->Print(TString(outDir + "overlay_" + plot1DList[i] + suffix.at(0) + ".C"));
    
  	///-----------------------
  	/// Output
  	///-----------------------
  	TFile *outfile2 = new TFile(TString(outDir + "overlay_" + plot1DList[i] + suffix.at(0) + ".root"),"RECREATE");
  	outfile2->cd();
  	canvas->Write();
  	outfile2->Close();
  	delete outfile2;
  	
  	canvas->Print(TString(psFile + ".ps"));
  }
  cout << "Finished Plotting 1D plots" << endl;






  ///-----------------------                      
  /// Btag Significance Plots   dans
  ///-----------------------

  if(!special)
    {
  cout << "Plotting Btag Significance plots" << endl;
  for (Int_t i=0; i<nBtagPlots; i++) {
    vector<TH1F*> bkgplots;
    vector<TH1F*> sigplots;
    vector<TString> sigstrings;
    vector<TString> sigstrings2;
    //sigstrings.push_back("background (di-jets+ttbar+wbb)");

   
    for (Int_t fileItr=0; fileItr < NOverlay; fileItr++) {
      cout << "Reading fileItr = " << fileItr << endl;
      if(signal.at(fileItr)) {
      	sigstrings.push_back(outstrings.at(fileItr));
      	sigstrings2.push_back(outstrings.at(fileItr));
      	}
      for (unsigned int j=0; j<4; j++) {
	///get rid of _jsv0%dsv0 etc
      	TH1F* h = (TH1F*)((files.at(fileItr))->Get(TString(plotDir.at(fileItr) + prefix.at(fileItr) + plotBtagSignificanceList[i])));
      	if (h) 
	  cout << "Got histogram: " << TString(plotDir.at(fileItr) + prefix.at(fileItr) + plotBtagSignificanceList[i]) << endl;
      	else 
	  cout << "Did not get histogram: " << TString(plotDir.at(fileItr) + prefix.at(fileItr) + plotBtagSignificanceList[i]) << endl;

      	h->SetName(TString(plotBtagSignificanceList[i] + Form("_%d",fileItr)));

	if(signal.at(fileItr)) sigplots.push_back(h);
      	else if (bkgplots.size()<4) bkgplots.push_back(h);
      	else bkgplots.at(j)->Add(h);
      	}
    }
    sigstrings2.push_back("background (di-jets+ttbar+Wbb)");
  
    bool drawNorm = kFALSE;
    bool logx = kFALSE;
    bool logy = kFALSE;//doLogY;
    bool doFit = kFALSE;
    bool drawStats = kFALSE;
    bool drawExtra = kTRUE;
    
  	
  	//Sort out signal and background
  	int nSig = sigplots.size()/4;
  	float IntBkg = bkgplots.at(0)->Integral(0,101);
  	TH1F* plots[40];
  	TH1F* plotssig[40];
  	TH1F* effbkg;

  	//2btag inclusive
  	effbkg = new TH1F(TString(plotBtagSignificanceList[i] + "_effbkg"),TString(";j2pt cut;Efficiency"),binz,0,400);
  	effbkg->Sumw2(); 
  	//TH1F* denom = new TH1F("denom","denom",binz,-15.,25.);
	//denom->Sumw2();
  	for(unsigned int k=1; k<binz+1; k++) {
  		float A = bkgplots.at(1)->Integral(k,binz+1);
  		float B = IntBkg;
  		effbkg->SetBinContent(k,(A/B));
  		effbkg->SetBinError(k,(A/B)*TMath::Sqrt(1./A+1./B-(2*TMath::Sqrt(A))/(B*TMath::Sqrt(B))));
  		//denom->SetBinContent(k,IntBkg);
  		//denom->SetBinError(k,TMath::Sqrt(IntBkg));
  	}
  	//effbkg->Divide(denom);
  	plots[nSig]=effbkg;
  		
  	for (unsigned int j=0; j<nSig; j++) { //for each signal
  		float IntSig = sigplots.at(j*4)->Integral(0,binz+1);
  		
  		TH1F* effsig = new TH1F(TString(sigstrings2[j] + "_" + plotBtagSignificanceList[i] + "_effsig"),TString(";j2pt cut;Efficiency"),binz,0,400);
  		effsig->Sumw2();

  		for(unsigned int k=1; k<binz+1; k++) {
  			float A = sigplots.at(j*4+1)->Integral(k,binz+1);
  			float B = IntSig;  			
  			effsig->SetBinContent(k,(A/B));
  			effsig->SetBinError(k,(A/B)*TMath::Sqrt(1./A+1./B-(2*TMath::Sqrt(A))/(B*TMath::Sqrt(B))));
  			//cout << (A/B)*TMath::Sqrt(1./A+1./B-(2*TMath::Sqrt(A))/(B*TMath::Sqrt(B))) << endl;
  			//effsig->SetBinContent(k,sigplots.at(j*4+1)->Integral(k,binz+1));
  			//effsig->SetBinError(k,TMath::Sqrt(sigplots.at(j*4+1)->Integral(k,binz+1)));
  			//denom->SetBinContent(k,IntSig);
  			//denom->SetBinError(k,TMath::Sqrt(IntSig));
  		}
  		plots[j]=effsig;

  		 		
  		//Significance plot
  		TH1F* sig = new TH1F(TString(sigstrings2[j] + "_" + plotBtagSignificanceList[i] + "_sig"),TString(";j2pt cut;Significance (#epsilon(s)/#sqrt{B})*100 "),binz,0,400);
  		sig->Sumw2();  		
  		
  		for(unsigned int k=1; k<binz+1; k++) {
  			if(bkgplots.at(1)->Integral(k,binz+1)>0.) sig->SetBinContent(k,(plots[j]->GetBinContent(k)*100.)/TMath::Sqrt(bkgplots.at(1)->Integral(k,binz+1))); //might be divide by zero,also is wrong
  		}
  		plotssig[j]=sig;
  	}
      

  	
  	canvas =
        PlotAll(plots,
           	nSig+1,
            sigstrings2,
	        "",
            "",
    	    (const char*)(outDir + plotBtagSignificanceList[i] + "_eff" + plotType),
           	(const char*)(plotBtagSignificanceList[i] + "_eff"),
            outfile,
	        0.0, 0.0,
    	    0.0, 1.0,
        	drawNorm,
            logx, logy,
	        drawStats,
            drawExtra,
            writeFile,
      	    false,
          	false,
          	myLabel,
           	false,
           	true  //line-only
     	);

    
  	///-----------------------
  	/// Output
  	///-----------------------
  	TFile *outfile2 = new TFile(TString(outDir + plotBtagSignificanceList[i] + "_eff" + ".root"),"RECREATE");
  	outfile2->cd();
  	canvas->Write();
  	outfile2->Close();
  	delete outfile2;
  	
  	canvas->Print(TString(psFile + ".ps"));
  		
  	canvas =
        PlotAll(plotssig,
            nSig,
          	sigstrings2,
          	"",
            "",	
            (const char*)(outDir + plotBtagSignificanceList[i] + "_sig" + plotType),
            (const char*)(plotBtagSignificanceList[i] + "_sig"),
          	outfile,
          	0.0, 0.0,
   	        0.0, 0.0,
            drawNorm,
       	    logx, logy,
       	    drawStats,
   	        drawExtra,
            writeFile,
      	    false,
           	false,
           	myLabel,
           	false,
           	true  //line-only   
      	);
  		
        canvas =
	  PlotAll(plotssig,
		  nSig,
		  sigstrings2,
		  "",
		  "",
		  (const char*)(outDir + plotBtagSignificanceList[i] + "_sig_logy" + plotType),
		  (const char*)(plotBtagSignificanceList[i] + "_sig_logy"),
		  outfile,
		  0.0, 0.0,
		  0.0, 0.0,
		  drawNorm,
		  logx, true,
		  drawStats,
		  drawExtra,
		  writeFile,
		  false,
		  false,
		  myLabel,
		  false,
		  true  //line-only
		  );


	//  	canvas->Print(TString(outDir + plotBtagSignificanceList[i] + "_sig" + ".C"));
    
  	///-----------------------
  	/// Output
  	///-----------------------
  	outfile2 = new TFile(TString(outDir + plotBtagSignificanceList[i] + "_sig" + ".root"),"RECREATE");
  	outfile2->cd();
  	canvas->Write();
  	outfile2->Close();
  	delete outfile2;
  	
  	canvas->Print(TString(psFile + ".ps"));
  		
  	delete effbkg;
  	
  	//2btag exclusive
  }
    }



  if(special)
    {
  cout << "Plotting Btag Significance plots" << endl;
  for (Int_t i=0; i<nBtagPlots; i++) {
    vector<TH1F*> bkgplots;
    vector<TH1F*> sigplots;
    vector<TString> sigstrings;
    vector<TString> sigstrings2;
    //sigstrings.push_back("background (di-jets+ttbar+wbb)");

   
    for (Int_t fileItr=0; fileItr < NOverlay; fileItr++) {
      cout << "Reading fileItr = " << fileItr << endl;
      if(signal.at(fileItr)) {
      	sigstrings.push_back(outstrings.at(fileItr));
      	sigstrings2.push_back(outstrings.at(fileItr));
      	}
      for (unsigned int j=0; j<4; j++) {
	///get rid of _jsv0%dsv0 etc
      	TH1F* h = (TH1F*)((files.at(fileItr))->Get(TString(plotDir.at(fileItr) + prefix.at(fileItr) + plotBtagSignificanceList[i])));
      	if (h) 
	  cout << "Got histogram: " << TString(plotDir.at(fileItr) + prefix.at(fileItr) + plotBtagSignificanceList[i]) << endl;
      	else 
	  cout << "Did not get histogram: " << TString(plotDir.at(fileItr) + prefix.at(fileItr) + plotBtagSignificanceList[i]) << endl;

      	h->SetName(TString(plotBtagSignificanceList[i] + Form("_%d",fileItr)));

	if(signal.at(fileItr)) sigplots.push_back(h);
      	else if (bkgplots.size()<4) bkgplots.push_back(h);
      	else bkgplots.at(j)->Add(h);
      	}
    }
    sigstrings2.push_back("background (di-jets+ttbar+Wbb)");
  
    bool drawNorm = kFALSE;
    bool logx = kFALSE;
    bool logy = kFALSE;//doLogY;
    bool doFit = kFALSE;
    bool drawStats = kFALSE;
    bool drawExtra = kTRUE;
    
  	
  	//Sort out signal and background
  	int nSig = sigplots.size()/4;
  	float IntBkg = bkgplots.at(0)->Integral(0,binz+1);
  	TH1F* plots[40];
  	TH1F* plotssig[40];
  	TH1F* effbkg;

  	//2btag inclusive
  	effbkg = new TH1F(TString(plotBtagSignificanceList[i] + "_effbkg"),TString(";j2pt cut;Efficiency"),binz,0,400);
  	effbkg->Sumw2(); 
  	//TH1F* denom = new TH1F("denom","denom",binz,-15.,25.);
	//denom->Sumw2();
  	for(unsigned int k=binz+1; k>0; k--) {
  		float A = bkgplots.at(1)->Integral(0,k);
  		float B = IntBkg;
  		effbkg->SetBinContent(k,(A/B));
  		effbkg->SetBinError(k,(A/B)*TMath::Sqrt(1./A+1./B-(2*TMath::Sqrt(A))/(B*TMath::Sqrt(B))));
  		//denom->SetBinContent(k,IntBkg);
  		//denom->SetBinError(k,TMath::Sqrt(IntBkg));
  	}
  	//effbkg->Divide(denom);
  	plots[nSig]=effbkg;
  		
  	for (unsigned int j=0; j<nSig; j++) { //for each signal
  		float IntSig = sigplots.at(j*4)->Integral(0,binz+1);
  		
  		TH1F* effsig = new TH1F(TString(sigstrings2[j] + "_" + plotBtagSignificanceList[i] + "_effsig"),TString(";j2pt cut;Efficiency"),binz,0,400);
  		effsig->Sumw2();

  		for(unsigned int k=binz+1; k>0; k--) {
		        float A = sigplots.at(j*4+1)->Integral(0,k);
  			float B = IntSig;  			
  			effsig->SetBinContent(k,(A/B));
  			effsig->SetBinError(k,(A/B)*TMath::Sqrt(1./A+1./B-(2*TMath::Sqrt(A))/(B*TMath::Sqrt(B))));
  			
  		}
  		plots[j]=effsig;

  		 		
  		//Significance plot
  		TH1F* sig = new TH1F(TString(sigstrings2[j] + "_" + plotBtagSignificanceList[i] + "_sig"),TString(";j2pt cut;Significance (#epsilon(s)/#sqrt{B})*100 "),binz,0,400);
  		sig->Sumw2();  		
  		
  		for(unsigned int k=binz+1; k>0; k--) {
  			if(bkgplots.at(1)->Integral(0,k)>0.) sig->SetBinContent(k,(plots[j]->GetBinContent(k)*100.)/TMath::Sqrt(bkgplots.at(1)->Integral(0,k))); //might be divide by zero,also is wrong
  		}
  		plotssig[j]=sig;
  	}
      

  	
  	canvas =
        PlotAll(plots,
           	nSig+1,
            sigstrings2,
	        "",
            "",
    	    (const char*)(outDir + plotBtagSignificanceList[i] + "_eff" + plotType),
           	(const char*)(plotBtagSignificanceList[i] + "_eff"),
            outfile,
	        0.0, 0.0,
    	    0.0, 1.0,
        	drawNorm,
            logx, logy,
	        drawStats,
            drawExtra,
            writeFile,
      	    false,
          	false,
          	myLabel,
           	false,
           	true  //line-only
     	);

    
  	///-----------------------
  	/// Output
  	///-----------------------
  	TFile *outfile2 = new TFile(TString(outDir + plotBtagSignificanceList[i] + "_eff" + ".root"),"RECREATE");
  	outfile2->cd();
  	canvas->Write();
  	outfile2->Close();
  	delete outfile2;
  	
  	canvas->Print(TString(psFile + ".ps"));
  		
  	canvas =
        PlotAll(plotssig,
            nSig,
          	sigstrings2,
          	"",
            "",	
            (const char*)(outDir + plotBtagSignificanceList[i] + "_sig" + plotType),
            (const char*)(plotBtagSignificanceList[i] + "_sig"),
          	outfile,
          	0.0, 0.0,
   	        0.0, 0.0,
            drawNorm,
       	    logx, logy,
       	    drawStats,
   	        drawExtra,
            writeFile,
      	    false,
           	false,
           	myLabel,
           	false,
           	true  //line-only   
      	);
  		
        canvas =
	  PlotAll(plotssig,
		  nSig,
		  sigstrings2,
		  "",
		  "",
		  (const char*)(outDir + plotBtagSignificanceList[i] + "_sig_logy" + plotType),
		  (const char*)(plotBtagSignificanceList[i] + "_sig_logy"),
		  outfile,
		  0.0, 0.0,
		  0.0, 0.0,
		  drawNorm,
		  logx, true,
		  drawStats,
		  drawExtra,
		  writeFile,
		  false,
		  false,
		  myLabel,
		  false,
		  true  //line-only
		  );


	//  	canvas->Print(TString(outDir + plotBtagSignificanceList[i] + "_sig" + ".C"));
    
  	///-----------------------
  	/// Output
  	///-----------------------
  	outfile2 = new TFile(TString(outDir + plotBtagSignificanceList[i] + "_sig" + ".root"),"RECREATE");
  	outfile2->cd();
  	canvas->Write();
  	outfile2->Close();
  	delete outfile2;
  	
  	canvas->Print(TString(psFile + ".ps"));
  		
  	delete effbkg;
  	
  	//2btag exclusive
  }
    }


  
  canvas->Print(TString(psFile + ".ps]"));       
}

