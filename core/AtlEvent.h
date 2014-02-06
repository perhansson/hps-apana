/**************************************************************************
 **
 **   File:         AtlEvent.h
 **
 **   Description:  Generic event analysis. It creates a generic
 **                 analysis event from external data
 **
 **   Author:       P. Hansson
 **
 **   Created:      
 **   Modified:
 **
 **************************************************************************/

#ifndef __ATLEVENT_H
#define __ATLEVENT_H

#include <iostream>
#include "AtlUtil.h"
#include "Electron.h"
#include "Muon.h"
//#include "Neutrino.h"
#include "Tau.h"
#include "Jet.h"
#include "Cell.h"
#include "L1Jet.h"
#include "L2BJet.h"
#include "L1EMObj.h"
#include "L2El.h"
#include "EFEl.h"
#include "Parton.h"
#include "Roi.h"
#include "TrigDec.h"
#include "EventSrc.h"
#include "AtlConfig.h"
#include "TagRate.h"
#include "BeamSpot.h"
#include "Track.h"

class AtlEvent {
   public:
      AtlEvent(const TString & cfgfile="atlana.txt",
               const double jes=0.0,
               const double metScale=0.0,
               const double jer=0.0) {
         cfg.read_file(cfgfile);
         m_jes=1.0+jes/100.0;
         m_mets=1.0+metScale/100.0;
         m_jer=1.0+jer/100.0;
      };
      void init(void);
      void do_overlap(void);
      void do_sort_pt(void);
      void do_duplicate_check(void);

      //virtual ~AtlEvent(){};
      bool BuildEvent(EventSrc &evt);
      int rois(void) const {return m_rois.size();};
      int rois(const TString & name) const { return m_rois.count(name);};
      int leptons(void) const {return m_leptons.size();};
      int leptons_loose(void) const {return m_leptons_loose.size();};
      int electrons(void) const {return m_electrons.size();};
      int electrons_raw(void) const {return m_electrons_raw.size();};
      int electrons_loose(void) const {return m_electrons_loose.size();};
      int trks(void) const {return m_trks.size();};
      int cells(void) const {return m_cells.size();};
      //int neutrinos(void) const {return m_neutrinos.size();};
      int muons(void) const {return m_muons.size();};
      int muons_loose(void) const {return m_muons_loose.size();};
      int muons_raw(void) const {return m_muons_raw.size();};
      int jets(void) const {return m_jets.size();};
      int taus(void) const {return m_taus.size();};
      int leptons_truth(void) const {return m_leptons_truth.size();};
      int electrons_truth(void) const {return m_electrons_truth.size();};
      //int neutrinos_truth(void) const {return m_neutrinos_truth.size();};
      int muons_truth(void) const {return m_muons_truth.size();};
      int jets_truth(void) const {return m_jets_truth.size();};
      int taus_truth(void) const {return m_taus_truth.size();};
      int l1jets(void) const {return m_l1jets.size();};
      int l2jets(void) const {return m_l2jets.size();};
      Particles<L2BJet> GetHLTBjets(const std::string& level, const std::string& chain) const {
         Particles<L2BJet> bjets;
         for(size_t i=0;i!=(level=="L2"?m_l2bjets.size():m_efbjets.size());++i) {
            if((level=="L2"?m_l2bjets:m_efbjets)[i].Chain()==chain) bjets.push_back((level=="L2"?m_l2bjets:m_efbjets)[i]);
         }
         return bjets;         
      }
      int l2bjets(const std::string chain="") const {
         if(chain=="") return m_l2bjets.size();
         Particles<L2BJet> bjets = GetHLTBjets("L2",chain);
         return bjets.size();
      };
      int efbjets(const std::string chain="") const {
         if(chain=="") return m_efbjets.size();
         Particles<L2BJet> bjets = GetHLTBjets("EF",chain);
         return bjets.size();
      };
      int l1emobjs(void) const {return m_l1emobjs.size();};
      int l2els(void) const {return m_l2els.size();};
      int efels(void) const {return m_efels.size();};
      int partons(void) const {return m_partons.size();};
      int vertices(const int& mintrks=0) const {
         if(mintrks==0) return m_vertex.size();
         int n=0;
         Vertices::const_iterator i  = m_vertex.begin();
         Vertices::const_iterator iE = m_vertex.end();         
         for(;i!=iE;++i) {if(i->n()>=mintrks) n++;}
         return n;
      }

  
      const Particle * lepton(const int i) const {return m_leptons[i];};
      const Particle * lepton_loose(const int i) const
      {return m_leptons_loose[i];};
      const Rois roi() const {
         Rois tmp;
         Rois_dict::const_iterator itr=m_rois.begin();
         Rois_dict::const_iterator eitr=m_rois.end();
         for (; itr!=eitr; ++itr) tmp.push_back(itr->second);
         return tmp;
      };
      const Rois roi(const TString & name) const {
         Rois tmp;
         Rois_dict::const_iterator itr=m_rois.lower_bound(name);
         Rois_dict::const_iterator eitr=m_rois.upper_bound(name);
         for (; itr!=eitr; ++itr) tmp.push_back(itr->second);
         return tmp;
      };
      const Electron & electron(const int i) const {return m_electrons[i];};
      const Electron & electron_raw(const int i) const
      {return m_electrons_raw[i];};
      const Electron & electron_loose(const int i) const
      {return m_electrons_loose[i];};
      const Track & trk(const int i) const {return m_trks[i];};
      const Cell & cell(const int i) const {return m_cells[i];};
      const Muon & muon(const int i) const {return m_muons[i];};
      //const Neutrino & neutrino(const int i) const {return m_neutrino[i];};

      const Muon & muon_loose(const int i) const {return m_muons_loose[i];};
      const Muon & muon_raw(const int i) const {return m_muons_raw[i];};
      const Tau & tau(const int i) const {return m_taus[i];};
      const Jet & jet(const int i) const {return m_jets[i];};
      const Particle * lepton_truth(const int i) const {
         return m_leptons_truth[i];
      };
      const Electron & electron_truth(const int i) const {
         return m_electrons_truth[i];
      };
      const Muon & muon_truth(const int i) const {return m_muons_truth[i];};
      //const Neutrino & neutrino_truth(const int i) const {return m_neutrinos_truth[i];};

      const Tau & tau_truth(const int i) const {return m_taus_truth[i];};
      const Jet & jet_truth(const int i) const {return m_jets_truth[i];};
      const Parton & parton(const int i) const {return m_partons[i];};
      const L1Jet & l1jet(const int& i) const { return m_l1jets[i];}
      const Jet & l2jet(const int& i) const { return m_l2jets[i];}
      const L2BJet & l2bjet(const int& i) const {return m_l2bjets[i];};
      const L2BJet & efbjet(const int& i) const {return m_efbjets[i];};
      const L1EMObj * l1emobj(const int i) const {
         for(std::vector<L1EMObj>::const_iterator it=m_l1emobjs.begin();
             it!=m_l1emobjs.end();++it) {
            if( it->Index() == i ) return &(*it);           
         }
         return 0;
      };
      const L2El * l2el(const int i) const {
         for(std::vector<L2El>::const_iterator it=m_l2els.begin();
             it!=m_l2els.end();++it) {
            if( it->Index() == i ) return &(*it);           
         }
         return 0;
      };
      const EFEl * efel(const int i) const {
         for(std::vector<EFEl>::const_iterator it=m_efels.begin();
             it!=m_efels.end();++it) {
            if( it->Index() == i ) return &(*it);           
         }
         return 0;
      };
      double l1_met(void) const {
         return sqrt(m_l1_metx*m_l1_metx+m_l1_mety*m_l1_mety);
      };
      double l2_met(void) const {
         return sqrt(m_l2_metx*m_l2_metx+m_l2_mety*m_l2_mety);
      };
      double ef_met(void) const {
         return sqrt(m_ef_metx*m_ef_metx+m_ef_mety*m_ef_mety);
      };
      int nuN(void) const{return m_nuN;}
      double nuP(void) const{return m_nuP;}
      double TowerEnergy(const int i, const int j) const {return m_TE[i][j];}
      double met(void) const {return sqrt(m_metx*m_metx+m_mety*m_mety);}
      const TLorentzVector met_p(void) const {
	TLorentzVector p;p.SetXYZM(m_metx,m_mety,0,0); return p;}
      const TLorentzVector met_p_truth(void) const {
	TLorentzVector p; p.SetXYZM(m_metx_truth,m_mety_truth,0,0); return p;}
      double etsum(void) const {return m_etsum;}
      double etsum_truth(void) const {return m_etsum_truth;}
      double metx(void) const {return m_metx;}
      double mety(void) const {return m_mety;}
      double met_truth(void) const {
         return sqrt(m_metx_truth*m_metx_truth+m_mety_truth*m_mety_truth);}
      double metx_truth(void) const {return m_metx_truth;}
      double mety_truth(void) const {return m_mety_truth;}
      double evtopo(const TString& var) const {
         return m_topovars.find(var) == m_topovars.end() ? -99. :
            m_topovars.find(var)->second;}
      int TrigDecision(const TString & trigger) {
         return m_trigdec.getTrigDec(trigger);}
      double Sphericity() {
         std::vector<const TLorentzVector*> v;
         for(size_t i=0; i<m_leptons.size(); ++i){
            v.push_back(&(m_leptons[i]->p));
         }
         for(size_t i=0; i<m_jets.size(); ++i){
            v.push_back(&(m_jets[i].p));
         }
         std::map< TString, double > topo=TopoCalculation( v ); 
         return topo["SPH"];
      }
      double Sphericity_truth() {
         std::vector<const TLorentzVector*> v;
         for(size_t i=0; i<m_leptons_truth.size(); ++i){
            v.push_back(&(m_leptons_truth[i]->p));
         }
         for(size_t i=0; i<m_jets_truth.size(); ++i){
            v.push_back(&(m_jets_truth[i].p));
         }
         std::map< TString, double > topo=TopoCalculation( v ); 
         return topo["SPH"];
      }
      double EffectiveMass(int nlep=0,int njetreq=4) {          
         if(njetreq) {
            if((int)m_jets.size()<njetreq) {
               std::cout << "Wrong usage of Effective Mass" << std::endl;
               exit(1);
            }
         }
         Particles_p<const Particle*> jets;
         for(size_t i=0;i!=m_jets.size();++i) jets.push_back(&(m_jets[i]));
         return util.EffMass(nlep,m_leptons, njetreq, jets, met_p() );
      }
      double EffectiveMass_truth(int nlep=0,int njetreq=4) {          
         if(njetreq) {
            if((int)m_jets_truth.size()<njetreq) {
               std::cout << "Wrong usage of Effective Mass Truth" << std::endl;
               exit(1);
            }
         }
         Particles_p<const Particle*> jets;
         for(size_t i=0;i!=m_jets_truth.size();++i) jets.push_back(&(m_jets_truth[i]));
         return util.EffMass(nlep,m_leptons_truth, njetreq, jets, met_p_truth() );
      }

   double SumJetEt(bool isTru=false,double absetacut=99.0);
      int L1SumJetEt(std::string vetostr="JF",double absetacut=99.0);
      double L2SumJetEt(bool EMscale=false,double absetacut=3.2);
      double weight_raw(void) const {return m_weight_raw;}
      double weight(void) const {return m_weight;}
      void weight(double w) {
         m_weight_raw=w;
         m_weight=(lumi>0 && xs>0 ? w*xs*lumi/(double)m_req_events : w);
      }
  
      void print(int level=0);
  
      bool electron_cut_store(Electron & ele, bool tru=false);
      bool muon_cut_store(Muon & muo, bool tru=false);
      //bool neutrino_cut_store(Neutrino & nu, bool tru=false);

      bool tau_cut_store(const Tau & tau);
      bool jet_cut_store(const Jet & jet, bool tru=false);
      bool trk_cut_store(const Track & trk);
      bool vtx_cut_store(const Vertex & vtx);
      bool l1jet_cut_store(const L1Jet & em);
      bool l2jet_cut_store(const Jet & l2jet);
      bool l2bjet_cut_store(const L2BJet & em);
      bool efbjet_cut_store(const L2BJet & em);
      void l1emobj_cut_store(L1EMObj & em);
      void l2el_cut_store(L2El & em);
      void efel_cut_store(EFEl & em);
  
      double xs,lumi,m_jes,m_mets,m_jer;
      int m_event, m_req_events, m_runnr, m_evtnr,m_lumiblocknr;
      double m_etsum,m_etsum_truth;
      double m_metx,m_mety,m_metx_truth,m_mety_truth;
      std::map<TString,double> m_topovars;
      double m_weight,m_weight_raw;
      double m_l1_metx,m_l1_mety;
      double m_l2_metx,m_l2_mety;
      double m_ef_metx,m_ef_mety;
      double m_nuP;
      int m_nuN;
      double m_TE[64][100];
      int m_isemDil,m_iseeDil,m_ismmDil,m_isDil,m_isTauDil,m_isTTbarDil,
         m_is_1We,m_is_1Wm;
      Particles<Electron> m_electrons, m_electrons_truth, m_electrons_truth_raw,
         m_electrons_raw, m_electrons_loose, m_electrons_fakeable,
         m_electrons_noniso;
      //Particles<Neutrino> m_neutrinos, m_truth_neutrinos;
      Particles<Muon> m_muons, m_muons_truth, m_muons_truth_raw, m_muons_raw,
         m_muons_loose, m_muons_fakeable, m_muons_noniso;
      Particles<Tau> m_taus, m_taus_truth;
      Particles<Jet> m_jets, m_jets_truth;
      Particles<L1Jet> m_l1jets;
      Particles<Jet> m_l2jets;
      Particles<L2BJet> m_l2bjets, m_efbjets;
      Particles<L1EMObj> m_l1emobjs;
      Particles<L2El> m_l2els;
      Particles<EFEl> m_efels;
      Particles<Parton> m_partons;
      Particles<Particle> m_top_truth;
      Particles<Track> m_trks;
      Particles<Cell> m_cells;
      TrigDec m_trigdec;
      Particles_p<const Particle*> m_leptons, m_leptons_loose,
         m_leptons_truth;
      Rois_dict m_rois;
      AtlConfig cfg;
      AtlUtil util;
      TagRate tagrate;
      BeamSpot beamspot;
      Vertices m_vertex;


};

#endif  /* __ATLEVENT_H */
