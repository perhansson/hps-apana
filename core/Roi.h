/**************************************************************************
 **
 **   File:         Roi.h
 **
 **   Description:  Generic analysis region of interest
 **
 **   Author:       J. Sjolin
 **
 **   Created:      fre maj 18 17:29:57 CEST 2007
 **   Modified:
 **
 **************************************************************************/

#ifndef __ROI_H
#define __ROI_H

#include <vector>
#include <map>
#include "Particle.h"
#include "TString.h"
#include "TLorentzVector.h"

class Roi {
 public:
  Roi(void) {};
  Roi(const float eta, const float phi, const float pt, const TString & name) :
    m_name(name) {
    m_p.SetPtEtaPhiM(pt,eta,phi,0.);
  };
  float eta(void) const {return m_p.Eta();};
  float phi(void) const {return m_p.Phi();};
  float pt(void) const {return m_p.Pt();};
  const TLorentzVector & p(void) const {return m_p;};
  const TString & name(void) const {return m_name;};
  void print(void) const {
    std::cout << "  Roi" << std::endl;
    std::cout << "    Eta     = " << eta() << std::endl;
    std::cout << "    Phi     = " << phi() << std::endl;
    std::cout << "    Pt      = " << pt() << std::endl;
    std::cout << "    Name    = " << name() << std::endl;
  }
 private:
  TLorentzVector m_p;
  TString m_name;
};

typedef std::multimap<TString,Roi> Rois_dict;
typedef std::vector<Roi> Rois;

#endif  /* __ROI_H */
