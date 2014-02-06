/**************************************************************************
 **
 **   File:         TrigChain.h
 **
 **   Description:  
 **
 **
 **   Author:       P. Hansson
 **
 **   Created:      Tue Mar 20 2007
 **   Modified:
 **
 **************************************************************************/

#ifndef __TRIGCHAIN_H
#define __TRIGCHAIN_H

#include <map>
#include <string>
#include <iostream>
#include "AtlEvent.h"


static const double drMaxROI=0.4;


class TrigChainBase {
 public:
 TrigChainBase() :  m_debug(0),chain_name("") {};
 TrigChainBase(const std::string& chainName, const int& debug=0) 
   : m_debug(debug), chain_name(chainName) {};
  virtual ~TrigChainBase() {};
  
  //Virtual functions --> must be defined!
  virtual bool PassL1(AtlEvent& evt) const {
    if(get_debug()>1) std::cout << "TrigChainBase::PassL1: evt at " << &evt << std::endl;exit(-1);
    return false;
  };
  virtual bool PassL2(AtlEvent& evt) const {
    if(get_debug()>1) std::cout << "TrigChainBase::PassL2: evt at " << &evt << std::endl;exit(-1);
    return false;
  };    
  virtual bool PassEF(AtlEvent& evt) const {
    if(get_debug()>1) std::cout << "TrigChainBase::PassEF: evt at " << &evt << std::endl;exit(-1);
    return false;
  };    
  virtual bool Pass(AtlEvent& evt) const {
    if(get_debug()>1) std::cout << "TrigChainBase::Pass: evt at " << &evt << std::endl;exit(-1);
    return false;
  };

  void Clear() {
    chain_name="";
    m_debug=0;
    L1_names.clear();
    L2_names.clear();
    EF_names.clear();
  }
  
  std::string ChainName() const {
    return chain_name;
  };
  void ChainName(const std::string& str, const int& debug=0) {
    chain_name = str; set_debug(debug);
  };
  
  void addL1(const std::string& name) {
    L1_names.push_back(name);
  };
  void addL2(const std::string& namel2,const std::string& namel1) {
    std::vector<std::string> tmp; 
    tmp.push_back(namel2);
    tmp.push_back(namel1);
    L2_names.push_back(tmp);
  };
  void addEF(const std::string& nameef,const std::string& namel2,const std::string& namel1) {
     std::vector<std::string> tmp; 
     tmp.push_back(nameef);
     tmp.push_back(namel2);
     tmp.push_back(namel1);
     EF_names.push_back(tmp);
  };
  void set_debug(const int& debug) {m_debug = debug;};
  int get_debug() const { return m_debug;};

 private:
  
  int m_debug;
  std::string chain_name; //in order to identify with other items
  std::vector<std::string> L1_names; 
  std::vector< std::vector< std::string > > L2_names; //[L2_name][L1_name]
  std::vector< std::vector< std::string > > EF_names; //[EF_Name][L2_name][L1_name]
  
};



class TrigChainsBase {
  
 public:
  TrigChainsBase() {};
  ~TrigChainsBase() {
    for(size_t i=0;i!=m_chains.size();++i) delete m_chains.at(i);
  };
  
  int find_chain(const std::string& name) {
    for(size_t i=0;i!=m_chains.size();++i) {
      if(name==(m_chains.at(i))->ChainName()) return (int)i;
    }
    return -1;
  };
  void add(TrigChainBase* chain) {
    //check that it doesn't exist
    if(find_chain(chain->ChainName())!=-1) {
      std::cout << "TrigChainsBase: ERROR in add_chain, " << chain->ChainName() << " already exists!" << std::endl;
      exit(-1);
    }
    m_chains.push_back(chain);
  };
  
  bool pass(const std::string& name, AtlEvent& evt) {
    int index = find_chain(name);
    if(index==-1) {
      std::cout << "TrigChainsBase: ERROR in pass, " << name << " doesn't exists!" << std::endl;
      exit(-1);
    }
    assert(index<(int)m_chains.size());
    return (m_chains.at(index))->Pass(evt);
  };
  
  void print_chains(void) {
    std::cout << "###### TrigChain: Defined chains:" << std::endl;
    for(size_t i=0;i!=m_chains.size();++i) std::cout << m_chains.at(i)->ChainName() << std::endl; 
    std::cout << "######" << std::endl;
  };

  std::vector<std::string> get_passed_chains(AtlEvent& evt) {
    std::vector<std::string> chains;
    for(size_t i=0;i!=m_chains.size();++i) {
      if((m_chains.at(i))->Pass(evt)) {
	chains.push_back( (m_chains.at(i))->ChainName());
      }
    }
    return chains;
  };
 private:
  std::vector<TrigChainBase*> m_chains;
};



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


/*** Usage
     TrigJetXEChain chain("L1_2J30L1_XE20L2_2j40L2_xe30",0);
     chain.addL1(L1_2J30);
     chain.addL1(L1_XE30);
     chain.addL2(L2_2j40,L1_2J30);
     chain.addL2(L2_xe40,L1_XE30);
***/

class TrigJetXEChain : public TrigChainBase {
 public:
 TrigJetXEChain() :  TrigChainBase() {};
 TrigJetXEChain(const std::string& chainName, const int& debug=0) 
   :  TrigChainBase(chainName,debug) {};
  ~TrigJetXEChain() {};
  
  bool PassL1(AtlEvent& evt) const;
  bool PassL2(AtlEvent& evt) const;  
  bool PassEF(AtlEvent& evt) const;  
  bool Pass(AtlEvent& evt) const {
    if(get_debug()>0) {
      std::cout << "TrigJetXEChain "<< chain_name <<" in Pass()" << std::endl;
    }
    bool result = PassL1(evt); 
    if(get_debug()>0) { std::cout << "TrigJetXEChain in Pass(): L1 --> " << (result?"PASS":"FAILED") << std::endl; }
    if(!result) return false;
    result = PassL2(evt); 
    if(get_debug()>0) { std::cout << "TrigJetXEChain in Pass(): L2 --> " << (result?"PASS":"FAILED") << std::endl; }
    if(!result) return false;
    result = PassEF(evt); 
    if(get_debug()>0) { std::cout << "TrigJetXEChain in Pass(): EF --> " << (result?"PASS":"FAILED") << std::endl; }
    if(!result) return false;
    return true;
  };
 private:
  
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


/*** Usage
     TrigJetChain jetItem("L2_1J40L2_4J20","L2_J40",0);
     jetItem.addL1(L1_4J10);
     jetItem.addL1(L1_1J40);
     jetItem.addL2(L2_4J20,L1_4J10);
     jetItem.addL2(L2_1J40,L1_1J40);
***/

class TrigJetChain : public TrigChainBase {
 public:
 TrigJetChain() :  TrigChainBase() {};
 TrigJetChain(const std::string& chainName, const int& debug=0) 
   :  TrigChainBase(chainName,debug) {};
  ~TrigJetChain() {};
  
  bool PassL1(AtlEvent& evt) const;
  bool PassL2(AtlEvent& evt) const;  
  bool Pass(AtlEvent& evt) const {
    if(get_debug()>0) {
      std::cout << "TrigChain "<< chain_name <<" in Pass()" << std::endl;
    }
    bool result = PassL1(evt); 
    if(get_debug()>0) { std::cout << "TrigChain in Pass(): L1 --> " << (result?"PASS":"FAILED") << std::endl; }
    if(!result) return false;
    result = PassL2(evt); 
    if(get_debug()>0) { std::cout << "TrigChain in Pass(): L2 --> " << (result?"PASS":"FAILED") << std::endl; }
    if(!result) return false;
    return true;
  };
 private:
  
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*
class TrigJetChains {

 public:
  TrigJetChains() {};
  ~TrigJetChains() {};

  int find_chain(const std::string& name) {
    for(size_t i=0;i!=m_chains.size();++i) {
      if(name==(m_chains.at(i)).ChainName()) return (int)i;
    }
    return -1;
  }
  void add(const TrigJetChain& chain) {
    //check that it doesn't exist
    if(find_chain(chain.ChainName())!=-1) {
      std::cout << "TrigJetChains: ERROR in add_chain, " << chain.ChainName() << " already exists!" << std::endl;
      exit(-1);
    }
    m_chains.push_back(chain);
  };
  
  bool pass(const std::string& name, AtlEvent& evt) {
    int index = find_chain(name);
    if(index==-1) {
      std::cout << "TrigJetChains: ERROR in pass, " << name << " doesn't exists!" << std::endl;
      exit(-1);
    }
    assert(index<(int)m_chains.size());
    return (m_chains.at(index)).Pass(evt);
  }

  std::vector<std::string> get_passed_chains(AtlEvent& evt) {
    std::vector<std::string> chains;
    for(size_t i=0;i!=m_chains.size();++i) {
      if((m_chains.at(i)).Pass(evt)) {
	chains.push_back( (m_chains.at(i)).ChainName());;
      }
    }
    return chains;
  };
 private:
  std::vector<TrigJetChain> m_chains;
};
*/
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%






//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%% SUM JET ET


/*** Usage
     TrigSumJetEtChain jetItem("L1_JE90L2_JE200",0);
     jetItem.addL1(L1_JE90);
     jetItem.addL2(L2_4J20,L1_JE90);
***/

class TrigSumJetEtChain : public TrigChainBase {
 public:
 TrigSumJetEtChain() : TrigChainBase() {};
 TrigSumJetEtChain(const std::string& chainName, const int& debug=0) : 
  TrigChainBase(chainName, debug) {};
  ~TrigSumJetEtChain() {};
  
  bool PassL1(AtlEvent& evt) const;
  bool PassL2(AtlEvent& evt) const;  
  bool Pass(AtlEvent& evt) const {
    if(get_debug()>0) {
      std::cout << "TrigSumJetEtChain "<< chain_name <<" in Pass()" << std::endl;
    }
    bool result = PassL1(evt); 
    if(get_debug()>0) { std::cout << "TrigSumJetEtChain in Pass(): L1 --> " << (result?"PASS":"FAILED") << std::endl; }
    if(!result) return false;
    result = PassL2(evt); 
    if(get_debug()>0) { std::cout << "TrigSumJetEtChain in Pass(): L2 --> " << (result?"PASS":"FAILED") << std::endl; }
    if(!result) return false;
    return true;
  };
  
 private:
  
};



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%% L2 bjet chains

/*** Usage
     TrigJetChain jetItem("L1_4J10L1_1J40L2_2b",0);
     jetItem.addL1(L1_4J10);
     jetItem.addL1(L1_1J40);
     jetItem.addL2(L2_2b,L1_4J10);
     jetItem.addL2(L2_1b,L1_1J40);
***/



class TrigL2BJetChain : public TrigChainBase {
 public:
 TrigL2BJetChain() :  TrigChainBase() {};
 TrigL2BJetChain(const std::string& chainName, const int& debug=0) 
   :  TrigChainBase(chainName,debug) {};
  ~TrigL2BJetChain() {};
  
  
  bool PassL1(AtlEvent& evt) const;
  bool PassL2(AtlEvent& evt) const;  
  
  bool Pass(AtlEvent& evt) const {
    if(get_debug()>0) {
      std::cout << "TrigChain "<< chain_name <<" in Pass()" << std::endl;
    }
    bool result = PassL1(evt); 
    if(get_debug()>0) { std::cout << "TrigChain in Pass(): L1 --> " << (result?"PASS":"FAILED") << std::endl; }
    if(!result) return false;
    result = PassL2(evt); 
    if(get_debug()>0) { std::cout << "TrigChain in Pass(): L2 --> " << (result?"PASS":"FAILED") << std::endl; }
    if(!result) return false;
    return true;
  };
  
 private:
  
  
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/* class TrigL2BJetChains { */
  
/*  public: */
/*   TrigL2BJetChains() {}; */
/*   ~TrigL2BJetChains() {}; */
  
/*   int find_chain(const std::string& name) { */
/*     for(size_t i=0;i!=m_chains.size();++i) { */
/*       if(name==(m_chains.at(i)).ChainName()) return (int)i; */
/*     } */
/*     return -1; */
/*   } */
/*   void add(const TrigL2BJetChain& chain) { */
/*     //check that it doesn't exist */
/*     if(find_chain(chain.ChainName())!=-1) { */
/*       std::cout << "TrigL2BJetChains: ERROR in add_chain, " << chain.ChainName() << " already exists!" << std::endl; */
/*       exit(-1); */
/*     } */
/*     m_chains.push_back(chain); */
/*   }; */
  
/*   bool pass(const std::string& name, AtlEvent& evt) { */
/*     int index = find_chain(name); */
/*     if(index==-1) { */
/*       std::cout << "TrigL2BJetChains: ERROR in pass, " << name << " doesn't exists!" << std::endl; */
/*       exit(-1); */
/*     } */
/*     assert(index<(int)m_chains.size()); */
/*     return (m_chains.at(index)).Pass(evt); */
/*   } */
  
/*   std::vector<std::string> get_passed_chains(AtlEvent& evt) { */
/*     std::vector<std::string> chains; */
/*     for(size_t i=0;i!=m_chains.size();++i) { */
/*       if((m_chains.at(i)).Pass(evt)) { */
/* 	chains.push_back( (m_chains.at(i)).ChainName());; */
/*       } */
/*     } */
/*     return chains; */
/*   }; */
/*  private: */
/*   std::vector<TrigL2BJetChain> m_chains; */
/* }; */

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%% XE chains

/*** Usage
     TrigJetChain jetItem("L1_XE35L2_xe50",0);
     jetItem.addL1(L1_XE35);
     jetItem.addL2(L2_xe50,L1_XE35);
***/



class TrigXEChain : public TrigChainBase {
 public:
 TrigXEChain() :  TrigChainBase() {};
 TrigXEChain(const std::string& chainName, const int& debug=0) 
   :  TrigChainBase(chainName,debug) {};
  ~TrigXEChain() {};

  bool PassL1(AtlEvent& evt) const;
  bool PassL2(AtlEvent& evt) const;  
  bool PassEF(AtlEvent& evt) const;  
  
  bool Pass(AtlEvent& evt) const {
    if(get_debug()>0) {
      std::cout << "TrigChain "<< chain_name <<" in Pass()" << std::endl;
    }
    bool result = PassL1(evt); 
    if(get_debug()>0) { std::cout << "TrigChain in Pass(): L1 --> " << (result?"PASS":"FAILED") << std::endl; }
    if(!result) return false;
    result = PassL2(evt); 
    if(get_debug()>0) { std::cout << "TrigChain in Pass(): L2 --> " << (result?"PASS":"FAILED") << std::endl; }
    if(!result) return false;
    result = PassEF(evt); 
    if(get_debug()>0) { std::cout << "TrigChain in Pass(): EF --> " << (result?"PASS":"FAILED") << std::endl; }
    if(!result) return false;
    return true;
  };
  
 private:
  
  
};



#endif  /* __TRIGCHAIN_H */
