/**************************************************************************
 **
 **   File:         TrigDec.h
 **
 **   Description:  Holding the trig decisions
 **
 **
 **   Author:       P. Hansson
 **
 **   Created:      Tue Mar 20 2007
 **   Modified:
 **
 **************************************************************************/

#ifndef __TRIGDEC_H
#define __TRIGDEC_H

#include "TString.h"
#include <map>
#include <vector>
#include <iomanip>


class TrigDec {
   public:
      TrigDec(void) {};
      void setTrigDec(const TString & trigger, const int & dec) {         
         m_trigdec[trigger] = dec;
      }
      
      int getTrigDec(const TString & trigger) {
         std::map< TString,int >::const_iterator it=m_trigdec.find(trigger);
         if( it == m_trigdec.end() ) {
            std::map< TString,bool >::iterator itwarn=WarnAbsentTriggers.find(trigger);
            if(itwarn == WarnAbsentTriggers.end()) {
               WarnAbsentTriggers[trigger]=true;
               itwarn=WarnAbsentTriggers.find(trigger);
            }
            assert(itwarn!=WarnAbsentTriggers.end());
            if(itwarn->second) {
               std::cout << "WARNING!! the trigger name "
                         << trigger.Data() << " was not found!!" << std::endl
                         << "No more warnings will be raised for this trigger name!" << std::endl;
               itwarn->second = false;
            }
            return 0;
         }
         return it->second;
      }
      
      
      const std::map< TString, int >* getAllTrigDec(void) const {
         return &m_trigdec;
      }
      
      inline const std::vector<TString> GetAllTrigDecisionNames(void) {          
         std::map< TString,int >::const_iterator it = m_trigdec.begin();
         std::map< TString,int >::const_iterator itE = m_trigdec.end();
         std::vector<TString> triggernames;
         for( ; it != itE; ++it ) triggernames.push_back(it->first);
         return triggernames;
      }


      void Reset(void) {
         std::map< TString,int >::iterator it = m_trigdec.begin();
         std::map< TString,int >::iterator itE = m_trigdec.end();
         for( ; it != itE; ++it )
            it->second = 0;         
      }
      
      void print(void) const {
         std::cout << "--------------------------------------" << std::endl;
         std::cout << "Trigger decisions for this event:" << std::endl;
         std::map< TString,int >::const_iterator it = m_trigdec.begin();
         std::map< TString,int >::const_iterator itE = m_trigdec.end();
         for( ; it != itE; ++it )
            std::cout << it->first << " -> " << it->second <<  std::endl;
         std::cout << "--------------------------------------" << std::endl;
      }


      void FillTriggerEfficiencies(TString prefix,TString suffix, TDirectory* dir) {
         TString name=prefix+suffix+"_teff";
         if (dir->Get(name)==0) {
            std::cout << "Creating new trigger efficiency histo with name: " << name <<  std::endl;
            dir->cd();
            new TH2F(name,"Trigger Efficiency",60,0.,60.,3,0.,3.);
         }
         TH2* h2=(TH2*)dir->Get(name);
         if (!h2){
            std::cout << "TrigDec: ERROR could not find trigger efficiency histogram: " << name << std::endl;      
            exit(1);
         }
         const std::vector<TString> triggers = GetAllTrigDecisionNames();
         if( triggers.size() == 0 ) {
            std::cout << "ERROR: no triggers defined, is this really what you want?" << std::endl;
            exit(1);
         }
         //loop over all triggers and fill trigger efficiency 2D-histogram
         for( int it=0; it!=static_cast<int>(triggers.size()); ++it) {        
            h2->Fill(it, getTrigDec(triggers[it]),1.0);      
            int bin = h2->GetXaxis()->FindBin(it);
            TString blabel(h2->GetXaxis()->GetBinLabel(bin));
            //set bin labels to trigger names - check first if they have already been set
            if( !blabel.Contains("L1") && !blabel.Contains("L2") && !blabel.Contains("EF") ) {
               h2->GetXaxis()->SetBinLabel(bin,triggers[it].Data());
            }
         } //it
         return;
      }//FillTriggerEfficiencies()
      

      
      double histTeff(const int& iTrig, const TString& mode, const TString& sel, const TString& effplot) {
         //overloaded interface
         TString name(Form("diem%s%s",sel.Data(),effplot.Data()));
         TH2* h2=(TH2*)gDirectory->Get(name);
         if (!h2) {
            std::cout << "TrigDec: ERROR could not find histogram with name: " << name 
                      << " to calculate efficiency." << std::endl;      
            exit(1);
         }
         return histTeff(iTrig,mode,h2);
      }
      
      
      double histTeff(const int& iTrig, const TString& mode, TH2* h2) {
         if (!h2) {
            std::cout << "TrigDec: ERROR could not find histogram with name: " << h2->GetName() 
                      << " to calculate efficiency." << std::endl;      
            exit(1);
         }
         // read the bins and calcluate ratio of true and false bins
         // At the moment it can return Npass,Nfail, efficiency

         // It is also optional to fill bin 3 with a condition to pass e.g. match as well
         // a bit ugly and possibly time consuming....

         // I hope the errors are correct, they are not binomial, 
         // this could be implemented easily I guess

         int bin = h2->GetXaxis()->FindBin(iTrig);
         double pass,epass,fail,efail,eff,eeff,passm,epassm,effm,eeffm;
         pass = h2->GetBinContent(bin,2);
         epass = h2->GetBinError(bin,2);
         fail = h2->GetBinContent(bin,1);
         efail = h2->GetBinError(bin,1);
         eff = (pass+fail)==0. ? -1. : pass/(pass+fail);

         passm = h2->GetBinContent(bin,3);
         epassm = h2->GetBinError(bin,3);
         effm = (passm+fail)==0. ? -1. : passm/(passm+fail);

         if(pass+fail!=0.) {
            double dfda = 1./(pass+fail) - pass/((pass+fail)*(pass+fail)); 
            double dfdb = - pass/((pass+fail)*(pass+fail)); 
            eeff = (pass+fail)==0. ? -1. :  sqrt( (dfda*epass)*(dfda*epass) + (dfdb*efail)*(dfdb*efail) );
         } else {
            eeff = -1.;
         }
         if(passm+fail!=0.) {
            double dfda = 1./(passm+fail) - passm/((passm+fail)*(passm+fail)); 
            double dfdb = - passm/((passm+fail)*(passm+fail)); 
            eeffm = (passm+fail)==0. ? -1. :  sqrt( (dfda*epassm)*(dfda*epassm) + (dfdb*efail)*(dfdb*efail) );
         } else {
            eeffm = -1.;
         }
    
         if(mode == "PASS") return pass;
         if(mode == "EPASS") return epass;
         if(mode == "FAIL") return fail;
         if(mode == "EFAIL") return efail;
         if(mode == "EFF") return eff;
         if(mode == "EEFF") return eeff;
         if(mode == "PASSMATCH") return passm;
         if(mode == "EPASSMATCH") return epassm;
         if(mode == "EFFMATCH") return effm;
         if(mode == "EEFFMATCH") return eeffm;

    
         std::cout << "TrigDec: ERROR!!!: this mode: " << mode << " is not supported" << std::endl;      
         //return -1.;
         exit(1);
    
      }

      
      
      void PrintTriggerEfficiencies(TDirectory* dir,TString selection="", TString mode="EFF") {
         std::cout << "\n\n---------------------------------------------------------------\n"
                   << " Inclusive trigger efficiencies for the defined triggers in TrigDecision" << std::endl; 
         const std::vector<TString> triggers = GetAllTrigDecisionNames();
         //find all teff histograms and print
         TIter next(dir->GetList());
//          std::cout << "Before loop over " << dir->GetList()->GetEntries() 
//                    << " keys in dir address: " << dir << std::endl;
         TObject* obj;
         while((obj = next())) {
            //std::cout << "Found an object at address: " << obj << std::endl;
            if( obj->IsA()->InheritsFrom( "TH2" )) {
               TH2F* h = (TH2F*)obj;
               TString name(h->GetName());
               if(name.EndsWith("_teff")) {
                  //check if it has correct selection
                  if(selection=="" || name.BeginsWith(selection+"_teff")) {
                     
                     std::cout << "\n*** Selection: " << name << std::endl;
                     TString error_mode = Form("E%s",mode.Data());
                     for( int it=0; it!=static_cast<int>(triggers.size()); ++it) {
		       std::cout << std::setw(15) << triggers[it] 
                                  << "  " << histTeff(it,mode,h) 
                                  << " +- "<< histTeff(it,error_mode,h) <<  std::endl;             
                     } 
                  }
               }
            }
         }
         std::cout << "\n\n---------------------------------------------------------------" << std::endl;
         return;
      } //PrintTriggerEfficiencies
      
      
      
   private:
      std::map< TString,int > m_trigdec;
      std::map< TString,bool > WarnAbsentTriggers;
};

#endif  /* __TRIGDEC_H */
