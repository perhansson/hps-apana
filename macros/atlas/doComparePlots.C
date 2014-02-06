
void doComparePlots()
{
   ///-------------------------------------------------------------------------
   /// Compile everything
   ///-------------------------------------------------------------------------  
   gSystem->Load("libPhysics.so");
   //gSystem->CompileMacro ("Util.cpp","k");
   gSystem->CompileMacro ("~/RootUtils/trunk/Util.cpp", "k");
   gSystem->CompileMacro ("JetMetbTagAnalysisBase.cxx", "k");
   
   
   bool do_dataMCComparison        = 1;


   ///-------------------------------------------------------------------------
   /// Setup input/ouput paths
   ///-------------------------------------------------------------------------

   Long64_t EvtMax         = 1;
   Long64_t EvtCnt         = 1;
   Int_t    NFilesNeeded   = 1;
   bool     verbose        = false;
   
   /// output
   TString outDir      = "~/public_html/files/dataMC/";
   TString plotType    = ".png";
   TString rootFile    = "outputfile_final.root";
   TString outfilename = outDir + rootFile;
   TString dir         = "../topologies/jetmetbtag/";

   TString tag   = "test";
   
   

   /// Setup analysis
   JetMetbTagAnalysisBase *jetAlgs = new JetMetbTagAnalysisBase(0,verbose);
   jetAlgs->SetPlotTypeAndLumi(plotType,tag);
   jetAlgs->SetOutputDirectory(outDir);
   jetAlgs->SetOutputRootFile(rootFile);
   
   
   
   TLegendEntry *entry;
   TString plotNames[500];
   TString fileNames[50];
   TString selection[50];
   TString legend[50];             
   
   Int_t NumberPlots = 0;
   Int_t NumberSelections = 0;


   ///+++++++++++++++++++++++++++++++++++++++++++++
   /// setup plots 
   ///+++++++++++++++++++++++++++++++++++++++++++++

   TString baseName    = "jetmetbtagsusy0l3j5020L1_J10";
   
   if( do_dataMCComparison) { 

     //Input Files
     ///-------------------------------------------      
     Int_t numberFiles = 2;      
     fileNames[0] = dir + "jCOMB.exttrgmc008.jetmet.root";
     fileNames[1] = dir + "periodDslim.susy001.jetmet.root";
     //fileNames[1] = dir + "data158116.exttrg006.root";

     //Legend Names
     ///-------------------------------------------
     legend[0] = "QCD";
     legend[1] = "D";
     //legend[1] = "158116";

      int c = 0;
     //Plot Names
     ///-------------------------------------------
      plotNames[c++] = "jpt";
      /*
      plotNames[c++] = "Meff4";
      plotNames[c++] = "meff4";
      plotNames[c++] = "Mht";
      plotNames[c++] = "mht";
      plotNames[c++] = "Met";
      plotNames[c++] = "met";
      plotNames[c++] = "nj";
      plotNames[c++] = "nbtag";
      plotNames[c++] = "j0phi";
      plotNames[c++] = "j0pt";
      plotNames[c++] = "j0eta";
      plotNames[c++] = "j1phi";
      plotNames[c++] = "j1pt";
      plotNames[c++] = "j1eta";
      plotNames[c++] = "j2phi";
      plotNames[c++] = "j2pt";
      plotNames[c++] = "j2eta";
      */


      NumberPlots = c;  
      
      //Selections
      ///-------------------------------------------     
      NumberSelections = 1;
      selection[0] = baseName + "";
      //selection[0] = baseName + "";
      //selection[1] = baseName + "dj";
      //selection[0] = baseName + "djdphi27";
      

       //Boring plotting loop
      ///-------------------------------------------
     
      for(int iplot=0;iplot!=NumberPlots;++iplot) {
         for(int iselection=0;iselection!=NumberSelections;++iselection) {
            for(int ilog=0;ilog!=2;++ilog) {
               bool logx=false;
               bool logy=false;
               TString logAddOn;
               if(ilog==0) {logy=true;  logAddOn="logy";cout << "inlogAddon=" << logAddOn << endl; }
               else if(ilog==2) {logx=true; logAddOn="logx";cout << "inlogAddon=" << logAddOn << endl; }
               else {logAddOn="";}
               cout << "----------------------------------------------" << endl;
               cout << "Starting plot overlay" << endl;
               cout << "----------------------------------------------" << endl;
              
               //jetAlgs->SetRebin(2);
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
               TString newLabel = "L1_J10";
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
  
    






 
}
