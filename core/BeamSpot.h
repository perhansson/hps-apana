/**************************************************************************
 **
 **   File:         BeamSpot.h
 **
 **   Description:  Generic analysis BeamSpot
 **
 **   Author:       P. Hansson 
 **
 **   Created:      Sun Jul 29 16:20:04 CEST 2007
 **   Modified:
 **
 **************************************************************************/

#ifndef __BEAMSPOT_H
#define __BEAMSPOT_H


class BeamSpot {
   public:
      //enum BEAMSPOT_CUTS {PT=(1<<0),ETA=(1<<1)};
      BeamSpot(void) {Reset();};
      BeamSpot(const double& x, const double& y, const double& z) :
         m_x(x),m_y(y),m_z(z), m_sigx(-1.), m_sigy(-1.), m_sigz(-1.) {};

      void Set(const double& x, const double& y, const double& z,
          const double& sigx, const double& sigy, const double& sigz) {
         m_x=x; m_y=y; m_z=z; m_sigx=sigx; m_sigy=sigy; m_sigz=sigz;
      };
      
      void x(const double& value) { m_x=value;};
      void y(const double& value) { m_y=value;};
      void z(const double& value) { m_z=value;};
      void sigx(const double& value) { m_sigx=value;};
      void sigy(const double& value) { m_sigy=value;};
      void sigz(const double& value) { m_sigz=value;};
      double x(void) const {return m_x;};
      double y(void) const {return m_y;};
      double z(void) const {return m_z;};
      double sigx(void) const {return m_sigx;};
      double sigy(void) const {return m_sigy;};
      double sigz(void) const {return m_sigz;};
      void Reset(void) {
         m_x=0;
         m_y=0;
         m_z=0;
         m_sigx=0;
         m_sigy=0;
         m_sigz=0;
      }
      void print(void) const {
         std::cout << "  BeamSpot" << std::endl;
         std::cout << "    x,y,z           : " << x() << "," << y() << "," << z() << std::endl;
         std::cout << "sigma x,y,z         : " << sigx() << "," << sigy() << "," << sigz() << std::endl;
      }
   private:
      double m_x,m_y,m_z,m_sigx,m_sigy,m_sigz;
};


class Vertex {
   public:
      enum VERTEX_CUTS {N=(1<<0)};
      Vertex(void) {Reset();};
      Vertex(const double& x, const double& y, const double& z,const int& n) :
         m_x(x),m_y(y),m_z(z), m_n(n) {};
      
      void x(const double& value) { m_x=value;};
      void y(const double& value) { m_y=value;};
      void z(const double& value) { m_z=value;};
      void n(const int& value) { m_n=value;};
      double x(void) const {return m_x;};
      double y(void) const {return m_y;};
      double z(void) const {return m_z;};
      int n(void) const {return m_n;};
      void Reset(void) {
         m_x=0;
         m_y=0;
         m_z=0;
         m_n=-1;
      }
      void print(void) const {
         std::cout << "  Offline Vertex" << std::endl;
         std::cout << "    x,y,z           : " << x() << "," << y() << "," << z() << std::endl;
         std::cout << "    nTrks           : " << n() << std::endl;
      }
   private:
      double m_x,m_y,m_z;
      int m_n;
};


class Vertices : public std::vector<Vertex> {
   public:
      //void sort()
   private:
      

};



#endif  /* __BEAMSPOT_H */
