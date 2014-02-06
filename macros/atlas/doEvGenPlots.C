void doEvGenPlots()
{
  ///-------------------------------------------------------------------------
  /// Compile everything
  ///-------------------------------------------------------------------------  
   gSystem->Load("libPhysics.so");
   gSystem->CompileMacro ("style.cpp", "k");
   gSystem->CompileMacro ("old/Util.cpp", "k");
   gSystem->CompileMacro ("old/rootlogonCompile.h", "k");
   //gSystem->CompileMacro ("SlimJetMetbTriggerTree.C", "k");
   gSystem->CompileMacro ("JetMetbTagAnalysisBase.cxx", "k");
   //gSystem->CompileMacro ("JetMetbTagAnalysis.cxx", "k");
   //gSystem->CompileMacro ("GetTChainFromDirectory.C","k");
   
   gROOT->SetStyle("ATLAS");
   gROOT->ForceStyle();
   
   
   
  ///-------------------------------------------------------------------------
  /// Switch on or off analyses
  ///-------------------------------------------------------------------------
  
   bool do_fileComparison          = 1;
   bool do_selectionComparison     = 0;
   bool do_plotComparison          = 0;
 
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
   TString rootFile    = "outputfile_final.root";
   TString outfilename = outDir + rootFile;
   TString dir         = "../topologies/dataMC/files/";
   TString savePrefix = "comboMsplit300-BKG";
   TString tag_ttbar   = "final";
   
   bool doBKG = true; 
   //bool doBKG = false;

   /// Setup analysis
   JetMetbTagAnalysisBase *jetAlgs = new JetMetbTagAnalysisBase(0,verbose);
   jetAlgs->SetPlotTypeAndLumi(plotType,tag_ttbar);
   jetAlgs->SetOutputDirectory(outDir);
   jetAlgs->SetOutputRootFile(rootFile);
   
   
   
   ///+++++++++++++++++++++++++++++++++++++++++++++
   /// Generic plots stuff
   ///+++++++++++++++++++++++++++++++++++++++++++++
   TLegendEntry *entry;
   TString plotNames[50];
   TString fileNames[50];
   TString selection[50];
   TString legend[50];             
   
   Int_t NumberPlots = 0;
   Int_t NumberSelections = 0;

   TString baseName    = "l2rate";
   //TString baseName    = "jetmetbtag";
   //TString baseName    = "l2btag";
   
   
   
   
   if( do_fileComparison) { 
      ///+++++++++++++++++++++++++++++++++++++++++++++
      /// Combined plots
      ///+++++++++++++++++++++++++++++++++++++++++++++
      
      
      ///------------------------------------------      
      Int_t numberFiles = 0;
      
      if(doBKG)
	{
	  fileNames[numberFiles++] = dir + "jnewCOMB.com002.root";
	  fileNames[numberFiles++] = dir + "tt.trg004.root";      
	  //fileNames[numberFiles++] = dir + "su4.trg002.root";
	}
      //fileNames[numberFiles++] = dir + "py2bB300L200.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB300L100.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB300L60.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB400L300.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB400L200.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB400L100.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB400L60.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB500L400.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB500L300.tru002.root";
      fileNames[numberFiles++] = dir + "py2bB500L200.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB500L100.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB500L60.tru002.root";
      
      //fileNames[numberFiles++] = dir + "py4bG300L200.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG300L100.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG300L60.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG400L300.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG400L200.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG400L100.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG400L60.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG500L400.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG500L300.tru002.root";
      fileNames[numberFiles++] = dir + "py4bG500L200.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG500L100.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG500L60.tru002.root";
      
      //fileNames[numberFiles++] = dir + "py4tbG300L100.tru002.root";
      //fileNames[numberFiles++] = dir + "py4tbG300L60.tru002.root";
      //fileNames[numberFiles++] = dir + "py4tbG400L200.tru002.root";
      //fileNames[numberFiles++] = dir + "py4tbG400L100.tru002.root";
      //fileNames[numberFiles++] = dir + "py4tbG400L60.tru002.root";
      fileNames[numberFiles++] = dir + "py4tbG500L200.tru002.root";
      //fileNames[numberFiles++] = dir + "py4tbG500L100.tru002.root";
      //fileNames[numberFiles++] = dir + "py4tbG500L60.tru002.root";


      //fileNames[numberFiles++] = dir + "tt.trg004.root";
      //fileNames[numberFiles++] = dir + "jnewCOMB.com002.root";

      //
      for(int il=0;il!=numberFiles;++il) {
         legend[il] = fileNames[il];
         legend[il].ReplaceAll(".tru002.root","");
         legend[il].ReplaceAll(".trg002.root","");
         legend[il].ReplaceAll(dir,"");
      }
      //legend[0] = "QCD (J0-J2)";
      //legend[1] = "153565";
      //legend[1] = "t#bar{t} #rightarrow l+jets";

     ///-------------------------------------------
     NumberPlots = 0;  

     //plotNames[NumberPlots++] = "jpt";
     plotNames[NumberPlots++] = "j0pt";
     plotNames[NumberPlots++] = "j1pt";
     plotNames[NumberPlots++] = "j2pt";
     plotNames[NumberPlots++] = "j3pt";
     plotNames[NumberPlots++] = "j0eta";
     plotNames[NumberPlots++] = "j1eta";
     plotNames[NumberPlots++] = "ht";
     plotNames[NumberPlots++] = "J0pt";
     plotNames[NumberPlots++] = "J1pt";
     //      plotNames[5] = "ne";
     //      plotNames[6] = "nm";
     //      plotNames[7] = "nl";    
     plotNames[NumberPlots++] = "nj";    
     //plotNames[2] = "jeta";    
     //plotNames[10] = "jflavor";    
     //plotNames[11] = "jflavorman";    
     //      plotNames[11] = "jeta";
     plotNames[NumberPlots++] = "met";    
     plotNames[NumberPlots++] = "Met";    
     //      plotNames[14] = "nbtag";    
     plotNames[15] = "dphij1j0";
     //      plotNames[16] = "dphij2j0";
     //      plotNames[17] = "dphij2j1";
     //      plotNames[19] = "bjbtagrank";
     //      plotNames[20] = "bjrank";
     //      plotNames[21] = "cjrank";
     //      plotNames[22] = "ljrank";
     plotNames[NumberPlots++] = "nbj";
     plotNames[NumberPlots++] = "E2ratio";
     plotNames[NumberPlots++] = "Pt2ratio";
     plotNames[NumberPlots++] = "maxBJdr";
     plotNames[NumberPlots++] = "minBJdr";
     //plotNames[NumberPlots++] = "bjpt";
     plotNames[NumberPlots++] = "MetMhtAsy";


     //      plotNames[10] = "ncj";
     //      plotNames[11] = "nlj";
     //if(!doBKG)
      plotNames[NumberPlots++] = "bj0pt";
      plotNames[NumberPlots++] = "bj1pt";
      plotNames[NumberPlots++] = "Bj0pt";
      plotNames[NumberPlots++] = "Bj1pt";
      plotNames[NumberPlots++] = "bj2pt";
      plotNames[NumberPlots++] = "bj3pt";
      plotNames[NumberPlots++] = "bj0eta";
      plotNames[NumberPlots++] = "bj1eta";
     
     //plotNames[NumberPlots++] = "bj2eta";
     //plotNames[NumberPlots++] = "bj3eta";
     
     plotNames[NumberPlots++] = "meff4";
      //      plotNames[13] = "bjeta";
      //     plotNames[0] = "dphij0met";
      //     plotNames[1] = "dphij1met";
      //     plotNames[2] = "dphij2met";
      //     plotNames[3] = "dphij3met";
      //     plotNames[4] = "dphibj0met";
      //     plotNames[5] = "dphibj1met";
      //      plotNames[5] = "htasym";
      //      plotNames[6] = "dphijetsmet";
      //      plotNames[7] = "dphiptmet";
      //      plotNames[8] = "sumtrackpt";
      //      plotNames[9] = "mettrackpt";
      //      plotNames[14] = "htmet";
      //      plotNames[31] = "mj1j0";
      //plotNames[NumberPlots++] = "drbj1bj0";
      //plotNames[NumberPlots++] = "drbj2bj1";
      //plotNames[NumberPlots++] = "drbj3bj1";
      //plotNames[NumberPlots++] = "drbj3bj0";
      //plotNames[NumberPlots++] = "drbj3bj2";
     
     //if(!doBKG)
       plotNames[NumberPlots++] = "dphibj1bj0";
     
      //       plotNames[NumberPlots++] = "dphibj2bj1";
      //       plotNames[NumberPlots++] = "dphibj3bj1";
      //       plotNames[NumberPlots++] = "dphibj3bj0";
      //       plotNames[NumberPlots++] = "dphibj3bj2";
      //      plotNames[34] = "bjbhadcount4";
      //      plotNames[35] = "sph";
      

     ///-------------------------------------------
     
     NumberSelections = 1;
     //selection[0] = baseName;
     //selection[1] = baseName + "ljetslveto";
      selection[0] = baseName + "_truth";
     //selection[1] = baseName + "truth_4j";
     ///-------------------------------------------
     
     for(int iplot=0;iplot!=NumberPlots;++iplot) {
        for(int iselection=0;iselection!=NumberSelections;++iselection) {
           for(int ilog=0;ilog!=2;++ilog) {
             //dans note i turned off logX scale by replace 3 with a 2 above 
	     bool logx=false;
              bool logy=false;
              TString logAddOn;
              if(ilog==1) {logy=true;  logAddOn="logy";cout << "inlogAddon=" << logAddOn << endl; }
              else if(ilog==2) {logx=true; logAddOn="logx";cout << "inlogAddon=" << logAddOn << endl; }
              else {logAddOn="";}
              TString plotName = selection[iselection] + "_" + plotNames[iplot];       
              TString saveName = savePrefix + "_" + selection[iselection] + "_" + plotNames[iplot] + "_" + logAddOn;       
              //saveName += "_"; saveName += logAddOn;
              
              //jetAlgs->SetRebin(2);
//               jetAlgs->makeCombinedFilePlots(fileNames,
//                                                    plotName,
//                                                    legend,
//                                                    numberFiles,
//                                                    plotNames[iplot],
//                                                    "Entries",
//                                                    saveName,-1,-1,
//                                                    true,
//                                                    logx,logy,-1,-1,
//                                                    false,"hist",1);

               bool drawStats = false;
               bool drawExtra = false;
               bool writeFile = true;
               bool dataMCCompare = false;
               bool dataMCRatio = false;
               TString xAxis = plotNames[iplot];
               TString yAxis = "Entries";
               Float_t YMin = -1;
               Float_t YMax = -1;
               Float_t XMin = -1;
               Float_t XMax = -1;
               bool drawNorm = true;
               TString newLabel = "";
               bool plotMore = false;
               bool lineOnly = true;
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
  
 
}
