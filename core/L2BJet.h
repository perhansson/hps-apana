/**************************************************************************
 **
 **   File:         L2BJet.h
 **
 **   Description:  L2 b-Jet 
 **
 **
 **   Author:       P. Hansson
 **
 **   Created:      
 **   Modified:
 **
 **
 **
 **************************************************************************/

#ifndef __L2BJET_H
#define __L2BJET_H

#include "Particle.h"
#include <iostream>


class L2BJetProperties {
   public:
      enum L2BJET_CUTS {ET=(1<<0)};
      L2BJetProperties(void) :
         m_IP1D(-1.),m_IP2D(-1.),m_IP3D(-1.),m_Chi2(-1.),m_SV(-1.),m_Mvtx(-1.),m_Evtx(-1.),m_Nvtx(-1.),m_zvtx(0.),m_chain("") {};
      void SetIP1D(double v) {m_IP1D=v;};
      void SetIP2D(double v) {m_IP2D=v;};
      void SetIP3D(double v) {m_IP3D=v;};
      void SetChi2(double v) {m_Chi2=v;};
      void SetSV(double v) {m_SV=v;};
      void SetMvtx(double v) {m_Mvtx=v;};
      void SetEvtx(double v) {m_Evtx=v;};
      void SetNvtx(double v) {m_Nvtx=v;};
      void SetZvtx(double v) {m_zvtx=v;};
      void SetChain(const std::string& chain) {m_chain=chain;};
      
      double IP1D(void) const {return m_IP1D;};
      double IP2D(void) const {return m_IP2D;};
      double IP3D(void) const {return m_IP3D;};
      double Chi2(void) const {return m_Chi2;};
      double SV(void) const  {return m_SV;};
      double Mvtx(void) const {return m_Mvtx;};
      double Evtx(void) const {return m_Evtx;};
      double Nvtx(void) const {return m_Nvtx;};
      double Zvtx(void) const {return m_zvtx;};
      std::string Chain(void) const {return m_chain;};
      
      bool IsChain(const std::string& chain) {return m_chain==chain? true : false;}      
      bool IsTagged(std::string type,double cut) const {
         if(type=="IP2D") { return IP2D()>cut; }
         else if(type=="IP3D") { return IP3D()>cut; }
         else if(type=="CHI2") { return Chi2()>cut; }
         else { 
            std::cout << "This type \""  << type
                      << "\" of L2 B tag is not implemented"
                      << std::endl; exit(-1); 
         }
      }
      
      void print_properties(void) const {
         std::cout << "    IP1D    : " << IP1D() << std::endl;
         std::cout << "    IP2D    : " << IP2D() << std::endl;
         std::cout << "    IP3D    : " << IP3D() << std::endl;
         std::cout << "    Chi2    : " << Chi2() << std::endl;
         std::cout << "    Chain   : " << Chain() << std::endl;;
         //std::cout << "    Comb    : " << Comb() << std::endl;
      }      
   private:
      double m_IP1D;
      double m_IP2D;
      double m_IP3D;
      double m_Chi2;
      double m_SV;
      double m_Mvtx;
      double m_Evtx;
      double m_Nvtx;
      double m_zvtx;
      std::string m_chain;
};

class L2BJet : public Particle, public L2BJetProperties {
   public:
      L2BJet(void) {};
      L2BJet(const Particle &p, const L2BJetProperties &e)
         : Particle(p), L2BJetProperties(e),index(-1) {};
      void print(void) const {
         std::cout << "  L2BJet" << std::endl;
         std::cout << "    Index     : " << Index() << std::endl;
         print_particle();
         print_properties();
      }
      int Index(void) const {return index;}
      void Index(int i) {index=i;};
      
   private:
      int index;
};



#endif  /* __L2BJET_H */
