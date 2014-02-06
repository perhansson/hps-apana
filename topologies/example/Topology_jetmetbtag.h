/**************************************************************************
 **
 **   File:         Topology_jetmetbtag
 **
 **   Description:  analysis topology class
 ** 
 **   Author:       phansson@cern.ch
 **
 **   Created:      
 **   Modified:     
 **                   
 **************************************************************************/ 

#ifndef __TOPOLOGY_JETMETBTAG_H
#define __TOPOLOGY_JETMETBTAG_H

#include "Topology_base.h"



class Topology_jetmetbtag : public Topology_base {
 public:
  Topology_jetmetbtag(AtlEvent *evt) : Topology_base(evt){};
  void cut(const TString & prefix);
  void book(const TString & prefix, const TString & suffix);
  void finalize(void);

 private:
  void plotBtagProp(TString obj="",
                    TString category="",
                    TString value="",TString type="eff");
  bool IsTaggedJet(const Jet& j, TString type="");

  vector<int> btagindex(bool isTru=false);
  int btags(bool isTru=false);
  int btags(const std::map<TString,std::pair<double,bool> >& evttagrate,std::string error="");
  int btags_pred(const std::string& type,bool isTru=false, std::string error="");
  bool passSusyGroupCuts2(bool isTru);
  void checkMCLeptonEfficiency(const TString& pre, const TString& suf,
                               double drmatch = 0.05);
  void checkBtagEff(const TString& pre, const TString& suf);
  std::map< TString,std::pair< double,bool> > EvtTagProb(const std::string& param_type,bool isTru=false,std::string error="");

};

#endif  /* __TOPOLOGY_JETMETBTAG_H */
