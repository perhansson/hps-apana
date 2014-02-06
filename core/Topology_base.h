/**************************************************************************
 **
 **   File:         Topology_base
 **
 **   Description:  Base class for user analysis topologies
 ** 
 **   Author:       jorgen.sjolin@physto.se
 **
 **   Created:      Mon Apr 23 15:47:26 CEST 2007
 **   Modified:     
 **                   
 **************************************************************************/ 

#ifndef __TOPOLOGY_BASE_H
#define __TOPOLOGY_BASE_H

#include <map>
#include <iostream>
#include "AtlEvent.h"
#include <assert.h>

#include "TDirectory.h"
#include "TString.h"
#include "TProfile.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"

class Topology_base {
   public:
      Topology_base() : evt(0) {assert(false);}; // Bugfix for g++ 3.x
      Topology_base(AtlEvent *atlevt) : evt(atlevt) {};
      virtual ~Topology_base() {};
      virtual void analyze(const TString & prefix) {
         if (m_topo.find(prefix)!=m_topo.end())
            m_topo[prefix]->cut(prefix);
         else {
            std::cout << "Topology '" << prefix << "' not defined!" << std::endl;
            exit(1);
         }
      };
      virtual void finalize(void) {};
      void add_topology(const TString & prefix, Topology_base  *topo) {
         m_topo[prefix]=topo;
      }

   protected:
      float min_ppmetphi(const TLorentzVector & p1,
                         const TLorentzVector & p2,
                         const TLorentzVector & met) {
         float phi1=fabs(p1.DeltaPhi(met));
         float phi2=fabs(p2.DeltaPhi(met));
         return (phi1<phi2 ? phi1 : phi2);
      }
      virtual void cut(const TString & prefix);
      virtual void book(const TString & prefix, const TString & suffix);
      void ufill(TH1 *h, const double a) {h->Fill(a,evt->weight()>0 ? 1 : -1);}
      void wfill(TH1 *h, const double a) {h->Fill(a,evt->weight());}
      //void wfill(TH1 *h, const double a) {h->Fill(a,1.0);}
      void wfill(TH1 *h, const double a, const double w) {h->Fill(a,w);}
      void wfill2(TH2 *h, const double a, const double b)
      {h->Fill(a,b,evt->weight());}
      void wfill2(TH2 *h, const double a, const double b, const double w)
      {h->Fill(a,b,w);}
      void wfill2(TProfile *h, const double a, const double b)
      {h->Fill(a,b,evt->weight());}
      TH1* hist(const TString & prefix, const TString & suffix,
                const TString & name) {
         TH1* h1=(TH1*)gDirectory->Get(prefix+suffix+"_"+name);
         if (!h1) {
            std::cout << "Missing histogram " << prefix+suffix+"_"+name << std::endl;
            exit(1);
         }
         return h1;
      }
      TH2* hist2(const TString & prefix, const TString & suffix,
                 const TString & name) {
         TH2* h2=(TH2*)gDirectory->Get(prefix+suffix+"_"+name);
         if (!h2) {
            std::cout << "Missing histogram " << prefix+suffix+"_"+name << std::endl;
            exit(1);
         }
         return h2;
      }
      TTree* tree(const TString & type, const TString & ch) {
         TTree* t1=(TTree*)gDirectory->Get(type+ch);
         if (!t1) {
            std::cout << "Missing TTree " << type+ch << std::endl;
            exit(1);
         }
         return t1;
      }
      float histC(const TString & prefix, const TString & suffix,
                  const TString & name) {
         TH1* h1=(TH1*)gDirectory->Get(prefix+suffix+"_"+name);
         if (!h1)
            return 0.0;
         else
            return h1->Integral(-1,9999);
      }
      float histE(const TString & prefix, const TString & suffix,
                  const TString & name) {
         TH1* h1=(TH1*)gDirectory->Get(prefix+suffix+"_"+name);
         if (!h1)
            return 1.0;
         else
            return h1->Integral(-1,9999)/sqrt(h1->GetEntries());
      }
      bool isElectron(const Particle *p) const {
         return typeid(*p)==typeid(Electron);
      };
      bool isMuon(const Particle *p) const {
         return typeid(*p)==typeid(Muon);
      };

      double jetIP1D(bool truth=false, int j=0){
	double ip1dValue = -999.0;
	ip1dValue = jet(j,truth).IP1D_w();
	return ip1dValue;
      }


      double jetIP2D(bool truth=false, int j=0){
        double ip2dValue = -999.0;
        ip2dValue = jet(j,truth).IP2D_w();
        return ip2dValue;
      }
      double jetIP3D(bool truth=false, int j=0){
        double ip3dValue = -999.0;
        ip3dValue = jet(j,truth).IP3D_w();
        return ip3dValue;
      }

      double jetSV1IP3D(bool truth=false, int j=0){
        double sv1Value = -999.0;
        sv1Value = jet(j,truth).SV1IP3D_w();
        return sv1Value;

      }
      double jetProb(bool truth=false, int j=0){
        double pValue = -999.0;
        pValue = jet(j,truth).JetProb_w();
        return pValue;

      }

      int jetMatchIndex(bool truth=false, int j=0) {
         double minDR =10;
         double jetdR =10;
         int match_index =-1;
         
         for(int truth_index=0;truth_index<jets(!truth);++truth_index)
         {
            jetdR = jet(j,truth).p.DeltaR(jet(truth_index,!truth).p);
            if(jetdR < minDR)
            {
               minDR = jetdR;
               match_index = truth_index;
            }
         }
         if(minDR < 0.3)
            return match_index;
         else
            return -1;
         
      }



      bool isIsoJet(bool truth=false, int j=0) const {

	double jetdR =0;
	for(int ijet=0;ijet!=jets(truth);++ijet) {
          if(ijet!=j && jet(ijet,truth).p.Pt() > 7)
	    {
	      jetdR = jet(j,truth).p.DeltaR(jet(ijet,truth).p);
	      if(jetdR < 1.0)
		return false;
	    }
	
	}

	return true; 
      };


      AtlUtil & util(void) {return evt->util;};

      int rois(const TString & name) const {
         return evt->rois(name);
      };
      const Rois roi(const TString & name) const {
         return evt->roi(name);
      };
      int leptons(bool truth=false) const {
         return (truth ? evt->leptons_truth() : evt->leptons());
      };
      int leptons_loose(void) const {
         return evt->leptons_loose();
      };
      int electrons(bool truth=false) const {
         return (truth ? evt->electrons_truth() : evt->electrons());
      };
      int electrons_loose(bool truth=false) const {
         return (truth ? evt->electrons_truth() : evt->electrons_loose());
      };
      int electrons_raw(int bit=-1) const { // N-1 cut electrons, -1=no cuts
         int n=0;
         if (bit==-1) return evt->electrons_raw();
         for (int i=0; i<evt->electrons_raw(); ++i)
            if (!(evt->electron_raw(i).IDbits()&(~(1<<bit)))) ++n;
         return n;
      };
      const Electron & electron_raw(const int idx, const int bit=-1) const {
         int n=0;
         if (bit==-1) return evt->electron_raw(idx);
         for (int i=0; i<evt->electrons_raw(); ++i) {
            if (!(evt->electron_raw(i).IDbits()&(~(1<<bit)))) {
               if (idx==n) return evt->electron_raw(i);
               ++n;
            }
         }
         std::cout << "Error electron raw: n=" << n << ", index=" << idx
                   <<", bit=" << bit << std::endl;
         exit(1);
      };
      int trks(void) const {
         return evt->trks();
      };
      int cells(void) const {
         return evt->cells();
      };
      int muons(bool truth=false) const {
         return (truth ? evt->muons_truth() : evt->muons());
      };

      /*
      int neutrinos(bool truth=false) const {
         return (truth ? evt->neutrinos_truth() : evt->neutrinos());
      };
      */
      int muons_raw(int bit=-1) const { // N-1 cut muons, -1=no cuts
         int n=0;
         if (bit==-1) return evt->muons_raw();
         for (int i=0; i<evt->muons_raw(); ++i)
            if (!(evt->muon_raw(i).IDbits()&(~(1<<bit)))) ++n;
         return n;
      };
      const Muon & muon_raw(const int idx, const int bit=-1) const {
         int n=0;
         if (bit==-1) return evt->muon_raw(idx);
         for (int i=0; i<evt->muons_raw(); ++i) {
            if (!(evt->muon_raw(i).IDbits()&(~(1<<bit)))) {
               if (idx==n) return evt->muon_raw(i);
               ++n;
            }
         }
         std::cout << "Error muon raw: n=" << n << ", index=" << idx
                   <<", bit=" << bit << std::endl;
         exit(1);
      };
      int jets(bool truth=false) const {
         return (truth ? evt->jets_truth() : evt->jets());
      };
      int taus(bool truth=false) const {
         return (truth ? evt->taus_truth() : evt->taus());
      };
      int partons(void) const {
         return evt->partons();
      };
      int l1jets(void) const {return evt->l1jets();};
      int l2jets(void) const {return evt->l2jets();};
      Particles<L2BJet> GetHLTBjets(const std::string& level, const std::string& chain) const {
         return evt->GetHLTBjets(level,chain);
      };
      int l2bjets(const std::string chain="") const {return evt->l2bjets(chain);};
      int efbjets(const std::string chain="") const {return evt->efbjets(chain);};
      int l1emobjs(void) const {return evt->l1emobjs();};
      int l2els(void) const {return evt->l2els();};
      int efels(void) const {return evt->efels();};
      int vertices(const int& mintrks=0){return evt->vertices(mintrks);}
      const Particle * lepton(const int i, bool truth=false) const {
         return (truth ? evt->lepton_truth(i) : evt->lepton(i));
      };
      const Particle * lepton_loose(const int i) const {
         return evt->lepton_loose(i);
      };
      const Electron & electron(const int i, bool truth=false) const {
         return (truth ? evt->electron_truth(i) : evt->electron(i));
      };
      const Electron & electron_loose(const int i, bool truth=false) const {
         return (truth ? evt->electron_truth(i) : evt->electron_loose(i));
      };
      const Track & trk(const int i) const {
         return evt->trk(i);
      };
      const Cell & cell(const int i) const {
         return evt->cell(i);
      };
      const Muon & muon(const int i, bool truth=false) const {
         return (truth ? evt->muon_truth(i) : evt->muon(i));
      };
      const Jet & jet(const int i, bool truth=false) const {
         return (truth ? evt->jet_truth(i) : evt->jet(i));
      };
      const Tau & tau(const int i, bool truth=false) const {
         return (truth ? evt->tau_truth(i) : evt->tau(i));
      };
      const Parton & parton(const int i) const {
         return evt->parton(i);
      };
      const L1Jet & l1jet(const int& i) const {return evt->l1jet(i);};
      const Jet & l2jet(const int& i) const {return evt->l2jet(i);};
      const L2BJet & l2bjet(const int& i) const {return evt->l2bjet(i);};
      const L2BJet & efbjet(const int& i) const {return evt->efbjet(i);};
      const L1EMObj * l1emobj(const int i) const {return evt->l1emobj(i);};
      const L2El * l2el(const int i) const {return evt->l2el(i);};
      const EFEl * efel(const int i) const {return evt->efel(i);};
      double l1_met(void) const {return evt->l1_met();}
      double l2_met(void) const {return evt->l2_met();}
      double ef_met(void) const {return evt->ef_met();}
      double met(bool truth=false) const {
         return (truth ? evt->met_truth() : evt->met());
      }
      const TLorentzVector met_p(bool truth=false) const {
         return (truth ? evt->met_p_truth() : evt->met_p());
      }

      //dans adding function
      
      double E2ratio(bool truth = false)
      {
	double Et0, Et1;
	double Etsum =0;
	double Eratio = -1;
	
	if(jets(truth) > 2)
          {
            for(int ijet=0;ijet!=jets(truth);++ijet)
              {
		if(ijet == 0)
		  Et0 = jet(ijet,truth).p.Et();
		if(ijet ==1)
                  Et1 =jet(ijet,truth).p.Et();
		
		Etsum +=jet(ijet,truth).p.Et();
              }
	    Eratio = (Et0 + Et1)/Etsum;
	  }
        return Eratio;
      }


      double Pt2ratio(bool truth = false)
      {
        double Pt0, Pt1;
        double Ptsum =0;
        double Ptratio = -1;

        if(jets(truth) > 2)
          {
            for(int ijet=0;ijet!=jets(truth);++ijet)
              {
                if(ijet == 0)
                  Pt0 = jet(ijet,truth).p.Pt();
                if(ijet ==1)
                  Pt1 =jet(ijet,truth).p.Pt();

                Ptsum +=jet(ijet,truth).p.Pt();
              }
            Ptratio = (Pt0 + Pt1)/Ptsum;
          }
        return Ptratio;
      }


      TLorentzVector mht_p(bool truth = false) 
      {
         TLorentzVector sumPt;
         for(int ijet=0;ijet!=jets(truth);++ijet) 
         {
            sumPt +=jet(ijet,truth).p;
         }
         return sumPt;
      }

      double mht(bool truth = false) 
      {
         TLorentzVector sumPt = mht_p(truth);
         return sumPt.Pt();
      }
      

      double MetMhtAsym(bool truth = false)
      {
	TLorentzVector sumPt;
	double Mht =0;
	double Asym = -1000;
	double Met = met(truth);
	
	if(jets(truth))
	  {
	    for(int ijet=0;ijet!=jets(truth);++ijet) 
	      {
		sumPt +=jet(ijet,truth).p;
	      }
	    Mht = sumPt.Pt();
	    Asym = (Met - Mht) / (Met + Mht);
	  }
	return Asym;
      }
      
	
      double j123(bool truth=false)
      {
         bool foundJets = false;
         double J1pt, J2pt, J0pt, tot_pt;

         for(int ijet=0;ijet!=jets(truth);++ijet) {
            if(ijet ==0)
               J0pt = jet(ijet,truth).p.Pt();
            if(ijet ==1)
               J1pt = jet(ijet,truth).p.Pt();
            if(ijet ==2)
            {
               J2pt = jet(ijet,truth).p.Pt();
               foundJets = true;
            }
         }
         if(foundJets == false)
            return -1;
         tot_pt = J1pt + J2pt + J0pt;
         return tot_pt;
      }

      double METoverSumEt(bool truth=false)
      {	
         double sum_et=0.0;
         for(int ijet=0;ijet!=jets(truth);++ijet) {
            sum_et += jet(ijet,truth).p.Et();
         }

         //cout << "DEBUG " <<  met(truth) << "/ " <<sum_et << endl;
         return met(truth)/sum_et;
      }

   
      double alpha_t(bool truth=false)
      {
        double j0M, j0Pt, j1M, j1Pt;
        bool foundJets = false;
        double alpha =0;
        for(int ijet=0;ijet!=jets(truth);++ijet) {
          if(ijet ==0)
            {
              j0M = jet(ijet,truth).p.M();
              j0Pt = jet(ijet,truth).p.Pt();
            }
          if(ijet ==1)
            {
              j1Pt = jet(ijet,truth).p.Pt();
              j1M = jet(ijet,truth).p.M();
              foundJets = true;
            }
        }

        if(!foundJets)
          return -1;

        alpha = j1Pt/(j0M+j1M);
        return alpha;
      }
      
      
      
      double Egap123(bool truth=false)
      {
         bool foundJets = false;
         double E1, E2, E0, EgapRatio, Egap12, Egap23;
	
	
         for(int ijet=0;ijet!=jets(truth);++ijet) {
            if(ijet ==0)
               E0 = jet(ijet,truth).p.E();
            if(ijet ==1)
               E1 = jet(ijet,truth).p.E();
            if(ijet ==2)
            {
               E2 = jet(ijet,truth).p.E();
               foundJets = true;
            }
         }
         if(foundJets == false)
            return -1;
         Egap12 = E0 - E1;
         Egap23 = E1 - E2;
         EgapRatio = Egap12/Egap23;
         return fabs(EgapRatio);
      }
      
      double responseMu(bool truth=false, int t_index = 0,int r_index=0)
      {
        double jPt, true_jPt, pt_ratio;

        if(!truth)
          {
            jPt = jet(r_index,truth).p.Pt() + muon(0,truth).p.Pt();
            true_jPt = jet(t_index,!truth).p.Pt() + muon(0,!truth).p.Pt();
            pt_ratio = jPt/true_jPt;

            return fabs(pt_ratio);
          }
        else
          return -1;
      }



      double responseNew(bool truth=false, int t_index = 0,int r_index=0)
      {
	double jPt, true_jPt, pt_ratio;

	if(!truth)  
	  {
	    jPt = jet(r_index,truth).p.Pt();
	    true_jPt = jet(t_index,!truth).p.Pt();
	    pt_ratio = jPt/true_jPt;
	    
	    return fabs(pt_ratio);
	  }
	else
	  return -1;
      }

      double responseE(bool truth=false, int t_index = 0,int r_index=0)
      {
        double jE, true_jE, E_ratio;

        if(!truth)
          {
            jE = jet(r_index,truth).p.E();
            true_jE = jet(t_index,!truth).p.E();
            E_ratio = jE/true_jE;

            return fabs(E_ratio);
          }
        else
          return -1;
      }



      double responseD(bool truth=false, int j=0)
      {
	double jPt, true_jPt, pt_ratio;

	//if(jets(!truth) >= j)
	if(!truth)  
	  {
	    jPt = jet(j,truth).p.Pt();
	    true_jPt = jet(j,!truth).p.Pt();
	    pt_ratio = jPt/true_jPt;
	    
	    return fabs(pt_ratio);
	  }
	else
	  return -1;
      }
      

      double sumjetPt(bool truth=false){
         double sum_pt=0.0;
         for(int ijet=0;ijet!=jets(truth);++ijet) {
            sum_pt += jet(ijet,truth).p.Pt();
         }
         return sum_pt;
      }

      double sumtrackPt() {
         return sumtrackvec().Pt();
      }
      
      TLorentzVector sumtrackvec() {
         TLorentzVector sumtracks;
         for(int itrk=0;itrk!=trks();++itrk) {
            sumtracks += trk(itrk).p;
         }
         return sumtracks;
      }
      
      double invmass(const Particle& p1, const Particle& p2) {
	return (p1.p+p2.p).M();
      }

      double etsum(bool truth=false) const {
         return (truth ? evt->etsum_truth() : evt->etsum());
      }
      double metx(bool truth=false) const {
         return (truth ? evt->metx_truth() : evt->metx());
      }
      double mety(bool truth=false) const {
         return (truth ? evt->mety_truth() : evt->mety());
      }
      double evtopo(const TString& var) const {
         //    return (truth ? evt->mety_truth() : evt->mety());
         return (evt->evtopo(var));
      }
      double Sphericity(bool truth=false) const {
         return (truth ? evt->Sphericity_truth() : evt->Sphericity() );}
      double EffectiveMass(bool truth=false,int nlep=0,int njetreq=4) const {
         return (truth ? evt->EffectiveMass_truth(nlep,njetreq) :
                 evt->EffectiveMass(nlep,njetreq));}
      int TrigDecision(TString trigger, bool truth=false)
      {return truth ? 1 : evt->TrigDecision(trigger);}
      const std::map< TString, int>* TrigDecisions(void) const  {
         return evt->m_trigdec.getAllTrigDec();}
      const std::vector<TString> GetAllTrigDecisionNames(void) const {
         return evt->m_trigdec.GetAllTrigDecisionNames();}
      void PrintTrigDecisions(void) {return evt->m_trigdec.print();}
      void FillTriggerEfficiencies(TString prefix,TString suffix,TDirectory* dir) {
         evt->m_trigdec.FillTriggerEfficiencies(prefix,suffix,dir);}
      void PrintTriggerEfficiencies(TDirectory* dir,TString selection="diem_",TString mode="EFF") {
         evt->m_trigdec.PrintTriggerEfficiencies(dir,selection,mode);}
      double weight(void) const {return evt->weight();}
      void weight(double w) {evt->weight(w);}
      bool isDil(void) const {return evt->m_isDil;}
      bool isTauDil(void) const {return evt->m_isTauDil;}
      bool isTTDil(void) const {return evt->m_isTTbarDil;}
      int get_debug(void) {return evt->cfg.get_debug();}
      void print(int level=0) { evt->print(level);}
      int SumJetEt(bool isTru=false,double absetacut=99.) { return evt->SumJetEt(isTru,absetacut);};
      int L1SumJetEt(std::string str="",double absetacut=99.) { return evt->L1SumJetEt(str,absetacut);};
      double L2SumJetEt(bool EMscale=false,double absetacut=3.2) { return evt->L2SumJetEt(EMscale,absetacut);};
      bool passSUSYJetMetDphiCut(const bool& isTru,const int& njet, const double& min_cut) {
         assert(jets(isTru)>=njet);
         for(int i=0;i!=njet;++i) {if( TMath::Abs( jet(i,isTru).p.DeltaPhi( met_p(isTru) ) ) < min_cut) return false;}
         return true;
      };

      std::map<TString, Topology_base*> m_topo;
      std::map<TString, bool> _h;      
      AtlEvent *evt;
};

#endif  /* __TOPOLOGY_BASE_H */
