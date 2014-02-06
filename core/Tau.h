/**************************************************************************
 **
 **   File:         Tau.h
 **
 **   Description:  Generic analysis tau
 **
 **   Author:       J. Sjolin
 **
 **   Created:      Mon Sep 19 16:20:04 CEST 2005
 **   Modified:
 **
 **************************************************************************/

#ifndef __TAU_H
#define __TAU_H

#include "Particle.h"

class Tau : public Particle {
 public:
  enum TAU_CUTS {ET=(1<<0), ETA1=(1<<1), ETA2=(1<<2), LL=(1<<3), ISO=(1<<4),
		 EMRAD=(1<<5),EMF=(1<<6)};
  Tau(void) {};
  Tau(const Particle &p) : Particle(p), m_loglikelihood(0),
    m_emf(0), m_iso(0), m_emradius(0) {};
  void loglikelihood(const float ll) {m_loglikelihood=ll;};
  float loglikelihood(void) const {return m_loglikelihood;};
  void emf(const float emf) {m_emf=emf;};
  float emf(void) const {return m_emf;};
  void iso(const float iso) {m_iso=iso;};
  float iso(void) const {return m_iso;};
  void emradius(const float emradius) {m_emradius=emradius;};
  float emradius(void) const {return m_emradius;};
  void print(void) const {
    std::cout << "  Tau" << std::endl;
    print_particle();
    std::cout << "      LL    = " << loglikelihood() << std::endl;
    std::cout << "      EMF   = " << emf() << std::endl;
    std::cout << "      EMRAD = " << emradius() << std::endl;
    std::cout << "      ISO   = " << iso() << std::endl;
  }
private:
  float m_loglikelihood, m_emf, m_iso, m_emradius;
};

#endif  /* __TAU_H */
