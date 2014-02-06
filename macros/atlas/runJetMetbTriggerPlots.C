
void runJetMetbTriggerPlots(TString outputname="")
{
  ///-------------------------------------------------------------------------
  /// Compile everything
  ///-------------------------------------------------------------------------  
   gSystem->Load("libPhysics.so");
   gSystem->CompileMacro ("style.cpp", "k");
   gSystem->CompileMacro ("../../..//RootUtils/trunk/Util.cpp","k");
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
  
   bool do_fileComparison          = 0;
   bool do_selectionComparison     = 0;
   bool do_plotComparison          = 1;
 
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
   //TString dir         = "../topologies/jetmetbtag/files/290410/";
   //TString dir         = "../topologies/jetmetbtag/files/200510_2/";
   //TString dir         = "../topologies/jetmetbtag/files/270510/";
//   TString dir         = "../topologies/jetmetbtag/files/190510_all/";
//   TString dir         = "../topologies/jetmetbtag/files/010610_trigrates_alpgen_pythia/";
//   TString dir         = "../topologies/jetmetbtag/files/truth_070610/";
   //TString dir         = "../topologies/jetmetbtag/files/100720_full/";
//   TString dir         = "../topologies/jetmetbtag/files/100727_l2rate/";
//   TString dir         = "../topologies/jetmetbtag/files/100806_jetmetbtag/";
//   TString dir         = "../topologies/jetmetbtag/files/truth_simplsusy_100625/";
   //TString dir         = "TagRates/290510/";
   //TString dir         = "../topologies/jetmetbtag/files/100818_l2menu/";
   TString dir         = "../topologies/jetmetbtag/files/100914_l2menu/";
   //TString dir         = "../topologies/jetmetbtag/files/100922_l2btag/";
   TString tag_ttbar   = "final";
   
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
   
   
   
   if( do_selectionComparison ) {
      ///+++++++++++++++++++++++++++++++++++++++++++++
      /// Standard plots for different samples
      ///+++++++++++++++++++++++++++++++++++++++++++++
      
      //gStyle->SetDrawOption("hist");
     ///-------------------------------------------
      Int_t numberFiles = 4;
      fileNames[0] = dir + "jCOMB.trg002.root";        
      fileNames[1] = dir + "tt.trg002.root";
//      fileNames[2] = dir + "pyt2b.tru001.root";        
//      fileNames[3] = dir + "pyt4b.tru001.root";        
//      fileNames[4] = dir + "pyts2b.tru001.root";        
      fileNames[5] = dir + "su4.trg002.root";        
      fileNames[1] = dir + "bbCOMB.trg002.root";        
      fileNames[2] = dir + "jaCOMB.trg002.root";    
      fileNames[3] = dir + "qcdCOMB.trg002.root";    
      //fileNames[3] = dir + "wbbCOMB.trg002.root";        
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
     NumberPlots = 18;  
     //plotNames[2] = "ljl2ip3d";
     //plotNames[1] = "bjl2ip3d";
     plotNames[0] = "Jpt";
     plotNames[1] = "jeta";
     plotNames[2] = "j0pt";
     plotNames[3] = "j1pt";
     plotNames[4] = "j2pt";
     plotNames[5] = "j3pt";
     plotNames[6] = "j4pt";
     plotNames[8] = "nj";    
     plotNames[9] = "Met";    
     plotNames[10] = "dphij0met";    
     plotNames[11] = "dphij1met";    
     plotNames[12] = "bjpt";    
     plotNames[13] = "nbj";    
     plotNames[14] = "dphibj0met";    
     plotNames[15] = "dphibj1met";    
     plotNames[16] = "dphibj1bj0";    
     plotNames[17] = "drbj1bj0";    

     NumberSelections = 1;
     selection[0] = baseName;
     //selection[0] = baseName + "4j3j40met400l";
     //selection[1] = baseName + "4j3j40met400ldphi";
     //selection[0] = baseName + "4j3j40met400ldphi1inv";
     ///-------------------------------------------
     legend[0] = "no cut";  
     //legend[1] = "#Delta #phi(jet_{1,2},#slash{E_{T}})>0.8 (pretag)";  
     //legend[0] = "#Delta #phi(jet_{1},#slash{E_{T}})<0.2";  
     ///-------------------------------------------
     
     for(int ifile=0;ifile!=numberFiles;++ifile) {        
        for(int iplot=0;iplot!=NumberPlots;++iplot) {
           for(int ilog=0;ilog!=1;++ilog) {
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
              saveName.ReplaceAll(".","-");
              saveName.ReplaceAll("/","");
              
//              jetAlgs->makeCombinedFilePlots(fileNames,plotName,legend,numberFiles,plotNames[iplot],"Entries",saveName,-1,-1,true);  
              
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
   
   
   
   
   
   if( do_fileComparison) { 
      ///+++++++++++++++++++++++++++++++++++++++++++++
      /// Combined plots
      ///+++++++++++++++++++++++++++++++++++++++++++++
      
      
      ///------------------------------------------      
      Int_t numberFiles = 0;      
      //fileNames[numberFiles++] = dir + "jCOMB.exttrgmc006.root";
      //legend[numberLegends++]  = "QCD";
      //fileNames[numberFiles++] = dir + "tt.exttrgmc006.root";
      //legend[numberLegends++]  = "t#bar{t} (T1)";
      //fileNames[numberFiles++] = dir + "su4.exttrgmc006.root";
      //legend[numberLegends++]  = "SU4";

      //fileNames[numberFiles++] = dir + "py2bB300L60.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB300L100.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB300L200.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB400L60.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB400L100.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB400L200.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB400L300.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB500L60.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB500L100.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB500L200.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB500L300.tru002.root";
      //fileNames[numberFiles++] = dir + "py2bB500L400.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG300L60.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG300L100.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG300L200.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG400L60.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG400L100.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG400L200.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG400L300.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG500L60.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG500L100.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG500L200.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG500L300.tru002.root";
      //fileNames[numberFiles++] = dir + "py4bG500L400.tru002.root";
//       fileNames[numberFiles++] = dir + "py4tbG300L60.tru002.root";
//       fileNames[numberFiles++] = dir + "py4tbG300L100.tru002.root";
//       fileNames[numberFiles++] = dir + "py4tbG400L60.tru002.root";
//       fileNames[numberFiles++] = dir + "py4tbG400L100.tru002.root";
//       fileNames[numberFiles++] = dir + "py4tbG400L200.tru002.root";
//       fileNames[numberFiles++] = dir + "py4tbG500L60.tru002.root";
//       fileNames[numberFiles++] = dir + "py4tbG500L100.tru002.root";
//       fileNames[numberFiles++] = dir + "py4tbG500L200.tru002.root";





      legend[numberFiles]  = "#tilde{g}#rightarrowb#bar{b}#Chi^{0}, #DeltaM(#tilde{g},#Chi^{0})=100GeV";
      //legend[numberFiles]  = "#tilde{g}#rightarrowb#bar{b}#Chi^{0}, M_{#tilde{g}}=400GeV,M_{#Chi^{0}}=300GeV";
      fileNames[numberFiles++] = dir + "py4bG400L300.exttrgmc106.root";

      legend[numberFiles]  = "#tilde{g}#rightarrowb#bar{b}#Chi^{0}, #DeltaM(#tilde{g},#Chi^{0})=300GeV";
      //legend[numberFiles]  = "#tilde{g}#rightarrowb#bar{b}#Chi^{0}, M_{#tilde{g}}=400GeV,M_{#Chi^{0}}=100GeV";
      fileNames[numberFiles++] = dir + "py4bG400L100.exttrgmc106.root";

      legend[numberFiles]  = "#tilde{b}#rightarrowb#Chi^{0}, #DeltaM(#tilde{b},#Chi^{0})=300GeV";
      //legend[numberFiles]  = "#tilde{b}#rightarrowb#Chi^{0}, M_{#tilde{b}}=400GeV,M_{#Chi^{0}}=100GeV";
      fileNames[numberFiles++] = dir + "py2bB400L100.exttrgmc106.root";

      legend[numberFiles]  = "#tilde{b}#rightarrowb#Chi^{0}, #DeltaM(#tilde{b},#Chi^{0})=100GeV";
      //legend[numberFiles]  = "#tilde{b}#rightarrowb#Chi^{0}, M_{#tilde{b}}=400GeV,M_{#Chi^{0}}=300GeV";
      fileNames[numberFiles++] = dir + "py2bB400L300.exttrgmc106.root";
    

      //fileNames[4] = dir + "py4tbG400L100.exttrgmc106.root";
      //fileNames[5] = dir + "py4tbG400L200.exttrgmc106.root";
      //fileNames[6] = dir + "py4tG500L100.exttrgmc106.root";
      //fileNames[7] = dir + "py4tG500L60.exttrgmc106.root";
      //fileNames[8] = dir + "su4.exttrgmc106.root";

      legend[numberFiles]  = "Pythia J2 QCD ";
      fileNames[numberFiles++] = dir + "j3.exttrgmc008.root";
      
      
      
//       fileNames[numberFiles++] = dir + "jCOMB.exttrgmc008.root";
//       legend[numberLegends++]  = "Pythia QCD";
//       //fileNames[numberFiles++] = dir + "jpu2.exttrgmc008.root";
//       //legend[numberLegends++]  = "Pythia J2 Pile-up QCD";
//       fileNames[numberFiles++] = dir + "tt.exttrgmc008.root";
//       legend[numberLegends++]  = "t#bar{t} QCD";

      //fileNames[1] = dir + "tt.trg002.root";
//       fileNames[4] = dir + "su4.trg002.root";
      //fileNames[1] = dir + "pyt4b.tru001.root";        
      //fileNames[2] = dir + "pyts2b.tru001.root";        
      //fileNames[3] = dir + "jCOMB.trg002.root";        
//     fileNames[5] = dir + "su4.trg002.root";        
      //fileNames[1] = dir + "bbCOMB.trg002.root";        
      //fileNames[5] = dir + "wbbCOMB.trg002.root";        
      //fileNames[2] = dir + "bbbarCOMB.trg002.root";        
      //fileNames[2] = dir + "jaCOMB.trg002.root";        
      //fileNames[3] = dir + "qcdCOMB.trg002.root";        
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
//       legend[0] = "J0";  
//       legend[1] = "J1";  
//       legend[2] = "J2";  
//       legend[3] = "J3";  
//       legend[4] = "J4";  
//       legend[5] = "J5";  
//       legend[6] = "J6";  
//       legend[0] = "ja22";  
//       legend[1] = "ja23";  
//       legend[2] = "ja24";  
//       legend[3] = "J3";  
//       legend[4] = "J4";  
//       legend[5] = "J5";  
//       legend[6] = "J6";  

//       for(int il=0;il!=numberFiles;++il) {
//          legend[il] = fileNames[il];
//          legend[il].ReplaceAll(".exttrgmc006.root","");
//          legend[il].ReplaceAll(".trg002.root","");
//          legend[il].ReplaceAll(dir,"");
//       }

      


      //legend[0] = "QCD (J0-J2)";
      //legend[1] = "153565";
      //legend[1] = "t#bar{t} #rightarrow l+jets";
//       legend[4] = "SU4";
//      legend[4] = "QCD Pythia J0-6";  
//      legend[0] = "Pythia sbottom pair (2b)";
//      legend[1] = "Pythia gluino pair (4b)";
//      legend[2] = "Pythia sbottom pair (2b) BR20%";
//     legend[5] = "SU4";  
      //legend[4] = "QCD(b#bar{b}) Alpgen";  
//      legend[5] = "W#rightarrowl#nub#bar{b}";  
     //legend[2] = "b#bar{b}+JX";  
//      legend[2] = "QCD(light) Alpgen";  
//      legend[3] = "QCD Alpgen";  
     //legend[4] = "Alpgen b#bar{b}+QCD";  
     //legend[4] = "W#rightarrowl#nu";  
     //legend[5] = "Z#rightarrowl#bar{l}";  
     //legend[3] = "W#rightarrowe";  
     //legend[4] = "W#rightarrow#mu";  
     //legend[5] = "W#rightarrow#tau";  
     //legend[6] = "Z#rightarrowee";  
     //legend[7] = "Z#rightarrow#mu#mu";  
     //legend[4] = "Z#rightarrow#tau#tau";  
     //legend[5] = "Single top";  
     ///-------------------------------------------
     NumberPlots = 0;  
     //plotNames[2] = "ljl2ip3d";
     //plotNames[1] = "bjl2ip3d";
//     plotNames[NumberPlots++] = "jpt";
//      plotNames[NumberPlots++] = "j0pt";
//      plotNames[NumberPlots++] = "j1pt";
//      plotNames[NumberPlots++] = "j2pt";
//      plotNames[NumberPlots++] = "j3pt";
//      plotNames[5] = "ne";
//      plotNames[6] = "nm";
//      plotNames[7] = "nl";    
//     plotNames[NumberPlots++] = "nj";    
     //plotNames[2] = "jeta";    
     //plotNames[10] = "jflavor";    
     //plotNames[11] = "jflavorman";    
//      plotNames[11] = "jeta";
     plotNames[NumberPlots++] = "jptpassJ10eff";
     plotNames[NumberPlots++] = "jptpassJ30eff";
//      plotNames[NumberPlots++] = "jm0e0c0tracklipsignneg";
//      plotNames[NumberPlots++] = "jm1e0c0tracklipsignneg";
//      plotNames[NumberPlots++] = "jm2e0c0tracklipsignneg";
//      plotNames[NumberPlots++] = "jm3e0c0tracklipsignneg";
//      plotNames[NumberPlots++] = "jm0e0c0tracklipsignneg";
//      plotNames[NumberPlots++] = "jm1e2c0tracklipsignneg";
//      plotNames[NumberPlots++] = "jm1e4c0tracklipsignneg";
//      plotNames[NumberPlots++] = "jm3e2c0tracklipsignneg";
//      plotNames[NumberPlots++] = "jm3e4c0tracklipsignneg";
//      plotNames[NumberPlots++] = "l2jetetsum";    
//      plotNames[NumberPlots++] = "l2jetetsumeta20";    
//      plotNames[NumberPlots++] = "l2jetetsumeta25";    
//      plotNames[NumberPlots++] = "l2jetetsumeta27";    
//      plotNames[NumberPlots++] = "l2jetetsumeta30";    
//      plotNames[NumberPlots++] = "l2jetetsumeta32";    
//      plotNames[NumberPlots++] = "l2jetetsumeta40";    
     //plotNames[NumberPlots++] = "l1met";    
     //plotNames[NumberPlots++] = "l2met";    
     //plotNames[NumberPlots++] = "met";    
     //plotNames[NumberPlots++] = "Met";    
     //plotNames[NumberPlots++] = "mht";    
     //plotNames[NumberPlots++] = "Mht";    
//     plotNames[NumberPlots++] = "nbtag";    
//      plotNames[15] = "dphij1j0";
//      plotNames[16] = "dphij2j0";
//      plotNames[17] = "dphij2j1";
//      plotNames[19] = "bjbtagrank";
//      plotNames[20] = "bjrank";
//      plotNames[21] = "cjrank";
//      plotNames[22] = "ljrank";
//     plotNames[NumberPlots++] = "nbj";
//      plotNames[10] = "ncj";
//      plotNames[11] = "nlj";
//       plotNames[NumberPlots++] = "bj0pt";
//       plotNames[NumberPlots++] = "bj1pt";
//       plotNames[NumberPlots++] = "bj2pt";
//       plotNames[NumberPlots++] = "bj3pt";
//       plotNames[NumberPlots++] = "bj0eta";
//       plotNames[NumberPlots++] = "bj1eta";
//       plotNames[NumberPlots++] = "bj2eta";
//       plotNames[NumberPlots++] = "bj3eta";
//       plotNames[NumberPlots++] = "meff4";
//      plotNames[13] = "bjeta";
//       plotNames[NumberPlots++] = "jsv0";
//       plotNames[NumberPlots++] = "bjsv0";
//       plotNames[NumberPlots++] = "ljsv0";
//       plotNames[NumberPlots++] = "j0sv0";
//       plotNames[NumberPlots++] = "j1sv0";
//       plotNames[NumberPlots++] = "j2sv0";
//       plotNames[NumberPlots++] = "j3sv0";
//       plotNames[NumberPlots++] = "dphij0met";
//       plotNames[NumberPlots++] = "dphij1met";
//     plotNames[1] = "dphij1met";
//     plotNames[2] = "dphij2met";
//     plotNames[3] = "dphij3met";
//       plotNames[NumberPlots++] = "dphibj0met";
//       plotNames[NumberPlots++] = "dphibj1met";
//      plotNames[5] = "htasym";
//      plotNames[6] = "dphijetsmet";
//      plotNames[7] = "dphiptmet";
//      plotNames[8] = "sumtrackpt";
//      plotNames[9] = "mettrackpt";
//      plotNames[14] = "htmet";
//      plotNames[31] = "mj1j0";
//      plotNames[NumberPlots++] = "drbj1bj0";
//      plotNames[NumberPlots++] = "drbj2bj1";
//      plotNames[NumberPlots++] = "drbj3bj1";
//      plotNames[NumberPlots++] = "drbj3bj0";
//      plotNames[NumberPlots++] = "drbj3bj2";
//       plotNames[NumberPlots++] = "dphibj1bj0";
//       plotNames[NumberPlots++] = "dphibj2bj1";
//       plotNames[NumberPlots++] = "dphibj3bj1";
//       plotNames[NumberPlots++] = "dphibj3bj0";
//       plotNames[NumberPlots++] = "dphibj3bj2";
//      plotNames[34] = "bjbhadcount4";
//      plotNames[35] = "sph";
//      plotNames[0] = "tagraterecopt";
//      plotNames[1] = "tagraterecotaggedpt";
//      plotNames[2] = "tagraterecotaggedpteff";
//      plotNames[3] = "tagraterecoeta";
//      plotNames[4] = "tagraterecotaggedeta";
//      plotNames[5] = "tagraterecotaggedetaeff";

     ///-------------------------------------------
     
     NumberSelections = 0;
     //selection[0] = baseName;
     selection[NumberSelections++] = baseName + "";
     //selection[NumberSelections++] = baseName + "susy0l";
     //selection[NumberSelections++] = baseName + "susy0l1j70";
     //selection[NumberSelections++] = baseName + "susy0l2j7030";
     //selection[NumberSelections++] = baseName + "susy0l3j7030";
     //selection[NumberSelections++] = baseName + "susy0l4j7030";
     //selection[NumberSelections++] = baseName + "susy0l4j7030met30";
     //selection[NumberSelections++] = baseName + "truthoffjet";
     //selection[NumberSelections++] = baseName + "L1_JE100";
     //selection[1] = baseName + "4j3j40";
     //selection[0] = baseName + "4j3j40met400ldphi0inv";
     //selection[0] = baseName + "4j3j40met400l";
     //selection[1] = baseName + "4j3j40met400ldphi1inv";
     //selection[2] = baseName + "4j3j40met400ldphi";


     //selection[0] = baseName + "ljetslveto";
     //selection[0] = baseName + "";
     //selection[1] = baseName + "truth_4j";
     ///-------------------------------------------
     
     for(int iplot=0;iplot!=NumberPlots;++iplot) {
        for(int iselection=0;iselection!=NumberSelections;++iselection) {
           for(int ilog=0;ilog!=1;++ilog) {
              bool logx=false;
              bool logy=false;
              TString logAddOn;
              if(ilog==1) {logy=true;  logAddOn="logy";cout << "inlogAddon=" << logAddOn << endl; }
              else if(ilog==2) {logx=true; logAddOn="logx";cout << "inlogAddon=" << logAddOn << endl; }
              else {logAddOn="";}
              TString plotName = selection[iselection] + "_" + plotNames[iplot];       
              TString saveName = selection[iselection] + "_" + outputname + "_" + plotNames[iplot] + "_" + logAddOn;       
              //saveName += "_"; saveName += logAddOn;
              
              //jetAlgs->SetRebin(2);

               bool drawStats = false;
               bool drawExtra = false;
               bool writeFile = true;
               bool dataMCCompare = false;
               bool dataMCRatio = false;
               //TString xAxis = plotNames[iplot];
               //TString yAxis = "Entries";
               TString xAxis = "";//L1 #slash{E}_{T} [GeV]";
               TString yAxis = "Efficiency";
               Float_t YMin = -1;
               Float_t YMax = -1;
               Float_t XMin = -1;
               Float_t XMax = -1;
               bool drawNorm = false;
               TString newLabel = "";//"#tilde{g} #rightarrow b#bar{b}+LSP,";
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
  
    
 


   if( do_plotComparison ) {
      ///+++++++++++++++++++++++++++++++++++++++++++++
      /// Compare different plots for same file
      ///+++++++++++++++++++++++++++++++++++++++++++++
      
      //gStyle->SetDrawOption("hist");
     ///-------------------------------------------

      TString newLabels[30];


      Int_t numberFiles = 0;


      newLabels[numberFiles]  = "#tilde{g}#rightarrowb#bar{b}#Chi^{0}, #DeltaM(#tilde{g},#Chi^{0})=100GeV";
      //newLabels[numberFiles]  = "#tilde{g}#rightarrowb#bar{b}#Chi^{0}, M_{#tilde{g}}=400GeV,M_{#Chi^{0}}=300GeV";
      fileNames[numberFiles++] = dir + "py4bG400L300.exttrgmc106.root";

      newLabels[numberFiles]  = "#tilde{g}#rightarrowb#bar{b}#Chi^{0}, #DeltaM(#tilde{g},#Chi^{0})=300GeV";
      //newLabels[numberFiles]  = "#tilde{g}#rightarrowb#bar{b}#Chi^{0}, M_{#tilde{g}}=400GeV,M_{#Chi^{0}}=100GeV";
      fileNames[numberFiles++] = dir + "py4bG400L100.exttrgmc106.root";

      newLabels[numberFiles]  = "#tilde{b}#rightarrowb#Chi^{0}, #DeltaM(#tilde{b},#Chi^{0})=300GeV";
      //newLabels[numberFiles]  = "#tilde{b}#rightarrowb#Chi^{0}, M_{#tilde{b}}=400GeV,M_{#Chi^{0}}=100GeV";
      fileNames[numberFiles++] = dir + "py2bB400L100.exttrgmc106.root";

      newLabels[numberFiles]  = "#tilde{b}#rightarrowb#Chi^{0}, #DeltaM(#tilde{b},#Chi^{0})=100GeV";
      //newLabels[numberFiles]  = "#tilde{b}#rightarrowb#Chi^{0}, M_{#tilde{b}}=400GeV,M_{#Chi^{0}}=300GeV";
      fileNames[numberFiles++] = dir + "py2bB400L300.exttrgmc106.root";
    

      //fileNames[4] = dir + "py4tbG400L100.exttrgmc106.root";
      //fileNames[5] = dir + "py4tbG400L200.exttrgmc106.root";
      //fileNames[6] = dir + "py4tG500L100.exttrgmc106.root";
      //fileNames[7] = dir + "py4tG500L60.exttrgmc106.root";
      //fileNames[8] = dir + "su4.exttrgmc106.root";

      newLabels[numberFiles]  = "Pythia J2 QCD ";
      fileNames[numberFiles++] = dir + "j3.exttrgmc008.root";

      //newLabels[numberFiles]  = "Pythia J2 Pile-up QCD ";
      //fileNames[numberFiles++] = dir + "j3pu.exttrgmc008.root";
      






//      fileNames[0] = dir + "jCOMB.trg004.root";        
//      fileNames[1] = dir + "qcdCOMB.trg004.root";        
//      fileNames[1] = dir + "tt.trg002.root";
//      fileNames[2] = dir + "pyt2b.tru001.root";        
//      fileNames[3] = dir + "pyt4b.tru001.root";        
//      fileNames[4] = dir + "pyts2b.tru001.root";        
//     fileNames[5] = dir + "su4.trg002.root";        
//      fileNames[1] = dir + "bbCOMB.trg004.root";        
//      fileNames[2] = dir + "bbbarCOMB.trg002.root";        
      //fileNames[3] = dir + "wbbCOMB.trg002.root";        
      //fileNames[4] = dir + "wlCOMB.trg002.root";        
      //fileNames[5] = dir + "zllCOMB.trg002.root";        
      //fileNames[9] = dir + "we.trg001.root";        
      ///fileNames[4] = dir + "wm.trg001.root";        
     //fileNames[5] = dir + "wt.trg001.root";        
     //fileNames[6] = dir + "zee.trg001.root";        
     //fileNames[7] = dir + "zmm.trg001.root";        
     //fileNames[4] = dir + "ztt.trg001.root";        
     //fileNames[5] = dir + "st.trg001.root";        
      //fileNames[0] = dir + "TagRates_final.root";        
     ///-------------------------------------------
      NumberPlots = 0;  
      //plotNames[0] = "met";    
      //plotNames[0] = "Met";    
      //plotNames[2] = "mht";    
      //plotNames[1] = "Mht";    
      
      
//       plotNames[NumberPlots] = "Metpassl1xe20eff";
//       legend[NumberPlots++] = "L1_XE20";
      
//       plotNames[NumberPlots] = "Metpassl1xe30eff";
//       legend[NumberPlots++] = "L1_XE30";
      
//       plotNames[NumberPlots] = "Metpassl1xe45eff";
//       legend[NumberPlots++] = "L1_XE45";

      plotNames[NumberPlots] = "jetetsumpassl1je60eff";
      legend[NumberPlots++] = "L1_JE60";

      plotNames[NumberPlots] = "jetetsumpassl1je100eff";
      legend[NumberPlots++] = "L1_JE100";

      plotNames[NumberPlots] = "jetetsumpassl1je140eff";
      legend[NumberPlots++] = "L1_JE140";


      
      
//       plotNames[NumberPlots] = "jptpassJ10eff";
//       legend[NumberPlots++] = "L1_J10";

//       plotNames[NumberPlots] = "jptpassJ15eff";
//       legend[NumberPlots++] = "L1_J15";

//       //plotNames[NumberPlots] = "jptpassJ20eff";
//       //legend[NumberPlots++] = "L1_J20";

//       plotNames[NumberPlots] = "jptpassJ30eff";
//       legend[NumberPlots++] = "L1_J30";

//       plotNames[NumberPlots] = "jptpassJ55eff";
//       legend[NumberPlots++] = "L1_J55";



//       plotNames[0] = "j0ptpassl1je60eff";
//       legend[0] = "L1_JE60";
//       plotNames[1] = "j0ptpassl1je100eff";
//       legend[1] = "L1_JE100";
//       plotNames[2] = "j0ptpassl1je140eff";
//       legend[2] = "L1_JE140";
      
//        plotNames[0] = "j3ptpassl1je60eff";
//        legend[0] = "L1_JE60";
//        plotNames[1] = "j3ptpassl1je100eff";
//        legend[1] = "L1_JE100";
//        plotNames[2] = "j3ptpassl1je140eff";
//        legend[2] = "L1_JE140";
      

//      plotNames[0] = "l2jetetsum";    
//      legend[0] = "Default";
//      plotNames[1] = "l2jetetsumeta20";    
//      legend[1] = "L2 jet |#eta|<2.0";
//      plotNames[2] = "l2jetetsumeta25";    
//      legend[2] = "L2 jet |#eta|<2.5";
//      plotNames[3] = "l2jetetsumeta27";    
//      legend[3] = "L2 jet |#eta|<2.7";
//      plotNames[4] = "l2jetetsumeta30";    
//      legend[4] = "L2 jet |#eta|<3.0";
//      plotNames[5] = "l2jetetsumeta32";    
//      legend[5] = "L2 jet |#eta|<3.2";
//      plotNames[6] = "l2jetetsumeta40";    
//      legend[6] = "L2 jet |#eta|<4.0";





//       plotNames[0] = "l2jJ50pt";    
//       legend[0] = "Leading";
//       plotNames[1] = "l2jJ51pt";    
//       legend[1] = "2^{nd}";
//       plotNames[2] = "l2jJ52pt";    
//       legend[2] = "3^{rd}";
//       plotNames[3] = "l2jJ53pt";    
//       legend[3] = "4^{th}";
      //plotNames[0] = "jptpassJ5eff";
      //plotNames[1] = "jptpassJ10eff";
      //plotNames[2] = "jptpassJ15eff";
      //plotNames[3] = "jptpassJ30eff";
      //plotNames[0] = "nbtag";    
      //plotNames[1] = "nbtagpredalppt";    
      //plotNames[2] = "nbtagpredalpptstatup";    
      //plotNames[3] = "nbtagpredalpptstatdown";    
      //plotNames[2] = "nbtagpredalpptdphi";    
      //plotNames[5] = "nbtagpredalpptdphistatup";    
      //plotNames[6] = "nbtagpredalpptdphistatdown";    
      //plotNames[3] = "nbtagpredalpptdphii";    
      //plotNames[8] = "nbtagpredalpptdphiistatup";    
      //plotNames[9] = "nbtagpredalpptdphiistatdown";    
      //plotNames[1] = "nbtagpredalpptjmd";    
      //plotNames[2] = "nbtagpredalpptjmdstatup";    
      //plotNames[3] = "nbtagpredalpptjmdstatdown";    
      //plotNames[2] = "nbtagpredpytptjmd";    
      //plotNames[2] = "nbtagpredpytptjmdstatup";    
      //plotNames[3] = "nbtagpredpytptjmdstatdown";    
      //plotNames[0] = "jetmetbtag4j3j40met400ldphi1inv_jetmetbtag4j3j40met400ldphi1inv_tagraterecotaggedpt_tagrate_final_index_Pythia_J0_6";
      //plotNames[0] = "jetmetbtag4j3j40met400ldphi1inv_jetmetbtag4j3j40met400ldphi1inv_tagraterecotaggedpt_tagrate_final_index_QCD_Alpgen";
      //plotNames[0] = "jetmetbtag4j3j40met400ldphi1inv_jetmetbtag4j3j40met400ldphi1inv_tagratedphirecotaggedpt_tagrate_final_index_Pythia_J0_6";
      //plotNames[1] = "jetmetbtag4j3j40met400ldphi1inv_jetmetbtag4j3j40met400ldphi1inv_tagratedphirecotaggedpt_tagrate_final_index_QCD_Alpgen";
      //plotNames[2] = "jetmetbtag4j3j40met400ldphi1inv_jetmetbtag4j3j40met400ldphi1inv_tagratedphiirecotaggedpt_tagrate_final_index_Pythia_J0_6";
      //plotNames[3] = "jetmetbtag4j3j40met400ldphi1inv_jetmetbtag4j3j40met400ldphi1inv_tagratedphiirecotaggedpt_tagrate_final_index_QCD_Alpgen";
      ///-------------------------------------------
      //legend[0] = "#slash{E_{T}}";
      //legend[1] = "#slash{H_{T}}";
      //legend[0] = "J5";
      //legend[1] = "J10";
      //legend[2] = "J15";
      //legend[3] = "J30";
      //legend[0] = "Obs.  ";
      //legend[1] = "Pred.  par:jet p_{T} ";
      //legend[2] = "Pred.  par:jet p_{T} +1#sigma_{stat}";
      //legend[3] = "Pred.  par:jet p_{T} -1#sigma_{stat}";
      //legend[2] = "Pred.  par:jet p_{T} (#Delta#phi(j,#slash{E_{T}}>1.0)";
      //legend[3] = "Pred.  par:jet p_{T} (#Delta#phi(j,#slash{E_{T}}<1.0)";
      //legend[1] = "Pred. (alp) par:jet p_{T},#Delta#phi(j,#slash{E_{T}})";
      //legend[2] = "Pred. (pyt) par:jet p_{T},#Delta#phi(j,#slash{E_{T}})";
      //legend[2] = "Pred. (pyt) par:jet p_{T},#Delta#phi(j,#slash{E_{T}}) +1#sigma_{stat}";
      //legend[3] = "Pred. (pyt) par:jet p_{T},#Delta#phi(j,#slash{E_{T}}) -1#sigma_{stat}";
      //legend[0] = "Tag rate all jets (pyt)";
      //legend[0] = "Tag rate all jets (alp)";
      //legend[0] = "Tag rate #Delta#phi(j,#slash{E_{T}})>1.0 (pyt)";
      //legend[1] = "Tag rate #Delta#phi(j,#slash{E_{T}})>1.0 (alp)";
      //legend[2] = "Tag rate #Delta#phi(j,#slash{E_{T}})<1.0 (pyt)";
      //legend[3] = "Tag rate #Delta#phi(j,#slash{E_{T}})<1.0 (alp)";
      
      NumberSelections = 1;
      //selection[0] = baseName + "4j3j40met400ldphi";
      //selection[0] = baseName + "4j3j40met400ldphi1inv";
      selection[0] = baseName + "";
      //selection[0] = baseName + "L1_JE100";
      //selection[0] = baseName + "susy0l4jfullsoft";
      //selection[1] = baseName + "L1_4J10";
      //selection[0] = baseName + "susy0l4j7030";
      ///-------------------------------------------
      
      for(int ifile=0;ifile!=numberFiles;++ifile) {        
         for(int iselection=0;iselection!=NumberSelections;++iselection) {
            for(int ilog=0;ilog!=1;++ilog) {
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
               TString saveName = jetAlgs->StripFileName(fileNames[ifile]) + "_" + outputname + "_" + selection[iselection] + "_" + plotNames [0] + "_" + logAddOn;       
               
               
               TString newLabel = newLabels[ifile];
               newLabel.ReplaceAll(dir,"");
               newLabel.ReplaceAll(".root","");
               newLabel.ReplaceAll(".exttrgmc006","");
               newLabel.ReplaceAll(".exttrgmc106","");
               newLabel.ReplaceAll(".exttrgmc007","");
               newLabel.ReplaceAll(".exttrgmc008","");
               //jetAlgs->SetRebin(4);
               jetAlgs->makeCombinedPlots(fileNames[ifile],
                                          fullPlotNames,
                                          legend,
                                          NumberPlots,
//                                          plotNames[0],
//                                          "Entries",
//                                          "L2 jet pT [GeV]",
                                          "Sum jet E_{T} [GeV]",
                                          "Efficiency",
                                          saveName,-1,-1,
                                          false,
                                          logx,logy,-1,-1,
                                          false,"E",0,newLabel);
            }
        }
     }
     
     
     
     
   }
   
   





 
}
