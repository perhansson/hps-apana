/**************************************************************************
 **
 **   File:         Particle.h
 **
 **   Description:  Generic analysis Particle
 **
 **   Author:       J. Sjolin
 **
 **   Created:      Mon Sep 19 16:20:04 CEST 2005
 **   Modified:
 **
 **************************************************************************/

#ifndef __PARTICLE_H
#define __PARTICLE_H

#include <iostream>
#include <algorithm>
#include <vector>
#include "TLorentzVector.h"

class Particle {
 public:
  virtual ~Particle() {};
      Particle(void) : m_author(0), m_charge(0), m_iso(0), m_d0(0), m_d0err(0),
    m_trthits(0), m_trtht(0), m_origin(-1), m_truth_match(false) {
  };
  TLorentzVector p;
  TVector3 x;
  virtual void author(const int author) {m_author=author;};
  virtual int author(void) const {return m_author;};
  virtual void origin(const int origin) {m_origin=origin;};
  virtual int origin(void) const {return m_origin;};
  virtual void truth_match(const bool truth_match){m_truth_match=truth_match;};
  virtual bool truth_match(void) const {return m_truth_match;};
  virtual void Charge(const double d) {
    m_charge=(int)(d+(d>=0.0 ? 0.5 : -0.5));
  };
  virtual int Charge(void) const {return m_charge;};
  virtual void Iso(double iso) {m_iso=iso;};
  virtual double Iso(void) const {return m_iso;};
  virtual void d0(const float d0) {m_d0=d0;};
  virtual float d0(void) const {return m_d0;};
  virtual void d0err(const float d0err) {m_d0err=d0err;};
  virtual float d0err(void) const {return m_d0err;};
  virtual void trthits(const int trthits) {m_trthits=trthits;};
  virtual int trthits(void) const {return m_trthits;};
  virtual void trtht(const int trtht) {m_trtht=trtht;};
  virtual int trtht(void) const {return m_trtht;};
  virtual void print(void) const {};
  virtual void print_particle(void) const {
    std::cout << "    Et        = " << p.Et() << std::endl;
    std::cout << "    Pt        = " << p.Pt() << std::endl;
    std::cout << "    Eta       = " << p.Eta() << std::endl;
    std::cout << "    Phi       = " << p.Phi() << std::endl;
    std::cout << "    Charge    = " << Charge() << std::endl;
    std::cout << "    Truth mat = " << truth_match() << std::endl;
    std::cout << "    Iso       = " << Iso() << std::endl;
    std::cout << "    Px        = " << p.Px() << std::endl;
    std::cout << "    Py        = " << p.Py() << std::endl;
    std::cout << "    Pz        = " << p.Pz() << std::endl;
    std::cout << "    d0        = " << d0() << std::endl;
    std::cout << "    d0err     = " << d0err() << std::endl;
    std::cout << "    trthits   = " << trthits() << std::endl;
    std::cout << "    trtht     = " << trtht() << std::endl;
//     std::cout << "    X      : " << x.X() << std::endl;
//     std::cout << "    Y      : " << x.Y() << std::endl;
//     std::cout << "    Z      : " << x.Z() << std::endl;
  }
 private:
  int m_author, m_charge;
  float m_iso, m_d0, m_d0err;
  int m_trthits, m_trtht, m_origin;
  bool m_truth_match;
};

template <class T>
static bool order_pt(const T &x, const T &y) {
  // return (x.p.Pt() > y.p.Pt());
  return (x.p.Et() > y.p.Et());  // Only important for jets!
};
template <class T>
static bool order_hmva(const T &x, const T &y) {
  return (x.toptag.htmva() > y.toptag.htmva());  
};
template <class T>
static bool porder_hmva(const T &x, const T &y) {
  return (x->toptag.htmva() > y->toptag.htmva());  
};
template <class T>
class Particles : public std::vector<T> {
 public:
  void sort_pt(void) {
    std::sort(this->begin(), this->end(), order_pt<T>);
  }
  void sort_hmva(void) {
    std::sort(this->begin(), this->end(), order_hmva<T>);
  }
 private:
};

template <class T>
static bool porder_pt(const T x, const T y) {
  //return (x->p.Pt() > y->p.Pt());
  return (x->p.Et() > y->p.Et()); // Only important for jets!
};

template <class T>
class Particles_p : public std::vector<T> {
 public:
  void sort_pt(void) {
    std::sort(this->begin(), this->end(), porder_pt<T>);
  }
  void sort_hmva(void) {
    std::sort(this->begin(), this->end(), porder_hmva<T>);
  }
 private:
};


#endif  /* __PARTICLE_H */
