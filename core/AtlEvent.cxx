/**************************************************************************
 **
 **   File:         AtlEvent.cxx
 **
 **   Description:  See AtlEvent.h
 **
 **   Author:       J. Sjolin, P. Hansson
 **
 **   Created:      
 **   Modified:     
 **
 **************************************************************************/

#include "AtlEvent.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TH1F.h"
#include "assert.h"


void AtlEvent::init(void) {
   weight(0);
   m_is_1We=false;
   m_is_1Wm=false;
   m_isemDil=false;
   m_iseeDil=false;
   m_ismmDil=false;
   m_isDil=false;
   m_isTauDil=false;
   m_isTTbarDil=false;
   m_electrons_fakeable.clear();
   m_electrons_raw.clear();
   m_electrons_loose.clear();
   m_electrons.clear();
   m_electrons_noniso.clear();
   m_electrons_truth.clear();
   m_electrons_truth_raw.clear();
   m_muons_fakeable.clear();
   m_muons_raw.clear();
   m_muons_loose.clear();
   m_muons.clear();
   m_muons_noniso.clear();
   m_muons_truth.clear();
   m_muons_truth_raw.clear();
   //m_neutrinos.clear();
   //m_neutrinos_truth.clear();
   m_taus.clear();
   m_taus_truth.clear();
   m_jets.clear();
   m_jets_truth.clear();
   m_trks.clear();
   m_cells.clear();
   m_l1jets.clear();
   m_l2jets.clear();
   m_l2bjets.clear();
   m_efbjets.clear();
   m_l1emobjs.clear();
   m_l2els.clear();
   m_efels.clear();
   m_partons.clear(); 
   m_leptons_loose.clear();
   m_leptons.clear();
   m_leptons_truth.clear();
   m_rois.clear();
   m_topovars.clear();
   m_metx=0;
   m_mety=0;
   m_nuN =0;
   m_nuP=0;
   m_metx_truth=0;
   m_mety_truth=0;
   m_etsum=0;
   m_isDil=false;
   m_isTauDil=false;
   m_trigdec.Reset();
   beamspot.Reset();
   m_vertex.clear();
}

bool AtlEvent::BuildEvent(EventSrc &src) {

  // This function builds the event:
  // - Copies the TTree variables into the flatana objects
  // - Sorts in pT
  // - Handles overlaps if needed
  // - Can also inject fake objects if needed
  
  init();

  
  //Copy the event variables into the flatana variables
  // if event is already used due to joined trigger chains we skip it
  if (!src.copy_to_interface(*this)) return false;

  //---- Good runs list
  
  //if(!src.passGRL(this->m_runnr,this->m_lumiblocknr)) {
     //cout<<"AtlEvent::BuildEvent: this event from run "<<this->m_runnr<<" and lumiblk "<< this->m_lumiblocknr <<" do not pass GRL"<<std::endl;
  // return false;
  //}

  
  //Overlap removals
  do_overlap();
  
  //Sorting accoring to Pt 
  do_sort_pt();

  // Check for duplicate objects
  if(cfg.get_dupl_obj_check()) { do_duplicate_check(); }
    
  
   return true;
}


void AtlEvent::do_duplicate_check(void) {
  
//    // Duplicate electrons check
//    for(std::vector<Electron>::iterator e1=m_electrons.begin();
//        e1!=m_electrons.end();++e1) {
//       for(std::vector<Electron>::iterator e2=m_electrons.begin();
//           e2!=m_electrons.end();++e2){
//          if (e1!=e2 && e1->p.DeltaR(e2->p)<0.01) {
//             std::cout << "Warning duplicate electrons!!" << std::endl;
// //             std::cout << "electron1:" << endl; e1->print();
// //             std::cout << "electron2:" << endl; e2->print();
//          }
//       }
//    }  
  

  
}

// Overlap removal of objects in the event. 
void AtlEvent::do_overlap(void) {
   
   // // remove electrons which overlaps with jets
   // for(std::vector<Jet>::iterator j=m_jets_truth.begin();
   //     j!=m_jets_truth.end(); ++j) {     
   //   for(std::vector<Electron>::iterator e=m_electrons_truth.begin();
   // 	 e!=m_electrons_truth.end();) {
   //     if (j->p.DeltaR(e->p)<cfg.get_obj_dr()) {
   // 	 e=m_electrons_truth.erase(e);
   // 	 // cout << "jet overlapping with electron removal." << endl;
   //     } else ++e;
   //   }
   // }
   
}

void AtlEvent::do_sort_pt(void) {  
   m_electrons.sort_pt();
   m_electrons_noniso.sort_pt();
   m_electrons_fakeable.sort_pt();
   m_electrons_raw.sort_pt();
   m_electrons_loose.sort_pt();
   m_electrons_truth.sort_pt();
   m_electrons_truth_raw.sort_pt();
   m_muons_fakeable.sort_pt();
   m_muons_raw.sort_pt();
   m_muons_loose.sort_pt();
   m_muons.sort_pt();
   m_muons_noniso.sort_pt();
   m_muons_truth.sort_pt();
   //m_neutrinos.sort_pt();
   //m_neutrinos_truth.sort_pt();
   m_muons_truth_raw.sort_pt();
   m_taus.sort_pt();
   m_taus_truth.sort_pt();
   m_jets.sort_pt();
   m_jets_truth.sort_pt();
   m_trks.sort_pt();
   m_cells.sort_pt();
   m_l1emobjs.sort_pt();
   m_l1jets.sort_pt();
   m_l2jets.sort_pt();
   m_l2bjets.sort_pt();
   m_efbjets.sort_pt();
   // m_l2els.sort_pt();
   // m_efels.sort_pt();

   m_leptons.clear();
   for (int i=0; i<electrons(); ++i)
      m_leptons.push_back(&electron(i));
   for (int i=0; i<muons(); ++i)
      m_leptons.push_back(&muon(i));
   m_leptons.sort_pt();
  
   m_leptons_loose.clear();
   for (int i=0; i<electrons_loose(); ++i)
      m_leptons_loose.push_back(&electron_loose(i));
   for (int i=0; i<muons_loose(); ++i)
      m_leptons_loose.push_back(&muon_loose(i));
   m_leptons_loose.sort_pt();
  
   m_leptons_truth.clear();
   for (int i=0; i<electrons_truth(); ++i)
      m_leptons_truth.push_back(&electron_truth(i));
   for (int i=0; i<muons_truth(); ++i)
      m_leptons_truth.push_back(&muon_truth(i));
   m_leptons_truth.sort_pt();
   
   /*
   m_neutrinos_truth.clear()
   for (int i=0; i<neutrinos_truth(); ++i)
      m_neutrinos_truth.push_back(&neutrino_truth(i));
   m_neutrinos_truth.sort_pt();
   
   m_neutrinos.clear()
     for (int i=0; i<neutrinos(); ++i)
       m_neutrinos.push_back(&neutrino(i));
   m_neutrinos.sort_pt();
   */
}

class ElectronHist {
   public:
      ElectronHist(void) {
         et_n1=new TH1F("ele_et_n1","Electron Et (N-1)",100,0.,300.);
         eta_n1=new TH1F("ele_eta_n1","Electron eta (N-1)",100,-5,5);
         eta2_n1=new TH1F("ele_eta2_n1","Electron eta2 (N-1)",100,-5,5);
         trkpt_n1=new TH1F("ele_trkpt_n1","Electron trkpt (N-1)",100,0.,300.);
         trk_n1=new TH1F("ele_trk_n1","Electron trk (N-1)",100,0.,300.);
         isoA_n1=new TH1F("ele_isoA_n1","Electron iso. (N-1)",100,-10.,80.);
         trkisoA_n1=new TH1F("ele_trkisoA_n1","Ele trk iso (N-1)",100,-10.,80.);
         iso_n1=new TH1F("ele_iso_n1","Electron iso. (N-1)",100,-0.2,1.0);
         trkiso_n1=new TH1F("ele_trkiso_n1","Ele trk iso. (N-1)",100,-0.2,1.0);
         isemsimple_n1=new TH1F("ele_isemsimple_n1","Ele isEM simple (N-1)",5,0.,5.);
         idbits=new TH1F("ele_idbits","Ele ID bits",32,0.,32.);
      }
      void fill_n1(const Electron & ele, const int cuts, const double w) {
         for(int i=0;i!=32;++i) {
            int cut=(1<<i);
            int j = cut&cuts; 
            if(j) idbits->Fill(i);
         }
         if (!(cuts&(~Electron::EG_ET))) et_n1->Fill(ele.p.Et(),w);
	if (!(cuts&(~Electron::EG_ETA))) eta_n1->Fill(ele.p.Eta(),w);
         if (!(cuts&(~Electron::EG_ETA2))) eta2_n1->Fill(ele.p.Eta(),w);
         if (!(cuts&(~Electron::TRK_PT))) trkpt_n1->Fill(ele.TrkPt(),w);
         if (!(cuts&(~Electron::TRK))) trkpt_n1->Fill(ele.TrkPt(),w);
         if (!(cuts&(~Electron::ISO))) {
	   //ele.print();
	   //cout << "l666" << endl;
            iso_n1->Fill(ele.Iso(),w); isoA_n1->Fill(ele.Iso(),w);
         }

         if (!(cuts&(~Electron::TRKISO))) {
            trkiso_n1->Fill(ele.TrkIso(),w); trkisoA_n1->Fill(ele.TrkIso(),w);
         }
         if (!(cuts&(~Electron::ISEM_SIMPLE))) isemsimple_n1->Fill(ele.IsEMsimple(),w);

      }
   private:
      TH1F *et_n1,*eta_n1,*eta2_n1,*trkpt_n1,*trk_n1,*idbits;
      TH1F *iso_n1,*trkiso_n1,*isoA_n1,*trkisoA_n1,*isemsimple_n1;
};
static ElectronHist _he;

// Electron definition
bool AtlEvent::electron_cut_store(Electron & ele, bool tru) {
   int cuts=0;
   util.cut("Electron","KIN","EG_ET",ele.p.Et()<cfg.get_ele_et(),
            Electron::EG_ET,cuts);
   util.cut("Electron","KIN","EG_ETA1",
            fabs(ele.p.Eta())>cfg.get_ele_eta(),Electron::EG_ETA,cuts);
   util.cut("Electron","KIN","EG_ETA2",
            (fabs(ele.p.Eta())>cfg.get_ele_cracklow() &&
             TMath::Abs(ele.p.Eta())<cfg.get_ele_crackhigh()) 
            && cfg.get_ele_crack()==1,Electron::EG_ETA2,cuts);
   util.cut("Electron","KIN","TRK",TMath::Abs(ele.Charge())!=1,
            Electron::TRK,cuts);
   util.cut("Electron","ID","AUTHOR",(ele.author()&1)!=1,Electron::AUTHOR,cuts);
   util.cut("Electron","ID","ISO",
            ele.Iso()>cfg.get_ele_iso()&&cfg.get_ele_iso()>0.,
            Electron::ISO,cuts);
   util.cut("Electron","ID","ISEM_LOOSE",
            ((ele.IsEM())&(cfg.get_loose_ele_em()))!=0,
            Electron::ISEM_LOOSE,cuts);
   util.cut("Electron","ID","ISEM_MEDIUM",(ele.IsEM()&(cfg.get_ele_em()))!=0,
            Electron::ISEM_MEDIUM,cuts);
   util.cut("Electron","ID","ISEM_SIMPLE",cfg.get_ele_em_simple()!=0 && (ele.IsEMsimple()!=cfg.get_ele_em_simple()),
            Electron::ISEM_SIMPLE,cuts);
   if (cfg.get_ele_trk()>0) {
      util.cut("Electron","ID","TRKISO1",ele.TrkIso()>cfg.get_ele_trk(),
               Electron::TRKISO,cuts);
      util.cut("Electron","ID","TRKISO2",ele.TrkIso()<0.0,Electron::TRKISO,cuts);
   }
   if (tru) {
     m_electrons_truth_raw.push_back(ele);
     if (!cuts) {
        m_electrons_truth.push_back(ele);
     }
   }
   else {
     util.cnt1("Electron","Electron","CAND");
     // Match electrons to the available truth electrons added already in FileEvent
     // If the truth matching is done in the ntuple already you can cross-check 
     // that the truth electron is found among the existing ones.
     if(ele.truth_match()) {
       /*
       bool findtruthmatch=false;
       for(std::vector<Electron>::iterator t=m_electrons_truth_raw.begin();
	   t!=m_electrons_truth_raw.end(); ++t) {
	 cout << "AtlEvent: Electron truth match candidate: " << endl; t->print_particle();
	 if (ele.p.DeltaR(t->p)<0.4) {
	   cout << "AtlEvent: Electron truth match!\nparticle: " << endl;t->print_particle();
	   findtruthmatch = true;
	   break;
	 }
       }
       if(!findtruthmatch) {
	 cout << "AtlEvent:WARNING! Could not find the AOD truth match electron among " 
	      << " the truth particles. Something might be wrong?" << endl; //exit(-1);
       }
       */
     } else {
       //there was no match -> try to match here
       for(std::vector<Electron>::iterator t=m_electrons_truth_raw.begin();
	   t!=m_electrons_truth_raw.end(); ++t)
	 if (ele.p.DeltaR(t->p)<0.05) {
	   //cout << "AtlEvent: Electron truth match!\nparticle: " << endl;t->print();
	   ele.truth_match(true);
	   break;
	 }
     }
     _he.fill_n1(ele,cuts,weight());
     ele.IDbits(cuts);
     {
        //isEM cross-check
        int cut = ele.IsEM()&(cfg.get_ele_em());
        if(ele.IsEMsimple() == 2) {
           if(cut!=0) {
              cout << "ISEM ERROR!!??"<<endl; exit(-1);
           }
        }
     }
     if (!(cuts & (~Electron::ISO))) {
        m_electrons_noniso.push_back(ele);
        util.cnt1("Electron","Electron","NONISO");
        if (!cuts) {
           m_electrons.push_back(ele);
           util.cnt1("Electron","Electron","OK");
           if (ele.truth_match()) util.cnt1("Electron","Electron","MAT");
        }
     }
     if ((cuts&(Electron::EG_ET|Electron::EG_ETA|Electron::EG_ETA2))==0) {
       m_electrons_raw.push_back(ele);
       util.cnt1("Electron","Electron","RAW");
       if ((cuts & (Electron::ISO))==0) m_electrons_fakeable.push_back(ele);
       if ((cuts & (Electron::TRK))==0) {
	 bool fail_loose_iso = (cfg.get_loose_ele_iso()>0.) &&
	   (ele.Iso()>cfg.get_loose_ele_iso());
	 if(!fail_loose_iso) {
	   m_electrons_loose.push_back(ele);
	   util.cnt1("Electron","Electron","LOOSE");
	 }
       }
     }
   }

   return !cuts;
}

class MuonHist {
   public:
      MuonHist(void) {
         pt_n1=new TH1F("muon_pt_n1","Muon Pt (N-1)",300,0.,300.);
         eta_n1=new TH1F("muon_eta_n1","Muon Eta (N-1)",100,-5.,5.);
         a0_n1=new TH1F("muon_a0_n1","Muon A0 (N-1)",100,-50,50.);
         z_n1=new TH1F("muon_z_n1","Muon Z (N-1)",100,-200,200.);
         chi2_n1=new TH1F("muon_chi2_n1","Muon Chi2 (N-1)",100,0.,25.);
         fitchi2_n1=new TH1F("muon_fitchi2_n1","Muon track fit Chi2 (N-1)",100,0.,
                             100.);
         matchchi2_n1=new TH1F("muon_matchchi2_n1","Muon match Chi2 (N-1)",100,0.,
                               100.);
         isoA_n1=new TH1F("muon_isoA_n1","Muon Isolation (N-1)",100,-10.,80.);
         isoAlo_n1=new TH1F("muon_isoAlo_n1","Mu low isolation (N-1)",100,-10.,80.);
         trkisoA_n1=new TH1F("muon_trkisoA_n1","Muo trk iso (N-1)",100,-10.,80.);
         iso_n1=new TH1F("muon_iso_n1","Muon Isolation (N-1)",100,-0.2,1.0);
         isolo_n1=new TH1F("muon_isolo_n1","Mu low isolation (N-1)",100,-0.2,1.0);
         trkiso_n1=new TH1F("muon_trkiso_n1","Muon trk iso (N-1)",100,-0.2,1.0);
      }
      void fill_n1(const Muon & muo, const int cuts, const double w) {
         if (!(cuts&(~Muon::PT))) pt_n1->Fill(muo.p.Pt(),w);
         if (!(cuts&(~Muon::ETA))) eta_n1->Fill(muo.p.Eta(),w);
         if (!(cuts&(~Muon::A0))) a0_n1->Fill(muo.a0(),w);
         if (!(cuts&(~Muon::Z))) z_n1->Fill(muo.z(),w);
         if (!(cuts&(~Muon::CHI2))) chi2_n1->Fill(muo.Chi2DoverF(),w);
         if (!(cuts&(~Muon::FITCHI2))) fitchi2_n1->Fill(muo.FitChi2(),w);
         if (!(cuts&(~Muon::MATCHCHI2))) matchchi2_n1->Fill(muo.MatchChi2(),w);
         if (!(cuts&(~Muon::ISO))) {
            iso_n1->Fill(muo.Iso(),w); isoA_n1->Fill(muo.Iso(),w);
         }
         if (!(cuts&(~Muon::ISO_LOOSE))) {
            isolo_n1->Fill(muo.Iso(),w); isoAlo_n1->Fill(muo.Iso(),w);
         }
         if (!(cuts&(~Muon::TRKISO))) {
            trkiso_n1->Fill(muo.TrkIso(),w); trkisoA_n1->Fill(muo.TrkIso(),w);
         }
      }
   private:
      TH1F *pt_n1,*eta_n1,*a0_n1,*z_n1,*chi2_n1,*fitchi2_n1,*matchchi2_n1;
      TH1F *iso_n1,*isolo_n1,*trkiso_n1,*isoA_n1,*isoAlo_n1,*trkisoA_n1;
};
static MuonHist _hm;

// Muon definition
bool AtlEvent::muon_cut_store(Muon & muo, bool tru)
{
   const int STACO=6;
   //const int MUID=12;
   int cuts=0;
   util.cut("Muon","ID","AUTHOR",muo.Author()!=STACO,Muon::AUTHOR,cuts);
   util.cut("Muon","ID","COMB",!muo.isComb(),Muon::COMB,cuts);
   util.cut("Muon","KIN","PT",muo.p.Pt()<cfg.get_muo_pt(),Muon::PT,cuts);

   if (cfg.get_muo_d0_sig()>0) {
      util.cut("Muon","ID","D0",
               TMath::Abs(muo.d0()/muo.d0err())>cfg.get_muo_d0_sig(),
               Muon::A0,cuts);
   }
   util.cut("Muon","KIN","ETA1",fabs(muo.p.Eta())>cfg.get_muo_eta(),
            Muon::ETA,cuts);
   util.cut("Muon","KIN","ETA2",
            ((fabs(muo.p.Eta())>1.0 && fabs(muo.p.Eta())<1.3)
             || fabs(muo.p.Eta())<0.1) && 
            cfg.get_muo_crack()==1, Muon::ETA,cuts);
   util.cut("Muon","ID","ISO",cfg.get_muo_iso()>0 &&
            muo.Iso()>cfg.get_muo_iso(),Muon::ISO,cuts);
   if (cfg.get_muo_chi2()>0)
      util.cut("Muon","ID","CHI2",muo.Chi2DoverF()>cfg.get_muo_chi2(),
               Muon::CHI2,cuts);
   if (cfg.get_muo_fitchi2()>0)
      util.cut("Muon","ID","FITCHI2",muo.FitChi2()>cfg.get_muo_fitchi2(),
               Muon::FITCHI2,cuts);
   if (cfg.get_muo_matchchi2()>0)
      util.cut("Muon","ID","MATCHCHI2",muo.MatchChi2()>cfg.get_muo_matchchi2(),
               Muon::MATCHCHI2,cuts);
   if (cfg.get_muo_trk()>0) {
      util.cut("Muon","ID","TRKISO",muo.TrkIso()>cfg.get_muo_trk(),
               Muon::TRKISO,cuts);
      util.cut("Muon","ID","TRKISO",muo.TrkIso()<0.0,Muon::TRKISO,cuts);
   }
   muo.IDbits(cuts);
   if (tru) {
      m_muons_truth_raw.push_back(muo);
      if (!cuts) m_muons_truth.push_back(muo);
   }
   else {
     util.cnt1("Muon","Muon","CAND");
     // Match muons to the available truth muons added already in FileEvent
     // If the truth matching is done in the ntuple already you can cross-check 
     // that the truth muon is found among the existing ones.
     if(muo.truth_match()) {
       /*
       bool findtruthmatch=false;
       for(std::vector<Muon>::iterator t=m_muons_truth_raw.begin();
	   t!=m_muons_truth_raw.end(); ++t) {
	 //cout << "AtlEvent: Muon truth match candidate: " << endl;t->print_particle();
	 if (muo.p.DeltaR(t->p)<0.4) {
	   //cout << "AtlEvent: Muon truth match! \n particle: " << endl; t->print_particle();
	   findtruthmatch = true;
	   break;
	 }
       }           
       if(!findtruthmatch) {
	 cout << "AtlEvent:WARNING! Could not find the AOD truth match muon among " 
	      << " the truth particles. Something might be wrong?" << endl; //exit(-1);
       }
       */
     } else {
       //Do the truth matching here!
       for(std::vector<Muon>::iterator t=m_muons_truth_raw.begin();
	   t!=m_muons_truth_raw.end(); ++t)
         if (muo.p.DeltaR(t->p)<0.05) muo.truth_match(true);
     }
     _hm.fill_n1(muo,cuts,weight());
     if (!(cuts & (~(Muon::ISO & Muon::TRKISO)))) {
         m_muons_noniso.push_back(muo);
         if (!cuts) {
            m_muons.push_back(muo);
            util.cnt1("Muon","Muon","OK");
            if (muo.truth_match()) util.cnt1("Muon","Muon","MAT");
         }
      }
      if ((cuts&(Muon::PT|Muon::ETA|Muon::AUTHOR))==0) {
         m_muons_raw.push_back(muo);
         util.cnt1("Muon","Muon","RAW");
         if ((cuts&(Muon::PT|Muon::ETA|Muon::COMB|Muon::AUTHOR))==0) {
            m_muons_loose.push_back(muo);
            util.cnt1("Muon","Muon","LOOSE");
         }
      }
   }
   return !cuts;
}

class TauHist {
   public:
      TauHist(void) {
         et_n1=new TH1F("tau_et_n1","Tau Et (N-1)",100,0.,300.);
         eta1_n1=new TH1F("tau_eta1_n1","Tau eta1 (N-1)",100,-5,5);
         eta2_n1=new TH1F("tau_eta2_n1","Tau eta2 (N-1)",100,-5,5);
         emf_n1=new TH1F("tau_emf_n1","Tau EM fraction (N-1)",100,0.,1.);
         emradius_n1=new TH1F("tau_emradius_n1","Tau EM radius (N-1)",100,0.,1.);
         iso_n1=new TH1F("tau_iso_n1","Tau isolation fraction (N-1)",100,-0.1,1.);
         ll_n1=new TH1F("tau_ll_n1","Tau loglikelihood (N-1)",100,-30,30);
      }
      void fill_n1(const Tau & tau, const int cuts, const double w) {
         if (!(cuts&(~Tau::ET))) et_n1->Fill(tau.p.Et(),w);
         if (!(cuts&(~Tau::ETA1))) eta1_n1->Fill(tau.p.Eta(),w);
         if (!(cuts&(~Tau::ETA2))) eta2_n1->Fill(tau.p.Eta(),w);
         if (!(cuts&(~Tau::LL))) ll_n1->Fill(tau.loglikelihood(),w);
         if (!(cuts&(~Tau::EMF))) emf_n1->Fill(tau.emf(),w);
         if (!(cuts&(~Tau::EMRAD))) emradius_n1->Fill(tau.emradius(),w);
         if (!(cuts&(~Tau::ISO))) iso_n1->Fill(tau.iso(),w);
      }
   private:
      TH1F *et_n1,*eta1_n1,*eta2_n1,*ll_n1,*emf_n1,*emradius_n1,*iso_n1;
};
static TauHist _ht;

// Tau definition (EM like jet!!)
bool AtlEvent::tau_cut_store(const Tau & tau)
{
   int cuts=0;
   util.cut("Tau","Tau","CAND",false,0,cuts);
   util.cut("Tau","KIN","ET",tau.p.Et()<cfg.get_tau_et(),Tau::ET,cuts);
   util.cut("Tau","KIN","ETA1",
            fabs(tau.p.Eta())>cfg.get_tau_eta(),Tau::ETA1,cuts);
   // Problem with electron scale below 1.65
   util.cut("Tau","KIN","ETA2",
            fabs(tau.p.Eta())>1.37 && TMath::Abs(tau.p.Eta())<1.52 &&
            cfg.get_tau_crack()==1,Tau::ETA2,cuts);
   //util.cut("Tau","ID","EMF",tau.emf()<0.92,Tau::EMF,cuts);
   if (!cuts) m_taus.push_back(tau);
   _ht.fill_n1(tau,cuts,weight());
   return !cuts;
}

class JetHist {
   public:
      JetHist(void) {
         et_n1=new TH1F("jet_et_n1","Jet Et (N-1)",100,0.,300.);
         eta_n1=new TH1F("jet_eta_n1","Jet eta (N-1)",100,-5,5);
         qual_n1=new TH1F("jet_quality_n1","Jet quality (N-1)",10,-5,5);
         goodness_n1=new TH1F("jet_goodness_n1","Jet goodness (N-1)",5,0,5);
      }
      void fill_n1(const Jet & jet, const int cuts, const double w) {
         if (!(cuts&(~Jet::ET))) {
            et_n1->Fill(jet.p.Et(),w);
         }
         if (!(cuts&(~Jet::ETA))) {
            eta_n1->Fill(jet.p.Eta(),w);
         }
         if (!(cuts&(~Jet::QUAL))) {
            qual_n1->Fill(jet.jetQuality(),w);
         }
         if (!(cuts&(~Jet::GOODNESS))) {
            goodness_n1->Fill(jet.goodness(),w);
         }
      }
   private:
      TH1F *et_n1,*eta_n1,*qual_n1,*goodness_n1;
};
static JetHist _hj;

// Jet definition
bool AtlEvent::jet_cut_store(const Jet & jet, bool tru)
{
   int cuts=0;
   util.cut("Jet","Jet","CAND",false,0,cuts);
   util.cut("Jet","KIN","ET",jet.p.Et()<cfg.get_jet_et(),Jet::ET,cuts);
   if(cfg.get_jet_eta()>0.)
      util.cut("Jet","KIN","ETA",fabs(jet.p.Eta())>cfg.get_jet_eta(),
               Jet::ETA,cuts);
   //Cuts not applicable to truth jets
   if(!tru) {
      util.cut("Jet","QUAL","QUAL",jet.jetQuality()<-99999999,Jet::QUAL,cuts);   
      if(cfg.get_jet_goodness()>=0)
         util.cut("Jet","QUAL","GOODNESS",jet.goodness()!=cfg.get_jet_goodness(),Jet::GOODNESS,cuts);
      util.cut("Jet","QUAL","GOODNESS",jet.goodness()<-999999,Jet::GOODNESS,cuts);
   }
   if (tru) {
      if (!cuts) m_jets_truth.push_back(jet);
   }
   else {
      _hj.fill_n1(jet,cuts,weight());
      if (!cuts) {
         util.cnt1("Jet","Jet","OK");
         m_jets.push_back(jet);
      }
   }
   return !cuts;
}
// Track definition
bool AtlEvent::trk_cut_store(const Track & trk)
{
   int cuts=0;
   util.cnt1("Trk","Trk","CAND");
   util.cut("Trk","KIN","P",trk.p.P()<cfg.get_trk_p(),Track::P,cuts);
   if (!cuts) {
   util.cnt1("Trk","Trk","OK");     
     m_trks.push_back(trk);
   }
   return !cuts;
}

// Vertex definition
bool AtlEvent::vtx_cut_store(const Vertex & vtx)
{
   int cuts=0;
   util.cnt1("Vtx","Vtx","CAND");
   //util.cut("Trk","KIN","PT",trk.p.Pt()<cfg.get_trk_pt(),Trk::PT,cuts);
   if (!cuts) m_vertex.push_back(vtx);
   return !cuts;
}




class L1JetHist {
   public:
      L1JetHist(void) {
         et_n1=new TH1F("l1jet_et_n1","L1Jet Et (N-1)",100,0.,300.);
      }
      void fill_n1(const L1Jet & l1jet, const int cuts, const double w) {
         if (!(cuts&(~L1Jet::ET))) {
            et_n1->Fill(l1jet.p.Et(),w);
         }
      }
   private:
      TH1F *et_n1;
};
static L1JetHist _hl1j;

// L1Jet definition
bool AtlEvent::l1jet_cut_store(const L1Jet & l1jet)
{
   int cuts=0;
   util.cut("L1Jet","L1Jet","CAND",false,0,cuts);
   _hl1j.fill_n1(l1jet,cuts,weight());
   if (!cuts) {
      util.cnt1("L1Jet","L1Jet","OK");
      m_l1jets.push_back(l1jet);
   }    
   return !cuts;
}



class L2JetHist {
   public:
      L2JetHist(void) {
         et_n1=new TH1F("l2jet_et_n1","L2 Jet Et (N-1)",100,0.,300.);
         e_n1=new TH1F("l2jet_e_n1","L2 Jet E (N-1)",100,0.,300.);
      }
      void fill_n1(const Jet & l2jet, const int cuts, const double w) {
         if (!(cuts&(~Jet::ET))) {
            et_n1->Fill(l2jet.p.Et(),w);
         }
         if (!(cuts&(~Jet::E))) {
            e_n1->Fill(l2jet.p.E(),w);
         }
      }
   private:
      TH1F *et_n1,*e_n1;
};
static L2JetHist _hl2j;

// L2 Jet definition
bool AtlEvent::l2jet_cut_store(const Jet & l2jet)
{
   int cuts=0;
   util.cut("L2Jet","L2Jet","CAND",false,0,cuts);
   util.cut("L2Jet","L2Jet","E",l2jet.p.E()<cfg.get_l2_jet_e(),
            Jet::E,cuts);
   _hl2j.fill_n1(l2jet,cuts,weight());
   if (!cuts) {
      util.cnt1("L2Jet","L2Jet","OK");
      m_l2jets.push_back(l2jet);
   }    
   return !cuts;
}


class L2BJetHist {
   public:
      L2BJetHist(const std::string& name="") {
         et_n1=new TH1F(TString::Format("%sbjet_et_n1",name.c_str()),TString::Format("%sBJet Et (N-1)",name.c_str()),100,0.,300.);
      }
      void fill_n1(const L2BJet & l1jet, const int cuts, const double w) {
         if (!(cuts&(~L2BJet::ET))) {
            et_n1->Fill(l1jet.p.Et(),w);
         }
      }
   private:
      TH1F *et_n1;
};
static L2BJetHist _hl2bj("L2");
static L2BJetHist _hefbj("EF");

// L2BJet definition
bool AtlEvent::l2bjet_cut_store(const L2BJet & l2bjet)
{
   int cuts=0;
   util.cut("L2BJet","L2BJet","CAND",false,0,cuts);
   _hl2bj.fill_n1(l2bjet,cuts,weight());
   if (!cuts) {
      util.cnt1("L2BJet","L2BJet","OK");
      m_l2bjets.push_back(l2bjet);
   }   
   return !cuts;
}

// EFBJet definition
bool AtlEvent::efbjet_cut_store(const L2BJet & efbjet)
{
   int cuts=0;
   util.cut("EFBJet","EFBJet","CAND",false,0,cuts);
   _hefbj.fill_n1(efbjet,cuts,weight());
   if (!cuts) {
      util.cnt1("EFBJet","EFBJet","OK");
      m_efbjets.push_back(efbjet);
   }   
   return !cuts;
}



class L1EMHist {
   public:
      L1EMHist(void) {
         et_n1=new TH1F("l1em_et_n1","L1EM Et (N-1)",100,0.,300.);
         emisol_n1=new TH1F("l1em_emisol_n1","L1EM EmIsol (N-1)",100,0.,10.);
         hdisol_n1=new TH1F("l1em_hdisol_n1","L1EM HdIsol (N-1)",100,0.,10.);
         hdcore_n1=new TH1F("l1em_hdcore_n1","L1EM HdCore (N-1)",100,0.,10.);
      }
      void fill_n1(const L1EMObj & l1em, const int cuts, const double w) {
         if (!(cuts&(~L1EMObj::ET))) et_n1->Fill(l1em.p.Et(),w);
         if (!(cuts&(~L1EMObj::EMISOL))) emisol_n1->Fill(l1em.EmIso(),w);
         if (!(cuts&(~L1EMObj::HDISOL))) hdisol_n1->Fill(l1em.HdIso(),w);
         if (!(cuts&(~L1EMObj::HDCORE))) hdcore_n1->Fill(l1em.HdCore(),w);
      }
   private:
      TH1F *et_n1,*emisol_n1,*hdisol_n1,*hdcore_n1;
};
static L1EMHist _hl1em;

// L1EMObj definition
void AtlEvent::l1emobj_cut_store(L1EMObj & em)
{
   int cuts=0;
   util.cut("L1EMObj","L1EMObj","CAND",false,0,cuts);
//    util.cut("L1EMObj","KIN","ET",em.p.Et()<18,L1EMObj::ET,cuts);
//    util.cut("L1EMObj","KIN","EMISOL",em.EmIso()>3.,L1EMObj::EMISOL,cuts);
//    util.cut("L1EMObj","KIN","HDISOL",em.HdIso()>2.,L1EMObj::HDISOL,cuts);
//    util.cut("L1EMObj","KIN","HDCORE",em.HdCore()>2.,L1EMObj::HDCORE,cuts);
   _hl1em.fill_n1(em,cuts,weight());

   if(TMath::Abs(em.p.Eta())<= 2.5) {
      if(em.EmClus()> 18.0) {
         if(em.EmIso() <= 3.0) {
            if(em.HdCore() <= 2.0) {
               if(em.HdIso() <= 2.0) {
                  em.SetType("L1_EM25I");
               }
            }
         }
      }
   }

   if(TMath::Abs(em.p.Eta())<= 2.5) {
      if(em.EmClus()> 11.0) {
         if(em.EmIso() <= 3.0) {
            if(em.HdCore() <= 2.0) {
               if(em.HdIso() <= 2.0) {
                  em.SetType("L1_2EM15I");
               }
            }
         }
      }
   }

   if(TMath::Abs(em.p.Eta())<= 2.5) {
      if(em.EmClus()> 50.0) {
         em.SetType("L1_EM60");
      }
   }

   em.Index(static_cast<int>(m_l1emobjs.size()));
   if (!cuts) m_l1emobjs.push_back(em);
   util.cut("L1EMObj","L1EMObj","INSERTED",false,0,cuts);
}

class L2ElHist {
   public:
      L2ElHist(void) {
         et_n1=new TH1F("l2el_et_n1","L2El Et (N-1)",100,0.,300.);
         eta_n1=new TH1F("l2el_eta_n1","L2El Eta (N-1)",100,0.,300.);
         emisol_n1=new TH1F("l2el_emisol_n1","L2El EmIsol (N-1)",100,0.,10.);
         hdisol_n1=new TH1F("l2el_hdisol_n1","L2El HdIsol (N-1)",100,0.,10.);
         hdcore_n1=new TH1F("l2el_hdcore_n1","L2El HdCore (N-1)",100,0.,10.);
      }
      void fill_n1(const L2El & l2el, const int cuts, const double w) {
         if (!(cuts&(~L2El::ET))) et_n1->Fill(l2el.p.Et(),w);
         if (!(cuts&(~L2El::ETA))) eta_n1->Fill(l2el.p.Eta(),w);
      }
   private:
      TH1F *et_n1,*emisol_n1,*hdisol_n1,*hdcore_n1,*eta_n1;
};
static L2ElHist _hl2el;

// L2El definition
void AtlEvent::l2el_cut_store(L2El & em)
{
   int cuts=0;
   util.cut("L2El","L2El","CAND",false,0,cuts);
   _hl2el.fill_n1(em,cuts,weight());

   if(em.CL_Et()>20.0) {
      double eta = TMath::Abs(em.p.Eta());
      int etabin;
      if(eta <=0.75) etabin=0;
      else if(eta <=1.5) etabin=1;
      else if(eta <=1.8) etabin=2;
      else if(eta <=2.0) etabin=3;
      else if(eta <=2.5) etabin=4;
      else etabin=-1;
      
      if(etabin>=0) {         
         double ep_cal_leak[5] = {3.8,3.8,3.8,3.8,3.8};
         // no leakage cut > 90GeV
         if( em.CL_ehad()<ep_cal_leak[etabin] || em.CL_Et()>90.0 ) {
            double ep_Rcore[5] = {0.895,0.895,0.895,0.895,0.895};
            if( em.Rcore()>ep_Rcore[etabin] ) { 
               double ep_Eratio[5] = {0.730,0.730,0.730,0.730,0.730};
               if( (em.Eratio()>ep_Eratio[etabin])
                   || (eta>2.37 || (eta>1.37&&eta<1.52)) )  { 
                  //redefine etabins for ID
                  if(eta <=0.75) etabin=0;
                  else if(eta <=1.5) etabin=1;
                  else if(eta <=2.0) etabin=2;
                  else if(eta <=2.5) etabin=3;
                  else etabin=-1;
                  assert(etabin!=-1);
                  if(em.ID_p_T()>5.0) {
                     double ep_Ep_l[4] = {0.5,0.5,0.5,0.5};
                     if(em.ID_Ep()>ep_Ep_l[etabin]) {
                        double ep_Ep_u[4] = {5.5,5.5,5.5,5.5};
                        if(em.ID_Ep()<ep_Ep_u[etabin]) {
                           double ep_Deta[4] = {0.018,0.018,0.018,0.018};
                           if(em.CL_ID_Deta()<ep_Deta[etabin]) {
                              double ep_Dphi[4] = {0.06,0.06,0.06,0.06};
                              if(em.CL_ID_Dphi()<ep_Dphi[etabin]) {
                                 em.SetType("L2_e25i");
                              }
                           }
                        }
                     }
                  }                  
               }
            }
         }
      }  
   }
   
   if(em.CL_Et()>12.0) {      
      double eta = TMath::Abs(em.p.Eta());
      int etabin;
      if(eta <=0.75) etabin=0;
      else if(eta <=1.5) etabin=1;
      else if(eta <=1.8) etabin=2;
      else if(eta <=2.0) etabin=3;
      else if(eta <=2.5) etabin=4;
      else etabin=-1;
      
      if(etabin>=0) {         
         double ep_cal_leak[5] = {1.0,1.0,4.0,1.5,1.0};         
         // no leakage cut > 90GeV
         if( em.CL_ehad()<ep_cal_leak[etabin] || em.CL_Et()>90.0 ) {
            double ep_Rcore[5] = {0.9,0.89,0.89,0.9,0.89};
            if( em.Rcore()>ep_Rcore[etabin] ) { 
               double ep_Eratio[5] = {0.6,0.7,0.75,0.85,0.9};
               if( (em.Eratio()>ep_Eratio[etabin]) ||
                   (eta>2.37 ||(eta>1.37&&eta<1.52)) )  { 
                  //redefine etabins for ID
                  if(eta <=0.75) etabin=0;
                  else if(eta <=1.5) etabin=1;
                  else if(eta <=2.0) etabin=2;
                  else if(eta <=2.5) etabin=3;
                  else etabin=-1;
                  assert(etabin!=-1);
                  if(em.ID_p_T()>5.0) {
                     double ep_Ep_l[4] = {0.5,0.0,0.0,0.0};
                     if(em.ID_Ep()>ep_Ep_l[etabin]) {
                        double ep_Ep_u[4] = {4.0,4.5,5.5,5.5};
                        if(em.ID_Ep()<ep_Ep_u[etabin]) {
                           double ep_Deta[4] = {0.016,0.012,0.01,0.03};
                           if(em.CL_ID_Deta()<ep_Deta[etabin]) {
                              double ep_Dphi[4] = {0.04,0.06,0.1,0.08};
                              if(em.CL_ID_Dphi()<ep_Dphi[etabin]) {
                                 em.SetType("L2_2e15i");
                              }
                           }
                        }
                     }
                  }                  
               }
            }
         }
      }
   }
   
   if(em.CL_Et()>53.0) {   
      double eta = TMath::Abs(em.p.Eta());
      int etabin;
      if(eta <=0.75) etabin=0;
      else if(eta <=1.5) etabin=1;
      else if(eta <=1.8) etabin=2;
      else if(eta <=2.0) etabin=3;
      else if(eta <=2.5) etabin=4;
      else etabin=-1;
      
      if(etabin>=0) {         
         double ep_cal_leak[5] = {999.0,999.0,999.0,999.0,999.0};
         // no leakage cut > 90GeV
         if( em.CL_ehad()<ep_cal_leak[etabin] || em.CL_Et()>90.0 ) {
            double ep_Rcore[5] = {0.93,0.92,0.92,0.93,0.92};
            if( em.Rcore()>ep_Rcore[etabin] ) { 
               double ep_Eratio[5] = {0.85,0.75,0.8,0.85,0.85};
               if( (em.Eratio()>ep_Eratio[etabin]) ||
                   (eta>2.37 ||(eta>1.37&&eta<1.52)) )  { 
                  //redefine etabins for ID
                  if(eta <=0.75) etabin=0;
                  else if(eta <=1.5) etabin=1;
                  else if(eta <=2.0) etabin=2;
                  else if(eta <=2.5) etabin=3;
                  else etabin=-1;
                  assert(etabin!=-1);
                  if(em.ID_p_T()>5.0) {
                     double ep_Ep_l[4] = {0.5,0.5,0.5,0.5};
                     if(em.ID_Ep()>ep_Ep_l[etabin]) {
                        double ep_Ep_u[4] = {5.5,5.5,5.5,5.5};
                        if(em.ID_Ep()<ep_Ep_u[etabin]) {
                           double ep_Deta[4] = {0.018,0.018,0.018,0.018};
                           if(em.CL_ID_Deta()<ep_Deta[etabin]) {
                              double ep_Dphi[4] = {0.06,0.06,0.06,0.06};
                              if(em.CL_ID_Dphi()<ep_Dphi[etabin]) {
                                 em.SetType("L2_e60");
                              }
                           }
                        }
                     }
                  }                  
               }
            }
         }
      }
   }

   em.Index(static_cast<int>(m_l2els.size()));
   if (!cuts) m_l2els.push_back(em);
   util.cut("L2El","L2El","INSERTED",false,0,cuts);
}

class EFElHist {
   public:
      EFElHist(void) {
         et_n1=new TH1F("efel_et_n1","EFEl Et (N-1)",100,0.,300.);
         eta_n1=new TH1F("efel_eta_n1","EFEl Eta (N-1)",100,-3.,3.);
         eoverp_n1=new TH1F("efel_eoverp_n1","EFEl eoverp (N-1)",100,0.,10.);
         etcone_n1=new TH1F("efel_etcone_n1","EFEl etcone (N-1)",100,0.,10.);
      }
      void fill_n1(const EFEl & efel, const int cuts, const double w) {
         if (!(cuts&(~EFEl::ET))) et_n1->Fill(efel.p.Et(),w);
         if (!(cuts&(~EFEl::ETA))) eta_n1->Fill(efel.p.Eta(),w);
      }
   private:
      TH1F *et_n1,*eoverp_n1,*etcone_n1,*eta_n1;
};
static EFElHist _hefel;

// EFEl definition
void AtlEvent::efel_cut_store( EFEl & em)
{
   int cuts=0;
   util.cut("EFEl","EFEl","CAND",false,0,cuts);

   _hefel.fill_n1(em,cuts,weight());

   //!!!!!! This should be the EM Cluster
   //!!!!!! Not sure if its correct
   if(em.p.Et()>22.5) {
      double eta = TMath::Abs(em.p.Eta());
      int etabin;
      if(eta <=1.37) etabin=0;
      else etabin=1;
      
      double ep_l[2] = {0.5,0.5};
      if( em.EoverP()>ep_l[etabin] ) {
         double ep_u[2] = {2.08,3.86};
         if( em.EoverP()<ep_u[etabin] ) {
            if(em.TrkClsDeta()<0.0036) {
               if(em.TrkClsDphi()<0.037) {
                  em.SetType("EF_e25i");
               }
            }
         }         
      }      
   }

   //!!!!!! This should be the EM Cluster
   //!!!!!! Not sure if its correct
   //!!!!!! The Deta/Dphi of trkClust is not in there yet!
   if(em.p.Et()>12.5) {
      double eta = TMath::Abs(em.p.Eta());
      int etabin;
      if(eta <=1.37) etabin=0;
      else etabin=1;
      
      double ep_l[2] = {0.8,0.6};
      if( em.EoverP()>ep_l[etabin] ) {
         double ep_u[2] = {2.5,4.0};
         if( em.EoverP()<ep_u[etabin] ) {
            if(em.TrkClsDeta()<0.002) {
               if(em.TrkClsDphi()<0.02) {                  
                  em.SetType("EF_2e15i");
               }
            }
         }         
      }
   }

   //!!!!!! This should be the EM Cluster
   //!!!!!! Not sure if its correct
   //!!!!!! The Deta/Dphi of trkClust is not in there yet!
   if(em.p.Et()>57.5) {
      double eta = TMath::Abs(em.p.Eta());
      int etabin;
      if(eta <=1.37) etabin=0;
      else etabin=1;
      
      double ep_l[2] = {0.8,0.7};
      if( em.EoverP()>ep_l[etabin] ) {
         double ep_u[2] = {2.2,3.5};
         if( em.EoverP()<ep_u[etabin] ) {
            if(em.TrkClsDeta()<0.002) {
               if(em.TrkClsDphi()<0.025) {                  
                  em.SetType("EF_e60");
               }
            }
         }         
      }
   }

   em.Index(static_cast<int>(m_efels.size()));
   if (!cuts) m_efels.push_back(em);
   util.cut("EFEl","EFEl","INSERTED",false,0,cuts);
}

void AtlEvent::print(int level) {   
   std::cout << "-----------\nEvent: " << m_evtnr << " Run: " <<
      m_runnr <<std::endl;      
   std::cout << "Njets=" << jets() << " MET="<< met() <<std::endl;
   std::cout << "Nleptons=" << leptons() << " Nelectrons=" << electrons()
             << " Nmuons="<<muons() <<std::endl;
   std::cout << "Nlep true=" << leptons_truth() << " Nele true=" << electrons_truth()
             << " Nmuons true="<<muons_truth() <<std::endl;
  
   if(level>1)  std::cout << "N raw ele=" <<  electrons_raw()  
                          << " N loose muons=" << muons_raw() 
                          << "N loose ele=" << electrons_loose() << std::endl;   
  
   if (level>0) {
      for(int i=0;i!=jets();++i) jet(i).print();
      for(int i=0;i!=electrons();++i) electron(i).print();
      for(int i=0;i!=muons();++i) muon(i).print();
     
      if(level>1) {
         std::cout << "Raw El:" << std::endl;
         for(int i=0;i!=electrons_raw();++i) electron_raw(i).print();
      
         std::cout << "Loose El:" << std::endl;
         for(int i=0;i!=electrons_loose();++i) electron_loose(i).print();
       
         std::cout << "Loose Mu:" << std::endl;      
         for(int i=0;i!=muons_raw();++i) muon_raw(i).print();
      }
   }
   std::cout << "-----------\n" << std::endl;
}

int AtlEvent::L1SumJetEt(std::string vetostr, double absetacut) {
   // loop over the L1 jet ROIs and add the threshold passed
   std::map<int,int> thrs;
   if(cfg.get_debug()>1) std::cout << "L1SumJetEt for " << m_l1jets.size() <<  " objects" <<endl;
   for(int i=0;i!=(int)m_l1jets.size();++i) {
      //find the threshold that this ROI passed
      //remove forward jet?
      if(cfg.get_debug()>1) std::cout << "L1 jet "<< i << endl;
      for(std::map<string,double>::const_iterator j = m_l1jets[i].m_passedThresholds.begin(); j!=m_l1jets[i].m_passedThresholds.end();++j) {
         if(j->first.find("win")==std::string::npos) {
            bool use = true;
            if(vetostr!="") {
               //veto all trigger threhold names with this string
               if(j->first.find(vetostr)==std::string::npos) 
                  use=true;
               else
                  use=false;
            }
            //cut on eta
            if(TMath::Abs(m_l1jets[i].p.Eta())>absetacut) {
               use=false;
            }
            if(use) {
               thrs[(int)j->second]++;
               if(cfg.get_debug()>1) std::cout << "adding thr "<< j->second << " -> "<< thrs[(int)j->second] <<" so far" << endl;
            }
         }
      }
   }
   
   if(cfg.get_debug()>1) std::cout << "calculate sumjetpt " << endl;
   //now add them with weight from threshold
   int jetetsum = 0;
   for(std::map<int,int>::const_iterator i=thrs.begin();i!=thrs.end();++i) {
      int t = i->first;
      int n = i->second;
      jetetsum += t*n;
      if(cfg.get_debug()>1) std::cout << "t="<<t<<" n="<<n<<" jetetsum="<<jetetsum<<endl;
   }
   if(cfg.get_debug()>1) std::cout << "resulting sumjetpt " <<jetetsum << endl;
   
   return jetetsum;
   
}


double AtlEvent::L2SumJetEt(bool EMscale, double absetacut) {
   // loop over the L2 jets and add the threshold passed
   
   double sumjetet=0.0;
   if(cfg.get_debug()>1) std::cout << "L2SumJetEt for " << m_l2jets.size() <<  " objects" 
				   << (EMscale?" at EM scale!":"")<<endl;
   double pt;
   for(int i=0;i!=(int)m_l2jets.size();++i) {      
     if(cfg.get_debug()>1) std::cout << "Adding L2 jet at index "<< i << endl;
     //abs(Eta) cut
     if(TMath::Abs(m_l2jets[i].p.Eta())>absetacut) {
        if(cfg.get_debug()>1) std::cout << "eta = "<<m_l2jets[i].p.Eta()<<" -> not within abs(eta) cut at "<< absetacut << endl;
        continue;
     }
     if(EMscale) {
        Particle part(m_l2jets[i]);
        double e = m_l2jets[i].EMEnergy()+m_l2jets[i].HADEnergy();
        double scale = e/m_l2jets[i].p.E();
        part.p*=scale;
        pt = part.p.Pt();       
        if(cfg.get_debug()>1) std::cout << "EM scale pt="<<pt<<" before rescaling pt="<<m_l2jets[i].p.Pt()
                                        << "(E="<<m_l2jets[i].p.E()<<" e="<<e<<" scale="<<scale<<std::endl;
     }
     else { 
        pt = m_l2jets[i].p.Pt();
     }
     sumjetet += pt;
     if(cfg.get_debug()>1) std::cout << "L2 jet at index "<< i << " with pT="<< pt << " added: so far l2sumjetet="<<sumjetet <<  endl;
   }
   return sumjetet;
}

double AtlEvent::SumJetEt(bool isTru, double absetacut) {
   // loop over the jets and add the threshold passed
   
   double sumjetet=0.0;
   if(cfg.get_debug()>1) std::cout << "SumJetEt for " << m_jets.size() <<  " objects" << endl;
   double pt;   
   if(isTru) {
      
      for(int i=0;i!=(int)m_jets_truth.size();++i) {      
         if(cfg.get_debug()>1) std::cout << "Adding truth jet at index "<< i << endl;
         if(TMath::Abs(m_jets_truth[i].p.Eta())>absetacut) {
            if(cfg.get_debug()>1) std::cout << "eta = "<<m_jets_truth[i].p.Eta()<<" -> not within abs(eta) cut at "<< absetacut << endl;
            continue;
         }
         pt = m_jets_truth[i].p.Pt();
         sumjetet += pt;
         if(cfg.get_debug()>1) std::cout << " truth jet at index "<< i << " with pT="<< pt << " added: so far sumjetet="<<sumjetet <<  endl;
      }
      
   }
   else {
      
      for(int i=0;i!=(int)m_jets.size();++i) {      
         if(cfg.get_debug()>1) std::cout << "Adding  jet at index "<< i << endl;
         if(TMath::Abs(m_jets[i].p.Eta())>absetacut) {
            if(cfg.get_debug()>1) std::cout << "eta = "<<m_jets[i].p.Eta()<<" -> not within abs(eta) cut at "<< absetacut << endl;
            continue;
         }
         pt = m_jets[i].p.Pt();
         sumjetet += pt;
         if(cfg.get_debug()>1) std::cout << " jet at index "<< i << " with pT="<< pt << " added: so far sumjetet="<<sumjetet <<  endl;
      }
      
   }
   return sumjetet;
}

