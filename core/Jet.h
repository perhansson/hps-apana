/**************************************************************************
 **
 **   File:         Jet.h
 **
 **   Description:  Generic analysis jet
 **
 **   Author:       J. Sjolin
 **
 **   Created:      Mon Sep 19 16:20:04 CEST 2005
 **   Modified:
 **
 **************************************************************************/

#ifndef __JET_H
#define __JET_H

#include "Particle.h"


bool isBadJet(float n90, float hecFrac,
           float jetQuality, float emf, float time)
{
   bool result=false;
   if ( (n90 <= 5 && hecFrac>0.8) ||
        (fabs(jetQuality)>0.8 && emf>0.95) ||
        fabs(time)>50 )
      result = true;
   
   return result;
}
bool isGoodJet(float jetN90, float hecFrac,
               float jetQuality, float jetemf, float jettime)
{
   bool result=false;
   if ( !isBadJet(jetN90, hecFrac, jetQuality, jetemf,jettime) )  result = true;
   return result;
}

// bool isGoodJet(float tileGap3Frac, float bch,
//             float jetN90, float hecFrac,
//             float jetQuality, float jetemf, float jettime)
// {
//    bool result=false;
   
//    if ( !isBadJet(jetN90, hecFrac, jetQuality, jetemf,jettime)
//         /*&&!isUgly(tileGap3Frac, bch)*/) result = true;
   
//    return result;
// }


bool isUglyJet(float tileGap3Frac, float BCH_CORR_CELL)
{
   bool result=false;
   if (tileGap3Frac>0.5 || BCH_CORR_CELL>0.5) result=true;
   return result;
}


class BtagProperties {
 public:
 BtagProperties(void) : m_flavor(0)
    , m_dr_bquark(-9999.)
    , m_dr_cquark(-9999.)
    , m_SV1_w(-9999.)
    , m_SV_m(-9999.)
    , m_SV_Lxy_sig(-9999.)  
    , m_SV2_w(-9999.)
    , m_JetProb_w(-9999.)
    , m_SV1IP3D_w(-9999.)
    , m_JetFitterComb_w(-9999.)
    , m_JetFitterNN_w(-9999.)
    , m_JetFitterNNComb_w(-9999.)
    , m_IPTrack_d0sig(-9999.)
    , m_IP1D_w(-9999.)
    , m_IP2D_w(-9999.)
    , m_IP3D_w(-9999.)
    , m_JVF(-9999.)
    , m_NV(-9999.)
    , m_SV0_w(-9999.)
    , m_mutag_w(0.)                      
    , m_mutag_ptrel(0.)                      
    , m_manual_tag_prob(-1.) {};
  
  int flavor(void) const { return m_flavor; }; 
  void flavor(const int& v) { m_flavor=v; }; 
  double bquark_dr(void) const { return m_dr_bquark; };
  void bquark_dr(const double& v) {  m_dr_bquark=v; };
  double cquark_dr(void) const { return m_dr_cquark; };
  void cquark_dr(const double& v) { m_dr_cquark=v; };
  double SV1_w(void) const { return m_SV1_w; };
  void SV1_w(const double& v) { m_SV1_w=v; };
  double SV_m(void) const { return m_SV_m; };
  void SV2_w(const double& v) { m_SV2_w=v; };
  double SV2_w(void) const { return m_SV2_w; };
  void JetProb_w(const double& v) { m_JetProb_w=v; };
  double JetProb_w(void) const { return m_JetProb_w; };
  double SV1IP3D_w(void) const { return m_SV1IP3D_w; };
  void SV1IP3D_w(const double& v) { m_SV1IP3D_w=v; };

  void SV0_w(const double& v) { m_SV0_w=v; };
  double SV0_w(void) const { return m_SV0_w; };
  void mutag_w(const double& v) { m_mutag_w=v; };
  double mutag_w(void) const { return m_mutag_w; };
  void mutag_ptrel(const double& v) { m_mutag_ptrel=v; };
  double mutag_ptrel(void) const { return m_mutag_ptrel; };


  double JVF(void) const { return m_JVF; };
  void JVF(const double& v){ m_JVF=v; };
  double NV(void) const { return m_NV; };
  void NV(const double& v){ m_NV=v; };


 
  double JetFitterComb_w(void) const { return m_JetFitterComb_w; };
  double JetFitterNN_w(void) const { return m_JetFitterNN_w; };
  double JetFitterNNComb_w(void) const { return m_JetFitterNNComb_w; };
  double IPTrack_d0sig(void) const { return m_IPTrack_d0sig; };  
  double IP1D_w(void) const { return m_IP1D_w; };
  void IP1D_w(const double& v) { m_IP1D_w=v; };
  double IP2D_w(void) const { return m_IP2D_w; };
  void IP2D_w(const double& v) { m_IP2D_w=v; };
  double IP3D_w(void) const { return m_IP3D_w; };
  void IP3D_w(const double& v) { m_IP3D_w=v; };
  void TagProbMan(const double& v) {m_manual_tag_prob=v;};
  double TagProbMan(void) const {return m_manual_tag_prob;};

  
 private:
  int m_flavor;
  double m_dr_bquark;
  double m_dr_cquark;
  double m_SV1_w;
  double m_SV_m;
  double m_SV_Lxy_sig;  
  double m_SV2_w;
  double m_JetProb_w;
  double m_SV1IP3D_w;
  double m_JetFitterComb_w;
  double m_JetFitterNN_w;
  double m_JetFitterNNComb_w;
  double m_IPTrack_d0sig;
  double m_IP1D_w;
  double m_IP2D_w;
  double m_IP3D_w;
  double m_JVF;
  double m_NV;
  double m_SV0_w;
  double m_mutag_w;
  double m_mutag_ptrel;

  // variable to set
  double m_manual_tag_prob;
  
};


class Jet : public Particle , public BtagProperties {
 public:
      enum JET_CUTS {ET=(1<<0), ETA=(1<<1),QUAL=(1<<2),GOODNESS=(1<<3),E=(1<<4)};
      Jet(const Particle &p) : Particle(p),m_emenergy(-1.),m_hadenergy(-1.)
                             , m_n90(-1.)
                             , m_hecFrac(-1.0)
                             , m_jetQuality(-1.0) 
                             , m_goodness(-1) 
                             , m_emf(-1.0)
                             , m_time(-1.0)
                             , m_tileGap3Frac(-1.0)
                             , m_BCH_CORR_CELL(-1.0)
      {};
      
      Jet(const Particle &p,const BtagProperties& btagprop) : Particle(p), BtagProperties(btagprop)
                                                            , m_n90(-1.)
                                                            , m_hecFrac(-1.0)
                                                            , m_jetQuality(-1.0) 
                                                            , m_goodness(-1) 
                                                            , m_emf(-1.0)
                                                            , m_time(-1.0)
                                                            , m_tileGap3Frac(-1.0)
                                                            , m_BCH_CORR_CELL(-1.0) {};
  void print(void) const {
    std::cout << "  Jet" << std::endl;
    std::cout << "    EM energy     : " << m_emenergy << std::endl;
    std::cout << "    HAD energy    : " << m_hadenergy << std::endl;
    print_particle();
  }
  void EMEnergy(const double& e) {m_emenergy=e;}
  double EMEnergy(void) const {return m_emenergy;}
  void HADEnergy(const double& e) {m_hadenergy=e;}
  double HADEnergy(void) const {return m_hadenergy;}

      double n90(void) { return m_n90;}
      double hecFrac(void) { return m_hecFrac;}
      double jetQuality(void) const { return m_jetQuality;} 
      int goodness(void) const { return m_goodness;} 
      double emf(void) { return m_emf;}
      double time(void) { return m_time;}
      double tileGap3Frac(void) { return m_tileGap3Frac;}
      double BCH_CORR_CELL(void) { return m_BCH_CORR_CELL;}

      void n90(const double& val) {  m_n90=val;}
      void hecFrac(const double& val) {  m_hecFrac=val;}
      void jetQuality(const double& val) {  m_jetQuality=val;} 
      void goodness(const int& val) {  m_goodness=val;} 
      void emf(const double& val) {  m_emf=val;}
      void time(const double& val) {  m_time=val;}
      void tileGap3Frac(const double& val) {  m_tileGap3Frac=val;}
      void BCH_CORR_CELL(const double& val) {  m_BCH_CORR_CELL=val;}
      
      bool Bad(void) { return isBadJet(m_n90, m_hecFrac,m_jetQuality,m_emf,m_time);}
      bool Good(void) {return isGoodJet(m_n90, m_hecFrac,m_jetQuality,m_emf,m_time);}
      bool Ugly(void) { return isUglyJet(m_tileGap3Frac,m_BCH_CORR_CELL);}
      
      
private:
      double m_emenergy;
      double m_hadenergy;

      double m_n90;
      double m_hecFrac;
      double m_jetQuality; 
      int m_goodness; 
      double m_emf;
      double m_time;
      double m_tileGap3Frac;
      double m_BCH_CORR_CELL;
      //bool isGood,isBad,isUgly;

};

#endif  /* __JET_H */

