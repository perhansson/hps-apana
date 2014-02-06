/**************************************************************************
 **
 **   File:         Parton.h
 **
 **   Description:  Generic analysis parton from MC truth
 **
 **   Author:       P. Hansson , J. Sjolin
 **
 **   Created:      Sun Jul 29 16:20:04 CEST 2007
 **   Modified:
 **
 **************************************************************************/

#ifndef __PARTON_H
#define __PARTON_H

#include "Particle.h"

class Parton : public Particle {
   public:
      enum PARTON_CUTS {PT=(1<<0),ETA=(1<<1)};
      Parton(void) {Reset();};
      Parton(const Particle &p) : Particle(p) {Reset();};
      void pdgId(const int _pdgid) {m_pdgId=_pdgid;};
      void mother1(const int _pdgid) {m_motherid1=_pdgid;};
      void mother2(const int _pdgid) {m_motherid2=_pdgid;};
      void Reset(void) {
         m_pdgId=0; m_motherid1=0; m_motherid2=0;
      }
      int pdgId(void) const {return m_pdgId;};
      int mother1(void) const { return m_motherid1;};
      int mother2(void) const { return m_motherid2;};
      void print(void) const {
         std::cout << "  Parton" << std::endl;
         print_particle();
         std::cout << "    PdgId           : " << pdgId() << std::endl;
         std::cout << "    Mother1 PdgId   : " << mother1() << std::endl;
         std::cout << "    Mother2 PdgId   : " << mother2() << std::endl;
      }
   private:
      int m_pdgId,m_motherid1,m_motherid2;
};

#endif  /* __PARTON_H */
