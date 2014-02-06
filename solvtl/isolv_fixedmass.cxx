//
// Solve for the two unknown neutrinos in a ttbar dilepton event.
// n gives the number of solutions, up to 4.
//
// sjolin@physto.se
//

#include "TLorentzVector.h"
#include "solvtl.h"

extern "C" {void solvtl_(double[], double[], double[], double[],
			 double*, double*, double*, double*, double*,
			 double[][4], double[][4], int *);}


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

void solv_top_dil(const TLorentzVector & l1,
		  const TLorentzVector & l2,
		  const TLorentzVector & b1,
		  const TLorentzVector & b2,
		  double metx,
		  double mety,
		  TLorentzVector (&n1)[4],
		  TLorentzVector (&n2)[4],
		  int &n)
{
  double pl1[4],pl2[4],pb1[4],pb2[4],pn1[4][4],pn2[4][4];
  double mt=175;
  double mw=80.4;
  double mb=4.7;
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
