/**************************************************************************
 **
 **   File:         L2El.h
 **
 **   Description:  L2 electron object
 **
 **
 **   Author:       P. Hansson
 **
 **   Created:      Mon Sep 19 16:20:04 CEST 2005
 **   Modified:
 **
 **
 **
 **************************************************************************/

#ifndef __L2ELOBJ_H
#define __L2ELOBJ_H

#include "Particle.h"
#include <iostream>


class L2ElProperties {
   public:
      enum L2EL_CUTS {ET=(1<<0), ETA=(1<<1)};
      L2ElProperties(void) {};

      
      void CL_Et(double Et) {m_CL_Et=Et;};
      double CL_Et(void) const {return m_CL_Et;};
      void CL_Eta(double Eta) {m_CL_Eta=Eta;};
      double CL_Eta(void) const {return m_CL_Eta;};
      void CL_Phi(double Phi) {m_CL_Phi=Phi;};
      double CL_Phi(void) const {return m_CL_Phi;};
      void CL_ehad(double e) {m_CL_ehad=e;};
      double CL_ehad(void) const {return m_CL_ehad;};
      void Rcore(double e) {m_Rcore=e;};
      double Rcore(void) const {return m_Rcore;};
      void Eratio(double e) {m_Eratio=e;};
      double Eratio(void) const {return m_Eratio;};
      void ID_p_T(double pt) {m_ID_p_T=pt;};
      double ID_p_T(void) const {return m_ID_p_T;};
      void ID_eta(double eta) {m_ID_eta=eta;};
      double ID_eta(void) const {return m_ID_eta;};
      void ID_phi0(double phi0) {m_ID_phi0=phi0;};
      double ID_phi0(void) const {return m_ID_phi0;};
      void ID_Ep(double ep) {m_ID_Ep=ep;};
      double ID_Ep(void) const {return m_ID_Ep;};
      void CL_ID_Deta(double deta) {m_CL_ID_Deta=deta;};
      double CL_ID_Deta(void) const {return m_CL_ID_Deta;};
      void CL_ID_Dphi(double dphi) {m_CL_ID_Dphi=dphi;};
      double CL_ID_Dphi(void) const {return m_CL_ID_Dphi;};

      void SetType(const std::string & s) {m_types.push_back(s);};
      bool HasType(const std::string & s) const {
         return std::find(m_types.begin(),m_types.end(),s)==m_types.end() ?
	   false : true;
      }

      void print_properties(void) const {
         std::cout << "    EmClusEt     : " << CL_Et() << std::endl;
         std::cout << "    EmClusEta    : " <<CL_Eta() << std::endl;
         std::cout << "    EmClusPhi    : " << CL_Phi() << std::endl;
         std::cout << "    Em ehad      : " << CL_ehad() << std::endl;
         std::cout << "    Em rcore      : " << Rcore() << std::endl;
         std::cout << "    Em eratio    : " << Eratio() << std::endl;
         std::cout << "    Em ID pt     : " << ID_p_T() << std::endl;
         std::cout << "    Em ID eta    : " << ID_eta() << std::endl;
         std::cout << "    Em ID phi0   : " << ID_phi0() << std::endl;
         std::cout << "    Em ID Ep     : " << ID_Ep() << std::endl;
         std::cout << "    Em CL ID Deta: " << CL_ID_Deta() << std::endl;
         std::cout << "    Em CL ID Dphi: " << CL_ID_Dphi() << std::endl;
         std::cout << " " << m_types.size() << " Types     : ";
         for(int i=0;i!=static_cast<int>(m_types.size());++i)
            std::cout << "  " << m_types[i];
         std::cout << std::endl;

      }
      
   private:

      double m_CL_Eta;
      double m_CL_Phi;
      double m_CL_Et;
      double m_CL_ehad;
      double m_Rcore;
      double m_Eratio;
      double m_ID_p_T;
      double m_ID_eta;
      double m_ID_phi0;
      double m_ID_Ep;
      double m_CL_ID_Deta;
      double m_CL_ID_Dphi;
      std::vector<std::string> m_types;

};

class L2El : public Particle, public L2ElProperties {
   public:
      L2El(void) {};
      L2El(Particle &p, L2ElProperties &e)
         : Particle(p), L2ElProperties(e),index(-1) {};
      void print(void) const {
         std::cout << "  L2El" << std::endl;
         std::cout << "    Index     : " << Index() << std::endl;
         print_particle();
         print_properties();
      }

      int Index(void) const {return index;}
      void Index(int i) {index=i;};

   private:
      int index;

};


#endif  /* __L2ELOBJ_H */
