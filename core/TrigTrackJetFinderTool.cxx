// *********************************************************
//
// NAME.cxx
// PACKAGE:  Trigger/TrigTools/TrigTrackJetFinderTool
//
// AUTHOR:   Andrea Coccaro    (Andrea.Coccaro@ge.infn.it)
//           Andrew Lowe       (Andrew.Lowe@cern.ch)
//           Ariel Schwartzman (sch@slac.stanford.edu)
// 
// *********************************************************

#include "TrigTrackJetFinderTool.h"

using namespace std;
using std::vector;



//** ----------------------------------------------------------------------------------------------------------------- **//


bool TrackAttributesSortPredicate(const TrackAttributes& lhs, const TrackAttributes& rhs) {

   return fabs(lhs.Pt()) > fabs(rhs.Pt());
}


//** ----------------------------------------------------------------------------------------------------------------- **//


TrigTrackJetFinderTool::TrigTrackJetFinderTool(const int& debug)
   :  m_pi(3.14159265358979323846), m_debug(debug)
{

   m_dr    = 0.6;
   m_dz    = 10.0;
   m_ptMin = 0.5;
   m_ptJet = 0.0;
   m_ptSeed = 2.0;
   m_mult   = 2;
   m_zpv   = 0.0;
}


//** ----------------------------------------------------------------------------------------------------------------- **//


TrigTrackJetFinderTool::~TrigTrackJetFinderTool() {}


//** ----------------------------------------------------------------------------------------------------------------- **//


void TrigTrackJetFinderTool::initialize() {
  
 


   if (m_debug) {
      cout << "Initializing TrigTrackJetFinderTool" << endl;    
      cout  << "declareProperty review:" << endl;
      cout  << " DeltaR = "              << m_dr << endl; 
      cout  << " DeltaZ = "              << m_dz << endl; 
      cout  << " PtMin = "               << m_ptMin << endl; 
      cout  << " PtJet = "               << m_ptJet << endl; 
      cout  << " PtSeed = "              << m_ptSeed << endl; 
      cout  << " Mult = "                << m_mult << endl; 
   }

   return;
}


//** ----------------------------------------------------------------------------------------------------------------- **//


void TrigTrackJetFinderTool::clear() {

   m_attributesOfTracks.clear();
}


//** ----------------------------------------------------------------------------------------------------------------- **//


void TrigTrackJetFinderTool::setMultiplicity(int mult) {

   m_mult = mult;
}

//** ----------------------------------------------------------------------------------------------------------------- **//

void TrigTrackJetFinderTool::setDebug(const int& debug) {

   m_debug = debug;

}


//** ----------------------------------------------------------------------------------------------------------------- **//


void TrigTrackJetFinderTool::addTrack(const Track*& track, unsigned int i) {

   TrackAttributes p(track, i);

//    double z0 = track->param()->z0();
//    double pT = track->param()->pT();
   double z0 = track->z0();
   double pT = track->p.Pt();

   if (pT >= m_ptMin && (fabs(z0 - m_zpv) < m_dz)) m_attributesOfTracks.push_back(p);

   if(m_debug) cout << "TrigTrackJetFinderTool addTrack id="<<i<<" with pT="<<pT<<" d0="<< track->d0() << " and z0="<<z0<<endl;

   std::sort(m_attributesOfTracks.begin(), m_attributesOfTracks.end(), TrackAttributesSortPredicate);
}


//** ----------------------------------------------------------------------------------------------------------------- **//


// void TrigTrackJetFinderTool::addTrack(const Rec::TrackParticle*& track, unsigned int i) {

//    TrackAttributes p(track, i);

//    double z0 = track->measuredPerigee()->parameters()[Trk::z0];
//    double pT = track->pt();

//    if (pT >= m_ptMin && (fabs(z0 - m_zpv) < m_dz)) m_attributesOfTracks.push_back(p);

//    std::sort(m_attributesOfTracks.begin(), m_attributesOfTracks.end(), TrackAttributesSortPredicate);
// }


//** ----------------------------------------------------------------------------------------------------------------- **//


// void TrigTrackJetFinderTool::addTrack(const Trk::Track*& track, unsigned int i) {

//    TrackAttributes p(track, i);

//    double z0 = track->perigeeParameters()->parameters()[Trk::z0];
//    double pT = track->perigeeParameters()->pT();
  
//    if(pT >= m_ptMin && (fabs(z0 - m_zpv) < m_dz)) m_attributesOfTracks.push_back(p);
  
//    std::sort(m_attributesOfTracks.begin(), m_attributesOfTracks.end(), TrackAttributesSortPredicate);
// }


//** ----------------------------------------------------------------------------------------------------------------- **//


void TrigTrackJetFinderTool::inputPrimaryVertexZ(double zPV) {

   m_zpv = zPV;
}


//** ----------------------------------------------------------------------------------------------------------------- **//


void TrigTrackJetFinderTool::findJet(std::vector<int>& tracks, double& jetEta, double& jetPhi) {

   tracks.clear();
   double jetPx = 0, jetPy = 0, jetPz = 0;
   double jetP = 0;
   jetEta = 0, jetPhi = 0;

   if (m_debug) {
      cout << "TrigTrackJetFinderTool: simple cone jet algorithm." << endl;
      cout << "- Cone size (R,Z)      = " << m_dr << ", " << m_dz << endl;
      cout << "- minimum seed pT      = " << m_ptSeed << endl;
      cout << "- minimum jet pT       = " << m_ptJet  << endl;
      cout << "- minimum track pT     = " << m_ptMin  << endl;
      cout << "- minimum multiplicity = " << m_mult  << endl;
      cout << "Number of input tracks = " << m_attributesOfTracks.size() << " [";
      for(size_t j=0;j!=m_attributesOfTracks.size();++j) cout << ","<<m_attributesOfTracks[j].Id();
      cout << "]"<<endl;
   }

   if(m_attributesOfTracks.size() < m_mult) {
      jetEta = -99; jetPhi = -99;
      return;
   }

   TrackAttributes seed = m_attributesOfTracks[0];
   if(fabs(seed.Pt())<m_ptSeed) { 
      jetEta = -99; jetPhi = -99;
      return;
   }
  
   tracks.push_back(seed.Id());
  
   jetPx += seed.Px();
   jetPy += seed.Py();
   jetPz += seed.Pz();
   jetP   = sqrt(jetPx*jetPx+jetPy*jetPy+jetPz*jetPz);
   jetEta = 0.5*log( (jetP+jetPz)/(jetP-jetPz) );
   jetPhi = phiCorr(atan2(jetPy,jetPx));

   for(unsigned int j=1; j < m_attributesOfTracks.size(); j++) {
    
      double pEta = m_attributesOfTracks[j].Eta();
      double pPhi = m_attributesOfTracks[j].Phi();
    
      double dr = deltaR(jetEta,jetPhi, pEta,pPhi);
	  
      if(dr<m_dr) {
	    
         jetPx += m_attributesOfTracks[j].Px();
         jetPy += m_attributesOfTracks[j].Py();
         jetPz += m_attributesOfTracks[j].Pz();
         tracks.push_back(m_attributesOfTracks[j].Id());
	    
         jetP = sqrt(jetPx*jetPx+jetPy*jetPy+jetPz*jetPz);
         jetEta = 0.5*log((jetP+jetPz)/(jetP-jetPz));
         jetPhi = atan2(jetPy,jetPx);
      
      }
   }

   //double jetPt = sqrt(jetPx*jetPx+jetPy*jetPy);
}


//** ----------------------------------------------------------------------------------------------------------------- **//


double TrigTrackJetFinderTool::deltaR(double& eta0, double& phi0, double& eta1, double& phi1) {

   double deta = eta0 - eta1;
   double dphi = phiCorr(phiCorr(phi0) - phiCorr(phi1));

   return sqrt(deta*deta+dphi*dphi);
}


//** ----------------------------------------------------------------------------------------------------------------- **//


double TrigTrackJetFinderTool::phiCorr(double phi){

   if(phi < -m_pi) phi += 2*m_pi;
   if(phi >  m_pi) phi -= 2*m_pi;

   return phi;
}


//** ----------------------------------------------------------------------------------------------------------------- **//


void TrigTrackJetFinderTool::finalize() {


   if(m_debug) cout << "Finalizing TrigTrackJetFinderTool" << endl;
   
   return;
}


