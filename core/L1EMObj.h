/**************************************************************************
 **
 **   File:         L1EMObj.h
 **
 **   Description:  L1 electron
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

#ifndef __L1EMOBJ_H
#define __L1EMOBJ_H

#include "Particle.h"
#include <iostream>


class L1EMObjProperties {
   public:
      enum L1EM_CUTS {ET=(1<<0), EMISOL=(1<<1), HDISOL=(1<<2), HDCORE=(1<<3)};
      L1EMObjProperties(void) :
         m_EmClus(-1.0),m_EmIsol(-1.0),m_HdIsol(-1.0),m_EmCore(-1.0),m_HdCore(-1.0),m_DeltaR(-1.0) {};
      void SetEmClus(double clus) {m_EmClus=clus;};
      void SetEmIso(double iso) {m_EmIsol=iso;};
      void SetHdIso(double iso) {m_HdIsol=iso;};
      void SetEmCore(double core) {m_EmCore=core;};
      void SetHdCore(double core) {m_HdCore=core;};
      void SetDeltaR(double dr) {m_DeltaR=dr;};
      void SetType(const std::string & s) {m_types.push_back(s);};
      double EmIso(void) const {return m_EmIsol;};
      double HdIso(void) const {return m_HdIsol;};
      double EmCore(void) const {return m_EmCore;};
      double HdCore(void) const {return m_HdCore;};
      double EmClus(void) const {return m_EmClus;};
      double DeltaR(void) const {return m_DeltaR;};
      bool HasType(const std::string & s) const {
	return std::find(m_types.begin(),m_types.end(),s)==m_types.end() ?
	  false : true;
      }
      void print_properties(void) const {
         std::cout << "    EmIso     : " << EmIso() << std::endl;
         std::cout << "    HdIso     : " << HdIso() << std::endl;
         std::cout << "    DeltaR    : " << DeltaR() << std::endl;
         std::cout << "    EmCore    : " << EmCore() << std::endl;
         std::cout << "    HdCore    : " << HdCore() << std::endl;
         std::cout << "    EmClus    : " << EmClus() << std::endl;
         std::cout << " " << m_types.size() << " Types     : ";
         for(int i=0;i!=static_cast<int>(m_types.size());++i)
            std::cout << "  " << m_types[i];
         std::cout << std::endl;
      }
      
   private:
      double m_EmClus;
      double m_EmIsol;
      double m_HdIsol;
      double m_EmCore;
      double m_HdCore;
      double m_DeltaR;
      std::vector<std::string> m_types;
      
};

class L1EMObj : public Particle, public L1EMObjProperties {
   public:
      L1EMObj(void) {};
      L1EMObj(const Particle &p, const L1EMObjProperties &e)
         : Particle(p), L1EMObjProperties(e),index(-1) {};
      void print(void) const {
         std::cout << "  L1EMObj" << std::endl;
         std::cout << "    Index     : " << Index() << std::endl;
         print_particle();
         print_properties();
      }
      int Index(void) const {return index;}
      void Index(int i) {index=i;};
      
   private:
      int index;
};


#endif  /* __L1EMOBJ_H */
