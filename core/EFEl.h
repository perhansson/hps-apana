/**************************************************************************
 **
 **   File:         EFEl.h
 **
 **   Description:  EF electorn object
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

#ifndef __EFELOBJ_H
#define __EFELOBJ_H

#include "Particle.h"
#include <iostream>


class EFElProperties {
   public:
      enum EFEL_CUTS {ET=(1<<0), ETA=(1<<1)};
      EFElProperties(void) {};

      void SetEtCone(double E) {m_etcone=E;};
      void SetEoverP(double r) {m_eoverp=r;};
      void SetTrkClsDeta(double d) {m_trkcls_deta=d;};
      void SetTrkClsDphi(double d) {m_trkcls_dphi=d;};

      double EtCone(void) const {return m_etcone;};
      double EoverP(void) const {return m_eoverp;};
      double TrkClsDeta(void) const {return m_trkcls_deta;};
      double TrkClsDphi(void) const {return m_trkcls_dphi;};

      void SetType(const std::string & s) {m_types.push_back(s);};
      bool HasType(const std::string & s) const {
         return std::find(m_types.begin(),m_types.end(),s)==m_types.end() ?
	   false : true;
      }

      void print_properties(void) const {
         std::cout << "    EtCone       : " << EtCone() << std::endl;
         std::cout << "    EoverP       : " << EoverP() << std::endl;
         std::cout << "    TrkCls_deta  : " << TrkClsDeta() << std::endl;
         std::cout << "    TrkCls_dphi  : " << TrkClsDphi() << std::endl;
         std::cout << " " << m_types.size() << " Types     : ";
         for(int i=0;i!=static_cast<int>(m_types.size());++i)
            std::cout << "  " << m_types[i];
         std::cout << std::endl;
      }
      
   private:

      double m_eoverp;
      double m_etcone;
      double m_trkcls_deta;
      double m_trkcls_dphi;
      std::vector<std::string> m_types;

};

class EFEl : public Particle, public EFElProperties {
   public:
      EFEl(void) {};
      EFEl(Particle &p, EFElProperties &e)
         : Particle(p), EFElProperties(e), index(-1) {};
      void print(void) const {
         std::cout << "  EFEl" << std::endl;
         std::cout << "    Index     : " << Index() << std::endl;
         print_particle();
         print_properties();
      }
      
      int Index(void) const {return index;}
      void Index(int i) {index=i;};

   private:
      int index;

};


#endif  /* __EFELOBJ_H */
