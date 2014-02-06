#include "Topology_jetmetbtag.h"
#include <iomanip>
#include <cstdio>

static const bool CUT_MINIMAL=true; // Minimal event selection
static const bool BOOK_DETAIL=false; // Detailed booking
static const bool BOOK_CONTROL=false; // Book control regoins
static const bool BOOK_SUSY=false; // Book SUSY selection


static const double SV0CUT = 6.0;
static const double SV1IP3DCUT = 4.0;
static const TString tagratesys[3] = {"","STATU","STATD"};

static const bool DO_TAGRATES=false;
static const bool DO_ONLY_TRUTH=false;
static const bool DO_TRUTH=false;
static const bool DO_TT = false;
static const bool DO_SUSY = true;
static const bool DO_SUSY_0L_4JET = false;
static const bool DO_SUSY_TIGHT = false;


void Topology_jetmetbtag::cut(const TString & prefix) {

   if(get_debug()) cout << "cut prefix=" << prefix << endl;
   //This is where you make your cuts

   if(DO_ONLY_TRUTH) assert(DO_TRUTH);

   book(prefix,"");      
   book(prefix,"_truth");   

   bool passSUSYLeptonVeto = false;  
   bool TruthpassSUSYLeptonVeto = false;  
   
   if(leptons()==0) passSUSYLeptonVeto=true;
   else if(lepton(0)->p.Pt()<10.0) passSUSYLeptonVeto=true;
   else passSUSYLeptonVeto = false;
   
   if(DO_TRUTH) {
      if(leptons(true)==0) TruthpassSUSYLeptonVeto=true;
      else if(lepton(0,true)->p.Pt()<10.0) TruthpassSUSYLeptonVeto=true;
      else TruthpassSUSYLeptonVeto = false;
   }
   
   
   if(DO_SUSY) {
      
      for(int iTru=0;iTru!=2;++iTru) {
         bool isTru = (bool) iTru;
         if(isTru && !DO_TRUTH) continue;
         if(DO_ONLY_TRUTH && !isTru) continue;
         
         if((isTru&&TruthpassSUSYLeptonVeto) || (!isTru&&passSUSYLeptonVeto) ) {                                 
            book(prefix,isTru?"susytruth_0l":"susy0l");
            


            if(DO_SUSY_0L_4JET) {
               
               if( jets(isTru)>=1 ) {
                  if(jet(0,isTru).p.Pt() > 70.0) {                        
                     book(prefix,isTru?"susytruth_0l1j70":"susy0l1j70");
                     if( jets(isTru)>=2 ) {
                        if(jet(1,isTru).p.Pt() > 30.0) {
                           book(prefix,isTru?"susytruth_0l2j7030":"susy0l2j7030");
                           if( jets(isTru)>=3 ) {
                              if(jet(2,isTru).p.Pt() > 30.0) {
                                 book(prefix,isTru?"susytruth_0l3j7030":"susy0l3j7030");
                                 if( jets(isTru)>=4 ) {
                                    if(jet(3,isTru).p.Pt() > 30.0) {
                                       book(prefix,isTru?"susytruth_0l4j7030":"susy0l4j7030");
                                       if(met(isTru) > 30.0) {            
                                          book(prefix,isTru?"susytruth_0l4j7030met30":"susy0l4j7030met30");
                                          //if(Sphericity()>0.2) {
                                          if(passSUSYJetMetDphiCut(false,3,0.2)) {                                          
                                             if(met()>0.2*EffectiveMass(false,0,4)  ) {
                                                book(prefix,isTru?"susytruth_0l4j7030met30dphimeff":"susy0l4j7030met30dphimeff");
                                                
                                                
                                                if(btags(isTru) >= 1)            
                                                   book(prefix,isTru?"susytruth_0l4j7030met30dphimeff1bi":"susy0l4j7030met30dphimeff1bi");
                                                if(btags(isTru) >= 2)            
                                                   book(prefix,isTru?"susytruth_0l4j7030met30dphimeff2bi":"susy0l4j7030met30dphimeff2bi");
                                                if(btags(isTru) == 0)            
                                                   book(prefix,isTru?"susytruth_0l4j7030met30dphimeff0b":"susy0l4j7030met30dphimeff0b");
                                                if(btags(isTru) == 1)            
                                                   book(prefix,isTru?"susytruth_0l4j7030met30dphimeff1b":"susy0l4j7030met30dphimeff1b");
                                                if(btags(isTru) == 2)            
                                                   book(prefix,isTru?"susytruth_0l4j7030met30dphimeff2b":"susy0l4j7030met30dphimeff2b");
                                                if(btags(isTru) == 3)            
                                                   book(prefix,isTru?"susytruth_0l4j7030met30dphimeff3b":"susy0l4j7030met30dphimeff3b");
                                                if(btags(isTru) == 4)            
                                                   book(prefix,isTru?"susytruth_0l4j7030met30dphimeff4b":"susy0l4j7030met30dphimeff4b");
                                                
                                                /*
                                                  if(passSUSYJetMetDphiCut(isTru,2,0.8)) {                                    
                                                  book(prefix,isTru?"susytruth_4j301j70met500ldphi":"susy4j301j70met500ldphi");
                                               
                                                  if(btags(isTru) == 0) {           
                                                  book(prefix,isTru?"susytruth_4j301j70met500ldphi0bt":"susy4j301j70met500ldphi0bt");
                                                  }
                                                  if(btags(isTru) == 1) {           
                                                  book(prefix,isTru?"susytruth_4j301j70met500ldphi1bt":"susy4j301j70met500ldphi1bt");
                                                  }
                                                  if(btags(isTru) >= 2) {           
                                                  book(prefix,isTru?"susytruth_4j301j70met500ldphi2btinc":"susy4j301j70met500ldphi2btinc");
                                                  }
                                                  if(btags(isTru) == 2) {           
                                                  book(prefix,isTru?"susytruth_4j301j70met500ldphi2bt":"susy4j301j70met500ldphi2bt");
                                                  }
                                                  if(btags(isTru) == 3) {           
                                                  book(prefix,isTru?"susytruth_4j301j70met500ldphi3bt":"susy4j301j70met500ldphi3bt");
                                                  }
                                                  if(btags(isTru) >= 4) {           
                                                  book(prefix,isTru?"susytruth_4j301j70met500ldphi4bt":"susy4j301j70met500ldphi4bt");
                                                  }
                                               
                                                  }
                                                  if(TMath::Abs( jet(0,isTru).p.DeltaPhi( met_p(isTru) ) ) < 0.2 && TMath::Abs( jet(1,isTru).p.DeltaPhi( met_p(isTru) ) ) < 0.2) {
                                                  book(prefix,isTru?"susytruth_4j301j70met500ldphi01inv":"susy4j301j70met500ldphi01inv");                                    
                                                  if(btags(isTru) == 1) {           
                                                  book(prefix,isTru?"susytruth_4j301j70met500ldphi01inv1bt":"susy4j301j70met500ldphi01inv1bt");
                                                  }
                                                  if(btags(isTru) >= 2) {           
                                                  book(prefix,isTru?"susytruth_4j301j70met500ldphi01inv2btinc":"susy4j301j70met500ldphi01inv2btinc");
                                                  }
                                                  }
                                                  }
                                                */
                                             }
                                          }
                                       }
                                    }
                                 }
                              }
                           }
                        }
                     }
                  }
               }
            } //0L 4jet
         } //lept veto
      } //isTru
   } //DO_SUSY

   if(DO_SUSY_TIGHT) {
      
      for(int iTru=0;iTru!=2;++iTru) {
         bool isTru = (bool) iTru;
         if(isTru && !DO_TRUTH) continue;
         if(DO_ONLY_TRUTH && !isTru) continue;
            
         if((isTru&&TruthpassSUSYLeptonVeto) || (!isTru&&passSUSYLeptonVeto) ) {                                 
            if( jets(isTru)>=1 ) {
               if(jet(0,isTru).p.Pt() > 100.0) {                        
                  book(prefix,isTru?"susytruth_0l1j100":"susy0l1j100");
                  if( jets(isTru)>=2 ) {
                     if(jet(1,isTru).p.Pt() > 40.0) {
                        book(prefix,isTru?"susytruth_0l2j10040":"susy0l2j10040");
                        if( jets(isTru)>=3 ) {
                           if(jet(2,isTru).p.Pt() > 40.0) {
                              book(prefix,isTru?"susytruth_0l3j10040":"susy0l3j10040");
                              if( jets(isTru)>=4 ) {
                                 if(jet(3,isTru).p.Pt() > 40.0) {
                                    book(prefix,isTru?"susytruth_0l4j10040":"susy0l4j10040");
                                    if(met(isTru) > 70.0) {            
                                       book(prefix,isTru?"susytruth_0l4j10040met70":"susy0l4j10040met70");

                                       if(passSUSYJetMetDphiCut(false,3,0.2)) {                                          
                                          if(met()>0.2*EffectiveMass(false,0,4)  ) {
                                             book(prefix,isTru?"susytruth_0l4j10040met70dphimeff":"susy0l4j10040met70dphimeff");
                                             
                                             if(btags(isTru) >= 1)            
                                                book(prefix,isTru?"susytruth_0l4j10040met70dphimeff1bi":"susy0l4j10040met70dphimeff1bi");
                                             if(btags(isTru) >= 2)            
                                                book(prefix,isTru?"susytruth_0l4j10040met70dphimeff2bi":"susy0l4j10040met70dphimeff2bi");
                                             if(btags(isTru) == 0)            
                                                book(prefix,isTru?"susytruth_0l4j10040met70dphimeff0b":"susy0l4j10040met70dphimeff0b");
                                             if(btags(isTru) == 1)            
                                                book(prefix,isTru?"susytruth_0l4j10040met70dphimeff1b":"susy0l4j10040met70dphimeff1b");
                                             if(btags(isTru) == 2)            
                                                book(prefix,isTru?"susytruth_0l4j10040met70dphimeff2b":"susy0l4j10040met70dphimeff2b");
                                             if(btags(isTru) == 3)            
                                                book(prefix,isTru?"susytruth_0l4j10040met70dphimeff3b":"susy0l4j10040met70dphimeff3b");
                                             if(btags(isTru) == 4)            
                                                book(prefix,isTru?"susytruth_0l4j10040met70dphimeff4b":"susy0l4j10040met70dphimeff4b");
                                             
                                          }
                                       }
                                     
                                    }
                                 }
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }
   


   if(DO_TT) {

      for(int iTru=0;iTru!=2;++iTru) {
         bool isTru = (bool) iTru;
         if(isTru && !DO_TRUTH) continue;
         if(DO_ONLY_TRUTH && !isTru) continue;

      
         if( jets(isTru)>=1 ) {
            book(prefix,isTru?"truth_1j":"1j");
            if( jets(isTru)>=2 ) {
               //book(prefix,isTru?"truth_2j":"2j");
               if( jets(isTru)>=3 ) {
                  //book(prefix,isTru?"truth_3j":"3j");
                  if( jets(isTru)>=4 ) {
                     book(prefix,isTru?"truth_4j":"4j");
                     if(jet(0,isTru).p.Pt() > 20.0) {
                     
                        if(jet(2,isTru).p.Pt()>40.) book(prefix,isTru?"truth_4j3j40":"4j3j40"); 
                        if((isTru&&TruthpassSUSYLeptonVeto) || (!isTru&&passSUSYLeptonVeto) ) book(prefix,isTru?"truth_4j3j400l":"4j3j400l");
                     
                        if(met(isTru) > 40.0) {            
                           book(prefix,isTru?"truth_4jmet40":"4jmet40");
                           if(jet(0,isTru).p.Pt()>40.) {
                              book(prefix,isTru?"truth_4j1j40met40":"4j1j40met40"); 
                              if(jet(2,isTru).p.Pt()>40.) {
                                 book(prefix,isTru?"truth_4j3j40met40":"4j3j40met40"); 
                                 if(electrons(isTru) == 1) { 
                                    book(prefix,isTru?"truth_4j3j40met40e1":"4j3j40met40e1");                       
                                 }                          
                                 if(muons(isTru) == 1) { 
                                    book(prefix,isTru?"truth_4j3j40met40m1":"4j3j40met40m1");                       
                                 }                       
                                 if( btags(isTru)==1 ) {           
                                    book(prefix,isTru?"truth_4j3j40met401bt":"4j3j40met401bt");
                                    if(btags(isTru) >= 2) {           
                                       book(prefix,isTru?"truth_4j3j40met402bt":"4j3j40met402bt");
                                    }
                                 }
                                 if((isTru&&TruthpassSUSYLeptonVeto) || (!isTru&&passSUSYLeptonVeto) ) {                                 
                                    book(prefix,isTru?"truth_4j3j40met400l":"4j3j40met400l");
                                 
                                    if(passSUSYJetMetDphiCut(isTru,2,0.8)) {                                    
                                       book(prefix,isTru?"truth_4j3j40met400ldphi":"4j3j40met400ldphi");
                                    
                                       if(btags(isTru) == 0) {           
                                          book(prefix,isTru?"truth_4j3j40met400ldphi0bt":"4j3j40met400ldphi0bt");
                                       }
                                       if(btags(isTru) == 1) {           
                                          book(prefix,isTru?"truth_4j3j40met400ldphi1bt":"4j3j40met400ldphi1bt");
                                       }
                                       if(btags(isTru) >= 2) {           
                                          book(prefix,isTru?"truth_4j3j40met400ldphi2bt":"4j3j40met400ldphi2bt");
                                       }
                                    
                                    
                                       for(int isys=0;isys!=3;++isys) {
                                          TString sysName = tagratesys[isys];
                                          if(btags_pred("alp,pt,jmd",isTru,sysName.Data()) == 0) {           
                                             book(prefix,isTru?TString::Format("truth_4j3j40met400ldphi0btpalp%s",sysName.Data()):TString::Format("4j3j40met400ldphi0btpalp%s",sysName.Data()));
                                          }
                                          if(btags_pred("alp,pt,jmd",isTru,sysName.Data()) == 1) {           
                                             book(prefix,isTru?TString::Format("truth_4j3j40met400ldphi1btpalp%s",sysName.Data()):TString::Format("4j3j40met400ldphi1btpalp%s",sysName.Data()));
                                          }
                                          if(btags_pred("alp,pt,jmd",isTru,sysName.Data()) >= 2) {           
                                             book(prefix,isTru?TString::Format("truth_4j3j40met400ldphi2btpalp%s",sysName.Data()):TString::Format("4j3j40met400ldphi2btpalp%s",sysName.Data()));
                                          }
                                          if(btags_pred("pyt,pt,jmd",isTru,sysName.Data()) == 0) {           
                                             book(prefix,isTru?TString::Format("truth_4j3j40met400ldphi0btppyt%s",sysName.Data()):TString::Format("4j3j40met400ldphi0btppyt%s",sysName.Data()));
                                          }
                                          if(btags_pred("pyt,pt,jmd",isTru,sysName.Data()) == 1) {           
                                             book(prefix,isTru?TString::Format("truth_4j3j40met400ldphi1btppyt%s",sysName.Data()):TString::Format("4j3j40met400ldphi1btppyt%s",sysName.Data()));
                                          }
                                          if(btags_pred("pyt,pt,jmd",isTru,sysName.Data()) >= 2) {           
                                             book(prefix,isTru?TString::Format("truth_4j3j40met400ldphi2btppyt%s",sysName.Data()):TString::Format("4j3j40met400ldphi2btppyt%s",sysName.Data()));
                                          }

                                       }
                                    }
                                    //control sample?
                                    if(TMath::Abs( jet(0,isTru).p.DeltaPhi( met_p(isTru) ) ) < 0.2) {
                                       book(prefix,isTru?"truth_4j3j40met400ldphi0inv":"4j3j40met400ldphi0inv");                                    
                                       if(btags(isTru) == 1) {           
                                          book(prefix,isTru?"truth_4j3j40met400ldphi0inv1bt":"4j3j40met400ldphi0inv1bt");
                                       }
                                       if(btags(isTru) >= 2) {           
                                          book(prefix,isTru?"truth_4j3j40met400ldphi0inv2bt":"4j3j40met400ldphi0inv2bt");
                                       }
                                    }
                                    if(TMath::Abs( jet(1,isTru).p.DeltaPhi( met_p(isTru) ) ) < 0.2) {
                                       book(prefix,isTru?"truth_4j3j40met400ldphi1inv":"4j3j40met400ldphi1inv");                                    
                                       if(btags(isTru) == 0) {           
                                          book(prefix,isTru?"truth_4j3j40met400ldphi1inv0bt":"4j3j40met400ldphi1inv0bt");
                                       }
                                       if(btags(isTru) == 1) {           
                                          book(prefix,isTru?"truth_4j3j40met400ldphi1inv1bt":"4j3j40met400ldphi1inv1bt");
                                       }
                                       if(btags(isTru) >= 2) {           
                                          book(prefix,isTru?"truth_4j3j40met400ldphi1inv2bt":"4j3j40met400ldphi1inv2bt");
                                       }
                                    }
                                    if(TMath::Abs( jet(0,isTru).p.DeltaPhi( met_p(isTru) ) ) < 0.2 && TMath::Abs( jet(1,isTru).p.DeltaPhi( met_p(isTru) ) ) < 0.2) {
                                       book(prefix,isTru?"truth_4j3j40met400ldphi01inv":"4j3j40met400ldphi01inv");                                    
                                       if(btags(isTru) == 1) {           
                                          book(prefix,isTru?"truth_4j3j40met400ldphi01inv1bt":"4j3j40met400ldphi01inv1bt");
                                       }
                                       if(btags(isTru) >= 2) {           
                                          book(prefix,isTru?"truth_4j3j40met400ldphi01inv2bt":"4j3j40met400ldphi01inv2bt");
                                       }
                                    
                                    
                                    }
                                 
                                 }
                              }
                           }
                        }
                     
                        if(!CUT_MINIMAL) {
                        
                           // multijet sample?
                           if(met(isTru) < 25.0) {            
                           
                              if(jet(2,isTru).p.Pt()>40.) {
                                 if((isTru&&TruthpassSUSYLeptonVeto) || (!isTru&&passSUSYLeptonVeto) ) {                                 
                                    book(prefix,isTru?"truth_4j3j40meti250l":"4j3j40meti250l");
                                    if(btags(isTru) == 1) {           
                                       book(prefix,isTru?"truth_4j3j40meti250l1bt":"4j3j40meti250l1bt");
                                    }
                                    if(btags(isTru) >= 2) {           
                                       book(prefix,isTru?"truth_4j3j40meti250l2bt":"4j3j40meti250l2bt");
                                    }
                                 
                                    //control sample?
                                    if(TMath::Abs( jet(0,isTru).p.DeltaPhi( met_p(isTru) ) ) < 0.2) {
                                       book(prefix,isTru?"truth_4j3j40meti250ldphi0inv":"4j3j40meti250ldphi0inv");                                    
                                       if(btags(isTru) == 1) {           
                                          book(prefix,isTru?"truth_4j3j40meti250ldphi0inv1bt":"4j3j40meti250ldphi0inv1bt");
                                       }
                                       if(btags(isTru) >= 2) {           
                                          book(prefix,isTru?"truth_4j3j40meti250ldphi0inv2bt":"4j3j40meti250ldphi0inv2bt");
                                       }
                                    }
                                    if(TMath::Abs( jet(1,isTru).p.DeltaPhi( met_p(isTru) ) ) < 0.2) {
                                       book(prefix,isTru?"truth_4j3j40meti250ldphi1inv":"4j3j40meti250ldphi1inv");                                    
                                       if(btags(isTru) == 1) {           
                                          book(prefix,isTru?"truth_4j3j40meti250ldphi1inv1bt":"4j3j40meti250ldphi1inv1bt");
                                       }
                                       if(btags(isTru) >= 2) {           
                                          book(prefix,isTru?"truth_4j3j40meti250ldphi1inv2bt":"4j3j40meti250ldphi1inv2bt");
                                       }
                                    }
                                    if(TMath::Abs( jet(0,isTru).p.DeltaPhi( met_p(isTru) ) ) < 0.2 && TMath::Abs( jet(1,isTru).p.DeltaPhi( met_p(isTru) ) ) < 0.2) {
                                       book(prefix,isTru?"truth_4j3j40meti250ldphi01inv":"4j3j40meti250ldphi01inv");                                    
                                       if(btags(isTru) == 1) {           
                                          book(prefix,isTru?"truth_4j3j40meti250ldphi01inv1bt":"4j3j40meti250ldphi01inv1bt");
                                       }
                                       if(btags(isTru) >= 2) {           
                                          book(prefix,isTru?"truth_4j3j40meti250ldphi01inv2bt":"4j3j40meti250ldphi01inv2bt");
                                       }
                                    }
                                 }
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }





//    if(DO_SUSY) {
//       if( passSUSYLeptonVeto ) {
//          book(prefix,"susy0l");    
//          if( jets()>=4){
//             book(prefix,"susy0l4j");
//             if( jets()>=4 && jet(0).p.Pt()>70 && jet(3).p.Pt()>30 ) { 
//                book(prefix,"susy0l4jsoft");
//                if(met()>50) {
//                   book(prefix,"susy0l4jmetsoft");
//                   if(met()>0.2*EffectiveMass(false,0,4)) {
//                      book(prefix,"susy0l4jmetmeffsoft");
//                      if(Sphericity()>0.2) {
//                         book(prefix,"susy0l4jmetmeffsphsoft"); 
//                         if(passSUSYJetMetDphiCut(false,3,0.2)) {
//                            book(prefix,"susy0l4jmetmeffsphdphisoft"); 
//                            book(prefix,"susy0l4jfullsoft"); 
//                            if(btags() == 1) {           
//                               book(prefix,"susy0l4jmetmeffsphdphi1btsoft"); 
//                            }                                      
//                            if(btags() >= 2) {           
//                               book(prefix,"susy0l4jmetmeffsphdphi2btsoft"); 
//                               book(prefix,"susy0l4j2btfullsoft"); 
//                            }                                      
//                         }
//                      }
//                   }                 
//                }              
//             }     
//          }
//       }
//    }
   
   
}

void Topology_jetmetbtag::book(const TString & pre, const TString & suf) {
   
   if(get_debug()) cout << "book pre=" << pre << "  suf=" << suf << endl;
  
   //This is where you fill your histograms!
   
   //Tip: Keep a bool if you want automatically switch between truth and reco
   const bool isTru=suf.Contains("truth");
   
   
   // Use the name directory of one histograms to check if this is the 
   // first event
   
   if (gDirectory->Get(pre+suf+"_runnr")==0) {
      
      const TString key=pre+suf+"_";

      /* ======== BOOK HISTOGRAMS ========= */
      new TH1F(key+"runnr",";Run number;Enties",100,0.,1000000.);            

      //Jets
      new TH1F(key+"Jpt",";Jet p_{T} [GeV];Entries",100,0.,200.);
      new TH1F(key+"jpt",";Jet p_{T} [GeV];Entries",100,0.,600.);
      new TH1F(key+"bjpt",";b-jet p_{T} [GeV];Entries",100,0.,600.);
      new TH1F(key+"bjeta",";b-jet |#eta|;Entries",100,0.,5.);
      new TH1F(key+"cjpt",";c-jet p_{T} [GeV];Entries",100,0.,600.);
      new TH1F(key+"cjeta",";c-jet |#eta|;Entries",100,0.,5.);
      new TH1F(key+"ljpt",";light jet p_{T} [GeV];Entries",100,0.,600.);
      new TH1F(key+"ljeta",";light jet |#eta|;Entries",100,0.,5.);
      new TH1F(key+"jeta",";Jet #eta;Entries",100,-5.,5.);
      for(int i=0;i!=4;++i) {
         new TH1F(key+TString::Format("j%isv0",i),TString::Format(";Jet%i SV0;Entries",i),100,-15.,25.);
         new TH1F(key+TString::Format("j%ipt",i),TString::Format(";Jet%i p_{T} [GeV];Entries",i),100,0.,400.);
         new TH1F(key+TString::Format("j%ieta",i),TString::Format(";Jet%i #eta;Entries",i),100,-5.,5.);
         new TH1F(key+TString::Format("j%iphi",i),TString::Format(";Jet%i #phi;Entries",i),100,-5.,5.);
         new TH2F(key+TString::Format("j%ietaphi",i),TString::Format(";Jet%i #eta;Jet%i #eta",i,i),50,-5.,5.,50,-5.,5.);
         new TH1F(key+TString::Format("bj%ipt",i),TString::Format(";b-jet%i p_{T} [GeV];Entries",i),100,0.,400.);
         new TH1F(key+TString::Format("bj%ieta",i),TString::Format(";b-jet%i #eta;Entries",i),100,-5.,5.);
         new TH1F(key+TString::Format("bj%iphi",i),TString::Format(";b-jet%i #phi;Entries",i),100,-5.,5.);
      }
      new TH1F(key+"nj",";Number of jets;Entries",10,0.,10.);
      new TH1F(key+"nbj",";Number of matched b-jets;Entries",10,0.,10.);
      new TH1F(key+"ncj",";Number of matched c-jets;Entries",10,0.,10.);
      new TH1F(key+"nlj",";Number of matched light jets;Entries",10,0.,10.);
      new TH1F(key+"jgoodness",";Jet Goodness;Entries",5,0.,5.);

      new TH1F(key+"nbjparton",";Number of matched b-jets (parton-match);Entries",10,0.,10.);
      new TH1F(key+"ncjparton",";Number of matched c-jets (parton-match);Entries",10,0.,10.);
      new TH1F(key+"nljparton",";Number of matched light jets(parton-match);Entries",10,0.,10.);

      new TH1F(key+"nbjboth",";Number of matched b-jets (both parton-meson match);Entries",10,0.,10.);
      new TH1F(key+"ncjboth",";Number of matched c-jets (both parton-meson match);Entries",10,0.,10.);
      new TH1F(key+"nljboth",";Number of matched light jets(both parton-meson match);Entries",10,0.,10.);

      if(DO_TAGRATES) {
         
         //b-tagging
         new TH1F(key+"nbtagpredalppt",";Number of tags (predicted pT inclusice CM);Entries",5,0,5);
         new TH1F(key+"nbtagpredalpptstatup",";Number of tags (predicted STATU  pT inclusice CM);Entries",5,0,5);
         new TH1F(key+"nbtagpredalpptstatdown",";Number of tags (predicted STATD pT inclusice CM);Entries",5,0,5);
         
         new TH1F(key+"nbtagpredalpptjmd",";Number of tags (predicted pT,#Delta #phi(jet,#slash{E_{T}}) );Entries",5,0,5);
         new TH1F(key+"nbtagpredalpptjmdstatup",";Number of tags (predicted STATU  pT,#Delta #phi(jet,#slash{E_{T}}));Entries",5,0,5);
         new TH1F(key+"nbtagpredalpptjmdstatdown",";Number of tags (predicted STATD pT,#Delta #phi(jet,#slash{E_{T}}));Entries",5,0,5);
         
         new TH1F(key+"nbtagpredpytptjmd",";Number of tags (predicted pT,#Delta #phi(jet,#slash{E_{T}}) );Entries",5,0,5);
         new TH1F(key+"nbtagpredpytptjmdstatup",";Number of tags (predicted STATU  pT,#Delta #phi(jet,#slash{E_{T}}));Entries",5,0,5);
         new TH1F(key+"nbtagpredpytptjmdstatdown",";Number of tags (predicted STATD pT,#Delta #phi(jet,#slash{E_{T}}));Entries",5,0,5);
         
         new TH1F(key+"nbtagpredalpptdphi",";Number of tags (predicted pT for #Delta #phi(jet,#slash{E_{T}})>1.0 );Entries",5,0,5);
         new TH1F(key+"nbtagpredalpptdphistatup",";Number of tags (predicted pT STATU for #Delta #phi(jet,#slash{E_{T}})>1.0 );Entries",5,0,5);
         new TH1F(key+"nbtagpredalpptdphistatdown",";Number of tags (predicted pT STATD for #Delta #phi(jet,#slash{E_{T}})>1.0 );Entries",5,0,5);
         
         new TH1F(key+"nbtagpredalpptdphii",";Number of tags (predicted pT for #Delta #phi(jet,#slash{E_{T}})<1.0 );Entries",5,0,5);
         new TH1F(key+"nbtagpredalpptdphiistatup",";Number of tags (predicted pT STATU for #Delta #phi(jet,#slash{E_{T}})<1.0 );Entries",5,0,5);
         new TH1F(key+"nbtagpredalpptdphiistatdown",";Number of tags (predicted pT STATD for #Delta #phi(jet,#slash{E_{T}})<1.0 );Entries",5,0,5);

      }

      new TH1F(key+"nbtag",";Number of tags;Entries",5,0,5);
      new TH1F(key+"nbtag2incl",";Number of tags (#leq2 incl);Entries",5,0,5);
      new TH1F(key+"btagrank",";Rank (jet p_{T}) of b-tags;Entries",10,0,10);
      new TH1F(key+"jsv0",";Jet SV0;Entries",100,-15.,25.);
      new TH1F(key+"bjsv0",";B Matched Jet SV0;Entries",100,-15.,25.);
      new TH1F(key+"cjsv0",";D Matched Jet SV0;Entries",100,-15.,25.);
      new TH1F(key+"ljsv0",";L Matched Jet SV0;Entries",100,-15.,25.);
      new TH1F(key+"btagpt",";b-tagged jet p_{T} [GeV];Entries",100,0.,400.);
      new TH1F(key+"btageta",";b-tagged jet #eta;Entries",100,-5.,5.);
      
      new TH1F(key+"jsv1ip3d",";Jet SV1IP3D;Entries",100,-10.,15.);
      new TH1F(key+"bjsv1ip3d",";B Matched Jet SV1IP3D;Entries",100,-10.,15.);
      new TH1F(key+"cjsv1ip3d",";D Matched Jet SV1IP3D;Entries",100,-10.,15.);
      new TH1F(key+"ljsv1ip3d",";L Matched Jet SV1IP3D;Entries",100,-10.,15.);
      new TH1F(key+"bjbtagrank",";Rank (jet p_{T}) of b-tags for b-jets;Entries",10,0,10);
      new TH1F(key+"cjbtagrank",";Rank (jet p_{T}) of b-tags for c-jets;Entries",10,0,10);
      new TH1F(key+"ljbtagrank",";Rank (jet p_{T}) of b-tags for light jets;Entries",10,0,10);
      new TH1F(key+"bjrank",";Rank (jet p_{T}) of b-jets;Entries",10,0,10);
      new TH1F(key+"cjrank",";Rank (jet p_{T}) of c-jets;Entries",10,0,10);
      new TH1F(key+"ljrank",";Rank (jet p_{T}) of light jets;Entries",10,0,10);
      new TH1F(key+"mbtbt",";M(b-tagged jet_{0},b-tagged jet_{1});Entries",100,0.,600.);
      new TH1F(key+"dphibtbt",";#Delta #phi(b-tagged jet_{%i},b-tagged jet_{%i});Entries",100,0.,TMath::Pi());
      new TH1F(key+"drbtbt",";#DeltaR(b-tagged jet_{%i},b-tagged jet_{%i});Entries",100,0.0,5.0);      
      new TH1F(key+"dphibt0met",";#Delta #phi(b-tagged jet_{0},#slash{E_{T}});Entries",100,0.,TMath::Pi());
      new TH1F(key+"dphibt1met",";#Delta #phi(b-tagged jet_{1},#slash{E_{T}});Entries",100,0.,TMath::Pi());

      new TH1F(key+"jflavor",";Jet flavor;Entries",32,-16.,16);
      new TH1F(key+"jflavorman",";Jet flavor (manual);Entries",32,-16.,16);
      
      new TH1F(key+"bjrecopt",";b Jet p_{T} [GeV];Entries",100,0.,400.);
      new TH1F(key+"bjrecotaggedpt",";b Jet (tagged) p_{T} [GeV];Entries",100,0.,400.);
      new TH1F(key+"bjrecotaggedsv1ip3dpt",";b Jet (tagged SV1IP3D) p_{T} [GeV];Entries",100,0.,400.);
      new TH1F(key+"bjrecol2ip3dpt",";b Jet (matched to L2 b-jet) p_{T} [GeV];Entries",100,0.,400.);
      new TH1F(key+"bjrecotaggedl2ip3dpt",";b Jet (tagged L2 IP3D) p_{T} [GeV];Entries",100,0.,400.);
      new TH1F(key+"bjrecoeta",";b Jet #eta;Entries",100,-5.,5.);
      new TH1F(key+"bjrecotaggedeta",";b Jet (tagged) #eta;Entries",100,-5.,5.);
      new TH1F(key+"bqjrecopt",";b Jet p_{T} [GeV];Entries",100,0.,400.);
      new TH1F(key+"bqjrecotaggedpt",";b Jet (tagged) p_{T} [GeV];Entries",100,0.,400.);
      new TH1F(key+"bqjrecotaggedsv1ip3dpt",";b Jet (tagged SV1IP3D) p_{T} [GeV];Entries",100,0.,400.);
      new TH1F(key+"bqjrecol2ip3dpt",";b Jet (matched to L2 b-jet) p_{T} [GeV];Entries",100,0.,400.);
      new TH1F(key+"bqjrecotaggedl2ip3dpt",";b Jet (tagged L2 IP3D) p_{T} [GeV];Entries",100,0.,400.);
      new TH1F(key+"bqjrecoeta",";b Jet #eta;Entries",100,-5.,5.);
      new TH1F(key+"bqjrecotaggedeta",";b Jet (tagged) #eta;Entries",100,-5.,5.);


      new TH1F(key+"bjbhadcount4",";B hadrons in 0.4 cone of tagged jet;Entries",5,0.,5);
      new TH1F(key+"bjchadcount4",";C hadrons in 0.4 cone of tagged jet;Entries",5,0.,5);
      
      
      //Leptons
      new TH1F(key+"nl",";Number of leptons;Entries",10,0.,10.);
      new TH1F(key+"ne",";Number of electrons;Entries",10,0.,10.);
      new TH1F(key+"nm",";Number of muons;Entries",10,0.,10.);
      new TH1F(key+"etrupt",";Truth electron p_{T} [GeV];Entries",100,0.,100.);
      new TH1F(key+"etrurecomatchpt",";Reco matched truth electron p_{T} [GeV];Entries",100,0.,100.);
      new TH1F(key+"etrueta",";Truth electron |#eta|;Entries",100,0.,5.);
      new TH1F(key+"etrurecomatcheta",";Reco matched truth electron |#eta|;Entries",100,0.,5.);
      new TH1F(key+"mtrupt",";Truth muon p_{T} [GeV];Entries",100,0.,100.);
      new TH1F(key+"mtrurecomatchpt",";Reco matched truth muon p_{T} [GeV];Entries",100,0.,100.);
      new TH1F(key+"mtrueta",";Truth muon |#eta|;Entries",100,0.,5.);
      new TH1F(key+"mtrurecomatcheta",";Reco matched truth muon |#eta|;Entries",100,0.,5.);
      
      
      
      //event variables
      new TH1F(key+"met",";Etmiss [GeV];Entries",100,0.,800.);
      new TH1F(key+"Met",";Etmiss [GeV];Entries",100,0.,200.);
      new TH1F(key+"ht",";HT [GeV];Entries",100,0.,800.);
      new TH1F(key+"Ht",";HT [GeV];Entries",100,0.,800.);
      new TH1F(key+"mht",";Missing HT [GeV];Entries",100,0.,800.);
      new TH1F(key+"Mht",";Missing HT [GeV];Entries",100,0.,200.);
      
      for(int i=0;i!=4;++i) {      
         for(int j=0;j!=4;++j) {               
            if(i<=j) continue;
            new TH1F(key+TString::Format("dphij%ij%i",i,j),TString::Format(";#Delta #phi(jet_{%i},jet_{%i});Entries",i,j),100,0.,TMath::Pi());
            new TH1F(key+TString::Format("mj%ij%i",i,j),TString::Format(";M(jet_{%i},jet_{%i});Entries",i,j),100,0.,600.);
            new TH1F(key+TString::Format("dphibj%ibj%i",i,j),TString::Format(";#Delta #phi(b-jet_{%i},b-jet_{%i});Entries",i,j),100,0.,TMath::Pi());
            new TH1F(key+TString::Format("drbj%ibj%i",i,j),TString::Format(";#DeltaR(b-jet_{%i},b-jet_{%i});Entries",i,j),100,0.,5.);
            new TH1F(key+TString::Format("mbj%ibj%i",i,j),TString::Format(";M(b-jet_{%i},b-jet_{%i}) [GeV];Entries",i,j),100,0.,600.);

         }
         new TH1F(key+TString::Format("dphibj%imet",i),TString::Format(";#Delta #phi(b-jet_{%i},MET);Entries",i),100,0.,TMath::Pi());
         new TH1F(key+TString::Format("dphij%imet",i),TString::Format(";#Delta #phi(jet_{%i},MET);Entries",i),100,0.,TMath::Pi());
         new TH1F(key+TString::Format("dphij%imht",i),TString::Format(";#Delta #phi(jet_{%i},MHT);Entries",i),100,0.,TMath::Pi());
         new TH2F(key+TString::Format("metdphij%imet",i),TString::Format(";#Delta #phi(jet_{%i},MET);MET",i),50,0.,TMath::Pi(),50,0.,200.);
         new TH2F(key+TString::Format("j%idphij%imet",i,i),TString::Format(";#Delta #phi(jet_{%i},MET);jet_{%i} p_{T} [GeV]",i,i),50,0.,TMath::Pi(),50,0.,400.);
      }
      new TH1F(key+"dphij01met",";#Delta #phi(jet_{0,1},MET);Entries",100,0.,TMath::Pi());
      
      new TH1F(key+"meff4",";M_{eff,4} [GeV];Entries",100,0.,800.);
      new TH1F(key+"Meff4",";M_{eff,4} [GeV];Entries",100,0.,1200.);
      
      new TH1F(key+"sph","TSphericity;Tr. sphericity;Events",100,0.,1.);
      new TH1F(key+"trackpt","Track p_{T};Track p_{T} [GeV];Events",100,0.,20.);
      new TH1F(key+"sumtrackpt","Sum of track p_{T};Sum of track p_{T} [GeV];Events",100,0.,150.);
      new TH1F(key+"mettrack","#slash{p_{T}};#slash{p_{T}} [GeV];Events",100,0.,150.);

      new TH1F(key+"htasym","#slash{H_{T}} asym;A=(#slash{H_{T}} - #slash{E_{T}})/(#slash{H_{T}} + #slash{E_{T}}));Events",100,-1.1,1.1);
      new TH2F(key+"htmet","#slash{H_{T}} vs #slash{E_{T}};#slash{E_{T}} [GeV];#slash{H_{T}} [Gev]",100,0.,200.,50,0.,600.);
      new TH1F(key+"dphiptmet","#Delta #phi(#slash{p_{T}},#slash{E_{T}}) ;Events",100,0.,TMath::Pi());
      new TH1F(key+"dphijetsmet","#Delta #phi(jets,#slash{E_{T}}) ;Events",100,0.,TMath::Pi());



      //rag rate function 
      if(DO_TAGRATES) {
         new TH1F(key+"tagraterecopt",";Jet p_{T} [GeV];Entries",100,0.,200.);
         new TH1F(key+"tagraterecotaggedpt",";Jet (tagged) p_{T} [GeV];Entries",100,0.,200.);
         new TH1F(key+"tagraterecoeta",";Jet #eta;Entries",100,0.,2.5);
         new TH1F(key+"tagraterecotaggedeta",";Jet (tagged) #eta;Entries",100,0.,2.5);
         new TH1F(key+"tagratedphirecopt",";Jet p_{T} (|#Delta#phi(jet,#slash{E_{T}})| large) [GeV];Entries",100,0.,200.);
         new TH1F(key+"tagratedphirecotaggedpt",";Tagged jet (|#Delta#phi(jet,#slash{E_{T}})| large) p_{T} [GeV];Entries",100,0.,200.);
         new TH1F(key+"tagratedphirecoeta",";Jet (|#Delta#phi(jet,#slash{E_{T}})| large) #eta;Entries",100,0.,2.5);
         new TH1F(key+"tagratedphirecotaggedeta",";Tagged jet #eta (|#Delta#phi(jet,#slash{E_{T}})| large);Entries",100,0.,2.5);
         new TH1F(key+"tagratedphiirecopt",";Jet p_{T} (|#Delta#phi(jet,#slash{E_{T}})| small) [GeV];Entries",100,0.,200.);
         new TH1F(key+"tagratedphiirecotaggedpt",";Tagged jet (|#Delta#phi(jet,#slash{E_{T}})| small) p_{T} [GeV];Entries",100,0.,200.);
         new TH1F(key+"tagratedphiirecoeta",";Jet (|#Delta#phi(jet,#slash{E_{T}})| small) #eta;Entries",100,0.,2.5);
         new TH1F(key+"tagratedphiirecotaggedeta",";Tagged jet #eta (|#Delta#phi(jet,#slash{E_{T}})| small);Entries",100,0.,2.5);
         new TH1F(key+"tagraterecodphi",";|#Delta#phi(jet,#slash{E_{T}})|;Entries",100,0.,TMath::Pi());
         new TH1F(key+"tagraterecotaggeddphi",";|#Delta#phi(tagged jet,#slash{E_{T}})|;Entries",100,0.,TMath::Pi());
         
         
         new TH2F(key+"tagrateptw","Tag rate efficiency vs p_{T};p_{T} [GeV];Efficiency",50,0.,500.,50,0.,0.5);
         new TH2F(key+"tagrateptwu","Tag rate efficiency vs p_{T} STATU;p_{T} [GeV];Efficiency",50,0.,500.,50,0.,0.5);
         new TH2F(key+"tagrateptwd","Tag rate efficiency vs p_{T} STATD;p_{T} [GeV];Efficiency",50,0.,500.,50,0.,0.5);
      }
      
      //Sets the sum of weights for all TH*
      FixSumw2(gDirectory);
   };
   
   if(get_debug()) cout << "1" <<endl;   
   
   //Tip: use the built in cut tracker
   int cuts=0;
   util().cut(pre,suf,"CAND",false,0,cuts);
   
   //Fill runnr
   wfill(hist(pre,suf,"runnr"),evt->m_runnr);
   if(get_debug()) cout << "filled runnr with " << evt->m_runnr << " so far has " << hist(pre,suf,"runnr")->Integral() <<endl;   
   
   //cross-check lepton efficiencies
   checkMCLeptonEfficiency(pre,suf,0.05);
   
   //cross-check tagging efficiency
   checkBtagEff(pre,suf);

   //Fill jet multiplicities
   wfill(hist(pre,suf,"nj"),jets(isTru));

   if(get_debug()) cout << "filled nj with " << jets(isTru) << " so far has " << hist(pre,suf,"nj")->Integral() <<endl;   
   

   TLorentzVector ptsum_p = sumtrackvec();
   wfill(hist(pre,suf,"sumtrackpt"),ptsum_p.Pt());
   TLorentzVector metptsum_p = -1.0*ptsum_p;
   wfill(hist(pre,suf,"mettrack"),metptsum_p.Pt());

   if(get_debug()) cout << " Fill trk pt" << endl;

   for(int i=0;i!=trks();++i) {
      wfill(hist(pre,suf,"trackpt"),trk(i).p.Pt());
   }

   wfill(hist(pre,suf,"dphiptmet"),TMath::Abs(met_p(isTru).DeltaPhi(metptsum_p)));
   
   for(int i=0;i!=jets(isTru);++i) {
      wfill(hist(pre,suf,"dphijetsmet"),TMath::Abs( jet(i,isTru).p.DeltaPhi( met_p(isTru) ) ));
   }

   if(get_debug()) cout << "filled some met variables" << endl;
   
   double HTT = sumjetPt(isTru);
   double HTTasym = (HTT-met(isTru))/(HTT+met(isTru));
   wfill(hist(pre,suf,"htasym"),HTTasym);
   wfill2(hist2(pre,suf,"htmet"),met(isTru),HTT);
   wfill(hist(pre,suf,"ht"),HTT);
   wfill(hist(pre,suf,"Ht"),HTT);
   
   
   //Fill btag multiplicity and rank
   vector<int> btagind = btagindex(isTru);
   int nbtags = btagind.size();

   if(get_debug()) cout << " nbtags in event = "<<nbtags<< endl;
   
   wfill(hist(pre,suf,"nbtag2incl"),(nbtags>=2?2:nbtags));   
   wfill(hist(pre,suf,"nbtag"),nbtags);   
   
   if(get_debug()) {
      cout << " btags on jets ";
      for(size_t i=0;i!=btagind.size();++i) cout << btagind.at(i) << " ";
      cout << endl;
   }

   assert(nbtags == (int)btagind.size());
   
   for(size_t i=0;i!=btagind.size();++i) {
      if(get_debug()) cout << " btagindex="<<i<< endl;
      wfill(hist(pre,suf,"btagrank"),btagind.at(i));
      wfill(hist(pre,suf,"btagpt"),jet(btagind.at(i),isTru).p.Pt());
      wfill(hist(pre,suf,"btageta"),jet(btagind.at(i),isTru).p.Eta());
      

      if(get_debug()) cout << " counting meson in jet"<< endl;
      std::map<std::string,std::vector<size_t> > mesons = util().CountMesonsInJet(jet(btagind.at(i),isTru),evt->m_partons,0.4);
      if(get_debug()) cout << " found "<<mesons.size() <<" mesons in jet"<< endl;
      std::map<std::string,std::vector<size_t> >::const_iterator ifound = mesons.find("B");
      if(ifound!=mesons.end()) {      
         wfill(hist(pre,suf,"bjbhadcount4"),ifound->second.size());
         if(get_debug()) cout << " found " << ifound->second.size() <<" B mesons"<<endl;
      }
      ifound = mesons.find("C");
      if(ifound!=mesons.end()) {      
         wfill(hist(pre,suf,"bjchadcount4"),ifound->second.size());
         if(get_debug()) cout << " found " << ifound->second.size() <<" C mesons"<<endl;
      }

      if(i<2) {
         wfill(hist(pre,suf,TString::Format("dphibt%dmet",i)),TMath::Abs(jet(btagind.at(i),isTru).p.DeltaPhi(met_p(isTru))));
      }

   }

   if(get_debug()) cout << " Fill jet properties of the btagged jets" << endl;

   //Fill invariant mass of b-tagged jets
   if(btagind.size()>1) {
      wfill(hist(pre,suf,"mbtbt"),(jet(btagind.at(0),isTru).p+jet(btagind.at(1),isTru).p).M());
      wfill(hist(pre,suf,"dphibtbt"),TMath::Abs(jet(btagind.at(0),isTru).p.DeltaPhi(jet(btagind.at(1),isTru).p)));
      wfill(hist(pre,suf,"drbtbt"),jet(btagind.at(0),isTru).p.DeltaR(jet(btagind.at(1),isTru).p));
   }
   
   
   
   //Fill lepton multiplicities
   wfill(hist(pre,suf,"nl"),leptons(isTru));
   wfill(hist(pre,suf,"ne"),electrons(isTru));
   wfill(hist(pre,suf,"nm"),muons(isTru));
   
   //Fill MET
   wfill(hist(pre,suf,"Met"),met(isTru));
   wfill(hist(pre,suf,"met"),met(isTru));

   wfill(hist(pre,suf,"Mht"),mht(isTru));
   wfill(hist(pre,suf,"mht"),mht(isTru));
   

   
   //Fill event variables
   for(int i=0;i!=4;++i) {      
      if(jets(isTru)>i)  {
         wfill(hist(pre,suf,TString::Format("dphij%imet",i)),TMath::Abs( jet(i,isTru).p.DeltaPhi( met_p(isTru) )) );
         wfill(hist(pre,suf,TString::Format("dphij%imht",i)),TMath::Abs( jet(i,isTru).p.DeltaPhi( mht_p(isTru) )) );
         wfill2(hist2(pre,suf,TString::Format("metdphij%imet",i)),TMath::Abs(jet(i,isTru).p.DeltaPhi( met_p(isTru) )),met(isTru) );
         wfill2(hist2(pre,suf,TString::Format("j%idphij%imet",i,i)),TMath::Abs(jet(i,isTru).p.DeltaPhi( met_p(isTru) )),jet(i,isTru).p.Pt() );
      }         
      for(int j=0;j!=4;++j) {               
         if(i<=j) continue;
         if(jets(isTru)>i&&jets(isTru)>j) {
            wfill(hist(pre,suf,TString::Format("dphij%ij%i",i,j)),TMath::Abs(jet(i,isTru).p.DeltaPhi(jet(j,isTru).p)));            
            wfill(hist(pre,suf,TString::Format("mj%ij%i",i,j)),(jet(i,isTru).p + jet(j,isTru).p).M());
         }
      }
   }
   if(jets(isTru)>=4) wfill(hist(pre,suf,"meff4"),EffectiveMass(isTru,0,4));
   if(jets(isTru)>=2) {
      wfill(hist(pre,suf,"dphij01met"),TMath::Abs( jet(0,isTru).p.DeltaPhi( met_p(isTru) )) );
      wfill(hist(pre,suf,"dphij01met"),TMath::Abs( jet(1,isTru).p.DeltaPhi( met_p(isTru) )) );
   }
   
   wfill(hist(pre,suf,"sph"),Sphericity());
                     


   if(get_debug()) cout << "2" <<endl;

   int nflavor[3] = {0,0,0};
   int nflavor_parton[3] = {0,0,0}; //matching partons
   int nflavor_both[3] = {0,0,0}; // both mesons and partons agree
   std::vector<int> bjet_indexes;
   
   


   //Fill styles
   for(int i=0;i!=jets(isTru);++i) {
      wfill(hist(pre,suf,"jpt"),jet(i,isTru).p.Pt());
      wfill(hist(pre,suf,"Jpt"),jet(i,isTru).p.Pt());
      wfill(hist(pre,suf,"jeta"),jet(i,isTru).p.Eta());
      wfill(hist(pre,suf,"jgoodness"),jet(i,isTru).goodness());
      if(i<4) {
         wfill(hist(pre,suf,TString::Format("j%ipt",i)),jet(i,isTru).p.Pt());
         wfill(hist(pre,suf,TString::Format("j%ieta",i)),jet(i,isTru).p.Eta());
         wfill(hist(pre,suf,TString::Format("j%iphi",i)),jet(i,isTru).p.Phi());
         wfill2(hist2(pre,suf,TString::Format("j%ietaphi",i)),jet(i,isTru).p.Eta(),jet(i,isTru).p.Phi());
         wfill(hist(pre,suf,TString::Format("j%isv0",i)),jet(i,isTru).SV0_w());
      }
      wfill(hist(pre,suf,"jsv0"),jet(i,isTru).SV0_w());
      double sv1ip3d = jet(i,isTru).SV1IP3D_w();
      wfill(hist(pre,suf,"jsv1ip3d"),sv1ip3d);
      
      if(get_debug()) cout << "21" <<endl;
      
      int truth_particle_index = -1;
      const Particles<Jet> jetsref = isTru==true ? evt->m_jets_truth : evt->m_jets;
      std::pair<int,int> match = util().TruthMatching(truth_particle_index,
                                                      jet(i,isTru),
                                                      jetsref,
                                                      evt->m_partons, 0.4,0);
      if(get_debug()) cout << "22" <<endl;

      wfill(hist(pre,suf,"jflavor"),jet(i,isTru).flavor());
      wfill(hist(pre,suf,"jflavorman"),match.first);
      
      if(match.first == 5) {
         bjet_indexes.push_back(i);
         wfill(hist(pre,suf,"bjsv0"),jet(i,isTru).SV0_w()); 
         wfill(hist(pre,suf,"bjsv1ip3d"),sv1ip3d);
         wfill(hist(pre,suf,"bjrank"),i);
         wfill(hist(pre,suf,"bjpt"),jet(i,isTru).p.Pt());      
         wfill(hist(pre,suf,"bjeta"),TMath::Abs(jet(i,isTru).p.Eta()));      
         nflavor[0]++;
         if(match.second == 5) nflavor_both[0]++;
         if( IsTaggedJet(jet(i,isTru))) wfill(hist(pre,suf,"bjbtagrank"),i);
      }
      else if(match.first == 4) {
         wfill(hist(pre,suf,"cjsv0"),jet(i,isTru).SV0_w()); 
         wfill(hist(pre,suf,"cjsv1ip3d"),sv1ip3d);
         wfill(hist(pre,suf,"cjrank"),i);
         wfill(hist(pre,suf,"cjpt"),jet(i,isTru).p.Pt());      
         wfill(hist(pre,suf,"cjeta"),TMath::Abs(jet(i,isTru).p.Eta()));      
         nflavor[1]++;
         if(match.second == 4) nflavor_both[1]++;
         if( IsTaggedJet(jet(i,isTru))) wfill(hist(pre,suf,"cjbtagrank"),i);
      }
      else {
         wfill(hist(pre,suf,"ljsv0"),jet(i,isTru).SV0_w()); 
         wfill(hist(pre,suf,"ljsv1ip3d"),sv1ip3d);
         wfill(hist(pre,suf,"ljrank"),i);
         wfill(hist(pre,suf,"ljpt"),jet(i,isTru).p.Pt());      
         wfill(hist(pre,suf,"ljeta"),TMath::Abs(jet(i,isTru).p.Eta()));      

         nflavor[2]++;
         if(match.second == 1) nflavor_both[2]++;
         if( IsTaggedJet(jet(i,isTru))) wfill(hist(pre,suf,"ljbtagrank"),i);
      }
      
      //cross-check the parton matching
      if(match.second == 5) {
         nflavor_parton[0]++;
      } else if(match.second == 4) {
         nflavor_parton[1]++;
      } else {
         nflavor_parton[2]++;
      }
      
      /*
      //manual weight
      wfill(hist(pre,suf,"jpt"),jet(i,isTru).p.Pt(),evt->weight_raw());
      //find histo manually and fill
      hist(pre,suf,"jpt")->Fill(jet(i,isTru).p.Pt(),evt->weight_raw());
      */
      



      if(DO_TAGRATES) {
         
         //Fill the tag rates for these jets
         
         std::string tagratetype;
         if(TMath::Abs(jet(i,isTru).p.DeltaPhi(met_p(isTru))) > 1.0 )
            tagratetype = "alpptdphi";
         else
            tagratetype = "alpptdphii";
         
         double tagrateeff = evt->tagrate.GetTagRateEff(tagratetype,jet(i,isTru).p.Pt());
         double tagrateeffstatu = evt->tagrate.GetTagRateEff(tagratetype,jet(i,isTru).p.Pt(),"STATU");
         double tagrateeffstatd = evt->tagrate.GetTagRateEff(tagratetype,jet(i,isTru).p.Pt(),"STATD");
         //jet(i,isTru).TagProbMan(tagrate);
         wfill(hist(pre,suf,"tagrateptw"),jet(i,isTru).p.Pt(),tagrateeff);
         wfill(hist(pre,suf,"tagrateptwu"),jet(i,isTru).p.Pt(),tagrateeff+tagrateeffstatu);
         wfill(hist(pre,suf,"tagrateptwd"),jet(i,isTru).p.Pt(),tagrateeff-tagrateeffstatd);
         
         
         
      }
   } //jets
   
   if(DO_TAGRATES) {
      
      std::map< TString,std::pair<double,bool> > event_tag_rates = EvtTagProb("alp,pt");
      wfill(hist(pre,suf,"nbtagpredalppt"),btags(event_tag_rates));   
      event_tag_rates = EvtTagProb("alp,pt",false,"STATU");
      wfill(hist(pre,suf,"nbtagpredalpptstatup"),btags(event_tag_rates,"STATU"));   
      event_tag_rates = EvtTagProb("alp,pt",false,"STATD");
      wfill(hist(pre,suf,"nbtagpredalpptstatdown"),btags(event_tag_rates,"STATD"));   
      
      event_tag_rates = EvtTagProb("alp,pt,jmd");
      wfill(hist(pre,suf,"nbtagpredalpptjmd"),btags(event_tag_rates));   
      event_tag_rates = EvtTagProb("alp,pt,jmd",false,"STATU");
      wfill(hist(pre,suf,"nbtagpredalpptjmdstatup"),btags(event_tag_rates,"STATU"));   
      event_tag_rates = EvtTagProb("alp,pt,jmd",false,"STATD");
      wfill(hist(pre,suf,"nbtagpredalpptjmdstatdown"),btags(event_tag_rates,"STATD"));   
      
      event_tag_rates = EvtTagProb("pyt,pt,jmd");
      wfill(hist(pre,suf,"nbtagpredpytptjmd"),btags(event_tag_rates));   
      event_tag_rates = EvtTagProb("pyt,pt,jmd",false,"STATU");
      wfill(hist(pre,suf,"nbtagpredpytptjmdstatup"),btags(event_tag_rates,"STATU"));   
      event_tag_rates = EvtTagProb("pyt,pt,jmd",false,"STATD");
      wfill(hist(pre,suf,"nbtagpredpytptjmdstatdown"),btags(event_tag_rates,"STATD"));   
      
      event_tag_rates = EvtTagProb("alp,pt,dphi");
      wfill(hist(pre,suf,"nbtagpredalpptdphi"),btags(event_tag_rates));   
      event_tag_rates = EvtTagProb("alp,pt,dphi",false,"STATU");
      wfill(hist(pre,suf,"nbtagpredalpptdphistatup"),btags(event_tag_rates,"STATU"));   
      event_tag_rates = EvtTagProb("alp,pt,dphi",false,"STATD");
      wfill(hist(pre,suf,"nbtagpredalpptdphistatdown"),btags(event_tag_rates,"STATD"));   
      
      event_tag_rates = EvtTagProb("alp,pt,dphii");
      wfill(hist(pre,suf,"nbtagpredalpptdphii"),btags(event_tag_rates));   
      event_tag_rates = EvtTagProb("alp,pt,dphii",false,"STATU");
      wfill(hist(pre,suf,"nbtagpredalpptdphiistatup"),btags(event_tag_rates,"STATU"));   
      event_tag_rates = EvtTagProb("alp,pt,dphii",false,"STATD");
      wfill(hist(pre,suf,"nbtagpredalpptdphiistatdown"),btags(event_tag_rates,"STATD"));   
   }




   wfill(hist(pre,suf,"nbj"),nflavor[0]);
   wfill(hist(pre,suf,"ncj"),nflavor[1]);
   wfill(hist(pre,suf,"nlj"),nflavor[2]);
   wfill(hist(pre,suf,"nbjparton"),nflavor_parton[0]);
   wfill(hist(pre,suf,"ncjparton"),nflavor_parton[1]);
   wfill(hist(pre,suf,"nljparton"),nflavor_parton[2]);
   wfill(hist(pre,suf,"nbjboth"),nflavor_both[0]);
   wfill(hist(pre,suf,"ncjboth"),nflavor_both[1]);
   wfill(hist(pre,suf,"nljboth"),nflavor_both[2]);
   
   for(size_t i=0;i!=bjet_indexes.size();++i) {
      if(i<4) {
         wfill(hist(pre,suf,TString::Format("dphibj%imet",i)),TMath::Abs(jet(bjet_indexes[i],isTru).p.DeltaPhi(met_p(isTru))));            
         wfill(hist(pre,suf,TString::Format("bj%ipt",i)),jet(bjet_indexes[i],isTru).p.Pt());
         wfill(hist(pre,suf,TString::Format("bj%ieta",i)),jet(bjet_indexes[i],isTru).p.Eta());
         wfill(hist(pre,suf,TString::Format("bj%iphi",i)),jet(bjet_indexes[i],isTru).p.Phi());
         for(size_t j=0;j!=bjet_indexes.size();++j) {
            if(i<=j) continue;                  
            if(i<4 && j<4) { //only the first four jets
               wfill(hist(pre,suf,TString::Format("dphibj%ibj%i",i,j)),TMath::Abs(jet(bjet_indexes[i],isTru).p.DeltaPhi(jet(bjet_indexes[j],isTru).p)));            
               wfill(hist(pre,suf,TString::Format("drbj%ibj%i",i,j)),jet(bjet_indexes[i],isTru).p.DeltaR(jet(bjet_indexes[j],isTru).p));            
               wfill(hist(pre,suf,TString::Format("mbj%ibj%i",i,j)),(jet(bjet_indexes[i],isTru).p + jet(bjet_indexes[j],isTru).p).M());            
            } 
         }
      }
   }
   
   


   if(get_debug()) cout << "4" <<endl;


   
}

  


void Topology_jetmetbtag::finalize(void) {
   

   util().plotEfficiency("etrurecomatchpt","etrupt");
   util().plotEfficiency("etrurecomatcheta","etrueta");
   util().plotEfficiency("mtrurecomatchpt","mtrupt");
   util().plotEfficiency("mtrurecomatcheta","mtrueta");
   
   util().plotEfficiency("bjrecotaggedeta","bjrecoeta");
   util().plotEfficiency("bjrecotaggedpt","bjrecopt");
   util().plotEfficiency("bjrecotaggedsv1ip3dpt","bjrecopt");
   util().plotEfficiency("bjrecotaggedl2ip3dpt","bjrecol2ip3dpt");

   util().plotEfficiency("bqjrecotaggedeta","bqjrecoeta");
   util().plotEfficiency("bqjrecotaggedpt","bqjrecopt");
   util().plotEfficiency("bqjrecotaggedsv1ip3dpt","bqjrecopt");
   util().plotEfficiency("bqjrecotaggedl2ip3dpt","bqjrecol2ip3dpt");

   util().plotEfficiency("tagraterecotaggedeta","tagraterecoeta");
   util().plotEfficiency("tagraterecotaggedpt","tagraterecopt");
   util().plotEfficiency("tagratedphirecotaggedeta","tagratedphirecoeta");
   util().plotEfficiency("tagratedphirecotaggedpt","tagratedphirecopt");



   plotBtagProp("jetmetbtag","","ljsv1ip3d","rej");
   plotBtagProp("jetmetbtag","","bjsv1ip3d","eff");
   plotBtagProp("jetmetbtag","","cjsv1ip3d","eff");
  
   plotBtagProp("jetmetbtag","","ljsv0","rej");
   plotBtagProp("jetmetbtag","","cjsv0","eff");
   plotBtagProp("jetmetbtag","","bjsv0","eff");

   // Print some statistics
   
   std::cout << "\n\n ------------------- Jetmetbtag analysis results -------------------"
             << std::endl;
   std::cout << "Events         : " << histC("jetmetbtag","","runnr") << std::endl;
   
   float ne_ok=util().cnt("Electron","Electron","OK");
   float ne_cand=util().cnt("Electron","Electron","CAND");
   float nm_ok=util().cnt("Muon","Muon","OK");
   float nm_cand=util().cnt("Muon","Muon","CAND");
   
   std::cout << "Ele cand   : " << ne_cand << std::endl;
   std::cout << "Ele ok     : " << ne_ok << " -> efficiency: " << (ne_cand!=0.?ne_ok/ne_cand:-1.) << std::endl;   
   std::cout << "Mu  cand   : " << nm_cand << std::endl;
   std::cout << "Mu  ok     : " << nm_ok << "  -> efficiency: " << (nm_cand!=0.?nm_ok/nm_cand:-1.) << std::endl;
   std::cout << "Jet raw    : " << util().cnt("Jet","Jet","CAND") << std::endl;
   std::cout << "Jet        : " << util().cnt("Jet","Jet","OK") << std::endl;   
   
   
   std::cout << "Event selection:" << std::endl;

   util().displayCutMap();

   util().printCutMap("jetmetbtag","","runnr");


   
}





void Topology_jetmetbtag::plotBtagProp(TString obj,
                                       TString category,
                                       TString value, TString type) {
   
   std::cout << " Making " << type << " btag plot" << endl;
   //Calculate the rejection and efficiency for b-tag cuts
   // Find the histograms with the weights for all jets
   TH1* h = hist(obj, category,value);
   TString value_new = value + type;
   h->Clone(obj+category+"_"+value_new);  
   //   new TH1F(obj+category+"_"+value_new,";L2 b-jet IP2D Cut;Rejection",
   // 	   h->GetNbinsX(),
   // 	   h->-0.1,1.1);
   //Integrate
   TH1* hr = hist(obj, category,value_new);
   TString title = TString::Format(";%s;%s",value.Data(),type.Data());
   hr->SetTitle(title);
   double tot = h->Integral(-1,999999);
   if(tot==0.) return;
   for(int ibin=0; ibin != h->GetNbinsX()+1; ++ibin) {
      double s = h->Integral(0,ibin);
      double eff[2];
      util().getEfficiency( (tot-s), tot, eff);
      if(type=="rej") {
         if(eff[0]==0.) {
            hr->SetBinContent(ibin, -1.);
            hr->SetBinError(ibin, -1.);
         } else {
            hr->SetBinContent(ibin, 1./eff[0]);
            hr->SetBinError(ibin, eff[1]/eff[0]);
         }
      }
      else {
         hr->SetBinContent(ibin, eff[0]);
         hr->SetBinError(ibin, eff[1]);
      }
   }  
}


bool Topology_jetmetbtag::passSusyGroupCuts2(bool isTru) {
   if( jets(isTru)>=2 ) {
      if(jet(0,isTru).p.Pt() > 180.0) {
         if(jet(1,isTru).p.Pt() > 50.0) {
            if(met(isTru) > 80.0) {
               return true;
            }
         }
      }
   }
   return false;
}


void Topology_jetmetbtag::checkBtagEff(const TString& pre, const TString& suf) {
   
   double dphicut = 1.0;
   
   for(int i=0;i!=jets();++i) {

      if(DO_TAGRATES) {
         
         wfill(hist(pre,suf,"tagraterecopt"),jet(i).p.Pt());
         wfill(hist(pre,suf,"tagraterecoeta"),TMath::Abs(jet(i).p.Eta()));
         wfill(hist(pre,suf,"tagraterecodphi"),TMath::Abs(jet(i).p.DeltaPhi(met_p())));
         if(TMath::Abs(jet(i).p.DeltaPhi(met_p())) > dphicut ) {         
            wfill(hist(pre,suf,"tagratedphirecopt"),jet(i).p.Pt());
            wfill(hist(pre,suf,"tagratedphirecoeta"),TMath::Abs(jet(i).p.Eta()));
         } else {
            wfill(hist(pre,suf,"tagratedphiirecopt"),jet(i).p.Pt());
            wfill(hist(pre,suf,"tagratedphiirecoeta"),TMath::Abs(jet(i).p.Eta()));
         }
         if(jet(i).SV0_w() > SV0CUT) {
            wfill(hist(pre,suf,"tagraterecotaggedpt"),jet(i).p.Pt());
            wfill(hist(pre,suf,"tagraterecotaggedeta"),TMath::Abs(jet(i).p.Eta()));
            wfill(hist(pre,suf,"tagraterecotaggeddphi"),TMath::Abs(jet(i).p.DeltaPhi(met_p())));
            if(TMath::Abs(jet(i).p.DeltaPhi(met_p())) > dphicut ) {         
               wfill(hist(pre,suf,"tagratedphirecotaggedpt"),jet(i).p.Pt());
               wfill(hist(pre,suf,"tagratedphirecotaggedeta"),TMath::Abs(jet(i).p.Eta()));
            } else {
               wfill(hist(pre,suf,"tagratedphiirecotaggedpt"),jet(i).p.Pt());
               wfill(hist(pre,suf,"tagratedphiirecotaggedeta"),TMath::Abs(jet(i).p.Eta()));
            }
         }

      }
      
      //match truth jets to reco jets and then check their flavor
      //match truth particles
      int truth_particle_index = -1;
      std::pair<int,int> match = util().TruthMatching(truth_particle_index,
                                                      jet(i),
                                                      evt->m_jets,                                                         
                                                      evt->m_partons, 0.4,0);

      int meson_match = match.first;
      int parton_match = match.second;
      if(meson_match == 5) {
         //this is a b-jet
         wfill(hist(pre,suf,"bjrecopt"),jet(i).p.Pt());
         wfill(hist(pre,suf,"bjrecoeta"),jet(i).p.Eta());
         if(jet(i).SV0_w() > SV0CUT) {
            //this is tagged
            wfill(hist(pre,suf,"bjrecotaggedpt"),jet(i).p.Pt());             
            wfill(hist(pre,suf,"bjrecotaggedeta"),jet(i).p.Eta());            
         }
         if(jet(i).SV1IP3D_w() > SV1IP3DCUT) {            
            wfill(hist(pre,suf,"bjrecotaggedsv1ip3dpt"),jet(i).p.Pt());             
         }
         
         L2BJet* matched_l2bjet = matchObjects(jet(i).p,evt->m_l2bjets,0.4);
         if(matched_l2bjet) {
            wfill(hist(pre,suf,"bjrecol2ip3dpt"),jet(i).p.Pt());
            if(matched_l2bjet->IsTagged("IP3D",0.61)) {
               wfill(hist(pre,suf,"bjrecotaggedl2ip3dpt"),jet(i).p.Pt());               
            }            
         }
      }

      if(parton_match == 5) {
         //this is a b-jet
         wfill(hist(pre,suf,"bqjrecopt"),jet(i).p.Pt());
         wfill(hist(pre,suf,"bqjrecoeta"),jet(i).p.Eta());
         if(jet(i).SV0_w() > SV0CUT) {
            //this is tagged
            wfill(hist(pre,suf,"bqjrecotaggedpt"),jet(i).p.Pt());             
            wfill(hist(pre,suf,"bqjrecotaggedeta"),jet(i).p.Eta());            
         }
         if(jet(i).SV1IP3D_w() > SV1IP3DCUT) {            
            wfill(hist(pre,suf,"bqjrecotaggedsv1ip3dpt"),jet(i).p.Pt());             
         }
         
         L2BJet* matched_l2bjet = matchObjects(jet(i).p,evt->m_l2bjets,0.4);
         if(matched_l2bjet) {
            wfill(hist(pre,suf,"bqjrecol2ip3dpt"),jet(i).p.Pt());
            if(matched_l2bjet->IsTagged("IP3D",0.61)) {
               wfill(hist(pre,suf,"bqjrecotaggedl2ip3dpt"),jet(i).p.Pt());               
            }            
         }
      }


   } //jets
   
}


void Topology_jetmetbtag::checkMCLeptonEfficiency(const TString& pre, const TString& suf,
                                                  double drmatch) {
   
   //match truth leptons to reconstructed leptons
   for(int i=0;i!=electrons(true);++i) {
      wfill(hist(pre,suf,"etrupt"),electron(i,true).p.Pt());
      wfill(hist(pre,suf,"etrueta"),electron(i,true).p.Eta());
      //cout << "fill etru pt " << electron(i,true).p.Pt() << endl;
      for(int j=0;j!=electrons();++j) {
         double dr = electron(i,true).p.DeltaR(electron(j).p);
         if( dr < drmatch) {
            wfill(hist(pre,suf,"etrurecomatchpt"),electron(i,true).p.Pt());
            wfill(hist(pre,suf,"etrurecomatcheta"),electron(i,true).p.Eta());
            //cout << "fill match etru pt " << electron(i,true).p.Pt() << endl;
            break;
         }
      }
   }
   
   for(int i=0;i!=muons(true);++i) {
      wfill(hist(pre,suf,"mtrupt"),muon(i,true).p.Pt());
      wfill(hist(pre,suf,"mtrueta"),muon(i,true).p.Eta());
      //cout << "fill etru pt " << electron(i,true).p.Pt() << endl;
      for(int j=0;j!=muons();++j) {
         double dr = muon(i,true).p.DeltaR(muon(j).p);
         if( dr < drmatch) {
            wfill(hist(pre,suf,"mtrurecomatchpt"),muon(i,true).p.Pt());
            wfill(hist(pre,suf,"mtrurecomatcheta"),muon(i,true).p.Eta());
            //cout << "fill match etru pt " << electron(i,true).p.Pt() << endl;
            break;
         }
      }
   }
   
}


bool Topology_jetmetbtag::IsTaggedJet(const Jet& j, TString type) {
   if(type=="SV1IP3D")
      return j.SV1IP3D_w() > SV1IP3DCUT ? true : false;   
   else
      return j.SV0_w() > SV0CUT ? true : false;   
   
}

vector<int> Topology_jetmetbtag::btagindex(bool isTru) {
   
   vector<int> taggedjets;
   for(int i=0;i!=jets(isTru);++i) {
      if(!isTru) {
         if (IsTaggedJet(jet(i))) taggedjets.push_back(i);
      } else {
         //match truth particles
         int truth_particle_index = -1;
         const Particles<Jet> jetsref = isTru==true ? evt->m_jets_truth : evt->m_jets;
         std::pair<int,int> match = util().TruthMatching(truth_particle_index,
                                                         jet(i,isTru),
                                                         jetsref,                                                         
                                                         evt->m_partons, 0.4,0);
         // 100% efficiency! ->FIX THIS!
         if(match.first == 5) taggedjets.push_back(i);
         
      }
   }
   return taggedjets;
}
int Topology_jetmetbtag::btags(bool isTru) {
   
   vector<int> tags = btagindex(isTru);
   return (int)tags.size();
}
int Topology_jetmetbtag::btags_pred(const std::string& type, bool isTru, std::string error) {
   std::map< TString,std::pair<double,bool> > m  = EvtTagProb(type,isTru,error);
   return btags(m,error);
}


int Topology_jetmetbtag::btags(const std::map<TString, std::pair<double,bool> >& evttagrate,std::string error) {
   //use the probabilities to define nr of tags
   std::string name = "zero-excl"; name += error;
   std::map<TString, std::pair<double,bool> >::const_iterator ifound = evttagrate.find(TString(name.c_str()));
   if(ifound==evttagrate.end()) { cout << "ERROR! Could not find evt tag rate for name="<<name<<endl; exit(-1); }
   std::pair<double,bool> tmp = ifound->second;
   int zerotags = tmp.second;
   //
   name = "one-excl"; name += error;
   ifound = evttagrate.find(TString(name.c_str()));
   if(ifound==evttagrate.end()) { cout << "ERROR! Could not find evt tag rate for name="<<name<<endl; exit(-1); }
   tmp = ifound->second;
   int onetags = tmp.second;
   //
   name = "two-incl"; name += error;
   ifound = evttagrate.find(TString(name.c_str()));
   if(ifound==evttagrate.end()) { cout << "ERROR! Could not find evt tag rate for name="<<name<<endl; exit(-1); }
   tmp = ifound->second;
   int twotags = tmp.second;
   if((zerotags+onetags+twotags)!=1) {
      cout << "ERROR! btags prediction does not sum up to one (error="<<error<<")"<<endl;
      cout << "0,1,2: "<<zerotags<<","<<onetags<<","<<twotags<<endl;
      exit(-1);
   }
   return zerotags!=0 ? 0 : (onetags!=0 ? 1 : 2);   
}







std::map< TString,std::pair<double,bool> > Topology_jetmetbtag::EvtTagProb(const std::string& param_type, bool isTru, std::string error) {
   
   
   if(get_debug()>0) cout << "Calculating event tag probability using parametrization "<<param_type<<" (error=\""<<error<<"\") --------" << endl;
   std::string variation;
   if(error!="") {
      variation = error.at(error.size()-1);
      assert(variation=="U"||variation=="D");
   }
   
   
   //build the string that finds the correct parametrization
   std::string sample;
   if(param_type.find("alp")!=std::string::npos) sample = "alp";
   else if(param_type.find("pyt")!=std::string::npos) sample = "pyt";
   else {std::cout<<"ERROR " << param_type << " does not contain a valid sample!" << endl; exit(-1);}
   
   std::string par1;
   if(param_type.find("pt")!=std::string::npos) par1 = "pt";
   else if(param_type.find("eta")!=std::string::npos) par1 = "eta";
   else {std::cout<<"ERROR " << param_type << " does not contain a valid par1!" << endl; exit(-1);}
   
   std::string par2;
   if(param_type.find("jmd")!=std::string::npos) par2 = "jmd";
   else if(param_type.find("dphii")!=std::string::npos) par2 = "dphii";
   else if(param_type.find("dphi")!=std::string::npos) par2 = "dphi";   
   else {
      par2="";
      //std::cout<<"ERROR " << param_type << " does not contain a valid par2!" << endl; exit(-1);
   }
   
   
   if(get_debug()>0) cout << "sample: "<<sample<<" par1:"<<par1<<" par2:"<<par2<<endl;
   

   
   std::string parametrization;
   double notagprob = -1.0;
   double singletagprob = 0.0;
   for(int i=0;i!=jets(isTru);++i) {
      
      
      //HACK to get the extra dimension in dphi(j,MET) ->FIX THIS!
      if(par2=="jmd") {
         if(TMath::Abs(jet(i,isTru).p.DeltaPhi(met_p(isTru))) > 1.0 )
            parametrization = sample + par1 + "dphi";
         else
            parametrization = sample + par1 + "dphii";
      } else {
         parametrization = sample + par1 + par2;
      }
      
      if(get_debug()>0) cout << "parametrization -> "<<parametrization<<endl;
      
      
      double p = evt->tagrate.GetTagRateEff(parametrization,jet(i,isTru).p.Pt());
      if(error!="") {         
         double ep = evt->tagrate.GetTagRateEff(parametrization,jet(i,isTru).p.Pt(),error);         
         if(variation=="U") { p += ep; }
         else               { p -= ep; }
      }
      if(notagprob < 0.) notagprob = (1.0 - p) ;
      else notagprob *= (1.0-p);
      
      double notagprob_sub = -1.0;
      for(int j=0;j!=jets(isTru);++j) {
         if(i!=j) {
            
            //HACK to get the extra dimension in dphi(j,MET) ->FIX THIS!
            if(par2=="jmd") {
               if(TMath::Abs(jet(j,isTru).p.DeltaPhi(met_p(isTru))) > 1.0 )
                  parametrization = sample + par1 + "dphi";
               else
                  parametrization = sample + par1 + "dphii";
            } else {
               parametrization = sample + par1 + par2;
            }

            
            double pp = evt->tagrate.GetTagRateEff(parametrization,jet(j,isTru).p.Pt());
            if(error!="") {         
               double epp = evt->tagrate.GetTagRateEff(parametrization,jet(j,isTru).p.Pt(),error);         
               if(variation=="U") { pp += epp; }
               else               { pp -= epp; }
            }
            if(notagprob_sub < 0.) notagprob_sub = (1.0 -pp);
            else notagprob_sub *= (1.0-pp);
         }
      }//j
      
      singletagprob += (p * notagprob_sub);
      if(get_debug()>0) cout << "jet " << i << " prob = "<< p << " prod(1-p)="<<notagprob<<" prod_j(1-p)="<<notagprob_sub<<" singletagprob="<<singletagprob<<" (pT="<<jet(i,isTru).p.Pt()<< " )" << endl;
      
      
   }//i
   double oneormoretagprob = 1.0 - notagprob;
   double twoormoretagprob = oneormoretagprob - singletagprob;
   if(get_debug()>0) cout << "SUMMARY" << endl;
   if(get_debug()>0) cout << "0-tag:    " << notagprob << endl;
   if(get_debug()>0) cout << "1-tag:    " << singletagprob << endl;
   if(get_debug()>0) cout << ">=1-tag:    " << oneormoretagprob << endl;
   if(get_debug()>0) cout << ">=2-tag:    " << twoormoretagprob << endl;
   if(get_debug()>0) cout << "-----------" << endl;
   std::map< TString,std::pair<double,bool> > m;
   std::string name0 = "zero-excl";name0+=error;
   m[name0.c_str()] = std::make_pair(singletagprob,false);
   std::string name1 = "one-excl";name1+=error;      
   m[name1.c_str()] = std::make_pair(singletagprob,false);
   std::string name11 = "one-incl";name11+=error;      
   m[name11.c_str()] = std::make_pair(oneormoretagprob,false);
   std::string name2 = "two-incl";name2+=error;      
   m[name2.c_str()] = std::make_pair(twoormoretagprob,false);
   //Role the dice!
   double x  = util().ran.Rndm();
   if( x < notagprob) { 
      m[name0].second = true;
   } else if( x>notagprob && x < (notagprob+singletagprob)) {
      m[name1].second = true;         
   } else if( x > (notagprob+singletagprob)) {
      m[name2].second = true;
   } else {
      cout << "ERROR EvtTagProb for x=" << x << " was neither of 0,1 or >=2 tag ranges:"<<notagprob<<","<<notagprob+singletagprob<<endl; 
      exit(-1);
   }
   
   if(get_debug()>0) {
      cout << "Content of evttagprob map:" << endl;
      for(std::map< TString,std::pair<double,bool> >::const_iterator i = m.begin();i!=m.end();++i) {
         cout << "Name " << i->first << " prob="<< (i->second).first << " bool="<<(i->second).second <<endl;
      }
   }
   
   return m;

}
