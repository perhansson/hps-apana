/**************************************************************************
 **
 **   File:         Cell.h
 **
 **   Description:  Generic analysis calorimeter cell
 **
 **   Author:       J. Sjolin
 **
 **   Created:      Wed Nov 19 11:17:08 CET 2008
 **   Modified:
 **
 **************************************************************************/

#ifndef __CELL_H
#define __CELL_H

#include "Particle.h"

class Cell : public Particle {
public:
  enum CELL_CUTS {ET=(1<<0),ETA=(1<<1)};
  Cell(void) {Reset();};
  Cell(const Particle &p) : Particle(p) {Reset();};
  void d(const double _d) {m_d=_d;};
  void t(const double _t) {m_t=_t;};
  void x(const double _x) {m_x=_x;};
  void y(const double _y) {m_y=_y;};
  void z(const double _z) {m_z=_z;};
  void Reset(void) {
    m_d=0; m_t=0; m_x=0; m_y=0; m_z=0;
  }
  double d(void) const {return m_d;};
  double t(void) const {return m_t;};
  double x(void) const {return m_x;};
  double y(void) const {return m_y;};
  double z(void) const {return m_z;};
  void print(void) const {
    std::cout << "  Cell" << std::endl;
    print_particle();
    std::cout << "    d   = " << d() << std::endl;
    std::cout << "    t   = " << t() << std::endl;
    std::cout << "    x   = " << x() << std::endl;
    std::cout << "    y   = " << y() << std::endl;
    std::cout << "    x   = " << z() << std::endl;
  }
private:
  double m_d,m_t,m_x,m_y,m_z;
};

#endif  /* __CELL_H */
