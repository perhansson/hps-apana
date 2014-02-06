#include "Topology_example.h"
#include <iomanip>
#include <cstdio>


/*
 * This function get called for each event and is where you put your selections and bookings of histograms
 */

void Topology_example::cut(const TString & prefix) {

   if(get_debug()) cout << "cut prefix=" << prefix << endl;

   //This is where you make your cuts

   // Produce e.g. plots with no selection at all
   book(prefix,"");      
   // with the "_truth" flag automatically use truth objects here if they are available      
   //book(prefix,"_truth"); 
   

   //Example of single track selection
   if ( trks() == 1 ) {
     
     book(prefix,"1trk");   
     
     //Example of two track selection
     if ( trks() == 2 ) {
       
       book(prefix,"2trk");   
       
       if( trk(0).Charge() * trk(1).Charge() < 0 ) {
	 
	 book(prefix,"2trkoppq");   
	 
	 if( trk(0).p.P() > 1.0 && trk(1).p.P() > 1.0 ) {
	   
	   book(prefix,"2trkoppqhighp");   
	   
	 }

       }
       
     } 

   }
   
   
}

void Topology_example::book(const TString & pre, const TString & suf) {
   
   if(get_debug()) cout << "book pre=" << pre << "  suf=" << suf << endl;
  
   //This is where you fill your histograms!
   
   //Tip: Keep a bool if you want automatically switch between truth and reco
   const bool isTru=suf.Contains("truth");
   
   
   // Use the name directory of one histograms to check if this is the first event
   
   if (gDirectory->Get(pre+suf+"_runnr")==0) {
      
      const TString key=pre+suf+"_";

      /* ======== BOOK HISTOGRAMS ========= */

      //Tracks
      new TH1F(key+"trkp",";Track p (GeV);Entries",50,0,5);
      //Event
      new TH1F(key+"runnr",";Run number;Entries",100,0.,1000000);            
      new TH1F(key+"invm",";Invariant mass (GeV);Entries",50,0,5);
      
      //Sets the sum of weights for all TH*
      FixSumw2(gDirectory);
   };
   
   
   //Tip: use the built in cut tracker
   int cuts=0;
   util().cut(pre,suf,"CAND",false,0,cuts);
   
   //Fill runnr
   wfill(hist(pre,suf,"runnr"),evt->m_runnr);
   if(get_debug()) cout << "filled runnr with " << evt->m_runnr << " so far has " << hist(pre,suf,"runnr")->Integral() <<endl;   
   
   // Fill track momentum
   for(int itrk=0; itrk < trks(); ++ itrk) {
     wfill(hist(pre,suf,"trkp"),trk(itrk).p.P());
   }
   
   // Fill event variables 
   // - example of using a base class function available to all topologies
   if(trks()>1) {
     wfill(hist(pre,suf,"invm"),invmass(trk(0),trk(1)));
   }
   
}

  


void Topology_example::finalize(void) {
   

   // Print some statistics
   
   std::cout << "\n\n ------------------- Example analysis results -------------------"
             << std::endl;
   std::cout << "Events         : " << histC("example","","runnr") << std::endl;
   
   // use the cut utility to count e.g. efficiency easily

   float nt_ok=util().cnt("Track","Track","OK");
   float nt_cand=util().cnt("Track","Track","CAND");
   
   std::cout << "Track cand   : " << nt_cand << std::endl;
   std::cout << "Track ok     : " << nt_ok << " -> efficiency: " << (nt_cand!=0.?nt_ok/nt_cand:-1.) << std::endl;   
      
   std::cout << "Event selection:" << std::endl;
   util().displayCutMap("");
   util().printCutMap("example","","runnr");
   
}

void Topology_example::exampleFunction() {
  // not implemented
}

