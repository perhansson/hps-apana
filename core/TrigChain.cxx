#include "TrigChain.h"

static const int debug_var=0;


bool IsL1Jet( const std::string &name,int& N,int& thr) {
  //Ex. syntax L1_1J50
  char str2;
  int found = sscanf(name.c_str(),"L1_%d%c%d",&N,&str2,&thr);
  if(debug_var>1) {
    std::cout<<"IsL1Jet: item "<<name
	     <<" splitted into "
	     <<" str2="<<str2 << " N="<<N << " thr="<<thr <<std::endl;
  }
  
    bool ok = false;
    if(found==3 && str2=='J' && N>0 && thr>0) {
      ok = true;
    }
    if(debug_var>1) {  
      std::cout<<" ---> ok="<<ok << std::endl;
    }
    if(!ok) {
      if(debug_var>1) {
	std::cout<<name<<" is not a L1 jet item"<< std::endl;
      }
      return false;
    }
    if(debug_var>1) {
      std::cout<<name<<" is a L1 jet item with: N=" << N << ", thr=" << thr << std::endl;  
    }
    return true;         
};

bool IsL2Jet( const std::string &name,int& N,int& thr) {
  //Ex. syntax L2_1j50
  char str2;
    int found = sscanf(name.c_str(),"L2_%d%c%d",&N,&str2,&thr);
    if(debug_var>1) {
      std::cout<<"IsL2Jet: item "<<name
	       <<" splitted into "
	       <<" str2="<<str2 << " N="<<N << " thr="<<thr <<std::endl;
    }
    
    bool ok = false;
    if(found==3 && str2=='j' && N>0 && thr>0) {
      ok = true;
    }
    if(debug_var>1) {  
      std::cout<<" ---> ok="<<ok << std::endl;
    }
    if(!ok) {
      if(debug_var>1) {
	std::cout<<name<<" is not a L2 jet item"<< std::endl;
      }
      return false;
    }
    if(debug_var>1) {
      std::cout<<name<<" is a L2 jet item with: N=" << N << ", thr=" << thr << std::endl;  
    }
    return true;         
  };

bool IsEFJet( const std::string &name,int& N,int& thr) {
  //Ex. syntax EF_1j50
  char str2;
    int found = sscanf(name.c_str(),"EF_%d%c%d",&N,&str2,&thr);
    if(debug_var>1) {
      std::cout<<"IsEFJet: item "<<name
	       <<" splitted into "
	       <<" str2="<<str2 << " N="<<N << " thr="<<thr <<std::endl;
    }
    
    bool ok = false;
    if(found==3 && str2=='j' && N>0 && thr>0) {
      ok = true;
    }
    if(debug_var>1) {  
      std::cout<<" ---> ok="<<ok << std::endl;
    }
    if(!ok) {
      if(debug_var>1) {
	std::cout<<name<<" is not a EF jet item"<< std::endl;
      }
      return false;
    }
    if(debug_var>1) {
      std::cout<<name<<" is a EF jet item with: N=" << N << ", thr=" << thr << std::endl;  
    }
    return true;         
  };

bool IsL2BJet( const std::string &name,std::string &type, int& N) {
  //Ex. syntax L2_1bD
  char strtype;
  char str;
  int found = sscanf(name.c_str(),"L2_%d%c%c",&N,&str,&strtype);
  if(debug_var>1) {
    std::cout<<"IsL2BJet: item "<<name
	     <<" splitted into "
	     <<" str="<<str <<" strtype="<<strtype << " N="<<N << std::endl;
  }  
  bool ok = false;
  bool tightnessOK = false;
  if(strtype=='D' || strtype=='L' || strtype=='E') tightnessOK=true;
  if(found==3 && str=='b' && tightnessOK && N>0 ) {
    ok = true;
    type = strtype;
  }
  if(debug_var>1) {  
    std::cout<<" ---> ok="<<ok << std::endl;
  }
  if(!ok) {
    if(debug_var>1) {
      std::cout<<name<<" is not a L2Bjet item"<< std::endl;
    }
    return false;
  }
  if(debug_var>1) {
    std::cout<<name<<" is a L2Bjet item with: N=" << N << ", str=" << str << "strtype="<<strtype << std::endl;  
  }
  return true;         
};


bool GetL1JetItems(AtlEvent& evt, const std::string &name, std::vector<const L1Jet*>& l1jetobjects ) {
   if(debug_var>1) {
      std::cout << "TrigChain GetL1JetItems for name="<<name<<std::endl;
   }
    
   int N,thr;
   bool isL1Jet = IsL1Jet(name,N,thr);
   if(!isL1Jet) { 
      //if(debug_var>1) {
      std::cout << "TrigChain GetL1JetItems this name="<<name<<" is not a L1 jet name!"<<std::endl;       
      //}
      exit(-1);
      //return false;
   }
   std::ostringstream item_name;
   item_name << "J";
   item_name << thr;
   //Find the objects passing the selections
   double threshold = static_cast<double>( thr );
   if(debug_var>1) {
      std::cout << "TrigChain GetL1JetItems checking if any of the "<<evt.m_l1jets.size()<<" pass thr="<<threshold<<std::endl;
   }
   for(size_t i=0;i!=evt.m_l1jets.size();++i) { 
      if(debug_var>1) {
         std::cout << "L1 jet i="<<i<<" pt="<<evt.m_l1jets[i].p.Pt() << " threshold="<<threshold << ". Check if it passed threshold name " << item_name.str() << std::endl;
      }
      
      if( evt.m_l1jets[i].PassedThr(item_name.str())) { //rounding problems?
         l1jetobjects.push_back(&(evt.m_l1jets[i]));
         if(debug_var>1) { 
            std::cout << " --> PASS ( so far "<<l1jetobjects.size()<<" has passed)"<<std::endl;
         }
      }
   }
   //Check if the trigger is satisfied
   bool result = l1jetobjects.size()>=(size_t)N ? true : false;
   if(debug_var>1) {
      std::cout << name << " trigger result="<<result <<std::endl;
      std::cout << name << " the following L1 Objects is saved:"<<std::endl;
      for(size_t i=0;i!=l1jetobjects.size();++i) { 
         std::cout << "pt="<<l1jetobjects.at(i)->p.Pt()<<" eta="<<l1jetobjects.at(i)->p.Eta()<<std::endl;
      }
   }
   return result;
};






bool GetL2JetItems(AtlEvent& evt, const std::string &name, std::vector<const Jet*>& l2jetobjects ) {
    if(debug_var>1) {
      std::cout << "TrigChain GetL2JetItems for name="<<name<<std::endl;
    }
    int N,thr;
    bool isL2Jet = IsL2Jet(name,N,thr);
    if(!isL2Jet) { 
      if(debug_var>1) {
	std::cout << "TrigChain GetL2JetItems this name="<<name<<" is not a L2 jet name!"<<std::endl;
      }
      return false;
    }
    //Find the objects passing the selections
    double threshold = static_cast<double>( thr );
    
    if(debug_var>1) {
      std::cout << "TrigChain GetL2JetItems checking if any of the "<<evt.m_l2jets.size()<<" pass thr="<<threshold<<std::endl;
    }
    for(size_t i=0;i!=evt.m_l2jets.size();++i) { 
      if(debug_var>1) {
	std::cout << "L2 jet i="<<i<<" pt="<<evt.m_l2jets[i].p.Pt() << " threshold="<<threshold << " diff="<< (evt.m_l2jets[i].p.Pt()-threshold) << std::endl;
      }
      if( evt.m_l2jets[i].p.Pt() - threshold > -0.0001 ) { //rounding problems?
	l2jetobjects.push_back(&(evt.m_l2jets[i]));
	if(debug_var>1) { 
	  std::cout << " --> PASS ( so far "<<l2jetobjects.size()<<" has passed)"<<std::endl;
	}
      }
    }
    //Check if the trigger is satisfied
    bool result = l2jetobjects.size()>=(size_t)N ? true : false;
    if(debug_var>1) {
      std::cout << name << " trigger result="<<result <<std::endl;
      std::cout << name << " the following L2 Objects is saved:"<<std::endl;
      for(size_t i=0;i!=l2jetobjects.size();++i) { 
	std::cout << "pt="<<l2jetobjects.at(i)->p.Pt()<<" eta="<<l2jetobjects.at(i)->p.Eta()<<std::endl;
      }
    }
    return result;
  };



bool GetL2BJetItems(AtlEvent& evt, const std::string &name, std::vector<const L2BJet*>& l2jetobjects ) {
  if(debug_var>1) {
    std::cout << "TrigChain GetL2BJetItems for name="<<name<<std::endl;
  }
  int N;
  std::string type="";
  bool isL2Jet = IsL2BJet(name,type,N);
  if(!isL2Jet) { 
    if(debug_var>1) {
      std::cout << "GetL2BJetItems this name="<<name<<" is not a L2bjet name!"<<std::endl;
    }
    return false;
  }
  
  //Use the type to udnerstand what cut to use
  double cut;
  std::string tagger = "IP3D";
  //For IP3D
  //NOTE: this should come from the config file!
  //if(type=="D") cut = 0.49;
  if(type=="D") cut = 0.61;
  else if(type=="L") cut = 0.30;
  else if(type=="E") cut = 0.20;
  else {
    std::cout << "GetL2BJetItems ERROR: type "<<type<<" is not defined!"<<std::endl;
    exit(-1);
  }
  //   //For CHI2
  //   //NOTE: this should come from the config file!
  //   if(type=="D") cut = 0.35;
  //   else if(type=="L") cut = 0.46;
  //   else if(type=="E") cut = 0.55;
  //   else {
  //     std::cout << "GetL2BJetItems ERROR: type "<<type<<" is not defined!"<<std::endl;
  //     exit(-1);
  //   }
  
  if(debug_var>1) {
    std::cout << "TrigChain GetL2BJetItems checking if any of the "<<evt.m_l2bjets.size()<<" L2 bjets pass cut = "<<cut<< std::endl;
  }
  
  for(size_t i=0;i!=evt.m_l2bjets.size();++i) { 
    if(debug_var>1) cout << "L2 bjet " << i << " IP3D="<<(evt.m_l2bjets.at(i)).IP3D() << ": ";
    if( (evt.m_l2bjets.at(i)).IsTagged(tagger,cut) ) {
      l2jetobjects.push_back(&(evt.m_l2bjets.at(i)));
      if(debug_var) cout << " is tagged! (so far "<<l2jetobjects.size() << " tagged)"<<endl;
    }
  }
  
  //Check if the trigger is satisfied
  bool result = l2jetobjects.size()>=(size_t)N ? true : false;
  if(debug_var>1) {
    std::cout << name << " trigger result="<<result <<std::endl;
    std::cout << name << " the following L2 bjet Objects is saved:"<<std::endl;
    for(size_t i=0;i!=l2jetobjects.size();++i) { 
      std::cout << "phi="<<l2jetobjects.at(i)->p.Phi()<<" eta="<<l2jetobjects.at(i)->p.Eta()<<std::endl;
    }
  }
  return result;
};



bool IsL1XE( const std::string &name,int& thr) {
  //Ex. syntax L1_XE100
  int found = sscanf(name.c_str(),"L1_XE%d",&thr);
  if(debug_var>1) {
    std::cout<<"IsL1XE: item "<<name
	     <<" splitted into "
	     << " thr="<<thr <<std::endl;
  }
  
  bool ok = false;
  if(found==1 && thr>0) {
    ok = true;
  }
  if(debug_var>1) {  
    std::cout<<" ---> ok="<<ok << std::endl;
  }
  if(!ok) {
    if(debug_var>1) {
      std::cout<<name<<" is not a L1 XE item"<< std::endl;
    }
    return false;
  }
  if(debug_var>1) {
    std::cout<<name<<" is a L1 XE item with thr=" << thr << std::endl;  
  }
  return true;         
};

bool IsL2XE( const std::string &name,int& thr) {
  //Ex. syntax L2_XE100
  int found = sscanf(name.c_str(),"L2_xe%d",&thr);
  if(debug_var>1) {
    std::cout<<"IsL2XE: item "<<name
	     <<" splitted into "
	     << " thr="<<thr <<std::endl;
  }
  
  bool ok = false;
  if(found==1 && thr>0) {
    ok = true;
  }
  if(debug_var>1) {  
    std::cout<<" ---> ok="<<ok << std::endl;
  }
  if(!ok) {
    if(debug_var>1) {
      std::cout<<name<<" is not a L2 XE item"<< std::endl;
    }
    return false;
  }
  if(debug_var>1) {
    std::cout<<name<<" is a L2 XE item with thr=" << thr << std::endl;  
  }
  return true;         
};

bool IsEFXE( const std::string &name,int& thr) {
  //Ex. syntax EF_xe100
  int found = sscanf(name.c_str(),"EF_xe%d",&thr);
  if(debug_var>1) {
    std::cout<<"IsEFXE: item "<<name
	     <<" splitted into "
	     << " thr="<<thr <<std::endl;
  }
  
  bool ok = false;
  if(found==1 && thr>0) {
    ok = true;
  }
  if(debug_var>1) {  
    std::cout<<" ---> ok="<<ok << std::endl;
  }
  if(!ok) {
    if(debug_var>1) {
      std::cout<<name<<" is not a EF XE item"<< std::endl;
    }
    return false;
  }
  if(debug_var>1) {
    std::cout<<name<<" is a EF XE item with thr=" << thr << std::endl;  
  }
  return true;         
};

bool IsL1SumJetEt( const std::string &name,int& thr) {
  //Ex. syntax L1_JE100
  int found = sscanf(name.c_str(),"L1_JE%d",&thr);
  if(debug_var>1) {
    std::cout<<"IsL1SumJetEt: item "<<name
	     <<" splitted into "
	     << " thr="<<thr <<std::endl;
  }
  
  bool ok = false;
  if(found==1 && thr>0) {
    ok = true;
  }
  if(debug_var>1) {  
    std::cout<<" ---> ok="<<ok << std::endl;
  }
  if(!ok) {
    if(debug_var>1) {
      std::cout<<name<<" is not a L1 sum jet et item"<< std::endl;
    }
    return false;
  }
  if(debug_var>1) {
    std::cout<<name<<" is a L1 sum jet et item with thr=" << thr << std::endl;  
  }
  return true;         
};

bool IsL2SumJetEt( const std::string &name,int& thr) {
  //Ex. syntax L2_je100
  int found = sscanf(name.c_str(),"L2_je%d",&thr);
  if(debug_var>1) {
    std::cout<<"IsL2SumJetEt: item "<<name
	     <<" splitted into "
	     <<" thr="<<thr <<std::endl;
  }
    
  bool ok = false;
  if(found==1 && thr>0) {
    ok = true;
  }
  if(debug_var>1) {  
    std::cout<<" ---> ok="<<ok << std::endl;
  }
  if(!ok) {
    if(debug_var>1) {
      std::cout<<name<<" is not a L2 sum jet et item"<< std::endl;
    }
    return false;
  }
  if(debug_var>1) {
    std::cout<<name<<" is a L2 sum jet et item with thr=" << thr << std::endl;  
  }
  return true;         
};





bool TrigXEChain::PassL1(AtlEvent& evt) const {
  if(L1_names.size()==0) {
    std::cout << "TrigXEChain ERROR: no L1 names!"<< std::endl; exit(-1);
  }
  if(get_debug()>1) {
    std::cout << "TrigXEChain in PassL1()" << std::endl;
    std::cout << "PassL1 L1_names: ";
    for(size_t i=0;i!=L1_names.size();++i) {std::cout << L1_names.at(i) << "";}
    std::cout<<std::endl;      
  }
  
  //Loop over each L1 name
  for(size_t i =0;i!=L1_names.size();++i) {
    std::string L1_name = L1_names.at(i);
    if(get_debug()>1) {
      std::cout << "L1Name "<<L1_name<<" in TrigXEChain" << std::endl;
    }
    int thr;
    bool ok = IsL1XE(L1_name,thr);
    if(!ok) {
      std::cout << L1_name << " is not a L1 TrigXEChain name!"<<std::endl;
      exit(-1);      
    }
    bool pass =  evt.l1_met() > thr ? true : false;
    if(get_debug()>1) {
      std::cout << "TrigXEChain met="<<evt.l1_met()<<" --> result = "<<pass<<std::endl;
    }
    if(!pass) return false;
  }
  if(get_debug()>1) {
    std::cout << "TrigXEChain passed all L1 names"<<std::endl;
  }
  return true; 
};


bool TrigXEChain::PassL2(AtlEvent& evt) const  {
  if(get_debug()>1) {
    std::cout << "TrigXEChain in PassL2()" << std::endl;
    std::cout << "L2_names: ";
    for(size_t i=0;i!=L2_names.size();++i) {std::cout << L2_names.at(i)[0] << "";}
    std::cout<<std::endl;      
  }
  
  //Loop over each L2 name
  for(size_t i =0;i!=L2_names.size();++i) {
    std::string L2_name = L2_names.at(i)[0];

    if(get_debug()>1) {
      std::cout << "L2Name "<<L2_name<<" in TrigXEChain" << std::endl;
    }
    //assume that it passed already!
//     bool passl1_tmp = PassL1(evt);
//     if(!passl1_tmp) {
//       std::cout << "L1 did not pass for "<<L2_name<<" TrigXEChain"<<std::endl;
//       exit(-1);      
//     }
    if(get_debug()>1) {
      std::cout << "L1 passed for "<<L2_name<<" TrigXEChain" << std::endl;
    }
    
    int thr;
    bool ok = IsL2XE(L2_name,thr);
    if(!ok) {
      std::cout << L2_name << " is not a L2 TrigXEChain name!"<<std::endl;
      exit(-1);      
    }
    bool pass =  evt.l2_met() > thr ? true : false;
    if(get_debug()>1) {
      std::cout << "TrigXEChain result for L2 name "<< L2_name << " with L2 met = "<<evt.l2_met()<<" --> "<<pass<<std::endl;
    }
    if(!pass) return false;
  }
  if(get_debug()>1) {
    std::cout << "TrigXEChain passed all L2 names"<<std::endl;
  }
  return true; 
};




// bool TrigXEChain::PassEF(AtlEvent& evt) const  {
//    if(get_debug()>1) {
//       std::cout << "TrigXEChain in PassEF()" << std::endl;
//       std::cout << "EF_names: ";
//       //for(size_t i=0;i!=EF_names.size();++i) {std::cout << EF_names.at(i)[0] << "";}
//       std::cout<<std::endl;      
//    }
//    return false;
// }


bool TrigXEChain::PassEF(AtlEvent& evt) const  {
  if(get_debug()>1) {
    std::cout << "TrigXEChain in PassEF()" << std::endl;
    std::cout << "EF_names: ";
    for(size_t i=0;i!=EF_names.size();++i) {std::cout << EF_names.at(i)[0] << "";}
    std::cout<<std::endl;      
  }
  
  //Loop over each EF name
  for(size_t i =0;i!=EF_names.size();++i) {
    std::string EF_name = EF_names.at(i)[0];
    
    if(get_debug()>1) {
       std::cout << "EFName "<<EF_name<<" in TrigXEChain" << std::endl;
    }
    //assume that it passed already!
//     bool passl1_tmp = PassL1(evt);
//     if(!passl1_tmp) {
//       std::cout << "L1 did not pass for "<<L2_name<<" TrigXEChain"<<std::endl;
//       exit(-1);      
//     }
    if(get_debug()>1) {
       std::cout << "Assume L1 passed for "<<EF_name<<" TrigXEChain" << std::endl;
       std::cout << "Assume L2 passed for "<<EF_name<<" TrigXEChain" << std::endl;
    }
    
    int thr;
    bool ok = IsEFXE(EF_name,thr);
    if(!ok) {
      std::cout << EF_name << " is not a EF TrigXEChain name!"<<std::endl;
      exit(-1);      
    }
    bool pass =  evt.ef_met() > thr ? true : false;
    if(get_debug()>1) {
       std::cout << "TrigXEChain result for EF name "<< EF_name << " with EF met = "<<evt.ef_met()<<" --> "<<pass<<std::endl;
    }
    if(!pass) return false;
  }
  if(get_debug()>1) {
    std::cout << "TrigXEChain passed all EF names"<<std::endl;
  }
  return true; 
};



bool TrigSumJetEtChain::PassL1(AtlEvent& evt) const {
  if(L1_names.size()==0) {
    std::cout << "TrigSumJetEtChain ERROR: no L1 names!"<< std::endl; exit(-1);
  }
  if(get_debug()>1) {
    std::cout << "TrigSumJetEtChain in PassL1()" << std::endl;
    std::cout << "PassL1 L1_names: ";
    for(size_t i=0;i!=L1_names.size();++i) {std::cout << L1_names.at(i) << "";}
    std::cout<<std::endl;      
  }
  
  //Loop over each L1 name
  for(size_t i =0;i!=L1_names.size();++i) {
    std::string L1_name = L1_names.at(i);
    if(get_debug()>1) {
      std::cout << "L1Name "<<L1_name<<" in TrigChainSumJetEt" << std::endl;
    }
    int thr;
    bool ok = IsL1SumJetEt(L1_name,thr);
    if(!ok) {
      std::cout << L1_name << " is not a L1 TrigChainSumJetEt name!"<<std::endl;
      exit(-1);
    }
    bool pass =  evt.L1SumJetEt() > thr ? true : false;
    if(get_debug()>1) {
      std::cout << "TrigChainSumJetEt result = "<<pass<<std::endl;
    }
    if(!pass) return false;
  }
  if(get_debug()>1) {
    std::cout << "TrigChainSumJetEt passed all L1 names"<<std::endl;
  }
  return true; 
};



bool TrigSumJetEtChain::PassL2(AtlEvent& evt) const {
  if(get_debug()>1) {
    std::cout << "TrigSumJetEtChain in PassL2()" << std::endl;
    std::cout << "PassL2 L2_names: ";
    for(size_t i=0;i!=L2_names.size();++i) {std::cout << L2_names.at(i)[0] << "";}
    std::cout<<std::endl;      
  }
  
  //Loop over each L2 name
  for(size_t i =0;i!=L2_names.size();++i) {
    std::string L2_name = L2_names.at(i)[0];

    if(get_debug()>1) {
      std::cout << "L2Name "<<L2_name<<" in TrigChainSumJetEt" << std::endl;
    }
    //assume that it passed already
//     bool passl1_tmp = PassL1(evt);
//     if(!passl1_tmp) {
//       std::cout << "L1 did not pass for "<<L2_name<<" TrigSumJetEtChain"<<std::endl;
//       exit(-1);      
//     }
    if(get_debug()>1) {
      std::cout << "L1 passed for "<<L2_name<<" TrigSimJetEtChain" << std::endl;
    }
    
    int thr;
    bool ok = IsL2SumJetEt(L2_name,thr);
    if(!ok) {
      std::cout << L2_name << " is not a L2 TrigChainSumJetEt name!"<<std::endl;
      exit(-1);      
    }
    bool EMscale = true;
    bool pass =  evt.L2SumJetEt(EMscale) > thr ? true : false;
    if(get_debug()>1) {
      std::cout << "TrigChainSumJetEt result for L2 name "<< L2_name << " = "<<pass<<std::endl;
    }
    if(!pass) return false;
  }
  if(get_debug()>1) {
    std::cout << "TrigChainSumJetEt passed all L2 names"<<std::endl;
  }
  return true; 
};


bool TrigJetXEChain::PassL1(AtlEvent& evt) const {
  if(L1_names.size()==0) {
    std::cout << "TrigJetXEChain ERROR: no L1 names!"<< std::endl; exit(-1);
  }
  if(get_debug()>1) {
    std::cout << "TrigJetXEChain in PassL1()" << std::endl;
    std::cout << "PassL1 L1_names: ";
    for(size_t i=0;i!=L1_names.size();++i) {std::cout << L1_names.at(i) << ",";}
    std::cout<<std::endl;      
  }
  
  //Loop over each L1 name
  for(size_t i =0;i!=L1_names.size();++i) {
    std::string L1_name = L1_names.at(i);
    
    //This is either a jet or a XE trigger
    //start by checking if it is a XE trigger
    int thrxe;
    bool isL1XE = IsL1XE(L1_name,thrxe);
    if(isL1XE) {
      if(get_debug()>1) std::cout << L1_name << " is a L1 XE name!"<<std::endl;
      bool passL1XE =  evt.l1_met() > thrxe ? true : false;
      if(get_debug()>1) {
	std::cout << "TrigJetXEChain met="<<evt.l1_met()<<" --> pass = "<<passL1XE<<std::endl;
      }
      if(!passL1XE) return false;

      //go to next L1 name
      continue;
    }
    //This is not a XE trigger
    if(get_debug()>1) std::cout << L1_name << " is NOT a L1 XE name!"<<std::endl;
    
    //Check if it is a L1 jet trigger
    int N,thr;
    bool isL1Jet = IsL1Jet(L1_name,N,thr);
    if(!isL1Jet) { 
      if(get_debug()>1) {
	std::cout <<L1_name<<" is not a L1 jet name either so it fails!"<<std::endl;
	exit(-1);
      }
    }
    
    // This is a L1 Jet name!
    if(get_debug()>1) std::cout << L1_name << " is a L1 Jet name!"<<std::endl;
    
    //Does it pass the L1 requirement? 
    std::vector<const L1Jet*> l1jetobjects;
    bool PassL1Jet =  GetL1JetItems(evt,L1_name,l1jetobjects);
    if(get_debug()>1) {
      std::cout << "L1Name "<<L1_name<<" in TrigJetXEChain in PassL1() PassL1Jet="<<PassL1Jet<<" with "<<l1jetobjects.size()<<" l1 jet objetcts"<<std::endl;
    }
    if(PassL1Jet) assert(l1jetobjects.size()!=0);
    if(l1jetobjects.size()==0) assert(!PassL1Jet);      
    if(get_debug()>1) {
      std::cout << "TrigJetXEChain PassL1() result = "<<PassL1Jet<<std::endl;
    }
    if(!PassL1Jet) return false;
  }
  if(get_debug()>1) {
    std::cout << "TrigJetXEChain PassL1() passed all L1 names"<<std::endl;
  }
  return true; 
};


bool TrigJetXEChain::PassL2(AtlEvent& evt) const {
  if(get_debug()>1) {
    std::cout << "TrigJetXEChain in PassL2()" <<std::endl;
  }
  //assume it passed L1!
  
  // Now go through each of the L2 names
  // check if those exist and passes
  // It will either be a XE or jet trigger!
  // If it is a jet item then find the L1 objects that is 
  // suppose to seed the L2 and check if the L2 that passed 
  // are seeded correctly    
  for(size_t i=0;i!=L2_names.size();++i) {
    assert((L2_names.at(i)).size()==2); // [L2_name],[L1_name]
    std::string L2_name = (L2_names.at(i))[0];

    //Is this a jet trigger?
    //Get vector of objects passing the L2 requirement
    std::vector<const Jet*> l2jetobjects;
    bool passL2xe = false;
    bool passL2Jet = false;
    passL2Jet =  GetL2JetItems(evt,L2_name,l2jetobjects);
    if(get_debug()>1) {
      std::cout << "L2Name "<<L2_name<<"pass="<<passL2Jet<<" with "<<l2jetobjects.size()<<" l2 jet objetcts"<<std::endl;
    }
    if(passL2Jet) assert(l2jetobjects.size()!=0);
    if(l2jetobjects.size()==0) assert(!passL2Jet);      
    
    if(!passL2Jet) {
       if(get_debug()>1) {
          std::cout << "the L2 failed for "<<L2_name 
                    <<  "  --> Check if this is a XE chain!" << std::endl;
       }	
       
       int xethr;
       bool isL2xe = IsL2XE(L2_name,xethr);
       if(!isL2xe) {
          if(get_debug()>1) {
             std::cout << L2_name << " is not a L2 xe name!"
                       << "  --> this L2 name "<< L2_name<< " failed the L2 in TrigJetXEChain!" <<std::endl;
          }
          return false;
       }
       if(get_debug()>1) std::cout << L2_name << "TrigJetXEChain is a L2 xe name" << std::endl;
       passL2xe =  evt.l2_met() > xethr ? true : false;
       
       if(get_debug()>1) {
          std::cout << "TrigJetXEChain result for L2 name "<< L2_name 
                    << " with L2 met = "<<evt.l2_met()<<" --> "<<passL2xe<<std::endl;	
       }
       if(!passL2xe) return false;
       
       
    }
    
    if(get_debug()>1) {
      std::cout << "this "<<L2_name<<" passed L2 as L2XE="<<passL2xe<< " or L2Jet="<<passL2Jet<<std::endl;
    }	    

    //it cannot pass both!
    assert(!(passL2xe && passL2Jet));
    
    //but it needs to have passed one at this stage!
    assert(passL2xe||passL2Jet);

    //Since the L2xe is not seeded by direct ROIs I can go to the next L2_name  here if this was passed
    if(passL2xe) {
       if(get_debug()>1) {
          std::cout << "this "<<L2_name<<" passed L2 as L2XE="<<passL2xe<< std::endl;
       }	    
       continue;
    }
    
    //This is a L2Jet name 
    
    assert(passL2Jet);
    
    //-> find L1 seeds
    
    std::string L1_name = (L2_names.at(i))[1];
    
    assert(l2jetobjects.size()>0);
    
    if(get_debug()>1) std::cout << " lets check for L1 seed from name " << L1_name<<std::endl;
    
    //this name MUST exist in L1!
    std::vector<std::string>::const_iterator foundL1 = std::find(L1_names.begin(), L1_names.end(),L1_name);
    if(foundL1==L1_names.end()) {
      std::cout<<"ERROR: THe L1 name " << L1_name << " was not found among L1 items for the L2 name " << L2_name << std::endl;exit(-1);
    }
    
    //Find the L1 objects that is seeding
    std::vector<const L1Jet*> l1jetobjs;
    bool passl1_tmp =  GetL1JetItems(evt,L1_name,l1jetobjs);
    if(get_debug()>1) {
      std::cout << "TrigJetXEChain for L2_name="<<L2_name<<" with L1Name "<<L1_name<<" pass="<<passl1_tmp<<" with "<<l1jetobjs.size()<<" l1 jet objetcts"<<std::endl;
    }
    
    if(passl1_tmp) assert(l1jetobjs.size()!=0);
    if(l1jetobjs.size()==0) assert(!passl1_tmp);      
    
    //I think it needs to pass this but not 100%..      
    assert(passl1_tmp);
    
    //Now we have a set of L2 and L1 objects.
    //Make sure that each L2 is matched to a L1
    //Note that only the requires number of L2 objs need to be matched
    
    //This is just to get the number of L2 required to pass the trigger!
    int N,thr;
    bool isL2Jet = IsL2Jet(L2_name,N,thr);
    
    assert(isL2Jet);
    
    if(get_debug()>1) {
      std::cout << "We need "<<N<<" matched L2 objects and we have " 
		<< l2jetobjects.size() << " L2 jets passing the cuts and "
		<< l1jetobjs.size() << " L1 jets "<<std::endl;
    }
    
    std::vector<const Jet*> l2jetobjects_matched;      
    for(size_t j=0;j!=l2jetobjects.size();++j) {
       for(size_t jL1=0;jL1!=l1jetobjs.size();++jL1) {
          double dr = l2jetobjects[j]->p.DeltaR(l1jetobjs[jL1]->p);
          if(dr < drMaxROI) {
             //this is matched to L1
             l2jetobjects_matched.push_back(l2jetobjects[j]);
             if(get_debug()>1) {
                std::cout << "l2 jet "<<j<<" is matched to l1 jet "<<jL1<<" with dr="<<dr
                          <<" (so far "<<l2jetobjects_matched.size()<<" matches)"<<std::endl;
             }
          }//dr
       }//jL1
    }//j
    
    //Now we can check how many that was matched to L1 and get the result      
    size_t matches = l2jetobjects_matched.size();
    
    bool L2JetPass = matches>=(size_t)N ? true : false;
    if(get_debug()>1) {
      std::cout << "The L2 name "<<L2_name<<" is a L2Jet with "<<matches<<" matched and requires "<<N
		<< " which gives the result= "<<L2JetPass<<std::endl;
    }      
    if(!L2JetPass) return false;
    
  } //loop over L2_names
  
  if(get_debug()>1) {
    std::cout << "The L2 seems to have passed all "<<L2_names.size()<<" so this trigger is passed!"<<std::endl;
  }     
  return true;
    
};


bool TrigJetXEChain::PassEF(AtlEvent& evt) const {
   if(get_debug()>1) {
    std::cout << "TrigJetXEChain in PassEF()" <<std::endl;
   }
   //assume it passed L1 & L2!
   // don't use jets at EF yet!
   
   // Now go through each of the EF names
   // check if those exist and passes
   // It will either be a XE or jet trigger!
   for(size_t i=0;i!=EF_names.size();++i) {
      assert((EF_names.at(i)).size()==3); // [EF_name][L2_name],[L1_name]
      std::string EF_name = (EF_names.at(i))[0];
      
      if(get_debug()>1) {
         std::cout << "EFName "<<EF_name<<std::endl;
      }
      
      bool passEFxe = false;
      bool passEFJet = false;
      
     // Is this a jet trigger? 
     // Use only L2 so far! so check the name and pass through!
     int N,thr;
     bool isEFJet = IsEFJet(EF_name,N,thr);
     if(isEFJet) passEFJet = true;


     if(!isEFJet) { 
        if(debug_var>1) {
           std::cout << "TrigJetXEChain PaSSEF  "<<EF_name<<" is not a EF jet name!"<<std::endl;
        }
        if(get_debug()>1) {
           std::cout << "EFName "<<EF_name<<"pass="<<passEFJet<<std::endl;
        }
        
        if(get_debug()>1) {
           std::cout << "the EF failed for "<<EF_name 
                     <<  "  --> Check if this is a XE chain!" << std::endl;
        }	
        
        int xethr;
        bool isEFxe = IsEFXE(EF_name,xethr);
        if(!isEFxe) {
           if(get_debug()>1) {
              std::cout << EF_name << " is not a EF xe name!"
                        << "  --> this EF name "<< EF_name<< " failed the EF in TrigJetXEChain!" <<std::endl;
           }
           return false;
        }
        if(get_debug()>1) std::cout << EF_name << "TrigJetXEChain is a EF xe name" << std::endl;
        passEFxe =  evt.ef_met() > xethr ? true : false;
        
        if(get_debug()>1) {
           std::cout << "TrigJetXEChain result for EF name "<< EF_name 
                     << " with EF met = "<<evt.l2_met()<<" --> "<<passEFxe<<std::endl;	
        }
        if(!passEFxe) return false;
        
        
     }
     
     if(get_debug()>1) {
        std::cout << "this "<<EF_name<<" passed EF as EFXE="<<passEFxe<< " or EFJet="<<passEFJet<<std::endl;
     }	    
     
     //it cannot pass both!
     assert(!(passEFxe && passEFJet));
     
     //but it needs to have passed one at this stage!
     assert(passEFxe||passEFJet);
     
     //Since the EFxe is not seeded by direct ROIs I can go to the next EF_name  here if this was passed
     if(passEFxe) {
        if(get_debug()>1) {
           std::cout << "this "<<EF_name<<" passed EF as EFXE="<<passEFxe<< std::endl;
        }	    
        continue;
     }
     
     //This is a EFJet name 
     
     assert(passEFJet);
     
     // The EF jet does not look at ROIs so if it is passed I will go to next EF_name
     // This assumes that the L1/L2 was passed -> Is this correct?

     if(passEFJet) {
        if(get_debug()>1) {
           std::cout << "this "<<EF_name<<" passed EF as EFJet="<<passEFJet<< std::endl;
        }	    
        continue;
     }
     
  } //loop over EF_names
  
  if(get_debug()>1) {
     std::cout << "The EF seems to have passed all "<<EF_names.size()<<" so this trigger is passed!"<<std::endl;
  }     
  return true;
    
};




bool TrigJetChain::PassL1(AtlEvent& evt) const {
    if(L1_names.size()==0) {
      std::cout << "TrigChain ERROR: no L1 names!"<< std::endl; exit(-1);
    }
    if(get_debug()>1) {
      std::cout << "TrigChain in PassL1()" << std::endl;
      std::cout << "PassL1 L1_names: ";
      for(size_t i=0;i!=L1_names.size();++i) {std::cout << L1_names.at(i) << "";}
      std::cout<<std::endl;      
    }
    
    //Loop over each L1 name
    for(size_t i =0;i!=L1_names.size();++i) {
      std::string L1_name = L1_names.at(i);
      //Get vector of objects passing the L1 requirement
      std::vector<const L1Jet*> l1jetobjects;
      bool pass =  GetL1JetItems(evt,L1_name,l1jetobjects);
      if(get_debug()>1) {
	std::cout << "L1Name "<<L1_name<<" TrigChain in PassL1() pass="<<pass<<" with "<<l1jetobjects.size()<<" l1 jet objetcts"<<std::endl;
      }
      if(pass) assert(l1jetobjects.size()!=0);
      if(l1jetobjects.size()==0) assert(!pass);      
      if(get_debug()>1) {
	std::cout << "TrigChain PassL1() result = "<<pass<<std::endl;
      }
      if(!pass) return false;
    }
    if(get_debug()>1) {
      std::cout << "TrigChain PassL1() passed all l1 names"<<std::endl;
    }
    return true; 
  };


bool TrigL2BJetChain::PassL1(AtlEvent& evt) const {
  if(L1_names.size()==0) {
    std::cout << "TrigL2BJetChain ERROR: no L1 names!"<< std::endl; exit(-1);
  }
  if(get_debug()>1) {
    std::cout << "TrigL2BJetChain in PassL1()" << std::endl;
    std::cout << "PassL1 L1_names: ";
    for(size_t i=0;i!=L1_names.size();++i) {std::cout << L1_names.at(i) << "";}
    std::cout<<std::endl;      
  }
  
  //Loop over each L1 name
  for(size_t i =0;i!=L1_names.size();++i) {
    std::string L1_name = L1_names.at(i);
    //Get vector of objects passing the L1 requirement
    std::vector<const L1Jet*> l1jetobjects;
    bool pass =  GetL1JetItems(evt,L1_name,l1jetobjects);
    if(get_debug()>1) {
      std::cout << "L1Name "<<L1_name<<" TrigL2BJetChain in PassL1() pass="<<pass<<" with "<<l1jetobjects.size()<<" l1 jet objetcts"<<std::endl;
    }
    if(pass) assert(l1jetobjects.size()!=0);
    if(l1jetobjects.size()==0) assert(!pass);      
    if(get_debug()>1) {
      std::cout << "TrigL2BJetChain PassL1() result = "<<pass<<std::endl;
    }
    if(!pass) return false;
  }
  if(get_debug()>1) {
    std::cout << "TrigL2BJetChain PassL1() passed all l1 names"<<std::endl;
  }
  return true; 
};


bool TrigJetChain::PassL2(AtlEvent& evt) const {
    if(get_debug()>1) {
      std::cout << "TrigJetChain in PassL2()" <<std::endl;
    }
    //First Check if L1 was passed -> NO, assume that its checked!
//     bool passl1 = PassL1(evt);
//     if(!passl1) {
//        if(get_debug()>1) {std::cout << "TrigChain in PassL2() did not pass the L1 so it fails L2!" << std::endl;}
//        exit(-1);
//     }
    if(get_debug()>1) {
      std::cout << "TrigChain in PassL2() passes L1." <<std::endl;
    }
    //Now go through each of the L2 names
    //check if those exist and passes
    // then find the L1 objects that is suppose to seed the L2
    // and check if the L2 that passed are seeded correctly    
    for(size_t i=0;i!=L2_names.size();++i) {
      assert((L2_names.at(i)).size()==2); // [L2_name],[L1_name]
      std::string L2_name = (L2_names.at(i))[0];
      //Get vector of objects passing the L2 requirement
      std::vector<const Jet*> l2jetobjects;
      bool pass =  GetL2JetItems(evt,L2_name,l2jetobjects);
      if(get_debug()>1) {
         std::cout << "L2Name "<<L2_name<<"pass="<<pass<<" with "<<l2jetobjects.size()<<" l2 jet objetcts"<<std::endl;
      }
      if(pass) assert(l2jetobjects.size()!=0);
      if(l2jetobjects.size()==0) assert(!pass);      
      if(!pass) {
         if(get_debug()>1) {
            std::cout << "the L2 failed for "<<L2_name<<" and so the whole L2 failed"<<std::endl;
         }	
         return false;
      }
      std::string L1_name = (L2_names.at(i))[1];
      if(get_debug()>1) {
         std::cout << "this L2 passed for "<<L2_name<<" , lets check for L1 seed from name " << L1_name<<std::endl;
      }	
      //this name MUST exist in L1!
      std::vector<std::string>::const_iterator foundL1 = std::find(L1_names.begin(), L1_names.end(),L1_name);
      if(foundL1==L1_names.end()) {
         std::cout<<"ERROR: THe L1 name " << L1_name << " was not found among L1 items for the L2 name " << L2_name << std::endl;exit(-1);
      }
      //Find the L1 objects that is seeding
      std::vector<const L1Jet*> l1jetobjs;
      bool passl1_tmp =  GetL1JetItems(evt,L1_name,l1jetobjs);
      if(get_debug()>1) {
         std::cout << "L1Name "<<L1_name<<" TrigChain in PassL2() pass="<<passl1_tmp<<" with "<<l1jetobjs.size()<<" l1 jet objetcts"<<std::endl;
      }
      if(passl1_tmp) assert(l1jetobjs.size()!=0);
      if(l1jetobjs.size()==0) assert(!passl1_tmp);      
      //I think it needs to pass this but not 100%..      
      assert(passl1_tmp);

      //Now we have a set of L2 and L1 objects.
      //Make sure that each L2 is matched to a L1
      //Note that only the requires number of L2 objs need to be matched
      
      //This is just to get the number of L2 required to pass the trigger!
      int N,thr;
      bool isL2Jet = IsL2Jet(L2_name,N,thr);
      assert(isL2Jet);
      if(get_debug()>1) {
	std::cout << "We need "<<N<<" matched L2 objects and we have " 
		  << l2jetobjects.size() << " L2 jets passing the cuts and "
		  <<l1jetobjs.size() << " L1 jets "<<std::endl;
      }
      std::vector<const Jet*> l2jetobjects_matched;      
      for(size_t j=0;j!=l2jetobjects.size();++j) {
	for(size_t jL1=0;jL1!=l1jetobjs.size();++jL1) {
	  double dr = l2jetobjects[j]->p.DeltaR(l1jetobjs[jL1]->p);
	  if(dr < drMaxROI) {
	    //this is matched to L1
	    l2jetobjects_matched.push_back(l2jetobjects[j]);
	    if(get_debug()>1) {
	      std::cout << "l2 jet "<<j<<" is matched to l1 jet "<<jL1<<" with dr="<<dr
			<<" (so far "<<l2jetobjects_matched.size()<<" matches)"<<std::endl;
	    }
	  }//dr
	}//jL1
      }//j
      
      //Now we can check how many that was matched to L1 and get the result
      
      size_t matches = l2jetobjects_matched.size();
      bool result = matches>=(size_t)N ? true : false;
      if(get_debug()>1) {
	std::cout << "lThe L2 name "<<L2_name<<" has "<<matches<<" and requires "<<N
		  << " which gives the result= "<<result<<std::endl;
      }      
      if(!result) return false;
    }
    
    if(get_debug()>1) {
      std::cout << "The L2 seems to have passed all "<<L2_names.size()<<" so this trigger is passed!"<<std::endl;
    }      
    return true;
    
    
};



bool TrigL2BJetChain::PassL2(AtlEvent& evt) const {
  if(get_debug()>1) {
    std::cout << "TrigL2BJetChain in PassL2()" <<std::endl;
  }
  //First Check if L1 was passed
  bool passl1 = PassL1(evt);
  if(!passl1) {
    if(get_debug()>1) {
      std::cout << "TrigL2BJetChain in PassL2() did not pass the L1 so it fails L2!" << std::endl;
    }
    return false;
  }
  if(get_debug()>1) {
    std::cout << "TrigL2BJetChain in PassL2() passes L1." <<std::endl;
  }
  //Now go through each of the L2 names
  //check if those exist and passes
  // then find the L1 objects that is suppose to seed the L2
  // and check if the L2 that passed are seeded correctly    
  for(size_t i=0;i!=L2_names.size();++i) {
    assert((L2_names.at(i)).size()==2); // [L2_name],[L1_name]
    std::string L2_name = (L2_names.at(i))[0];
    //Get vector of objects passing the L2 requirement
    std::vector<const L2BJet*> l2jetobjects;
    bool pass =  GetL2BJetItems(evt,L2_name,l2jetobjects);
    if(get_debug()>1) {
      std::cout << "L2Name "<<L2_name<<"pass="<<pass<<" with "<<l2jetobjects.size()<<" l2 jet objects"<<std::endl;
    }
    if(pass) assert(l2jetobjects.size()!=0);
    if(l2jetobjects.size()==0) assert(!pass);      
    if(!pass) {
      if(get_debug()>1) {
	std::cout << "the L2 failed for "<<L2_name<<" and so the whole L2 failed"<<std::endl;
      }	
      return false;
    }
    std::string L1_name = (L2_names.at(i))[1];
    if(get_debug()>1) {
      std::cout << "this L2 passed for "<<L2_name<<" , lets check for L1 seed from name " << L1_name<<std::endl;
    }	
    //this name MUST exist in L1!
    std::vector<std::string>::const_iterator foundL1 = std::find(L1_names.begin(), L1_names.end(),L1_name);
    if(foundL1==L1_names.end()) {
      std::cout<<"ERROR: THe L1 name " << L1_name << " was not found among L1 items for the L2 name " << L2_name << std::endl;
      exit(-1);
    }
    //Find the L1 objects that is seeding
    std::vector<const L1Jet*> l1jetobjs;
    bool passl1_tmp =  GetL1JetItems(evt,L1_name,l1jetobjs);
    if(get_debug()>1) {
      std::cout << "L1Name "<<L1_name<<" TrigL2BJetChain in PassL2() pass="<<passl1_tmp<<" with "<<l1jetobjs.size()<<" l1 jet objetcts"<<std::endl;
    }
    if(passl1_tmp) assert(l1jetobjs.size()!=0);
    if(l1jetobjs.size()==0) assert(!passl1_tmp);      
    //I think it needs to pass this but not 100%..      
    assert(passl1_tmp);
    
    //Now we have a set of L2 and L1 objects.
    //Make sure that each L2 is matched to a L1
    //Note that only the requires number of L2 objs need to be matched to pass the trigger
    
    //This is just to get the number of L2 required to pass the trigger!
    int N;
    std::string type;
    bool isL2BJet = IsL2BJet(L2_name,type,N);
    assert(isL2BJet);
    if(get_debug()>1) {
       std::cout << "We need "<<N<<" matched L2Bjet objects and we have " 
                 << l2jetobjects.size() << " L2Bjets passing the cuts and "
                 << l1jetobjs.size() << " L1 jets "<<std::endl;
    }
    std::vector<const L2BJet*> l2jetobjects_matched;      
    for(size_t j=0;j!=l2jetobjects.size();++j) {
       for(size_t jL1=0;jL1!=l1jetobjs.size();++jL1) {
          double dr = l2jetobjects[j]->p.DeltaR(l1jetobjs[jL1]->p);
          if(dr < drMaxROI) {
             //this is matched to L1
             l2jetobjects_matched.push_back(l2jetobjects[j]);
             if(get_debug()>1) {
                std::cout << "L2bjet "<<j<<" is matched to L1 jet "<<jL1<<" with dr="<<dr
                          <<" (so far "<<l2jetobjects_matched.size()<<" matches)"<<std::endl;
             }
          }//dr
       }//jL1
    }//j
    
    //Now we can check how many that was matched to L1 and get the result
    
    size_t matches = l2jetobjects_matched.size();
    bool result = matches>=(size_t)N ? true : false;
    if(get_debug()>1) {
       std::cout << "The L2 name "<<L2_name<<" has "<<matches<<" and requires "<<N
                 << " which gives the result= "<<result<<std::endl;
    }      
    if(!result) return false;
  }
  
  if(get_debug()>1) {
     std::cout << "The L2 seems to have passed all "<<L2_names.size()<<" so this trigger is passed!"<<std::endl;
  }      
  return true;
  
};
