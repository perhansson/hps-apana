/**************************************************************************
 **
 **   File:         FileEvent_dst001.h
 **
 **   Description:  Interface from DST to AtlEvent
 ** 
 **   Author:       phansson@slac.stanford.edu
 **
 **   Created:      Feb 5, 2014
 **   Modified:     
 **                   
 **************************************************************************/ 

#ifndef __FILEEVENT_DST001_H
#define __FILEEVENT_DST001_H

#include <TRef.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TBranch.h>
#include <TString.h>
#include <iostream>
#include <list>

#include "EventSrc.h"
#include "AtlEvent.h"


   const Int_t kMaxtracks = 1;
   const Int_t kMaxsvt_hits = 5;
   const Int_t kMaxecal_clusters = 3;
   const Int_t kMaxecal_hits = 5;
   const Int_t kMaxmuon_clusters = 1;
   const Int_t kMaxfs_recon_particles = 1;
   const Int_t kMaxvtx_recon_particles = 1;
   const Int_t kMaxgbl_tracks_data = 1;


class FileEvent_dst001 : public EventSrc {
public:  
  FileEvent_dst001() : fChain(NULL) {}
  bool copy_to_interface(AtlEvent &atl);
  int Open(std::list<TString> filelist);
  void SetBranches(void);
  void DisableBranches(void);
  double GetNEntries(void) {return double(fChain->GetEntries());} 
  void GetEntry(int entry) {fChain->GetEntry(entry);}
  
private:


   TChain          *fChain;   //!pointer to the analyzed TTree or TChain


   Int_t           fCurrent; //!current Tree number in a TChain


   /*
    * ===========================================================================
    * Put the declaration of leaf types below (typically from TTree->MakeClass())
    */

   // Declaration of leaf types



   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           tracks_;
   UInt_t          tracks_fUniqueID[kMaxtracks];   //[tracks_]
   UInt_t          tracks_fBits[kMaxtracks];   //[tracks_]
   Int_t           tracks_n_hits[kMaxtracks];   //[tracks_]
   Double_t        tracks_px[kMaxtracks];   //[tracks_]
   Double_t        tracks_py[kMaxtracks];   //[tracks_]
   Double_t        tracks_pz[kMaxtracks];   //[tracks_]
   Double_t        tracks_d0[kMaxtracks];   //[tracks_]
   Double_t        tracks_phi[kMaxtracks];   //[tracks_]
   Double_t        tracks_omega[kMaxtracks];   //[tracks_]
   Double_t        tracks_tan_lambda[kMaxtracks];   //[tracks_]
   Double_t        tracks_z0[kMaxtracks];   //[tracks_]
   Double_t        tracks_chi_squared[kMaxtracks];   //[tracks_]
   Double_t        tracks_charge[kMaxtracks];   //[tracks_]
   Int_t           svt_hits_;
   UInt_t          svt_hits_fUniqueID[kMaxsvt_hits];   //[svt_hits_]
   UInt_t          svt_hits_fBits[kMaxsvt_hits];   //[svt_hits_]
   Int_t           svt_hits_hit_layer[kMaxsvt_hits];   //[svt_hits_]
   Double_t        svt_hits_x[kMaxsvt_hits];   //[svt_hits_]
   Double_t        svt_hits_y[kMaxsvt_hits];   //[svt_hits_]
   Double_t        svt_hits_z[kMaxsvt_hits];   //[svt_hits_]
   Double_t        svt_hits_x_err[kMaxsvt_hits];   //[svt_hits_]
   Double_t        svt_hits_y_err[kMaxsvt_hits];   //[svt_hits_]
   Double_t        svt_hits_z_err[kMaxsvt_hits];   //[svt_hits_]
   Int_t           ecal_clusters_;
   UInt_t          ecal_clusters_fUniqueID[kMaxecal_clusters];   //[ecal_clusters_]
   UInt_t          ecal_clusters_fBits[kMaxecal_clusters];   //[ecal_clusters_]
   TRef            ecal_clusters_seed_hit[kMaxecal_clusters];
   Int_t           ecal_clusters_n_ecal_hits[kMaxecal_clusters];   //[ecal_clusters_]
   Double_t        ecal_clusters_x[kMaxecal_clusters];   //[ecal_clusters_]
   Double_t        ecal_clusters_y[kMaxecal_clusters];   //[ecal_clusters_]
   Double_t        ecal_clusters_z[kMaxecal_clusters];   //[ecal_clusters_]
   Double_t        ecal_clusters_energy[kMaxecal_clusters];   //[ecal_clusters_]
   Double_t        ecal_clusters_hit_time[kMaxecal_clusters];   //[ecal_clusters_]
   Double_t        ecal_clusters_m2[kMaxecal_clusters];   //[ecal_clusters_]
   Double_t        ecal_clusters_m3[kMaxecal_clusters];   //[ecal_clusters_]
   Int_t           ecal_hits_;
   UInt_t          ecal_hits_fUniqueID[kMaxecal_hits];   //[ecal_hits_]
   UInt_t          ecal_hits_fBits[kMaxecal_hits];   //[ecal_hits_]
   Double_t        ecal_hits_energy[kMaxecal_hits];   //[ecal_hits_]
   Int_t           ecal_hits_index_x[kMaxecal_hits];   //[ecal_hits_]
   Int_t           ecal_hits_index_y[kMaxecal_hits];   //[ecal_hits_]
   Double_t        ecal_hits_hit_x[kMaxecal_hits];   //[ecal_hits_]
   Double_t        ecal_hits_hit_y[kMaxecal_hits];   //[ecal_hits_]
   Double_t        ecal_hits_hit_z[kMaxecal_hits];   //[ecal_hits_]
   Int_t           muon_clusters_;
   UInt_t          muon_clusters_fUniqueID[kMaxmuon_clusters];   //[muon_clusters_]
   UInt_t          muon_clusters_fBits[kMaxmuon_clusters];   //[muon_clusters_]
   Int_t           fs_recon_particles_;
   UInt_t          fs_recon_particles_fUniqueID[kMaxfs_recon_particles];   //[fs_recon_particles_]
   UInt_t          fs_recon_particles_fBits[kMaxfs_recon_particles];   //[fs_recon_particles_]
   TRef            fs_recon_particles_track[kMaxfs_recon_particles];
   TRef            fs_recon_particles_ecal_cluster[kMaxfs_recon_particles];
   Double_t        fs_recon_particles_vtx_x[kMaxfs_recon_particles];   //[fs_recon_particles_]
   Double_t        fs_recon_particles_vtx_y[kMaxfs_recon_particles];   //[fs_recon_particles_]
   Double_t        fs_recon_particles_vtx_z[kMaxfs_recon_particles];   //[fs_recon_particles_]
   Int_t           vtx_recon_particles_;
   UInt_t          vtx_recon_particles_fUniqueID[kMaxvtx_recon_particles];   //[vtx_recon_particles_]
   UInt_t          vtx_recon_particles_fBits[kMaxvtx_recon_particles];   //[vtx_recon_particles_]
   TRef            vtx_recon_particles_track[kMaxvtx_recon_particles];
   TRef            vtx_recon_particles_ecal_cluster[kMaxvtx_recon_particles];
   Double_t        vtx_recon_particles_vtx_x[kMaxvtx_recon_particles];   //[vtx_recon_particles_]
   Double_t        vtx_recon_particles_vtx_y[kMaxvtx_recon_particles];   //[vtx_recon_particles_]
   Double_t        vtx_recon_particles_vtx_z[kMaxvtx_recon_particles];   //[vtx_recon_particles_]
   Int_t           gbl_tracks_data_;
   UInt_t          gbl_tracks_data_fUniqueID[kMaxgbl_tracks_data];   //[gbl_tracks_data_]
   UInt_t          gbl_tracks_data_fBits[kMaxgbl_tracks_data];   //[gbl_tracks_data_]
   Int_t           event_number;
   Int_t           run_number;
   Int_t           n_tracks;
   Int_t           n_hits;
   Int_t           n_ecal_clusters;
   Int_t           n_ecal_hits;
   Int_t           n_muon_clusters;
   Int_t           n_fs_recon_particles;
   Int_t           n_vtx_recon_particles;
   Int_t           n_gbl_tracks_data;
   std::vector<int>     trigger_bits;

   // List of branches
   TBranch        *b_Event_fUniqueID;   //!
   TBranch        *b_Event_fBits;   //!
   TBranch        *b_Event_tracks_;   //!
   TBranch        *b_tracks_fUniqueID;   //!
   TBranch        *b_tracks_fBits;   //!
   TBranch        *b_tracks_n_hits;   //!
   TBranch        *b_tracks_px;   //!
   TBranch        *b_tracks_py;   //!
   TBranch        *b_tracks_pz;   //!
   TBranch        *b_tracks_d0;   //!
   TBranch        *b_tracks_phi;   //!
   TBranch        *b_tracks_omega;   //!
   TBranch        *b_tracks_tan_lambda;   //!
   TBranch        *b_tracks_z0;   //!
   TBranch        *b_tracks_chi_squared;   //!
   TBranch        *b_tracks_charge;   //!
   TBranch        *b_Event_svt_hits_;   //!
   TBranch        *b_svt_hits_fUniqueID;   //!
   TBranch        *b_svt_hits_fBits;   //!
   TBranch        *b_svt_hits_hit_layer;   //!
   TBranch        *b_svt_hits_x;   //!
   TBranch        *b_svt_hits_y;   //!
   TBranch        *b_svt_hits_z;   //!
   TBranch        *b_svt_hits_x_err;   //!
   TBranch        *b_svt_hits_y_err;   //!
   TBranch        *b_svt_hits_z_err;   //!
   TBranch        *b_Event_ecal_clusters_;   //!
   TBranch        *b_ecal_clusters_fUniqueID;   //!
   TBranch        *b_ecal_clusters_fBits;   //!
   TBranch        *b_ecal_clusters_seed_hit;   //!
   TBranch        *b_ecal_clusters_n_ecal_hits;   //!
   TBranch        *b_ecal_clusters_x;   //!
   TBranch        *b_ecal_clusters_y;   //!
   TBranch        *b_ecal_clusters_z;   //!
   TBranch        *b_ecal_clusters_energy;   //!
   TBranch        *b_ecal_clusters_hit_time;   //!
   TBranch        *b_ecal_clusters_m2;   //!
   TBranch        *b_ecal_clusters_m3;   //!
   TBranch        *b_Event_ecal_hits_;   //!
   TBranch        *b_ecal_hits_fUniqueID;   //!
   TBranch        *b_ecal_hits_fBits;   //!
   TBranch        *b_ecal_hits_energy;   //!
   TBranch        *b_ecal_hits_index_x;   //!
   TBranch        *b_ecal_hits_index_y;   //!
   TBranch        *b_ecal_hits_hit_x;   //!
   TBranch        *b_ecal_hits_hit_y;   //!
   TBranch        *b_ecal_hits_hit_z;   //!
   TBranch        *b_Event_muon_clusters_;   //!
   TBranch        *b_muon_clusters_fUniqueID;   //!
   TBranch        *b_muon_clusters_fBits;   //!
   TBranch        *b_Event_fs_recon_particles_;   //!
   TBranch        *b_fs_recon_particles_fUniqueID;   //!
   TBranch        *b_fs_recon_particles_fBits;   //!
   TBranch        *b_fs_recon_particles_track;   //!
   TBranch        *b_fs_recon_particles_ecal_cluster;   //!
   TBranch        *b_fs_recon_particles_vtx_x;   //!
   TBranch        *b_fs_recon_particles_vtx_y;   //!
   TBranch        *b_fs_recon_particles_vtx_z;   //!
   TBranch        *b_Event_vtx_recon_particles_;   //!
   TBranch        *b_vtx_recon_particles_fUniqueID;   //!
   TBranch        *b_vtx_recon_particles_fBits;   //!
   TBranch        *b_vtx_recon_particles_track;   //!
   TBranch        *b_vtx_recon_particles_ecal_cluster;   //!
   TBranch        *b_vtx_recon_particles_vtx_x;   //!
   TBranch        *b_vtx_recon_particles_vtx_y;   //!
   TBranch        *b_vtx_recon_particles_vtx_z;   //!
   TBranch        *b_Event_gbl_tracks_data_;   //!
   TBranch        *b_gbl_tracks_data_fUniqueID;   //!
   TBranch        *b_gbl_tracks_data_fBits;   //!
   TBranch        *b_Event_event_number;   //!
   TBranch        *b_Event_run_number;   //!
   TBranch        *b_Event_n_tracks;   //!
   TBranch        *b_Event_n_hits;   //!
   TBranch        *b_Event_n_ecal_clusters;   //!
   TBranch        *b_Event_n_ecal_hits;   //!
   TBranch        *b_Event_n_muon_clusters;   //!
   TBranch        *b_Event_n_fs_recon_particles;   //!
   TBranch        *b_Event_n_vtx_recon_particles;   //!
   TBranch        *b_Event_n_gbl_tracks_data;   //!
   TBranch        *b_Event_trigger_bits;   //!





};

#endif  /* __FILEEVENT_DST001_H */






