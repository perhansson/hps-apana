{
  std::string directory = "/u1/dans/bmet/devel/FlatAna/trunk/topologies/dataMC/files/";
  std::string saveDirectory = "/u1/dans/bmet/devel/FlatAna/trunk/macros/plots/";

  std::string histoname = "plotTest";
  //save name above

  std::string prefix = "";

  //std::string filename  = std::string("158045slim-PILE.dat003.root");
  std::string filename  = std::string("tt-RESP.trg004.root");

int n = 25;
int par = 1;
int firstHBin = 21;
int lastHBin = 1000;
//std::string filename  = histoname+std::string(".root");
std::string saveName  = saveDirectory+prefix+histoname+".root";
std::string saveNamePng  = saveDirectory+prefix+histoname+".png";
std::string saveNameC  = saveDirectory+prefix+histoname+".C";



TFile f((directory+filename).c_str());

TCanvas* c1;
f.GetObject("c1",c1);
//TH2F* h = (TH2F*) c1->FindObject("l2rate_jEresponse);
 



 TH2F* h = (TH2F*) gROOT->FindObject("l2rate_bjHadEresponse")->Clone("h");

 //read from a second file
 //TFile* f1 = new TFile("/u1/dans/bmet/devel/FlatAna/trunk/topologies/dataMC/files/tt.trg004.root","read");
 //TH2F* bh = (TH2F*) gROOT->FindObject("l2rate_bMatchjresponseEta3")->Clone("bh");
 TH2F* bh = (TH2F*) gROOT->FindObject("l2rate_bjMuonMuresponse")->Clone("bh");




 //TH2* h = (TH2*) c1->FindObject(histoname.c_str());
 //TH2* h = 0;
//f.GetObject(histoname.c_str(), h);
TH1D* ptdist = h->ProjectionX("pt",-1,-1,"e");

double* x     = new double[n];
double* xlow  = new double[n];
double* xhigh = new double[n];

int* lowBin  = new double[n];
int* highBin = new double[n];

double* y     = new double[n];
double* ylow  = new double[n];
double* yhigh = new double[n];

int totalEntries = 0;

lowBin[0] =21;
lowBin[1] =26;
lowBin[2] =31;
lowBin[3] =41;
lowBin[4] =51;
lowBin[5] =61;
lowBin[6] =71;
lowBin[7] =81;
lowBin[8] =91;
lowBin[9] =101;
lowBin[10] =121;
lowBin[11] =141;
lowBin[12] =161;
lowBin[13] =181;
lowBin[14] =201;
lowBin[15] =251;
lowBin[16] =301;
lowBin[17] =351;
lowBin[18] =401;
lowBin[19] =451;
lowBin[20] =501;
lowBin[21] =601;
lowBin[22] =701;
lowBin[23] =801;
lowBin[24] =901;

highBin[0] =25;
highBin[1] =30;
highBin[2] =40;
highBin[3] =50;
highBin[4] =60;
highBin[5] =70;
highBin[6] =80;
highBin[7] =90;
highBin[8] =100;
highBin[9] =120;
highBin[10] =140;
highBin[11] =160;
highBin[12] =180;
highBin[13] =200;
highBin[14] =250;
highBin[15] =300;
highBin[16] =350;
highBin[17] =400;
highBin[18] =450;
highBin[19] =500;
highBin[20] =600;
highBin[21] =700;
highBin[22] =800;
highBin[23] =900;
highBin[24] =1000;

x[0] = 22.5;
x[1] = 27.5;
x[2] = 35;
x[3] = 45;
x[4] = 55;
x[5] = 65;
x[6] = 75;
x[7] = 85;
x[8] = 95;
x[9] = 110;
x[10] = 130;
x[11] = 150;
x[12] = 170;
x[13] = 190;
x[14] = 225;
x[15] = 275;
x[16] = 325;
x[17] = 375;
x[18] = 425;
x[19] = 475;
x[20] = 550;
x[21] = 650;
x[22] = 750;
x[23] = 850;
x[24] = 950;

xlow[0] = 2.5;
xlow[1] = 2.5;
xlow[2] = 5;
xlow[3] = 5;
xlow[4] = 5;
xlow[5] = 5;
xlow[6] = 5;
xlow[7] = 5;
xlow[8] = 5;
xlow[9] = 10;
xlow[10] = 10;
xlow[11] = 10;
xlow[12] = 10;
xlow[13] = 10;
xlow[14] = 25;
xlow[15] = 25;
xlow[16] = 25;
xlow[17] = 25;
xlow[18] = 25;
xlow[19] = 25;
xlow[20] = 50;
xlow[21] = 50;
xlow[22] = 50;
xlow[23] = 50;
xlow[24] = 50;
int totaln = 0;


for(int i = 0; i<n; i++){
  TH1D* temp = h->ProjectionY("temp",lowBin[i],highBin[i]);
  //temp->Rebin(4);
  std::cout << i << " " << temp->GetEntries() << std::endl;
  if(temp->GetEntries() < 10){
    y[i] = -1;
    ylow[i] = 0;
    yhigh[i] = 0;
    continue;
  }
  totaln++;
  temp->Fit("gaus","L");//,"R","",temp->GetMean()-2*temp->GetRMS(),temp->GetMean()+2*temp->GetRMS());
  temp->Fit("gaus","RL","",temp->GetFunction("gaus")->GetParameter(1)-2*temp->GetFunction("gaus")->GetParameter(2), temp->GetFunction("gaus")->GetParameter(1)+2*temp->GetFunction("gaus")->GetParameter(2));
  //temp->Fit("gaus","R","",temp->GetFunction("gaus")->GetParameter(1)-1.5*temp->GetFunction("gaus")->GetParameter(2), temp->GetFunction("gaus")->GetParameter(1)+1.5*temp->GetFunction("gaus")->GetParameter(2));
  //temp->Fit("gaus","R","",temp->GetFunction("gaus")->GetParameter(1)-1.5*temp->GetFunction("gaus")->GetParameter(2), temp->GetFunction("gaus")->GetParameter(1)+1.5*temp->GetFunction("gaus")->GetParameter(2));
  //temp->Fit("gaus","R","",temp->GetFunction("gaus")->GetParameter(1)-1.5*temp->GetFunction("gaus")->GetParameter(2), temp->GetFunction("gaus")->GetParameter(1)+1.5*temp->GetFunction("gaus")->GetParameter(2));
  y    [i] = temp->GetFunction("gaus")->GetParameter(par);//temp->GetMean();//
  ylow [i] = temp->GetFunction("gaus")->GetParError(par);//temp->GetMeanError();//
  yhigh[i] = ylow[i];//temp->GetFunction("gaus")->GetParError(par);
  if(par == 2){
    y    [i] /= temp->GetFunction("gaus")->GetParameter(1);
    ylow [i] = sqrt(pow(temp->GetFunction("gaus")->GetParError(par)/temp->GetFunction("gaus")->GetParameter(1),2)+
		    pow(temp->GetFunction("gaus")->GetParameter(par)*temp->GetFunction("gaus")->GetParError(1)/
			pow(temp->GetFunction("gaus")->GetParameter(1),2),2));
  }
  delete temp;
}

TGraphErrors* gae = new TGraphErrors(totaln,x,y,xlow,ylow);

TF1 fit("fit","TMath::Sqrt([0]*[0]/x+[1]*[1]/(x*x)+[2]*[2])",10,1000);
fit.SetParameter(0,0.52);
fit.SetParameter(1,3.1);
fit.SetParameter(2,0.0296);
//gae->Fit(&fit);


for(int i = 0; i<n; i++){
  TH1D* temp = bh->ProjectionY("temp",lowBin[i],highBin[i]);
  //temp->Rebin(4);
  std::cout << i << " " << temp->GetEntries() << std::endl;
  if(temp->GetEntries() < 10){
    y[i] = -1;
    ylow[i] = 0;
    yhigh[i] = 0;
    continue;
  }
  totaln++;
  temp->Fit("gaus","L");//,"R","",temp->GetMean()-2*temp->GetRMS(),temp->GetMean()+2*temp->GetRMS());
  temp->Fit("gaus","RL","",temp->GetFunction("gaus")->GetParameter(1)-2*temp->GetFunction("gaus")->GetParameter(2), temp->GetFunction("gaus")->GetParameter(1)+2*temp->GetFunction("gaus")->GetParameter(2));
  //temp->Fit("gaus","R","",temp->GetFunction("gaus")->GetParameter(1)-1.5*temp->GetFunction("gaus")->GetParameter(2), temp->GetFunction("gaus")->GetParameter(1)+1.5*temp->GetFunction("gaus")->GetParameter(2));
  //temp->Fit("gaus","R","",temp->GetFunction("gaus")->GetParameter(1)-1.5*temp->GetFunction("gaus")->GetParameter(2), temp->GetFunction("gaus")->GetParameter(1)+1.5*temp->GetFunction("gaus")->GetParameter(2));
  //temp->Fit("gaus","R","",temp->GetFunction("gaus")->GetParameter(1)-1.5*temp->GetFunction("gaus")->GetParameter(2), temp->GetFunction("gaus")->GetParameter(1)+1.5*temp->GetFunction("gaus")->GetParameter(2));
  y    [i] = temp->GetFunction("gaus")->GetParameter(par);//temp->GetMean();//
  ylow [i] = temp->GetFunction("gaus")->GetParError(par);//temp->GetMeanError();//
  yhigh[i] = ylow[i];//temp->GetFunction("gaus")->GetParError(par);
  if(par == 2){
    y    [i] /= temp->GetFunction("gaus")->GetParameter(1);
    ylow [i] = sqrt(pow(temp->GetFunction("gaus")->GetParError(par)/temp->GetFunction("gaus")->GetParameter(1),2)+
		    pow(temp->GetFunction("gaus")->GetParameter(par)*temp->GetFunction("gaus")->GetParError(1)/
			pow(temp->GetFunction("gaus")->GetParameter(1),2),2));
  }
  delete temp;
}

TGraphErrors* bgae = new TGraphErrors(totaln,x,y,xlow,ylow);

TF1 fit("fit","TMath::Sqrt([0]*[0]/x+[1]*[1]/(x*x)+[2]*[2])",10,1000);
fit.SetParameter(0,0.52);
fit.SetParameter(1,3.1);
fit.SetParameter(2,0.0296);
//gae->Fit(&fit);




TCanvas c;
c.SetGridx();
c.SetGridy();
c.SetLogx();
gae->Draw("AP");
gae->GetXaxis()->SetLimits(10,1000);
gae->GetXaxis()->SetNoExponent();
gae->GetXaxis()->SetMoreLogLabels();
gae->GetYaxis()->SetNoExponent();
//gae->RemovePoint(24);
//gae->RemovePoint(23);
//gae->RemovePoint(22);
//gae->RemovePoint(21);
gae->GetYaxis()->SetMoreLogLabels();
gae->GetXaxis()->SetTitle("p^{true}_{T} [GeV]");
if(par == 2){
  c.SetLogy();
  gae->SetMaximum(0.3);
  gae->SetMinimum(0.02);
  gae->GetYaxis()->SetTitle("#sigma_{R}/R");
}else{
  
  gae->GetYaxis()->SetTitle("Response=p^{reco}_{T}/p^{true}_{T}");
  gae->GetYaxis()->SetTitleOffset(1.13);
  gae->SetMaximum(1.10);
  gae->SetMinimum(0.9);
}

//bgae->Draw("AP");
 bgae->Draw("P,SAME");
 bgae->GetXaxis()->SetLimits(10,1000);
 bgae->GetXaxis()->SetNoExponent();
 bgae->GetXaxis()->SetMoreLogLabels();
 bgae->GetYaxis()->SetNoExponent();
 bgae->SetMarkerColor(2);
//bgae->RemovePoint(24);
 //bgae->RemovePoint(23);
 //bgae->RemovePoint(22);
 //bgae->RemovePoint(21);
 bgae->GetYaxis()->SetMoreLogLabels();
 bgae->GetXaxis()->SetTitle("p^{true}_{T} [GeV]");
 if(par == 2){
   c.SetLogy();
   bgae->SetMaximum(0.3);
   bgae->SetMinimum(0.02);
   bgae->GetYaxis()->SetTitle("#sigma_{R}/R");
 }else{

   bgae->GetYaxis()->SetTitle("Response=p^{reco}_{T}/p^{true}_{T}");
   bgae->GetYaxis()->SetTitleOffset(1.13);
   bgae->SetMaximum(1.10);
   bgae->SetMinimum(0.9);
 }



TLegend leg(0.25,0.2,0.65,0.5);
leg.AddEntry(gae,"bjHadE","pl");
leg.AddEntry(bgae,"bjMuonMuresp","pl");

leg.SetFillStyle(0);
leg.SetBorderSize(0);
leg.Draw("same");
c.SaveAs(saveName.c_str());
c.SaveAs(saveNamePng.c_str());
//c.SaveAs(saveNameC.c_str());


}
