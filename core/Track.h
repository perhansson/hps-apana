/**************************************************************************
 **
 **   File:         Track.h
 **
 **   Description:  Generic analysis Track
 **
 **   Author:       J. Sjolin
 **
 **   Created:      Mon Sep 19 16:20:04 CEST 2005
 **   Modified:
 **
 **************************************************************************/

#ifndef __TRACK_H
#define __TRACK_H

#include "Particle.h"

class TrackProperties {
 public:
      TrackProperties(void) : 
         m_chi2(-1.)
         ,m_z0(9999.9)
         ,m_z0err(9999.9)
         ,m_sihits(-1)
         ,m_pixhits(-1)
         ,m_scthits(-1)
         ,m_trthits(-1)
      {};
   TrackProperties(const TrackProperties& prop) : 
     m_chi2(prop.chi2())
    ,m_z0(prop.z0())
    ,m_z0err(prop.z0err())
    ,m_sihits(prop.siHits())
    ,m_pixhits(prop.pixHits())
    ,m_scthits(prop.sctHits())
    ,m_trthits(prop.trtHits())
      {};
      
      void z0(const double& val) {m_z0=val;};
      void z0err(const double& val) {m_z0err=val;};
      void chi2(const double& val)  {m_chi2=val;};
      double z0(void) const {return m_z0;};
      double z0err(void) const {return m_z0err;};
      double chi2(void) const {return m_chi2;};
      void siHits(const int& val) {m_sihits=val;}
      void pixHits(const int& val) {m_pixhits=val;}
      void sctHits(const int& val) {m_scthits=val;}
      void trtHits(const int& val) {m_trthits=val;}
      int siHits(void) const {return m_sihits;}
      int pixHits(void) const {return m_pixhits;}
      int sctHits(void) const {return m_scthits;}
      int trtHits(void) const {return m_trthits;}
      

      void print_prop(void) const {
         std::cout << "  chi2     : " << chi2() << std::endl;
         std::cout << "  z0       : " << z0() << std::endl;
         std::cout << "  z0err    : " << z0err() << std::endl;
         std::cout << "  siHits  : " << siHits() << std::endl;
         std::cout << "  pixHits  : " << pixHits() << std::endl;
         std::cout << "  sctHits  : " << sctHits() << std::endl;
         std::cout << "  trtHits  : " << trtHits() << std::endl;
      };
      
      


      
   private:
      double m_chi2;
      double m_z0;
      double m_z0err;
      int m_sihits,m_pixhits,m_scthits,m_trthits;
};


class Track : public Particle , public TrackProperties {
   public:
      enum TRACK_CUTS {P=(1<<0)};
      Track(void) {};
      Track(const Track &trk) : Particle(trk), TrackProperties(trk) {};
      Track(const Particle &p) : Particle(p)  {};
      Track(const Particle &p,const TrackProperties& prop) : 
         Particle(p),TrackProperties(prop) {};
      void print(void) const {
         std::cout << "  Track" << std::endl;
         print_prop();
         print_particle();
      }
      
private:
};

#endif  /* __TRACK_H */
