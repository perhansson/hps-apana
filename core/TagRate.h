/**************************************************************************
 **
 **   File:         TagRate.h
 **
 **   Description:  Rsponsible for reading tag rate functions
 **
 **   Author:       P. Hansson
 **
 **   Created:      
 **   Modified:
 **
 **************************************************************************/

#ifndef __TAGRATE_H
#define __TAGRATE_H

#include <map>
#include "TString.h"

typedef std::map<std::string,TH1F*> TagRateDict;


TH1F* GetHistFromFile(std::string histName,std::string fileName) {
   TDirectory* sDir = gDirectory;
   TFile file(fileName.c_str());
   if (!file.IsOpen()) {
      std::cout << "Could not open file "<<fileName
                <<" to extract " << histName << std::endl;
      return 0;
   }
   TH1F* h;
   file.GetObject(histName.c_str(),h);
   if (!h) {
      std::cout << "Could not find histogram "<<histName
                <<" in file " << fileName << std::endl;
      return 0;
   }
   sDir->cd();
   std::cout << "Found "<<histName
             <<" in file " << fileName << std::endl;
   TH1F* hh = (TH1F*)h->Clone();
   hh->SetDirectory(0);
   return hh;
}


class TagRate {
   public:
      TagRate(void) : m_init(false) {};
      ~TagRate(void) {
         for(TagRateDict::iterator i=m_tagrate.begin();i!=m_tagrate.end();++i)
            delete i->second;
      };
      
      bool initialized(void) const { return m_init;};
      void add(const std::string& name, const std::string& identifier) {
         TH1F* h = GetHistFromFile(name,m_file);
         if (!h) {
            std::cout << "ERROR TagRate for name " << name <<" was not found!" << std::endl;
            exit(-1);
         }
         m_tagrate[identifier] = h;
         
      }
      void init() {
         std::cout << "Initializing TagRate..." << std::endl;
         //Read the files hard-coded here -> FIX THIS!
         //m_file = "../../macros/TagRates/190510/TagRates_final.root";
         //m_file = "../../macros/TagRates/210510/TagRates_final.root";
         m_file = "../../macros/TagRates/290510/TagRates_final.root";
         //open file and extract the functions
         add("jetmetbtag4j3j40met400ldphi1inv_jetmetbtag4j3j40met400ldphi1inv_tagraterecotaggedpt_tagrate_final_index_Pythia_J0_6","pytpt");
         add("jetmetbtag4j3j40met400ldphi1inv_jetmetbtag4j3j40met400ldphi1inv_tagratedphirecotaggedpt_tagrate_final_index_Pythia_J0_6","pytptdphi");
         add("jetmetbtag4j3j40met400ldphi1inv_jetmetbtag4j3j40met400ldphi1inv_tagratedphiirecotaggedpt_tagrate_final_index_Pythia_J0_6","pytptdphii");
         add("jetmetbtag4j3j40met400ldphi1inv_jetmetbtag4j3j40met400ldphi1inv_tagraterecotaggedpt_tagrate_final_index_QCD_Alpgen","alppt");
         add("jetmetbtag4j3j40met400ldphi1inv_jetmetbtag4j3j40met400ldphi1inv_tagratedphirecotaggedpt_tagrate_final_index_QCD_Alpgen","alpptdphi");
         add("jetmetbtag4j3j40met400ldphi1inv_jetmetbtag4j3j40met400ldphi1inv_tagratedphiirecotaggedpt_tagrate_final_index_QCD_Alpgen","alpptdphii");         
         m_init = true;
         
      };
      
      
      double GetTagRate(TH1F* h, const double& val, std::string error="") {
         if(!initialized()) init();
         //check range
         double xmin = h->GetBinLowEdge(1);
         double xmax = h->GetXaxis()->GetBinUpEdge(h->GetNbinsX());
         int bin = -1;
         if(val<xmin||val>xmax) {
//             std::cout << "WARNING getting tag rate for "<< val 
//                       << " which is outside range of histogram ["
//                       << xmin << "," <<xmax<<"] -> using last bin closest!!"
//                       << std::endl;
            
            bin = val<xmin ? 1 : h->GetNbinsX();
         }
         else {
            bin = h->FindBin(val);
         }
         double y = -1.;
         if(error=="") y = h->GetBinContent(bin);
         else if(error=="STATU" || error=="STATD") y = h->GetBinError(bin);
         else {
            std::cout << "ERROR TagRate error " << error <<" is not defined!!" << std::endl; exit(-1);            
         }
         return y;
      }
      double GetTagRateEff(const TString& name, const double& val,std::string error="") {
         if(!initialized()) init();
         //Get the efficiency for this tag rate function
         TagRateDict::const_iterator ifound = m_tagrate.find(std::string(name.Data()));
         if(ifound==m_tagrate.end()) {
            std::cout << "ERROR TagRate for name " << name <<" was not found!" << std::endl;
            exit(-1);            
         }
         return GetTagRate(ifound->second,val,error);         
      };
      void print(void) const {
         std::cout << "  TagRate" << std::endl;
         std::cout << "    nr of fncs = " << m_tagrate.size() << std::endl;
      }
   private:
      TagRateDict m_tagrate;
      bool m_init;
      std::string m_file;
      
};

//typedef std::multimap<TString,TagRate> TagRates_dict;
//typedef std::vector<TagRate> TagRates;

#endif  /* __TAGRATE_H */
