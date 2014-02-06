//Created by Dan
//This macro plots many distros of the same name from different files
//Each file can have its own scale factor for its histos
//The true purpose of this is to scale the QCD backgrounds to the same lum as the data


void doWeightPlots()
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
   TString outDir      = "~/public_html/files/dataMC/F/";
   TString plotType    = ".png";
   TString rootFile    = "outputfile_final.root";
   TString outfilename = outDir + rootFile;
   TString dir         = "/afs/slac/g/atlas/work/data1/dans/AnaOut/";

   TString tag   = "weight";
   
   

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
   double histoWeights[50];
   Int_t NumberPlots = 0;
   Int_t NumberSelections = 0;


   ///+++++++++++++++++++++++++++++++++++++++++++++
   /// setup plots 
   ///+++++++++++++++++++++++++++++++++++++++++++++

   TString baseName    = "jetmetbtagsusy0l3j5020L1_J30";
   
   if( do_dataMCComparison) { 

     //Input Files
     ///-------------------------------------------      
     double lumi = 1.711; //luminosity in pb

     Int_t numberFiles = 4;      
     fileNames[0] = dir + "jCOMB.exttrgmc008.jetmet.eta25.root";
     histoWeights[0] = lumi/100.0;
     fileNames[1] = dir + "j5.exttrgmc008.jetmet.eta25.root";     
     histoWeights[1] = lumi/100.0;
     fileNames[2] = dir + "j4.exttrgmc008.jetmet.eta25.root";
     histoWeights[2] = lumi/100.0;
     fileNames[3] = dir + "periodFslim.susy001.jetmet.eta25.root";
     histoWeights[3] = 1;

     //fileNames[1] = dir + "data158116.exttrg006.root";
     //fileNames[1] = dir + "ttCOMB.exttrgmc006.jetmet.root";
     //Legend Names
     ///-------------------------------------------
     legend[0] = "QCD";
     legend[1] = "j5";
     legend[2] = "j4";
     legend[3] = "Period F";


      int c = 0;
     //Plot Names
     ///-------------------------------------------
      //plotNames[c++] = "j1pt";


      plotNames[c++] = "Mht";
      plotNames[c++] = "mht";
      plotNames[c++] = "Met";
      plotNames[c++] = "met";
      plotNames[c++] = "nj";
      plotNames[c++] = "nbtag";
      //plotNames[c++] = "j0phi";
      plotNames[c++] = "j0pt";
      // plotNames[c++] = "j0eta";
      // plotNames[c++] = "j1phi";
      plotNames[c++] = "j1pt";
      //plotNames[c++] = "j1eta";
      //plotNames[c++] = "j2phi";
      plotNames[c++] = "j2pt";
      //plotNames[c++] = "j2eta";
      //plotNames[c++] = "jsv0";
      plotNames[c++] = "dphij0met";
      //plotNames[c++] = "dphij1met";
      plotNames[c++] = "dphij0mht";
      plotNames[c++] = "ht";





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
               bool dataMCCompare = false;
               bool dataMCRatio = false;
               TString xAxis = plotNames[iplot];
               TString yAxis = "Entries";
               Float_t YMin = -1;
               Float_t YMax = -1;
               Float_t XMin = -1;
               Float_t XMax = -1;
               bool drawNorm = false;
               TString newLabel = "Period F, L1_J30";
               bool plotMore = false;
               bool lineOnly = false;
               jetAlgs->makeCombinedWeightPlots(fileNames,
                                              plotName, 
                                              legend,
						histoWeights,
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
