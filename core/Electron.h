/**************************************************************************
 **   File:         Electron.h
 **   Description:  Generic analysis electron
 **
 **   Author:       J. Sjolin
 **
 **   Created:      Mon Sep 19 16:20:04 CEST 2005
 **************************************************************************/

#ifndef __ELECTRON_H
#define __ELECTRON_H

#include "Particle.h"
#include <iostream>

class Electron : public Particle {
 public:
  Electron(void) {Reset();}
  Electron(const Particle &p) : Particle(p) {Reset();}
  void Reset(void) {
    author(1);
    m_trkiso=0; m_isem=0; m_isem_simple=0;
    m_trkpt=0; m_idbits=-1; m_istight=true;
    iL1EmObj=-1; iL2ElObj=-1; iEFElObj=-1;
  };
  void TrkPt(double trkpt) {m_trkpt=trkpt;};
  double TrkPt(void) const {return m_trkpt;};
  void TrkIso(double trkiso) {m_trkiso=trkiso;};
  double TrkIso(void) const {return m_trkiso;};
  void IsEM(int isem, int tightem) {
    m_isem=isem;
    // egammaPID::ElectronTightNoIsolation==92225523 for v14
    m_istight=!(tightem>1000000 ? isem&92225523 : isem&65535);
  };
  void IsEMsimple(int isem) {
    m_isem_simple=isem;
  };
  
  int IsEM(void) const {return m_isem;};
  int IsEMsimple(void) const {return m_isem_simple;};
  bool IsTight(void) const {return m_istight;};
  void IDbits(int bits) {m_idbits=bits;};
  int IDbits(void) const {return m_idbits;};
  int L1EmObj(void) const {return iL1EmObj;};
  void L1EmObj(int i) {iL1EmObj=i;};
  int L2ElObj(void) const {return iL2ElObj;};
  void L2ElObj(int i) {iL2ElObj=i;};
  int EFElObj(void) const {return iEFElObj;};
  void EFElObj(int i) {iEFElObj=i;};
  void print(void) const {
    std::cout << "  Electron" << std::endl;
    print_particle();
    std::cout << "    Author : " << author() << std::endl;
    std::cout << "    Trk Pt : " << TrkPt() << std::endl;
    std::cout << "    IsEMsimple   : " << IsEMsimple() << std::endl;
    std::cout << "    IsEM   : " << IsEM() << std::endl;
    std::cout << "    Iso   : " << Iso() << std::endl;
    std::cout << "    TrkIso   : " << TrkIso() << std::endl;
    std::cout << "    iL1EmObj : " << L1EmObj() << std::endl;
    std::cout << "    iL2ElObj : " << L2ElObj() << std::endl;
    std::cout << "    iEFElObj : " << EFElObj() << std::endl;
  }
  enum ELECTRON_CUTS {
    EG_ET=(1<<0),EG_ETA=(1<<1),TRK_PT=(1<<2),ISEM_LOOSE=(1<<3),
    ISEM_MEDIUM=(1<<4),ISEM_TIGHT=(1<<5),ISO=(1<<6),TRKISO=(1<<7),
    TRK=(1<<8),EG_ETA2=(1<<9),AUTHOR=(1<<10),ISEM_SIMPLE=(1<<11)
  };
  
 private:
  double m_trkiso;
  int m_isem;
  int m_isem_simple;
  double m_trkpt;
  int m_idbits;
  bool m_istight;
  int iL1EmObj;
  int iL2ElObj;
  int iEFElObj;
};

#endif  /* __ELECTRON_H */
