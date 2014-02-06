{
  std::string directory = "/u1/dans/bmet/devel/FlatAna/trunk/topologies/dataMC/";
  std::string saveDirectory = "/u1/dans/bmet/devel/FlatAna/trunk/macros/plots/";

  std::string histoname = "plotTest";
  //save name above

  std::string prefix = "RndCone";

  std::string filename  = std::string("towerslim.tow001.root");


int n = 25;
int par = 1;

//std::string filename  = histoname+std::string(".root");
std::string saveName  = saveDirectory+prefix+histoname+".root";
std::string saveNamePng  = saveDirectory+prefix+histoname+".png";
std::string saveNameC  = saveDirectory+prefix+histoname+".C";



TFile f((directory+filename).c_str());

TCanvas* c1;
f.GetObject("c1",c1);
//TH2F* h = (TH2F*) c1->FindObject("l2rate_jEresponse);
 



 TH2F* h = (TH2F*) gROOT->FindObject("l2rate3PV_ConeEtVeta3")->Clone("h");

 //read from a second file
 //TFile* f1 = new TFile("/u1/dans/bmet/devel/FlatAna/trunk/topologies/dataMC/files/tt.trg004.root","read");

 TH2F* bh = (TH2F*) gROOT->FindObject("l2rate3PV_ConeEtVeta4")->Clone("bh");

 TH2F* ch = (TH2F*) gROOT->FindObject("l2rate3PV_ConeEtVeta5")->Clone("ch");
  TH2F* dh = (TH2F*) gROOT->FindObject("l2rate3PV_ConeEtVeta6")->Clone("dh");


 TProfile *gae = h->ProfileX("gae");
 TProfile *bgae = bh->ProfileX("bgae");
 TProfile *cgae = ch->ProfileX("cgae");
 TProfile *dgae = dh->ProfileX("dgae");



 
 



     TCanvas c;
     c.SetGridx();
     c.SetGridy();
     //c.SetLogx();
     gae->Draw();
     gae->GetXaxis()->SetLimits(-5,5);
     gae->GetXaxis()->SetNoExponent();
     gae->GetXaxis()->SetMoreLogLabels();
     gae->GetYaxis()->SetNoExponent();
     gae->GetYaxis()->SetMoreLogLabels();
     gae->GetXaxis()->SetTitle("Eta");
     gae->GetYaxis()->SetTitle("E_{T} of Random Cone");
     gae->GetYaxis()->SetTitleOffset(1.13);
     gae->SetMaximum(6000);
     gae->SetMinimum(-1000);
     
     
     //bgae->Draw("AP");
     bgae->Draw("P,SAME");
     bgae->GetXaxis()->SetLimits(-5,5);
     bgae->GetXaxis()->SetNoExponent();
     bgae->GetXaxis()->SetMoreLogLabels();
     bgae->GetYaxis()->SetNoExponent();
     bgae->SetMarkerColor(2);
     bgae->GetYaxis()->SetMoreLogLabels();
     bgae->GetXaxis()->SetTitle("J0 JVF");
     bgae->GetYaxis()->SetTitle("Response=p^{1}_{T}/p^{0}_{T}");
     bgae->GetYaxis()->SetTitleOffset(1.13);
     bgae->SetMaximum(6000);
     bgae->SetMinimum(-1000);
     
     
     
     
     //cgae->Draw("AP");
     cgae->Draw("P,SAME");
     cgae->GetXaxis()->SetLimits(-5,5);
     cgae->GetXaxis()->SetNoExponent();
     cgae->GetXaxis()->SetMoreLogLabels();
     cgae->GetYaxis()->SetNoExponent();
     cgae->SetMarkerColor(3);
     cgae->GetYaxis()->SetMoreLogLabels();
     cgae->GetXaxis()->SetTitle("J0 JVF");
     cgae->GetYaxis()->SetTitle("Response=p^{1}_{T}/p^{0}_{T}");
     cgae->GetYaxis()->SetTitleOffset(1.13);
     cgae->SetMaximum(6000);
     cgae->SetMinimum(-1000);
     
     
     
     
       dgae->Draw("P,SAME");
       dgae->GetXaxis()->SetLimits(-5,5);
       dgae->GetXaxis()->SetNoExponent();
       dgae->GetXaxis()->SetMoreLogLabels();
       dgae->GetYaxis()->SetNoExponent();
       dgae->SetMarkerColor(4);
       dgae->GetYaxis()->SetMoreLogLabels();
       dgae->GetXaxis()->SetTitle("J0 JVF");
       dgae->GetYaxis()->SetTitle("Response=p^{1}_{T}/p^{0}_{T}");
       dgae->GetYaxis()->SetTitleOffset(1.13);
       dgae->SetMaximum(6000);
       dgae->SetMinimum(-1000);
          
     TLegend leg(0.25,0.2,0.65,0.5);
     leg.AddEntry(gae,"R=0.3","pl");
     leg.AddEntry(bgae,"R=0.4","pl");
     leg.AddEntry(cgae,"R=0.5","pl");
      leg.AddEntry(dgae,"R=0.6","pl");
     leg.SetFillStyle(0);
 leg.SetBorderSize(0);
 leg.Draw("same");
 c.SaveAs(saveName.c_str());
 c.SaveAs(saveNamePng.c_str());
 //c.SaveAs(saveNameC.c_str());

 
}
