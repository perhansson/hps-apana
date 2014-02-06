/**************************************************************************
 **
 **   File:         Topology_event
 **
 **   Description:  Main event topology class
 ** 
 **   Author:       jorgen.sjolin@physto.se
 **
 **   Created:      Mon Apr 23 15:47:26 CEST 2007
 **   Modified:     
 **                   
 **************************************************************************/ 

#ifndef __TOPOLOGY_EVENT_H
#define __TOPOLOGY_EVENT_H

#include "Topology_base.h"
#include <fstream>
#include <sstream>

using namespace std;

class Topology_event : public Topology_base {
 public:
  Topology_event(AtlEvent *evt) : Topology_base(evt) {
    m_topo[""]=dynamic_cast<Topology_base*>(this);
  };
  void cut(const TString & prefix);
  void book(const TString & prefix, const TString & suffix);
  void add_mc_sample(const string & mc_sample,const string & mc_set);
  void add_src_list(const TString & src_list);
  void loop_src(EventSrc *src, int maxev);
  void finalize(void);

private:
  std::list<TString> m_files;
};

#endif  /* __TOPOLOGY_EVENT_H */
