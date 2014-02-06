//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Feb  5 16:52:14 2014 by ROOT version 5.34/14
// from TTree HPS_Event/HPS event tree
// found on file: hps_dst001.root
//////////////////////////////////////////////////////////

#ifndef HPS_Event_h
#define HPS_Event_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TObject.h>

// Fixed size dimensions of array or collections stored in the TTree if any.
const Int_t kMaxtracks = 1;
const Int_t kMaxsvt_hits = 5;
const Int_t kMaxecal_clusters = 3;
const Int_t kMaxecal_hits = 5;
const Int_t kMaxmuon_clusters = 1;
const Int_t kMaxfs_recon_particles = 1;
const Int_t kMaxvtx_recon_particles = 1;
const Int_t kMaxgbl_tracks_data = 1;

class HPS_Event {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //HpsEvent        *Event;
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
   vector<int>     trigger_bits;

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

   HPS_Event(TTree *tree=0);
   virtual ~HPS_Event();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef HPS_Event_cxx
HPS_Event::HPS_Event(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("hps_dst001.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("hps_dst001.root");
      }
      f->GetObject("HPS_Event",tree);

   }
   Init(tree);
}

HPS_Event::~HPS_Event()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HPS_Event::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HPS_Event::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void HPS_Event::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_Event_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_Event_fBits);
   fChain->SetBranchAddress("tracks", &tracks_, &b_Event_tracks_);
   fChain->SetBranchAddress("tracks.fUniqueID", tracks_fUniqueID, &b_tracks_fUniqueID);
   fChain->SetBranchAddress("tracks.fBits", tracks_fBits, &b_tracks_fBits);
   fChain->SetBranchAddress("tracks.n_hits", tracks_n_hits, &b_tracks_n_hits);
   fChain->SetBranchAddress("tracks.px", tracks_px, &b_tracks_px);
   fChain->SetBranchAddress("tracks.py", tracks_py, &b_tracks_py);
   fChain->SetBranchAddress("tracks.pz", tracks_pz, &b_tracks_pz);
   fChain->SetBranchAddress("tracks.d0", tracks_d0, &b_tracks_d0);
   fChain->SetBranchAddress("tracks.phi", tracks_phi, &b_tracks_phi);
   fChain->SetBranchAddress("tracks.omega", tracks_omega, &b_tracks_omega);
   fChain->SetBranchAddress("tracks.tan_lambda", tracks_tan_lambda, &b_tracks_tan_lambda);
   fChain->SetBranchAddress("tracks.z0", tracks_z0, &b_tracks_z0);
   fChain->SetBranchAddress("tracks.chi_squared", tracks_chi_squared, &b_tracks_chi_squared);
   fChain->SetBranchAddress("tracks.charge", tracks_charge, &b_tracks_charge);
   fChain->SetBranchAddress("svt_hits", &svt_hits_, &b_Event_svt_hits_);
   fChain->SetBranchAddress("svt_hits.fUniqueID", svt_hits_fUniqueID, &b_svt_hits_fUniqueID);
   fChain->SetBranchAddress("svt_hits.fBits", svt_hits_fBits, &b_svt_hits_fBits);
   fChain->SetBranchAddress("svt_hits.hit_layer", svt_hits_hit_layer, &b_svt_hits_hit_layer);
   fChain->SetBranchAddress("svt_hits.x", svt_hits_x, &b_svt_hits_x);
   fChain->SetBranchAddress("svt_hits.y", svt_hits_y, &b_svt_hits_y);
   fChain->SetBranchAddress("svt_hits.z", svt_hits_z, &b_svt_hits_z);
   fChain->SetBranchAddress("svt_hits.x_err", svt_hits_x_err, &b_svt_hits_x_err);
   fChain->SetBranchAddress("svt_hits.y_err", svt_hits_y_err, &b_svt_hits_y_err);
   fChain->SetBranchAddress("svt_hits.z_err", svt_hits_z_err, &b_svt_hits_z_err);
   fChain->SetBranchAddress("ecal_clusters", &ecal_clusters_, &b_Event_ecal_clusters_);
   fChain->SetBranchAddress("ecal_clusters.fUniqueID", ecal_clusters_fUniqueID, &b_ecal_clusters_fUniqueID);
   fChain->SetBranchAddress("ecal_clusters.fBits", ecal_clusters_fBits, &b_ecal_clusters_fBits);
   fChain->SetBranchAddress("ecal_clusters.seed_hit", ecal_clusters_seed_hit, &b_ecal_clusters_seed_hit);
   fChain->SetBranchAddress("ecal_clusters.n_ecal_hits", ecal_clusters_n_ecal_hits, &b_ecal_clusters_n_ecal_hits);
   fChain->SetBranchAddress("ecal_clusters.x", ecal_clusters_x, &b_ecal_clusters_x);
   fChain->SetBranchAddress("ecal_clusters.y", ecal_clusters_y, &b_ecal_clusters_y);
   fChain->SetBranchAddress("ecal_clusters.z", ecal_clusters_z, &b_ecal_clusters_z);
   fChain->SetBranchAddress("ecal_clusters.energy", ecal_clusters_energy, &b_ecal_clusters_energy);
   fChain->SetBranchAddress("ecal_clusters.hit_time", ecal_clusters_hit_time, &b_ecal_clusters_hit_time);
   fChain->SetBranchAddress("ecal_clusters.m2", ecal_clusters_m2, &b_ecal_clusters_m2);
   fChain->SetBranchAddress("ecal_clusters.m3", ecal_clusters_m3, &b_ecal_clusters_m3);
   fChain->SetBranchAddress("ecal_hits", &ecal_hits_, &b_Event_ecal_hits_);
   fChain->SetBranchAddress("ecal_hits.fUniqueID", ecal_hits_fUniqueID, &b_ecal_hits_fUniqueID);
   fChain->SetBranchAddress("ecal_hits.fBits", ecal_hits_fBits, &b_ecal_hits_fBits);
   fChain->SetBranchAddress("ecal_hits.energy", ecal_hits_energy, &b_ecal_hits_energy);
   fChain->SetBranchAddress("ecal_hits.index_x", ecal_hits_index_x, &b_ecal_hits_index_x);
   fChain->SetBranchAddress("ecal_hits.index_y", ecal_hits_index_y, &b_ecal_hits_index_y);
   fChain->SetBranchAddress("ecal_hits.hit_x", ecal_hits_hit_x, &b_ecal_hits_hit_x);
   fChain->SetBranchAddress("ecal_hits.hit_y", ecal_hits_hit_y, &b_ecal_hits_hit_y);
   fChain->SetBranchAddress("ecal_hits.hit_z", ecal_hits_hit_z, &b_ecal_hits_hit_z);
   fChain->SetBranchAddress("muon_clusters", &muon_clusters_, &b_Event_muon_clusters_);
   fChain->SetBranchAddress("muon_clusters.fUniqueID", &muon_clusters_fUniqueID, &b_muon_clusters_fUniqueID);
   fChain->SetBranchAddress("muon_clusters.fBits", &muon_clusters_fBits, &b_muon_clusters_fBits);
   fChain->SetBranchAddress("fs_recon_particles", &fs_recon_particles_, &b_Event_fs_recon_particles_);
   fChain->SetBranchAddress("fs_recon_particles.fUniqueID", &fs_recon_particles_fUniqueID, &b_fs_recon_particles_fUniqueID);
   fChain->SetBranchAddress("fs_recon_particles.fBits", &fs_recon_particles_fBits, &b_fs_recon_particles_fBits);
   fChain->SetBranchAddress("fs_recon_particles.track", &fs_recon_particles_track, &b_fs_recon_particles_track);
   fChain->SetBranchAddress("fs_recon_particles.ecal_cluster", &fs_recon_particles_ecal_cluster, &b_fs_recon_particles_ecal_cluster);
   fChain->SetBranchAddress("fs_recon_particles.vtx_x", &fs_recon_particles_vtx_x, &b_fs_recon_particles_vtx_x);
   fChain->SetBranchAddress("fs_recon_particles.vtx_y", &fs_recon_particles_vtx_y, &b_fs_recon_particles_vtx_y);
   fChain->SetBranchAddress("fs_recon_particles.vtx_z", &fs_recon_particles_vtx_z, &b_fs_recon_particles_vtx_z);
   fChain->SetBranchAddress("vtx_recon_particles", &vtx_recon_particles_, &b_Event_vtx_recon_particles_);
   fChain->SetBranchAddress("vtx_recon_particles.fUniqueID", &vtx_recon_particles_fUniqueID, &b_vtx_recon_particles_fUniqueID);
   fChain->SetBranchAddress("vtx_recon_particles.fBits", &vtx_recon_particles_fBits, &b_vtx_recon_particles_fBits);
   fChain->SetBranchAddress("vtx_recon_particles.track", &vtx_recon_particles_track, &b_vtx_recon_particles_track);
   fChain->SetBranchAddress("vtx_recon_particles.ecal_cluster", &vtx_recon_particles_ecal_cluster, &b_vtx_recon_particles_ecal_cluster);
   fChain->SetBranchAddress("vtx_recon_particles.vtx_x", &vtx_recon_particles_vtx_x, &b_vtx_recon_particles_vtx_x);
   fChain->SetBranchAddress("vtx_recon_particles.vtx_y", &vtx_recon_particles_vtx_y, &b_vtx_recon_particles_vtx_y);
   fChain->SetBranchAddress("vtx_recon_particles.vtx_z", &vtx_recon_particles_vtx_z, &b_vtx_recon_particles_vtx_z);
   fChain->SetBranchAddress("gbl_tracks_data", &gbl_tracks_data_, &b_Event_gbl_tracks_data_);
   fChain->SetBranchAddress("gbl_tracks_data.fUniqueID", gbl_tracks_data_fUniqueID, &b_gbl_tracks_data_fUniqueID);
   fChain->SetBranchAddress("gbl_tracks_data.fBits", gbl_tracks_data_fBits, &b_gbl_tracks_data_fBits);
   fChain->SetBranchAddress("event_number", &event_number, &b_Event_event_number);
   fChain->SetBranchAddress("run_number", &run_number, &b_Event_run_number);
   fChain->SetBranchAddress("n_tracks", &n_tracks, &b_Event_n_tracks);
   fChain->SetBranchAddress("n_hits", &n_hits, &b_Event_n_hits);
   fChain->SetBranchAddress("n_ecal_clusters", &n_ecal_clusters, &b_Event_n_ecal_clusters);
   fChain->SetBranchAddress("n_ecal_hits", &n_ecal_hits, &b_Event_n_ecal_hits);
   fChain->SetBranchAddress("n_muon_clusters", &n_muon_clusters, &b_Event_n_muon_clusters);
   fChain->SetBranchAddress("n_fs_recon_particles", &n_fs_recon_particles, &b_Event_n_fs_recon_particles);
   fChain->SetBranchAddress("n_vtx_recon_particles", &n_vtx_recon_particles, &b_Event_n_vtx_recon_particles);
   fChain->SetBranchAddress("n_gbl_tracks_data", &n_gbl_tracks_data, &b_Event_n_gbl_tracks_data);
   fChain->SetBranchAddress("trigger_bits", &trigger_bits, &b_Event_trigger_bits);
   Notify();
}

Bool_t HPS_Event::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HPS_Event::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t HPS_Event::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef HPS_Event_cxx
