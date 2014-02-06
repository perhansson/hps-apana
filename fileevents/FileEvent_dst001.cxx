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

#include "FileEvent_dst001.h"
#include <TTree.h>
#include <TFile.h>


/*
 * Don't need to touch this unless your TTree changes
 */
int FileEvent_dst001::Open(std::list<TString> filelist) {
   TString file=filelist.front().Data();

   fChain=new TChain("HPS_Event");

   while (filelist.size()>0) {
      std::cout << "adding file: " << filelist.front().Data() << std::endl;
      fChain->Add(filelist.front().Data());
      filelist.pop_front();
   }

   if (fChain) { 
      SetBranches();
      DisableBranches();
   }
   else {
      std::cout << "FileEvent:: cannot create tree\n" ;
      exit(-1);
   }
   return 0;
}

bool FileEvent_dst001::copy_to_interface(AtlEvent &atl) {


  //This is the interface to the AtlEvent
  //Here is where the variables from the TTree are copied to the 
  // event. This is just an example and can/should be changed to 
  // copy only the things you use in your analysis if you want to 
  // speed up the program
  
  
  //Set the global event weight
  atl.weight(1.0); // Always 1 for data
  
  atl.m_evtnr = event_number;
  atl.m_runnr = run_number;
  
  cout << "\n------- Tracks:" << endl;
  
  //Copy the tracks
  for (int i=0; i < n_tracks; ++i) {
    Track t;
    double px =tracks_px[i];
    double py =tracks_px[i];
    double pz =tracks_pz[i];
    double E = px*px + py*py + pz*pz; // mass less
    t.p.SetPxPyPzE(px,py,pz,E);
    t.Charge( tracks_charge[i]>=0 ? 1 : -1);
    //check if this track passes the selections and then add it
    //this automatically counts and saves the cut bits for the track
    cout << " track i " << i << ": px " << px << " P " << t.p.P() <<endl; 
    atl.trk_cut_store(t);
   }
   
      
   //Add vertex
   // for (unsigned int i=0; i<vx_x->size(); ++i) { 
   //    Vertex vtx((*vx_x)[i],(*vx_y)[i],(*vx_z)[i],(*vx_nTracks)[i]);
   //    atl.vtx_cut_store(vtx);      
   // }

   
   
  
   return true;
}

void FileEvent_dst001::SetBranches(void) {

   // Initialize the leaves below (typically from TTree->makeClass() output)
//    e_px = 0;
//    e_py = 0;
//    e_pz = 0;
//    ....
//    ....

//    fChain->SetBranchAddress("e_px", &e_px, &b_e_px);
//    fChain->SetBranchAddress("e_py", &e_py, &b_e_py);
//    fChain->SetBranchAddress("e_pz", &e_pz, &b_e_pz);
//    ....
//    ....

   






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











}

void FileEvent_dst001::DisableBranches(void) {
   //Disable branches
//   fChain->SetBranchStatus("AntiKt4*",0);

}
