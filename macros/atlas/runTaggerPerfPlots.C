void runTaggerPerfPlots()
{
   ///-------------------------------------------------------------------------
   /// Compile everything
   ///-------------------------------------------------------------------------  
   gSystem->Load("libPhysics.so");
   //gSystem->CompileMacro ("style.cpp", "k");
   //gSystem->CompileMacro ("Util.cpp","k");
   //gSystem->CompileMacro ("/u1/phansson/jetmetbtag/RootUtils/trunk/AtlasStyle.C", "k");
   //gSystem->CompileMacro ("/u1/phansson/jetmetbtag/RootUtils/trunk/rootlogon.C", "k");
   gSystem->CompileMacro ("../../../RootUtils/trunk/Util.cpp", "k");
   //gSystem->CompileMacro ("rootlogonCompile.h", "k");
   gSystem->CompileMacro ("JetMetbTagAnalysisBase.cxx", "k");
   
   gROOT->LoadMacro("../../../RootUtils/trunk/AtlasStyle.C");
   SetAtlasStyle();
   
   
   
   ///-------------------------------------------------------------------------
   /// Switch on or off analyses
   ///-------------------------------------------------------------------------
  
   bool do_taggerPerf          = true;
  
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
   //TString dir         = "../topologies/jetmetbtag/files/100727_l2rate/";
   //TString dir         = "../topologies/jetmetbtag/files/100811_l2rate/";
   TString dir         = "../topologies/jetmetbtag/files/101005_l2btag/";
   TString tag_ttbar   = "final";
 
   /// Setup analysis
   JetMetbTagAnalysisBase *jetAlgs_ttbar = new JetMetbTagAnalysisBase(0,verbose);
   jetAlgs_ttbar->SetPlotTypeAndLumi(plotType,tag_ttbar);
   jetAlgs_ttbar->SetOutputDirectory(outDir);
   jetAlgs_ttbar->SetOutputRootFile(rootFile);


  
   ///+++++++++++++++++++++++++++++++++++++++++++++
   /// Generic plots stuff
   ///+++++++++++++++++++++++++++++++++++++++++++++
   TLegendEntry *entry;
   TString plotNames[30];
   TString fileNames[30];
   TString selection[30];
   TString legend[30];             
  
   Int_t NumberPlots = 0;
   Int_t NumberSelections = 0;

   TString baseName    = "l2rate";

  
 

   ///+++++++++++++++++++++++++++++++++++++++++++++
   /// tagging performance
   if(do_taggerPerf) {


      Int_t color_85eff = kGreen; Int_t color_80eff = kBlue; Int_t color_70eff = kRed; Int_t color_60eff = kViolet;
      Int_t line_MET = 1; Int_t line_DPhi = 3;
      Int_t markerSize = 1.7;
      Int_t specificSize = 2.0;
      
      
      Float_t ip3dcut_Op70 = -1;
      Float_t ip3dcut_Op80 = -1;
      Float_t ip3dcut_Op85 = -1;


      
      TGraph* l2_tag_perf = jetAlgs_ttbar->TaggerPerformance(dir + "tt.exttrgmc008.root",
                                                             dir + "tt.exttrgmc008.root",
                                                             "l2btagtruth_L1_J10offjet_jetjm0e0c0ljetprobparam",
                                                             "l2btagtruth_L1_J10offjet_jetjm0e0c0bjetprobparam",
                                                             -0.1,1.1);

      TGraph* l2_tag_perf_highpt = jetAlgs_ttbar->TaggerPerformance(dir + "tt.exttrgmc008.root",
                                                                    dir + "tt.exttrgmc008.root",
                                                                    "l2btagtruth_L1_J10offjet_jetjm2e0c0ljetprobparam",
                                                                    "l2btagtruth_L1_J10offjet_jetjm2e0c0bjetprobparam",
                                                                    -0.1,1.1);

      TGraph* l2_tag_perf_higheta = jetAlgs_ttbar->TaggerPerformance(dir + "tt.exttrgmc008.root",
                                                                     dir + "tt.exttrgmc008.root",
                                                                     "l2btagtruth_L1_J10offjet_jetjm0e3c0ljetprobparam",
                                                                     "l2btagtruth_L1_J10offjet_jetjm0e3c0bjetprobparam",
                                                                     -0.1,1.1);
      
      TGraph* l2_tag_perf_old = jetAlgs_ttbar->TaggerPerformance(dir + "tt.exttrgmc008.root",
                                                                 dir + "tt.exttrgmc008.root",
                                                                 "l2btagtruth_L1_J10offjet_jetjm0e0c0ljetprob",
                                                                 "l2btagtruth_L1_J10offjet_jetjm0e0c0bjetprob",
                                                                 -0.1,1.1);

      TGraph* l2_tag_perf_old_highpt = jetAlgs_ttbar->TaggerPerformance(dir + "tt.exttrgmc008.root",
                                                                        dir + "tt.exttrgmc008.root",
                                                                        "l2btagtruth_L1_J10offjet_jetjm2e0c0ljetprob",
                                                                        "l2btagtruth_L1_J10offjet_jetjm2e0c0bjetprob",
                                                                        -0.1,1.1);

      TGraph* l2_tag_perf_old_higheta = jetAlgs_ttbar->TaggerPerformance(dir + "tt.exttrgmc008.root",
                                                                        dir + "tt.exttrgmc008.root",
                                                                        "l2btagtruth_L1_J10offjet_jetjm0e3c0ljetprob",
                                                                        "l2btagtruth_L1_J10offjet_jetjm0e3c0bjetprob",
                                                                        -0.1,1.1);
      
      

//       TGraph* tag_perf = jetAlgs_ttbar->TaggerPerformance(dir + "j2.trg004.root",
//                                                           dir + "tt.trg004.root",
//                                                           "l2rate_ljip3d",
//                                                           "l2rate_bjip3d",
//                                                           -1000.,1500.);

      
      /*


      TGraph* l2_tag_perf = jetAlgs_ttbar->TaggerPerformance(dir + "j2.exttrgmc006.root",
                                                             dir + "tt.exttrgmc006.root",
                                                             "l2rate_ljl2ip3d",
                                                             "l2rate_bjl2ip3d",
                                                             0.,1.,
                                                             -1.,0.7,ip3dcut_Op70);
      
      TGraph* l2_tag_perf_alt_sig = jetAlgs_ttbar->TaggerPerformance(dir + "j2.exttrgmc006.root",
                                                                     dir + "py2bB400L300.exttrgmc006.root",
                                                                     "l2rate_ljl2ip3d",
                                                                     "l2rate_bjl2ip3d",
                                                                     0.,1.);

      TGraph* l2_tag_perf_j2r1303_only_J15 = jetAlgs_ttbar->TaggerPerformance(dir + "j2.exttrgmc006.root",
                                                                              dir + "j2.exttrgmc006.root",
                                                                              "l2rate_ljl2J15ip3d",
                                                                              "l2rate_bjl2J15ip3d",
                                                                              0.,1.);

      TGraph* l2_tag_perf_ttr1303_only_J15 = jetAlgs_ttbar->TaggerPerformance(dir + "tt.exttrgmc006.root",
                                                                              dir + "tt.exttrgmc006.root",
                                                                              "l2rate_ljl2J15ip3d",
                                                                              "l2rate_bjl2J15ip3d",
                                                                              0.,1.);
      
      TGraph* l2_tag_perf_r1303_J15 = jetAlgs_ttbar->TaggerPerformance(dir + "j2.exttrgmc006.root",
                                                                       dir + "tt.exttrgmc006.root",
                                                                       "l2rate_ljl2J15ip3d",
                                                                       "l2rate_bjl2J15ip3d",
                                                                       0.,1.);

      TGraph* l2_tag_perf_r1303_J10 = jetAlgs_ttbar->TaggerPerformance(dir + "j2.exttrgmc006.root",
                                                                       dir + "tt.exttrgmc006.root",
                                                                       "l2rate_ljl2J10ip3d",
                                                                       "l2rate_bjl2J10ip3d",
                                                                       0.,1.);

      TGraph* l2_tag_perf_ttr1260_only_J15 = jetAlgs_ttbar->TaggerPerformance(dir + "tt.trg004.root",
                                                                              dir + "tt.trg004.root",
                                                                              "l2rate_ljl2J15ip3d",
                                                                              "l2rate_bjl2J15ip3d",
                                                                              0.,1.);

      TGraph* l2_tag_perf_j2r1260_only_J15 = jetAlgs_ttbar->TaggerPerformance(dir + "j2.trg004.root",
                                                                              dir + "j2.trg004.root",
                                                                              "l2rate_ljl2J15ip3d",
                                                                              "l2rate_bjl2J15ip3d",
                                                                              0.,1.);

      TGraph* l2_tag_perf_r1260_J15 = jetAlgs_ttbar->TaggerPerformance(dir + "j2.trg004.root",
                                                                       dir + "tt.trg004.root",
                                                                       "l2rate_ljl2J15ip3d",
                                                                       "l2rate_bjl2J15ip3d",
                                                                       0.,1.);

      TGraph* l2_tag_perf_ttr13_only_J15 = jetAlgs_ttbar->TaggerPerformance(dir + "ttr13.trg004.root",
                                                                            dir + "ttr13.trg004.root",
                                                                            "l2rate_ljl2J15ip3d",
                                                                            "l2rate_bjl2J15ip3d",
                                                                            0.,1.);

      TGraph* l2_tag_perf_j2r13_only_J15 = jetAlgs_ttbar->TaggerPerformance(dir + "j2r13.trg004.root",
                                                                            dir + "j2r13.trg004.root",
                                                                            "l2rate_ljl2J15ip3d",
                                                                            "l2rate_bjl2J15ip3d",
                                                                            0.,1.);

      TGraph* l2_tag_perf_r13_J15 = jetAlgs_ttbar->TaggerPerformance(dir + "j2r13.trg004.root",
                                                                     dir + "ttr13.trg004.root",
                                                                     "l2rate_ljl2J15ip3d",
                                                                     "l2rate_bjl2J15ip3d",
                                                                     0.,1.);
      
      
      TGraph* l2_tag_perf_tmp = jetAlgs_ttbar->TaggerPerformance(dir + "j2.exttrgmc006.root",
                                                                 dir + "tt.trg004.root",
                                                                 "l2rate_ljl2ip3d",
                                                                 "l2rate_bjl2ip3d",
                                                                 0.,1.,
                                                                 -1.,0.8,ip3dcut_Op80);
      delete l2_tag_perf_tmp;
      
      l2_tag_perf_tmp = jetAlgs_ttbar->TaggerPerformance(dir + "j2.exttrgmc006.root",
                                                         dir + "tt.trg004.root",
                                                         "l2rate_ljl2ip3d",
                                                         "l2rate_bjl2ip3d",
                                                         0.,1.,
                                                         -1.,0.85,ip3dcut_Op85);
      delete l2_tag_perf_tmp;
      
      
      
 
      
      TGraph* tag_perf_alt_sig = jetAlgs_ttbar->TaggerPerformance(dir + "j2.exttrgmc006.root",
                                                                  dir + "py2bB400L300.exttrgmc006.root",
                                                                  "l2rate_ljip3d",
                                                                  "l2rate_bjip3d",
                                                                  -1000.,1500.);
      
      Float_t sv1ip3dcut_Op50 = -1;
      
      TGraph* tag_perf_sv1ip3d = jetAlgs_ttbar->TaggerPerformance(dir + "j2.exttrgmc006.root",
                                                                  dir + "tt.trg004.root",
                                                                  "l2rate_ljsv1ip3d",
                                                                  "l2rate_bjsv1ip3d",
                                                                  -1000.,1500.,
                                                                  -1.,0.5,sv1ip3dcut_Op50);

      TGraph* tag_perf_sv1ip3d_alt_sig = jetAlgs_ttbar->TaggerPerformance(dir + "j2.exttrgmc006.root",
                                                                          dir + "py2bB400L300.exttrgmc006.root",
                                                                          "l2rate_ljsv1ip3d",
                                                                          "l2rate_bjsv1ip3d",
                                                                          -1000.,1500.);
      
      Float_t sv1ip3dcut_Op60 = -1;
      TGraph* tag_perf_sv1ip3d_tmp = jetAlgs_ttbar->TaggerPerformance(dir + "j2.exttrgmc006.root",
                                                                      dir + "tt.trg004.root",
                                                                      "l2rate_ljsv1ip3d",
                                                                      "l2rate_bjsv1ip3d",
                                                                      -1000.,1500.,
                                                                      -1.,0.6,sv1ip3dcut_Op60);
      
      
      TGraph* tag_perf_sv1ip3d_jCOMB = jetAlgs_ttbar->TaggerPerformance(dir + "j1.exttrgmc006.root",
                                                                        dir + "tt.trg004.root",
                                                                        "l2rate_ljsv1ip3d",
                                                                        "l2rate_bjsv1ip3d",
                                                                        -1000.,1500.);
      
      TGraph* tag_perf_sv1ip3d_tt = jetAlgs_ttbar->TaggerPerformance(dir + "tt.trg004.root",
                                                                     dir + "tt.trg004.root",
                                                                     "l2rate_ljsv1ip3d",
                                                                     "l2rate_bjsv1ip3d",
                                                                     -1000.,1500.);
      
      */
      ///+++++++++++++++++++++++++++++++++++++++++++++
      TCanvas *canv_exist_bTag_perf = new TCanvas("canv_exist_bTag_perf","canv_exist_bTag_perf",650,600);
      canv_exist_bTag_perf->SetFillColor(0);
      canv_exist_bTag_perf->cd();
      //canv_exist_bTag_perf->SetLogy();
      //canv_exist_bTag_perf->SetLogx();
      canv_exist_bTag_perf->SetGridx(kTRUE);
      canv_exist_bTag_perf->SetGridy(kTRUE);   
      canv_exist_bTag_perf->cd();
     
      TH2F* frame_exist_bTag_perf = new TH2F("frame_exist_bTag_perf","",2,0.1,1.0,2,1.,100.0);
      frame_exist_bTag_perf->SetYTitle("light jet rejection");
      frame_exist_bTag_perf->SetXTitle("b-jet efficiency");
      frame_exist_bTag_perf->GetXaxis()->SetTitleColor(1);
      frame_exist_bTag_perf->GetYaxis()->SetTitleOffset(1.3);
      frame_exist_bTag_perf->GetYaxis()->SetNoExponent(kTRUE);
      frame_exist_bTag_perf->GetYaxis()->SetMoreLogLabels(kTRUE);
      frame_exist_bTag_perf->GetXaxis()->SetTitleOffset(1.13);
      frame_exist_bTag_perf->Draw("");   
      canv_exist_bTag_perf->cd();
      
      
      TLegend *leg_exist_bTag_perf = new TLegend(0.1630673,0.1607774,0.4921753,0.3975265);
      leg_exist_bTag_perf->SetFillStyle(0);

      l2_tag_perf->SetMarkerColor(kRed);
      l2_tag_perf->Draw("lpsame");
      entry = leg_exist_bTag_perf->AddEntry(l2_tag_perf,"New L2 JetProb","p");

      l2_tag_perf_highpt->SetLineColor(kRed);
      l2_tag_perf_highpt->Draw("lsame");
      entry = leg_exist_bTag_perf->AddEntry(l2_tag_perf_highpt,"New L2 JetProb 60<jet p_{T}<120GeV","l");
      
      l2_tag_perf_higheta->SetLineColor(kRed);
      l2_tag_perf_higheta->SetLineStyle(2);
      l2_tag_perf_higheta->Draw("lsame");
      entry = leg_exist_bTag_perf->AddEntry(l2_tag_perf_higheta,"New L2 JetProb 2.0<jet |#eta|<2.5GeV","l");

      l2_tag_perf_old->SetMarkerColor(kBlack);
      l2_tag_perf_old->Draw("lpsame");
      entry = leg_exist_bTag_perf->AddEntry(l2_tag_perf_old,"Online L2 JetProb","p");

      l2_tag_perf_old_highpt->SetMarkerColor(kBlack);
      l2_tag_perf_old_highpt->Draw("lsame");
      entry = leg_exist_bTag_perf->AddEntry(l2_tag_perf_old_highpt,"Online L2 JetProb 60<jet p_{T}<120GeV","l");

      l2_tag_perf_old_higheta->SetMarkerColor(kBlack);
      l2_tag_perf_old_higheta->SetLineStyle(2);
      l2_tag_perf_old_higheta->Draw("lsame");
      entry = leg_exist_bTag_perf->AddEntry(l2_tag_perf_old_higheta,"Online L2 JetProb 2.0<jet |#eta|<2.5GeV","l");

/*
      l2_tag_perf_j2r1303_only_J15->SetMarkerColor(kRed);
      l2_tag_perf_j2r1303_only_J15->Draw("lpsame");
      entry = leg_exist_bTag_perf->AddEntry(l2_tag_perf_j2r1303_only_J15,"L2 IP3D [QCD J2,r1303,J15]","p");

      l2_tag_perf_ttr1303_only_J15->SetMarkerColor(kRed+2);
      l2_tag_perf_ttr1303_only_J15->Draw("lpsame");
      entry = leg_exist_bTag_perf->AddEntry(l2_tag_perf_ttr1303_only_J15,"L2 IP3D [t#bar{t},r1303,J15]","p");

      l2_tag_perf_r1303_J15->SetLineColor(kRed+2);
      l2_tag_perf_r1303_J15->Draw("lsame");
      entry = leg_exist_bTag_perf->AddEntry(l2_tag_perf_r1303_J15,"L2 IP3D [r1303,J15]","l");

      l2_tag_perf_r1303_J10->SetLineColor(kRed+2);
      l2_tag_perf_r1303_J10->SetLineStyle(2);
      l2_tag_perf_r1303_J10->Draw("lsame");
      entry = leg_exist_bTag_perf->AddEntry(l2_tag_perf_r1303_J10,"L2 IP3D [r1303,J10]","l");

      l2_tag_perf_j2r13_only_J15->SetMarkerColor(kGreen);
      l2_tag_perf_j2r13_only_J15->Draw("lpsame");
      entry = leg_exist_bTag_perf->AddEntry(l2_tag_perf_j2r13_only_J15,"L2 IP3D [QCD J2,r13,J15]","p");
      
      l2_tag_perf_ttr13_only_J15->SetMarkerColor(kGreen+2);
      l2_tag_perf_ttr13_only_J15->Draw("lpsame");
      entry = leg_exist_bTag_perf->AddEntry(l2_tag_perf_ttr13_only_J15,"L2 IP3D [t#bar{t},r13,J15]","p");
      
      l2_tag_perf_r13_J15->SetLineColor(kGreen+2);
      l2_tag_perf_r13_J15->Draw("lsame");
      entry = leg_exist_bTag_perf->AddEntry(l2_tag_perf_r13_J15,"L2 IP3D [r13,J15]","l");
      
      l2_tag_perf_j2r1260_only_J15->SetMarkerColor(kBlack);
      l2_tag_perf_j2r1260_only_J15->Draw("lpsame");
      entry = leg_exist_bTag_perf->AddEntry(l2_tag_perf_j2r1260_only_J15,"L2 IP3D [QCD J2,r1260,J15]","p");

      l2_tag_perf_ttr1260_only_J15->SetMarkerColor(kGray);
      l2_tag_perf_ttr1260_only_J15->Draw("lpsame");
      entry = leg_exist_bTag_perf->AddEntry(l2_tag_perf_ttr1260_only_J15,"L2 IP3D [t#bar{t},r1260,J15]","p");

      l2_tag_perf_r1260_J15->SetLineColor(kGray);
      l2_tag_perf_r1260_J15->Draw("lsame");
      entry = leg_exist_bTag_perf->AddEntry(l2_tag_perf_r1260_J15,"L2 IP3D [r1260,J15]","l");

      tag_perf->SetLineColor(kCyan);
      tag_perf->Draw("lsame");
      entry = leg_exist_bTag_perf->AddEntry(tag_perf,"Offline IP3D [r1303]","l");
*/

//       l2_tag_perf->SetMarkerColor(kRed);
//       l2_tag_perf->Draw("lpsame");


//       l2_tag_perf_alt_sig->SetLineColor(kRed+1);
//       l2_tag_perf_alt_sig->SetLineStyle(2);
//       l2_tag_perf_alt_sig->Draw("lsame");
//       tag_perf->Draw("lpsame");
//       tag_perf_alt_sig->SetLineColor(tag_perf->GetMarkerColor()+1);
//       tag_perf_alt_sig->SetLineStyle(2);
//       tag_perf_alt_sig->Draw("lsame");
//       tag_perf_sv1ip3d->SetMarkerColor(kBlack);
//       tag_perf_sv1ip3d->Draw("lpsame");
//       tag_perf_sv1ip3d_alt_sig->SetLineColor(kBlack);
//       tag_perf_sv1ip3d_alt_sig->SetLineStyle(2);
//       tag_perf_sv1ip3d_alt_sig->Draw("lsame");
      //tag_perf_sv1ip3d_tt->SetMarkerColor(kGreen);
      //tag_perf_sv1ip3d_tt->Draw("lsame");
      //tag_perf_sv1ip3d_jCOMB->SetMarkerColor(kGreen);
      //tag_perf_sv1ip3d_jCOMB->Draw("lpsame");

     
//      TMarker* L2_def_op = new TMarker(0.70,16,22); 
//      L2_def_op->SetMarkerSize(specificSize); L2_def_op->SetMarkerColor(color_70eff); L2_def_op->Draw("");


      /*

      //Find the operating point from the curve
      double effOp70 = 0.;
      double effOp80 = 0.;
      double effOp85 = 0.;
      double rejOp70,rejOp80,rejOp85;
      for(int i=0;i!=l2_tag_perf->GetN();++i) {
         double x,y; 
         l2_tag_perf->GetPoint(i,x,y);
         if(fabs(x-0.7) < fabs(effOp70-0.7)) { effOp70 = x; rejOp70=y; }
         if(fabs(x-0.8) < fabs(effOp80-0.8)) { effOp80 = x; rejOp80=y; }
         if(fabs(x-0.85) < fabs(effOp85-0.85)) { effOp85 = x; rejOp85=y; }
      }
      TMarker* L2_Op70= new TMarker(effOp70,rejOp70,23); 
      L2_Op70->SetMarkerSize(specificSize); L2_Op70->SetMarkerColor(kMagenta); L2_Op70->Draw("");
      TMarker* L2_Op80= new TMarker(effOp80,rejOp80,22); 
      L2_Op80->SetMarkerSize(specificSize); L2_Op80->SetMarkerColor(kMagenta); L2_Op80->Draw("");
      TMarker* L2_Op85= new TMarker(effOp85,rejOp85,21); 
      L2_Op85->SetMarkerSize(specificSize); L2_Op85->SetMarkerColor(kMagenta); L2_Op85->Draw("");

      //Find operating points from the curve
      double effOp50; 
      double effOp60; 
      double rejOp50;
      double rejOp60;
      for(int i=0;i!=tag_perf_sv1ip3d->GetN();++i) {
         double x,y; 
         tag_perf_sv1ip3d->GetPoint(i,x,y);
         if(fabs(x-0.5) < fabs(effOp50-0.5)) { effOp50 = x; rejOp50=y; }
         if(fabs(x-0.6) < fabs(effOp60-0.6)) { effOp60 = x; rejOp60=y; }
      }
      TMarker* OFF_Op50= new TMarker(effOp50,rejOp50,23); 
      OFF_Op50->SetMarkerSize(specificSize); OFF_Op50->SetMarkerColor(kBlack); OFF_Op50->Draw("");
      TMarker* OFF_Op60= new TMarker(effOp60,rejOp60,22); 
      OFF_Op60->SetMarkerSize(specificSize); OFF_Op60->SetMarkerColor(kBlack); OFF_Op60->Draw("");

      double effttOp50; 
      double effttOp60; 
      double rejttOp50;
      double rejttOp60;
      for(int i=0;i!=tag_perf_sv1ip3d_tt->GetN();++i) {
         double x,y; 
         tag_perf_sv1ip3d_tt->GetPoint(i,x,y);
         if(fabs(x-0.5) < fabs(effttOp50-0.5)) { effttOp50 = x; rejttOp50=y; }
         if(fabs(x-0.6) < fabs(effttOp60-0.6)) { effttOp60 = x; rejttOp60=y; }
      }
      TMarker* OFF_tt_Op50= new TMarker(effttOp50,rejttOp50,25); 
      OFF_tt_Op50->SetMarkerSize(specificSize); OFF_tt_Op50->SetMarkerColor(kBlack); OFF_tt_Op50->Draw("");
      TMarker* OFF_tt_Op60= new TMarker(effttOp60,rejttOp60,26); 
      OFF_tt_Op60->SetMarkerSize(specificSize); OFF_tt_Op60->SetMarkerColor(kBlack); OFF_tt_Op60->Draw("");
      
      
      //ATLAS_LABEL(0.20,0.80);
     
      TString leg_Op70; leg_Op70.Form("IP3D (eff=70%,rej=%.0f)",rejOp70);
      TString leg_Op80; leg_Op80.Form("IP3D (eff=80%,rej=%.0f)",rejOp80);
      TString leg_Op85; leg_Op85.Form("IP3D (eff=85%,rej=%.0f)",rejOp85);
      TString leg_Op50; leg_Op50.Form("SV1IP3D (eff=50%,rej=%.0f)",rejOp50);
      TString leg_Op60; leg_Op60.Form("SV1IP3D (eff=60%,rej=%.0f)",rejOp60);
      TString leg_tt_Op50; leg_tt_Op50.Form("SV1IP3D t#bar{t} (eff=50%,rej=%.0f)",rejttOp50);
      TString leg_tt_Op60; leg_tt_Op60.Form("SV1IP3D t#bar{t} (eff=60%,rej=%.0f)",rejttOp60);
//      entry = leg_exist_bTag_perf->AddEntry(OFF_Op50,leg_Op50.Data(),"p");
//      entry = leg_exist_bTag_perf->AddEntry(OFF_Op60,leg_Op60.Data(),"p");
//      entry = leg_exist_bTag_perf->AddEntry(OFF_tt_Op50,leg_tt_Op50.Data(),"p");
//      entry = leg_exist_bTag_perf->AddEntry(OFF_tt_Op60,leg_tt_Op60.Data(),"p");
//       entry = leg_exist_bTag_perf->AddEntry(L2_Op70,leg_Op70.Data(),"p");
//       entry = leg_exist_bTag_perf->AddEntry(L2_Op80,leg_Op80,"p");
//       entry = leg_exist_bTag_perf->AddEntry(L2_Op85,leg_Op85,"p");
      entry = leg_exist_bTag_perf->AddEntry(l2_tag_perf,"L2 IP3D","p");
      entry = leg_exist_bTag_perf->AddEntry(l2_tag_perf_alt_sig,"L2 IP3D (#DeltaM=100GeV)","l");
      entry = leg_exist_bTag_perf->AddEntry(tag_perf,"Offline IP3D (#DeltaM=100GeV)","p");
      entry = leg_exist_bTag_perf->AddEntry(tag_perf_alt_sig,"Offline IP3D","p");
      entry = leg_exist_bTag_perf->AddEntry(tag_perf_sv1ip3d,"Offline SV1IP3D","p");
      entry = leg_exist_bTag_perf->AddEntry(tag_perf_sv1ip3d_alt_sig,"Offline SV1IP3D (#DeltaM=100GeV)","l");
      //entry = leg_exist_bTag_perf->AddEntry(tag_perf_sv1ip3d_jCOMB,"Offline jCOMB","p");
      //entry = leg_exist_bTag_perf->AddEntry(tag_perf_sv1ip3d_tt,"Offline SV1IP3D (only t#bar{t})","l");
      */


      entry->SetTextAlign(12);
      entry->SetTextColor(1);
      leg_exist_bTag_perf->Draw();

      /*
      TString text_ip3dcut_Op70;text_ip3dcut_Op70.Form("70%: IP3D>%.2f", ip3dcut_Op70);
      myText(0.65,0.88,kBlack,text_ip3dcut_Op70.Data());
      text_ip3dcut_Op70.Form("80%: IP3D>%.2f", ip3dcut_Op80);
      myText(0.65,0.82,kBlack,text_ip3dcut_Op70.Data());
      text_ip3dcut_Op70.Form("85%: IP3D>%.2f", ip3dcut_Op85);
      myText(0.65,0.76,kBlack,text_ip3dcut_Op70.Data());
      */
//void myText(Double_t x,Double_t y,const char *text, Double_t tsize=0.05,Color_t color=1) {

      /*
      TString text_sv1ip3dcut_Op60;
      text_sv1ip3dcut_Op60.Form("60%: SV1IP3D>%.2f", sv1ip3dcut_Op60);
      Utils::myText(0.65,0.88,text_sv1ip3dcut_Op60.Data());
      text_sv1ip3dcut_Op60.Form("50%: SV1IP3D>%.2f", sv1ip3dcut_Op50);
      Utils::myText(0.65,0.82,text_sv1ip3dcut_Op60.Data());
      */

      canv_exist_bTag_perf->Update();
     
      TString saveName = TString( "tagperf");
     
      canv_exist_bTag_perf->SaveAs(saveName + ".png");
      canv_exist_bTag_perf->SaveAs(saveName + ".root");
   
   }
  
  
}
