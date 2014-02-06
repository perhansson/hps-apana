// *********************************************************
//
// NAME:     TrigTrackJetFinderTool.h
// PACKAGE:  Trigger/TrigTools/TrigTrackJetFinderTool
//
// AUTHOR:   Andrea Coccaro    (Andrea.Coccaro@ge.infn.it)
//           Andrew Lowe       (Andrew.Lowe@cern.ch)
//           Ariel Schwartzman (sch@slac.stanford.edu)
// 
// *********************************************************

#ifndef TRIGTRACKJETFINDERTOOL_H
#define TRIGTRACKJETFINDERTOOL_H

#include <vector>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iostream>

//#include "AthenaBaseComps/AthAlgTool.h"
//#include "TrigTrackJetFinderTool/ITrigTrackJetFinderTool.h"

#include "Track.h"
//#include "Particle/TrackParticle.h"
//#include "TrkTrack/Track.h"



class TrackAttributes {

   public:
  
      TrackAttributes() {};
      TrackAttributes(const Track*& track, unsigned int id) {

         const double pi = 3.14159265358979323846;

         m_id  = id;
//          m_pt  = track->param()->pT();
//          m_phi = track->param()->phi0();
//          m_eta = track->param()->eta();
//          m_z0  = track->param()->z0();
//          m_d0  = track->param()->a0();
         m_pt  = track->p.Pt()*track->Charge();
         m_phi = track->p.Phi();
         m_eta = track->p.Eta();
         m_z0  = track->z0();
         m_d0  = track->d0();
         
         if(m_phi < -pi) m_phi += 2 * pi;
         if(m_phi >  pi) m_phi -= 2 * pi;
         
         m_px = fabs(m_pt)*cos(m_phi);
         m_py = fabs(m_pt)*sin(m_phi);
         m_pz = fabs(m_pt)*sinh(m_eta);
         
      };

//       TrackAttributes(const Rec::TrackParticle*& track, unsigned int id) {

//          const double pi = 3.14159265358979323846;

//          m_id  = id;
//          m_pt  = track->pt();
//          m_phi = track->phi();
//          m_eta = track->eta();
//          m_z0  = track->measuredPerigee()->parameters()[Trk::z0];
//          m_d0  = track->measuredPerigee()->parameters()[Trk::d0];

//          if(m_phi < -pi) m_phi += 2 * pi;
//          if(m_phi >  pi) m_phi -= 2 * pi;

//          m_px = fabs(m_pt)*cos(m_phi);
//          m_py = fabs(m_pt)*sin(m_phi);
//          m_pz = fabs(m_pt)*sinh(m_eta);

//       };

//       TrackAttributes(const Trk::Track*& track, unsigned int id) {

//          const double pi = 3.14159265358979323846;

//          m_id  = id;
//          m_pt  = track->perigeeParameters()->pT();
//          m_phi = track->perigeeParameters()->parameters()[Trk::phi];
//          m_eta = track->perigeeParameters()->eta();
//          m_z0  = track->perigeeParameters()->parameters()[Trk::z0];
//          m_d0  = track->perigeeParameters()->parameters()[Trk::d0];

//          if(m_phi < -pi) m_phi += 2 * pi;
//          if(m_phi >  pi) m_phi -= 2 * pi;

//          m_px = fabs(m_pt)*cos(m_phi);
//          m_py = fabs(m_pt)*sin(m_phi);
//          m_pz = fabs(m_pt)*sinh(m_eta);

//       };

      ~TrackAttributes() {};

      int   Id()  const { return m_id; }

      double Px()  const { return m_px;  }
      double Py()  const { return m_py;  }
      double Pz()  const { return m_pz;  }
      double Pt()  const { return m_pt;  }
      double Eta() const { return m_eta; }
      double Phi() const { return m_phi; }
      double Z()   const { return m_z0;  }

      bool operator== (const TrackAttributes &other) const {
         if(this->Phi() != other.Phi()) return false;
         return true;
      }
  
   private:

      unsigned int m_id;

      double m_px;
      double m_py;
      double m_pz;
      double m_pt;
      double m_eta;
      double m_phi;
      double m_z0;
      double m_d0;

};


//** ----------------------------------------------------------------------------------------------------------------- **//


//class TrigTrackJetFinderTool: public AthAlgTool, virtual public ITrigTrackJetFinderTool {
class TrigTrackJetFinderTool {

   public:

      TrigTrackJetFinderTool(const int& debug=0);
      virtual ~TrigTrackJetFinderTool();

      virtual void initialize();
      virtual void finalize();
  
      void inputPrimaryVertexZ(double zPV);
      void addTrack(const Track*&, unsigned int);
      //void addTrack(const Rec::TrackParticle*&, unsigned int);
      //void addTrack(const Trk::Track*&, unsigned int);

      void setMultiplicity(int mult);

      void setDebug(const int& debug);

      void findJet(std::vector<int>& tracks, double& eta, double& phi);

      void clear();
  
   private:

      double phiCorr(double);
      double deltaR(double& eta0, double& phi0, double& eta1, double& phi1); 

      double m_dr, m_dz, m_ptMin, m_ptJet, m_ptSeed, m_mult;
      double m_zpv;

      /** @brief Value of pi set in CTOR to the exact value in TMath.h to avoid including everything in the TMath namespace and multiple calls to TMath::Pi(). */
      const double m_pi;  
      int m_debug;
      std::vector<TrackAttributes> m_attributesOfTracks;
};

#endif

