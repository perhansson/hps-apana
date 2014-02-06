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

void BtagOptOverlay(Int_t NOverlay,
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
                        TString plotType = ".eps",
                        bool dataMCCompare = true,
                        bool dataMCRatio = true,
                        TString newLabel = "",
                        bool writeFile = true,
                        bool doLogY = false,
                        bool doLogZ = false,
                        int Rebin = 1)
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
  Int_t n1DPlots = 0;
  TString plot1DList[40] = {
  			    			"btagopt_susy_0lmet504j7030_jsv00sv0",  
  			    			"btagopt_susy_0lmet504j7030_jsv01sv0",  
  			    			"btagopt_susy_0lmet504j7030_jsv02sv0",  
  			    			"btagopt_susy_0lmet504j7030_jsv03sv0",
  			    			/*
			    			"btagopt_susy_0lmet502j7030_jpt",  
			    			"btagopt_susy_0lmet502j7030_bjpt",  
			    			"btagopt_susy_0lmet502j7030_btagpt", 
			    			"btagopt_susy_0lmet502j7030_nbj",  
			    			"btagopt_susy_0lmet502j7030_nbtag", 
			    			"btagopt_susy_0lmet502j7030_nbtag2incl", 
			    			"btagopt_susy_0lmet503j7030_jsv0",  
			    			"btagopt_susy_0lmet503j7030_jpt",  
			    			"btagopt_susy_0lmet503j7030_bjpt",  
			    			"btagopt_susy_0lmet503j7030_btagpt", 
			    			"btagopt_susy_0lmet503j7030_nbj",  
			    			"btagopt_susy_0lmet503j7030_nbtag", 
			    			"btagopt_susy_0lmet503j7030_nbtag2incl",
			    			*/
                           };
                           
  Int_t nBtagPlots = 0;
  TString plotBtagSignificanceList[40] = {
  			    			//"btagopt_susy_0lmet503j7030",  
  			    			"btagopt_susy_0lmet504j7030", 
                           };    

  Int_t nBtagTriggerPlots = 10;
  TString plotBtagTriggerList[40] = {
  			    			"btagopt_susy_0lmet502j16020_nbtag",  //L1_J55
  			    			"btagopt_susy_0lmet502j160_nbtag",  //L1_2J55
  			    			"btagopt_susy_0lmet503j60_nbtag",  //L1_3J10
  			    			"btagopt_susy_0lmet503j12012060_nbtag", //L1_3J10_2J30
  			    			"btagopt_susy_0lmet504j60_nbtag", //L1_4J5
  			    			"btagopt_susy_0lmet504j8060_nbtag", //L1_4J5_J15
  			    			"btagopt_susy_0lmet504j12060_nbtag", //L1_4J5_J30
  			    			"btagopt_susy_0lmet502j20je330_nbtag", //L1_JE100
  			    			"btagopt_susy_0lmet502j20je370_nbtag", //L1_JE140
  			    			"btagopt_susy_0lmet1002j20_nbtag", //L1_XE30
                           };       
  TString plotBtagTriggerList2[40] = {
  			    			"L1_J55",
  			    			"L1_2J55",
  			    			"L1_3J10",
  			    			"L1_3J10_2J30",
  			    			"L1_4J5",
  			    			"L1_4J5_J15",
  			    			"L1_4J5_J30",
  			    			"L1_JE100",
  			    			"L1_JE140",
  			    			"L1_XE30",
                           };                         
  /*
  Int_t nXProfilePlots = 12;
  TString plotXProfileList[20] = {
                               "NTrkVsPt_0_0",
                               "NTrkVsPt_0_1",
                               "NTrkVsPt_0_2",
                               "NTrkVsPt_1_0",
                               "NTrkVsPt_1_1",
                               "NTrkVsPt_1_2", 
                               "DPhiVsPt_0_0",
                               "DPhiVsPt_0_1",
                               "DPhiVsPt_0_2",
                               "DPhiVsPt_1_0",
                               "DPhiVsPt_1_1",
                               "DPhiVsPt_1_2",  
                              };
                              
  Int_t n2DPlots = 6;
  TString plot2DList[20] = {
                               "DPhiVsPt_0_0",
                               "DPhiVsPt_0_1",
                               "DPhiVsPt_0_2",
                               "DPhiVsPt_1_0",
                               "DPhiVsPt_1_1",
                               "DPhiVsPt_1_2",  
                              };
  */
  
  ///-----------------------                      
  /// 1D Plots   
  ///-----------------------
  cout << "Plotting 1D plots" << endl;
  for (Int_t i=0; i<n1DPlots; i++) {
    //vector<TH1F*> plots;
    TH1F* plots[50];
    double max = 0.0;
    double min = 1.0;
    for (Int_t fileItr=(NOverlay-1); fileItr > -1; fileItr--) {
      cout << "Reading fileItr = " << fileItr << endl;
      TH1F *h = (TH1F*)((files.at(fileItr))->Get(TString(plotDir.at(fileItr) + prefix.at(fileItr) + plot1DList[i] + suffix.at(fileItr))));
      if (h) cout << "Got histogram: " << TString(plotDir.at(fileItr) + prefix.at(fileItr) + plot1DList[i] + suffix.at(fileItr)) << endl;
      else cout << "Did not get histogram: " << TString(plotDir.at(fileItr) + prefix.at(fileItr) + plot1DList[i] + suffix.at(fileItr)) << endl;
      h->SetName(TString(plot1DList[i] + Form("_%d",fileItr)));
      h->Rebin(Rebin);
      h->Scale(1./(float)h->Integral(0,h->GetNbinsX()+1));
      //if(fileItr==0) {
		//h->Scale(plots[1]->GetEntries()/h->GetEntries());
      //}
      //h->Scale(weights.at(fileItr));
      //cout << "Set Name: " << TString(plot1DList[i] + Form("_%d",fileItr)) << endl;
      //plots.push_back(h);
      //if (plot1DList[i].Contains("Res_NTrk") || plot1DList[i].Contains("Res_EMFrac") || plot1DList[i].Contains("Res_SumTrkPt")) h->Rebin(3);
      //if (plot1DList[i].Contains("Inclusive_0_0_1")) h->Rebin(6);
      //if (plot1DList[i].Contains("Inclusive_0_0_2")) h->Rebin(6);
 
 
	  for (unsigned int j=1; j<h->GetNbinsX()+1; j++) {
	  	if (h->GetBinContent(j)==0) continue;
	  	if (h->GetBinContent(j)>max) max = h->GetBinContent(j);
	  	if (h->GetBinContent(j)<min) min = h->GetBinContent(j);
	  
	  }
      
      //max = exp(100.0*log(max));
      //float tempmax = 2.0*h->GetBinContent(h->GetMaximumBin());
      
      //min = exp(0.9*log(min));
    
      //if(min<1.0) min = 1.0;
      //h->SetTitle(plot1DList[i]);
      plots[fileItr] = h;
    }
    
    cout << "Min: " << min << endl;
    cout << "Max: " << max << endl;
  
    bool drawNorm = kFALSE; //kFALSE;
    bool logx = kFALSE;
    bool logy = kFALSE;//doLogY;
    bool doFit = kFALSE;
    bool drawStats = kFALSE;
    bool drawExtra = kTRUE;
    
    if (plot1DList[i].Contains("sv0") 
        //|| plot1DList[i] == "jet_EFracConst"
       ) logy = true;
    else logy = false;
    
    //vector<TString> tags2;
  	//tags2.push_back(tags.at(0));
  	//tags2.push_back(tags.at(1));
  	//if (plot1DList[i].Contains("NTrk_0")) tags2.push_back("anti-k_{t} topo-cluster jets R=0.6, "+TString(plots[0]->GetTitle()));
  	//else if (plot1DList[i].Contains("NTrk_1")) tags2.push_back("anti-k_{t} topo-tower jets R=0.6, "+TString(plots[0]->GetTitle()));

  	//if (plot1DList[i].Contains("TrackPt_0")) tags2.push_back("anti-k_{t} topo-cluster jets R=0.6, "+TString(plots[0]->GetTitle()));
  	//else if (plot1DList[i].Contains("TrackPt_1")) tags2.push_back("anti-k_{t} topo-tower jets R=0.6, "+TString(plots[0]->GetTitle()));
    
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
                0.00001, 10000.,
                drawNorm,
                logx, logy,
                drawStats,
                drawExtra,
                writeFile,
                dataMCCompare,
                dataMCRatio,
                plot1DList[i].ReplaceAll("btagopt_susy_",""),
                false,
                true  //line-only
               );
               
    canvas->Print(TString(outDir + "overlay_" + plot1DList[i] + suffix.at(0) + ".C"));
    
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
  /// Btag Significance Plots   
  ///-----------------------
  cout << "Plotting Btag Significance plots" << endl;
  for (Int_t i=0; i<nBtagPlots; i++) {
    vector<TH1F*> bkgplots;
    vector<TH1F*> sigplots;
    vector<TString> bkgstrings;
    vector<TString> sigstrings2;
    //sigstrings.push_back("background (di-jets+ttbar+wbb)");
    for (Int_t fileItr=0; fileItr < NOverlay; fileItr++) {
      cout << "Reading fileItr = " << fileItr << endl;
      if(signal.at(fileItr)) {
      	sigstrings2.push_back(outstrings.at(fileItr));
      	}
      else bkgstrings.push_back(tags.at(fileItr));
      for (unsigned int j=0; j<4; j++) {
      	TH1F* h = (TH1F*)((files.at(fileItr))->Get(TString(plotDir.at(fileItr) + prefix.at(fileItr) + plotBtagSignificanceList[i] + Form("_jsv0%dsv0",j))));
      	if (h) cout << "Got histogram: " << TString(plotDir.at(fileItr) + prefix.at(fileItr) + plotBtagSignificanceList[i] + Form("_jsv0%dsv0",j)) << endl;
      	else cout << "Did not get histogram: " << TString(plotDir.at(fileItr) + prefix.at(fileItr) + plotBtagSignificanceList[i] + Form("_jsv0%dsv0",j)) << endl;
      	h->SetName(TString(plotBtagSignificanceList[i] + Form("_jsv0%dsv0",j) + Form("_%d",fileItr)));
		h->Rebin(Rebin);

		if(signal.at(fileItr)) sigplots.push_back(h);
      	else if (bkgplots.size()<4) bkgplots.push_back(h);
      	else bkgplots.at(j)->Add(h);
      	}
    }
    TString bkgs = "";
    TString type = "";
    for (unsigned int j = 0; j<bkgstrings.size(); j++) {
    	if (bkgstrings.at(j).Contains("hadronic")) continue;
		if(j==0) bkgs = bkgstrings.at(j);
		else bkgs = TString(bkgs+"+"+bkgstrings.at(j));
    }
    if (bkgs.Contains("QCD")&&bkgs.Contains("ttbar")) type = "all ";
    else if (bkgs.Contains("QCD")) type = "light ";
    else if (bkgs.Contains("ttbar")) type = "heavy ";
    sigstrings2.push_back(TString(type+"backgrounds ("+bkgs+")"));
  
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
  	TH1F* plotssb[40];
  	TH1F* effbkg;
	TH1F* sigtags1[40];
	TH1F* sigtags2[40];
	
	for (unsigned int isExclusive=0; isExclusive<2; isExclusive++) {
		
		TString inex = "in";
		if(isExclusive) inex = "ex";
		
		if(!isExclusive) {
  			for (unsigned int j=0; j<nSig; j++) { //for each signal	
				sigtags1[j] = new TH1F(TString(plotBtagSignificanceList[i] + "_" + sigstrings2[j] + inex + "cl_sigtags1"),TString(TString(";N_{tags} ") + inex + "clusive, SV0>1;Relative significance"),5,-0.5,4.5);
				sigtags2[j] = new TH1F(TString(plotBtagSignificanceList[i] + "_" + sigstrings2[j] + inex + "cl_sigtags2"),TString(TString(";N_{tags} ") + inex + "clusive, SV0>5;Relative significance"),5,-0.5,4.5);
			}
		}
		
		for (unsigned int nTag=1; nTag<5; nTag++) {
		
			float sigmax = -1.0;
			float sbmax = -1.0;
			
			cout << "N tags: " << nTag << endl;
		
			if((nTag==4)&&isExclusive) continue;
		
  			effbkg = new TH1F(TString(plotBtagSignificanceList[i] + Form("_%dbtag",nTag) + inex + "cl_effbkg"),TString(TString(";Jet SV0 cut;Efficiency ") + Form("%d-btag ",nTag) + inex + "clusive"),100/Rebin,-15.,25.);
  			effbkg->Sumw2();
  			//TH1F* denom = new TH1F("denom","denom",100,-15.,25.);
			//denom->Sumw2();
  			for(unsigned int k=1; k<(100/Rebin+1); k++) {
  				float A = bkgplots.at(nTag-1)->Integral(k,(100/Rebin+1));
  				if(isExclusive) A = bkgplots.at(nTag-1)->Integral(k,(100/Rebin+1)) - bkgplots.at(nTag)->Integral(k,(100/Rebin+1));
  				float B = IntBkg;
  				effbkg->SetBinContent(k,(A/B));
  				effbkg->SetBinError(k,(A/B)*TMath::Sqrt(1./A+1./B-(2*TMath::Sqrt(A))/(B*TMath::Sqrt(B))));
  				//denom->SetBinContent(k,IntBkg);
  				//denom->SetBinError(k,TMath::Sqrt(IntBkg));
  			}
  			//effbkg->Divide(denom);
  			plots[nSig]=effbkg;

  			for (unsigned int j=0; j<nSig; j++) { //for each signal	
  			
  				float IntSig = sigplots.at(j*4)->Integral(0,(100/Rebin+1));
  		
  				if((nTag==1)&&!isExclusive) {
  					sigtags1[j]->SetBinContent(1,IntSig/IntBkg);
  					sigtags2[j]->SetBinContent(1,IntSig/IntBkg);
  				}
  		
  				TH1F* effsig = new TH1F(TString(sigstrings2[j] + "_" + plotBtagSignificanceList[i] + Form("_%dbtag",nTag) + inex + "cl_effsig"),TString(TString(";Jet SV0 cut;Efficiency ")+Form("%d-btag ",nTag)+inex+"clusive"),100/Rebin,-15.,25.);
  				effsig->Sumw2();

  				for(unsigned int k=1; k<(100/Rebin+1); k++) {
  					float A = sigplots.at(j*4+nTag-1)->Integral(k,(100/Rebin+1));
  					if(isExclusive) A = sigplots.at(j*4+nTag-1)->Integral(k,(100/Rebin+1)) - sigplots.at(j*4+nTag)->Integral(k,(100/Rebin+1));
  					float B = IntSig;  			
  					effsig->SetBinContent(k,(A/B));
  					effsig->SetBinError(k,(A/B)*TMath::Sqrt(1./A+1./B-(2*TMath::Sqrt(A))/(B*TMath::Sqrt(B))));

  				}
  				plots[j]=effsig;
 		
  				//Significance plot
  				TH1F* sig = new TH1F(TString(sigstrings2[j] + "_" + plotBtagSignificanceList[i] + Form("_%dbtag",nTag) + inex + "cl_sig"),TString(TString(";Jet SV0 cut;S/#sqrt{B} (arbitrary scale) ")+Form("%d-btag ",nTag)+inex+"clusive"),100/Rebin,-15.,25.);
  				sig->Sumw2();  	
  				
				float localmax = -1.0; 		
  		
  				for(unsigned int k=1; k<(100/Rebin+1); k++) {
  					if((!isExclusive)&&(bkgplots.at(nTag-1)->Integral(k,(100/Rebin+1))>0.)) sig->SetBinContent(k,(sigplots.at(j*4+nTag-1)->Integral(k,(100/Rebin+1)))/TMath::Sqrt(bkgplots.at(nTag-1)->Integral(k,(100/Rebin+1)))); //might be divide by zero,also is wrong
  					else if((isExclusive)&&((bkgplots.at(nTag-1)->Integral(k,(100/Rebin+1))-bkgplots.at(nTag)->Integral(k,(100/Rebin+1)))>0.)) sig->SetBinContent(k,(sigplots.at(j*4+nTag-1)->Integral(k,(100/Rebin+1)) - sigplots.at(j*4+nTag)->Integral(k,(100/Rebin+1)))/TMath::Sqrt(bkgplots.at(nTag-1)->Integral(k,(100/Rebin+1))-bkgplots.at(nTag)->Integral(k,(100/Rebin+1)))); //might be divide by zero,also is wrong
					else sig->SetBinContent(k,0.0);
					if ((k>floor(39/Rebin)+1)&&(sig->GetBinContent(k)>(localmax/1.2))) localmax=sig->GetBinContent(k)*1.2;
					//cout << "Bin: " << k << " Local max: " << localmax << endl;
  				}
  				if(!isExclusive) {
  					sigtags1[j]->SetBinContent(nTag+1,sig->GetBinContent(5));
  					sigtags2[j]->SetBinContent(nTag+1,sig->GetBinContent(6));
  				}
  				if(localmax/sig->GetBinContent(floor(39/Rebin)+2)>sigmax) sigmax=localmax/sig->GetBinContent(floor(39/Rebin)+2);
  				sig->Scale(1/sig->GetBinContent(floor(39/Rebin)+2));
  				plotssig[j]=sig;

  				//S/B plot
  				TH1F* sb = new TH1F(TString(sigstrings2[j] + "_" + plotBtagSignificanceList[i] + Form("_%dbtag",nTag) + inex + "cl_sb"),TString(TString(";Jet SV0 cut;S/B (arbitrary scale) ")+Form("%d-btag ",nTag)+inex+"clusive"),100/Rebin,-15.,25.);
  				sb->Sumw2();  	
  				
				localmax = -1.0; 	
  		
  				for(unsigned int k=1; k<(100/Rebin+1); k++) {
  					if((!isExclusive)&&(bkgplots.at(nTag-1)->Integral(k,(100/Rebin+1))>0.)) sb->SetBinContent(k,(sigplots.at(j*4+nTag-1)->Integral(k,(100/Rebin+1)))/bkgplots.at(nTag-1)->Integral(k,(100/Rebin+1))); //might be divide by zero,also is wrong
  					else if((isExclusive)&&((bkgplots.at(nTag-1)->Integral(k,(100/Rebin+1))-bkgplots.at(nTag)->Integral(k,(100/Rebin+1)))>0.)) sb->SetBinContent(k,(sigplots.at(j*4+nTag-1)->Integral(k,(100/Rebin+1)) - sigplots.at(j*4+nTag)->Integral(k,(100/Rebin+1)))/(bkgplots.at(nTag-1)->Integral(k,(100/Rebin+1))-bkgplots.at(nTag)->Integral(k,(100/Rebin+1)))); //might be divide by zero,also is wrong
					else sb->SetBinContent(k,0.0);
					if ((k>floor(39/Rebin)+1)&&(sb->GetBinContent(k)>(localmax/1.2))) localmax=sb->GetBinContent(k)*1.2;
  				}
  				if(localmax/sb->GetBinContent(floor(39/Rebin)+2)>sbmax) sbmax=localmax/sb->GetBinContent(floor(39/Rebin)+2);
  				sb->Scale(1/sb->GetBinContent(floor(39/Rebin)+2));
  				plotssb[j]=sb;
  			}

			//cout << "Sigmax: " << sigmax << endl;  			
  			if (sigmax<2.0) sigmax=2.0;
  			if (sbmax<6.0) sbmax=6.0;

  			canvas =
    		    PlotAll(plots,
   		        	nSig+1,
  		          	sigstrings2,
			        "",
			        "",
			        (const char*)(TString(outDir + plotBtagSignificanceList[i] + Form("_%dbtag",nTag) + inex + "cl_eff" + plotType)),
           			(const char*)(TString(plotBtagSignificanceList[i] + Form("_%dbtag",nTag) + inex + "cl_eff")),
            		outfile,
	        		1.0, 25.,
    	    		0.0, 1.0,
        			drawNorm,
            		logx, logy,
	        		drawStats,
            		drawExtra,
            		writeFile,
      	    		false,
          			false,
          			plotBtagSignificanceList[i].ReplaceAll("btagopt_susy_",""),
           			false,
           			true  //line-only
     			);
  		
  			canvas->Print(TString(outDir + plotBtagSignificanceList[i] + Form("_%dbtag",nTag) + inex + "cl_eff" + ".C"));
    
  			///-----------------------
  			/// Output
  			///-----------------------
  			TFile *outfile2 = new TFile(TString(outDir + plotBtagSignificanceList[i] + Form("_%dbtag",nTag) + inex + "cl_eff" + ".root"),"RECREATE");
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
            		(const char*)(TString(outDir + plotBtagSignificanceList[i] + Form("_%dbtag",nTag) + inex + "cl_sig" + plotType)),
            		(const char*)(TString(plotBtagSignificanceList[i] + Form("_%dbtag",nTag) + inex + "cl_sig")),
          			outfile,
          			1.0, 25.,
   	        		0.0, sigmax,
            		drawNorm,
       	    		logx, logy,
       	    		drawStats,
   	        		drawExtra,
            		writeFile,
      	    		false,
           			false,
           			plotBtagSignificanceList[i].ReplaceAll("btagopt_susy_",""),
           			false,
           			true  //line-only   
      			);
  		
  			canvas->Print(TString(outDir + plotBtagSignificanceList[i] + Form("_%dbtag",nTag) + inex + "cl_sig" + ".C"));
    
  			///-----------------------
  			/// Output
  			///-----------------------
  			outfile2 = new TFile(TString(outDir + plotBtagSignificanceList[i] + Form("_%dbtag",nTag) + inex + "cl_sig" + ".root"),"RECREATE");
  			outfile2->cd();
  			canvas->Write();
  			outfile2->Close();
  			delete outfile2;
  	
  			canvas->Print(TString(psFile + ".ps"));
  	
  			canvas =
        		PlotAll(plotssb,
            		nSig,
          			sigstrings2,
          			"",
            		"",	
            		(const char*)(TString(outDir + plotBtagSignificanceList[i] + Form("_%dbtag",nTag) + inex + "cl_sb" + plotType)),
            		(const char*)(TString(plotBtagSignificanceList[i] + Form("_%dbtag",nTag) + inex + "cl_sb")),
          			outfile,
          			1.0, 25.,
   	        		0.0, sbmax,
            		drawNorm,
       	    		logx, logy,
       	    		drawStats,
   	        		drawExtra,
            		writeFile,
      	    		false,
           			false,
           			plotBtagSignificanceList[i].ReplaceAll("btagopt_susy_",""),
           			false,
           			true  //line-only   
      			);
  		
  			canvas->Print(TString(outDir + plotBtagSignificanceList[i] + Form("_%dbtag",nTag) + inex + "cl_sb" + ".C"));
    
  			///-----------------------
  			/// Output
  			///-----------------------
  			outfile2 = new TFile(TString(outDir + plotBtagSignificanceList[i] + Form("_%dbtag",nTag) + inex + "cl_sb" + ".root"),"RECREATE");
  			outfile2->cd();
  			canvas->Write();
  			outfile2->Close();
  			delete outfile2;
  	
  			canvas->Print(TString(psFile + ".ps"));
  		
  			delete effbkg;
  		}
  	}       
  	
  	//Now plot signals vs ntag
  	
  	for (unsigned int j=0; j<nSig; j++) { //for each signal	
  		sigtags2[j]->Scale(1/sigtags1[j]->GetBinContent(1));
  		sigtags1[j]->Scale(1/sigtags1[j]->GetBinContent(1));
  	}  	
  	
  	canvas =
        PlotAll(sigtags1,
       		nSig,  
       		sigstrings2,
          	"",
       		"",	
       		(const char*)(TString(outDir + plotBtagSignificanceList[i] + "_incl_sigtag1" + plotType)),
       		(const char*)(TString(plotBtagSignificanceList[i] + "_incl_sigtag1")),
   			outfile,
    		-0.5, 4.5,
   	   		0.0, 0.0,
       		drawNorm,
       		logx, logy,
       		drawStats,
   	   		drawExtra,
       		writeFile,
       		false,
   			false,
   			plotBtagSignificanceList[i].ReplaceAll("btagopt_susy_",""),
      		false,
           	true  //line-only   
      	);
  		
  	canvas->Print(TString(outDir + plotBtagSignificanceList[i] + "_incl_sigtag1" + ".C"));
    
  	///-----------------------
  	/// Output
  	///-----------------------
  	TFile* outfile2 = new TFile(TString(outDir + plotBtagSignificanceList[i] + "_incl_sigtag1" + ".root"),"RECREATE");
  	outfile2->cd();
  	canvas->Write();
  	outfile2->Close();
  	delete outfile2;
  	
  	canvas->Print(TString(psFile + ".ps"));
  	
  	canvas =
        PlotAll(sigtags2,
       		nSig,  
       		sigstrings2,
          	"",
       		"",	
       		(const char*)(TString(outDir + plotBtagSignificanceList[i] + "_incl_sigtags2" + plotType)),
       		(const char*)(TString(plotBtagSignificanceList[i] + "_incl_sigtags2")),
   			outfile,
    		-0.5, 4.5,
   	   		0.0, 0.0,
       		drawNorm,
       		logx, logy,
       		drawStats,
   	   		drawExtra,
       		writeFile,
       		false,
   			false,
   			plotBtagSignificanceList[i].ReplaceAll("btagopt_susy_",""),
      		false,
           	true  //line-only   
      	);
  		
  	canvas->Print(TString(outDir + plotBtagSignificanceList[i] + "_incl_sigtags2" + ".C"));
    
  	///-----------------------
  	/// Output
  	///-----------------------
  	outfile2 = new TFile(TString(outDir + plotBtagSignificanceList[i] + "_incl_sigtags2" + ".root"),"RECREATE");
  	outfile2->cd();
  	canvas->Write();
  	outfile2->Close();
  	delete outfile2;
  	
  	canvas->Print(TString(psFile + ".ps"));
  	
  }
  cout << "Finished Plotting Btag Significance plots" << endl;

  ///-----------------------                      
  /// Btag Trigger Plots   
  ///-----------------------
  cout << "Plotting Btag Trigger plots" << endl;
  //Put in factor of 1/2 for 50 pb-1
  for (Int_t i=0; i<nBtagTriggerPlots; i++) {
    vector<TH1F*> bkgplots;
    vector<TH1F*> sigplots;
    vector<TString> bkgstrings;
    vector<TString> sigstrings2;
    //sigstrings.push_back("background (di-jets+ttbar+wbb)");
    for (Int_t fileItr=0; fileItr < NOverlay; fileItr++) {
      cout << "Reading fileItr = " << fileItr << endl;
      if(signal.at(fileItr)) {
      	sigstrings2.push_back(outstrings.at(fileItr));
      	}
      else bkgstrings.push_back(tags.at(fileItr));
      
      TH1F* h = (TH1F*)((files.at(fileItr))->Get(TString(plotDir.at(fileItr) + prefix.at(fileItr) + plotBtagTriggerList[i])));
      if (h) cout << "Got histogram: " << TString(plotDir.at(fileItr) + prefix.at(fileItr) + plotBtagTriggerList[i]) << endl;
      else cout << "Did not get histogram: " << TString(plotDir.at(fileItr) + prefix.at(fileItr) + plotBtagTriggerList[i]) << endl;
      h->SetName(TString(plotBtagSignificanceList[i] + Form("_%d",fileItr)));
	  //h->Rebin(Rebin);

	  if(signal.at(fileItr)) sigplots.push_back(h);
      else if (bkgplots.size()==0) bkgplots.push_back(h);
      else bkgplots.at(0)->Add(h);
    }
	//cout << "Hi" << endl;

    TString bkgs = "";
    TString type = "";
    for (unsigned int j = 0; j<bkgstrings.size(); j++) {
    	if (bkgstrings.at(j).Contains("hadronic")) continue;
		if(j==0) bkgs = bkgstrings.at(j);
		else bkgs = TString(bkgs+"+"+bkgstrings.at(j));
    }
    if (bkgs.Contains("QCD")&&bkgs.Contains("ttbar")) type = "all ";
    else if (bkgs.Contains("QCD")) type = "light ";
    else if (bkgs.Contains("ttbar")) type = "heavy ";
    sigstrings2.push_back(TString(type+"backgrounds ("+bkgs+")"));
  
    bool drawNorm = kFALSE;
    bool logx = kFALSE;
    bool logy = kFALSE;//doLogY;
    bool doFit = kFALSE;
    bool drawStats = kFALSE;
    bool drawExtra = kTRUE;

	bool do2D = false;
  	
  	//Sort out signal and background
  	int nSig = sigplots.size();
  	//float IntBkg = bkgplots.at(0)->Integral(0,101);
  	TH1F* plots[40];
  	TH1F* plotssig[40];
  	//TH1F* plotssb[40];
  	//TH1F* effbkg;
	//TH1F* sigtags1[40];
	//TH1F* sigtags2[40];
	
	//cout << "Hi" << endl;
	
	if(do2D) gStyle->SetOptTitle(1);
	
  	for (unsigned int j=0; j<nSig; j++) { //for each signal	
 		
 		TH2F* nEvents2 = new TH2F(TString(plotBtagTriggerList2[i] + "_" + sigstrings2[j] + "_nEvents"),TString(TString("S, ")+sigstrings2[j]+", "+plotBtagTriggerList2[i]+";#sigma/#sigma_{PYTHIA};N_{tags} SV0>3 (inclusive)"),10,0.1,2.1,5,-0.5,4.5);
 		TH2F* Sig2 = new TH2F(TString(plotBtagTriggerList2[i] + "_" + sigstrings2[j] + "_Sig"),TString(TString("S/#sqrt{B}, ")+sigstrings2[j]+", "+plotBtagTriggerList2[i]+";#sigma/#sigma_{PYTHIA};N_{tags} SV0>3 (inclusive)"),10,0.1,2.1,5,-0.5,4.5); 

 		TH1F* nEvents1 = new TH1F(TString(plotBtagTriggerList2[i] + "_" + sigstrings2[j] + "_nEvents"),TString(";N_{tags} SV0>3 (inclusive); N events at 50 pb^{-1}"),5,-0.5,4.5);
 		TH1F* Sig1 = new TH1F(TString(plotBtagTriggerList2[i] + "_" + sigstrings2[j] + "_Sig"),TString(";N_{tags} SV0>3 (inclusive); S/#sqrt{B} at 50 pb^{-1}"),5,-0.5,4.5); 		
	
		for(unsigned int nTags=0; nTags<5; nTags++) {
		
			if(do2D) {
				float S = sigplots.at(j)->Integral(nTags+1,5)/2.0; //inclusive
				float B = bkgplots.at(0)->Integral(nTags+1,5)/2.0; //inclusive
			
				for(unsigned int k=1; k<11; k++) {
					if (S*(float(k)/5.0)>10.0) nEvents2->SetBinContent(k,nTags,S*(float(k)/5.0));
				
					if(B>0.0) Sig2->SetBinContent(k,nTags,(S*(float(k)/5.0))/TMath::Sqrt(B));	
					//else if (S*(float(k)/5.0)<=10.0) Sig->SetBinContent(k,nTags,0.0);
					//else if (B<=0.0) Sig->SetBinContent(k,nTags,-1.0);
				}
			}
			else {
				double errS = 0;
				double errB = 0;
				double S = sigplots.at(j)->IntegralAndError(nTags+1,5,errS); //inclusive
				double B = bkgplots.at(0)->IntegralAndError(nTags+1,5,errB); //inclusive
				
				nEvents1->SetBinContent(nTags,S);
				nEvents1->SetBinError(nTags,errS);
				
				Sig1->SetBinContent(nTags,S/TMath::Sqrt(B));
				Sig1->SetBinError(nTags,(S/TMath::Sqrt(B))*TMath::Sqrt((errS/S)*(errS/S)+0.25*(errB/B)*(errB/B)));
			}
		}
		
		if(do2D) {
		nEvents2->Draw("colz");
		
		canvas->SetRightMargin(10);

  		canvas->Print(TString(outDir + plotBtagTriggerList2[i] + "_" + sigstrings2.at(j) + "_nEvents" + ".eps"));	
  		canvas->Print(TString(outDir + plotBtagTriggerList2[i] + "_" + sigstrings2.at(j) + "_nEvents" + ".C"));
    
  		///-----------------------
  		/// Output
  		///-----------------------
  		TFile* outfile2 = new TFile(TString(outDir + plotBtagTriggerList2[i] + "_" + sigstrings2.at(j) + "_nEvents" + ".root"),"RECREATE");
  		outfile2->cd();
  		canvas->Write();
  		outfile2->Close();
  		delete outfile2;
  		
  		canvas->Print(TString(psFile + ".ps"));
  		
		Sig2->Draw("colz");

  		canvas->Print(TString(outDir + plotBtagTriggerList2[i] + "_" + sigstrings2.at(j) + "_Sig" + ".eps"));	
  		canvas->Print(TString(outDir + plotBtagTriggerList2[i] + "_" + sigstrings2.at(j) + "_Sig" + ".C"));
    
  		///-----------------------
  		/// Output
  		///-----------------------
  		outfile2 = new TFile(TString(outDir + plotBtagTriggerList2[i] + "_" + sigstrings2.at(j) + "_Sig" + ".root"),"RECREATE");
  		outfile2->cd();
  		canvas->Write();
  		outfile2->Close();
  		delete outfile2;
  	
  		canvas->Print(TString(psFile + ".ps"));
  		}
  		else {
  		plots[j]=nEvents1;
  		plotssig[j]=Sig1;
  		}
  	}
  	
  	//1D plotting
  	
  	if(!do2D) {

	logy = true;
	bool line = false;

  	canvas =
        PlotAll(plots,
       		nSig,  
       		sigstrings2,
          	"",
       		"",	
       		(const char*)(TString(outDir + plotBtagTriggerList2[i] + "_nEvents" + plotType)),
       		(const char*)(TString(plotBtagTriggerList2[i] + "_nEvents")),
   			outfile,
    		-0.5, 4.5,
   	   		0.0, 0.0,
       		drawNorm,
       		logx, logy,
       		drawStats,
   	   		drawExtra,
       		writeFile,
       		false,
   			false,
   			plotBtagTriggerList2[i],
      		false,
           	line  //line-only   
      	);
  		
  	canvas->Print(TString(outDir + plotBtagTriggerList2[i] + "_nEvents" + ".C"));
    
  	///-----------------------
  	/// Output
  	///-----------------------
  	TFile* outfile2 = new TFile(TString(outDir + plotBtagTriggerList2[i] + "_nEvents" + ".root"),"RECREATE");
  	outfile2->cd();
  	canvas->Write();
  	outfile2->Close();
  	delete outfile2;
  	
  	canvas->Print(TString(psFile + ".ps"));  	
  	
  	logy = false;
  	
  	canvas =
        PlotAll(plotssig,
       		nSig,  
       		sigstrings2,
          	"",
       		"",	
       		(const char*)(TString(outDir + plotBtagTriggerList2[i] + "_Sig" + plotType)),
       		(const char*)(TString(plotBtagTriggerList2[i] + "_Sig")),
   			outfile,
    		-0.5, 4.5,
   	   		0.0, 0.0,
       		drawNorm,
       		logx, logy,
       		drawStats,
   	   		drawExtra,
       		writeFile,
       		false,
   			false,
   			plotBtagTriggerList2[i],
      		false,
           	line  //line-only   
      	);
  		
  	canvas->Print(TString(outDir + plotBtagTriggerList2[i] + "_Sig" + ".C"));
    
  	///-----------------------
  	/// Output
  	///-----------------------
  	outfile2 = new TFile(TString(outDir + plotBtagTriggerList2[i] + "_Sig" + ".root"),"RECREATE");
  	outfile2->cd();
  	canvas->Write();
  	outfile2->Close();
  	delete outfile2;
  	
  	canvas->Print(TString(psFile + ".ps"));  	
  	
  	}
  }
  cout << "Finished Plotting Btag Trigger plots" << endl;
  
  /*
  ///-----------------------                      
  /// X-Profile Plots   
  ///-----------------------
  canvas->SetBottomMargin(0.15); //clear ratio space
  cout << "Plotting X-Profile plots" << endl;
  for (Int_t i=0; i<nXProfilePlots; i++) {
    
    //vector<TH1F*> plots;
    TH1F* plots[50];
    TH2F* plots2D[50];
    double bins[11] = {20,30,40,60,80,110,160,310,400,800};
    for (Int_t fileItr=0; fileItr < NOverlay; fileItr++) {
      TH2F *h2 = (TH2F*)((files.at(fileItr))->Get(TString(plotDir.at(fileItr) + prefix.at(fileItr) + plotXProfileList[i] + suffix.at(fileItr))));
      if (!h2) cout << "Did not get histogram: " << TString(plotDir.at(fileItr) + prefix.at(fileItr) + plotXProfileList[i] + suffix.at(fileItr)) << endl;
      TH1F *h1 = (TH1F*)h2->ProfileX(TString(plotXProfileList[i] + Form("_profX_%d",fileItr)));
      if (!h1) cout << "Did not get histogram projection: " << TString(plotDir.at(fileItr) + prefix.at(fileItr) + plotXProfileList[i] + suffix.at(fileItr)) << endl;
      h1->SetName(TString(plotXProfileList[i] + Form("_%d",fileItr)));
      h1->SetXTitle("Jet p_{T} (GeV)");
      if (plotXProfileList[i].Contains("NTrk")) h1->SetYTitle("Average number of matched tracks");
      if (plotXProfileList[i].Contains("DPhi")) h1->SetYTitle("Average minimum matched track #delta#phi");
      h1->GetXaxis()->Set(9,bins);
      //h1->GetXaxis()->SetMoreLogLabels(kTRUE);
      //h1->GetXaxis()->SetNoExponent(kTRUE);
      h1->GetXaxis()->SetRangeUser(20,150);
      //h1->GetXaxis()->SetBinLabel(0.5,"hi");
      //h1->GetXaxis()->CenterLabels(kFALSE);
      //h1->Scale(weights.at(fileItr));
      plots[fileItr] = h1;
      plots2D[fileItr] = h2;
    }
  
    bool drawNorm = kFALSE;
    bool logx = kFALSE;
    bool logy = kFALSE;
    bool doFit = kFALSE;
    bool drawStats = kFALSE;
    bool drawExtra = kTRUE;
    
    //if (plotYProjList[i] == "jet_NConstVsEta" || 
    //    plotYProjList[i] == "eEta"
     //  ) logy = true;
    //else logy = false;
    
    vector<TString> tags2;
  	tags2.push_back(tags.at(0));
  	tags2.push_back(tags.at(1));
  	if (plotXProfileList[i].Contains("VsPt_0")) tags2.push_back("anti-k_{t} topo-cluster jets R=0.6, "+TString(plots2D[0]->GetTitle()));
  	else if (plotXProfileList[i].Contains("VsPt_1")) tags2.push_back("anti-k_{t} topo-tower jets R=0.6, "+TString(plots2D[0]->GetTitle()));
    
    
    double ymax = 0;
    if (plotXProfileList[i].Contains("NTrk")) ymax = 22.0;
    if (plotXProfileList[i].Contains("DPhi")) ymax = 0.30;
    
    if (NOverlay > 1) {
      canvas =
          PlotAll(plots,
                  NOverlay,
                  tags2,
                  "",
                  "",
                  (const char*)(outDir + "overlay_XProf_" + plotXProfileList[i] + suffix.at(0) + plotType),
                  (const char*)("overlay_XProf_" + plotXProfileList[i]),
                  outfile,
                  0.0, 0.0,
                  0.0, ymax,
                  drawNorm,
                  logx, logy,
                  drawStats,
                  drawExtra,
                  writeFile,
                  dataMCCompare,
                  kFALSE,
                  ""
                 );
    	canvas->Print(TString(outDir + "overlay_XProf_" + plotXProfileList[i] + suffix.at(0) + ".C"));
    
  		///-----------------------
  		/// Output
  		///-----------------------
  		TFile *outfile2 = new TFile(TString(outDir + "overlay_XProf_" + plotXProfileList[i] + suffix.at(0) + ".root"),"RECREATE");
  		outfile2->cd();
  		canvas->Write();
  		outfile2->Close();
  		delete outfile2;
                 
      canvas->Print(TString(psFile + ".ps"));       
    }        
    else {
      Plot2DPlusProfile(plots2D[0], 
                        (const char*)(TString(TString(plots2D[0]->GetName()) + "_" + tags.at(0) + suffix.at(0) + plotType)), 
                        (const char*)(TString(TString(plots2D[0]->GetName()) + "_" + tags.at(0))),
                        outfile,
                        0.,0.,
                        "","",
                        doLogY,
                        doLogZ);
    }
  }
  cout << "Finished Plotting X-Profile plots" << endl;
  
  ///-----------------------                      
  /// 2D Plots   
  ///-----------------------
  cout << "Plotting 2D plots" << endl;
  for (Int_t i=0; i<n2DPlots; i++) {
    //vector<TH1F*> plots;
    TH2F* plots[50];
    double bins[11] = {20,30,40,60,80,110,160,310,400,800};
    double max = 0.0;
    double min = 0.0;
    for (Int_t fileItr=(NOverlay-1); fileItr > -1; fileItr--) {
      cout << "Reading fileItr = " << fileItr << endl;
      TH2F *h = (TH2F*)((files.at(fileItr))->Get(TString(plotDir.at(fileItr) + prefix.at(fileItr) + plot2DList[i] + suffix.at(fileItr))));
      if (h) cout << "Got histogram: " << TString(plotDir.at(fileItr) + prefix.at(fileItr) + plot2DList[i] + suffix.at(fileItr)) << endl;
      else cout << "Did not get histogram: " << TString(plotDir.at(fileItr) + prefix.at(fileItr) + plot2DList[i] + suffix.at(fileItr)) << endl;
      h->SetName(TString(plot2DList[i] + Form("_%d",fileItr)));
      //h->Scale(1./(float)h->GetEntries());
      if(fileItr==0) {
		h->Scale(plots[1]->GetEntries()/h->GetEntries());
      }
      h->GetXaxis()->Set(9,bins);
      //h->GetXaxis()->SetMoreLogLabels(kTRUE);
      //h->GetXaxis()->SetNoExponent(kTRUE);
      h->GetXaxis()->SetRangeUser(20,150);
      //h->Scale(weights.at(fileItr));
      //cout << "Set Name: " << TString(plot1DList[i] + Form("_%d",fileItr)) << endl;
      //plots.push_back(h);
      //if (plot1DList[i].Contains("Res_NTrk") || plot1DList[i].Contains("Res_EMFrac") || plot1DList[i].Contains("Res_SumTrkPt")) h->Rebin(3);
      //if (plot1DList[i].Contains("Inclusive_0_0_1")) h->Rebin(6);
      //if (plot1DList[i].Contains("Inclusive_0_0_2")) h->Rebin(6);
      //if(fileItr==1) {
      //	max = exp(1.3*log(h->GetBinContent(h->GetMaximumBin())));
      // 	min = exp(0.9*log(h->GetBinContent(h->GetMinimumBin())));
      // 	if(min<1.0) min = 1.0;
      //}
      plots[fileItr] = h;
    }
  
    bool drawNorm = kFALSE;
    bool logx = kFALSE;
    bool logy = kFALSE;
    bool doFit = kFALSE;
    bool drawStats = kFALSE;
    bool drawExtra = kTRUE;
    
    gStyle->SetOptTitle(1);
    
    for(unsigned int j = 0; j<NOverlay; j++) {
    
    	vector<TString> tags2;
    	tags2.clear();
    	vector<TString> labels;
    	labels.clear();
  		//tags2.push_back(tags.at(j));
  		if(j==0) labels.push_back(TString("MC"));
  		else labels.push_back(TString("Data"));
  		//tags2.push_back(tags.at(1));
  		if (plot2DList[i].Contains("VsPt_0")) tags2.push_back(tags.at(j)+", anti-k_{t} topo-cluster jets R=0.6, "+TString(plots[j]->GetTitle()));
  		else if (plot2DList[i].Contains("VsPt_1")) tags2.push_back(tags.at(j)+", anti-k_{t} topo-tower jets R=0.6, "+TString(plots[j]->GetTitle()));

  		//if (plot2DList[i].Contains("TrackPt_0")) tags2.push_back("anti-k_{t} topo-cluster jets R=0.6, "+TString(plots[0]->GetTitle()));
  		//else if (plot2DList[i].Contains("TrackPt_1")) tags2.push_back("anti-k_{t} topo-tower jets R=0.6, "+TString(plots[0]->GetTitle()));
    
    	canvas =
        Plot2DPlusProfile(plots[j],
                (const char*)(outDir + "overlay_" + plot2DList[i] + "_" + labels.at(0) + plotType),
                (const char*)("overlay_" + plot2DList[i] + "_" + labels.at(0)),
                outfile,
                0.0, 0.0,
                "Jet p_{T} (GeV)",
                "Minimum matched track #delta#phi",
                tags2.at(0),
				true,
				true,
				true
               );
               
    canvas->Print(TString(outDir + "overlay_" + plot2DList[i] + "_" + labels.at(0) + ".C"));
    
  	///-----------------------
  	/// Output
  	///-----------------------
  	TFile *outfile2 = new TFile(TString(outDir + "overlay_" + plot2DList[i] + "_" + labels.at(0) + ".root"),"RECREATE");
  	outfile2->cd();
  	canvas->Write();
  	outfile2->Close();
  	delete outfile2;
  	
  	canvas->Print(TString(psFile + ".ps"));
  	
  	}
  	
  	gStyle->SetOptTitle(0);
  }
  cout << "Finished Plotting 2D plots" << endl;
    */
  canvas->Print(TString(psFile + ".ps]"));       
  
}
