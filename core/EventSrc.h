/**************************************************************************
 **
 **   File:         EventSrc.h
 **
 **   Description:  Generic event source interface to AtlEvent
 ** 
 **   Author:       jorgen.sjolin@physto.se
 **
 **   Created:      Wed Jun 21 16:43:37 CEST 2006 J.S.
 **   Modified:     
 **                   
 **************************************************************************/ 

#ifndef __EVENT_SRC_H
#define __EVENT_SRC_H

#include <iostream>
#include <utility>
#include <list>
#include <map>
#include "TString.h"

//GRL
//#include "GoodRunsLists/DQHelperFunctions.h"


class AtlEvent;

class PreTrigger {
 public:
  enum TRIGBITS {
    CONSUMED=(1<<0), EF_E20I=(1<<1), EF_MU20=(1<<2), EF_E105=(1<<3),
    EF_J20=(1<<4),EF_J33=(1<<5),EF_J55=(1<<6)
  };
  PreTrigger(void) : m_trigbits(0) {}
  void setEF_e20i(bool passed) {if (passed) m_trigbits |= EF_E20I;}
  void setEF_e105(bool passed) {if (passed) m_trigbits |= EF_E105;}
  void setEF_mu20(bool passed) {if (passed) m_trigbits |= EF_MU20;}
  void setEF_J20(bool passed) {if (passed) m_trigbits |= EF_J20;}
  void setEF_J33(bool passed) {if (passed) m_trigbits |= EF_J33;}
  void setEF_J55(bool passed) {if (passed) m_trigbits |= EF_J55;}
  void set_consumed(void) {m_trigbits |= CONSUMED;}
  bool getEF_e20i(void) const {return m_trigbits & EF_E20I;}
  bool getEF_e105(void) const {return m_trigbits & EF_E105;}
  bool getEF_mu20(void) const {return m_trigbits & EF_MU20;}
  bool getEF_J20(void) const {return m_trigbits & EF_J20;}
  bool getEF_J33(void) const {return m_trigbits & EF_J33;}
  bool getEF_J55(void) const {return m_trigbits & EF_J55;}
  bool get_consumed(void) const {return m_trigbits & CONSUMED;}

 private:
  int m_trigbits;
};

class EventSrc {
 public:
  EventSrc() : m_useGRL(true){};
  virtual ~EventSrc() {};
  virtual bool copy_to_interface(AtlEvent &atl);
  virtual int Open(std::list<TString> filelist);
  virtual void Close(void);
  virtual void SetBranches(void);
  virtual void Initialise(void);
  virtual void Finalise(void);
  virtual double GetNEntries(void);
  virtual void GetEntry(int entry);

  void useGRL(const int& val) {m_useGRL=(int)val;}
  bool useGRL(void) const {return m_useGRL;}
  
 private:
  bool m_useGRL;

  typedef std::map<std::pair<int,int>, PreTrigger> PreTriggerMap;

  
  void SetXMLFile(const TString& filename) {
    std::cout<<"eventsrc: setting grl to " << filename << std::endl;
    /*   DQ::SetXMLFile(filename); */
  } 
  bool passGRL(const int& runnr,const int& lumiblocknr ) {
    if (1==0) std::cout << runnr << " " << lumiblocknr << std::endl;
    return true;
  }
  

  PreTrigger* pretrigger(std::pair<int,int> & key) {
    PreTriggerMap::iterator item=m_pretriggers.find(key);
    if(item != m_pretriggers.end())
      return &(item->second);
    else
      return 0;
  }

  bool pretrigger_check_and_consume(std::pair<int,int> key) {
    if (!pretrigger(key)) {
      std::cout << "Reconstructed event not in the trigger (run, event) = "
	   << key.first << ", " << key.second << std::endl;
      exit(1);
    }
    if (pretrigger(key)->get_consumed()) {
      std::cout << "Duplicate event (run, event) = " << key.first
	   << ", " << key.second << std::endl;
      return false;
    }
    pretrigger(key)->set_consumed();
    return true;
  }

  PreTrigger & add_pretrigger(int run, int event) {
    std::pair<int,int> key(run,event);
    if(m_pretriggers.find(key)==m_pretriggers.end()) {
      PreTrigger pret;
      m_pretriggers[key]=pret;
    }
    return m_pretriggers[key];
  }

  PreTriggerMap m_pretriggers;
};

#endif  /* __EVENT_SRC_H */
