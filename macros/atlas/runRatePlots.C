void runRatePlots(TString signal="",TString OutputFileName = "", TString ytitle = "")
{
   ///-------------------------------------------------------------------------
   /// Compile everything
   ///-------------------------------------------------------------------------  
   gSystem->Load("libPhysics.so");
   //gSystem->CompileMacro ("style.cpp", "k");
   //gSystem->CompileMacro ("Util.cpp","k");
   //gSystem->CompileMacro ("../../..//RootUtils/trunk/AtlasStyle.C", "k");
   //gSystem->CompileMacro ("../../..//RootUtils/trunk/rootlogon.C", "k");
   gSystem->CompileMacro ("../../../RootUtils/trunk/Util.cpp", "k");
   //gSystem->CompileMacro ("rootlogonCompile.h", "k");
   gSystem->CompileMacro ("JetMetbTagAnalysisBase.cxx", "k");
   
   gROOT->LoadMacro("../../..//RootUtils/trunk/AtlasStyle.C");
   SetAtlasStyle();
   
   
   
   ///-------------------------------------------------------------------------
   /// Switch on or off analyses
   ///-------------------------------------------------------------------------
   
   bool do_rates               = true;   
   bool do_multijet_ref        = 1;
   bool do_jetX_ref            = 1;
   bool do_l2bmenu_ref         = 0;
   bool do_jetetsum_ref        = 0;
   bool do_l2btag_plots        = 0;
   bool do_jetetsum            = 0;
   bool do_jetetsum_scan       = 0;
   bool do_l2btag_scan         = 0;
   bool do_l1jetet_scan        = 0;
   bool do_l1jetetsum_scan     = 0;
   bool do_l1met_scan          = 1;

   bool do_compact             = 0;
   
   ///-------------------------------------------------------------------------
   /// Setup run
   ///-------------------------------------------------------------------------
   Long64_t EvtMax         = 1;
   Long64_t EvtCnt         = 1;
   Int_t    NFilesNeeded   = 1;
   bool     verbose        = false;
   bool multi = false;
  

   

   /// output
   TString outDir      = "plots/";
   TString plotType    = ".png";
   TString rootFile    = "EventRates_final.root";
   if (multi) rootFile    = "EventRates_final_multi.root";
   TString outfilename = outDir + rootFile;
   //TString dir         = "../topologies/jetmetbtag/files/trg004_080510/";
   //TString dir         = "../topologies/jetmetbtag/files/trg_100510/";
   //TString dir         = "../topologies/jetmetbtag/files/290410/";
   //TString dir         = "../topologies/jetmetbtag/files/010610_rates/";
   //TString dir         = "../topologies/jetmetbtag/files/100727_l2rate/";
   //TString dir         = "../topologies/jetmetbtag/files/100809_l2menu/";
   //TString dir         = "../topologies/jetmetbtag/files/100819_l2menu/";
   //TString dir         = "../topologies/jetmetbtag/files/100824_l2menu/";
   //TString dir         = "../topologies/jetmetbtag/files/100825_l2menu/";
   //TString dir         = "../topologies/jetmetbtag/files/100826_l2menu/";
   TString dir         = "../topologies/jetmetbtag/files/100923_l2menu/";
   
   TString tag_ttbar   = "final";
   
   /// Setup analysis
   JetMetbTagAnalysisBase *jetAlgs_ttbar = new JetMetbTagAnalysisBase(0,verbose);
   jetAlgs_ttbar->SetPlotTypeAndLumi(plotType,tag_ttbar);
   jetAlgs_ttbar->SetOutputDirectory(outDir);
   jetAlgs_ttbar->SetOutputRootFile(rootFile);
   
   jetAlgs_ttbar->SetTurnOffErrors(true);
  
   ///+++++++++++++++++++++++++++++++++++++++++++++
   /// Generic plots stuff
   ///+++++++++++++++++++++++++++++++++++++++++++++
   TLegendEntry *entry;
   TString plotNames[30];
   TString plotNamesLegend[30];
   TString fileNames[30];
   TString selection[30];
   TString legend[30];             
   
   Int_t NumberPlots = 0;
   Int_t NumberSelections = 0;
   
   TString baseName    = "l2rate";
   
   //susy0l4j2btfull
   TString baseSignalSelection = "susy0l4j2btfullsoft";
   //TString SignalSample = "py2bB400L100"; //"tt";
   //TString SignalSample = "py2bB400L100"; //"tt";
   TString SignalSample = "py4bG400L100"; //"tt";
   //TString SignalSample = "su4"; //"tt";
   //TString baseSignalSelection = "ljets0l2bt";
   //TString SignalSample = "tt";

   if(signal!="") SignalSample = signal;

   TString RateSample = "j2";
   //TString SampleType = ".trg004";
   TString SampleType = ".exttrgmc106";
   
      
   if( do_rates) {

      
      //if(SignalSample.Contains("su4")) do_jetetsum_ref = 0;
      
      


      Int_t markerSize = 1.7;
      Int_t markerSizeCompact = markerSize*1.0;
      Int_t specificSize = 2.0;
     
      Float_t lumi = TMath::Power(10,31) * TMath::Power(10,-36); //[pb s^-1]
      Float_t xs = 41194700.0; // J2 [pb]
      //Float_t xs = 2328.56; // J5 [pb]
      Float_t rateConv = lumi * xs; //[s^-1]
      cout << "rateConv="<<rateConv<<endl;
      //Float_t rateConv = 0.51952;
      bool rates = true;
      Float_t scaleSignal[2] = {1.0,0.0};
      Float_t scaleRate[2] = {1.0,0.0};
      Width_t width = 1;

      ///-------------------------------------------
      TCanvas *canv_exist_bTag = new TCanvas("canv_exist_bTag","canv_exist_bTag",650,600);
      canv_exist_bTag->SetFillColor(0);
      canv_exist_bTag->cd();
      //canv_exist_bTag->SetLogy();
      canv_exist_bTag->SetLogx();
      canv_exist_bTag->SetGridx(kTRUE);
      canv_exist_bTag->SetGridy(kTRUE);
  
      canv_exist_bTag->cd();
  
      TH2F* frame_exist_bTag = new TH2F("frame_exist_bTag","",2,0.001,100.0,2,0.7,1.0);
//       if(SignalSample.Contains("su4"))     frame_exist_bTag->SetYTitle("Efficiency for SU4 events");
//       else if(SignalSample.Contains("tt")) frame_exist_bTag->SetYTitle("Efficiency for t#bar{t} events");
      
      frame_exist_bTag->SetYTitle("Efficiency");
      //Ugly, I didnt get it to work with the the shell script!!
      if(ytitle=="GbL")  frame_exist_bTag->SetYTitle("Efficiency #tilde{g}#rightarrowb#bar{b}+LSP,#DeltaM_{#tilde{g},LSP}=300GeV");
      if(ytitle=="GbS")  frame_exist_bTag->SetYTitle("Efficiency #tilde{g}#rightarrowb#bar{b}+LSP,#DeltaM_{#tilde{g},LSP}=100GeV");
      frame_exist_bTag->SetXTitle("Trigger rate at 10^{31} cm^{-2} s^{-1} (Hz)");
      frame_exist_bTag->GetXaxis()->SetTitleColor(1);
      frame_exist_bTag->SetStats(0);
      frame_exist_bTag->GetYaxis()->SetTitleOffset(1.3);
      frame_exist_bTag->GetYaxis()->SetNoExponent(kTRUE);
      frame_exist_bTag->GetYaxis()->SetMoreLogLabels(kTRUE);
      frame_exist_bTag->GetXaxis()->SetTitleOffset(1.13);
      frame_exist_bTag->Draw("");
      //TLegend *leg_exist_bTag = new TLegend(0.4630673,0.1607774,0.9921753,0.4975265);
      //TLegend *leg_exist_bTag = new TLegend(0.4130673,0.1607774,0.9421753,0.4975265);
      TLegend *leg_exist_bTag = new TLegend(0.4130673,0.1607774,0.9421753,0.65975265);
      leg_exist_bTag->SetFillStyle(0);
      leg_exist_bTag->SetBorderSize(0);
     
      canv_exist_bTag->cd();
      ///-------------------------------------------
     
     



      if(do_jetetsum) {
         
         //------------------------------
         //Plot jet ET sum

         TString histo = baseName + "_l1jetetsum";
         TString histo_signal = baseName + baseSignalSelection + "_l1jetetsum";
         
         //get scale factors
         
         scaleSignal[0] = 1.;scaleSignal[1] = 0.;
         scaleRate[0]   = 1.;scaleRate[1]   = 0.;
         TGraph *rate_eff_jetetsum = jetAlgs_ttbar->RatePerformance(dir + RateSample + SampleType + ".root",
                                                                    dir + SignalSample + SampleType + ".root",
                                                                    histo,histo_signal,
                                                                    rates,rateConv,scaleSignal,scaleRate,
                                                                    -1.,9999.);
         rate_eff_jetetsum->SetName(TString(histo + "_rate"));
         rate_eff_jetetsum->SetLineColor(1); rate_eff_jetetsum->SetLineWidth(width); rate_eff_jetetsum->SetMarkerColor(1); rate_eff_jetetsum->SetMarkerStyle(20); rate_eff_jetetsum->SetMarkerSize(markerSize); rate_eff_jetetsum->SetLineStyle(1);//line_MET); 
         
         canv_exist_bTag->cd();
         
         rate_eff_jetetsum->Draw("lsame");
         
         TString s = "L1_JE t#bar{t} xs";
         entry = leg_exist_bTag->AddEntry(rate_eff_jetetsum,s.Data(),"l");
         
         //compare with susy cuts 
         histo = baseName + "_l1jetetsum";
         histo_signal = baseName + "susy0l4jfullsoft_l1jetetsum";
         TGraph *rate_eff_jetetsum_susysel = jetAlgs_ttbar->RatePerformance(dir + RateSample + SampleType + ".root",
                                                                            dir + SignalSample + SampleType + ".root",
                                                                            histo,histo_signal,
                                                                            rates,rateConv,scaleSignal,scaleRate,
                                                                            -1.0,9999.);
         rate_eff_jetetsum_susysel->SetName(TString(histo + "_rate"));
         rate_eff_jetetsum_susysel->SetLineColor(2); rate_eff_jetetsum_susysel->SetLineWidth(width); rate_eff_jetetsum_susysel->SetMarkerColor(1); rate_eff_jetetsum_susysel->SetMarkerStyle(20); rate_eff_jetetsum_susysel->SetMarkerSize(markerSize); rate_eff_jetetsum_susysel->SetLineStyle(1);//line_MET); 
         
         canv_exist_bTag->cd();
         
         rate_eff_jetetsum_susysel->Draw("lsame");
         
         s = "L1_JE susy 0l 4jets";
         entry = leg_exist_bTag->AddEntry(rate_eff_jetetsum_susysel,s.Data(),"l");
         
         //Plot specific points on the L1 jet et sum
         
         Float_t jetetsumcuts[6] = {60,70,90,100,120,220};
         
         for(int iii=0; iii!=6;++iii) {
            
            TGraph *rate_eff_jetetsum_susysel_tmp = jetAlgs_ttbar->RatePerformance(dir + RateSample + SampleType + ".root",
                                                                                   dir + SignalSample + SampleType + ".root",
                                                                                   histo,histo_signal,
                                                                                   rates,rateConv,scaleSignal,scaleRate,
                                                                                   -1.0,9999.,true,jetetsumcuts[iii]);
            rate_eff_jetetsum_susysel_tmp->SetName(TString(histo + "_rate"));
            rate_eff_jetetsum_susysel_tmp->SetMarkerColor(2); rate_eff_jetetsum_susysel_tmp->SetMarkerStyle(20+iii); rate_eff_jetetsum_susysel_tmp->SetMarkerSize(markerSize); 
            
            canv_exist_bTag->cd();
            
            rate_eff_jetetsum_susysel_tmp->Draw("p,same");
            
            double xtmp,ytmp;rate_eff_jetetsum_susysel_tmp->GetPoint(0,xtmp,ytmp);
            s.Form("L1_JE%.0f (%.2f%/%.0f)",jetetsumcuts[iii],ytmp*100.0,xtmp);
            entry = leg_exist_bTag->AddEntry(rate_eff_jetetsum_susysel_tmp,s.Data(),"p");
            
            canv_exist_bTag->Update();
         }

         ///-------------------------------------------
         
      }


      

      if(do_multijet_ref) {
         
         //------------------------------
         //Plot multi jet reference triggers
         
         int nothersel=0;
         TString otherSelection[30];           
         //L1
         otherSelection[nothersel++] = "L1_3J10";
         otherSelection[nothersel++] = "L1_1J30L1_3J10";
         otherSelection[nothersel++] = "L1_3J15";
         //otherSelection[nothersel++] = "L1_1J30";
         //otherSelection[nothersel++] = "L1_1J55";
         //L2
         //otherSelection[nothersel++] = "L1_3J15L1_1J30L2_3j30L2_1j60";
         //otherSelection[nothersel++] = "L1_1J30L1_3J10L2_1j80L2_3j40";
         //otherSelection[nothersel++] = "L1_3J15L2_3j30";

         //otherSelection[3] = "L1_1J95_L2_1j170";  --> no events?
         //L1_3J15
         //L1_3J10
         //L1_1J55
         //otherSelection[nothersel++] = "L1_1J55L2_1j120";
         //L1_4J10
         //L1_4J5
         //L1_3J5
         //L1_4J15
         //otherSelection[nothersel++] = "L1_4J15";
         //otherSelection[nothersel++] = "L1_4J10";
         //otherSelection[nothersel++] = "L1_4J5";
         //otherSelection[nothersel++] = "L1_4J15L2_4j30";
         //otherSelection[nothersel++] = "L1_4J10L1_3J20L2_4j20L2_3j40L2_1j60";
         //L1_4J18L1_J23L1_2J35L1_1J42
         //L1_4J18L1_3J23L1_2J35L1_1J42
         //L1_1J30L1_3J15
         //L1_4J23
         //otherSelection[8] = "L1_4J23L2_4j50";
         //L1_1J95
         //otherSelection[nothersel++] = "L1_1J95L2_1j170";
         //L1_3J20
         //L1_1J40L1_3J20
         //otherSelection[nothersel++] = "L1_3J20L2_3j60";
         //otherSelection[nothersel++] = "L1_1J40L1_3J20L2_3j40L2_1j80";
         //L1_4J20
         //otherSelection[nothersel++] = "L1_4J20L2_4j40";
         //L1_1J130
         //otherSelection[11] = "L1_1J130L2_1j260";
         //L1_3J40
         //otherSelection[11] = "L1_3J40L2_3j80";
         
         
         
         for(int iother=0;iother!=nothersel;++iother) {
            
            TString histo = baseName + otherSelection[iother] + "_nj";
            TString histo_signal = baseName + otherSelection[iother] + baseSignalSelection+ "_nj";
            
            scaleSignal[0] = 1.;scaleSignal[1] = 0.;
            scaleRate[0]   = 1.;scaleRate[1]   = 0.;
            TString signalFileName = dir + SignalSample + SampleType + ".root";
            cout << "Signal filename: " << dir << SignalSample << SampleType << " and add root to this becomes: " << signalFileName<<endl;            
            jetAlgs_ttbar->GetScaleFactorFromRatio(scaleSignal,
                                                   signalFileName,
                                                   signalFileName,
                                                   baseName + otherSelection[iother] + baseSignalSelection + "_nj",
                                                   baseName + baseSignalSelection + "_nj");
            cout << "Extracted scaleSignal = " << scaleSignal[0] << "+-" << scaleSignal[1] << endl;
            
            TString rateFileName = dir + RateSample + SampleType + ".root";
            cout << "Rate filename: " << dir << RateSample << SampleType << " and add root to this becomes: " << rateFileName<<endl;
            
            jetAlgs_ttbar->GetScaleFactorFromRatio(scaleRate,
                                                   rateFileName,
                                                   rateFileName,
                                                   baseName + otherSelection[iother] + "_nj",
                                                   baseName + "_nj");            
            cout << "Extracted scaleRate = " << scaleRate[0] << "+-" << scaleRate[1] << endl;
            if(scaleRate[0]<0.) {
               cout << "Error! scaleRate is " << scaleRate[0] << endl; exit(-1);
            }
            
            TGraph *rate_eff_xe = jetAlgs_ttbar->RatePerformance(dir + RateSample + SampleType + ".root",
                                                                 dir + SignalSample + SampleType + ".root",
                                                                 histo,histo_signal,
                                                                 rates,rateConv,scaleSignal,scaleRate,
                                                                 -9999.,99999.,true,-9999.);
            rate_eff_xe->SetName(TString::Format("%s_ratemultijetref_%i",histo.Data(),iother).Data());
            Color_t color = kRed; //iother + 1;
            rate_eff_xe->SetLineColor(color); 
            rate_eff_xe->SetMarkerColor(color); 
            
            if(do_compact) {
               rate_eff_xe->SetMarkerStyle(20); 
               rate_eff_xe->SetMarkerSize(markerSizeCompact); 
            } else {
               rate_eff_xe->SetMarkerStyle(20+iother); 
               rate_eff_xe->SetMarkerSize(markerSize*1.7); 
            }
            canv_exist_bTag->cd();
            
            rate_eff_xe->Draw("p,same");
            TString s;  
            if(!do_compact) {
               s.Form("%s",otherSelection[iother].Data());
               entry = leg_exist_bTag->AddEntry(rate_eff_xe,s.Data(),"p");
            }
            canv_exist_bTag->Update();
         } //iop
         
      }
      ///-------------------------------------------
      





      if(do_jetX_ref) {
         
         //------------------------------
         //Plot jet+X reference triggers
         TString otherSelection[30];           
         
         int nothersel=0;
         //otherSelection[nothersel++] = "L1_XE10";
         //otherSelection[nothersel++] = "L1_XE15";
         //otherSelection[nothersel++] = "L1_XE30";
         //otherSelection[nothersel++] = "L1_XE15L2_xe20";
         //otherSelection[nothersel++] = "L1_XE30L2_xe35";
         //otherSelection[nothersel++] = "L1_XE40L2_xe45";
         //otherSelection[nothersel++] = "L1_XE50L2_xe60";
         //otherSelection[nothersel++] = "L1_XE50L2_xe50EF_xe70";
         //otherSelection[nothersel++] = "L1_XE30L2_xe50EF_xe50";
         otherSelection[nothersel++] = "L1_1J30L1_XE15";
         otherSelection[nothersel++] = "L1_2J15L1_XE15";
         otherSelection[nothersel++] = "L1_2J15L1_XE30";
         //otherSelection[nothersel++] = "L2_1j80L2_xe30";
         //otherSelection[nothersel++] = "L1_1J30L1_XE30L2_1j60";
         //otherSelection[nothersel++] = "L1_1J30L1_XE30L2_xe30";
         //otherSelection[nothersel++] = "L2_2j40L2_xe30";
         otherSelection[nothersel++] = "L1_2J15L1_XE30L2_2j30";
         //otherSelection[nothersel++] = "EF_2j30EF_xe35L2_2j30L2_xe30L1_2J15L1_XE30";
         
         for(int iother=0;iother!=nothersel;++iother) {
            TString histo = baseName + otherSelection[iother] + "_nj";
            TString histo_signal = baseName + otherSelection[iother] + baseSignalSelection+ "_nj";
            
            scaleSignal[0] = 1.;scaleSignal[1] = 0.;
            scaleRate[0]   = 1.;scaleRate[1]   = 0.;
            jetAlgs_ttbar->GetScaleFactorFromRatio(scaleSignal,
                                                   dir + SignalSample + SampleType + ".root",
                                                   dir + SignalSample + SampleType + ".root",
                                                   baseName + otherSelection[iother] + baseSignalSelection + "_nj",
                                                   baseName + baseSignalSelection + "_nj");
            cout << "Extracted scaleSignal = " << scaleSignal[0] << "+-" << scaleSignal[1] << endl;
            
            jetAlgs_ttbar->GetScaleFactorFromRatio(scaleRate,
                                                   dir + RateSample + SampleType + ".root",
                                                   dir + RateSample + SampleType + ".root",
                                                   baseName + otherSelection[iother] + "_nj",
                                                   baseName + "_nj");            
            cout << "Extracted scaleRate = " << scaleRate[0] << "+-" << scaleRate[1] << endl;
            if(scaleRate[0]<0.) {
               cout << "Error! scaleRate is " << scaleRate[0] << endl; exit(-1);
            }
            
            TGraph *rate_eff_xe = jetAlgs_ttbar->RatePerformance(dir + RateSample + SampleType + ".root",
                                                                 dir + SignalSample + SampleType + ".root",
                                                                 histo,histo_signal,
                                                                 rates,rateConv,scaleSignal,scaleRate,
                                                                 -9999.,9999.,true,-9999.);
            rate_eff_xe->SetName(TString::Format("%s_ratejetxref_%i",histo.Data(),iother).Data());
            Color_t color = kBlue; //iother + 1;
            rate_eff_xe->SetLineColor(color); 
            rate_eff_xe->SetMarkerColor(color); 
            if(do_compact) {
               rate_eff_xe->SetMarkerStyle(20); 
               rate_eff_xe->SetMarkerSize(markerSizeCompact); 
            } else {
               rate_eff_xe->SetMarkerStyle(20+iother); 
               rate_eff_xe->SetMarkerSize(markerSize*1.7); 
            }
            
            canv_exist_bTag->cd();
            
            rate_eff_xe->Draw("p,same");
            TString s;
            if(!do_compact) {
               s.Form("%s",otherSelection[iother].Data());
               entry = leg_exist_bTag->AddEntry(rate_eff_xe,s.Data(),"p");
            }
            
            canv_exist_bTag->Update();
         } //iop
         
      }
      ///-------------------------------------------
      

      
      
      if(do_l2bmenu_ref) {
         
         //------------------------------
         //Plot jet+X reference triggers
         
         const int nothersel=0;
         TString otherSelection[30];           
         otherSelection[nothersel++] = "L1_3J10";
         otherSelection[nothersel++] = "L1_4J10";
         //otherSelection[1] = "L1_3J20";
         otherSelection[nothersel++] = "L1_3J15";
         //otherSelection[3] = "L1_4J20";
         //otherSelection[4] = "L1_1J30L1_3J10";
         //otherSelection[4] = "L1_1J30L1_3J15";
         //otherSelection[5] = "L1_1J40L1_3J15";
         otherSelection[nothersel++] = "L1_1J30L1_3J10L2_2bD";
         otherSelection[nothersel++] = "L1_3J15L2_2bD";
         //otherSelection[2] = "L1_3J15L1_2J40L2_2bD";
         otherSelection[nothersel++] = "L1_4J15L2_2bD";
         otherSelection[nothersel++] = "L1_4J10L2_3bD";
         //otherSelection[nothersel++] = "L1_4J15L2_3bD";
         
         for(int iother=0;iother!=nothersel;++iother) {
            TString histo        = baseName + otherSelection[iother] + "_nj";
            TString histo_signal = baseName + otherSelection[iother] + baseSignalSelection+ "_nj";
            
            scaleSignal[0] = 1.;scaleSignal[1] = 0.;
            scaleRate[0]   = 1.;scaleRate[1]   = 0.;
            jetAlgs_ttbar->GetScaleFactorFromRatio(scaleSignal,
                                                   dir + SignalSample + SampleType + ".root",
                                                   dir + SignalSample + SampleType + ".root",
                                                   baseName + otherSelection[iother] + baseSignalSelection + "_nj",
                                                   baseName + baseSignalSelection + "_nj");
            cout << "scaleSignal = " << scaleSignal[0] << "+-" << scaleSignal[1] << endl;
            
            jetAlgs_ttbar->GetScaleFactorFromRatio(scaleRate,
                                                   dir + RateSample + SampleType + ".root",
                                                   dir + RateSample + SampleType + ".root",
                                                   baseName + otherSelection[iother] + "_nj",
                                                   baseName + "_nj");
            
            cout << "scaleRate = " << scaleRate[0] << "+-" << scaleRate[1] << endl;
            if(scaleRate[0]<0.) {
               cout << "Error! scaleRate is " << scaleRate[0] << endl; exit(-1);
            }
            
            
            TGraph *rate_eff_xe = jetAlgs_ttbar->RatePerformance(dir + RateSample + SampleType + ".root",
                                                                 dir + SignalSample + SampleType + ".root",
                                                                 histo,histo_signal,
                                                                 rates,rateConv,scaleSignal,scaleRate,
                                                                 -9999.,9999.,true,-9999.);
            rate_eff_xe->SetName(TString::Format("%s_ratel2btagmenuref_%i",histo.Data(),iother).Data());
            Color_t color = kGreen; //iother + 1;
            rate_eff_xe->SetLineColor(color); 
            rate_eff_xe->SetMarkerColor(color); 
            if(do_compact) {
               rate_eff_xe->SetMarkerStyle(20); 
               rate_eff_xe->SetMarkerSize(markerSizeCompact); 
            } else {
               rate_eff_xe->SetMarkerStyle(20+iother); 
               rate_eff_xe->SetMarkerSize(markerSize*1.7); 
            }
            
            canv_exist_bTag->cd();
            
            rate_eff_xe->Draw("p,same");
            TString s;
            if(!do_compact) {
               s.Form("%s",otherSelection[iother].Data());
               entry = leg_exist_bTag->AddEntry(rate_eff_xe,s.Data(),"p");
            }
            
            canv_exist_bTag->Update();
         } //iop
         
      }
      ///-------------------------------------------



      if(do_jetetsum_ref) {
         
         //------------------------------
         //Plot jet et sum reference triggers
         TString otherSelection[30];           
         int nothersel=0;
         //otherSelection[nothersel++] = "L1_JE60";
         otherSelection[nothersel++] = "L1_JE100";
         otherSelection[nothersel++] = "L1_JE140";
         otherSelection[nothersel++] = "L1_JE200";
         //otherSelection[nothersel++] = "L1_JE60L2_je135";
         //otherSelection[nothersel++] = "L1_JE100L2_je195";
         //otherSelection[nothersel++] = "L1_JE140L2_je220";
         //otherSelection[7] = "L1_JE200L2_je350";
	 
         for(int iother=0;iother!=nothersel;++iother) {
            TString histo        = baseName + otherSelection[iother] + "_nj";
            TString histo_signal = baseName + otherSelection[iother] + baseSignalSelection+ "_nj";
            
            scaleSignal[0] = 1.;scaleSignal[1] = 0.;
            scaleRate[0]   = 1.;scaleRate[1]   = 0.;
            jetAlgs_ttbar->GetScaleFactorFromRatio(scaleSignal,
                                                   dir + SignalSample + SampleType + ".root",
                                                   dir + SignalSample + SampleType + ".root",
                                                   baseName + otherSelection[iother] + baseSignalSelection + "_nj",
                                                   baseName + baseSignalSelection + "_nj");
            cout << "scaleSignal = " << scaleSignal[0] << "+-" << scaleSignal[1] << endl;
            
            jetAlgs_ttbar->GetScaleFactorFromRatio(scaleRate,
                                                   dir + RateSample + SampleType + ".root",
                                                   dir + RateSample + SampleType + ".root",
                                                   baseName + otherSelection[iother] + "_nj",
                                                   baseName + "_nj");            
            cout << "scaleRate = " << scaleRate[0] << "+-" << scaleRate[1] << endl;
            if(scaleRate[0]<0.) {
               cout << "Error! scaleRate is " << scaleRate[0] << endl; exit(-1);
            }

            
            TGraph *rate_eff_xe = jetAlgs_ttbar->RatePerformance(dir + RateSample + SampleType + ".root",
                                                                 dir + SignalSample + SampleType + ".root",
                                                                 histo,histo_signal,
                                                                 rates,rateConv,scaleSignal,scaleRate,
                                                                 -9999.,9999.,true,-9999.);
            rate_eff_xe->SetName(TString::Format("%s_ratejetetsummenuref_%i",histo.Data(),iother).Data());
            Color_t color = kMagenta; //iother + 1;
            rate_eff_xe->SetLineColor(color); 
            rate_eff_xe->SetMarkerColor(color); 
            if(do_compact) {
               rate_eff_xe->SetMarkerStyle(20); 
               rate_eff_xe->SetMarkerSize(markerSizeCompact); 
            } else {
               rate_eff_xe->SetMarkerStyle(20+iother); 
               rate_eff_xe->SetMarkerSize(markerSize*1.7); 
            }
            
            canv_exist_bTag->cd();
            
            rate_eff_xe->Draw("p,same");
            TString s;
            if(!do_compact) {
               s.Form("%s",otherSelection[iother].Data());
               entry = leg_exist_bTag->AddEntry(rate_eff_xe,s.Data(),"p");
            }
            
            canv_exist_bTag->Update();
         } //iop
         
      }
      ///-------------------------------------------
      
      
      
      if(do_l2btag_scan) {
         ///--------------------------------------
         /// Plot optimization of L2 btag
         
         ///-------------------------------------------
         NumberPlots = 2;
         //plotNames[2] = "l2J153ip3d"; plotNamesLegend[2] = "L2_3b (J15) IP3D";
         plotNames[1] = "l2J102ip3d"; plotNamesLegend[1] = "L2_2b (J10) IP3D";
         plotNames[0] = "l2J101ip3d"; plotNamesLegend[0] = "L2_1b (J10) IP3D";
         //plotNames[1] = "l21ip3d";    plotNamesLegend[1] = "L2_1b (any) IP3D";
         //plotNames[2] = "l2J151ip3d"; plotNamesLegend[2] = "L2_1b (J15) IP3D";
         //plotNames[2] = "l23ip3d"; plotNamesLegend[2] = "L2_3b IP3D";
         //plotNames[2] = "l22ip3d"; plotNamesLegend[2] = "L2_2bASYMM IP3D";
         NumberSelections = 1;
         //selection[0] = "L1_JE60"; 
         //selection[1] = "L1_JE100"; 
         //selection[2] = "L1_JE140"; 
         //selection[1] = "L1_3J15L2_1bD"; 
         selection[0] = "L1_3J15"; 
         selection[0] = "L1_4J10"; 
         //selection[1] = "L1_3J20"; 
         //selection[0] = "L1_3J10L1_1J40"; 
         //selection[1] = "L1_3J10L1_1J40L2_1bD"; 
         //selection[1] = "L1_3J15L2_2bD";
         
         
         int counter =0;
         bool ok = true;
         for(int iselection = 0; iselection != NumberSelections; ++iselection) {
            
            // Loop over all the plots!
            
            
            for(int iplot=0;iplot!=NumberPlots;iplot++) {
               
               ok = true;
               
               //if(iplot==0 && iselection==1) ok=false;
               //if(iplot==1 && iselection==1) ok=false;            
               
               if(ok) {
                  cout << " Selected plot "<<plotNames[iplot] << " for selection " << selection[iselection] << endl;
                  
                  counter++;
                  TString histo = baseName + selection[iselection] + "_" + plotNames[iplot];
                  TString histo_signal = baseName + selection[iselection] + baseSignalSelection+ "_" + plotNames[iplot];
                  //Since the selection may already include a L1 or other selection 
                  //I should include that efficiency in my rate calculation        

                  scaleSignal[0] = 1.;scaleSignal[1] = 0.;
                  scaleRate[0]   = 1.;scaleRate[1]   = 0.;
                  
                  //---- Signal scale
                  // This takes into account that I want the efficiency w.r.t to the 
                  // base selection without trigger requirement so if I need to take 
                  // into account e.g. the L1 item before the cut on the L2 variable.
                  jetAlgs_ttbar->GetScaleFactorFromRatio(scaleSignal,dir + SignalSample + SampleType + ".root",
                                                         dir + SignalSample + SampleType + ".root",
                                                         baseName + selection[iselection] + baseSignalSelection + "_nj",
                                                         baseName + baseSignalSelection + "_nj");
                  cout << "scaleSignal = " << scaleSignal[0] << endl;
                  
                  //---- Background scale 
                  // This takes into account the efficiency for the rate to come to this selection
                  // note that the denominator is not the same as the numerator in this case 
                  // as the numerator includes a selection on having at least 2 L2Bjets (no cut though) 
                  // in the event
                  jetAlgs_ttbar->GetScaleFactorFromRatio(scaleRate,
                                                         dir + RateSample + SampleType + ".root",
                                                         dir + RateSample + SampleType + ".root",
                                                         baseName + selection[iselection] + "_nj",
                                                         baseName + "_nj");
                  
                  cout << "scaleRate = " << scaleRate[0] << endl;
                  if(scaleRate[0]<0.) {
                     cout << "Error! scaleRate is " << scaleRate[0] << endl; exit(-1);
                  }
                  
                  TGraph *rate_eff_bTag = jetAlgs_ttbar->RatePerformance(dir + RateSample + SampleType + ".root",
                                                                         dir + SignalSample + SampleType + ".root",
                                                                         histo,histo_signal,
                                                                         rates,rateConv,scaleSignal,scaleRate,
                                                                         -9999.,9999.);
                  rate_eff_bTag->SetName(TString(histo + "_rate"));
                  rate_eff_bTag->SetLineColor(counter); 
                  rate_eff_bTag->SetLineWidth(width); 
                  rate_eff_bTag->SetMarkerColor(counter); 
                  rate_eff_bTag->SetMarkerStyle(20); 
                  rate_eff_bTag->SetMarkerSize(markerSize); 
                  rate_eff_bTag->SetLineStyle(1);//line_MET); 
               
                  canv_exist_bTag->cd();
               
                  rate_eff_bTag->Draw("lsame");
               
                  TString s = selection[iselection] + ", " + plotNames[iplot];
                  //entry = leg_exist_bTag->AddEntry(rate_eff_bTag,s.Data(),"l");


               
               
                  //------------------------------
                  //Plot individual working points
               
                  Float_t eff[3]  = {0.7,0.8,0.85};
                  Float_t cuts[3] = {0.61,0.46,0.33};
               
                  for(int iop=0; iop!=3;++iop) {
                     
                     TGraph *rate_eff_bTag_Op = jetAlgs_ttbar->RatePerformance(dir + RateSample + SampleType + ".root",
                                                                               dir + SignalSample + SampleType + ".root",
                                                                               histo,histo_signal,
                                                                               rates,rateConv,scaleSignal,scaleRate,
                                                                               -9999.,9999.,true,cuts[iop]);
                     rate_eff_bTag_Op->SetName(TString::Format("%s_rate%i",histo.Data(),iop).Data());
                     rate_eff_bTag_Op->SetLineColor(kBlack); 
                     rate_eff_bTag_Op->SetMarkerColor(counter); 
                     rate_eff_bTag_Op->SetMarkerStyle(24+iop); 
                     rate_eff_bTag_Op->SetMarkerSize(markerSize*1.7); 
                     
                     canv_exist_bTag->cd();
                  
                     rate_eff_bTag_Op->Draw("p,same");
                  
                     s.Form("%s %s (%.2f)",selection[iselection].Data(),plotNamesLegend[iplot].Data(),cuts[iop]);
                     //s.Form("%s %s (%.2f)",selection[iselection].Data(),plotNamesLegend[iplot].Data(),eff[iop]);
                     entry = leg_exist_bTag->AddEntry(rate_eff_bTag_Op,s.Data(),"p");
                  
                     canv_exist_bTag->Update();
                  } //iop
               
               
               
               
               
               
                  //delete canv_exist_bTag;
                  //delete frame_exist_bTag;
                  //delete rate_eff_bTag;
                  //delete leg_exist_bTag;
               
               }
            }
         }
      } 
      //--------------------------------------



      
      if(do_l1jetet_scan) {
         ///--------------------------------------
         /// Plot optimization of L1 Jet input the L2 btag optimizations
         
         ///-------------------------------------------
         NumberPlots = 0;
         plotNames[NumberPlots++] = "l2jJ300pt"; plotNamesLegend[NumberPlots-1] = "L2_1jX";
         plotNames[NumberPlots++] = "l2jJ151pt"; plotNamesLegend[NumberPlots-1] = "L2_2jX";
//         plotNames[NumberPlots++] = "l10jpt"; plotNamesLegend[0] = "L1_1JX";
//         plotNames[NumberPlots++] = "l11jpt"; plotNamesLegend[1] = "L1_2JX";
//          plotNames[2] = "l1j2pt"; plotNamesLegend[2] = "L1_3JX";
//          plotNames[3] = "l1j3pt"; plotNamesLegend[3] = "L1_4JX";
         NumberSelections = 0;
         //selection[0] = "L1_3J10L2_2bD"; 
         //selection[1] = "L1_3J10L2_1bD"; 
         //selection[NumberSelections++] = "L1_XE15"; 
         //selection[NumberSelections++] = "L1_XE30"; 
         selection[NumberSelections++] = "L1_1J30L1_XE30L2_xe30"; 
         selection[NumberSelections++] = "L1_2J15L1_XE30L2_xe30"; 
         selection[NumberSelections++] = "EF_2j30EF_xe35L2_2j30L2_xe30L1_2J15L1_XE30";
         //selection[0] = "XE25L2_2bD"; 
         //selection[1] = "L2_1bD"; 
         //selection[0] = "L2_2bD"; 
         //selection[1] = "L2_1bD"; 
         //selection[1] = "L1_3J10L1_1J40L2_1bD"; 
         //selection[1] = "L1_3J15L2_2bD";
         
         
         int counter =0;
         bool ok = true;
         for(int iselection = 0; iselection != NumberSelections; ++iselection) {
            
            // Loop over all the plots!
            
            
            for(int iplot=0;iplot!=NumberPlots;iplot++) {

               ok = false;
               
               if(iplot==0 && iselection==0) ok=true;
               if(iplot==1 && iselection==1) ok=true;            
               
               if(ok) {
                  //cout << " Selected plot "<<plotNames[iplot] << " for selection " << selection[iselection] << endl;
                  
                  counter++;
                  TString histo = baseName + selection[iselection] + "_" + plotNames[iplot];
                  TString histo_signal = baseName + selection[iselection] + baseSignalSelection+ "_" + plotNames[iplot];
                  //Since the selection may already include a L1 or other selection 
                  //I should include that efficiency in my rate calculation        
               
                  scaleSignal[0] = 1.;scaleSignal[1] = 0.;
                  scaleRate[0]   = 1.;scaleRate[1]   = 0.;

                  //---- Signal scale
                  // This takes into account that I want the efficiency w.r.t to the 
                  // base selection without trigger requirement so if I need to take 
                  // into account e.g. the L1 item before the cut on the L2 variable.
                  jetAlgs_ttbar->GetScaleFactorFromRatio(scaleSignal,
                                                         dir + SignalSample + SampleType + ".root",
                                                         dir + SignalSample + SampleType + ".root",
                                                         baseName + selection[iselection] + baseSignalSelection + "_nj",
                                                         baseName + baseSignalSelection + "_nj");
                  cout << "scaleSignal = " << scaleSignal[0] << endl;
                  
                  //---- Background scale 
                  // This takes into account the efficiency for the rate to come to this selection
                  // note that the denominator is not the same as the numerator in this case 
                  // as the numerator includes a selection on having at least 2 L2Bjets (no cut though) 
                  // in the event
                  jetAlgs_ttbar->GetScaleFactorFromRatio(scaleRate,
                                                         dir + RateSample + SampleType + ".root",
                                                         dir + RateSample + SampleType + ".root",
                                                         baseName + selection[iselection] + "_nj",
                                                         baseName + "_nj");
                  
                  cout << "scaleRate = " << scaleRate[0] << endl;
                  if(scaleRate[0]<0.) {
                     cout << "Error! scaleRate is " << scaleRate[0] << endl; exit(-1);
                  }
                  
                  TGraph *rate_eff_bTag = jetAlgs_ttbar->RatePerformance(dir + RateSample + SampleType + ".root",
                                                                         dir + SignalSample + SampleType + ".root",
                                                                         histo,histo_signal,
                                                                         rates,rateConv,scaleSignal,scaleRate,
                                                                         -9999.,9999.);
                  rate_eff_bTag->SetName(TString(histo + "_ratel1jetetcut"));
                  rate_eff_bTag->SetLineColor(counter); 
                  rate_eff_bTag->SetLineWidth(width); 
                  rate_eff_bTag->SetMarkerColor(counter); 
                  rate_eff_bTag->SetMarkerStyle(20); 
                  rate_eff_bTag->SetMarkerSize(markerSize); 
                  rate_eff_bTag->SetLineStyle(1);//line_MET); 
               
                  canv_exist_bTag->cd();
               
                  rate_eff_bTag->Draw("lsame");
               
                  TString s = selection[iselection] + ", " + plotNames[iplot];
                  //entry = leg_exist_bTag->AddEntry(rate_eff_bTag,s.Data(),"l");


                  
               
                  //------------------------------
                  //Plot individual working points
                  
                  Float_t eff[3]  = {0.7,0.8,0.85};
                  Float_t cuts[3] = {30.,50.,70.};
                  //Float_t cuts[3] = {20.,30.,50.};
                  //Float_t cuts[3] = {50.,70.,90.};
               
                  for(int iop=0; iop!=3;++iop) {
                     
                     TGraph *rate_eff_bTag_Op = jetAlgs_ttbar->RatePerformance(dir + RateSample + SampleType + ".root",
                                                                               dir + SignalSample + SampleType + ".root",
                                                                               histo,histo_signal,
                                                                               rates,rateConv,scaleSignal,scaleRate,
                                                                               -9999.,9999.,true,cuts[iop]);
                     rate_eff_bTag_Op->SetName(TString::Format("%s_ratel1jetetcut%i",histo.Data(),iop).Data());
                     rate_eff_bTag_Op->SetLineColor(kBlack); 
                     rate_eff_bTag_Op->SetMarkerColor(counter); 
                     rate_eff_bTag_Op->SetMarkerStyle(24+iop); 
                     rate_eff_bTag_Op->SetMarkerSize(markerSize*1.7); 
                     
                     canv_exist_bTag->cd();
                     
                     rate_eff_bTag_Op->Draw("p,same");
                     
                     s.Form("%s %s (%.0fGeV)",selection[iselection].Data(),plotNamesLegend[iplot].Data(),cuts[iop]);
                     entry = leg_exist_bTag->AddEntry(rate_eff_bTag_Op,s.Data(),"p");
                  
                     canv_exist_bTag->Update();
                  } //iop
               
                  
               
               
               
               
                  //delete canv_exist_bTag;
                  //delete frame_exist_bTag;
                  //delete rate_eff_bTag;
                  //delete leg_exist_bTag;
               
               }
            }
         }
      } 
      //--------------------------------------







      
      if(do_l1jetetsum_scan) {
         ///--------------------------------------
         /// Plot optimization of L1 Jet input the L2 btag optimizations
         
         ///-------------------------------------------
         NumberPlots = 5;
         //plotNames[0] = "l2jetetsum"; plotNamesLegend[0] = "L2_JEX";
         plotNames[0] = "l2jetetsumeta20"; plotNamesLegend[0] = "L2_JEX |#eta|<2.0";
         plotNames[1] = "l2jetetsumeta27"; plotNamesLegend[1] = "L2_JEX |#eta|<2.7";
         plotNames[2] = "l2jetetsumeta30"; plotNamesLegend[2] = "L2_JEX |#eta|<3.0";
         plotNames[3] = "l2jetetsumeta32"; plotNamesLegend[3] = "L2_JEX |#eta|<3.2";
         plotNames[4] = "l2jetetsumeta40"; plotNamesLegend[4] = "L2_JEX |#eta|<4.0";
         //plotNames[0] = "l1jetetsum"; plotNamesLegend[0] = "L1_JEX";
         NumberSelections = 0;
         //selection[0] = "L_2bD"; 
         //selection[1] = "L2_1bD"; 
         selection[NumberSelections++] = "L1_JE100"; 
         //selection[NumberSelections++] = "L1_JE140"; 
         //selection[NumberSelections++] = "L1_JE200"; 
         
         
         int counter =0;
         bool ok = true;
         for(int iselection = 0; iselection != NumberSelections; ++iselection) {
            
            // Loop over all the plots!
            
            
            for(int iplot=0;iplot!=NumberPlots;iplot++) {

               ok = true;
               
               //if(iplot==0 && iselection==1) ok=false;
               //if(iplot==1 && iselection==1) ok=false;            
               
               if(ok) {
                  //cout << " Selected plot "<<plotNames[iplot] << " for selection " << selection[iselection] << endl;
                  
                  counter++;
                  TString histo = baseName + selection[iselection] + "_" + plotNames[iplot];
                  TString histo_signal = baseName + selection[iselection] + baseSignalSelection+ "_" + plotNames[iplot];
                  //Since the selection may already include a L1 or other selection 
                  //I should include that efficiency in my rate calculation        
               
                  scaleSignal[0] = 1.;scaleSignal[1] = 0.;
                  scaleRate[0]   = 1.;scaleRate[1]   = 0.;

                  //---- Signal scale
                  // This takes into account that I want the efficiency w.r.t to the 
                  // base selection without trigger requirement so if I need to take 
                  // into account e.g. the L1 item before the cut on the L2 variable.
                  jetAlgs_ttbar->GetScaleFactorFromRatio(scaleSignal,
                                                         dir + SignalSample + SampleType + ".root",
                                                         dir + SignalSample + SampleType + ".root",
                                                         baseName + selection[iselection] + baseSignalSelection + "_nj",
                                                         baseName + baseSignalSelection + "_nj");
                  cout << "scaleSignal = " << scaleSignal[0] << endl;
                  
                  //---- Background scale 
                  // This takes into account the efficiency for the rate to come to this selection
                  // note that the denominator is not the same as the numerator in this case 
                  // as the numerator includes a selection on having at least 2 L2Bjets (no cut though) 
                  // in the event
                  jetAlgs_ttbar->GetScaleFactorFromRatio(scaleRate,
                                                         dir + RateSample + SampleType + ".root",
                                                         dir + RateSample + SampleType + ".root",
                                                         baseName + selection[iselection] + "_nj",
                                                         baseName + "_nj");
                  
                  cout << "scaleRate = " << scaleRate[0] << endl;
                  if(scaleRate[0]<0.) {
                     cout << "Error! scaleRate is " << scaleRate[0] << endl; exit(-1);
                  }
                  
                  TGraph *rate_eff_bTag = jetAlgs_ttbar->RatePerformance(dir + RateSample + SampleType + ".root",
                                                                         dir + SignalSample + SampleType + ".root",
                                                                         histo,histo_signal,
                                                                         rates,rateConv,scaleSignal,scaleRate,
                                                                         -9999.,9999.);
                  rate_eff_bTag->SetName(TString(histo + "_ratel1jetetsumscancut"));
                  rate_eff_bTag->SetLineColor(counter); 
                  rate_eff_bTag->SetLineWidth(width); 
                  rate_eff_bTag->SetMarkerColor(counter); 
                  rate_eff_bTag->SetMarkerStyle(20); 
                  rate_eff_bTag->SetMarkerSize(markerSize); 
                  rate_eff_bTag->SetLineStyle(1);//line_MET); 
               
                  canv_exist_bTag->cd();
               
                  rate_eff_bTag->Draw("lsame");
               
                  TString s = selection[iselection] + ", " + plotNames[iplot];
                  //entry = leg_exist_bTag->AddEntry(rate_eff_bTag,s.Data(),"l");


                  
               
                  //------------------------------
                  //Plot individual working points
                  
                  Float_t eff[3]  = {0.7,0.8,0.85};
                  //Float_t cuts[3] = {150.,250.,400.};
                  //Float_t cuts[3] = {150.,195.,300.};
                  Float_t cuts[3] = {150.,180.,210.};

                  for(int iop=0; iop!=3;++iop) {
                     
                     TGraph *rate_eff_bTag_Op = jetAlgs_ttbar->RatePerformance(dir + RateSample + SampleType + ".root",
                                                                               dir + SignalSample + SampleType + ".root",
                                                                               histo,histo_signal,
                                                                               rates,rateConv,scaleSignal,scaleRate,
                                                                               -9999.,9999.,true,cuts[iop]);
                     rate_eff_bTag_Op->SetName(TString::Format("%s_ratel1jetetcut%i",histo.Data(),iop).Data());
                     rate_eff_bTag_Op->SetLineColor(kBlack); 
                     rate_eff_bTag_Op->SetMarkerColor(counter); 
                     rate_eff_bTag_Op->SetMarkerStyle(24+iop); 
                     rate_eff_bTag_Op->SetMarkerSize(markerSize*1.7); 
                     
                     canv_exist_bTag->cd();
                     
                     rate_eff_bTag_Op->Draw("p,same");
                     
                     s.Form("%s %s (%.0fGeV)",selection[iselection].Data(),plotNamesLegend[iplot].Data(),cuts[iop]);
                     entry = leg_exist_bTag->AddEntry(rate_eff_bTag_Op,s.Data(),"p");
                     
                     canv_exist_bTag->Update();
                  } //iop
                  
                  
               
                  //delete canv_exist_bTag;
                  //delete frame_exist_bTag;
                  //delete rate_eff_bTag;
                  //delete leg_exist_bTag;
               
               }
            }
         }
      } 
      //--------------------------------------




      
      if(do_jetetsum_scan) {
         ///--------------------------------------
         /// Plot optimization of L2 Jet et sum input to the L1 jet et sum
         
         ///-------------------------------------------
         NumberPlots = 1;
         plotNames[0] = "l2jetetsumemscale"; plotNamesLegend[0] = "L2_JE (EM)";
         plotNames[1] = "l2jetetsum"; plotNamesLegend[1] = "L2_JE";
         NumberSelections = 4;
         selection[0] = "L1_JE60"; 
         selection[1] = "L1_JE100"; 
         selection[2] = "L1_JE140"; 
         selection[3] = "L1_JE200"; 
         
         
         int counter =0;
         bool ok = true;
         for(int iselection = 0; iselection != NumberSelections; ++iselection) {
            
            // Loop over all the plots!
            
            
            for(int iplot=0;iplot!=NumberPlots;iplot++) {

               ok = true;
               
               //if(iplot==0 && iselection==1) ok=false;
               //if(iplot==1 && iselection==1) ok=false;            
               
               if(ok) {
                  //cout << " Selected plot "<<plotNames[iplot] << " for selection " << selection[iselection] << endl;
                  
                  counter++;
                  TString histo = baseName + selection[iselection] + "_" + plotNames[iplot];
                  TString histo_signal = baseName + selection[iselection] + baseSignalSelection+ "_" + plotNames[iplot];
                  //Since the selection may already include a L1 or other selection 
                  //I should include that efficiency in my rate calculation        
               
                  scaleSignal[0] = 1.;scaleSignal[1] = 0.;
                  scaleRate[0]   = 1.;scaleRate[1]   = 0.;

                  //---- Signal scale
                  // This takes into account that I want the efficiency w.r.t to the 
                  // base selection without trigger requirement so if I need to take 
                  // into account e.g. the L1 item before the cut on the L2 variable.
                  jetAlgs_ttbar->GetScaleFactorFromRatio(scaleSignal,
                                                         dir + SignalSample + SampleType + ".root",
                                                         dir + SignalSample + SampleType + ".root",
                                                         baseName + selection[iselection] + baseSignalSelection + "_nj",
                                                         baseName + baseSignalSelection + "_nj");
                  cout << "scaleSignal = " << scaleSignal[0] << endl;
                  
                  //---- Background scale 
                  // This takes into account the efficiency for the rate to come to this selection
                  // note that the denominator is not the same as the numerator in this case 
                  // as the numerator includes a selection on having at least 2 L2Bjets (no cut though) 
                  // in the event
                  jetAlgs_ttbar->GetScaleFactorFromRatio(scaleRate,
                                                         dir + RateSample + SampleType + ".root",
                                                         dir + RateSample + SampleType + ".root",
                                                         baseName + selection[iselection] + "_nj",
                                                         baseName + "_nj");
                  
                  cout << "scaleRate = " << scaleRate[0] << endl;
                  if(scaleRate[0]<0.) {
                     cout << "Error! scaleRate is " << scaleRate[0] << endl; exit(-1);
                  }
                  
                  TGraph *rate_eff_bTag = jetAlgs_ttbar->RatePerformance(dir + RateSample + SampleType + ".root",
                                                                         dir + SignalSample + SampleType + ".root",
                                                                         histo,histo_signal,
                                                                         rates,rateConv,scaleSignal,scaleRate,
                                                                         -9999.,9999.);
                  rate_eff_bTag->SetName(TString(histo + "_ratejetetsumscancut"));
                  rate_eff_bTag->SetLineColor(counter); 
                  rate_eff_bTag->SetLineWidth(width); 
                  rate_eff_bTag->SetMarkerColor(counter); 
                  rate_eff_bTag->SetMarkerStyle(20); 
                  rate_eff_bTag->SetMarkerSize(markerSize); 
                  rate_eff_bTag->SetLineStyle(1);//line_MET); 
               
                  canv_exist_bTag->cd();
               
                  rate_eff_bTag->Draw("lsame");
               
                  TString s = selection[iselection] + ", " + plotNames[iplot];
                  //entry = leg_exist_bTag->AddEntry(rate_eff_bTag,s.Data(),"l");


                  
               
                  //------------------------------
                  //Plot individual working points
                  
                  Float_t eff[3]  = {0.7,0.8,0.85};
                  Float_t cuts[3] = {100.,195.,245.};
                  
                  for(int iop=0; iop!=3;++iop) {
                     
                     TGraph *rate_eff_bTag_Op = jetAlgs_ttbar->RatePerformance(dir + RateSample + SampleType + ".root",
                                                                               dir + SignalSample + SampleType + ".root",
                                                                               histo,histo_signal,
                                                                               rates,rateConv,scaleSignal,scaleRate,
                                                                               -9999.,9999.,true,cuts[iop]);
                     rate_eff_bTag_Op->SetName(TString::Format("%s_ratejetetcut%i",histo.Data(),iop).Data());
                     rate_eff_bTag_Op->SetLineColor(kBlack); 
                     rate_eff_bTag_Op->SetMarkerColor(counter); 
                     rate_eff_bTag_Op->SetMarkerStyle(24+iop); 
                     rate_eff_bTag_Op->SetMarkerSize(markerSize*1.7); 
                     
                     canv_exist_bTag->cd();
                     
                     rate_eff_bTag_Op->Draw("p,same");
                     
                     s.Form("%s %s (%.0fGeV)",selection[iselection].Data(),plotNamesLegend[iplot].Data(),cuts[iop]);
                     entry = leg_exist_bTag->AddEntry(rate_eff_bTag_Op,s.Data(),"p");
                     
                     canv_exist_bTag->Update();
                  } //iop
                  
                  
               
                  //delete canv_exist_bTag;
                  //delete frame_exist_bTag;
                  //delete rate_eff_bTag;
                  //delete leg_exist_bTag;
               
               }
            }
         }
      } 
      //--------------------------------------





      
      if(do_l1met_scan) {
         ///--------------------------------------
         /// Plot optimization of L1 MET input the L2 btag
         
         ///-------------------------------------------
         NumberPlots = 1;
         //plotNames[0] = "l2met"; plotNamesLegend[0] = "L2_xe";
         plotNames[0] = "efmet"; plotNamesLegend[0] = "EF_xe";
         //plotNames[0] = "l1met"; plotNamesLegend[0] = "XE";
         NumberSelections = 3;
         //selection[0] = "L2_2bD"; 
         //selection[1] = "L2_1bD"; 
         //selection[0] = "L1_XE30";
         //selection[1] = "L1_XE30L2_xe35";
         //selection[2] = "L1_XE40L2_xe45";
         //selection[3] = "L1_XE50L2_xe60";
         //selection[0] = "L1_1J20L2_2bD"; 
         //selection[1] = "L1_2J20L2_2bD"; 
         //selection[0] = "L1_1J30";
         //selection[0] = "L1_1J55";
         selection[0] = "L1_JE100L2_je150";
         selection[1] = "L1_JE100L2_je195";
         selection[2] = "L1_2J15L1_XE30L2_2j30";

         
         int counter =0;
         bool ok = true;
         for(int iselection = 0; iselection != NumberSelections; ++iselection) {
            
            // Loop over all the plots!
            
            
            for(int iplot=0;iplot!=NumberPlots;iplot++) {

               ok = true;
               
               //if(iplot==0 && iselection==0) ok=true;
               //if(iplot==1 && (iselection>=1&&iselection<=3)) ok=true;            
               
               if(ok) {
                  //cout << " Selected plot "<<plotNames[iplot] << " for selection " << selection[iselection] << endl;
                  
                  counter++;
                  TString histo = baseName + selection[iselection] + "_" + plotNames[iplot];
                  TString histo_signal = baseName + selection[iselection] + baseSignalSelection+ "_" + plotNames[iplot];
                  //Since the selection may already include a L1 or other selection 
                  //I should include that efficiency in my rate calculation        

                  scaleSignal[0] = 1.;scaleSignal[1] = 0.;
                  scaleRate[0]   = 1.;scaleRate[1]   = 0.;

                  //---- Signal scale
                  // This takes into account that I want the efficiency w.r.t to the 
                  // base selection without trigger requirement so if I need to take 
                  // into account e.g. the L1 item before the cut on the L2 variable.
                  jetAlgs_ttbar->GetScaleFactorFromRatio(scaleSignal,
                                                         dir + SignalSample + SampleType + ".root",
                                                         dir + SignalSample + SampleType + ".root",
                                                         baseName + selection[iselection] + baseSignalSelection + "_nj",
                                                         baseName + baseSignalSelection + "_nj");
                  cout << "scaleSignal = " << scaleSignal[0] << endl;
                  
                  //---- Background scale 
                  // This takes into account the efficiency for the rate to come to this selection
                  // note that the denominator is not the same as the numerator in this case 
                  // as the numerator includes a selection on having at least 2 L2Bjets (no cut though) 
                  // in the event
                  jetAlgs_ttbar->GetScaleFactorFromRatio(scaleRate,
                                                         dir + RateSample + SampleType + ".root",
                                                         dir + RateSample + SampleType + ".root",
                                                         baseName + selection[iselection] + "_nj",
                                                         baseName + "_nj");
                  
                  cout << "scaleRate = " << scaleRate[0] << endl;
                  if(scaleRate[0]<0.) {
                     cout << "Error! scaleRate is " << scaleRate[0] << endl; exit(-1);
                  }
                  
                  TGraph *rate_eff_bTag = jetAlgs_ttbar->RatePerformance(dir + RateSample + SampleType + ".root",
                                                                         dir + SignalSample + SampleType + ".root",
                                                                         histo,histo_signal,
                                                                         rates,rateConv,scaleSignal,scaleRate,
                                                                         -9999.,9999.);
                  rate_eff_bTag->SetName(TString(histo + "_ratel1jetetsumscancut"));
                  rate_eff_bTag->SetLineColor(counter); 
                  rate_eff_bTag->SetLineWidth(width); 
                  rate_eff_bTag->SetMarkerColor(counter); 
                  rate_eff_bTag->SetMarkerStyle(20); 
                  rate_eff_bTag->SetMarkerSize(markerSize); 
                  rate_eff_bTag->SetLineStyle(1);//line_MET); 
               
                  canv_exist_bTag->cd();
               
                  rate_eff_bTag->Draw("lsame");
               
                  TString s = selection[iselection] + ", " + plotNames[iplot];
                  //entry = leg_exist_bTag->AddEntry(rate_eff_bTag,s.Data(),"l");


                  
               
                  //------------------------------
                  //Plot individual working points
                  
                  Float_t eff[3]  = {0.7,0.8,0.85};
                  Float_t cuts[3] = {30.,40.,45.};

                  for(int iop=0; iop!=3;++iop) {
                     
                     TGraph *rate_eff_bTag_Op = jetAlgs_ttbar->RatePerformance(dir + RateSample + SampleType + ".root",
                                                                               dir + SignalSample + SampleType + ".root",
                                                                               histo,histo_signal,
                                                                               rates,rateConv,scaleSignal,scaleRate,
                                                                               -9999.,9999.,true,cuts[iop]);
                     rate_eff_bTag_Op->SetName(TString::Format("%s_ratel1jetetcut%i",histo.Data(),iop).Data());
                     rate_eff_bTag_Op->SetLineColor(kBlack); 
                     rate_eff_bTag_Op->SetMarkerColor(counter); 
                     rate_eff_bTag_Op->SetMarkerStyle(24+iop); 
                     rate_eff_bTag_Op->SetMarkerSize(markerSize*1.7); 
                     
                     canv_exist_bTag->cd();
                     
                     rate_eff_bTag_Op->Draw("p,same");
                     
                     s.Form("%s %s (%.0fGeV)",selection[iselection].Data(),plotNamesLegend[iplot].Data(),cuts[iop]);
                     entry = leg_exist_bTag->AddEntry(rate_eff_bTag_Op,s.Data(),"p");
                     
                     canv_exist_bTag->Update();
                  } //iop
                  
                  
               
                  //delete canv_exist_bTag;
                  //delete frame_exist_bTag;
                  //delete rate_eff_bTag;
                  //delete leg_exist_bTag;
               
               }
            }
         }
      } 
      //--------------------------------------



      
      
      canv_exist_bTag->cd();
      canv_exist_bTag->Update();
      if(entry) {
         entry->SetTextAlign(12);
         entry->SetTextColor(1);
         leg_exist_bTag->Draw();
      }
      
      //ATLAS_LABEL(0.20,0.80);
      canv_exist_bTag->Update();
      
      TString saveName = TString( "plots/rates-l2btag-") + SignalSample + "-"+ OutputFileName;      
      
      canv_exist_bTag->SaveAs(saveName + ".png");
      canv_exist_bTag->SaveAs(saveName + ".root");

  


   }
  

}
