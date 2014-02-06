/**************************************************************************
 **
 **   File:         AtlUtil.h
 **
 **   Description:  Utility functions for analysis. E.g. cut book keeping.
 **
 **
 **   Author:       J. Sjolin
 **
 **   Created:      Mon Sep 19 16:20:04 CEST 2005
 **   Modified:
 **
 **
 **
 **************************************************************************/

#ifndef __ATLUTIL_H
#define __ATLUTIL_H

#include <map>
#include <fstream>
#include <iomanip>
#include <cassert>
#include "TString.h"
#include "TRandom3.h"
#include "TLorentzVector.h"
#include "Electron.h"
#include "Muon.h"
#include "Jet.h"
#include "Roi.h"
#include "Parton.h"
#include "Particle.h"
#include "solvtl.h"
#include "TMatrixDSymEigen.h"
#include "TMatrixTSym.h"
#include "TVectorD.h"
#include "TKey.h"
#include "TDirectory.h"
#include "TClass.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
//#include "TrigTrackJetFinderTool.h"


//class TBspline3;


bool cmpTStringSize(const TString& a, const TString& b) {
  return a.Length() < b.Length();
}
bool pcmpTStringSize(const TString a, const TString b) {
  return a.Length() < b.Length();
}

template <class T>
std::vector<TString> getSortedKeys(const std::map<TString,T>& m, bool fromSize=true) {
  std::vector<TString> k;
  typename std::map<TString,T>::const_iterator i = m.begin();
  typename std::map<TString,T>::const_iterator iE = m.end();
/*   typedef std::map<TString,T>::const_iterator VecIterConst; */
/*   VecIterConst i  = m.begin(); */
/*   VecIterConst iE = m.end(); */
  for(;i!=iE;++i) { k.push_back(i->first); }	
  if(fromSize)  std::sort(k.begin(),k.end(),pcmpTStringSize);
  else           std::sort(k.begin(),k.end());
  return k;
}


class AtlUtil {
   public:
      AtlUtil(void) {
         
         Bmesons = listBmesons();
         Cmesons = listCmesons();
         std::cout << "AtlUtil:: created B meson list with " <<
            Bmesons.size() << " Bmesons" << std::endl;
         std::cout << "AtlUtil:: created C meson list with " <<
            Cmesons.size() << " Cmesons" << std::endl;         
         jperm = GetJetPermutations();      
         std::cout << "Using mt=" << mt() << " GeV, mw=" << mw() <<
            " GeV, mb=" << mb() << " GeV" <<  std::endl;
      };
      ~AtlUtil(void) {
//          if(fTF[0]) delete fTF[0];
//          if(fTF[1]) delete fTF[1];
      }
      bool is_electron_fake(const Electron &) {return true;}
      bool is_muon_fake(const Muon &) {return true;}
      double mt(void) const {return 175.0;}
      double mw(void) const {return 80.4;}
      //double mb(void) const {return 4.7;}
      double mb(void) const {return 0.;}
      
      double trig_unfold(const TLorentzVector & p) const {
         if (!htrg) {
            static bool warn=true;
            if (warn) {
               std::cout << "unfold_trig called without trig curves!"<<std::endl;
               std::cout << "No more warnings are issued!" << std::endl;
               warn=false;
            }
            return 1.0;
         }
         return htrg->GetBinContent(htrg->FindBin((p.Pt()>59?59:p.Pt()),
                                                  fabs(p.Eta())));
      }

      void cut(const TString &obj,
               const TString &category,
               const TString &value,
               const bool cut,
               const int cut_bit,
               int &global_cut_bits) // Individual bits used for N-1 plots
      {
         global_cut_bits = global_cut_bits | (cut ? cut_bit : 0);
         if (!global_cut_bits) {
            TString key=obj+";"+category+";"+value;
            if (m_cutmap.find(key)==m_cutmap.end())
               m_cutmap[key]=1;
            else
               m_cutmap[key]+=1;
         }
      };
  
      void cnt1(const TString &obj,
                const TString &category,
                const TString &value)
      {
         TString key=obj+";"+category+";"+value;
         if (m_cutmap.find(key)==m_cutmap.end())
            m_cutmap[key]=1;
         else
            m_cutmap[key]+=1;
      };
  
      int cnt(const TString &obj,
              const TString &category,
              const TString &value)
      {
         TString key=obj+";"+category+";"+value;
         if (m_cutmap.find(key)==m_cutmap.end())
            return 0;
         else
            return m_cutmap[key];
      }
      
      
      
      void displayCutMap(TString obj="",
			 TString category="",
			 TString value="") {
	std::vector<TString> keys = getSortedKeys(m_cutmap,false);
	std::cout << "\nCut map ("<< obj << "," << category << "," << value << "):" << std::endl;
	std::vector<TString>::const_iterator i = keys.begin();
	std::vector<TString>::const_iterator iE= keys.end();
	for(;i!=iE;++i) {
	  if(obj!="") { 
	    if(i->Index(obj.Data()) == -1) {continue;}
	  }
	  if(category!="") { 
	    if(i->Index(category.Data()) == -1) {continue;}
	  }
	  if(value!="") { 
	    if(i->Index(value.Data()) == -1) {continue;}
	  }
	  //This key is selected
	  std::cout << std::setprecision(1) << std::fixed 
		    << std::setw(50) << *i << std::setw(20) << m_cutmap[*i] <<" +- "
		    << std::setw(3) << ( m_cutmap[*i] !=0 ? sqrt((double)m_cutmap[*i]) : -1. )
	  << std::endl;
	}
	return;
      }

      void printCutMap(TString object="",
		       TString category="",
		       TString name="") {
	
	
	std::cout << "\nCut list ("<< object << "," << category << "," << name << "):" << std::endl;
	
	//Loop over all the histos and find the matching names
	TIter nextkey( gDirectory->GetList() );
	std::map<TString,TH1*> m;
	while ( TObject *obj = nextkey() ) {      
	  // read object 
	  if ( obj->IsA()->InheritsFrom( "TH1" ) ) {
	    // descendant of TH1
	    TH1 *h1 = (TH1*)obj;
	    //check the name
	    TString Name = h1->GetName();
	    if(object!="") { 
	      if(Name.Index(object.Data()) == -1) {continue;}
	    }
	    if(category!="") { 
	      if(Name.Index(category.Data()) == -1) {continue;}
	    }
	    if(name!="") { 
	      if(Name.Index(name.Data()) == -1) {continue;}
	    }
	    //This key is selected
	    m[Name] = h1;
	  }
	}
	//sort
	std::vector<TString> keys = getSortedKeys(m,true);
	for(std::vector<TString>::const_iterator i = keys.begin();
	    i!=keys.end();++i) {
	  TString Name = *i;	
	  TH1* h1 = m[Name];
	  std::cout << std::setprecision(1) << std::fixed 
		    << std::setw(50) << Name << std::setw(20) << h1->Integral(-1,9999999)
		    <<" +- " << std::setw(3) << (h1->GetEntries()!=0?h1->Integral(-1,9999999)/sqrt(h1->GetEntries()):-1.)
		    << std::endl;
	  
	}
      }



      void printRatesMap(double xs, double lumi,
			 TString object="",
			 TString category="",
			 TString name="CAND") {
	
	
	std::cout << "\n----- Rate map" << std::endl;
	std::cout << "  ("<< object << "," << category << "," << name << ")\n" << std::endl;
	std::cout << "Luminosity " << std::scientific << lumi << "cm^-2s^-1" << std::endl;
	int Nd = cnt(object,"","CAND");
	if (!Nd) {
	  std::cout << "no events in denominator " << object+""+"_CAND" << std::endl;
	  return;
	}
	
	std::cout << "Denominator: " << object+"_CAND" << std::endl;
	
	std::vector<TString> keys = getSortedKeys(m_cutmap,true);
	
	for(std::vector<TString>::const_iterator i = keys.begin();
	    i!=keys.end();++i) {
	  TString key = *i;	
	  if(object!="") { 
	    if(!key.Contains(object)) continue;
	  }
	  if(category!="") { 
	    if(!key.Contains(category)) continue;
	  }
	  if(name!="") { 
	    if(!key.Contains(name)) continue;
	  }
	  int N = m_cutmap[key];
	  //This key is selected
	  //std::cout << "rate for key="<<key<< " with Nd=" << Nd << " N=" << N <<  endl;
	  std::cout << std::scientific
		    << std::setw(50) << key << std::setw(20) 
		    << rate((double)N,(double)Nd,xs, lumi)
		    << " +- "
		    << rateError((double)N,(double)Nd,xs, lumi)
		    << " Hz" << std::endl;
	}
      }
      

      double collinear_mass(const TLorentzVector & tau,
                            const TLorentzVector & lep,
                            const double metx,
                            const double mety) const
      {
         float det=tau.Px()*lep.Py()-tau.Py()*lep.Px();
         float x1=det/(metx*lep.Py()-mety*lep.Px()+det);
         float x2=det/(-metx*tau.Py()+mety*tau.Px()+det);
         float mz=-1;
         if (x1>0 && x1<1 && x2>0 && x2<1) mz=(tau+lep).M()/sqrt(x1*x2);
         return mz;
      }

      double collinear_mass_org(const TLorentzVector & tau,
                                const TLorentzVector & lep,
                                const double metx,
                                const double mety) const
      {
         double myZmass = -1.0;
         double rexy = tau.Py()/tau.Px();
         double rex = tau.Px()/tau.P();
         double rcx = lep.Px()/lep.P();
         double rcy = lep.Py()/lep.P();
         double ta = mety-rexy*metx;
         double tb = rcy-rexy*rcx;
         double eNu1 = ta/tb;
         double eNu2 = (metx-rcx*eNu1)/rex;
      
         //if (tau.DeltaPhi(lep) < 2.7 || tau.DeltaPhi(lep) > 3.6 ) {
         if (true) {
            if(eNu1>0 && eNu2>0) {
               double eTau1 = lep.P()+eNu1;
               double eTau2 = tau.P()+eNu2;
               double cosTheta = (lep.Px()*tau.Px()+lep.Py()*tau.Py()+
                                  lep.Pz()*tau.Pz())/(lep.P()*tau.P());
               myZmass = 2*eTau1*eTau2*(1-cosTheta);
               myZmass = sqrt(myZmass);
            }
         }
         return myZmass;
      }

      float ctm(const TLorentzVector &p1,
                const TLorentzVector &p2,
                const TLorentzVector &p3,
                const TLorentzVector &p4) {
         if (fabs(p4.Z())>0) {
            std::cout << "Illigal use of the cluster mass!" << std::endl;
            exit(1);
         }
         return ctm(p1+p2+p3,p4);
      }

      float ctm(const TLorentzVector &p1,const TLorentzVector &p2) {
         if (fabs(p2.Z())>0) {
            std::cout << "Illigal use of the cluster mass!" << std::endl;
            exit(1);
         }
         return sqrt(pow(sqrt(pow(p1.M(),2)+pow(p1.Pt(),2))+
                         p2.Pt(),2)-pow((p1+p2).Pt(),2));
      }

      //Neutrino z component from W mass constraint
      //Based on /offline/PhysicsAnalysis/SUSYPhys/SUSYValidation/src/EVtopRec.xxx
      //Added by EBs on May 11, 2009
      float pnuz(const TLorentzVector &plep, const TLorentzVector &met_p) {
         double mw2 = mw()*mw();
         double pet2 = pow(plep.Perp(),2);
         double pnut2 = pow(met_p.Perp(), 2);
         double petpnut = plep.Px()*(met_p.Px()) + plep.Py()*(met_p.Py());
         double pez = plep.Pz();

         double a = 4*pet2;
         double b = -4*pez*(mw2 + 2*petpnut);
         double c = -mw2*mw2 -4*mw2*petpnut + 4*pez*pez*pnut2;
         double d = b*b - 4*a*c;
         double pnu_z;

         //No real solutions or one solution
         if( d <= 0)  pnu_z=-b/(2*a);
         else { //Two real solutions
            d = sqrt( b*b - 4*a*c );
            double pnuz1 = (-b + d)/(2*a);
            double pnuz2 = (-b - d)/(2*a);
            //Choose smallest |pnuz|
            if(fabs(pnuz1) < fabs(pnuz2)) pnu_z=pnuz1;
            else pnu_z=pnuz2;

         }
         return pnu_z;
      }

      float pnuz_real(const TLorentzVector &plep, const TLorentzVector &met_p) {
         //return pnuz only if real solutions exist
         //otherwise return -100000
         double mw2 = mw()*mw();
         double pet2 = pow(plep.Perp(),2);
         double pnut2 = pow(met_p.Perp(), 2);
         double petpnut = plep.Px()*(met_p.Px()) + plep.Py()*(met_p.Py());
         double pez = plep.Pz();

         double a = 4*pet2;
         double b = -4*pez*(mw2 + 2*petpnut);
         double c = -mw2*mw2 -4*mw2*petpnut + 4*pez*pez*pnut2;
         double d = b*b - 4*a*c;
         double pnu_z;

    
         if( d < 0)  { //No real solution
            pnu_z=-100000;
            //cout << "r:Imag " << endl;
         }
         else { //Two real solutions
            //cout << "r:Real " << endl;
            d = sqrt( b*b - 4*a*c );
            double pnuz1 = (-b + d)/(2*a);
            double pnuz2 = (-b - d)/(2*a);
            //Choose smallest |pnuz|
            if(fabs(pnuz1) < fabs(pnuz2)) pnu_z=pnuz1;
            else pnu_z=pnuz2;
         }

         return pnu_z;
      }

      float pnuz_imag(const TLorentzVector &plep, const TLorentzVector &met_p) {
         //return Re(pnuz) only if NO real solutions exist
         //otherwise return -100000
         double mw2 = mw()*mw();
         double pet2 = pow(plep.Perp(),2);
         double pnut2 = pow(met_p.Perp(), 2);
         double petpnut = plep.Px()*(met_p.Px()) + plep.Py()*(met_p.Py());
         double pez = plep.Pz();

         double a = 4*pet2;
         double b = -4*pez*(mw2 + 2*petpnut);
         double c = -mw2*mw2 -4*mw2*petpnut + 4*pez*pez*pnut2;
         double d = b*b - 4*a*c;
         double pnu_z;

    
         if( d < 0)  { //No real solutions
            pnu_z=-b/(2*a);
            //cout << "i:Imag " << endl;
         }
         else { //real solutions
            pnu_z=-100000;
            //cout << "i:Real " << endl;
         }

         return pnu_z;    
      }

      //Invariant mass, using neutrino z component from W mass constraint
      //1l + njets configuration
      float invmass(const TLorentzVector &plep, const TLorentzVector &met_p, 
                    const TLorentzVector &pjets) {
         if (fabs(met_p.Z())>0) {
            std::cout << "Illegal use of the invariant mass from nu z component (W mass constraint)!" << std::endl;
            exit(1);
         }

         float pnu_z=pnuz(plep, met_p);
         TLorentzVector pnu;
         pnu.SetXYZM(met_p.X(), met_p.Y(), pnu_z, 0);

         return (plep + pnu + pjets).M();

      }

      float invmass_real(const TLorentzVector &plep, const TLorentzVector &met_p, 
                         const TLorentzVector &pjets) {
         if (fabs(met_p.Z())>0) {
            std::cout << "Illegal use of the invariant mass from nu z component (W mass constraint)!" << std::endl;
            exit(1);
         }

         float pnu_z=pnuz_real(plep, met_p);
         float invm;
         if(pnu_z<-99999.) {
            invm=0.1;
         }
         else {
            TLorentzVector pnu;
            pnu.SetXYZM(met_p.X(), met_p.Y(), pnu_z, 0);
            invm=(plep + pnu + pjets).M();
         }
         return invm;

      }

      float invmass_imag(const TLorentzVector &plep, const TLorentzVector &met_p, 
                         const TLorentzVector &pjets) {
         if (fabs(met_p.Z())>0) {
            std::cout << "Illegal use of the invariant mass from nu z component (W mass constraint)!" << std::endl;
            exit(1);
         }

         float pnu_z=pnuz_imag(plep, met_p);
         float invm;
         if(pnu_z<-99999.) {
            invm=0.1;
         }
         else {
            TLorentzVector pnu;
            pnu.SetXYZM(met_p.X(), met_p.Y(), pnu_z, 0);
            invm=(plep + pnu + pjets).M();
         }
         return invm;

      }


  
      void print(const TLorentzVector& p) const {
         std::cout << "TLorentzVector" << std::endl;
         std::cout << "    E      : " << p.E() << std::endl;
         std::cout << "    Et     : " << p.Et() << std::endl;
         std::cout << "    Pt     : " << p.Pt() << std::endl;
         std::cout << "    Eta    : " << p.Eta() << std::endl;
         std::cout << "    Phi    : " << p.Phi() << std::endl;
         std::cout << "    Mass   : " << p.M() << std::endl;
         std::cout << "    Px     : " << p.Px() << std::endl;
         std::cout << "    Py     : " << p.Py() << std::endl;
         std::cout << "    Pz     : " << p.Pz() << std::endl;
      }
  
      float EffMass(const TLorentzVector &p1,
                    const TLorentzVector &p2,
                    const TLorentzVector &p3,
                    const TLorentzVector &p4,
                    const TLorentzVector &p5) const {
    
         if (fabs(p5.Z())>0) {
            std::cout << "Illigal use of the effective mass!" << std::endl;
            exit(1);
         }
         return (p1.Pt()+p2.Pt()+p3.Pt()+p4.Pt()+p5.Pt());
      }
  
      float EffMass(const int& Nlep,
                    const Particles_p<const Particle*>& lep,
                    const TLorentzVector &p1,
                    const TLorentzVector &p2,
                    const TLorentzVector &p3,
                    const TLorentzVector &p4,
                    const TLorentzVector &p5) const {
    
         if (fabs(p5.Z())>0) {
            std::cout << "Illigal use of the effective mass!" << std::endl;
            exit(1);
         }
         assert(lep.size()>=static_cast<size_t>(Nlep));
         double effm = p1.Pt()+p2.Pt()+p3.Pt()+p4.Pt()+p5.Pt();
         for(size_t i=0;i<static_cast<size_t>(Nlep);++i) effm+=((lep[i]->p).Pt()); //optionally to include all leptons         
         return effm;
      }
      
      float EffMass(const int& Nlep,
                    const Particles_p<const Particle*>& lep,
                    const int& Njets,
                    const Particles_p<const Particle*>& jets,
                    const TLorentzVector &p5) const {
         
         if (fabs(p5.Z())>0) {
            std::cout << "Illigal use of the effective mass!" << std::endl;
            exit(1);
         }
         assert(lep.size()>=static_cast<size_t>(Nlep));
         assert(jets.size()>=static_cast<size_t>(Njets));
         double effm = 0.;
         for(size_t i=0;i<static_cast<size_t>(Nlep);++i) effm+=((lep[i]->p).Pt()); //optionally to include all leptons         
         for(size_t i=0;i<static_cast<size_t>(Njets);++i) effm+=((jets[i]->p).Pt()); //optionally to include all leptons         
         effm+=p5.Pt();
         return effm;
      }
  
      bool ttbarFullTruth( const Particles<Parton>& partons ) {
         //std::cout << " in Atlutil::ttbarFullTruth() " << std::endl;
         if(partons.size()>0) {
            bool bFromT=false;
            bool bbarFromTbar=false;
            for( int i=0; i!=static_cast<int>(partons.size()); ++i) {
               if(partons[i].pdgId()==5 && partons[i].mother1()==6) bFromT=true;
               if(partons[i].pdgId()==-5 && partons[i].mother1()==-6) bbarFromTbar=true;
            }//i
            // std::cout << " this event has bfromt=" << bFromT << ", and bbarfromtbar=" << bbarFromTbar << std::endl;
      
            if( bFromT && bbarFromTbar ) return true;
         }
         return false;
      } //ttbarFullTruth
  
      std::vector<int> listBmesons() {
         ifstream Bmesonlist("../../utils/Bmesons.txt");
         std::vector<int> mesons;
         int s;
         while (Bmesonlist >> s) {
            //cout << "s = " << s << endl;
            mesons.push_back(s);
         }
         sort(mesons.begin(), mesons.end());
    
         return mesons;
      }  //listBmesons()
  
  
      std::vector<int> listCmesons() {
         ifstream Cmesonlist("../../utils/Cmesons.txt");
         std::vector<int> mesons;
         int s;
         while (Cmesonlist >> s) mesons.push_back(s);
         sort(mesons.begin(), mesons.end());
    
         return mesons;
      }  //listCmesons()
      
      template <class T>
      std::map<std::string,std::vector<size_t> > CountMesonsInJet(const T j, 
                                                                  const Particles<Parton> partons, 
                                                                  float maxdR) {
         
         //std::cout << "in jetMatching()" << std::endl;
         
         // *****************************************************************    //
         // This function takes a jet and matches B & D mesons of a given flavor //
         //     a specific mother to be matched.                                 //
         //                                                                      //
         // It returns a vector of indices to the matched particles              //
         // *****************************************************************    //
         
         const T* jet = &j;
         bool debug = false;
         
         std::map<std::string,std::vector<size_t> > matched;
         
         
         if(debug) std::cout << "Matching particles to jet with pT,eta,phi " << jet->p.Pt() << "," << jet->p.Eta() << "," << jet->p.Phi() << std::endl;
         if(debug) std::cout << "Start loop over " << partons.size() << " MC particles"<< std::endl;
         
         float dr = -1.;
         for (size_t i=0; i!=partons.size(); ++i) { // loop over all MC particles
            const Parton * MCparticle = &(partons[i]); 
            int pdg = MCparticle->pdgId();
            int abs_pdg = TMath::Abs(pdg);
            
            //computethe delta R first since it should be quicker than to search for the mesons (??)
            
            dr = (jet->p).DeltaR(MCparticle->p); 
            
            if( dr < maxdR ) {
               
               //This particle is within the matching cone 
               
               std::string flavor("");
               
               if (binary_search(Bmesons.begin(),Bmesons.end(),abs_pdg)) {
                  flavor="B";
               }
               
               if (binary_search(Cmesons.begin(),Cmesons.end(),abs_pdg)) {
                  assert(flavor=="");
                  flavor="C";
               }
               
               //NOTE that I'm not checking if there is another jet closer
               
               if(flavor!="") {                  
                  //this particle is a meson
                  matched[flavor].push_back(i);
               }
            }
         }
         
         return matched;
         
      }







      template <class T>
	std::pair<int,int> TruthMatching(int& parton_index, 
					 const T j, 
					 const Particles<T> jets, 
					 const Particles<Parton> partons, 
					 float maxdR=0.5,
					 int mother=0) {
	
	//std::cout << "in jetMatching()" << std::endl;
	
	// ***************************************************************** //
	// This function takes a jet and matches it to B-mesons, D-mesons    //
	// and partons from the primary vertex.                              //
	// PH: new feature is to be able to require the parton to have       //
         //     a specific mother to be matched. This can make a difference   //
         //     for e.g. b-quarks that radiate and end up further away        //
         //     from the jet                                                  //  
         //                                                                   //
         // It returns a pair of integers:                                    // 
         //                                                                   //
         // 1) The jet is matched to a B-meson (5)                            //
         //    The jet is matched to a D-meson (no B-meson) (4)               //
         //    The jet is not matched to any B- or D-meson (1)                //
         //                                                                   //
         // 2) The jet is matched to a b parton from the PV (5)               //
         //    The jet is matched to a c parton from the PV (4)               //
         //    The jet is matched to a light parton from the PV (1)           //
         //    The jet is not matched to any parton from the PV (0)           //
         // ***************************************************************** //
    
	const T* jet = &j;
         bool debug = false;
    
         //float maxdR = 0.5;
         float mesonMaxdR = maxdR;
         int parton_match = 0;
         int Cmeson_match = 0;
         int Bmeson_match = 0;
         parton_index = -1;
         //int sparticle_offset = 1000000;
         int sparticle_offset = 0;
	 
         int NMCparticles = static_cast<int>(partons.size());
         int Njets = static_cast<int>(jets.size());
	 
         // *********************************************
         // I want to match partons
         // as well as B- and D-mesons
         // *********************************************
	 
         float min_dr_parton = 10.0;
         int matched_parton_flavor = sparticle_offset;
	 
         if(debug) std::cout << "Matching Jet with pT,eta,phi " << jet->p.Pt() << "," << jet->p.Eta() << "," << jet->p.Phi() << std::endl;
         if(debug) std::cout << "Start loop over " << NMCparticles << std::endl;
	 
         for (int i=0; i!=NMCparticles; ++i) { // loop over all MC particles
	   const Parton * MCparticle = &(partons[i]); 
	   int pdg = MCparticle->pdgId();
	   int abs_pdg = TMath::Abs(pdg);
	   if(mother) {
	     int mother1Pdg=TMath::Abs(MCparticle->mother1());
	     //int mother2Pdg=TMath::Abs(MCparticle->mother2());
	     if(mother!=mother1Pdg) 
	       continue;
	   }
	   //            if(debug) std::cout << "Parton " << i << " pdg: " << pdg << std::endl;
	   
	   // is the particle a squark or a gluino?
	   if (abs_pdg==sparticle_offset+1 || 
	       abs_pdg==sparticle_offset+2 || 
	       abs_pdg==sparticle_offset+3 || 
	       abs_pdg==sparticle_offset+4 || 
	       abs_pdg==sparticle_offset+5 || 
	       abs_pdg==sparticle_offset+21) {
	     
	     if(debug) std::cout << "Parton " << i << " is a quark, pT,eta,phi " << MCparticle->p.Pt() << "," << MCparticle->p.Eta() << "." << MCparticle->p.Phi() << std::endl;
	     
	     float dr = (jet->p).DeltaR(MCparticle->p); 
	     
	     if(debug) std::cout << "dr " << dr << std::endl;
	     
	     if (dr < maxdR && dr < min_dr_parton) {
	       // loop over all jets to make sure that no other jet in the event is closer to this MCparticle
	       bool use_this_particle = true;
	       for (int ijet=0; ijet!=Njets; ++ijet) {
		 const T* loopjet = &(jets[ijet]); 
		 if (loopjet == jet) {
                        if(debug) std::cout << "jetMatching::found same jet" << std::endl;
                        continue;
                     }
                     //if ((loopjet->p).Pt() < 15.0) continue;
                     float loop_dr = (loopjet->p).DeltaR(MCparticle->p);
                     if (loop_dr < dr) use_this_particle = false;
                  }
                  if (use_this_particle) {
                     if(debug) std::cout << "This parton is matched to my jet!" << std::endl;
                     ++parton_match;
                     min_dr_parton = dr;
                     matched_parton_flavor = abs_pdg;
                     parton_index = i;
                  }
               }
            }
            // Is it a B-meson?
            else if (binary_search(Bmesons.begin(),Bmesons.end(),abs_pdg)) {
               float dr = (jet->p).DeltaR(MCparticle->p); 
	
               if(debug) std::cout << "Found a B-meson(" <<MCparticle->pdgId() << ") with dr="<<dr<<std::endl;
	
               if (dr < mesonMaxdR) {
                  // loop over all jets to make sure that no other jet in the event is closer to this MCparticle
                  if(debug) std::cout << "This B-meson(" <<MCparticle->pdgId() << ") is close to the jet"<<std::endl;
	  
                  bool use_this_particle = true;
                  for (int ijet=0; ijet!=Njets; ++ijet) {
                     const T* loopjet = &(jets[ijet]); 
                     if (loopjet == jet) {
                        if(debug) std::cout << "jetMatching::found same jet" << std::endl;
                        continue;
                     }
                     //if ((loopjet->p).Pt() < 15.0) continue;
                     float loop_dr = (loopjet->p).DeltaR(MCparticle->p);
                     if (loop_dr < dr) use_this_particle = false;
                  }
                  if (use_this_particle) {
                     ++Bmeson_match;
                     if(debug) std::cout << "This B-meson(" <<MCparticle->pdgId() << ") was matched to the jet Bmeson_match=" << Bmeson_match<<std::endl;
                  }
               }
            }
            // Is it a C-meson?
            else if (binary_search(Cmesons.begin(),Cmesons.end(),abs_pdg)) {
	
               float dr = (jet->p).DeltaR(MCparticle->p); 
               if(debug) std::cout << "Found a C-meson(" <<MCparticle->pdgId() << ") with dr="<<dr<<std::endl;
	
               if (dr < mesonMaxdR) {
                  // loop over all jets to make sure that no other jet in the event is closer to this MCparticle
                  if(debug) std::cout << "This C-meson(" <<MCparticle->pdgId() << ") is close to the jet"<<std::endl;
                  bool use_this_particle = true;
                  for (int ijet=0; ijet!=Njets; ++ijet) {
                     const T* loopjet = &(jets[ijet]); 
                     if (loopjet == jet) {
                        if(debug) std::cout << "jetMatching::found same jet" << std::endl;
                        continue;
                     }
                     //if ((loopjet->p).Pt() < 15.0) continue;
                     float loop_dr = (loopjet->p).DeltaR(MCparticle->p);
                     if (loop_dr < dr) use_this_particle = false;
                  }
                  if (use_this_particle) {
                     // This meson is matched to my jet!
                     ++Cmeson_match;
                     if(debug) std::cout << "This C-meson(" <<MCparticle->pdgId() << ") was matched to the jet Cmeson_match=" << Cmeson_match<<std::endl;
                  }
               }
            }
      
         } // end loop over all MC particles
    
         matched_parton_flavor = matched_parton_flavor - sparticle_offset;
    
         // Define return values
         if (matched_parton_flavor == 1 || matched_parton_flavor == 2 || 
             matched_parton_flavor == 3 || matched_parton_flavor == 21) matched_parton_flavor = 1; 
    
         if (Bmeson_match>0) return std::make_pair(5,matched_parton_flavor);
         else if (Cmeson_match>0) return std::make_pair(4,matched_parton_flavor);
         return std::make_pair(1,matched_parton_flavor);
    
      }







//       std::pair<int,int> JetMatching(int& parton_index, 
//                                      const Jet* jet, 
//                                      const Particles<Jet>& jets, 
//                                      const Particles<Parton>& partons, 
//                                      float maxdR,
//                                      int mother) {
         
//          //std::cout << "in jetMatching()" << std::endl;
    
//          // ***************************************************************** //
//          // This function takes a jet and matches it to B-mesons, D-mesons    //
//          // and partons from the primary vertex.                              //
//          // PH: new feature is to be able to require the parton to have       //
//          //     a specific mother to be matched. This can make a difference   //
//          //     for e.g. b-quarks that radiate and end up further away        //
//          //     from the jet                                                  //  
//          //                                                                   //
//          // It returns a pair of integers:                                    // 
//          //                                                                   //
//          // 1) The jet is matched to a B-meson (5)                            //
//          //    The jet is matched to a D-meson (no B-meson) (4)               //
//          //    The jet is not matched to any B- or D-meson (1)                //
//          //                                                                   //
//          // 2) The jet is matched to a b parton from the PV (5)               //
//          //    The jet is matched to a c parton from the PV (4)               //
//          //    The jet is matched to a light parton from the PV (1)           //
//          //    The jet is not matched to any parton from the PV (0)           //
//          // ***************************************************************** //
    
//          bool debug = false;
    
//          //float maxdR = 0.5;
//          float mesonMaxdR = 0.5;
//          int parton_match = 0;
//          int Cmeson_match = 0;
//          int Bmeson_match = 0;
//          parton_index = -1;
//          //int sparticle_offset = 1000000;
//          int sparticle_offset = 0;
    
//          int NMCparticles = static_cast<int>(partons.size());
//          int Njets = static_cast<int>(jets.size());
    
//          // *********************************************
//          // I want to match partons
//          // as well as B- and D-mesons
//          // *********************************************
    
//          float min_dr_parton = 10.0;
//          int matched_parton_flavor = sparticle_offset;
    
//          if(debug) std::cout << "Matching Jet with pT,eta,phi " << jet->p.Pt() << "," << jet->p.Eta() << "," << jet->p.Phi() << std::endl;
//          if(debug) std::cout << "Start loop over " << NMCparticles << std::endl;
    
//          for (int i=0; i!=NMCparticles; ++i) { // loop over all MC particles
//             const Parton * MCparticle = &(partons[i]); 
//             int pdg = MCparticle->pdgId();
//             int abs_pdg = TMath::Abs(pdg);
//             if(mother) {
//                int mother1Pdg=TMath::Abs(MCparticle->mother1());
//                //int mother2Pdg=TMath::Abs(MCparticle->mother2());
//                if(mother!=mother1Pdg) 
//                   continue;
//             }
//             //            if(debug) std::cout << "Parton " << i << " pdg: " << pdg << std::endl;
      
//             // is the particle a squark or a gluino?
//             if (abs_pdg==sparticle_offset+1 || 
//                 abs_pdg==sparticle_offset+2 || 
//                 abs_pdg==sparticle_offset+3 || 
//                 abs_pdg==sparticle_offset+4 || 
//                 abs_pdg==sparticle_offset+5 || 
//                 abs_pdg==sparticle_offset+21) {
	
//                if(debug) std::cout << "Parton " << i << " is a quark, pT,eta,phi " << MCparticle->p.Pt() << "," << MCparticle->p.Eta() << "." << MCparticle->p.Phi() << std::endl;
	
//                float dr = (jet->p).DeltaR(MCparticle->p); 
	
//                if(debug) std::cout << "dr " << dr << std::endl;
	
//                if (dr < maxdR && dr < min_dr_parton) {
//                   // loop over all jets to make sure that no other jet in the event is closer to this MCparticle
//                   bool use_this_particle = true;
//                   for (int ijet=0; ijet!=Njets; ++ijet) {
//                      const Jet* loopjet = &(jets[ijet]); 
//                      if (loopjet == jet) {
//                         if(debug) std::cout << "jetMatching::found same jet" << std::endl;
//                         continue;
//                      }
//                      //if ((loopjet->p).Pt() < 15.0) continue;
//                      float loop_dr = (loopjet->p).DeltaR(MCparticle->p);
//                      if (loop_dr < dr) use_this_particle = false;
//                   }
//                   if (use_this_particle) {
//                      if(debug) std::cout << "This parton is matched to my jet!" << std::endl;
//                      ++parton_match;
//                      min_dr_parton = dr;
//                      matched_parton_flavor = abs_pdg;
//                      parton_index = i;
//                   }
//                }
//             }
//             // Is it a B-meson?
//             else if (binary_search(Bmesons.begin(),Bmesons.end(),abs_pdg)) {
//                float dr = (jet->p).DeltaR(MCparticle->p); 
	
//                if(debug) std::cout << "Found a B-meson(" <<MCparticle->pdgId() << ") with dr="<<dr<<std::endl;
	
//                if (dr < mesonMaxdR) {
//                   // loop over all jets to make sure that no other jet in the event is closer to this MCparticle
//                   if(debug) std::cout << "This B-meson(" <<MCparticle->pdgId() << ") is close to the jet"<<std::endl;
	  
//                   bool use_this_particle = true;
//                   for (int ijet=0; ijet!=Njets; ++ijet) {
//                      const Jet* loopjet = &(jets[ijet]); 
//                      if (loopjet == jet) {
//                         if(debug) std::cout << "jetMatching::found same jet" << std::endl;
//                         continue;
//                      }
//                      if ((loopjet->p).Pt() < 15.0) continue;
//                      float loop_dr = (loopjet->p).DeltaR(MCparticle->p);
//                      if (loop_dr < dr) use_this_particle = false;
//                   }
//                   if (use_this_particle) {
//                      ++Bmeson_match;
//                      if(debug) std::cout << "This B-meson(" <<MCparticle->pdgId() << ") was matched to the jet Bmeson_match=" << Bmeson_match<<std::endl;
//                   }
//                }
//             }
//             // Is it a C-meson?
//             else if (binary_search(Cmesons.begin(),Cmesons.end(),abs_pdg)) {
	
//                float dr = (jet->p).DeltaR(MCparticle->p); 
//                if(debug) std::cout << "Found a C-meson(" <<MCparticle->pdgId() << ") with dr="<<dr<<std::endl;
	
//                if (dr < mesonMaxdR) {
//                   // loop over all jets to make sure that no other jet in the event is closer to this MCparticle
//                   if(debug) std::cout << "This C-meson(" <<MCparticle->pdgId() << ") is close to the jet"<<std::endl;
//                   bool use_this_particle = true;
//                   for (int ijet=0; ijet!=Njets; ++ijet) {
//                      const Jet* loopjet = &(jets[ijet]); 
//                      if (loopjet == jet) {
//                         if(debug) std::cout << "jetMatching::found same jet" << std::endl;
//                         continue;
//                      }
//                      if ((loopjet->p).Pt() < 15.0) continue;
//                      float loop_dr = (loopjet->p).DeltaR(MCparticle->p);
//                      if (loop_dr < dr) use_this_particle = false;
//                   }
//                   if (use_this_particle) {
//                      // This meson is matched to my jet!
//                      ++Cmeson_match;
//                      if(debug) std::cout << "This C-meson(" <<MCparticle->pdgId() << ") was matched to the jet Cmeson_match=" << Cmeson_match<<std::endl;
//                   }
//                }
//             }
      
//          } // end loop over all MC particles
    
//          matched_parton_flavor = matched_parton_flavor - sparticle_offset;
    
//          // Define return values
//          if (matched_parton_flavor == 1 || matched_parton_flavor == 2 || 
//              matched_parton_flavor == 3 || matched_parton_flavor == 21) matched_parton_flavor = 1; 
    
//          if (Bmeson_match>0) return std::make_pair(5,matched_parton_flavor);
//          else if (Cmeson_match>0) return std::make_pair(4,matched_parton_flavor);
//          return std::make_pair(1,matched_parton_flavor);
    
//       }
  
//       std::pair<int,int> JetMatching(int& parton_index, 
//                                      const Jet* jet, 
//                                      const Particles<Jet>& jets, 
//                                      const Particles<Parton>& partons, 
//                                      float maxdR) {
//          //dont care about mother
//          return JetMatching(parton_index, 
//                             jet, 
//                             jets, 
//                             partons, 
//                             maxdR,
//                             0);
//       }
  
  
  
      std::vector< std::pair< std::vector<int>,std::vector<int> > > GetJetPermutations(void) {
         std::cout << "Listing all jet combinations"<<std::endl;
         ifstream prmFile("../../utils/testprm.dat");
         std::vector< std::pair< std::vector<int>,std::vector<int> > > jind;
         std::string s;
         while (prmFile >> s) {
            TString s1=s.substr(0,4);
            TString s2= s.substr(5,4);
            assert(s1.Length()==s2.Length()&&s1.Length()==4);
            std::vector<int> j1,j2;
            for(int i=0;i!=4;++i) {
               if(s1[i]==TString("l")) j1.push_back(i);
               if(s2[i]==TString("l")) j2.push_back(i);
            } //ix
            std::pair< std::vector<int>,std::vector<int> > bjets = std::make_pair(j1,j2);
            jind.push_back(bjets);
         }
         return jind;
      } //GetJetPermutations()
  
      void solv_top_dil_all_comb(const TLorentzVector &l1,
                                 const TLorentzVector & l2,
                                 const int jets, const TLorentzVector (&j)[4],
                                 double metx, double mety,
                                 std::vector<TLorentzVector> &j1,
                                 std::vector<TLorentzVector> &j2,
                                 std::vector< std::vector<TLorentzVector> > &nu1,
                                 std::vector< std::vector<TLorentzVector> > &nu2,
                                 std::vector< std::vector<float> > &tlm,
                                 std::vector<int> & nsol) {
    
         bool doFSR=false;
         int n,index;
         bool ok;
         for(int iperm=0;iperm!=static_cast<int>(jperm.size());++iperm) {
            //std::cout << "perm : " << iperm <<std::endl;
      
            if(!doFSR) {
	
               //TEST
               //Remove permutations with FSR hypo
               if((jperm[iperm].first).size() != 1 || (jperm[iperm].second).size() != 1 ) {
                  continue;
               }
               //TEST
            }           
      
            ok = true;
            TLorentzVector jet1,jet2,n1[4],n2[4];
            for(int i=0;i!=static_cast<int>((jperm[iperm].first).size());++i) {
               index = (jperm[iperm].first)[i];
               if(index>=jets) {
                  //this permutations requires more jets than there is in the event
                  ok=false;
                  break;
               }
               jet1+=j[index];
            } //i
            for(int i=0;i!=static_cast<int>((jperm[iperm].second).size());++i) {
               index = (jperm[iperm].second)[i];
               if(index>=jets) {
                  //this permutations requires more jets than there is in the event
                  ok=false;
                  break;
               }
               jet2+=j[index];
	
            } //i 
            if(!ok) {
               /*
                 std::cout << "This combination fails for having to few jets: " << jets;
                 cout << " j1: ";
                 for(int i=0;i!=static_cast<int>((jperm[iperm].first).size());++i) cout << (jperm[iperm].first)[i];               
                 cout << "   j2: ";
                 for(int i=0;i!=static_cast<int>((jperm[iperm].second).size());++i) cout << (jperm[iperm].second)[i];
                 cout << endl;
               */
               continue;
            }
            if(!doFSR) {
               if((mb()==0.&& (jet1.M()>1.0e-2|| jet2.M()>1.0e-2)) || (mb()!=0.&& (jet1.M()<1.0e-2|| jet2.M()<1.0e-2)) ) {
                  std::cout << "Error mb=" << mb() <<" but jets are"<<std::endl;
                  print(jet1); print(jet2); exit(0);
               }
            }
            solv_top_dil(l1,l2,jet1,jet2,metx,mety,n1,n2,n,mt(),mw(),mb());
            if(!n) continue;
            //             std::cout << "AtlUtil: got " << n << " solutions" <<std::endl;
            //             std::cout << "AtlUtil: Getting the tlms" <<std::endl;
            std::vector<float> tmptlm = CalcTopMass(l1,l2,jet1,jet2,n1,n2,n);
            //            std::cout << "AtlUtil: got " << tmptlm.size() <<" masses :";
            //             for(int i=0;i!=n;++i) std::cout << "  i=" <<i<<" "<< tmptlm[i]; 
            //             std::cout<<std::endl;
            std::vector<TLorentzVector> nutmp1;
            std::vector<TLorentzVector> nutmp2;
            for(int i=0;i!=n;++i) {
               nutmp1.push_back(n1[i]);
               nutmp2.push_back(n2[i]);
            }
            nu1.push_back(nutmp1);
            nu2.push_back(nutmp2);
            j1.push_back(jet1);
            j2.push_back(jet2);
            tlm.push_back(tmptlm);
            nsol.push_back(n);
            //            std::cout << "nsol.size=" << nsol.size() << " tlm.size=" << tlm.size() <<  std::endl;
         } //iperm
      }
  
  
      bool usedbjetpair(const std::vector< std::pair<TLorentzVector,TLorentzVector> >& pairs,
                        const TLorentzVector& j1,const TLorentzVector& j2) 
      {
         //int debug=0;
         //std::cout << "begin usedbjetpair()" << std::endl;
         //std::cout << "Trying to find j1:" << std::endl;
         //print(j1);
         //std::cout << "Trying to find j2:" << std::endl;
         //print(j2);         
         //this function checks if these pair of jets exist in the map
         std::vector< std::pair<TLorentzVector,TLorentzVector> >::const_iterator it  =  pairs.begin();
         std::vector< std::pair<TLorentzVector,TLorentzVector> >::const_iterator itE =  pairs.end();
         double dmin=0.001;
         //std::cout << "Number of pairs to look among: " << pairs.size() << std::endl;
         for(;it!=itE;++it) {            
            bool j1F=false;
            bool j2F=false;
            j1F = (it->first).DeltaR(j1)<dmin ? true : false;
            if(!j1F) j1F = (it->second).DeltaR(j1)<dmin ? true : false;
            j2F = (it->first).DeltaR(j2)<dmin ? true : false;
            if(!j2F) j2F = (it->second).DeltaR(j2)<dmin ? true : false;
	
            //if both are found then return true
            if(j1F&&j2F) return true;
         }
         return false;
      }
  
  
      void solv_top_dil_all_comb(const TLorentzVector &l1, const TLorentzVector & l2,
                                 const int jets, const TLorentzVector (&j)[4],
                                 const double& metx, const double& mety,
                                 TLorentzVector &j1, TLorentzVector &j2,
                                 TLorentzVector (&nu1)[4], TLorentzVector (&nu2)[4],
                                 int& n,bool doFSR=false)
      {
         int nbjetpairs=0;
         solv_top_dil_all_comb(l1,l2,jets,j,metx,mety,j1,j2,nu1,nu2,n,nbjetpairs,doFSR);
      }
  
      void solv_top_dil_all_comb(const TLorentzVector &l1, const TLorentzVector & l2,
                                 const int jets, const TLorentzVector (&j)[4],
                                 const double& metx, const double& mety,
                                 TLorentzVector &j1, TLorentzVector &j2,
                                 TLorentzVector (&nu1)[4], TLorentzVector (&nu2)[4],
                                 int& n,int& npairs,bool doFSR=false)
      {
      
         int index;
         bool ok;
         //npairs=0;
         n=0;
         // definition of bjetpairs is that count only one of the possible exchange of b-jets
         // if [j0,j1] AND [j1j0] has a solution then count this as one!
         // therefore I need to keep track of which pairs that are counted as I loop over all 
         // possible combinations to find a solution
         std::vector< std::pair<TLorentzVector,TLorentzVector> > bpairs; 
      
         for(int iperm=0;iperm!=static_cast<int>(jperm.size());++iperm) {
	
	
            if(!doFSR) {
               //TEST
               //Remove permutations with FSR hypo
               if((jperm[iperm].first).size() != 1 || (jperm[iperm].second).size() != 1 ) {
                  continue;
               }
               //TEST
            }
            //            std::cout << "FSR=" << doFSR << std::endl;
            //             std::cout << "perm " << iperm 
            //                       << ":  nr of indexes for j1/j2 = " << (jperm[iperm].first).size() 
            //                       << "/" << (jperm[iperm].second).size() << std::endl;
	
            ok = true;
            TLorentzVector jet1,jet2;
            for(int i=0;i!=static_cast<int>((jperm[iperm].first).size());++i) {
               index = (jperm[iperm].first)[i];
               if(index>=jets) {
                  //this permutations requires more jets than there is in the event
                  ok=false;
                  break;
               }
               jet1+=j[index];
            } //i
            for(int i=0;i!=static_cast<int>((jperm[iperm].second).size());++i) {
               index = (jperm[iperm].second)[i];
               if(index>=jets) {
                  //this permutations requires more jets than there is in the event
                  ok=false;
                  break;
               }
               jet2+=j[index];
	  
            } //i 
            if(!ok) continue;            
            if(!doFSR) {
               if((mb()==0.&& (jet1.M()>1.0e-2|| jet2.M()>1.0e-2)) || (mb()!=0.&& (jet1.M()<1.0e-2|| jet2.M()<1.0e-2)) ) {
                  std::cout << "Error mb=" << mb() <<" but jets are"<<std::endl;
                  print(jet1); print(jet2); exit(0);
               }
            }
            int nsol=0;
            solv_top_dil(l1,l2,jet1,jet2,metx,mety,nu1,nu2,nsol,mt(),mw(),mb());
            assert(nsol!=-1);
            if(nsol>0) {
               if(!usedbjetpair(bpairs,jet1,jet2)) {
                  //npairs++;
                  bpairs.push_back(std::make_pair(jet1,jet2));
               }
               if(nsol>n) {
                  //return the permutation with the most solutions...WHY?
                  n=nsol;
                  j1=jet1;
                  j2=jet2;
               }
               //return;
            }
         } //iperm
         npairs = (int)bpairs.size();
      }
  
      void solv_top_dil_all_comb_smear(const TLorentzVector &l1, const TLorentzVector & l2,
                                       const int jets, const TLorentzVector (&j)[4],
                                       double metx, double mety,
                                       TLorentzVector &j1, TLorentzVector &j2,
                                       TLorentzVector (&n1)[4], TLorentzVector (&n2)[4],
                                       int &n,int &npairs,const int Niters,const double& sumet, 
                                       TRandom* rnd, bool doFSR=false)
      {
      
         if(!Niters) {
            solv_top_dil_all_comb(l1,l2,jets,j,metx,mety,j1,j2,n1,n2,n,npairs);
            return;
         }
         //Fluctuate the MET and jet momentum
         // MET: p.289 Physics TDR
         //      sigma=0.46*sqrt(sumet)  seems low but a start..
         // Jet Et: p272 (cone04 sampling method)
         // sigma/E = 0.66/sqrt(E)+0.012
         //std::cout << "solve ttbar: fluctuate energies" << std::endl;
         double metNx,metNy,ENew;
         TLorentzVector jet[4];
         double pt,px,py,pz;
         for(int i=0;i!=Niters;++i) {
            metNx = rnd->Gaus(metx,0.46*sqrt(sumet));
            metNy = rnd->Gaus(mety,0.46*sqrt(sumet));
            for(int ijet=0;ijet!=jets;++ijet) {
               assert(j[ijet].E() > 0.);
               //propagate the jet energy to met
               metNx-=j[ijet].Px();
               metNy-=j[ijet].Py();
               ENew =  rnd->Gaus(j[ijet].E() , j[ijet].E()*(0.66/sqrt(j[ijet].E()) + 0.012) );
               pz = ENew*j[ijet].CosTheta();
               assert(fabs(pz)<fabs(ENew));
               pt = sqrt(ENew*ENew - pz*pz);
               px = pt*TMath::Cos(j[ijet].Phi());
               py = pt*TMath::Sin(j[ijet].Phi());
               jet[ijet] = j[ijet];         
               jet[ijet].SetPxPyPzE(px,py,pz,ENew);         
               //propagate the jet energy to met
               metNx+=jet[ijet].Px();
               metNy+=jet[ijet].Py();
	  
            }//ijet      
            solv_top_dil_all_comb(l1,l2,jets,jet,metNx,metNy,j1,j2,n1,n2,n,npairs,doFSR);      
            if(npairs) break;
         } //i
      }
  
      std::vector<float> CalcTopMass(const TLorentzVector &l1,const TLorentzVector &l2,const TLorentzVector &j1,const TLorentzVector &j2,
                                     const TLorentzVector (&n1)[4],const TLorentzVector (&n2)[4],const int &n) {
         std::vector<float> tmass;
         for (int i=0;i<n;++i) {
            float tmp=(l1+l2+j1+j2+n1[i]+n2[i]).M();
            //std::cout << "Top mass for sol " << i << ": " << tmp << std::endl;
            tmass.push_back(tmp);
         }//i
         return tmass;
      }
  
      void rescaleMET(const double& scale,
                      const std::vector<Particle>& objs,
                      double& metx,double& mety) {
         // input is scale uncertainty,vector of objects do remove, and default met variables
    
         //Remove the objects from the met
         for(size_t i=0;i!=objs.size();++i) {
            metx += (1.- scale)*(objs[i].p.Px());
            mety += (1.- scale)*(objs[i].p.Py());
         }
         //rescale met
         metx *= scale;
         mety *= scale;
    
         //add the objects from the met
         for(size_t i=0;i!=objs.size();++i) {
            metx += (scale - 1.)*(objs[i].p.Px());
            mety += (scale - 1.)*(objs[i].p.Py());
         }
         return;
    
      } //rescaleMET
  
      bool IsBmeson(const int& pdgid) {
	int abs_pdgid = TMath::Abs(pdgid);
	return binary_search(Bmesons.begin(),Bmesons.end(),abs_pdgid);
      }
      bool IsCmeson(const int& pdgid) {
	int abs_pdgid = TMath::Abs(pdgid);
	return binary_search(Cmesons.begin(),Cmesons.end(),abs_pdgid);
      }


void getEfficiency(double n,double d, double e[]) {  
  //error on the ration of n/d when n is a subset of d
  //using binomial errors
  if(d==0.) {
    std::cout << "WARNING! Cannot calculate ratio error with no entries!" << std::endl;
    e[0]=-1.; e[1]=-1.;
    return;
  }
  if(n>d) {
     std::cout << "AtlUtil:ERROR! wrong order of parameters in efficiency calculation!" 
               << ": n="<<n<<" & d="<<d<< std::endl; 
     e[0] = -1.;
     e[1] = -1.;
  }
  double p = n/d;
  e[0] = p;
  e[1] = sqrt( p*(1.-p)/d );
  //cout << "CalcEffErr: d="<<d<<" n="<<n<<" p="<<p<<"\n---> e="<<e<<std::endl; 
  return;
}


void getEfficiency(TH1* hn,TH1* hd, double e[]) {  
  double n = hn->Integral(-1,9999999);
  double d = hd->Integral(-1,9999999);
  getEfficiency(n,d,e);
  return;
}


double rate(double Npass, double Ntotal, double sigma, double lumi_inst) {
  // sigma [pb]
  // instantaneous lumi [cm^-2s^-1]
  // N events
  //   std::cout << setprecision(10) << endl;
/*       std::cout << "Npass=" << Npass << endl;  */
/*       std::cout << "Ntotal=" << Ntotal << endl;  */
/*       std::cout << "sigma=" << sigma << " pb" << endl;  */
/*       std::cout << "lumi_inst=" << lumi_inst*TMath::Power(10,-36) << " pb^-1s^-1" << endl; */
  
   if(Npass>Ntotal) {
      std::cout << "AtlUtil:ERROR! Npass="<<Npass<<" & Ntotal="<<Ntotal
                << " is not correct order! (diff="<< (Ntotal-Npass) << ")" << std::endl; return -1.;// exit(-1);
   }

  double eff[2];
  getEfficiency(Npass,Ntotal,eff);
  return eff[0] * sigma * lumi_inst*TMath::Power(10,-36);
}
double rateError(double Npass, double Ntotal, double sigma, double lumi_inst) {
  // sigma [pb]
  // instantaneous lumi [cm^-2s^-1]
  // N events
  //   std::cout << setprecision(10) << endl;
  //   std::cout << "Npass=" << Npass << endl;
  //   std::cout << "Ntotal=" << Ntotal << endl;
  //   std::cout << "sigma=" << sigma << " pb" << endl;
  //   std::cout << "lumi_inst=" << lumi_inst*TMath::Power(10,-36) << " pb^-1s^-1" << endl;
  double eff[2];
  getEfficiency(Npass,Ntotal,eff);
  //double r = eff[0] * sigma * lumi_inst*TMath::Power(10,-36);
  return (eff[1] * sigma * lumi_inst*TMath::Power(10,-36));
}




void plotEfficiency(TString numerator,TString denominator) {
   
   std::cout << " Making efficiency plot: [" << numerator << "] / [" << denominator << "] ";
   //Calculate the ratio of the histograms matching the plot name
   
   //Loop over all the histos and find the matching names
   TIter nextkey( gDirectory->GetList() );
   std::map<TString,TH1*> m;
   while ( TObject *obj = nextkey() ) {      
	  // read object 
	  if ( obj->IsA()->InheritsFrom( "TH1" ) ) {
         // descendant of TH1
         TH1 *h1 = (TH1*)obj;
         //check the name
         TString Name = h1->GetName();
         int pos = Name.Index(numerator.Data());
         if(pos == -1) {continue;}
         //cout << "This histogram " << Name << " is the numerator" << endl;
         TString Name2( Name ); 
         Name2.ReplaceAll(numerator,"");
         Name2 += denominator;
         //cout << "search for the denominator as " << Name2 << endl;
         if(TObject* obj2 = gDirectory->Get(Name2)) {
            if ( obj2->IsA()->InheritsFrom( "TH1" ) ) {
               // descendant of TH1
               TH1 *h12 = (TH1*)obj2;
               //divide the two
               TH1F* hnum = (TH1F*)h1;
               TH1F* hden = (TH1F*)h12;
               if(hnum && hden) {
                  if(hnum->GetEntries()!=0 && hden->GetEntries()!=0) {
                     TString value_new(h1->GetName()); value_new += "eff";
                     TH1F* h = (TH1F*)hnum->Clone(value_new);  
                     h->Reset();
                     h->Divide(hnum,hden,1.,1.,"B");
                     h->SetYTitle("Efficiency");
                     //cout << " -> done";
                  }
               }  
            }
         }
      }
   }
   std::cout  << std::endl;
}







      TRandom ran;
   private:
      std::map<TString,int> m_cutmap;
      std::vector<int> Bmesons,Cmesons;
      TF1* fTF[2];
      std::vector< std::pair< std::vector<int>,std::vector<int> > > jperm;
      TH2 *htrg;
      TH1F *h_ele_loose_tight_pt,*h_ele_loose_tight_eta;
      TH2F* h_ele_loose_tight_fe;
      TF1* h_ele_loose_tight_fit_pt,*h_ele_loose_tight_fit_pt_statup,*h_ele_loose_tight_fit_pt_statdown;
      //TrigTrackJetFinderTool m_trackjetfinder;

};

const Roi* matchObj(const TLorentzVector& obj,
                    const Rois& objs,
                    double drCut)
{
   double dr = 9999.0;
   double dr_cur;
   const Roi* v = 0;
   for(Rois::const_iterator it=objs.begin(); it!=objs.end(); ++it) {
      dr_cur = obj.DeltaR((*it).p()); 
      if ( dr_cur < dr ) {
         dr  = dr_cur;
         v = &(*it);
      }
   }
   if( dr < drCut )
      return v;
   else
      return 0;  
}

template <class T> 
T* matchObjects(const TLorentzVector & obj,
                Particles<T> &objs,
                double drCut)
{
  
   typename std::vector<T>::iterator it = objs.begin();
   typename std::vector<T>::iterator itE = objs.end();
   double dr = 9999.0;
   double dr_cur;
   T* v = 0;
   for( ; it != itE; ++it ) {
      dr_cur = obj.DeltaR(it->p); 
      if ( dr_cur < dr ) {
         dr  = dr_cur;
         v = &(*it);
      }
   }
   if( dr < drCut )
      return v;
   else
      return 0;
  
};

template <class T> 
std::vector<const T*> matchObjectsVec(const TLorentzVector & obj,
                                      Particles<T> &objs,
                                      double drCut)
{
  
   typename std::vector<T>::iterator it = objs.begin();
   typename std::vector<T>::iterator itE = objs.end();
   double dr_cur;
   std::vector<const T*> v;
   for( ; it != itE; ++it ) {
      dr_cur = obj.DeltaR(it->p); 
      if( dr_cur < drCut) v.push_back(&(*it));      
   }
   return v;
};

template <class T> 
const T* GetLeadingMatchedObj(const TLorentzVector & p,
                              Particles<T>& objs,
                              const double drmax=0.4)
{
   std::vector<const T*> ps = matchObjectsVec(p,objs,drmax);
   if(ps.size()==0) return 0;
   double ptmax=-99.0;
   const T* mobj=0;
   typename std::vector<const T*>::const_iterator it = ps.begin();
   typename std::vector<const T*>::const_iterator itE =ps.end();
   for( ; it!=itE; ++it) {
      if(((*it)->p).Pt()>drmax) {
         ptmax=(*it)->p.Pt();
         mobj=*it;
      } 
   }
   assert(mobj!=0);
   return mobj;
}

template <class T> 
double GetMatchedObjE(const TLorentzVector & p,
                      Particles<T>& objs,
                      const double drmax=0.4)
{
   std::vector<const T*> ps = matchObjectsVec(p,objs,drmax);
   if(ps.size()==0) return 0.;
   double e=0.;
   typename std::vector<const T*>::const_iterator it=ps.begin(); 
   typename std::vector<const T*>::const_iterator itE=ps.end();    
   for( ; it!=itE; ++it) e+=(*it)->p.Pt();   
   return e;
}

void FixSumw2(TDirectory* dir) {
  
   TIter nextkey( dir->GetList() );
   while ( TObject *obj = nextkey() ) {      
      // read object 
      if ( obj->IsA()->InheritsFrom( "TH1" ) ) {
         // descendant of TH1
         TH1 *h1 = (TH1*)obj;
         //check if sumw2 is set (from TH1::Sumw2() source file)
         if (h1->GetSumw2N()) {
            //std::cout <<"Sum of squares of weights structure already created" << std::endl;
            continue;
         }
         h1->Sumw2();
         //std::cout << "Setting sumw2 for histo: " << h1->GetName() << std::endl;
      }
   }
};




std::map< TString, double > TopoCalculation( const std::vector< const TLorentzVector* >& ptcls) 
{ 
   std::map< TString, double > mtopo;
   std::vector<const TLorentzVector*>::const_iterator itp = ptcls.begin();
   std::vector<const TLorentzVector*>::const_iterator itpEnd = ptcls.end();
  
   double px,py,pz;
   int N = 0;
   double stot = 0.;
   double stotZ = 0.;
   double array[3*3]; // should probably use some proper matrix class???
   double arrayZ[3*3];
  
   //init
   for (int i=0;i<9;i++) array[i]=0.;
  
   //calculate the kinematic matrix
   for( ; itp!=itpEnd; itp++) {     
      px=(*itp)->Px();
      py=(*itp)->Py();
      pz=(*itp)->Pz();         
      array[0]+=px*px;
      array[1]+=px*py;
      array[2]+=px*pz;
      array[3]+=py*px;
      array[4]+=py*py;
      array[5]+=py*pz;
      array[6]+=pz*px;
      array[7]+=pz*py;
      array[8]+=pz*pz;         
      stotZ += (*itp)->P()*(*itp)->P();
      stot += (*itp)->Pt()*(*itp)->Pt();
      N++;
   }
   //std::cout << N << " particles in topoCalc calculation" << std::endl;
   if (N==0) {
      //std::cout << "No particles found to calculate topology from. " << std::endl;
      mtopo["SPH"] = -99.;
      mtopo["SPHZ"] = -99.;
      mtopo["APL"] = -99.;
      mtopo["PL"] = -99.;
    
      //std::cout  << "topoCalc() succeeded" << std::endl;
      return mtopo;
   }
  
   for (int i=0;i<9;i++) {
      arrayZ[i] = array[i]/stotZ;
      array[i] = array[i]/stot;
   }
  
   array[2]=array[5]=array[6]=array[7]=array[8]=0.;
  
   // use root matrix to find eigenvalues...
   TMatrixTSym<double> matrix(3);  
   matrix.SetMatrixArray(array);
   TMatrixTSym<double> matrixZ(3);  
   matrixZ.SetMatrixArray(arrayZ);
   //  matrix.Print();
  
   TMatrixDSymEigen eigen(matrix);        
   TVectorT<Double_t> E = eigen.GetEigenValues();   
   TMatrixDSymEigen eigenZ(matrixZ);        
   TVectorT<Double_t> EZ = eigenZ.GetEigenValues();   
  
   // from the babar sphericity code...
   double Emax = E[0];
   double Emin = E[0];
   int j = 0, k = 0;
   double EmaxZ = EZ[0];
   double EminZ = EZ[0];
   int jZ = 0, kZ = 0;
   for ( int i = 0; i <= 2 ; ++i ) {
      if ( E[i] > Emax ) {Emax = E[i]; j = i;}
      if ( E[i] < Emin ) {Emin = E[i]; k = i;}
      if ( EZ[i] > EmaxZ ) {EmaxZ = EZ[i]; jZ = i;}
      if ( EZ[i] < EminZ ) {EminZ = EZ[i]; kZ = i;}
   }
  
   int l = 3-j-k;
   double sph = Emax;
   int lZ = 3-jZ-kZ;
   double sphZ = EmaxZ;
   sphZ = 3 * ( E[kZ] + E[lZ] ) / 2;
   sph = 2 * E[l] / (E[j] + E[l]);
  
   double apl = 3 * E[k] / 2;
   double pla = E[l] - E[k];
  
   //    std::cout <<  " lambda_1 " << E[0] << " lambda_2 " <<E[1] << " lambda_3 " <<E[2] << " Tsphericity " << sph << " aplanarity " << apl << " planarity " << pla << std::endl;
   //    std::cout <<  " lambda_1(Z) " << EZ[0] << " lambda_2(Z) " <<EZ[1] << " lambda_3(Z) " <<EZ[2] << " sphericity " << sphZ << " aplanarity " << apl << " planarity " << pla << std::endl;
  
   if(sph < -10e-12 || sph > 1.0) {
      std::cout << "WARNING: sphericity is not in [0,1] interval: " << sph << std::endl;
      //exit(1);
   }
  
   mtopo["SPH"] = sph;
   mtopo["SPHZ"] = sphZ;
   mtopo["APL"] = apl;
   mtopo["PL"] = pla;
  
   //std::cout << "topoCalc() succeeded" << std::endl;
  
   return mtopo;
  
};


Double_t sphericity(const std::vector<const TLorentzVector*>& v) {
//===============================================================================   
// usage:
// vector<TLorentzVector>* v = new vector<TLorentzVector>(); 
// for(int ilep=0;ilep<nlepton;ilep++ ) {
// // loop over leptons
//   TLorentzVector part;
//   part.SetPxPyPzE( pxl[ilep],pyl[ilep],pzl[ilep],eel[ilep] );
//   v->push_back(part);
// }
// for(int ijet=0;ijet<njet;ijet++ ) {
// // loop over jets
//   TLorentzVector part;
//   part.SetPxPyPzE( pxj[ijet],pyj[ijet],pzj[ijet],eej[ijet] );
//   v->push_back(part);
// }
// Double Sphericity=sphericity(v);
// libraries:
//#include "TMatrixDSym.h"
//#include "TMatrixDSymEigen.h"
//#include "TVector3.h"
//#include "TVector2.h"
//#include "vector.h"
//#include "TMath.h"
//#include "TComplex.h"
//#include "TRotation.h"
//#include "TLorentzVector.h"
//#include "TLorentzRotation.h"
//=============================================================================
// calculates the transverse sphericity for a list of particles using the 
// method on page 820 of Atlas det & phys performance tdr (vol ii)
// S_T = 2 lambda_2 / (lambda_1 + lambda_2). lambda_1,2 are the
//  eigenvalues of sphericity tensor: S_ij = Sum_k P_ki P_kj  (i,j = x,y)
// input: STL vectror of 4-momenta of particles
// return value - sphericity 
//=============================================================================== 
   int N=0; // counter of particles
   double stotT=0; // denominator
   double arrayT[2*2]; // nominator
   double S_T; 
   for (int i=0;i<4;i++) arrayT[i]=0.;
   for (size_t i=0; i<v.size(); i++){
      double jpx = (v[i])->Px();
      double jpy = (v[i])->Py();
      double jpt = (v[i])->Pt();
      arrayT[0]+=jpx*jpx;
      arrayT[1]+=jpx*jpy;
      arrayT[2]+=jpy*jpx;
      arrayT[3]+=jpy*jpy;
      stotT += jpt*jpt;
      N++;
   }
   
   if (N==0) {
      S_T         = -99.;
   }
   else {
      for (int i=0;i<4;i++) arrayT[i] = arrayT[i]/stotT;
      //====calculate Transverse Sphericity================
      // use root matrix to find eigenvalues...
      TMatrixDSym matrixT(2);  
      matrixT.SetMatrixArray(arrayT);
      //matrixT.Print();
     
      TMatrixDSymEigen eigenT(matrixT);        
      TVectorD ET = eigenT.GetEigenValues();
     
      // from the babar sphericity code...
      double ETmax = ET[0];
      double ETmin = ET[0];
      int m = 0, n = 0;
      for ( int i = 0; i <= 1; ++i ) {
         if ( ET[i] > ETmax ) {ETmax = ET[i]; m = i;}
         if ( ET[i] < ETmin ) {ETmin = ET[i]; n = i;}
      }
      S_T = 2 * ET[n] /( ET[m] + ET[n] );
   }
   return S_T;
};



/*


void solv_top_dil_all_comb(const TLorentzVector &l1, const TLorentzVector & l2,
const int jets, const TLorentzVector (&j)[4],
double metx, double mety,
TLorentzVector &j1, TLorentzVector &j2,
TLorentzVector (&n1)[4], TLorentzVector (&n2)[4],
int &n)
{


solv_top_dil(l1,l2,j1=j[0],j2=j[1],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[1],j2=j[0],metx,mety,n1,n2,n);

if (jets>=3 && n==0) {
if (!n) solv_top_dil(l1,l2,j1=j[1],j2=j[2],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[2],j2=j[1],metx,mety,n1,n2,n);

if (!n) solv_top_dil(l1,l2,j1=j[0],j2=j[1]+j[2],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[1]+j[2],j2=j[0],metx,mety,n1,n2,n);

if (!n) solv_top_dil(l1,l2,j1=j[0]+j[2],j2=j[1],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[1],j2=j[0]+j[2],metx,mety,n1,n2,n);

if (!n) solv_top_dil(l1,l2,j1=j[0]+j[1],j2=j[2],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[2],j2=j[0]+j[1],metx,mety,n1,n2,n);

if (!n) solv_top_dil(l1,l2,j1=j[0],j2=j[2],metx,mety,n1,n2,n); //PH
if (!n) solv_top_dil(l2,l1,j1=j[0],j2=j[2],metx,mety,n1,n2,n); //PH


if (jets>=4 && n==0) {
if (!n) solv_top_dil(l1,l2,j1=j[0],j2=j[3],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[3],j2=j[0],metx,mety,n1,n2,n);
      
if (!n) solv_top_dil(l1,l2,j1=j[1],j2=j[3],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[3],j2=j[1],metx,mety,n1,n2,n);

if (!n) solv_top_dil(l1,l2,j1=j[2],j2=j[3],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[3],j2=j[2],metx,mety,n1,n2,n);
       
if (!n) solv_top_dil(l1,l2,j1=j[0],j2=j[2]+j[3],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[2]+j[3],j2=j[0],metx,mety,n1,n2,n);

if (!n) solv_top_dil(l1,l2,j1=j[0]+j[2],j2=j[3],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[3],j2=j[0]+j[2],metx,mety,n1,n2,n);

if (!n) solv_top_dil(l1,l2,j1=j[0]+j[3],j2=j[2],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[2],j2=j[0]+j[3],metx,mety,n1,n2,n);

if (!n) solv_top_dil(l1,l2,j1=j[1],j2=j[2]+j[3],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[2]+j[3],j2=j[1],metx,mety,n1,n2,n);

if (!n) solv_top_dil(l1,l2,j1=j[1]+j[2],j2=j[3],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[3],j2=j[1]+j[2],metx,mety,n1,n2,n);

if (!n) solv_top_dil(l1,l2,j1=j[1]+j[3],j2=j[2],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[2],j2=j[1]+j[3],metx,mety,n1,n2,n);

if (!n) solv_top_dil(l1,l2,j1=j[0],j2=j[1]+j[3],metx,mety,n1,n2,n); //PH
if (!n) solv_top_dil(l1,l2,j1=j[1]+j[3],j2=j[0],metx,mety,n1,n2,n); //PH
      
if (!n) solv_top_dil(l1,l2,j1=j[0]+j[3],j2=j[1],metx,mety,n1,n2,n); //PH
if (!n) solv_top_dil(l1,l2,j1=j[1],j2=j[0]+j[3],metx,mety,n1,n2,n); //PH
      
if (!n) solv_top_dil(l1,l2,j1=j[1]+j[0],j2=j[3],metx,mety,n1,n2,n); //PH
if (!n) solv_top_dil(l1,l2,j1=j[3],j2=j[1]+j[0],metx,mety,n1,n2,n); //PH

      
if (!n) solv_top_dil(l1,l2,j1=j[0],j2=j[1]+j[2]+j[3],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[1]+j[2]+j[3],j2=j[0],metx,mety,n1,n2,n);

if (!n) solv_top_dil(l1,l2,j1=j[0]+j[1],j2=j[2]+j[3],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[2]+j[3],j2=j[0]+j[1],metx,mety,n1,n2,n);

if (!n) solv_top_dil(l1,l2,j1=j[0]+j[1]+j[2],j2=j[3],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[3],j2=j[0]+j[1]+j[2],metx,mety,n1,n2,n);

if (!n) solv_top_dil(l1,l2,j1=j[0]+j[2],j2=j[1]+j[3],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[1]+j[3],j2=j[0]+j[2],metx,mety,n1,n2,n);

if (!n) solv_top_dil(l1,l2,j1=j[0]+j[1]+j[3],j2=j[2],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[2],j2=j[0]+j[1]+j[3],metx,mety,n1,n2,n);

if (!n) solv_top_dil(l1,l2,j1=j[0]+j[2]+j[3],j2=j[1],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[1],j2=j[0]+j[2]+j[3],metx,mety,n1,n2,n);

if (!n) solv_top_dil(l1,l2,j1=j[0]+j[3],j2=j[1]+j[2],metx,mety,n1,n2,n);
if (!n) solv_top_dil(l1,l2,j1=j[1]+j[2],j2=j[0]+j[3],metx,mety,n1,n2,n);

}
}
}

*/



/*
      void readEMtrigcurves(void) {
         TDirectory* sDir = gDirectory;
         TFile file("indata/zee.phsth.root");
         if (!file.IsOpen()) {
            htrg=0;
            std::cout << "Could not open trigger curves!" << std::endl;
            return;
         }
         TH2F *h_num, *h_denom;
         file.GetObject("tse2j2_ef_e15i_el_TP_pteta",h_num);
         file.GetObject("tse2j2_probe_e15i_el_TP_pteta",h_denom);
         htrg=(TH2F*)h_num->Clone("htrg");
         htrg->SetDirectory(0);
         htrg->ResetBit(kCanDelete);
         htrg->Divide(h_denom);
         sDir->cd();
      }


      void readLooseTightEff(void) {
         TDirectory* sDir = gDirectory;
         TFile file("indata/fe_pteta_wsjpt.root");
         if (!file.IsOpen()) {
            h_ele_loose_tight_eta=h_ele_loose_tight_pt=0;
            h_ele_loose_tight_fe=0;
            std::cout << "Could not open loose-tight fake rate curves!" << std::endl;
            return;
         }
         TH2F* hfe;
         TH1D* h_pt, *h_eta;
         //TF1* f_pt, *f_pt_statup,*f_pt_statdown;
         file.GetObject("jstrm_st4J80_e1_j2_met40_wsjpt_hfe_x_hnum_diemj2met40_eeloose10offjet0stream_passed_4jet80wsjptpteta_jstrm_phsth_totn",
                        h_pt);
         file.GetObject("jstrm_st4J80_e1_j2_met40_wsjpt_hfe_y_hnum_diemj2met40_eeloose10offjet0stream_passed_4jet80wsjptpteta_jstrm_phsth_totn",
                        h_eta);
         file.GetObject("jstrm_st4J80_e1_j2_met40_wsjpt_fe_hnum_diemj2met40_eeloose10offjet0stream_passed_4jet80wsjptpteta_jstrm_phsth_totn",
                        hfe);
                  
         
         if(!h_pt||!h_eta||!hfe) {
            std::cout << "Could not find loose-tight fake rate pt hist: " << h_pt 
                      << " eta hist: " << h_eta       
                      << " hfe2D hist: " << hfe << std::endl; exit(1);       
         }
         h_ele_loose_tight_pt=(TH1F*)h_pt->Clone("h_ele_loose_tight_pt");
         h_ele_loose_tight_eta=(TH1F*)h_eta->Clone("h_ele_loose_tight_eta");
         h_ele_loose_tight_fe= (TH2F*)hfe->Clone("h_ele_loose_tight_fe");
         h_ele_loose_tight_pt->SetDirectory(0);
         h_ele_loose_tight_eta->SetDirectory(0);
         h_ele_loose_tight_fe->SetDirectory(0);
         
//          h_ele_loose_tight_fit_pt=(TF1*)f_pt->Clone("h_ele_loose_tight_fit_pt");
//          h_ele_loose_tight_fit_pt_statup=(TF1*)f_pt_statup->Clone("h_ele_loose_tight_fit_pt_statup");
//          h_ele_loose_tight_fit_pt_statdown=(TF1*)f_pt_statdown->Clone("h_ele_loose_tight_fit_pt_statdown");
//          h_ele_loose_tight_fit_pt->SetDirectory(0);
//          h_ele_loose_tight_fit_pt_statup->SetDirectory(0);
//          h_ele_loose_tight_fit_pt_statdown->SetDirectory(0);
         
         sDir->cd();
         return;
      }
      
      float getLooseTightEff(TString systematic="") const {
         // no lorentzvector interface 
         TLorentzVector p;
         return getLooseTightEff(p,systematic);
      }

      float getLooseTightEff(const TLorentzVector & p, TString systematic="") const {
         if (!h_ele_loose_tight_pt||!h_ele_loose_tight_eta||!h_ele_loose_tight_fe) {
            //static bool warnlt=true;
            bool warnlt=true;
            if (warnlt) {
               std::cout << "loose-tight eff called without curves for particle:"<<std::endl;
               print(p);
               warnlt=false;
               exit(1);
            }
            return 1.0;
         }
         
         //std::cout << "AtlUtil: getting loose-tight eff for sys: " << systematic << std::endl;
         
         float prob = 1.0;
         float p_pt = h_ele_loose_tight_pt->GetBinContent(h_ele_loose_tight_pt->FindBin(p.Pt()<20.?20.:p.Pt()));
         float ep_pt = h_ele_loose_tight_pt->GetBinError(h_ele_loose_tight_pt->FindBin(p.Pt()<20.?20.:p.Pt()));
         
         if(systematic== ""){
            prob = p_pt;
         }
         else if(systematic=="ltefakestat_up") {
            prob = p_pt + ep_pt;
         }
         else if(systematic=="ltefakestat_down") {
            prob = p_pt - ep_pt;
         }
         else {
            exit(1);
         }
         

         assert(prob>=0.);
         if(prob>1.0) prob = 1.;         
         return (prob>=0. ? prob : 0.);
      }
      
      
      void readTransferFunction(void)
      {
         TString fileName = "trFnc_T1_nosel.root";
         TDirectory* sDir = gDirectory;
         
         TFile* trfile = new TFile(fileName.Data());
         TString fnames[2] = {"fitTF_Final","NewtrFTmFitFinal"};
         TF1* f;
         for(int i=0;i!=2;++i) {
            trfile->GetObject(fnames[i],f);
            if(f) {
               fTF[i] = static_cast<TF1*>(f->Clone());
               std::cout << "AtlUtil:: added transfer function " <<
                  fTF[i]->GetName() << std::endl;
            }
            else {
               std::cout <<
                  "AtlUtil::WARNING: transfer function was not found "
                         << std::endl;
               fTF[i]=0;
            }
         }
         trfile->Close();
         delete trfile;
         sDir->cd();
      };

      float getTRFPt(const float& pt,const int& opt) {
         if(opt<0||opt>1) {
            std::cout << "AtlUtil::ERROR: opt " << opt << " is not defined for scalefactortransfer function scale factor set to 1 since function not found!!" << std::endl;
         }
         if(!fTF[opt]) {
            //std::cout << "AtlUtil::WARNING: transfer function scale factor set to 1 since function not found!!" << std::endl;
            return 1.0;
         }
         float newpt = -1.0;
         if(opt==1) {
            if(pt<15.0) {
               std::cout << "AtlUtil::ERROR transfer function is not defined for such low/high pt: " << pt << std::endl;            
               exit(1);
            } else if(pt>1000.) {
               newpt = fTF[opt]->Eval(1000.);
            }
            else {
               newpt = fTF[opt]->Eval(pt);
            }
            
         }
         else{
            float Xplateau = 160.0;
            //eta is not implemented..
            if(pt<15.0) {
               std::cout << "AtlUtil::ERROR transfer function is not defined for such low pt: " << pt << std::endl;            
               exit(1);
            } else if(pt<Xplateau) {
               newpt = pt*(fTF[0]->Eval(pt));             
            } else {
               //assume a flat function above 160
               newpt = pt*(fTF[0]->Eval(Xplateau));
            }
         }         
         //std::cout << "AtlUtil::pt of jet " << pt << " and eta " << eta << " -> transfer function gives parton pt: " << newpt << std::endl;                        
         return newpt;
      };
*/



#endif  /* __ATLUTIL_H */
