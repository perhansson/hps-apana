/**************************************************************************
 **
 **   File:         Muon.h
 **
 **   Description:  Generic analysis muon
 **
 **   Author:       J. Sjolin
 **
 **   Created:      Mon Sep 19 16:20:04 CEST 2005
 **   Modified:
 **
 **************************************************************************/

#ifndef __MUON_H
#define __MUON_H

#include "Particle.h"

class Muon : public Particle {
public:
  enum MUON_CUTS {PT=(1<<0),ETA=(1<<1),A0=(1<<2),Z=(1<<3),CHI2=(1<<4),
		  ISO=(1<<5),TRKISO=(1<<6),FITCHI2=(1<<7),
		  MATCHCHI2=(1<<8),ISO_LOOSE=(1<<9),
		  COMB=(1<<10),AUTHOR=(1<<11)};
  Muon(void) {Reset();};
  Muon(const Particle &p) : Particle(p) {Reset();};
  void a0(const double _a0) {m_a0=_a0;};
  void z(const double _z) {m_z=_z;};
  void Chi2DoverF(const double chi2) {m_chi2doverf=chi2;};
  void FitChi2(const double chi2) {m_fitchi2=chi2;};
  void MatchChi2(const double chi2) {m_matchchi2=chi2;};
  void ECalo(const double ecalo) {m_ecalo=ecalo;};
  void TrkIso(const double trkiso) {m_trkiso=trkiso;};
  void isComb(const bool iscomb) {m_iscomb=iscomb;};
  void Author(const int author) {m_author=author;};
  void IDbits(const int bits) {m_idbits=bits;};
  void L1Pt(const double pt) {m_l1_pt=pt;};
  void Reset(void) {
    m_a0=0; m_z=0; m_chi2doverf=1; m_fitchi2=0; m_matchchi2=0;
    m_iso=0; m_trkiso=0; m_iscomb=true; m_author=6; m_idbits=-1;
    m_l1_pt=-1; m_ecalo=0, m_isoverlapremoved=false;
  }
  double a0(void) const {return m_a0;};
  double z(void) const {return m_z;};
  double Chi2DoverF(void) const {return m_chi2doverf;};
  double FitChi2(void) const {return m_fitchi2;};
  double MatchChi2(void) const {return m_matchchi2;};
  double ECalo(void) const {return m_ecalo;};  
  double TrkIso(void) const {return m_trkiso;};
  double isComb(void) const {return m_iscomb;};
  double Author(void) const {return m_author;};
  int IDbits(void) const {return m_idbits;};
  double L1Pt(void) const {return m_l1_pt;};
  void isOverlapRemoved(const bool isoverlapremoved) {
    m_isoverlapremoved=isoverlapremoved;};
  double isOverlapRemoved(void) const {return m_isoverlapremoved;};
  void print(void) const {
    std::cout << "  Muon" << std::endl;
    print_particle();
    std::cout << "    Chi2DoverF= " << Chi2DoverF() << std::endl;
    std::cout << "    FitChi2   = " << FitChi2() << std::endl;
    std::cout << "    MatchChi2 = " << MatchChi2() << std::endl;
    std::cout << "    ECalo     = " << ECalo() << std::endl;
    std::cout << "    TrkIso    = " << TrkIso() << std::endl;
    std::cout << "    isComb    = " << isComb() << std::endl;
    std::cout << "    L1 pt     = " << L1Pt() << std::endl;
  }
private:
  double m_a0,m_z,m_chi2doverf,m_fitchi2,m_matchchi2,m_iso,m_trkiso,
    m_l1_pt,m_ecalo;
  int m_author,m_idbits;
  bool m_iscomb, m_isoverlapremoved;
};

#endif  /* __MUON_H */
