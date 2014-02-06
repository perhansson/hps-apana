#include <vector>

runBtagOptOverlay()
{

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);

  gSystem->AddIncludePath(" -I${HOME}/work/RootUtils ");
  gSystem->CompileMacro ("${HOME}/work/RootUtils/Util.cpp", "k");
  gSystem->CompileMacro ("BtagOptOverlay.C", "k");
  
  TString newLabel = " ";
  TString preStr   = "BtagOpt";
  TString fileStr  = preStr + "_v01";
  
  TString outDir      = "/Users/bbutler/work/Plots/BtagOptimization/";
  TString outFileName = fileStr + ".root";
  TString psFile      = outDir + fileStr;
  TString plotType    = ".eps";
  bool dataMCCompare  = false;
  
  vector<TString> fileNames;
  fileNames.push_back("/users/bbutler/work/FlatAna/topologies/jetmetbtag/btag_opt/jX.exttrgmc008.root");
  fileNames.push_back("/users/bbutler/work/FlatAna/topologies/jetmetbtag/btag_opt/tt.exttrgmc006.root");
  fileNames.push_back("/users/bbutler/work/FlatAna/topologies/jetmetbtag/btag_opt/tthad.exttrgmc106.root");
  fileNames.push_back("/users/bbutler/work/FlatAna/topologies/jetmetbtag/btag_opt/wbb.exttrgmc106.root");
  fileNames.push_back("/users/bbutler/work/FlatAna/topologies/jetmetbtag/btag_opt/py2bB400L100.exttrgmc106.root");
  fileNames.push_back("/users/bbutler/work/FlatAna/topologies/jetmetbtag/btag_opt/py2bB400L300.exttrgmc106.root");
  fileNames.push_back("/users/bbutler/work/FlatAna/topologies/jetmetbtag/btag_opt/py4bG400L100.exttrgmc106.root");
  fileNames.push_back("/users/bbutler/work/FlatAna/topologies/jetmetbtag/btag_opt/py4bG400L300.exttrgmc106.root");
  fileNames.push_back("/users/bbutler/work/FlatAna/topologies/jetmetbtag/btag_opt/py4tbG400L100.exttrgmc106.root");
  fileNames.push_back("/users/bbutler/work/FlatAna/topologies/jetmetbtag/btag_opt/py4tbG400L200.exttrgmc106.root");
  fileNames.push_back("/users/bbutler/work/FlatAna/topologies/jetmetbtag/btag_opt/su4.exttrgmc106.root");  
  fileNames.push_back("/users/bbutler/work/FlatAna/topologies/jetmetbtag/btag_opt/tt.exttrgmc006.root");
  //fileNames.push_back("/Users/bbutler/work/JetCONFNote/root/outdir/" + preStr + "_Data.root");
  
  vector<TString> prefix;
  prefix.push_back("");
  prefix.push_back("");
  prefix.push_back("");
  prefix.push_back("");
  prefix.push_back("");
  prefix.push_back("");
  prefix.push_back("");
  prefix.push_back("");
  prefix.push_back("");
  prefix.push_back("");
  prefix.push_back("");
  prefix.push_back("");
  
  vector<TString> suffix;
  suffix.push_back("");
  suffix.push_back("");
  suffix.push_back("");
  suffix.push_back("");
  suffix.push_back("");
  suffix.push_back("");
  suffix.push_back("");
  suffix.push_back("");
  suffix.push_back("");
  suffix.push_back("");
  suffix.push_back("");
  suffix.push_back("");
  
  vector<TString> tags;
  tags.push_back("QCD di-jets");
  tags.push_back("ttbar");
  tags.push_back("ttbar full-hadronic");
  tags.push_back("Wbb");  
  tags.push_back("2bB400L100");
  tags.push_back("2bB400L300");
  tags.push_back("4bG400L100");
  tags.push_back("4bG400L300");
  tags.push_back("4tbG400L100");
  tags.push_back("4tbG400L200");  
  tags.push_back("SU4");
  tags.push_back("ttbar");  
  //tags.push_back("Data 2010  #sqrt{s} = 7 TeV");
  //tags.push_back("anti-k_{t} topo-cluster jets R=0.6");
  
  vector<TString> outstrings;
  outstrings.push_back("qcd");
  outstrings.push_back("ttbar");
  outstrings.push_back("ttbarhad");
  outstrings.push_back("wjets");
  outstrings.push_back("2bB400L100");
  outstrings.push_back("2bB400L300");
  outstrings.push_back("4bG400L100");
  outstrings.push_back("4bG400L300");
  outstrings.push_back("4tbG400L100");
  outstrings.push_back("4tbG400L200");  
  outstrings.push_back("SU4");
  outstrings.push_back("ttbar");
  
  vector<TString> plotDir;
  plotDir.push_back("");
  plotDir.push_back("");
  plotDir.push_back("");
  plotDir.push_back("");
  plotDir.push_back("");
  plotDir.push_back("");
  plotDir.push_back("");
  plotDir.push_back("");
  plotDir.push_back("");
  plotDir.push_back("");
  plotDir.push_back("");
  plotDir.push_back("");
  
  vector<double> weights;
  weights.push_back(1.0); 
  weights.push_back(1.0);
  weights.push_back(1.0); 
  weights.push_back(1.0);
  weights.push_back(1.0); 
  weights.push_back(1.0);
  weights.push_back(1.0); 
  weights.push_back(1.0);
  weights.push_back(1.0); 
  weights.push_back(1.0);
  weights.push_back(1.0);
  weights.push_back(1.0);
  
  vector<bool> signal;
  signal.push_back(false); 
  signal.push_back(false);
  signal.push_back(false); 
  signal.push_back(false);
  signal.push_back(true); 
  signal.push_back(true);
  signal.push_back(true); 
  signal.push_back(true);
  signal.push_back(true); 
  signal.push_back(true);
  signal.push_back(true); 
  signal.push_back(true);
  
  bool savePlots = true;
  bool doRatio   = false;
  bool setLogY   = true;
  bool setLogZ   = false;
  int Rebin = 10;
  
  Int_t NOverlay = fileNames.size();
  BtagOptOverlay
            (NOverlay,
             outFileName,
             fileNames, 
             prefix, 
             suffix,
             tags, 
             outstrings,
             plotDir,
             weights,
             signal,
             outDir, 
             psFile,
             plotType,
             dataMCCompare,
             doRatio,
             "",
             savePlots,
             setLogY,
             setLogZ,
             Rebin);

}
