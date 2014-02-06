//
// gSystem->Load("libsolvtl.sl");
// gSystem->CompileMacro("tltest.C","k");
// 

#include <iostream>
#include "TLorentzVector.h"
#include "solvtl.h"

void tltest(void) {
  int n=0;
  double metx=0;
  double mety=0;

  {
    TLorentzVector l1,l2,b1,b2,n1[4],n2[4];
    l1.SetXYZT( 222.343456, 190.124817, -547.433259, 620.698986);
    l2.SetXYZT(-240.897738, -223.437082, 979.820499, 1033.44282);
    b1.SetXYZT( 384.903274, 254.728708, -897.567512, 1009.30158);
    b2.SetXYZT(-460.898173, -350.90404, 1643.00162, 1742.13664);
    solv_top_dil(l1,l2,b1,b2,metx,mety,n1,n2,n,175.,80.,4.8);
    std::cout << "dilepton solutions=" << n << std::endl;
  }

  {
    double chi2=0;
    TLorentzVector l1,n1,b1,b2,j1,j2;
    TLorentzVector l1_fit,n1_fit,b1_fit,b2_fit,j1_fit,j2_fit;
    l1.SetXYZT(   -6.457, -125.003, -323.055,  346.457);
    n1.SetXYZT(  -24.189,  -67.022,  -73.800,  102.584);
    b1.SetXYZT(   35.506,  -15.056, -240.553,  243.672);
    b2.SetXYZT(  -18.841,  115.817, -227.795,  256.286);
    j1.SetXYZT(    2.522,   24.052, -414.769,  415.474);
    j2.SetXYZT(   33.625,   77.125, -294.417,  306.207);
    metx=-24.189;
    mety=-67.022;
    cout << "W(1) mass=" << (l1+n1).M()<<", W(2) mass=" << (j1+j2).M()<<endl;
    cout << "top(1)="<<(l1+n1+b1).M()<< ", top(2)=" << (j1+j2+b2).M() << endl;
    solv_top_lj(l1,b1,b2,j1,j2,metx,mety,175.,80.,4.7,
		l1_fit,n1_fit,b1_fit,b2_fit,j1_fit,j2_fit,chi2);
    std::cout << "chi2(l+jets bjet combination 1)=" << chi2 << std::endl;
    solv_top_lj(l1,b2,b1,j1,j2,metx,mety,175.,80.,4.7,
		l1_fit,n1_fit,b1_fit,b2_fit,j1_fit,j2_fit,chi2);
    std::cout << "chi2(l+jets bjet combination 2)=" << chi2 << std::endl;
  }

}
