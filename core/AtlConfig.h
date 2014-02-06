/**************************************************************************
 **
 **   File:         AtlConfig.h
 **
 **   Description:  Read AtlAna configuration
 **
 **   Author:       J. Sjolin
 **   Created:      TUE JUN  5 14:06:17 CEST 2007
 **
 **************************************************************************/

#ifndef __ATLCONFIG_H
#define __ATLCONFIG_H

#include <fstream>
#include "TString.h"

class AtlConfig {
 public:
  AtlConfig(void) {reset();};
  void reset(void) {
    m_ele_et=-1; m_ele_eta=-1; m_ele_crack=-1; m_ele_cracklow=-1;
    m_ele_crackhigh=-1; m_jetele_rem=-1; m_jetlooseele_rem=-1; m_ele_cone=-1;
    m_ele_iso=-1; m_ele_trk=-1; m_ele_em=-1; m_ele_em_simple=-1;
    m_loose_ele_iso=-1; m_loose_ele_em=-1;
    m_ele_absi=-1;
    m_muo_pt=-1; m_muo_eta=-1; m_muo_crack=-1; m_jetmu_rem=-1; m_muo_cone=-1;
    m_muo_iso=-1; m_muo_trk=-1; m_muo_chi=-1; m_muo_fitchi=-1;
    m_muo_matchchi=-1; 
    m_muo_d0_sig=-1; 
    m_muo_absi=-1;
    m_l2_jet_e=-1;
    m_jet_et=-1,m_jet_eta=-1,m_jet_goodness=-1;
    m_tau_et=-1,m_tau_eta=-1,m_tau_crack=-1;
    m_trk_p=-1;
    m_met_min=-1,m_met_sig=-1,m_obj_dr=-1;
    m_lumi=-1;m_debug=-1,m_gen_fake=-1,m_gen_fake_ele=-1,m_gen_fake_muo=-1;
    m_dupl_obj_check=-1;
    m_grl="";
  }
  void read_file(const TString & cfg) {
    char buffer[256];
    std::ifstream fh(cfg);
    if (!fh.is_open()) {
      std::cout << "AtlConfig: Error opening config file! " << std::endl;
      exit(1);
    }
    fh.getline(buffer,250);    
    while (!fh.eof()) {
      TString n(buffer);
      if (n.Contains("E_LOOSE_ISO="))
	{n.ReplaceAll("E_LOOSE_ISO=",""); m_loose_ele_iso=n.Atof();}
      if (n.Contains("E_LOOSE_EM="))
	{n.ReplaceAll("E_LOOSE_EM=",""); m_loose_ele_em=n.Atoi();}
      if (n.Contains("E_ET=")) {n.ReplaceAll("E_ET=","");m_ele_et=n.Atof();}
      if (n.Contains("E_ETA=")) {n.ReplaceAll("E_ETA=","");m_ele_eta=n.Atof();}
      if (n.Contains("E_CRACK="))
	{n.ReplaceAll("E_CRACK=","");m_ele_crack=n.Atof();}
      if (n.Contains("E_CRACKHIGH="))
	{n.ReplaceAll("E_CRACKHIGH=","");m_ele_crackhigh=n.Atof();}
      if (n.Contains("E_CRACKLOW="))
	{n.ReplaceAll("E_CRACKLOW=","");m_ele_cracklow=n.Atof();}
      if (n.Contains("E_CO=")) {n.ReplaceAll("E_CO=","");m_ele_cone=n.Atof();}
      if (n.Contains("E_ABSI="))
	{n.ReplaceAll("E_ABSI=","");m_ele_absi=n.Atoi();}
      if (n.Contains("E_ISO=")) {n.ReplaceAll("E_ISO=","");m_ele_iso=n.Atof();}
      if (n.Contains("E_TRK=")) {n.ReplaceAll("E_TRK=","");m_ele_trk=n.Atof();}
      if (n.Contains("E_EM=")) {n.ReplaceAll("E_EM=","");m_ele_em=n.Atoi();}
      if (n.Contains("E_EMSIMPLE=")) {n.ReplaceAll("E_EMSIMPLE=","");m_ele_em_simple=n.Atoi();}
      if (n.Contains("M_PT=")) {n.ReplaceAll("M_PT=","");m_muo_pt=n.Atof();}
      if (n.Contains("M_ETA=")) {n.ReplaceAll("M_ETA=","");m_muo_eta=n.Atof();}
      if (n.Contains("M_CRACK="))
	{n.ReplaceAll("M_CRACK=","");m_muo_crack=n.Atof();}
      if (n.Contains("M_CO=")) {n.ReplaceAll("M_CO=","");m_muo_cone=n.Atof();}
      if (n.Contains("M_ABSI="))
	{n.ReplaceAll("M_ABSI=","");m_muo_absi=n.Atoi();}
      if (n.Contains("M_ISO=")) {n.ReplaceAll("M_ISO=","");m_muo_iso=n.Atof();}
      if (n.Contains("M_TRK=")) {n.ReplaceAll("M_TRK=","");m_muo_trk=n.Atof();}
      if (n.Contains("M_CHI=")) {n.ReplaceAll("M_CHI=","");m_muo_chi=n.Atof();}
      if (n.Contains("M_D0_SIG="))
	{n.ReplaceAll("M_D0_SIG=",""); m_muo_d0_sig=n.Atof();}
      if (n.Contains("M_FITCHI="))
	{n.ReplaceAll("M_FITCHI=","");m_muo_fitchi=n.Atof();}
      if (n.Contains("M_MATCHCHI="))
	{n.ReplaceAll("M_MATCHCHI=","");m_muo_matchchi=n.Atof();}
      if (n.Contains("L2_J_E=")) {n.ReplaceAll("L2_J_E=","");m_l2_jet_e=n.Atof();}
      if (n.Contains("J_ET=")) {n.ReplaceAll("J_ET=","");m_jet_et=n.Atof();}
      if (n.Contains("J_ETA=")) {n.ReplaceAll("J_ETA=","");m_jet_eta=n.Atof();}
      if (n.Contains("J_GOODNESS=")) {n.ReplaceAll("J_GOODNESS=","");m_jet_goodness=n.Atoi();}
      if (n.Contains("TRK_P=")) {n.ReplaceAll("TRK_P=","");m_trk_p=n.Atof();}
      if (n.Contains("T_ET=")) {n.ReplaceAll("T_ET=","");m_tau_et=n.Atof();}
      if (n.Contains("T_ETA=")) {n.ReplaceAll("T_ETA=","");m_tau_eta=n.Atof();}
      if (n.Contains("T_CRACK="))
	{n.ReplaceAll("T_CRACK=","");m_tau_crack=n.Atof();}
      if (n.Contains("MET_MIN="))
	{n.ReplaceAll("MET_MIN=","");m_met_min=n.Atof();}
      if (n.Contains("MET_SIG="))
	{n.ReplaceAll("MET_SIG=","");m_met_sig=n.Atof();}
      if (n.Contains("OBJ_DR="))
	{n.ReplaceAll("OBJ_DR=","");m_obj_dr=n.Atof();}
      if (n.Contains("LUMI=")) {n.ReplaceAll("LUMI=","");m_lumi=n.Atof();}
      if (n.Contains("DEBUG=")) {n.ReplaceAll("DEBUG=","");m_debug=n.Atoi();}
      if (n.Contains("REM_JETELE="))
	{n.ReplaceAll("REM_JETELE=","");m_jetele_rem=n.Atoi();}
      if (n.Contains("REM_JETLOOSEELE="))
	{n.ReplaceAll("REM_JETLOOSEELE=","");m_jetlooseele_rem=n.Atoi();}
      if (n.Contains("REM_JETMU="))
	{n.ReplaceAll("REM_JETMU=","");m_jetmu_rem=n.Atoi();}
      if (n.Contains("GEN_FAKE="))
	{n.ReplaceAll("GEN_FAKE=","");m_gen_fake=n.Atoi();}
      if (n.Contains("GEN_FAKE_ELE="))
	{n.ReplaceAll("GEN_FAKE_ELE=","");m_gen_fake_ele=n.Atoi();}
      if (n.Contains("GEN_FAKE_MUO="))
	{n.ReplaceAll("GEN_FAKE_MUO=","");m_gen_fake_muo=n.Atoi();}
      if (n.Contains("DUPL_OBJ_CHECK="))
	{n.ReplaceAll("DUPL_OBJ_CHECK=","");m_dupl_obj_check=n.Atoi();}
      if (n.Contains("GRL="))
	{n.ReplaceAll("GRL=","");m_grl=n;}

      fh.getline(buffer,250);
    }
    //verify();
    print();
  }
  void verify(void) {
    if (m_ele_et<0) {std::cout << "ERROR E_ET!" << std::endl; exit(1);}
    if (m_ele_eta<0) {std::cout << "ERROR E_ETA!" << std::endl; exit(1);}
    if (m_ele_cone<0) {std::cout << "ERROR E_CO!" << std::endl; exit(1);}
    if (m_ele_absi<0) {std::cout << "ERROR E_ABSI!" << std::endl; exit(1);}
    if (m_ele_iso<0) {std::cout << "ERROR E_ISO!" << std::endl; exit(1);}
    if (m_ele_trk<0) {std::cout << "ERROR E_TRK!" << std::endl; exit(1);}
    if (m_ele_em<0) {std::cout << "ERROR E_EM!" << std::endl; exit(1);}
    if (m_ele_em_simple<0) {std::cout << "ERROR E_EMSIMPLE!" << std::endl; exit(1);}
    if (m_ele_crack<0) {std::cout << "ERROR E_CRACK!" << std::endl; exit(1);}
    if (m_ele_crackhigh<0)
      {std::cout << "ERROR E_CRACKHIGH!" << std::endl; exit(1);}
    if (m_loose_ele_iso<0) {
      std::cout << "ERROR LOOSE_ISO! " << m_loose_ele_iso
		<< std::endl; exit(1);
    }
    if (m_loose_ele_em<0) {
      std::cout << "ERROR LOOSE_EM! " << m_loose_ele_em
		<< std::endl; exit(1);
    }
    if (m_jetele_rem<0)
      {std::cout << "ERROR REM_JETELE!" << std::endl; exit(1);}
    if (m_jetlooseele_rem<0)
      {std::cout << "ERROR REM_JETLOOSEELE!" << std::endl; exit(1);}
    if (m_ele_crack<0) {std::cout << "ERROR E_CRACK!" << std::endl; exit(1);}
    if (m_muo_pt<0) {std::cout << "ERROR M_PT!" << std::endl; exit(1);}
    if (m_muo_eta<0) {std::cout << "ERROR M_ETA!" << std::endl; exit(1);}
    if (m_muo_crack<0) {std::cout << "ERROR M_CRACK!" << std::endl; exit(1);}
    if (m_jetmu_rem<0) {std::cout << "ERROR REM_JETMU!" << std::endl; exit(1);}
    if (m_muo_cone<0) {std::cout << "ERROR M_CO!" << std::endl; exit(1);}
    if (m_muo_absi<0) {std::cout << "ERROR M_ABSI!" << std::endl; exit(1);}
    if (m_muo_iso<0) {std::cout << "ERROR M_ISO!" << std::endl; exit(1);}
    if (m_muo_trk<0) {std::cout << "ERROR M_TRK!" << std::endl; exit(1);}
    if (m_muo_chi<0) {std::cout << "ERROR M_CHI!" << std::endl; exit(1);}
    if (m_muo_d0_sig<0) {std::cout << "ERROR M_D0_SIG!" << std::endl; exit(1);}
    if (m_muo_fitchi<0) {std::cout << "ERROR M_FITCHI!" << std::endl; exit(1);}
    if (m_muo_matchchi<0)
      {std::cout << "ERROR M_MATCHCHI!" << std::endl; exit(1);}
    if (m_l2_jet_e<0) {std::cout << "ERROR L2_J_E!" << std::endl; exit(1);}
    if (m_jet_et<0) {std::cout << "ERROR J_ET!" << std::endl; exit(1);}
    if (m_jet_eta<0) {std::cout << "ERROR J_ETA!" << std::endl; exit(1);}
    if (m_jet_goodness<0) {std::cout << "ERROR J_GOODNESS!" << std::endl; exit(1);}
    if (m_trk_p<0) {std::cout << "ERROR TRK_P!" << std::endl; exit(1);}
    if (m_tau_et<0) {std::cout << "ERROR T_ET!" << std::endl; exit(1);}
    if (m_tau_eta<0) {std::cout << "ERROR T_ETA!" << std::endl; exit(1);}
    if (m_tau_crack<0) {std::cout << "ERROR T_CRACK!" << std::endl; exit(1);}
    if (m_met_min<0) {std::cout << "ERROR MET_MIN!" << std::endl; exit(1);}
    if (m_met_sig<0) {std::cout << "ERROR MET_SIG!" << std::endl; exit(1);}
    if (m_obj_dr<0) {std::cout << "ERROR OBJ_DR!" << std::endl; exit(1);}
    if (m_lumi<0) {std::cout << "ERROR LUMI!" << std::endl; exit(1);}
    if (m_debug<0) {std::cout << "ERROR DEBUG!" << std::endl; exit(1);}
    if (m_gen_fake<0) {std::cout << "ERROR GEN_FAKE!" << std::endl; exit(1);}
    if (m_gen_fake_ele<0)
      {std::cout << "ERROR GEN_FAKE_ELE!" << std::endl; exit(1);}
    if (m_gen_fake_muo<0)
      {std::cout << "ERROR GEN_FAKE_MUO!" << std::endl; exit(1);}
    if (m_dupl_obj_check<0)
      {std::cout << "ERROR DUPL_OBJ_CHECK!" << std::endl; exit(1);}
    if (m_grl!=""&&!m_grl.Contains(".xml"))
      {std::cout << "ERROR GRL_CHECK!" << std::endl; exit(1);}
  }
  void print(void) {
    std::cout << "AtlAna configuration" << std::endl;
    std::cout << "  Debug mode            : " << get_debug() << std::endl;
    std::cout << "  GRL                   : " << get_grl() << std::endl;
    std::cout << "  Fake mode             : " << get_gen_fake() << std::endl;
    std::cout << "  Luminosity            : " << get_lumi() << std::endl;
    std::cout << "  MET min. ET           : " << get_met_min() << std::endl;
    std::cout << "  MET significance      : " << get_met_sig() << std::endl;
    std::cout << "  Object deltaR         : " << get_obj_dr() << std::endl;
    std::cout << "  Jet-ele removal       : " << get_jetele_rem() << std::endl;
    std::cout << "  Jet-mu removal        : " << get_jetmu_rem() << std::endl;
    std::cout << "  Jet-looseele removal  : " << get_jetlooseele_rem()
	      << std::endl;
    std::cout << "  Check duplicate objects:" << get_dupl_obj_check()
	      << std::endl;
    std::cout << "  Electron ET           : " << get_ele_et() << std::endl;
    std::cout << "  Electron ETA          : " << get_ele_eta() << std::endl;
    std::cout << "  Electron rm crack     : " << get_ele_crack() << std::endl;
    std::cout << "  Electron crack H      : " << get_ele_crackhigh()
	      << std::endl;
    std::cout << "  Electron crack L      : " << get_ele_cracklow()
	      << std::endl;
    std::cout << "  Electron cone         : " << get_ele_cone() << std::endl;
    std::cout << "  Electron abs iso      : " << get_ele_absi() << std::endl;
    std::cout << "  Electron iso          : " << get_ele_iso() << std::endl;
    std::cout << "  Electron trkiso       : " << get_ele_trk() << std::endl;
    std::cout << "  Electron isEM simple  : " << get_ele_em_simple() << std::endl;
    std::cout << "  Electron isEM         : " << get_ele_em() << std::endl;
    std::cout << "  Loose Elec. iso       : " << get_loose_ele_iso()
	      << std::endl;
    std::cout << "  Loose Elec. IsEM      : " << get_loose_ele_em()
	      << std::endl;
    std::cout << "  Muon     pT           : " << get_muo_pt() << std::endl;
    std::cout << "  Muon     eta          : " << get_muo_eta() << std::endl;
    std::cout << "  Muon     rm crack     : " << get_muo_crack() << std::endl;
    std::cout << "  Muon     cone         : " << get_muo_cone() << std::endl;
    std::cout << "  Muon     abs iso      : " << get_muo_absi() << std::endl;
    std::cout << "  Muon     iso          : " << get_muo_iso() << std::endl;
    std::cout << "  Muon     trkiso       : " << get_muo_trk() << std::endl;
    std::cout << "  Muon     d0 signi.    : " << get_muo_d0_sig() << std::endl;
    std::cout << "  Muon     trkchi2      : " << get_muo_chi2() << std::endl;
    std::cout << "  Muon  fittrkchi2      : " << get_muo_fitchi2()
	      << std::endl;
    std::cout << "  Muon   matchchi2      : " << get_muo_matchchi2()
	      << std::endl;
    std::cout << "  Jet      ET           : " << get_jet_et() << std::endl;
    std::cout << "  Jet      ETA          : " << get_jet_eta() << std::endl;
    std::cout << "  Jet      GOODNESS          : " << get_jet_goodness() << std::endl;
    std::cout << "  Tau      ET           : " << get_tau_et() << std::endl;
    std::cout << "  Tau      ETA          : " << get_tau_eta() << std::endl;
    std::cout << "  Tau      CRACK        : " << get_tau_crack() << std::endl;
    std::cout << "  L2 Jet   E            : " << get_l2_jet_e() << std::endl;
    std::cout << "  Track P            : " << get_trk_p() << std::endl;
  }
  float get_lumi(void) {return m_lumi;};
  int get_debug(void) {return m_debug;};
  int get_gen_fake(void) {return m_gen_fake;};
  int get_gen_fake_ele(void) {return m_gen_fake_ele;};
  int get_gen_fake_muo(void) {return m_gen_fake_muo;};
  float get_met_min(void) {return m_met_min;};
  float get_met_sig(void) {return m_met_sig;};
  float get_obj_dr(void) {return m_obj_dr;};
  float get_ele_et(void) {return m_ele_et;};
  float get_ele_eta(void) {return m_ele_eta;};
  float get_ele_crack(void) {return m_ele_crack;};
  float get_ele_crackhigh(void) {return m_ele_crackhigh;};
  float get_ele_cracklow(void) {return m_ele_cracklow;};
  float get_jetele_rem(void) {return m_jetele_rem;};
  float get_jetlooseele_rem(void) {return m_jetlooseele_rem;};
  float get_ele_cone(void) {return m_ele_cone;};
  int get_ele_absi(void) {return m_ele_absi;};
  float get_ele_iso(void) {return m_ele_iso;};
  float get_ele_trk(void) {return m_ele_trk;};
  int get_ele_em_simple(void) {return m_ele_em_simple;};
  int get_ele_em(void) {return m_ele_em;};
  float get_loose_ele_iso(void) {return m_loose_ele_iso;};
  int get_loose_ele_em(void) {return m_loose_ele_em;};
  float get_muo_pt(void) {return m_muo_pt;};
  float get_muo_eta(void) {return m_muo_eta;};
  float get_muo_crack(void) {return m_muo_crack;};
  float get_jetmu_rem(void) {return m_jetmu_rem;};
  float get_muo_cone(void) {return m_muo_cone;};
  int get_muo_absi(void) {return m_muo_absi;};
  float get_muo_iso(void) {return m_muo_iso;};
  float get_muo_trk(void) {return m_muo_trk;};
  float get_muo_chi2(void) {return m_muo_chi;};
  float get_muo_d0_sig(void) {return m_muo_d0_sig;};
  float get_muo_fitchi2(void) {return m_muo_fitchi;};
  float get_muo_matchchi2(void) {return m_muo_matchchi;};
  float get_l2_jet_e(void) {return m_l2_jet_e;};
  float get_jet_et(void) {return m_jet_et;};
  float get_jet_eta(void) {return m_jet_eta;};
  int get_jet_goodness(void) {return m_jet_goodness;};
  float get_trk_p(void) {return m_trk_p;};
  float get_tau_et(void) {return m_tau_et;};
  float get_tau_eta(void) {return m_tau_eta;};
  float get_tau_crack(void) {return m_tau_crack;};
  int get_dupl_obj_check(void) {return m_dupl_obj_check;};
  TString get_grl(void) {return m_grl;};
  
 private:
  float m_ele_et,m_ele_eta,m_ele_crack,m_ele_crackhigh,m_ele_cracklow,
    m_ele_cone,m_ele_iso,m_ele_trk;
  int m_ele_em_simple,m_ele_em,m_ele_absi,m_jetele_rem,m_jetlooseele_rem;
  float m_loose_ele_iso;
  int  m_loose_ele_em;
  float m_muo_pt,m_muo_eta,m_muo_crack,m_muo_cone,m_muo_iso,m_muo_trk,
    m_muo_chi,m_muo_fitchi,m_muo_matchchi,m_muo_d0_sig;
  float m_jet_et,m_jet_eta;
  float m_l2_jet_e;
  int m_jet_goodness;
  float m_trk_p;
  float m_tau_et,m_tau_eta,m_tau_crack;
  int m_muo_absi,m_debug,m_jetmu_rem,m_gen_fake,m_gen_fake_muo,m_gen_fake_ele;
  float m_met_min,m_met_sig,m_obj_dr,m_lumi;
  int m_dupl_obj_check; 
  TString m_grl;
};

#endif  /* __ATLCONFIG_H */
