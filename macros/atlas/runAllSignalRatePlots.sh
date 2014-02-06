#!/bin/sh

#option=$1
#topo=$2
#nev=$3
#if [ -z "$2" ]; then 
#	nev=99999999
#fi

#if [ "${option}" = "l2btag" ]
#then
	#root -l -q -b ana.C\(\"$topo\",\"data158116.exttrg004\",$nev,1\) &> data158116.exttrg004.log&
	#root -l -q -b ana.C\(\"$topo\",\"data158045.exttrg004\",$nev,1\) &> data158045.exttrg004.log
	#root -l -q -b ana.C\(\"$topo\",\"data153565.exttrg003\",$nev,1\) &> data153565.exttrg003.log&
#	root -l -q -b ana.C\(\"$topo\",\"j2.exttrgmc006\",$nev,0\) &> j2.exttrgmc006.log&
#fi

root -l -b -q runRatePlots.C\(\"py2bB400L100\",\"xe-EF-scan-susysoft\"\)
root -l -b -q runRatePlots.C\(\"py2bB400L300\",\"xe-EF-scan-susysoft\"\)
root -l -b -q runRatePlots.C\(\"py4bG400L100\",\"xe-EF-scan-susysoft\",\"GbL\"\)
root -l -b -q runRatePlots.C\(\"py4bG400L300\",\"xe-EF-scan-susysoft\",\"GbS\"\)
#root -l -b -q runRatePlots.C\(\"py4tbG400L100\",\"xe-EF-scan-susysoft\"\)
#root -l -b -q runRatePlots.C\(\"py4tbG400L200\",\"xe-EF-scan-susysoft\"\)
#root -l -b -q runRatePlots.C\(\"py4tG500L100\",\"xe-EF-scan-susysoft\"\)
#root -l -b -q runRatePlots.C\(\"py4tG500L60\",\"xe-EF-scan-susysoft\"\)
#root -l -b -q runRatePlots.C\(\"su4\",\"xe-EF-scan-susysoft\"\)

#      legend[numberLegends++]  = "#tilde{g}#rightarrowb#bar{b}#Chi^{0} #DeltaM(#tilde{g},#Chi^{0})=100GeV";
#      //legend[numberLegends++]  = "#tilde{g}#rightarrowb#bar{b}#Chi^{0} M_{#tilde{g}}=400GeV,M_{#Chi^{0}}=300GeV";
#      fileNames[numberFiles++] = dir + "py4bG400L100.exttrgmc006.root";
#      legend[numberLegends++]  = "#tilde{g}#rightarrowb#bar{b}#Chi^{0} #DeltaM(#tilde{g},#Chi^{0})=300GeV";
#      //legend[numberLegends++]  = "#tilde{g}#rightarrowb#bar{b}#Chi^{0} M_{#tilde{g}}=400GeV,M_{#Chi^{0}}=100GeV";
#      fileNames[numberFiles++] = dir + "py2bB400L100.exttrgmc006.root";
#      legend[numberLegends++]  = "#tilde{b}#rightarrowb#Chi^{0} #DeltaM(#tilde{b},#Chi^{0})=300GeV";
#      //legend[numberLegends++]  = "#tilde{b}#rightarrowb#Chi^{0} M_{#tilde{b}}=400GeV,M_{#Chi^{0}}=100GeV";
#      fileNames[numberFiles++] = dir + "py2bB400L300.exttrgmc006.root";
#      legend[numberLegends++]  = "#tilde{b}#rightarrowb#Chi^{0} #DeltaM(#tilde{b},#Chi^{0})=100GeV";
