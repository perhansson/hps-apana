
void runL2btagChi2Plots(TString outputname="")
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
//    rootlogon();
//    gROOT->SetStyle("ATLAS");
//    gROOT->ForceStyle();
   
   
   
   ///-------------------------------------------------------------------------
   /// Switch on or off analyses
   ///-------------------------------------------------------------------------
  
   bool do_dataMCComparison        = 0;
   bool do_fileComparison          = 0;
   bool do_selectionComparison     = 0;
   bool do_plotComparison          = 1;
   bool do_bs_shift_plots          = 0;
   bool do_ip_fit                  = 0;
   bool do_flavor_plots            = 0;
   bool do_neg_ip_flavor_est       = 0;
   bool do_frac_zero_tracks_roi    = 0;




   ///-------------------------------------------------------------------------
   /// Setup run
   ///-------------------------------------------------------------------------
   Long64_t EvtMax         = 1;
   Long64_t EvtCnt         = 1;
   Int_t    NFilesNeeded   = 1;
   bool     verbose        = false;
   
   /// output
   TString outDir      = "plots/";
   TString plotType    = ".png";
   TString rootFile    = "outputfile_" + outputname + ".root";
   TString outfilename = outDir + rootFile;
   //TString dir         = "../topologies/jetmetbtag/files/100622_l2btag/";
   //TString dir         = "../topologies/jetmetbtag/files/100727_l2btag/";
   //TString dir         = "../topologies/jetmetbtag/files/100805_l2btag_3/";
   //TString dir         = "../topologies/jetmetbtag/files/100813_l2btag/";
   //TString dir         = "../topologies/jetmetbtag/files/100831_l2btag/";
   //TString dir         = "../topologies/jetmetbtag/files/100922_l2btag/";
   //TString dir         = "../topologies/jetmetbtag/files/100927_l2btag/";
   //TString dir         = "../topologies/jetmetbtag/files/100928_l2btag/";
   //TString dir         = "../topologies/jetmetbtag/files/100929_l2btag/";
   //TString dir         = "../topologies/jetmetbtag/files/100930_l2btag/";
   //TString dir         = "../topologies/jetmetbtag/files/101001_l2btag/";
   //TString dir         = "../topologies/jetmetbtag/files/101004_l2btag/";
   //TString dir         = "../topologies/jetmetbtag/files/101005_l2btag/";
   //TString dir         = "../topologies/jetmetbtag/files/101006_l2btag_2/";
   TString dir         = "../topologies/jetmetbtag/files/101014_l2btag/";
   
   TString tag   = outputname;
   
   /// Setup analysis
   JetMetbTagAnalysisBase *jetAlgs = new JetMetbTagAnalysisBase(0,verbose);
   jetAlgs->SetPlotTypeAndLumi(plotType,tag);
   jetAlgs->SetOutputDirectory(outDir);
   jetAlgs->SetOutputRootFile(rootFile);
   
   
   
   ///+++++++++++++++++++++++++++++++++++++++++++++
   /// Generic plots stuff
   ///+++++++++++++++++++++++++++++++++++++++++++++
   TLegendEntry *entry;
   TString plotNames[500];
   TString fileNames[50];
   TString selection[50];
   TString legend[50];             
   
   Int_t NumberPlots = 0;
   Int_t NumberSelections = 0;



   TString baseName    = "l2btag";
   
   if( do_dataMCComparison) { 
      
      Int_t numberFiles = 2;      
      fileNames[0] = dir + "jCOMB.exttrgmc009.root";
      //fileNames[1] = dir + "data159224.exttrg007.root";
      //fileNames[1] = dir + "data153565.exttrg008.root";
      //fileNames[1] = dir + "data158116.exttrg007.root";
      //fileNames[1] = dir + "data160980.exttrg008.root";
      fileNames[1] = dir + "data160980.exttrg009.root";
      //fileNames[1] = dir + "data160879.exttrg008.root";
      //fileNames[1] = dir + "tt.exttrgmc008.root";
      ///-------------------------------------------      
      legend[0] = "Pythia QCD";
      //legend[1] = "159224";
      //legend[1] = "153565";
      //legend[1] = "158116";
      legend[1] = "160980";
      //legend[1] = "160879";
      //legend[1] = "t#bar{t}";
      ///-------------------------------------------
      int c = 0;
      
      plotNames[c++] = "jsv0";
      plotNames[c++] = "jip3d";
      plotNames[c++] = "jpt";
      plotNames[c++] = "j0pt";
      plotNames[c++] = "j1pt";
      plotNames[c++] = "nj";          
      plotNames[c++] = "jjetprob";
      plotNames[c++] = "jsv0efip3dtag";
      plotNames[c++] = "jjetprobefjetprobtag";
      plotNames[c++] = "jefip3d";
      plotNames[c++] = "jefip2d";
      plotNames[c++] = "jefip1d";
      plotNames[c++] = "jefjetprob";      
      plotNames[c++] = "jsv0l2ip3dtag";
      plotNames[c++] = "jjetprobl2jetprobtag";
      plotNames[c++] = "jl2ip3d";
      plotNames[c++] = "jl2ip2d";
      plotNames[c++] = "jl2ip1d";
      plotNames[c++] = "jl2jetprob";

//       plotNames[c++] = "dphij0met";
//       plotNames[c++] = "dphij1met";
//       plotNames[c++] = "dphij0j1";
//       plotNames[c++] = "drj0j1";
      plotNames[c++] = "nl1j";
      plotNames[c++] = "l1jpt";
      plotNames[c++] = "met";
      //plotNames[c++] = "l1jeta";
      //plotNames[c++] = "trkjetphicorr";         
      plotNames[c++] = "trackrawpt";
      plotNames[c++] = "trackraweta";
      plotNames[c++] = "trackrawphi";
      plotNames[c++] = "trackrawd0";
      
      
      
      int N_pt_bins = 0;
      int N_eta_bins = 0;
      for(int ipt=0;ipt!=N_pt_bins;++ipt) {
         for(int ieta=0;ieta!=N_eta_bins;++ieta) {
            
            TString jm_str;
            jm_str.Form("jm%ie%ic0",ipt,ieta);         
            cout << "Looking at jet match string : " << jm_str << endl;            
            


            plotNames[c++] = TString::Format("%strackselz0",jm_str.Data());
            plotNames[c++] = TString::Format("%strackselZ0",jm_str.Data());
            plotNames[c++] = TString::Format("%strackselZ0sintheta",jm_str.Data());
            plotNames[c++] = TString::Format("%strackz0",jm_str.Data());
            plotNames[c++] = TString::Format("%strackz0sign",jm_str.Data());
            plotNames[c++] = TString::Format("%strackZ0sign",jm_str.Data());
            plotNames[c++] = TString::Format("%strackz0err",jm_str.Data());
            plotNames[c++] = TString::Format("%strackz0sintheta",jm_str.Data());
            plotNames[c++] = TString::Format("%strackZ0sintheta",jm_str.Data());

            


            plotNames[c++] = TString::Format("%sntrackphieta",jm_str.Data());
            plotNames[c++] = TString::Format("%strackselPt",jm_str.Data());
            plotNames[c++] = TString::Format("%sntrackpos",jm_str.Data());
            plotNames[c++] = TString::Format("%strackseld0",jm_str.Data());
            plotNames[c++] = TString::Format("%strackselD0",jm_str.Data());
            plotNames[c++] = TString::Format("%strackselz0",jm_str.Data());
            plotNames[c++] = TString::Format("%strackselZ0",jm_str.Data());
            plotNames[c++] = TString::Format("%strackselZ0sintheta",jm_str.Data());
            plotNames[c++] = TString::Format("%strackselchi2prob",jm_str.Data());
            plotNames[c++] = TString::Format("%strackselnsihits",jm_str.Data());


            
            plotNames[c++] = TString::Format("%sntrack",jm_str.Data());
            //plotNames[c++] = TString::Format("%strackip",jm_str.Data());
            plotNames[c++] = TString::Format("%strackipsignzoom",jm_str.Data());
            plotNames[c++] = TString::Format("%strackipsignzoomneg",jm_str.Data());
            plotNames[c++] = TString::Format("%strackz0",jm_str.Data());
            plotNames[c++] = TString::Format("%strackz0sign",jm_str.Data());
            plotNames[c++] = TString::Format("%strackZ0sign",jm_str.Data());
            plotNames[c++] = TString::Format("%strackz0err",jm_str.Data());
            plotNames[c++] = TString::Format("%strackz0sintheta",jm_str.Data());
            plotNames[c++] = TString::Format("%strackZ0sintheta",jm_str.Data());
            plotNames[c++] = TString::Format("%strackd0",jm_str.Data());
            plotNames[c++] = TString::Format("%strackd0err",jm_str.Data());
            plotNames[c++] = TString::Format("%strackpixhits",jm_str.Data());
            plotNames[c++] = TString::Format("%strackscthits",jm_str.Data());
            plotNames[c++] = TString::Format("%strackpixscthits",jm_str.Data());
            plotNames[c++] = TString::Format("%stracktrthits",jm_str.Data());
            plotNames[c++] = TString::Format("%strackdphijet",jm_str.Data());
            plotNames[c++] = TString::Format("%strackdrjet",jm_str.Data());
            plotNames[c++] = TString::Format("%strackchi2",jm_str.Data());
            plotNames[c++] = TString::Format("%strackchi2probhits",jm_str.Data());
            plotNames[c++] = TString::Format("%sl1pt",jm_str.Data());
            plotNames[c++] = TString::Format("%sl1eta",jm_str.Data());
            plotNames[c++] = TString::Format("%strackpt",jm_str.Data());
            plotNames[c++] = TString::Format("%strackphi",jm_str.Data());
            plotNames[c++] = TString::Format("%stracketa",jm_str.Data());
            plotNames[c++] = TString::Format("%strackprob",jm_str.Data());
            plotNames[c++] = TString::Format("jet%sjetprob",jm_str.Data());
            plotNames[c++] = TString::Format("jet%soffjetprob",jm_str.Data());
       
    
            
         }
      }
      
      
      NumberPlots = c;  
      
      ///-------------------------------------------     
      NumberSelections = 1;
//       selection[0] = baseName + "";
      selection[0] = baseName + "L1_J10";
      selection[1] = baseName + "L1_J10dj";
      selection[0] = baseName + "L1_J10djdphi27";
      selection[3] = baseName + "L1_J10djdphi27j40";
      selection[4] = baseName + "L1_J10djdphi27j40abtag";
      selection[5] = baseName + "L1_J10djdphi27j40abtagmuveto";

      selection[0] = baseName + "L1_J10offjet";
      //selection[0] = baseName + "L1_J10";
      //selection[0] = baseName + "L2_b10";
      ///-------------------------------------------
     
      for(int iplot=0;iplot!=NumberPlots;++iplot) {
         for(int iselection=0;iselection!=NumberSelections;++iselection) {
            for(int ilog=0;ilog!=3;++ilog) {
               bool logx=false;
               bool logy=false;
               TString logAddOn;
               if(ilog==1) {logy=true;  logAddOn="logy";cout << "inlogAddon=" << logAddOn << endl; }
               else if(ilog==2) {logx=true; logAddOn="logx";cout << "inlogAddon=" << logAddOn << endl; }
               else {logAddOn="";}
               cout << "----------------------------------------------" << endl;
               cout << "Starting plot overlay" << endl;
               cout << "----------------------------------------------" << endl;
              
               jetAlgs->SetRebin(2);
               TString plotName = selection[iselection] + "_" + plotNames[iplot];       
               TString saveName = selection[iselection] + "_" + plotNames[iplot] + "_" + logAddOn;       
               bool drawStats = false;
               bool drawExtra = false;
               bool writeFile = true;
               bool dataMCCompare = true;
               bool dataMCRatio = true;
               TString xAxis = plotNames[iplot];
               TString yAxis = "Entries";
               Float_t YMin = -1;
               Float_t YMax = -1;
               Float_t XMin = -1;
               Float_t XMax = -1;
               bool drawNorm = true;
               TString newLabel = "";
               bool plotMore = false;
               bool lineOnly = false;
               jetAlgs->makeCombinedFilePlots(fileNames,
                                              plotName, 
                                              legend,
                                              numberFiles, 
                                              xAxis,
                                              yAxis,
                                              saveName,
                                              YMin,YMax,
                                              drawNorm,
                                              logx, logy,
                                              XMin,XMax,
                                              drawStats,
                                              drawExtra,
                                              writeFile,
                                              dataMCCompare,
                                              dataMCRatio,newLabel,plotMore,lineOnly);
            }  
         }
      }
   }
  
    



   
   if( do_selectionComparison ) {
      ///+++++++++++++++++++++++++++++++++++++++++++++
      /// Compare plots for different selections
      ///+++++++++++++++++++++++++++++++++++++++++++++
      
      //gStyle->SetDrawOption("hist");
      ///-------------------------------------------
      Int_t numberFiles = 1;
      fileNames[0] = dir + "data158045.exttrg004.root";        
      fileNames[0] = dir + "data153565.exttrg003.root";        
      fileNames[0] = dir + "jCOMB.exttrgmc006.root";        
      ///-------------------------------------------
      int c=0;      
//       plotNames[c++] = "jm2trackipsign";    
//      plotNames[c++] = "jm0e0trackd0";    
//      plotNames[c++] = "jm0e0trackipsign";    
//       plotNames[c++] = "jm2trackd0err";    
//       plotNames[c++] = "jm2trackpt";    
//      plotNames[c++] = "jm0e0trackprob";    
      //plotNames[c++] = "jetjm0e0jetprob";    
      plotNames[c++] = "jetjm0e0offjetflavor";

      int NumberPlots = c;  

      int NumberSelections = 0;
      //selection[0] = baseName;
      //selection[NumberSelections++] = baseName + "L1_J10";
      selection[NumberSelections++] = baseName + "L1_J10dj";
      selection[NumberSelections++] = baseName + "L1_J10djdphi27";
      selection[NumberSelections++] = baseName + "L1_J10djdphi27j40";
      selection[NumberSelections++] = baseName + "L1_J10djdphi27j40abtag";
      selection[NumberSelections++] = baseName + "L1_J10djdphi27j40abtagmuveto";
      //selection[2] = baseName + "L1_J10nvtx1";
      //selection[3] = baseName + "L1_J10nvtx2";
      //selection[4] = baseName + "L1_J10nvtx3";
//       selection[NumberSelections++] = baseName + "L1_J10bsdxdy1";
//       selection[NumberSelections++] = baseName + "L1_J10bsdxdy2";
//       selection[NumberSelections++] = baseName + "L1_J10bsdxdy3";
//       selection[NumberSelections++] = baseName + "L1_J10bsdxdy4";
//       selection[NumberSelections++] = baseName + "L1_J10bsdxdy5";
//       selection[NumberSelections++] = baseName + "L1_J10bsdxdy6";
      ///-------------------------------------------
      double bs_shift[30];
      for(int ishift=0;ishift!=NumberSelections;++ishift) {
         //double shift = (ishift*0.5*bs_sigma);         
         bs_shift[ishift]=(ishift*0.5);//*bs_sigma);
      }

   
      ///-------------------------------------------
      //legend[0] = "All";  
      //legend[0] = "L1_J10";  
      for(int i=0;i!=NumberSelections;++i) 
         legend[i]=selection[i];
      //legend[i]=TString::Format("L1 J10 #Delta_{BS}/#sigma_{BS}#approx%.1f",bs_shift[i]);
      
      
      ///-------------------------------------------
      
      for(int ifile=0;ifile!=numberFiles;++ifile) {        
         for(int iplot=0;iplot!=NumberPlots;++iplot) {
            for(int ilog=1;ilog!=2;++ilog) {
               bool logx=false;
               bool logy=false;
               TString logAddOn;
               if(ilog==1) {logy=true;  logAddOn="logy";cout << "inlogAddon=" << logAddOn << endl; }
               else if(ilog==2) {logx=true; logAddOn="logx";cout << "inlogAddon=" << logAddOn << endl; }
               else {logAddOn="";}
               
               //make the plotnames to be compared
               TString fullPlotNames[30];
               for(int iselection=0;iselection!=NumberSelections;++iselection) {                 
                  fullPlotNames[iselection] = selection[iselection] + "_" + plotNames[iplot];       
               }
               TString saveName = fileNames[ifile] + "_" + plotNames[iplot]+"_"+logAddOn;       
               saveName.ReplaceAll(".","_");
               saveName.ReplaceAll("/","");
               saveName.ReplaceAll("__","");
               

               
               //jetAlgs->SetRebin(10);
               jetAlgs->makeCombinedPlots(fileNames[ifile],
                                          fullPlotNames,
                                          legend,
                                          NumberSelections,
                                          plotNames[iplot],
                                          "Entries",
                                          saveName,-1,-1,
                                          true,
                                          logx,logy,-1,-1,
                                          false,"hist");
               
            }
         }
      }
     
   }
   
   
   
    


   if( do_plotComparison ) {
      ///+++++++++++++++++++++++++++++++++++++++++++++
      /// Compare different plots for same file
      ///+++++++++++++++++++++++++++++++++++++++++++++
      
      //gStyle->SetDrawOption("hist");
      ///-------------------------------------------
      
      Int_t numberFiles = 0;
      //fileNames[numberFiles++] = dir + "jCOMB.exttrgmc008.root";
      //fileNames[numberFiles++] = dir + "data160879.exttrg008.root";
      //fileNames[numberFiles++] = dir + "data160980.exttrg008.root";
      fileNames[numberFiles++] = dir + "tt.exttrgmc010.root";
      ///-------------------------------------------
      int NumberPlots = 0;
      //for(int iclass=0;iclass!=8;++iclass) {
      //for(int iclass=0;iclass!=8;++iclass) {
      //TString jm_str = "jm";
      //if(iclass!=0) jm_str.Form("jm%i",iclass-1);         
      //cout << "jm_str : " << jm_str << endl;
      //plotNames[1] = TString::Format("%strackprob",jm_str.Data());
      //plotNames[0] = TString::Format("%strackbprob",jm_str.Data());
      //plotNames[2] = TString::Format("%strackcprob",jm_str.Data());
      //plotNames[3] = TString::Format("%stracklprob",jm_str.Data());
      //plotNames[1] = TString::Format("%strackipsign",jm_str.Data());
      //plotNames[0] = TString::Format("%strackbipsign",jm_str.Data());
      //plotNames[2] = TString::Format("%strackcipsign",jm_str.Data());
      //plotNames[3] = TString::Format("%stracklipsign",jm_str.Data());
      //plotNames[1] = TString::Format("jet%sjetprob",jm_str.Data());
      //plotNames[0] = TString::Format("jet%sbjetprob",jm_str.Data());
      //plotNames[2] = TString::Format("jet%scjetprob",jm_str.Data());
      //plotNames[3] = TString::Format("jet%sljetprob",jm_str.Data());
      //}


//                      wfill(hist(pre,suf,TString::Format("jet%sip3donl",jm_str2.Data())),l2bjet->IP3D());
//                      wfill(hist(pre,suf,TString::Format("jet%sjetprobonl",jm_str2.Data())),l2bjet->Chi2());
//                      wfill(hist(pre,suf,TString::Format("jet%sjetprob",jm_str2.Data())),jet_prob);

      plotNames[NumberPlots] = "jm0e0c0trackselpt";
      legend[NumberPlots++] = "track sel p_{T}";
                     

//       plotNames[NumberPlots] = "jetjm0e0c0ip3donl";
//       legend[NumberPlots++] = "IP3D L2_b10_noCut";
      
//       plotNames[NumberPlots] = "jetjm0e0c0jetprobonl";
//       legend[NumberPlots++] = "JetProb L2_b10_noCut";
      
//       plotNames[NumberPlots] = "jetjm0e0c0jetprob";
//       legend[NumberPlots++] = "Re-run JetProb L2_b10_noCut";
      
//       plotNames[NumberPlots] = "jsv0efip3dtag";
//       legend[NumberPlots++] = "SVO w/ HLT IP3D >0.3";
//       plotNames[NumberPlots] = "jsv0";
//       legend[NumberPlots++] = "SV0";
      
//       plotNames[NumberPlots] = "jjetprobefjetprobtag";
//       legend[NumberPlots++] = "JetProb w/ HLT JetProb >0.49";
//       plotNames[NumberPlots] = "jjetprob";
//       legend[NumberPlots++] = "JetProb";

//       plotNames[NumberPlots] = "bjjetprobefjetprobtag";
//       legend[NumberPlots++] = "b-jet JetProb w/ HLT JetProb >0.49";
//       plotNames[NumberPlots] = "bjjetprob";
//       legend[NumberPlots++] = "b-jet JetProb";
      
//        plotNames[NumberPlots] = "bjsv0";
//        legend[NumberPlots++] = "b-jet SV0";

//        plotNames[NumberPlots] = "bjsv0efip3dtag";
//        legend[NumberPlots++] = "b-jet SV0 w/ HLT IP3D >0.3";

//       plotNames[NumberPlots] = "ljsv0";
//       legend[NumberPlots++] = "light jet SV0";
      
//       plotNames[NumberPlots] = "ljsv0efip3dtag";
//       legend[NumberPlots++] = "light jet SV0 w/ HLT IP3D >0.3";

//       plotNames[NumberPlots] = "jm0e0c0trackZ0sign";
//       legend[NumberPlots++] = "Z_{0} all jets";
//       plotNames[NumberPlots] = "jm0e2c0trackZ0sign";
//       legend[NumberPlots++] = "Z_{0} -2.5<jet #eta<-2.0";
//       plotNames[NumberPlots] = "jm0e3c0trackZ0sign";
//       legend[NumberPlots++] = "Z_{0} -2.0<jet #eta<-1.0";
//       plotNames[NumberPlots] = "jm0e4c0trackZ0sign";
//       legend[NumberPlots++] = "Z_{0} -1.0<jet #eta<1.0";

//       plotNames[NumberPlots] = "jm0e0c0trackz0sintheta";
//       legend[NumberPlots++] = "Z_{0}#timessin(#theta) all jets";
//       plotNames[NumberPlots] = "jm0e2c0trackz0sintheta";
//       legend[NumberPlots++] = "Z_{0}#timessin(#theta) -2.5<jet #eta<-2.0";
//       plotNames[NumberPlots] = "jm0e3c0trackz0sintheta";
//       legend[NumberPlots++] = "Z_{0}#timessin(#theta) -2.0<jet #eta<-1.0";
//       plotNames[NumberPlots] = "jm0e4c0trackz0sintheta";
//       legend[NumberPlots++] = "Z_{0}#timessin(#theta) -1.0<jet #eta<1.0";

      
      //plotNames[NumberPlots] = "jetjm0e0c0bjetprob";
      //legend[NumberPlots++] = "Online b-jet";
      
//       plotNames[NumberPlots] = "jetjm0e0c0ljetprob";
//       legend[NumberPlots++] = "Online light jet";
      
//       plotNames[NumberPlots] = "jetjm1e0c0ljetprob";
//       legend[NumberPlots++] = "Online light jet p_{T}<60 GeV";
      
//       plotNames[NumberPlots] = "jetjm2e0c0ljetprob";
//       legend[NumberPlots++] = "Online light jet 60<jet p_{T}<120 GeV";
      
//       plotNames[NumberPlots] = "jm0e3c0tracklprob";
//       legend[NumberPlots++] = "Online light jet 2.0<jet |#eta|<2.5";
      

//       plotNames[NumberPlots] = "jm0e1c0tracklprobparam";
//       legend[NumberPlots++] = "New light jet jet |#eta|<1.0 GeV";

//       plotNames[NumberPlots] = "jm0e3c0tracklprobparam";
//       legend[NumberPlots++] = "New light jet  2.0<jet |#eta|<2.5";
      
//       plotNames[NumberPlots] = "jm1e0c0tracklprobparam";
//       legend[NumberPlots++] = "New param. jet p_{T}<60 GeV";

//       plotNames[NumberPlots] = "jm0e1c0tracklprobparam";
//       legend[NumberPlots++] = "New param. jet |#eta|<1.0 GeV";
      
//       plotNames[NumberPlots] = "jm2e0c0tracklprobparam";
//       legend[NumberPlots++] = "New param. 60<jet p_{T}<120 GeV";

//       plotNames[NumberPlots] = "jm0e3c0tracklprobparam";
//       legend[NumberPlots++] = "New param. 1.0<jet |#eta|<2.0";


//       plotNames[NumberPlots] = "jm0e0c1trackbprob";
//       legend[NumberPlots++] = "Online b-jet jet <7 Si hits";

//       plotNames[NumberPlots] = "jm0e0c2trackbprob";
//       legend[NumberPlots++] = "Online b-jet #geq7 Si hits";

//       plotNames[NumberPlots] = "jetjm0e0c0ljetprobparam";
//       legend[NumberPlots++] = "New light jet";
      
//       plotNames[NumberPlots] = "jetjm1e0c0ljetprobparam";
//       legend[NumberPlots++] = "New light jet p_{T}<60 GeV";
      
//       plotNames[NumberPlots] = "jetjm2e0c0ljetprobparam";
//       legend[NumberPlots++] = "New light 60<jet p_{T}<120 GeV";

//       plotNames[NumberPlots] = "jetjm0e0c0bjetprobparam";
//       legend[NumberPlots++] = "New b-jet";

//       plotNames[NumberPlots] = "jetjm0e0c0ljetprobparam";
//       legend[NumberPlots++] = "New light jet";
      
//       plotNames[NumberPlots] = "jm0e0c1trackbprobparam";
//       legend[NumberPlots++] = "New b-jet <7 Si hits";
      
//       plotNames[NumberPlots] = "jm0e0c2trackbprobparam";
//       legend[NumberPlots++] = "New b-jet #geq7 Si hits";


//       plotNames[NumberPlots] = "jm0e0c1tracklprobparam";
//       legend[NumberPlots++] = "New param. #leq7 Si hits";

//       plotNames[NumberPlots] = "jm0e0c2tracklprobparam";
//       legend[NumberPlots++] = "New param. >7 Si hits";
      
      
//       plotNames[NumberPlots] = "jm0e0c0trackbprob";
//       legend[NumberPlots++] = "Online b-jets";
      
//       plotNames[NumberPlots] = "jm0e0c0trackbprobparam";
//       legend[NumberPlots++] = "New b-jets";
      

//       plotNames[NumberPlots] = "jm0e0c0tracklipsignneg";
//       legend[NumberPlots++] = "All tracks";

//       plotNames[NumberPlots] = "jm0e0c1tracklipsignneg";
//       legend[NumberPlots++] = "(nPix+SCT hits)#leq7";

//       plotNames[NumberPlots] = "jm0e0c2tracklipsignneg";
//       legend[NumberPlots++] = "(nPix+SCT hits)>7";


//       plotNames[NumberPlots] = "jm0e0c0trackz0sintheta";
//       legend[NumberPlots++] = "Z_{0}#timessin(#theta) all jets";

//       plotNames[NumberPlots] = "jm0e0c0trackbz0sintheta";
//       legend[NumberPlots++] = "Z_{0}#timessin(#theta) b-jets";

//       plotNames[NumberPlots] = "jm0e2c0trackbz0sintheta";
//       legend[NumberPlots++] = "Z_{0}#timessin(#theta) -2.5<jet #eta<-2.0 b-jets";

//       plotNames[NumberPlots] = "jm0e3c0trackbz0sintheta";
//       legend[NumberPlots++] = "Z_{0}#timessin(#theta) -2.0<jet #eta<-1.0 b-jets";

//       plotNames[NumberPlots] = "jm0e4c0trackbz0sintheta";
//       legend[NumberPlots++] = "Z_{0}#timessin(#theta) -1.0<jet #eta<1.0 b-jets";

//       plotNames[NumberPlots] = "jm0e0c0trackcz0sintheta";
//       legend[NumberPlots++] = "Z_{0}#timessin(#theta) c-jets";

//       plotNames[NumberPlots] = "jm0e0c0tracklz0sintheta";
//       legend[NumberPlots++] = "Z_{0}#timessin(#theta) light jets";

        
//const double eta_bins[N_eta_bins] = {-9999999.9,-2.5,-2.0,-1.0,1.0,2.0,2.5,9999999.9};


//      plotNames[NumberPots = "jm3e0c0ntrackphi";
//       plotNames[1] = "jm3e0c0ntrackphieta";
//       plotNames[1] = "jm0e0c0ntrack";
//       plotNames[0] = "jm1e0c0ntrack";
//       plotNames[2] = "jm2e0c0ntrack";
//       plotNames[3] = "jm3e0c0ntrack";
      
//       plotNames[0] = "jm2e1c0trackipsign";
//       plotNames[1] = "jm2e1c0trackbipsign";
//       plotNames[2] = "jm2e1c0trackcipsign";
//       plotNames[1] = "jm2e1c0tracklipsign";
//       ///-------------------------------------------      
//       legend[0] = "#Delta#Phi(trk,ROI)<0.2";
//       legend[1] = "#Delta#Phi/#eta(trk,ROI)<0.2";
//       legend[1] = "All";
//       legend[0] = "jet p_{T}<40GeV";
//       legend[2] = "40<jet p_{T}<70GeV"; 
//       legend[3] = "70<jet p_{T}<120GeV";
//       legend[0] = "All jets";
//       legend[1] = "b-jets";
//       legend[2] = "c-jets";
//       legend[1] = "Veto b/c-jets";
      NumberSelections = 0;
      //selection[0] = "";
      //selection[0] = baseName + "L1_J10djdphi27";
      //selection[NumberSelections++] = baseName + "L1_J10";
      selection[NumberSelections++] = baseName + "truth_L1_J10offjet";
      ///-------------------------------------------
      
      for(int ifile=0;ifile!=numberFiles;++ifile) {        
         for(int iselection=0;iselection!=NumberSelections;++iselection) {
            for(int ilog=1;ilog!=2;++ilog) {
               bool logx=false;
               bool logy=false;
               TString logAddOn;
               if(ilog==1) {logy=true;  logAddOn="logy";cout << "inlogAddon=" << logAddOn << endl; }
               else if(ilog==2) {logx=true; logAddOn="logx";cout << "inlogAddon=" << logAddOn << endl; }
               else {logAddOn="";}
               
               //make the plotnames to be compared
               TString fullPlotNames[30];
               for(int iplot=0;iplot!=NumberPlots;++iplot) {
                  if(selection[iselection]=="")
                     fullPlotNames[iplot] = selection[iselection] + plotNames[iplot];       
                  else 
                     fullPlotNames[iplot] = selection[iselection] + "_" + plotNames[iplot];                            
                  
               }
               TString saveName = jetAlgs->StripFileName(fileNames[ifile]) + "_" + selection[iselection] + "_" + plotNames [0] + "_" + logAddOn;       
               
               
               jetAlgs->SetRebin(4);
               jetAlgs->makeCombinedPlots(fileNames[ifile],
                                          fullPlotNames,
                                          legend,
                                          NumberPlots,
                                          plotNames[0],
                                          "Entries",
                                          saveName,
                                          -1,-1,
                                          true,
                                          logx,logy,
                                          -1,-1,
                                          false,"E",0);


     
     



            } //log
         }//nsel
      }//ifile
   }
   
   


   
   if( do_bs_shift_plots ) {
      ///+++++++++++++++++++++++++++++++++++++++++++++
      /// Compare plots for different beam spots shifts
      ///+++++++++++++++++++++++++++++++++++++++++++++
      
      //gStyle->SetDrawOption("hist");
      ///-------------------------------------------
      Int_t numberFiles = 2;
      fileNames[0] = dir + "data158045.exttrg004.root";        
      fileNames[1] = dir + "data153565.exttrg003.root";        
      fileNames[0] = dir + "jCOMB.exttrgmc006.root";        
      ///-------------------------------------------
      int c=0;
      plotNames[c++] = "jetjm0e0jetprob";    
      plotNames[c++] = "jetjm2e0jetprob";    
      plotNames[c++] = "jetjm4e0jetprob";    
      plotNames[c++] = "jetjm0e1jetprob";    
      plotNames[c++] = "jetjm0e3jetprob";    
      //plotNames[c++] = "jm2trackd0";    
      //plotNames[c++] = "jm2trackipsign";    
      //plotNames[c++] = "jm2trackprob";    
      int NumberPlots = c;  

      ///-------------------------------------------
      
      int NumberSelections = 7;
      //selection[0] = baseName;
      selection[0] = baseName + "L1_J10";
      //selection[2] = baseName + "L1_J10nvtx1";
      //selection[3] = baseName + "L1_J10nvtx2";
      //selection[4] = baseName + "L1_J10nvtx3";
      selection[1] = baseName + "L1_J10bsdxdy1";
      selection[2] = baseName + "L1_J10bsdxdy2";
      selection[3] = baseName + "L1_J10bsdxdy3";
      selection[4] = baseName + "L1_J10bsdxdy4";
      selection[5] = baseName + "L1_J10bsdxdy5";
      selection[6] = baseName + "L1_J10bsdxdy6";
      ///-------------------------------------------
      double bs_shift[7];
      for(int ishift=1;ishift!=7;++ishift) {
         //double shift = (ishift*0.5*bs_sigma);         
         bs_shift[ishift]=(ishift*0.5);//*bs_sigma);
      }
      //legend[0] = "All";  
      ///-------------------------------------------
      
      

      TLegendEntry *entry;
      TLegend* leg = new TLegend(0.2,0.2,0.5,0.3);
      leg->SetFillColor(0);
      leg->SetBorderSize(0);
      TCanvas *c11 = (TCanvas*)gROOT->FindObject("c11");
      if (c11) {c11->Clear();} 
      else {
         c11 = new TCanvas("c11","c11");
      }
      c11->Clear();
      

      for(int ifile=0;ifile!=numberFiles;++ifile) {        
         
         
         TGraphErrors* gr_bs_frac_acc = new TGraphErrors(NumberSelections);
         
         
         //make the plotnames to be compared
         int iplot = 0;
         TString fullPlotName;
         for(int iselection=0;iselection!=NumberSelections;++iselection) {                 
            fullPlotName = selection[iselection] + "_" + plotNames[iplot];       
            
            
            //Open the file
            TFile* f = 0;
            TString fname = fileNames[ifile];
            f = (TFile*)gROOT->FindObject(fname);
            if(!f) {
               cout << "this file " << fname << " was not open -> open it" << endl;
               f = new TFile(fname);      
            }
            f->cd();
            TH1* h=0;
            if(f->IsOpen()) {
               h=(TH1*)gROOT->FindObject((const char*)(fullPlotName));
            }
            else {
               cout << "Could not open file " << dir << endl;
               exit(-1);
            }
            if(!h) {
               cout << "Could not find histogram " << fullPlotName << endl;
               exit(-1);      
            }
            
            //Integrate to some cut value
            double cut = 1.0 - 0.49;
            int bin_cut = h->FindBin(cut);
            double N_acc = h->Integral(1,bin_cut+1); 
            double N = h->Integral(1,h->GetNbinsX()); 
            double f_acc = N_acc / N;
            
            gr_bs_frac_acc->SetPoint(iselection,bs_shift[iselection],f_acc);
            gr_bs_frac_acc->SetPointError(iselection,0.,0.);
            
         }
         
         TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
         if (c1) {c1->Clear();} 
         else {
            Utils::style();
            c1 = (TCanvas*)gROOT->FindObject("c1");
         }
         c1->Clear();
         c1->cd();
         gr_bs_frac_acc->SetTitle(";Beam spot shift [#sigma_{BS}];Fraction of accepted events(#chi^{2} cut=0.49)");
         gr_bs_frac_acc->Draw("ALP");
         
         TString saveName = outDir +fileNames[ifile].ReplaceAll(dir,"") + ".frac_acc_bsshiftX.png";
         cout << "save as: " << saveName << endl;
         c1->SaveAs(saveName);
         
         
         c11->cd();
         
         gr_bs_frac_acc->SetMarkerColor(ifile+1);
         gr_bs_frac_acc->SetLineColor(ifile+1);
         gr_bs_frac_acc->SetMinimum(0.);
         if(ifile==0) gr_bs_frac_acc->Draw("ALP");
         else gr_bs_frac_acc->Draw("same,LP");
         
         
         TString fn = fileNames[ifile].ReplaceAll(dir,"");
         fn.ReplaceAll(".root","");
         fn.ReplaceAll(".exttrgmc006","");
         fn.ReplaceAll(".exttrg003","");
         entry = leg->AddEntry(gr_bs_frac_acc,fn,"LP");
         
      }
      
      leg->Draw();
      TString saveName = outDir + "frac_acc_bsshiftX_samplecmp.png";
      c11->SaveAs(saveName);
      
      
     
      
   }
   








   if( do_flavor_plots ) {
      ///+++++++++++++++++++++++++++++++++++++++++++++
      /// Compare plots for different beam spots shifts
      ///+++++++++++++++++++++++++++++++++++++++++++++
      
      //gStyle->SetDrawOption("hist");
      ///-------------------------------------------
      TString fileNameMC = dir + "jCOMB.exttrgmc006.root";        
      TString fileNameData = dir + "data153565.exttrg003.root";        
      ///-------------------------------------------
      int c=0;
      TString plotNameData[2];
      const int NumberPlotsMC = 4;
      TString plotNameMC[NumberPlotsMC][2];
      for(int ipt=0;ipt!=1;++ipt) {
         for(int ieta=0;ieta!=1;++ieta) {
            TString jm_str = TString::Format("jm%ie%i",ipt,ieta);         
            cout << "jm_str : " << jm_str << endl;
            //plotName[1] = TString::Format("%strackprob",jm_str.Data());
            //plotName[0] = TString::Format("%strackbprob",jm_str.Data());
            //plotName[2] = TString::Format("%strackcprob",jm_str.Data());
            //plotName[3] = TString::Format("%stracklprob",jm_str.Data());
//             plotNameMC[0][0] = TString::Format("jet%sljetprob",jm_str.Data());
//             plotNameMC[1][0] = TString::Format("jet%scjetprob",jm_str.Data());
//             plotNameMC[2][0] = TString::Format("jet%sbjetprob",jm_str.Data());
//             plotNameMC[3][0] = TString::Format("jet%sjetprob",jm_str.Data());
//             plotNameMC[0][0] = TString::Format("%stracklprob",jm_str.Data());
//             plotNameMC[1][0] = TString::Format("%strackcprob",jm_str.Data());
//             plotNameMC[2][0] = TString::Format("%strackbprob",jm_str.Data());
//             plotNameMC[3][0] = TString::Format("%strackprob",jm_str.Data());
            plotNameMC[0][0] = TString::Format("%stracklipsign",jm_str.Data());
            plotNameMC[1][0] = TString::Format("%strackcipsign",jm_str.Data());
            plotNameMC[2][0] = TString::Format("%strackbipsign",jm_str.Data());
            plotNameMC[3][0] = TString::Format("%strackipsign",jm_str.Data());
            plotNameMC[0][1] = "light jets";
            plotNameMC[1][1] = "c-jets";
            plotNameMC[2][1] = "b-jets";
            plotNameMC[3][1] = "All jets";
            //plotName[1] = TString::Format("jet%sjetprob",jm_str.Data());
            //plotName[0] = TString::Format("jet%sbjetprob",jm_str.Data());
            //plotName[2] = TString::Format("jet%scjetprob",jm_str.Data());
            //plotName[3] = TString::Format("jet%sljetprob",jm_str.Data());

            plotNameData[0] = TString::Format("%strackipsign",jm_str.Data());
            //plotNameData[0] = TString::Format("%strackprob",jm_str.Data());
            //plotNameData[0] = TString::Format("jet%sjetprob",jm_str.Data());
            plotNameData[1] = "Run 153565";
            
         }
      }

      ///-------------------------------------------
      
      int NumberSelections = 1;
      //selection[0] = baseName;
      //selection[0] = baseName + "L1_J10";
      selection[0] = baseName + "L1_J10djJ10dphi27";
      ///-------------------------------------------
      
      
      TLegendEntry *entry;
      TLegend* leg = new TLegend(0.2,0.2,0.5,0.3);
      leg->SetFillColor(0);
      leg->SetBorderSize(0);
      TCanvas *c11 = (TCanvas*)gROOT->FindObject("c11");
      if (c11) {c11->Clear();} 
      else {
         c11 = new TCanvas("c11","c11");
      }
      c11->Clear();

      
      TString fullPlotName;

      for(int iselection=0;iselection!=NumberSelections;++iselection) {                 

         TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
         if (c1) {c1->Clear();} 
         else {
            Utils::style();
            c1 = (TCanvas*)gROOT->FindObject("c1");
         }
         c1->Clear();
         c1->cd();
         
         
         
         TString fullPlotName = selection[iselection] + "_" + plotNameData[0];       
         TH1F* hdata = (TH1F*)jetAlgs->FindObjectInFile(fileNameData,fullPlotName);

         entry = leg->AddEntry(hdata,plotNameData[1],"LP");
         
         TH1F* histos[NumberPlotsMC];
         
         for(int imc=0;imc!=3;++imc) {
            fullPlotName = selection[iselection] + "_" + plotNameMC[imc][0];  
            histos[imc] = (TH1F*)jetAlgs->FindObjectInFile(fileNameMC,fullPlotName);
            //Normalize all to data
            histos[imc]->Scale(hdata->Integral(-1,99999)/histos[imc]->Integral(-1,999999));            
            histos[imc]->SetLineColor(imc+1);
            if(imc==0)
               histos[imc]->Draw("hist");
            else
               histos[imc]->Draw("hist,same");
            entry = leg->AddEntry(histos[imc],plotNameMC[imc][1],"L");
            
         }
         
         
         hdata->Draw("same");

         leg->Draw();
         
         TString saveName = outDir +fullPlotName.ReplaceAll(dir,"") + "flavor_overlay.png";
         cout << "save as: " << saveName << endl;
         //c1->SaveAs(saveName);
         
 
      }
     
      
   }
   


   if( do_neg_ip_flavor_est ) {
      ///+++++++++++++++++++++++++++++++++++++++++++++
      /// Compare the IP distributions for different flavors
      ///+++++++++++++++++++++++++++++++++++++++++++++      
      //gStyle->SetDrawOption("hist");
      ///-------------------------------------------
      
      TH1F* h_num = jetAlgs->FindObjectInFile(dir + "jCOMB.exttrgmc006.root",baseName + "L1_J10djdphi27_jm0e0c0tracklipsign");
      TH1F* h_den = jetAlgs->FindObjectInFile(dir + "jCOMB.exttrgmc006.root",baseName + "L1_J10djdphi27_jm0e0c0trackipsign");
      h_num->Rebin(2);
      h_den->Rebin(2);
      h_num->Scale(1./h_num->Integral());
      h_den->Scale(1./h_den->Integral());
      TH1F* h_ratio = (TH1F*)h_num->Clone("h_ratio");
      h_ratio->Divide(h_den);
      
      TCanvas *c11 = (TCanvas*)gROOT->FindObject("c11");
      if (c11) {c11->Clear();} 
      else {
         c11 = new TCanvas("c11","c11");
      }
      c11->Clear();            
      
      h_ratio->Draw();
      h_ratio->Fit("pol0");

      TString saveName = outDir + "h_ratio_ipsign_jm0e0c0_fit.png";
      saveName.ReplaceAll(dir,"");
      c11->SaveAs(saveName.Data());


   }

   if( do_frac_zero_tracks_roi ) {
      ///+++++++++++++++++++++++++++++++++++++++++++++
      /// Fraction of ROIs with no tracks
      ///+++++++++++++++++++++++++++++++++++++++++++++      
      //gStyle->SetDrawOption("hist");
      ///-------------------------------------------
      const int Nptbins = 4;
      //double ptbins[4] = {0.,40,70.,120.};
      double ptbins[Nptbins] = {20.,55,95.,140.};
      TH1F* h_ntrack[Nptbins];
      TH1F* h_ntrack_largeeta[Nptbins];
      TH1F* h_ntrack_data[Nptbins];
      TH1F* h_ntrack_data_largeeta[Nptbins];
      h_ntrack[0] = (TH1F*)jetAlgs->FindObjectInFile(dir + "jCOMB.exttrgmc006.root",baseName + "L1_J10djdphi27_jm1e1c0ntrackpos");
      h_ntrack[1] = (TH1F*)jetAlgs->FindObjectInFile(dir + "jCOMB.exttrgmc006.root",baseName + "L1_J10djdphi27_jm2e1c0ntrackpos");
      h_ntrack[2] = (TH1F*)jetAlgs->FindObjectInFile(dir + "jCOMB.exttrgmc006.root",baseName + "L1_J10djdphi27_jm3e1c0ntrackpos");
      h_ntrack[3] = (TH1F*)jetAlgs->FindObjectInFile(dir + "jCOMB.exttrgmc006.root",baseName + "L1_J10djdphi27_jm4e1c0ntrackpos");
      h_ntrack_largeeta[0] = (TH1F*)jetAlgs->FindObjectInFile(dir + "jCOMB.exttrgmc006.root",baseName + "L1_J10djdphi27_jm1e2c0ntrackpos");
      h_ntrack_largeeta[1] = (TH1F*)jetAlgs->FindObjectInFile(dir + "jCOMB.exttrgmc006.root",baseName + "L1_J10djdphi27_jm2e2c0ntrackpos");
      h_ntrack_largeeta[2] = (TH1F*)jetAlgs->FindObjectInFile(dir + "jCOMB.exttrgmc006.root",baseName + "L1_J10djdphi27_jm3e2c0ntrackpos");
      h_ntrack_largeeta[3] = (TH1F*)jetAlgs->FindObjectInFile(dir + "jCOMB.exttrgmc006.root",baseName + "L1_J10djdphi27_jm4e2c0ntrackpos");
      h_ntrack_data[0] = (TH1F*)jetAlgs->FindObjectInFile(dir + "data153565.exttrg003.root",baseName + "L1_J10djdphi27_jm1e1c0ntrackpos");
      h_ntrack_data[1] = (TH1F*)jetAlgs->FindObjectInFile(dir + "data153565.exttrg003.root",baseName + "L1_J10djdphi27_jm2e1c0ntrackpos");
      h_ntrack_data[2] = (TH1F*)jetAlgs->FindObjectInFile(dir + "data153565.exttrg003.root",baseName + "L1_J10djdphi27_jm3e1c0ntrackpos");
      h_ntrack_data[3] = (TH1F*)jetAlgs->FindObjectInFile(dir + "data153565.exttrg003.root",baseName + "L1_J10djdphi27_jm4e1c0ntrackpos");
      h_ntrack_data_largeeta[0] = (TH1F*)jetAlgs->FindObjectInFile(dir + "data153565.exttrg003.root",baseName + "L1_J10djdphi27_jm1e2c0ntrackpos");
      h_ntrack_data_largeeta[1] = (TH1F*)jetAlgs->FindObjectInFile(dir + "data153565.exttrg003.root",baseName + "L1_J10djdphi27_jm2e2c0ntrackpos");
      h_ntrack_data_largeeta[2] = (TH1F*)jetAlgs->FindObjectInFile(dir + "data153565.exttrg003.root",baseName + "L1_J10djdphi27_jm3e2c0ntrackpos");
      h_ntrack_data_largeeta[3] = (TH1F*)jetAlgs->FindObjectInFile(dir + "data153565.exttrg003.root",baseName + "L1_J10djdphi27_jm4e2c0ntrackpos");
      TGraphErrors* gr_ntrack = new TGraphErrors(Nptbins);
      gr_ntrack->SetTitle(";Offline jet p_{T} bin [GeV];Fraction Jet ROIs with no pos track"); 
      TGraphErrors* gr_ntrack_largeeta = new TGraphErrors(Nptbins);
      TGraphErrors* gr_ntrack_data = new TGraphErrors(Nptbins);
      gr_ntrack_data->SetTitle(";Offline jet p_{T} bin [GeV];Fraction Jet ROIs with no pos track");
      TGraphErrors* gr_ntrack_data_largeeta = new TGraphErrors(Nptbins);
      gr_ntrack_data_largeeta->SetTitle(";Offline jet p_{T} bin [GeV];Fraction Jet ROIs with no pos track");
      for(int i=0;i!=Nptbins;++i) {
         double n0 = h_ntrack[i]->Integral(h_ntrack[i]->FindBin(0.),h_ntrack[i]->FindBin(0.));
         double n = h_ntrack[i]->Integral(-1,999999);
         double f = n0/n;
         double f_e = Utils::CalcRatioErr(n0, n);
         gr_ntrack->SetPoint(i,ptbins[i],f);
         gr_ntrack->SetPointError(i,0.,f_e);
         
         n0 = h_ntrack_data[i]->Integral(h_ntrack_data[i]->FindBin(0.),h_ntrack_data[i]->FindBin(0.));
         n = h_ntrack_data[i]->Integral(-1,999999);
         f = n0/n;
         f_e = Utils::CalcRatioErr(n0, n);

         gr_ntrack_data->SetPoint(i,ptbins[i],f);
         gr_ntrack_data->SetPointError(i,0.,f_e);

         n0 = h_ntrack_data_largeeta[i]->Integral(h_ntrack_data_largeeta[i]->FindBin(0.),h_ntrack_data_largeeta[i]->FindBin(0.));
         n =  h_ntrack_data_largeeta[i]->Integral(-1,999999);
         f = n0/n;
         f_e = Utils::CalcRatioErr(n0, n);
         
         gr_ntrack_data_largeeta->SetPoint(i,ptbins[i],f);
         gr_ntrack_data_largeeta->SetPointError(i,0.,f_e);

         n0 = h_ntrack_largeeta[i]->Integral(h_ntrack_largeeta[i]->FindBin(0.),h_ntrack_largeeta[i]->FindBin(0.));
         n = h_ntrack_largeeta[i]->Integral(-1,999999);
         f = n0/n;
         f_e = Utils::CalcRatioErr(n0, n);
         
         gr_ntrack_largeeta->SetPoint(i,ptbins[i],f);
         gr_ntrack_largeeta->SetPointError(i,0.,f_e);


      }
      
      TCanvas *c11 = (TCanvas*)gROOT->FindObject("c11");
      if (c11) {c11->Clear();} 
      else {
         c11 = new TCanvas("c11","c11");
      }
      c11->Clear();            
      
      gr_ntrack_data_largeeta->SetMarkerStyle(kFullSquare);
      gr_ntrack_data_largeeta->Draw("ALP");
      gr_ntrack_data->SetLineColor(kRed);
      gr_ntrack_data->SetMarkerColor(kRed);
      gr_ntrack_data->Draw("LP");
      gr_ntrack_largeeta->SetMarkerStyle(kFullSquare);
      gr_ntrack->Draw("LP");
      gr_ntrack_largeeta->Draw("LP");
      gr_ntrack_data_largeeta->SetLineColor(kRed);
      gr_ntrack_data_largeeta->SetMarkerColor(kRed);
      
      TLegendEntry *entry;
      TLegend* leg = new TLegend(0.6,0.7,0.9,0.9);
      leg->SetFillColor(0);
      leg->SetBorderSize(0);

      entry = leg->AddEntry(gr_ntrack,"MC Pythia |#eta|<1.2","LP");
      entry = leg->AddEntry(gr_ntrack_largeeta,"MC Pythia |#eta|>1.2","LP");
      entry = leg->AddEntry(gr_ntrack_data,"Run 153565 |#eta|<1.2","LP");
      entry = leg->AddEntry(gr_ntrack_data_largeeta,"Run 153565 |#eta|>1.2","LP");
      leg->Draw();


      TString saveName = outDir + "h_frac_zero_tracks_vs_jetpt.png";
      saveName.ReplaceAll(dir,"");
      c11->SaveAs(saveName.Data());
      
      


   }




   
   if( do_ip_fit ) {
      ///+++++++++++++++++++++++++++++++++++++++++++++
      /// Fit the IP distributions
      /// Bins of: eta,pT
      ///+++++++++++++++++++++++++++++++++++++++++++++
      
      //gStyle->SetDrawOption("hist");
      ///-------------------------------------------
      
      TFile *outfile_ipfit = new TFile((const char*)(TString(outDir + outputname + "jetprob-neg-ip-fit.root")),"UPDATE");
      
      std::ofstream output_ipfit_fs(TString(outDir + outputname + "jetprob-neg-ip-fit.dat").Data());
      

      Int_t numberFiles = 1;
      fileNames[0] = dir + "jCOMB.exttrgmc008.root";        
      fileNames[0] = dir + "tt.exttrgmc008.root";        
      //fileNames[0] = dir + "data153565.exttrg003.root";        
      ///-------------------------------------------
      TString plotNamesLegend[60];
      TString plotNamesLabel[60];
      ///-------------------------------------------      
      const int N_pt_bins = 3;
      const double pt_bins[N_pt_bins] = {60.,120.,999.9};
      const int N_eta_bins = 4;
      const double eta_bins[N_eta_bins] = {1.0,2.0,2.5,999.9};
      const int N_si_hits_bins = 3;
      TString siHitsLabel[N_si_hits_bins] = {"","<7 Si hits","#geq7 Si hits"};
      int c=0;
      for(int isihit=0;isihit!=N_si_hits_bins;++isihit) {
         for(int ipt=0;ipt!=N_pt_bins;++ipt) {
            for(int ieta=0;ieta!=N_eta_bins;++ieta) {
               if(ieta==1 || ieta==(N_eta_bins-1)) continue; //remove invalidate bins with no entries...
               cout << ipt << "," << ieta << endl;
               //Set label on plot
               TString ptbinlabel,ptbinlegend;
               TString etabinlabel,etabinlegend;

               if(ieta==0) {
                  etabinlabel = TString::Format("jet |#eta|<2.5");
               } else if(ieta==1) {
                  etabinlabel = TString::Format("jet |#eta|<%.1f",eta_bins[ieta-1]);
               } else {
                  etabinlabel = TString::Format("%.1f<jet |#eta|<%.1f",eta_bins[ieta-2],eta_bins[ieta-1]);
               }

               if(ipt==0) {
                  ptbinlabel = TString::Format("jet p_{T}>20 GeV");
               } else if(ipt==1) {
                  ptbinlabel = TString::Format("jet p_{T}<%.1f GeV",pt_bins[ipt-1]);
               } else {
                  ptbinlabel = TString::Format("%.1f<jet p_{T}<%.1f GeV",pt_bins[ipt-2],pt_bins[ipt-1]);
               }
               
               TString ptetabinlabel = TString::Format("#splitline{%s}{%s}",ptbinlabel.Data(),etabinlabel.Data());
               TString ptetabinlegend = TString::Format("%s,%s",ptbinlabel.Data(),etabinlabel.Data());
               
//                if(ieta>1 && ipt>1) {
//                   double etalow =  eta_bins[ieta-1];
//                   double etahigh = eta_bins[ieta];
//                   double ptlow =  pt_bins[ipt-1];
//                   double pthigh = pt_bins[ipt];                  
//                   ptetabinlabel = TString::Format("#splitline{%.1f< jet |#eta|<%.1f}{%.1f< jet p_{T}<%.1f GeV}",etalow,etahigh,ptlow,pthigh);
//                   ptetabinlegend = TString::Format("%.1f< jet |#eta|<%.1f, %.1f< jet p_{T}<%.1f GeV",etalow,etahigh,ptlow,pthigh);
//                } else if(ieta=1 && ipt=1) {
//                   double etalow =  eta_bins[ieta-1];
//                   double etahigh = eta_bins[ieta];
//                   double ptlow =  pt_bins[ipt-1];
//                   double pthigh = pt_bins[ipt];                  
//                   ptetabinlabel = TString::Format("#splitline{%.1f< jet |#eta|<%.1f}{%.1f< jet p_{T}<%.1f GeV}",etalow,etahigh,ptlow,pthigh);
//                   ptetabinlegend = TString::Format("%.1f< jet |#eta|<%.1f, %.1f< jet p_{T}<%.1f GeV",etalow,etahigh,ptlow,pthigh);
//                } else if (ieta>=1 && ipt==0) {
//                   double etalow =  eta_bins[ieta-1];
//                   double etahigh = eta_bins[ieta];
//                   ptetabinlabel = TString::Format("%.1f< jet |#eta|<%.1f",etalow,etahigh);
//                   ptetabinlegend = ptetabinlabel;
//                } else if (ieta==0 && ipt>=1) {
//                   double ptlow =  pt_bins[ipt-1];
//                   double pthigh = pt_bins[ipt];
//                   ptetabinlabel = TString::Format("%.1f< jet p_{T}<%.1f GeV",ptlow,pthigh);
//                   ptetabinlegend = ptetabinlabel;
//                } else {
//                   ptetabinlabel = "#splitline{jet p_{T}>20 GeV}{jet |#eta|<2.5}";                              
//                   ptetabinlegend = "jet p_{T}>20 GeV, jet |#eta|<2.5";                              
//                }
               
               if(siHitsLabel[isihit]=="") {                  
                  plotNamesLabel[c] = ptetabinlabel;
                  plotNamesLegend[c] = ptetabinlegend;
               } else {
                  plotNamesLabel[c] = TString::Format("#splitline{%s}{%s}",ptetabinlabel.Data(),siHitsLabel[isihit].Data());
                  plotNamesLegend[c] = TString::Format("%s,%s",ptetabinlegend.Data(),siHitsLabel[isihit].Data());
               }
               TString jm_str;
               jm_str.Form("jm%ie%ic%i",ipt,ieta,isihit);         
               cout << "Looking at jet match string : " << jm_str << endl;
               plotNames[c++] = TString::Format("%stracklipsignneg",jm_str.Data());
            }
         }
      }
      
      int NumberPlots = c;        
      ///-------------------------------------------      
      int NumberSelections = 0;
      //selection[NumberSelections++] = baseName + "L1_J10";
      //selection[NumberSelections++] = baseName + "dj";
      //selection[NumberSelections++] = baseName + "L1_J10djdphi27";
      selection[NumberSelections++] = baseName + "truth_L1_J10offjet";
      //selection[NumberSelections++] = baseName + "truthoffjet";
      ///-------------------------------------------      
      TLegendEntry *entry;
      TLegend* leg = new TLegend(0.2,0.2,0.5,0.3);
      leg->SetFillColor(0);
      leg->SetBorderSize(0);
      TCanvas *c11 = (TCanvas*)gROOT->FindObject("c11");
      if (c11) {c11->Clear();} 
      else {
         c11 = new TCanvas("c11","c11");
      }
      c11->Clear();            

      TCanvas *c111 = (TCanvas*)gROOT->FindObject("c111");
      if (c111) {c111->Clear();} 
      else {
         c111 = new TCanvas("c111","c111");
      }
      c111->Clear();            
      TLegend* leg111 = new TLegend(0.2,0.45,0.7,0.85);
      leg111->SetFillStyle(0);
      leg111->SetFillColor(0);
      leg111->SetBorderSize(0);
      
      
      for(int ifile=0;ifile!=numberFiles;++ifile) {        
         
         cout << "---------------------------------------------" << endl;
         cout << "Plot all distributions for file: " << fileNames[ifile] << endl;
         
         
         for(int iselection=0;iselection!=NumberSelections;++iselection) {       
            
            cout << "and selection: " << selection[iselection] << endl;
            
            for(int ilog=1;ilog!=2;++ilog) {
               bool logx=false;
               bool logy=false;
               TString logAddOn;
               if(ilog==1) {logy=true;  logAddOn="logy";cout << "inlogAddon=" << logAddOn << endl; }
               else if(ilog==2) {logx=true; logAddOn="logx";cout << "inlogAddon=" << logAddOn << endl; }
               else {logAddOn="";}
               
               //make the plotnames
               TString fullPlotNames[60];
               for(int iplot=0;iplot!=NumberPlots;++iplot) {                 
                  fullPlotNames[iplot] = selection[iselection] + "_" + plotNames[iplot];
               }
               TString saveName = fileNames[ifile] + "_" + outputname+ "_" + selection[iselection]+"_"+logAddOn;       
               saveName.ReplaceAll(".","_");
               saveName.ReplaceAll("/","");
               saveName.ReplaceAll("__","");
               
               
               //jetAlgs->SetRebin(10);
               jetAlgs->makeCombinedPlots(fileNames[ifile],
                                          fullPlotNames,
                                          plotNamesLegend,
                                          NumberPlots,
                                          plotNames[iplot],
                                          "Entries",
                                          saveName,-1,-1,
                                          true,
                                          logx,logy,-1,-1,
                                          false,"hist");
               
            }//ilog

            
//             TCanvas *c11 = (TCanvas*)gROOT->FindObject("c11");
//             if (c11) {c11->Clear();} 
//             else {
//                Utils::style();
//                c11 = (TCanvas*)gROOT->FindObject("c11");
//             }
//             c11->Clear();
//             c11->cd();
//             c11->SetLogy();
            
            
            cout << "----------------------------------------------" << endl;
            cout << "Start the fit for total of " << NumberPlots << " plots" << endl;
            
            TF1* f_inclusive = 0;


            for(int iplot=0;iplot!=NumberPlots;++iplot) {                 
               
               cout << "Start the IP fit for file " << fileNames[ifile] << endl;
               
               TH1F* h = jetAlgs->FindObjectInFile(fileNames[ifile],fullPlotNames[iplot]);
               //h->Scale(1./h->Integral());
               //h->Rebin(2);
               h->SetFillStyle(1001);
               h->SetFillColor(kYellow);
               
               TString fnc_name = fullPlotNames[iplot] + "_fit";  
               //TF1* f = jetAlgs->Get_f_ip(h,fnc_name,-12.,-1.0.);
               //TF1* f = jetAlgs->Get_f_ip_twogaus(h,fnc_name,-11.,0.);
               //TF1* f = jetAlgs->Get_f_ip_twogaus(h,fnc_name,-11.,0., 0., 1000000., -4., 15., 200000, 0.,1.);
               //TF1* f = jetAlgs->Get_f_ip_twogaus(h,fnc_name,-11.,0., -1., 1000., 0., 3., 10000, 0.,10.,true);
               TF1* f = jetAlgs->Get_f_ip_twogaus(h,fnc_name,-11.,0., 0., 10., 0., 4., 400, 0.,1.,true);

               outfile_ipfit->cd();
               f->Write();
               output_ipfit_fs << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" <<endl;
               output_ipfit_fs << "Cumulative fit parameters for neg. IP fit: " << plotNamesLegend[iplot] << endl;
               for(int ip=0;ip!=f->GetNpar();++ip) {
                  output_ipfit_fs << "p"<<ip<<": " << f->GetParameter(ip) << endl;
               }               
               output_ipfit_fs << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" <<endl;
               
               

               TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
               if (c1) {c1->Clear();} 
               else {
                  Utils::style();
                  c1 = (TCanvas*)gROOT->FindObject("c1");
               }
               c1->Clear();               
               c1->cd();
               h->Draw("hist");
               f->SetLineColor(kRed);
               f->Draw("l,same");
               c1->cd();
               Utils::myText(0.7,0.21,plotNamesLabel[iplot],0.03);  
               //Utils::myText(0.3,0.18,plotNamesLabel[iplot]);  
               gStyle->SetStatX(0.45);
               gStyle->SetStatY(0.9);
               
               saveName = outDir + fileNames[ifile] + "_" + outputname + "_" + fullPlotNames[iplot] + "_fit.png";
               saveName.ReplaceAll(dir,"");
               saveName.ReplaceAll(".root","");
               saveName.ReplaceAll(".exttrgmc008","_exttrgmc008_");
               c1->SaveAs(saveName);
               
               //Get the cumulative parameters
               fnc_name = fullPlotNames[iplot] + "_cumulative_derived";                 
               TF1* f_cumul_direct = jetAlgs->Get_f_ip_direct(f,fnc_name,-15.,-0.);
               
               
               //Draw the result
               //save the direct derived cumulative
               c1 = (TCanvas*)gROOT->FindObject("c1");
               if (c1) {c1->Clear();} 
               else {
                  Utils::style();
                  c1 = (TCanvas*)gROOT->FindObject("c1");
               }
               c1->Clear();               
               c1->cd();
               f_cumul_direct->SetLineColor(kRed);
               f_cumul_direct->Draw("l");
               c1->cd();
               Utils::myText(0.7,0.21,plotNamesLabel[iplot],0.03);  
               //Utils::myText(0.3,0.18,plotNamesLabel[iplot]);  
               gStyle->SetStatX(0.45);
               gStyle->SetStatY(0.9);
               
               saveName = outDir + fileNames[ifile] + "_" + outputname + "_" + fullPlotNames[iplot] + "_fit_direct.png";
               saveName.ReplaceAll(dir,"");
               saveName.ReplaceAll(".root","");
               saveName.ReplaceAll(".exttrgmc008","_exttrgmc008_");
               c1->SaveAs(saveName);
               
               c11->cd();
               if(h->GetEntries()>0) {
                  TH1F* htmp;
                  if(iplot==0) htmp = (TH1F*) h->DrawNormalized("hist");
                  else htmp = (TH1F*) h->DrawNormalized("hist,same");
                  htmp->SetFillStyle(0);
               }
               
               c111->cd();
               if(iplot==0) {
                  TH2F* hframe = new TH2F("hframe_ip_cumul_direct",";Signed impact parameter significance;Arbitrary units",100,-16.,0.,100,f_cumul_direct->GetMinimum(-15.,0.),1.0);
                  hframe->SetStats(false);
                  hframe->Draw();
                  
               }
               f_cumul_direct->SetLineColor(iplot+1);
               f_cumul_direct->SetLineStyle(iplot%2==2);
               f_cumul_direct->Draw("L,same");
               leg111->AddEntry(f_cumul_direct,plotNamesLegend[iplot],"L");
               
               
               if(iplot==0) f_inclusive = f;
               
            } //iplot
            
         }//iselection
         
         
         c11->cd();
         //f_inclusive->Draw("same");
         TString saveName = outDir + fileNames[ifile] + "_" + outputname+ "_" + "_compare_ip.png";
         saveName.ReplaceAll(dir,"");
         saveName.ReplaceAll(".root","");
         saveName.ReplaceAll(".exttrgmc008","_exttrgmc008_");
         c11->SetLogy(true);
         c11->SaveAs(saveName);

         c111->cd();
         leg111->Draw();
         //f_inclusive->Draw("same");
         TString saveName = outDir + fileNames[ifile] + "_" + outputname+ "_" + "_compare_ip_cumul_direct.png";
         saveName.ReplaceAll(dir,"");
         saveName.ReplaceAll(".root","");
         saveName.ReplaceAll(".exttrgmc008","_exttrgmc008_");
         c111->SetLogy(true);
         c111->SaveAs(saveName);
         


         outfile_ipfit->Close();
         output_ipfit_fs.close();

//          TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
//          if (c1) {c1->Clear();} 
//          else {
//             Utils::style();
//             c1 = (TCanvas*)gROOT->FindObject("c1");
//          }
//          c1->Clear();
//          c1->cd();
         
//          TString saveName = outDir +fileNames[ifile].ReplaceAll(dir,"") + ".frac_acc_bsshiftX.png";
//          cout << "save as: " << saveName << endl;
//          c1->SaveAs(saveName);
         
//          entry = leg->AddEntry(gr_bs_frac_acc,fileNames[ifile].ReplaceAll(dir,""),"LP");
         
      } //ifile
      
      //leg->Draw();
      //TString saveName = outDir + "frac_acc_bsshiftX_samplecmp.png";
      //c11->SaveAs(saveName);
      
      
     
      
   }//do_ip_fit
   




 
}
