//==================================================================
//   Script for OO analysis with AtlAna
//==================================================================
void ana(TString topo_str="example",
         const TString sample="testrun.dst001",
         int maxev=9999999,int useGRL=0) 
{
   TString name=sample;

   //Create the output file
  
   TString outfile=name + ".root";
   std::cout << "Output file: " << outfile << std::endl; 
   TAuthenticate::SetGlobalUser("phansson");
   gSystem->SetIncludePath("-O0 -Wall -I../../core -I./include");
   gSystem->Load("libPhysics.so");
  
   //Create the histogram file  
   TFile* hist_file = new TFile(outfile, "RECREATE");  
   
   // GRL loader
   //gSystem->AddIncludePath(" -I../../../../DataQuality/GoodRunsLists/");
   //gSystem->Load("libGoodRunsLists.so");

   //Compile the Event base classes
   gSystem->CompileMacro("../../core/AtlEvent.cxx","k");
   gSystem->CompileMacro("../../core/EventSrc.cxx","k");
  
   /****** ADD YOUR OWN NTUPLE TYPE BELOW *******/
   gSystem->CompileMacro("../../fileevents/FileEvent_dst001.cxx","k"); 
  
   EventSrc *src;
  
   /******* ADD YOUR FILEEVENT NTUPLE FORMAT BELOW ********/  
   if (name.Contains(".dst001")) src=new FileEvent_dst001;
   //else if (name.Contains(".exttrg006")) src=new FileEvent_exttrg006;
   else {
      std::cout << "Unknown source type for FileEvent!" << endl;
      return;
   }

   //Decision on using GRL or not
   cout<<"useGRL="<<useGRL<<endl;
   src->useGRL(useGRL);
   
   //Compile the base topology classes  
   gSystem->CompileMacro("../../core/Topology_base.cxx","k");
   gSystem->CompileMacro("../../core/Topology_event.cxx","k");
   
   gSystem->CompileMacro("../../core/TrigChain.cxx","k");
  
   //Create the event object using the correct configuration
   //Switch for samples
   TString configfile;
   if (topo_str=="example")
      configfile = "../../config/bumphunt.config";
   //else if (topo_str=="l2rate")
   //  configfile = "../../config/l2bjetrate.trg001.config";
   else
     exit(1);
   
   AtlEvent evt(configfile);
    
   hist_file->cd();
  
  
   //Create the looper topology which handles the event loop control
   Topology_event topo(&evt);
  
  
  
   //Add the topologies you want to run
  
//   gSystem->CompileMacro("Topology_template.cxx","k");
//   topo.add_topology(TString("template"), new Topology_template(&evt));
  
   /******* ADD YOUR OWN TOPOLOGY BELOW ******/  
   gSystem->CompileMacro("Topology_example.cxx","k");
   //gSystem->CompileMacro("Topology_jetmetbtag.cxx","k");
  
   if(topo_str=="example")          topo.add_topology(TString("example"), new Topology_example(&evt)); 
   //else if(topo_str=="jetmetbtag") topo.add_topology(TString("jetmetbtag"), new Topology_jetmetbtag(&evt));
   else if (topo_str=="all") {
     topo.add_topology(TString("example"), new Topology_example(&evt));
     //topo.add_topology(TString("jetmetbtag"), new Topology_jetmetbtag(&evt));
   }
   
   
   // Add sample to run over from text file:
   // the sample name tells which dataset ID to run over in this file
   
   topo.add_mc_sample(sample.Data(),"../../filelists/dst_filelist.txt"); 
  

   // Enter the event loop 
   topo.loop_src(src,maxev);
  
   //Save some cross-section info
   TTree *fileinfo=new TTree("FileInfo","FileInfo");
   fileinfo->Branch("xs",&evt.xs,"xs/D");
   fileinfo->Fill();
  
   hist_file->Write();
   hist_file->Close();
   hist_file->Open(outfile);
}

