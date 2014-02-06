//
// Solve for the two unknown neutrinos in a ttbar dilepton event.
// n gives the number of solutions, up to 4.
//
// Solve 3C for ttbar lepton+jets.
//
// sjolin@physto.se
//
// C.Clement: 2010-01-30 added solvtlimg_ to resovle dilepton equation and 
//            provide imaginary part of pnuz
//

#include "TLorentzVector.h"
#include "solvtl.h"

void tlv2lv(const TLorentzVector & tlv, double (&lv)[4])
{
  lv[0]=tlv.Px();
  lv[1]=tlv.Py();
  lv[2]=tlv.Pz();
  lv[3]=tlv.E();
}

void lv2tlv(double (&lv)[4], TLorentzVector & tlv)
{
  tlv.SetPx(lv[0]);
  tlv.SetPy(lv[1]);
  tlv.SetPz(lv[2]);
  tlv.SetE(lv[3]);
}

extern "C" {void solvtl_(double[], double[], double[], double[],
			 double*, double*, double*, double*, double*,
			 double[][4], double[][4], int *);}

void solv_top_dil(const TLorentzVector & l1,
		  const TLorentzVector & l2,
		  const TLorentzVector & b1,
		  const TLorentzVector & b2,
		  double metx,
		  double mety,
		  TLorentzVector (&n1)[4],
		  TLorentzVector (&n2)[4],
		  int &n,
		  double mt, double mw, double mb)
{
  double pl1[4],pl2[4],pb1[4],pb2[4],pn1[4][4],pn2[4][4];
  tlv2lv(l1,pl1);
  tlv2lv(l2,pl2);
  tlv2lv(b1,pb1);
  tlv2lv(b2,pb2);
  solvtl_(pl1,pl2,pb1,pb2,&metx,&mety,&mt,&mw,&mb,pn1,pn2,&n);
  for (int i=0;i<n;++i) {
    double tmp[4];
    for (int j=0;j<4;++j) tmp[j]=pn1[i][j];
    lv2tlv(tmp,n1[i]);
    for (int j=0;j<4;++j) tmp[j]=pn2[i][j];
    lv2tlv(tmp,n2[i]);
  }
}

extern "C" {void solvtlimg_(double[], double[], double[], double[],
			    double*, double*, double*, double*, double*,
			    double[][4], double[][4], int *,
			    double[][4], double[][4]);}


void solv_top_dil_img(const TLorentzVector & l1,
		      const TLorentzVector & l2,
		      const TLorentzVector & b1,
		      const TLorentzVector & b2,
		      double metx,
		      double mety,
		      TLorentzVector (&n1)[4],
		      TLorentzVector (&n2)[4],
		      int &n,
		      double mt, double mw, double mb,
		      TLorentzVector (&ipnu1)[4], 
		      TLorentzVector (&ipnu2)[4])
{
  double pl1[4],pl2[4],pb1[4],pb2[4],pn1[4][4],pn2[4][4],ipn1[4][4],ipn2[4][4];
  tlv2lv(l1,pl1);
  tlv2lv(l2,pl2);
  tlv2lv(b1,pb1);
  tlv2lv(b2,pb2);
  solvtlimg_(pl1,pl2,pb1,pb2,&metx,&mety,&mt,&mw,&mb,pn1,pn2,&n,ipn1,ipn2);
  for (int i=0;i<n;++i) {
    double tmp[4];
    for (int j=0;j<4;++j) tmp[j]=pn1[i][j];
    lv2tlv(tmp,n1[i]);
    for (int j=0;j<4;++j) tmp[j]=pn2[i][j];
    lv2tlv(tmp,n2[i]);

    for (int j=0;j<4;++j) tmp[j]=ipn1[i][j];
    lv2tlv(tmp,ipnu1[i]);
    for (int j=0;j<4;++j) tmp[j]=ipn2[i][j];
    lv2tlv(tmp,ipnu2[i]);
  }
}


extern "C" {void ttlh3c_(double[], double[], double[], double[],
			 double[], double[],
			 double*, double*, double*, double*, double*,
			 double[][21], double*,
			 double[], double[]);}

extern "C" {void calcv_(double[], double[], double[], double[], double[],
			double*, double*, double[][21]);}

void solv_top_lj(const TLorentzVector & l1,
		 const TLorentzVector & b1,
		 const TLorentzVector & b2,
		 const TLorentzVector & j1,
		 const TLorentzVector & j2,
		 double metx,
		 double mety,
		 double mt, double mw, double mb,
		 TLorentzVector &fit_l1,
		 TLorentzVector &fit_n1,
		 TLorentzVector &fit_b1,
		 TLorentzVector &fit_b2,
		 TLorentzVector &fit_j1,
		 TLorentzVector &fit_j2,
		 double &chi2)
{
  double pl1[4],pn1[4],pb1[4],pb2[4],pj1[4],pj2[4],V[21][21],yin[21],yout[21];
  tlv2lv(l1,pl1);
  tlv2lv(b1,pb1);
  tlv2lv(b2,pb2);
  tlv2lv(j1,pj1);
  tlv2lv(j2,pj2);
  calcv_(pl1,pb1,pb2,pj1,pj2,&metx,&mety,V);
  ttlh3c_(pl1,pn1,pb1,pb2,pj1,pj2,&metx,&mety,&mb,&mw,&mt,V,&chi2,yin,yout);
  lv2tlv(pl1,fit_l1);
  lv2tlv(pn1,fit_n1);
  lv2tlv(pb1,fit_b1);
  lv2tlv(pb2,fit_b2);
  lv2tlv(pj1,fit_j1);
  lv2tlv(pj2,fit_j2);
}
