#include "TStyle.h"
#include "TCanvas.h"
#include "TROOT.h"

#include "style.h"

void style(float W, float H, 
	   float titleW, float titleH)
{


// 
// 
// 
// 
// // Graphics style parameters to avoid grey background on figures
//    gStyle->SetCanvasColor(10);
//    gStyle->SetStatColor(10);
//    gStyle->SetTitleColor(10);
//    gStyle->SetPadColor(10);
//    gStyle->SetPaperSize(20,24);
//    gStyle->SetStatFont(42);
// 
//    //title size
//    gStyle->SetOptStat(000000);
//    gStyle->SetOptFit(101);
//    gStyle->SetStatW(W); 
//    gStyle->SetStatH(H); 
//    gStyle->SetTitleFont(62);
//    gStyle->SetTitleY(0.99);
//    if(titleH>0)
//      gStyle->SetTitleH(titleH);
//    if(titleW>0)
//       gStyle->SetTitleW(titleW); 


// Canvas style
TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
if(c1) {c1->Clear();} 
 else {
   c1 = new TCanvas("c1","c1");
 }
   //c1->SetLeftMargin(0.15);
   //c1->SetBottomMargin(0.15);
   //c1->SetLogy(0);
   
   
// Set Style
   
}






