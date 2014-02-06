/**************************************************************************
 **
 **   File:         Topology_example
 **
 **   Description:  example analysis topology class
 ** 
 **   Author:       phansson@slac.stanford.edu
 **
 **   Created:      Feb 5, 2014
 **   Modified:     
 **                   
 **************************************************************************/ 

#ifndef __TOPOLOGY_EXAMPLE_H
#define __TOPOLOGY_EXAMPLE_H

#include "Topology_base.h"



class Topology_example : public Topology_base {
 public:
  Topology_example(AtlEvent *evt) : Topology_base(evt){};

  /* 
   * Override and implement the following functions
   */
  void cut(const TString & prefix); // called every event
  void book(const TString & prefix, const TString & suffix); // call after selection for each event
  void finalize(void); // plot or calcualte aggregated stuff

 private:
  /*
   * Put private functions only applicable to this analysis here
   * If they can be useful for others, put them in e.g. AtlEvent
   */
  void exampleFunction();

};

#endif  /* __TOPOLOGY_EXAMPLE_H */
