#include "Topology_event.h"
#include "TFile.h"
//#include "SimpleTiming.h"

void Topology_event::cut(const TString &) {
   for (std::map<TString, Topology_base*>::iterator it=m_topo.begin();
        it!=m_topo.end();++it) {
      if ((*it).first!="") (*it).second->cut((*it).first);
   }
}

void Topology_event::book(const TString &, const TString &) {
}

void Topology_event::finalize(void) {
   for (std::map<TString, Topology_base*>::iterator it=m_topo.begin();
        it!=m_topo.end();++it) {
      if ((*it).first!="") (*it).second->finalize();
   }
}

// ----------------------------------------------------------------------------
void Topology_event::add_mc_sample(const string & mc_sample,
                                   const string & mc_set) {
   string sline;
   ifstream fh(mc_set.c_str());
   if (!fh.is_open()) {
      cout << "Error opening mc set file " << mc_set << endl;
      exit(1);
   }
   string mc_path;
   getline(fh,mc_path);
   while (getline(fh,sline)) {
      stringstream ss;
      ss << sline;
      string mc_number,mc_name;
      ss >> mc_number;
      if (mc_number==mc_sample) {
         double kfactor=0, raw_xs=0;
         ss >> kfactor;
         ss >> raw_xs;
         evt->xs=kfactor*raw_xs;
         if (evt->xs) {
            std::cout << "K-factor          = " << kfactor << std::endl;
            std::cout << "Raw cross section = " << raw_xs << " pb" << std::endl;
            std::cout << "Cross section     = " << evt->xs << " pb" << std::endl;
         }
         else {
            std::cout << "Error, no cross-section specified." << std::endl;
            exit(1);
         }
         ss >> mc_name;
         m_files.push_back(mc_path+"/"+mc_name+"/*.root*");
         return;
      }
   }
   cout << "Error reading " << mc_set << ". Most probably this means that " << mc_sample <<" is not defined among the below samples:" << endl;
   {
      ifstream fh_tmp(mc_set.c_str());
      getline(fh,mc_path);
      while (getline(fh,sline)) {
         cout << sline << endl;
      }
   }
   exit(1);
}

// ----------------------------------------------------------------------------
void Topology_event::add_src_list(const TString & src_list) {
   const int BUFLEN=1000;
   char buffer[BUFLEN];
   std::ifstream fh(src_list.Data());
   if (!fh.is_open()) {
      std::cout << "Error opening source list file " << src_list << std::endl;
      exit(1);
   }
   if (fh >> evt->xs) {
      std::cout << "Cross section       = " << evt->xs << " pb" << std::endl;
   }
   else {
      std::cout << "No cross-section specified, bailing out ..." << std::endl;
      exit(1);
   }
   while (!fh.eof()) {
      TString name(buffer);
      if (name.Contains(".root")) {
         m_files.push_back(name); 
      }
      fh.getline(buffer,BUFLEN);
   }
}



// ----------------------------------------------------------------------------
void Topology_event::loop_src(EventSrc *src, int maxev) {

   //SimpleTiming timing("loop_src");

   int total_events=0;

   if (evt->m_jes!=1) std::cout << "Jet Energy Scale Shift: "
                                << (evt->m_jes-1.0)*100.0 
                                << " %" << std::endl;
   if (evt->m_jer!=1) std::cout << "Jet Energy Res.  Shift: "
                                << (evt->m_jer-1.0)*100.0
                                << " %" << std::endl;
   if (evt->m_mets!=1) std::cout << "      MET  Scale Shift: "
                                 << (evt->m_mets-1.0)*100.0
                                 << " %" << std::endl;

   std::cout << "---- Defined topologies ----" << std::endl;
   for (std::map<TString, Topology_base*>::iterator it=m_topo.begin();
        it!=m_topo.end();++it) {
      std::cout << "Topo = '" << (*it).first << "'" << std::endl;
   }
   std::cout << "----------------------------" << std::endl;
   
   if (m_topo.find("")==m_topo.end()) {
      std::cout << "Topology_event not defined!" << std::endl;
      exit(1);
   }
   int trig_events=src->Open(m_files);
   int raw_events = (int)src->GetNEntries();
   if (trig_events==0) trig_events=raw_events; // no trigger scan for MC
   if (raw_events<1) {
      std::cout << "No events in file, bailing out!" << std::endl;
      exit(1);
   }    
   evt->lumi=evt->cfg.get_lumi();
   if (evt->xs > 0)
     std::cout << "Equiv. luminosity      = " << evt->lumi << "/pb" << std::endl;
   std::cout << "Events in sample  = " << raw_events << std::endl;
   evt->m_req_events=TMath::Min(trig_events,maxev);
   std::cout << "Events triggered  = " << evt->m_req_events << std::endl;
   //Set GRL from config file
   TString grllist = "../../utils/lumi_files/"+evt->cfg.get_grl();
   src->SetXMLFile(grllist);
   std::cout << "Good Run List = " << grllist << std::endl;
   for ( int event=0 ; event<raw_events; ++event ) {
      evt->m_event=event;
      src->GetEntry(event);
      if (evt->BuildEvent(*src)) {
         ++total_events;
         analyze("");
      }
      if (total_events==evt->m_req_events) break;
      if (event%1000==0) std::cout << "event(processed,triggered) = "
                                  << event+1 << ", " << total_events << std::endl;
   }
   src->Close();
   //assert(total_events==trig_events);
   std::cout << "Total events analyzed: " << total_events << std::endl;
   finalize();

   //timing.Stop();
   //timing.Print();
   
}
