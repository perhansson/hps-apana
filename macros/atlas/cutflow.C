//
// CSC default cut & count dilepton analysis
//gSystem->CompileMacro("cutflow.C","k");
//  cutflow(".","synt",1,0)
//

#include <iostream>
#include <iomanip>
#include "TString.h"
#include "TFile.h"
#include "TH1F.h"
using namespace std;

void cutflow(const TString & filedir="",
             const TString & src=".exttrgmc008",
             const int ana=0,
             const int prec=0)
{

   TString basedir = "../topologies/jetmetbtag/files/";
   TString dir = basedir + filedir; 

   TH1F *h1;
   
   const int CHMAX=11;
   const int NREAL=9;
   const int NFLOW=12;
   
   const TString flows[2][NFLOW]={
      {"","","","susy0l","susy0l2j","susy0l2j1j150","susy0l2j1j15030","susy0l2j1j15040","susy0l2j1j15040met60","susy0l2j1j15040met601bti","susy0l2j1j15040met601btidphi","susy0l2j1j15040met601btidphimeff"},
      {"","","","susy0l","susy0l2j","susy0l2j1j150","susy0l2j1j15040","susy0l2j1j150150","susy0l2j1j150150met60","susy0l2j1j150150met601bti","susy0l2j1j150150met601btidphi","susy0l2j1j150150met601btidphimeff"},
   };
   
   

//       {"","","","susy0l","susy0l1j70","susy0l2j7030","susy0l3j7030","susy0l4j7030","susy0l4j7030met30","susy0l4j7030met30dphimeff","susy0l4j7030met30dphimeff1bi","susy0l4j7030met30dphimeff2bi"},
//       {"","","","susy0l","susy0l1j100","susy0l2j10040","susy0l3j10040","susy0l4j10040","susy0l4j10040met70","susy0l4j10040met70dphimeff","susy0l4j10040met70dphimeff1bi","susy0l4j10040met70dphimeff2bi"}


//       {"","","","susy0l","susy0l1j70","susy0l2j7030","susy0l3j7030","susy0l4j7030","susy0l4j7030met30","susy0l4j7030met301bi","susy0l4j7030met302bi","susy0l4j7030met300b","susy0l4j7030met301b","susy0l4j7030met302b","susy0l4j7030met303b","susy0l4j7030met304b"},
//       {"","","","susy0l","susy0l1j70","susy0l2j7030","susy0l3j7030","susy0l4j7030","susy0l4j7030met30","susy0l4j7030met301bi","susy0l4j7030met302bi","susy0l4j7030met300b","susy0l4j7030met301b","susy0l4j7030met302b","susy0l4j7030met303b","susy0l4j7030met304b"}
   
//      {"","","_truth","susytruth_1j","susytruth_4j","susytruth_4jmet50","susytruth_4j1j70met50","susytruth_4j301j70met50","susytruth_4j301j70met500l","susytruth_4j301j70met500ldphi","susytruth_4j301j70met500ldphi0bt","susytruth_4j301j70met500ldphi1bt","susytruth_4j301j70met500ldphi2bt"},
//      {"","","_truth","susytruth_1j","susytruth_4j","susytruth_4jmet50","susytruth_4j1j70met50","susytruth_4j301j70met50","susytruth_4j301j70met500l","susytruth_4j301j70met500ldphi","susytruth_4j301j70met500ldphi0bt","susytruth_4j301j70met500ldphi1bt","susytruth_4j301j70met500ldphi2bt"}

//      {"","","1j","4j","4jmet40","4j1j40met40","4j3j40met40","4j3j40met400l","4j3j40met400ldphi","4j3j40met400ldphi1bt","4j3j40met400ldphi2bt"},
//      {"","","1j","4j","4jmet40","4j1j40met40","4j3j40met40","4j3j40met400l","4j3j40met400ldphi0inv","4j3j40met400ldphi0inv1bt","4j3j40met400ldphi0inv2bt"}


//       {"","","susy0l","susy0l4j","susy0l4jsoft","susy0l4jmetsoft","susy0l4jmetmeffsoft","susy0l4jmetmeffsphsoft","susy0l4jmetmeffsphdphisoft","susy0l4jmetmeffsphdphi1btsoft","susy0l4jmetmeffsphdphi2btsoft"},
//       {"","","susy0l","susy0l4j","susy0l4jsoft","susy0l4jmetsoft","susy0l4jmetmeffsoft","susy0l4jmetmeffsphsoft","susy0l4jmetmeffsphdphisoft","susy0l4jmetmeffsphdphi1btsoft","susy0l4jmetmeffsphdphi2btsoft"}};
   
   const TString flowtxt[2][NFLOW-2]={
      {"","0l","2j20","1j150","2j30","2j40","met>60",">=1btag","dphi","Meff"},
      {"","0l","2j20","1j150","2j40","2j150","met>60",">=1btag","dphi","Meff"}


//       {"","0l","1j70","2j30","3j30","4j30","met>30","dphi/meff",">=1btag",">=2btag"},
//       {"","0l","1j100","2j40","3j40","4j40","met>70","dphi/meff",">=1btag",">=2btag"}
//       {"","0l","1j70","2j30","3j30","4j30","met>30",">=1btag",">=2btag","0 btag","1 btag","2 btag","3 btag","4 btag"},
//       {"","0l","1j70","2j30","3j30","4j30","met>30",">=1btag",">=2btag","0 btag","1 btag","2 btag","3 btag","4 btag"}
//       {"tru","1j","4j","met50","1j70","4j30","0l","dphi","==0bt","==1bt",">=2bt"},
//       {"tru","1j","4j","met50","1j70","4j30","0l","dphi","==0bt","==1bt",">=2bt"}
//       {"1j","4j","met40","1j40","3j40","0l","dphi>0.8","==1bt",">=2bt"},
//       {"1j","4j","met40","1j40","3j40","0l","dphi<0.2","==1bt",">=2bt"}
//       {"1j","2j","3j","4j","4jmet40","4j1j40met40","4j3j40met40","4j3j40met400l","4j3j40met400l1bt","4j3j40met400l2bt"},
//       {"1j","2j","3j","4j","4jmet40","4j1j40met40","4j3j40met40","4j3j40met400l","4j3j40met400l1bt","4j3j40met400l2bt"}
//       {"0l","4j","1j704j30","met","meff","sph","dphi(j,met)","1btags","2btags"},
//       {"0l","4j","1j704j30","met","meff","sph","dphi(j,met)","1btags","2btags"}
   };
   
   const TString chs[CHMAX]=
      {"jCOMB","tt","wbbCOMB","su4.exttrgmc106","py2bB400L100.exttrgmc106","py2bB400L300.exttrgmc106","py4bG400L100.exttrgmc106","py4bG400L300.exttrgmc106","py4tbG400L100.exttrgmc106","py4tbG400L200.exttrgmc106","sum"};
//       {"jCOMB.exttrgmc007","tt","su4",
//        "py2bB400L100","py2bB400L300","py4bG400L100","py4bG400L300","py4tbG400L100","py4tbG400L200","py4tG500L100","py4tG500L60","sum"};
//       {"jCOMB","tt","tthad","wbbCOMB.exttrgmc006","su4.exttrgmc006",
//        "py2bB400L100.exttrgmc006","py2bB400L300.exttrgmc006","py4bG400L100.exttrgmc006","py4bG400L300.exttrgmc006","py4tbG400L100.exttrgmc006","py4tbG400L200.exttrgmc006","py4tG500L100.exttrgmc006","py4tG500L60.exttrgmc006","sum"};
   //{"jCOMB","tt","tthad","zllCOMB","wCOMB","ww","wz","zz","su4",
   //"py2bB400L100.exttrgmc006","py2bB400L300.exttrgmc006","py4bG400L100.exttrgmc006","py4bG400L300.exttrgmc006","py4tbG400L100.exttrgmc006","py4tbG400L200.exttrgmc006","py4tG500L100.exttrgmc006","py4tG500L60.exttrgmc006","sum"};
   
   //{"jCOMB","tt","tthad","zeeCOMB","zmmCOMB","zttCOMB","zllCOMB","weCOMB","wmCOMB","wtCOMB","wCOMB","ww","wz","zz","su4","sum"};
   //{"tt","jCOMB","su4","py2bB400L100.exttrgmc006","py2bB400L300.exttrgmc006","py4bG400L100.exttrgmc006","py4bG400L300.exttrgmc006","py4tbG400L100.exttrgmc006","py4tbG400L200.exttrgmc006","py4tG500L100.exttrgmc006","py4tG500L60.exttrgmc006","sum"};





   //{"py4bG300LSP60","py4bG300LSP100","py4bG300LSP150","py4bG300LSP200","tt","jCOMB","wbbCOMB","su4","sum"};
   //{"jCOMB","wbbCOMB","bbCOMB","jaCOMB","sum"}; 
//      {"tt","jaCOMB","bbCOMB","wbbCOMB","st","sum"};
   //   {"tt","wbbCOMB","jCOMB","jaCOMB","bbCOMB","st","weCOMB","wmCOMB","wtCOMB","zeeCOMB","zmmCOMB","zttCOMB","sum"};
   
//      {"tt","bbCOMB","jCOMB","we","ztt","sum"};
//       {"tt","ww","zttA","wz","zz","zeeA","zmmA","t-wt",
//        "tt","weA","wmA","wtA","wbbA","t-wt","t-t","sum","108173"};
   
   float totem[NFLOW],totee[NFLOW],totmm[NFLOW];
   float c_totem[NFLOW],c_totee[NFLOW],c_totmm[NFLOW];
   float em[CHMAX][NFLOW],ee[CHMAX][NFLOW],mm[CHMAX][NFLOW];
   float c_em[CHMAX][NFLOW],c_ee[CHMAX][NFLOW],c_mm[CHMAX][NFLOW];
   float gen[CHMAX],c_gen[CHMAX];
   for (int i=0; i<CHMAX; ++i) {
      for (int j=0; j<NFLOW; ++j) {
         gen[i]=0;
         em[i][j]=0; c_em[i][j]=0;
         ee[i][j]=0; c_ee[i][j]=0;
         mm[i][j]=0; c_mm[i][j]=0;
      }
   }
   
   for (int cut=0;cut<NFLOW;++cut) {
      totem[cut]=0; totee[cut]=0; totmm[cut]=0;
      c_totem[cut]=0; c_totee[cut]=0; c_totmm[cut]=0;
      for (int ch=0;ch<CHMAX;++ch) {
         if (ch<CHMAX-1) {
            TString channel = chs[ch];
            if(channel.Contains(".")) channel += ".root";
            else channel += src+".root";
            TString name=dir+"/"+channel;
            const TString & sel=flows[ana][cut];
            TFile x(name);
            
            double sc=(ch<CHMAX-1?1.35:1);
//          if (chs[ch]=="tt") sc*=0.93;
//          if (chs[ch]=="ttlo") sc*=0.93;
//          if (chs[ch].Contains("ww")) sc*=2.0;
//          if (chs[ch].Contains("zee")||chs[ch].Contains("zmm")||chs[ch].Contains("ztt")) sc*=1.18;
//          if (chs[ch]=="ttlo") sc*=1.07;
            sc=1.0;
            
            h1=(TH1F*)gDirectory->Get("jetmetbtag_nj");
            if (h1!=0) {
               gen[ch]=sc*h1->Integral(-1,9999);c_gen[ch]=h1->GetEntries();
            }
            
            
            h1=(TH1F*)gDirectory->Get("jetmetbtag"+sel+"_nj");
            if (h1!=0) {
               em[ch][cut]=sc*h1->Integral(-1,9999);
               c_em[ch][cut]=h1->GetEntries();
               if (ch<CHMAX-1) { 
                  totem[cut]+=em[ch][cut]; c_totem[cut]+=c_em[ch][cut];
               }
            }
         
            /*
              if (cut==0 && ch>=NREAL) continue; // No real leptons
           
              if (cut==0) {
              h1=(TH1F*)gDirectory->Get("std_tru_em");
              }
              else
              h1=(TH1F*)gDirectory->Get("stde1m1"+sel+(ch<NREAL?"dil":"fake")+"_nj");
              if (ch==CHMAX-1) h1=(TH1F*)gDirectory->Get("stde1m1"+sel+"_nj");
              if (h1!=0) {
              em[ch][cut]=sc*h1->Integral(-1,9999);c_em[ch][cut]=h1->GetEntries();
              if (ch<CHMAX-2) totem[cut]+=em[ch][cut];
              }
           
              if (cut==0)
              h1=(TH1F*)gDirectory->Get("std_tru_ee");
              else
              h1=(TH1F*)gDirectory->Get("stde2"+sel+(ch<NREAL?"dil":"fake")+"_nj");
              if (ch==CHMAX-1) h1=(TH1F*)gDirectory->Get("stde2"+sel+"_nj");
              if (h1!=0) {
              ee[ch][cut]=sc*h1->Integral(-1,9999);c_ee[ch][cut]=h1->GetEntries();
              if (ch<CHMAX-2) totee[cut]+=ee[ch][cut];
              }
           
              if (cut==0)
              h1=(TH1F*)gDirectory->Get("std_tru_mm");
              else
              h1=(TH1F*)gDirectory->Get("stdm2"+sel+(ch<NREAL?"dil":"fake")+"_nj");
              if (ch==CHMAX-1) h1=(TH1F*)gDirectory->Get("stdm2"+sel+"_nj");
           
              if (h1!=0) {
              mm[ch][cut]=sc*h1->Integral(-1,9999);c_mm[ch][cut]=h1->GetEntries();
              if (ch<CHMAX-2) totmm[cut]+=mm[ch][cut];
              }
            */
         }
      }
   }
   
   int colWidth = 9;

   cout.setf(ios::fixed);
   for(int itabletype=0;itabletype!=5;++itabletype) {
      //show both entries and weighted entries
      bool isDefault = false;
      bool isWeighted = false;
      bool isFraction = false;
      bool isSelEff = false;
      bool isCutEff = false;
      if(itabletype == 1) {isWeighted=true; cout<<"Cross section weighted"<<endl;}
      else if(itabletype == 2) {isFraction=true; cout<<"Sample composition"<<endl;}
      else if(itabletype == 3) {isSelEff=true; cout<<"Selection efficiency"<<endl;}
      else if(itabletype == 4) {isCutEff=true; cout<<"Cut efficiency"<<endl;}
      else {isDefault=true; cout<<"Generated"<<endl;}
      //for (int fs=0; fs<3; ++fs) {
      for (int fs=0; fs<1; ++fs) {
         for (int i=0; i<1+colWidth*NFLOW;++i) cout << setw(0) << "="; cout << endl;
         cout << setw(23) << "dataset"
              << setw(colWidth) << "gen"
              << setw(colWidth) << "-"
              << setw(colWidth) << "-";
//            << setw(colWidth) << (fs==0?"tru em":(fs==1?"tru ee":"tru mm"))
//            << setw(colWidth) << "2l";
         for (int i=0; i<NFLOW-2; ++i) cout << setw(colWidth) << flowtxt[ana][i];
         cout << endl;
         for (int i=0; i<1+colWidth*NFLOW;++i) cout << setw(0) << "="; cout << endl;
         
         for (int ch=0; ch<CHMAX; ++ch) {
            TString channel = chs[ch];
            int found = channel.Index(".");
            if(found!=-1) {channel.Remove(found,channel.Length()-found);}
            cout << setw(23) << setprecision(prec) << channel << setw(colWidth) << gen[ch];
            for (int cut=0; cut<NFLOW; ++cut) {
               if(isWeighted) {                  
                  if (ch==CHMAX-1) 
                     cout<<setw(colWidth)<<(fs==0?totem[cut]:(fs==1?totee[cut]:totmm[cut]));
                  else
                     cout<<setw(colWidth)<<(fs==0?em[ch][cut]:(fs==1?ee[ch][cut]:mm[ch][cut]));
               }
               else if(isFraction) {
                  //fraction of total                  
                  float n=0.;
                  if (ch==CHMAX-1)                   
                     n = fs==0?totem[cut]:(fs==1?totee[cut]:totmm[cut]);
                  else 
                     n = fs==0?em[ch][cut]:(fs==1?ee[ch][cut]:mm[ch][cut]);
                  float N = fs==0?totem[cut]:(fs==1?totee[cut]:totmm[cut]);
                  float f = N==0.0 ? -1.0 : n/N;
                  cout.setf(ios::scientific);
                  //cout << "TEST n="<<n<<" N="<<N<<" f="<<f<<endl;
                  cout<<setw(colWidth)<<f;
                  //reset style
                  cout.setf(ios::fixed);
                  cout << setprecision(prec);
                  
               }

               else if(isSelEff) {
                  //Selection efficiency                  
                  float n=0.;
                  float N=0.;
                  //Define denominator
                  int base=0;
                  if (ch==CHMAX-1) {
                     N = fs==0?totem[base]:(fs==1?totee[base]:totmm[base]);
                     n = fs==0?totem[cut]:(fs==1?totee[cut]:totmm[cut]);
                  }
                  else {
                     N = fs==0?em[ch][base]:(fs==1?ee[ch][base]:mm[ch][base]);
                     n = fs==0?em[ch][cut]:(fs==1?ee[ch][cut]:mm[ch][cut]);
                  }
                  float f = N==0.0 ? -1.0 : n/N;
                  cout.setf(ios::scientific);
                  //cout << "TEST n="<<n<<" N="<<N<<" f="<<f<<endl;
                  cout<<setw(colWidth)<<f;
                  //reset style
                  cout.setf(ios::fixed);
                  cout << setprecision(prec);
                  
               }
               else if(isCutEff) {
                  //Selection efficiency w.r.t. to previous cut
                  float n=0.;
                  float N=0.;
                  //Define denominator
                  int base=cut==1?0:(cut-1);
                  if (ch==CHMAX-1) {
                     N = fs==0?totem[base]:(fs==1?totee[base]:totmm[base]);
                     n = fs==0?totem[cut]:(fs==1?totee[cut]:totmm[cut]);
                  }
                  else {
                     N = fs==0?em[ch][base]:(fs==1?ee[ch][base]:mm[ch][base]);
                     n = fs==0?em[ch][cut]:(fs==1?ee[ch][cut]:mm[ch][cut]);
                  }
                  float f = N==0.0 ? -1.0 : n/N;
                  cout.setf(ios::scientific);
                  //cout << "TEST n="<<n<<" N="<<N<<" f="<<f<<endl;
                  cout<<setw(colWidth)<<f;
                  //reset style
                  cout.setf(ios::fixed);
                  cout << setprecision(prec);
                  
               }
               else if(isDefault) {
                  if (ch==CHMAX-1) 
                     cout<<setw(colWidth)<<(fs==0?c_totem[cut]:(fs==1?c_totee[cut]:c_totmm[cut]));               
                  else
                     cout<<setw(colWidth)<<(fs==0?c_em[ch][cut]:(fs==1?c_ee[ch][cut]:c_mm[ch][cut]));               
               }
               else {
                  cout<<setw(colWidth)<<"not impl.";
               }
            }
            cout << endl;
         }
         for (int i=0; i<1+colWidth*NFLOW;++i) cout << setw(0) << "="; cout << endl;
      }
   }
   
   
}
