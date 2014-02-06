/**************************************************************************
 **
 **   File:         L1Jet.h
 **
 **   Description:  L1 Jet 
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

#ifndef __L1JET_H
#define __L1JET_H

#include "Particle.h"
#include <iostream>
#include <string>
#include <sstream>


class L1JetProperties {
 public:
  enum L1JET_CUTS {ET=(1<<0)};
 L1JetProperties(void) :
  m_Thresh(-1.0),m_RoIWord(0) {};
  void SetThr(double thr) {m_Thresh=thr;};
  void SetPassedThr(const double& thr, const std::string& name) {
     m_passedThresholds[name] = thr;
  }
      std::vector<double> GetVecPassedThr(void) const { 
         std::vector<double> thrs;
         for(std::map<std::string,double>::const_iterator i=m_passedThresholds.begin();i!=m_passedThresholds.end();++i) { thrs.push_back(i->second); }
         return thrs;
      };
      std::vector<std::string> GetVecPassedThrNames(void) const { 
         std::vector<std::string> thrs;
         for(std::map<std::string,double>::const_iterator i=m_passedThresholds.begin();i!=m_passedThresholds.end();++i) { thrs.push_back(i->first); }
         return thrs;
      };
      
      bool PassedThr(const std::string& name) const { 
         
         for(std::map<std::string,double>::const_iterator i=m_passedThresholds.begin();i!=m_passedThresholds.end();++i) { 
            if(i->first == name) return true;
         }
         return false;
      };
  double GetLowestThr(void) const {
    double minthr = -1.0;
    std::map<std::string, double>::const_iterator i  =  m_passedThresholds.begin();
    std::map<std::string, double>::const_iterator iE = m_passedThresholds.end();
    for(;i!=iE;++i) {
      if(minthr<0.) { minthr = i->second; }
      else {      
	if(i->second<minthr) { minthr=i->second; }
      }
    }
    return minthr;
  };
  void SetRoIWord(unsigned int word) {m_RoIWord=word;};
  double Thr(void) const {return m_Thresh;};      
  double RoIWord(void) const {return m_RoIWord;};      
  void print_properties(void) const {
    std::cout << "    Thresh    : " << Thr() << std::endl;
    std::cout << "    RoIWord   : " << RoIWord() << std::endl;
    for(map<string, double>::const_iterator i = m_passedThresholds.begin(); i!=m_passedThresholds.end();++i) {
       std::cout << "    " << i->first << ": " << i->second << std::endl;
    }
  }      
 private:
  double m_Thresh;
  double m_RoIWord;
  std::map<std::string, double> m_passedThresholds;
};

class L1Jet : public Particle, public L1JetProperties {
 public:
  L1Jet(void) {};
 L1Jet(const Particle &p, const L1JetProperties &e)
   : Particle(p), L1JetProperties(e),index(-1) {};
  void print(void) const {
    std::cout << "  L1Jet" << std::endl;
    std::cout << "    Index     : " << Index() << std::endl;
    print_particle();
    print_properties();
  }
  int Index(void) const {return index;}
  void Index(int i) {index=i;};
  
 private:
  int index;
};


#endif  /* __L1JET_H */
