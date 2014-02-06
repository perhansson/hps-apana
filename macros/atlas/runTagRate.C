void runTagRate() 
{
  ///-------------------------------------------------------------------------
  /// Compile everything
  ///-------------------------------------------------------------------------  
   gSystem->Load("libPhysics.so");
   gSystem->CompileMacro ("style.cpp", "k");
   gSystem->CompileMacro ("Util.cpp", "k");
   gSystem->CompileMacro ("rootlogonCompile.h", "k");
   //gSystem->CompileMacro ("SlimJetMetbTriggerTree.C", "k");
   gSystem->CompileMacro ("JetMetbTagAnalysisBase.cxx", "k");
   //gSystem->CompileMacro ("JetMetbTagAnalysis.cxx", "k");
   //gSystem->CompileMacro ("GetTChainFromDirectory.C","k");
   
   gROOT->SetStyle("ATLAS");
   gROOT->ForceStyle();
   
   
   
  ///-------------------------------------------------------------------------
  /// Switch on or off analyses
  ///-------------------------------------------------------------------------
  
   bool do_tagrate          = 1;

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
   TString rootFile    = "TagRates_final.root";
   if (multi) rootFile    = "TagRates_final_multi.root";
   TString outfilename = outDir + rootFile;
   //TString dir         = "../topologies/jetmetbtag/files/180510/";
   //TString dir         = "../topologies/jetmetbtag/files/200510_2/";
   TString dir         = "../topologies/jetmetbtag/files/290510/";
   //TString dir         = "../topologies/jetmetbtag/files/190510_all/";
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
   TString plotNames1[50];
   TString plotNames2[50];
   TString fileNames[50];
   TString selection[50];
   TString legend[50];             
   
   Int_t NumberPlots = 0;
   Int_t NumberSelections = 0;

   //TString baseName    = "l2rate";
   TString baseName    = "jetmetbtag";
   
   if( do_tagrate) {
      
      ///-------------------------------------------      
      Int_t numberFiles = 3;
      fileNames[0] = dir + "jCOMB.trg002.root";        
      //fileNames[1] = dir + "tt.trg002.root";
      fileNames[1] = dir + "jaCOMB.trg002.root";        
      //fileNames[3] = dir + "wbbCOMB.trg002.root";        
      //fileNames[2] = dir + "bbbarCOMB.trg002.root";        
      fileNames[2] = dir + "qcdCOMB.trg002.root";        
      //fileNames[4] = dir + "wlCOMB.trg002.root";        
      //fileNames[5] = dir + "zllCOMB.trg002.root";        
      //fileNames[9] = dir + "we.trg001.root";        
      ///fileNames[4] = dir + "wm.trg001.root";        
     //fileNames[5] = dir + "wt.trg001.root";        
     //fileNames[6] = dir + "zee.trg001.root";        
     //fileNames[7] = dir + "zmm.trg001.root";        
     //fileNames[4] = dir + "ztt.trg001.root";        
     //fileNames[5] = dir + "st.trg001.root";        
      ///-------------------------------------------
      legend[0] = "Pythia J0-6";  
      legend[1] = "QCD(light) Alpgen";  
      legend[2] = "QCD Alpgen";  
      //legend[2] = "W#rightarrowl#nub#bar{b}";  
      //legend[4] = "W#rightarrowl#nu";  
      //legend[5] = "Z#rightarrowl#bar{l}";  
      //legend[3] = "W#rightarrowe";  
      //legend[4] = "W#rightarrow#mu";  
      //legend[5] = "W#rightarrow#tau";  
      //legend[6] = "Z#rightarrowee";  
      //legend[7] = "Z#rightarrow#mu#mu";  
      //legend[4] = "Z#rightarrow#tau#tau";  
      //legend[5] = "Single top";  
      NumberPlots = 7;  
      
//       plotNames1[0] = "tagraterecotaggedpt";
//       plotNames2[0] = "tagraterecopt";
//       plotNames1[1] = "tagraterecotaggedeta";
//       plotNames2[1] = "tagraterecoeta";

      plotNames1[0] = "tagraterecotaggedpt";
      plotNames2[0] = "tagraterecopt";
      plotNames1[1] = "tagratedphirecotaggedpt";
      plotNames2[1] = "tagratedphirecopt";
      plotNames1[2] = "tagratedphiirecotaggedpt";
      plotNames2[2] = "tagratedphiirecopt";
      plotNames1[3] = "tagraterecotaggedeta";
      plotNames2[3] = "tagraterecoeta";
      plotNames1[4] = "tagratedphirecotaggedeta";
      plotNames2[4] = "tagratedphirecoeta";
      plotNames1[5] = "tagratedphiirecotaggedeta";
      plotNames2[5] = "tagratedphiirecoeta";
      plotNames1[6] = "tagraterecotaggeddphi";
      plotNames2[6] = "tagraterecodphi";

      
      ///-------------------------------------------
      
      NumberSelections = 1;
      //selection[1] = baseName;
      //selection[0] = baseName + "4j3j40met400ldphi0inv";
      selection[0] = baseName + "4j3j40met400ldphi1inv";
      ///-------------------------------------------
      
     for(int iplot=0;iplot!=NumberPlots;++iplot) {
        for(int iselection=0;iselection!=NumberSelections;++iselection) {
           
           TString plotNameNum = selection[iselection] + "_" + plotNames1[iplot];       
           TString plotNameDen = selection[iselection] + "_" + plotNames2[iplot];                  
           cout << "Num: " << plotNameNum << endl;
           cout << "Den: " << plotNameDen << endl;
           TString saveName = selection[iselection] + "_" + plotNameNum + "_tagrate";
           
           
           jetAlgs_ttbar->SetRebin(10);
           jetAlgs_ttbar->makeRatioPlotsPelle(fileNames, 
                                              plotNameNum, 
                                              plotNameDen, 
                                              legend, 
                                              numberFiles, 
                                              plotNameNum,
                                              "Tag rate",
                                              saveName,
                                              -1,-1,
                                              false,false,
                                              -1,-1,
                                              false);
           
        }
     }
   }
  
    
  
}
