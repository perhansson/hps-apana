#!/bin/sh

option=$1
topo=$2
nev=$3

if [ -z "$2" ]; then 
	nev=99999999
fi

if [ "${option}" = "data" ]
then
	#root -l -q -b ana.C\(\"$topo\",\"data158116.exttrg007\",$nev,1\) &> data158116.exttrg007.log&
	#root -l -q -b ana.C\(\"$topo\",\"data158116.exttrg006\",$nev,1\) &> data158116.exttrg006.log&
	#root -l -q -b ana.C\(\"$topo\",\"data158045.exttrg004\",$nev,1\) &> data158045.exttrg004.log
	#root -l -q -b ana.C\(\"$topo\",\"data153565.exttrg003\",$nev,1\) &> data153565.exttrg003.log&
	#root -l -q -b ana.C\(\"$topo\",\"data153565.exttrg008\",$nev,1\) &> data153565.exttrg008.log
	#root -l -q -b ana.C\(\"$topo\",\"data159224.exttrg007\",$nev,1\) &> data159224.exttrg007.log
	#root -l -q -b ana.C\(\"$topo\",\"data160953.exttrg008\",$nev,1\) &> data160953.exttrg008.log&
	#root -l -q -b ana.C\(\"$topo\",\"data160980.exttrg008\",$nev,1\) &> data160980.exttrg008.log
	#root -l -q -b ana.C\(\"$topo\",\"data160879.exttrg008\",$nev,1\) &> data160879.exttrg008.log
	root -l -q -b ana.C\(\"$topo\",\"data160980.exttrg009\",$nev,1\) &> data160980.exttrg009.log
	#root -l -q -b ana.C\(\"$topo\",\"data153565.exttrg009\",$nev,1\) &> data153565.exttrg009.log
fi

if [ "${option}" = "susy" ]
then
	root -l -q -b ana.C\(\"$topo\",\"py4bG400L100.exttrgmc106\",$nev,0\) &> py4bG400L100.exttrgmc106.log&
	root -l -q -b ana.C\(\"$topo\",\"py4bG400L300.exttrgmc106\",$nev,0\) &> py4bG400L300.exttrgmc106.log
	root -l -q -b ana.C\(\"$topo\",\"py2bB400L300.exttrgmc106\",$nev,0\) &> py2bB400L300.exttrgmc106.log&
	root -l -q -b ana.C\(\"$topo\",\"py2bB400L100.exttrgmc106\",$nev,0\) &> py2bB400L100.exttrgmc106.log
	root -l -q -b ana.C\(\"$topo\",\"su4.exttrgmc106\",$nev,0\) &> su4.exttrgmc106.log&
	root -l -q -b ana.C\(\"$topo\",\"py4tbG400L200.exttrgmc106\",$nev,0\) &> py4tbG400L200.exttrgmc106.log&
	root -l -q -b ana.C\(\"$topo\",\"py4tbG400L100.exttrgmc106\",$nev,0\) &> py4tbG400L100.exttrgmc106.log

	#root -l -q -b ana.C\(\"$topo\",\"py4tG500L60.exttrgmc006\",$nev,0\) &> py4tG500L60.exttrgmc006.log
	#root -l -q -b ana.C\(\"$topo\",\"py4tG500L100.exttrgmc006\",$nev,0\) &> py4tG500L100.exttrgmc006.log&
    #root -l -q -b ana.C\(\"$topo\",\"su4r13.trg004\",$nev,0\) &> su4r13.trg004.log

fi

if [ "${option}" = "qcd" ]
then
	root -l -q -b ana.C\(\"$topo\",\"j2.exttrgmc009\",$nev,0\) &> j2.exttrgmc009.log&
	root -l -q -b ana.C\(\"$topo\",\"j1.exttrgmc009\",$nev,0\) &> j1.exttrgmc009.log
	root -l -q -b ana.C\(\"$topo\",\"j0.exttrgmc009\",$nev,0\) &> j0.exttrgmc009.log&
	root -l -q -b ana.C\(\"$topo\",\"j3.exttrgmc009\",$nev,0\) &> j3.exttrgmc009.log
	root -l -q -b ana.C\(\"$topo\",\"j4.exttrgmc009\",$nev,0\) &> j4.exttrgmc009.log&
	root -l -q -b ana.C\(\"$topo\",\"j5.exttrgmc009\",$nev,0\) &> j5.exttrgmc009.log
	#root -l -q -b ana.C\(\"$topo\",\"j2.exttrgmc008\",$nev,0\) &> j2.exttrgmc008.log&
	#root -l -q -b ana.C\(\"$topo\",\"j1.exttrgmc008\",$nev,0\) &> j1.exttrgmc008.log
	#root -l -q -b ana.C\(\"$topo\",\"j0.exttrgmc008\",$nev,0\) &> j0.exttrgmc008.log&
	#root -l -q -b ana.C\(\"$topo\",\"j3.exttrgmc008\",$nev,0\) &> j3.exttrgmc008.log
	#root -l -q -b ana.C\(\"$topo\",\"j4.exttrgmc008\",$nev,0\) &> j4.exttrgmc008.log&
	#root -l -q -b ana.C\(\"$topo\",\"j5.exttrgmc008\",$nev,0\) &> j5.exttrgmc008.log
	#root -l -q -b ana.C\(\"$topo\",\"j2pu.exttrgmc008\",$nev,0\) &> j2pu.exttrgmc008.log&
	#root -l -q -b ana.C\(\"$topo\",\"j1pu.exttrgmc008\",$nev,0\) &> j1pu.exttrgmc008.log
	#root -l -q -b ana.C\(\"$topo\",\"j0pu.exttrgmc008\",$nev,0\) &> j0pu.exttrgmc008.log&
	#root -l -q -b ana.C\(\"$topo\",\"j3pu.exttrgmc008\",$nev,0\) &> j3pu.exttrgmc008.log
fi

if [ "${option}" = "mb" ]
then
	root -l -q -b ana.C\(\"$topo\",\"mb.exttrgmc008\",$nev,0\) &> mb.exttrgmc008.log
fi

if [ "${option}" = "top" ]
then
	root -l -q -b ana.C\(\"$topo\",\"tt.exttrgmc008\",$nev,0\) &> tt.exttrgmc008.log
	#root -l -q -b ana.C\(\"$topo\",\"tthad.exttrgmc008\",$nev,0\) &> tthad.exttrgmc008.log
fi


if [ "${option}" = "wjets" ]
then
	root -l -q -b ana.C\(\"$topo\",\"wbb0.exttrgmc008\",$nev,0\) &> wbb0.exttrgmc008.log& 
    root -l -q -b ana.C\(\"$topo\",\"wbb1.exttrgmc008\",$nev,0\) &> wbb1.exttrgmc008.log 
    root -l -q -b ana.C\(\"$topo\",\"wbb2.exttrgmc008\",$nev,0\) &> wbb2.exttrgmc008.log& 
    root -l -q -b ana.C\(\"$topo\",\"wbb3.exttrgmc008\",$nev,0\) &> wbb3.exttrgmc008.log 
	#root -l -q -b ana.C\(\"$topo\",\"we0.exttrgmc007\",$nev,0\) &> we0.exttrgmc007.log 
	#root -l -q -b ana.C\(\"$topo\",\"we1.exttrgmc007\",$nev,0\) &> we1.exttrgmc007.log 
	#root -l -q -b ana.C\(\"$topo\",\"we2.exttrgmc007\",$nev,0\) &> we2.exttrgmc007.log 
	#root -l -q -b ana.C\(\"$topo\",\"we3.exttrgmc007\",$nev,0\) &> we3.exttrgmc007.log 
	#root -l -q -b ana.C\(\"$topo\",\"we4.exttrgmc007\",$nev,0\) &> we4.exttrgmc007.log 
	#root -l -q -b ana.C\(\"$topo\",\"we5.exttrgmc007\",$nev,0\) &> we5.exttrgmc007.log 
	#root -l -q -b ana.C\(\"$topo\",\"wm0.exttrgmc007\",$nev,0\) &> wm0.exttrgmc007.log 
	#root -l -q -b ana.C\(\"$topo\",\"wm1.exttrgmc007\",$nev,0\) &> wm1.exttrgmc007.log 
	#root -l -q -b ana.C\(\"$topo\",\"wm2.exttrgmc007\",$nev,0\) &> wm2.exttrgmc007.log 
	#root -l -q -b ana.C\(\"$topo\",\"wm3.exttrgmc007\",$nev,0\) &> wm3.exttrgmc007.log 
	#root -l -q -b ana.C\(\"$topo\",\"wm4.exttrgmc007\",$nev,0\) &> wm4.exttrgmc007.log 
	#root -l -q -b ana.C\(\"$topo\",\"wm5.exttrgmc007\",$nev,0\) &> wm5.exttrgmc007.log 
	#root -l -q -b ana.C\(\"$topo\",\"wt0.exttrgmc007\",$nev,0\) &> wt0.exttrgmc007.log 
	#root -l -q -b ana.C\(\"$topo\",\"wt1.exttrgmc007\",$nev,0\) &> wt1.exttrgmc007.log 
	#root -l -q -b ana.C\(\"$topo\",\"wt2.exttrgmc007\",$nev,0\) &> wt2.exttrgmc007.log 
	#root -l -q -b ana.C\(\"$topo\",\"wt3.exttrgmc007\",$nev,0\) &> wt3.exttrgmc007.log 
	#root -l -q -b ana.C\(\"$topo\",\"wt4.exttrgmc007\",$nev,0\) &> wt4.exttrgmc007.log 
	#root -l -q -b ana.C\(\"$topo\",\"wt5.exttrgmc007\",$nev,0\) &> wt5.exttrgmc007.log 
fi

if [ "${option}" = "zjets" ]
then
	root -l -q -b ana.C\(\"$topo\",\"zee0.exttrgmc007\",$nev,0\) &> zee0.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"zee1.exttrgmc007\",$nev,0\) &> zee1.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"zee2.exttrgmc007\",$nev,0\) &> zee2.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"zee3.exttrgmc007\",$nev,0\) &> zee3.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"zee4.exttrgmc007\",$nev,0\) &> zee4.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"zee5.exttrgmc007\",$nev,0\) &> zee5.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"zmm0.exttrgmc007\",$nev,0\) &> zmm0.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"zmm1.exttrgmc007\",$nev,0\) &> zmm1.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"zmm2.exttrgmc007\",$nev,0\) &> zmm2.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"zmm3.exttrgmc007\",$nev,0\) &> zmm3.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"zmm4.exttrgmc007\",$nev,0\) &> zmm4.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"zmm5.exttrgmc007\",$nev,0\) &> zmm5.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"ztt0.exttrgmc007\",$nev,0\) &> ztt0.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"ztt1.exttrgmc007\",$nev,0\) &> ztt1.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"ztt2.exttrgmc007\",$nev,0\) &> ztt2.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"ztt3.exttrgmc007\",$nev,0\) &> ztt3.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"ztt4.exttrgmc007\",$nev,0\) &> ztt4.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"ztt5.exttrgmc007\",$nev,0\) &> ztt5.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"znn0.exttrgmc007\",$nev,0\) &> znn0.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"znn1.exttrgmc007\",$nev,0\) &> znn1.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"znn2.exttrgmc007\",$nev,0\) &> znn2.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"znn3.exttrgmc007\",$nev,0\) &> znn3.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"znn4.exttrgmc007\",$nev,0\) &> znn4.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"znn5.exttrgmc007\",$nev,0\) &> znn5.exttrgmc007.log 

fi

if [ "${option}" = "diboson" ]
then
	root -l -q -b ana.C\(\"$topo\",\"ww.exttrgmc007\",$nev,0\) &> ww.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"wz.exttrgmc007\",$nev,0\) &> wz.exttrgmc007.log 
	root -l -q -b ana.C\(\"$topo\",\"zz.exttrgmc007\",$nev,0\) &> zz.exttrgmc007.log 
fi

if [ "${option}" = "tru002" ]
then
	root -l -q -b ana.C\(\"$topo\",\"py4bG300L60.tru002\",$nev\) &> py4bG300L60.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4bG300L100.tru002\",$nev\) &> py4bG300L100.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4bG300L200.tru002\",$nev\) &> py4bG300L200.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4bG400L60.tru002\",$nev\) &> py4bG400L60.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4bG400L100.tru002\",$nev\) &> py4bG400L100.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4bG400L200.tru002\",$nev\) &> py4bG400L200.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4bG400L300.tru002\",$nev\) &> py4bG400L300.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4bG500L60.tru002\",$nev\) &> py4bG500L60.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4bG500L100.tru002\",$nev\) &> py4bG500L100.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4bG500L200.tru002\",$nev\) &> py4bG500L200.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4bG500L300.tru002\",$nev\) &> py4bG500L300.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4bG500L400.tru002\",$nev\) &> py4bG500L400.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py2bB300L60.tru002\",$nev\) &> py2bB300L60.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py2bB300L100.tru002\",$nev\) &> py2bB300L100.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py2bB300L200.tru002\",$nev\) &> py2bB300L200.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py2bB400L60.tru002\",$nev\) &> py2bB400L60.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py2bB400L100.tru002\",$nev\) &> py2bB400L100.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py2bB400L200.tru002\",$nev\) &> py2bB400L200.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py2bB400L300.tru002\",$nev\) &> py2bB400L300.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py2bB500L60.tru002\",$nev\) &> py2bB500L60.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py2bB500L100.tru002\",$nev\) &> py2bB500L100.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py2bB500L200.tru002\",$nev\) &> py2bB500L200.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py2bB500L300.tru002\",$nev\) &> py2bB500L300.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py2bB500L400.tru002\",$nev\) &> py2bB500L400.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4tbG300L60.tru002\",$nev\) &> py4tbG300L60.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4tbG300L100.tru002\",$nev\) &> py4tbG300L100.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4tbG400L60.tru002\",$nev\) &> py4tbG400L60.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4tbG400L100.tru002\",$nev\) &> py4tbG400L100.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4tbG400L200.tru002\",$nev\) &> py4tbG400L200.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4tbG500L60.tru002\",$nev\) &> py4tbG500L60.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4tbG500L100.tru002\",$nev\) &> py4tbG500L100.tru002.log
	root -l -q -b ana.C\(\"$topo\",\"py4tbG500L200.tru002\",$nev\) &> py4tbG500L200.tru002.log

fi



if [ "${option}" = "trg004" ]
then
    #root -l -q -b ana.C\(\"$topo\",\"j1r13.trg004\",$nev\) &> j1r13.trg004.log
    #root -l -q -b ana.C\(\"$topo\",\"j0r13.trg004\",$nev\) &> j0r13.trg004.log
    root -l -q -b ana.C\(\"$topo\",\"tt.trg004\",$nev,0\) &> tt.trg004.log&
    #root -l -q -b ana.C\(\"$topo\",\"j2.trg004\",$nev\) &> j2.trg004.log
    #root -l -q -b ana.C\(\"$topo\",\"su4r13.trg004\",$nev\) &> su4r13.trg004.log
    root -l -q -b ana.C\(\"$topo\",\"ttr13.trg004\",$nev,0\) &> ttr13.trg004.log&
    #root -l -q -b ana.C\(\"$topo\",\"j2r13.trg004\",$nev\) &> j2r13.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"bb20.trg004\",$nev\) &> bb20.trg004.log&
	#root -l -q -b ana.C\(\"$topo\",\"bb21.trg004\",$nev\) &> bb21.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"bb22.trg004\",$nev\) &> bb22.trg004.log&
	#root -l -q -b ana.C\(\"$topo\",\"bb23.trg004\",$nev\) &> bb23.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"bb24.trg004\",$nev\) &> bb24.trg004.log&
	#root -l -q -b ana.C\(\"$topo\",\"bb30.trg004\",$nev\) &> bb30.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"bb31.trg004\",$nev\) &> bb31.trg004.log&
	#root -l -q -b ana.C\(\"$topo\",\"bb32.trg004\",$nev\) &> bb32.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"bb33.trg004\",$nev\) &> bb33.trg004.log&
	#root -l -q -b ana.C\(\"$topo\",\"bb34.trg004\",$nev\) &> bb34.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"bb40.trg004\",$nev\) &> bb40.trg004.log&
	#root -l -q -b ana.C\(\"$topo\",\"bb41.trg004\",$nev\) &> bb41.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"bb42.trg004\",$nev\) &> bb42.trg004.log&
	#root -l -q -b ana.C\(\"$topo\",\"bb43.trg004\",$nev\) &> bb43.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"bb44.trg004\",$nev\) &> bb44.trg004.log&
	#root -l -q -b ana.C\(\"$topo\",\"bb50.trg004\",$nev\) &> bb50.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"bb51.trg004\",$nev\) &> bb51.trg004.log&
	#root -l -q -b ana.C\(\"$topo\",\"bb52.trg004\",$nev\) &> bb52.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"bb53.trg004\",$nev\) &> bb53.trg004.log&
	#root -l -q -b ana.C\(\"$topo\",\"bb54.trg004\",$nev\) &> bb54.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"ja22.trg004\",$nev\) &> ja22.trg004.log&
	#root -l -q -b ana.C\(\"$topo\",\"ja23.trg004\",$nev\) &> ja23.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"ja25.trg004\",$nev\) &> ja25.trg004.log&
	#root -l -q -b ana.C\(\"$topo\",\"ja32.trg004\",$nev\) &> ja32.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"ja33.trg004\",$nev\) &> ja33.trg004.log&
	#root -l -q -b ana.C\(\"$topo\",\"ja34.trg004\",$nev\) &> ja34.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"ja35.trg004\",$nev\) &> ja35.trg004.log&
	#root -l -q -b ana.C\(\"$topo\",\"ja43.trg004\",$nev\) &> ja43.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"ja44.trg004\",$nev\) &> ja44.trg004.log&
	#root -l -q -b ana.C\(\"$topo\",\"ja45.trg004\",$nev\) &> ja45.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"ja46.trg004\",$nev\) &> ja46.trg004.log&
	#root -l -q -b ana.C\(\"$topo\",\"ja53.trg004\",$nev\) &> ja53.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"ja54.trg004\",$nev\) &> ja54.trg004.log&
	#root -l -q -b ana.C\(\"$topo\",\"ja55.trg004\",$nev\) &> ja55.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"ja56.trg004\",$nev\) &> ja56.trg004.log&
fi


if [ "${option}" = "rates" ]
then
	#root -l -q -b ana.C\(\"$topo\",\"j2.trg004\",$nev\) &> j2.trg004.log
	root -l -q -b ana.C\(\"$topo\",\"j2.exttrgmc006\",$nev\) &> j2.exttrgmc006.log
	#root -l -q -b ana.C\(\"$topo\",\"j1.exttrgmc006\",$nev\) &> j1.exttrgmc006.log&
	#root -l -q -b ana.C\(\"$topo\",\"j0.exttrgmc006\",$nev\) &> j0.exttrgmc006.log&
	#root -l -q -b ana.C\(\"$topo\",\"py4bG400L100.exttrgmc006\",$nev\) &> py4bG400L100.exttrgmc006.log
	#root -l -q -b ana.C\(\"$topo\",\"py4bG400L300.exttrgmc006\",$nev\) &> py4bG400L300.exttrgmc006.log&
	#root -l -q -b ana.C\(\"$topo\",\"py4tbG400L200.exttrgmc006\",$nev\) &> py4tbG400L200.exttrgmc006.log
	#root -l -q -b ana.C\(\"$topo\",\"py4tbG400L100.exttrgmc006\",$nev\) &> py4tbG400L100.exttrgmc006.log&
	#root -l -q -b ana.C\(\"$topo\",\"py2bB400L100.exttrgmc006\",$nev\) &> py2bB400L100.exttrgmc006.log&
	#root -l -q -b ana.C\(\"$topo\",\"py2bB400L300.exttrgmc006\",$nev\) &> py2bB400L300.exttrgmc006.log
	#root -l -q -b ana.C\(\"$topo\",\"py4tG500L60.exttrgmc006\",$nev\) &> py4tG400L60.exttrgmc006.log&
	#root -l -q -b ana.C\(\"$topo\",\"py4tG500L100.exttrgmc006\",$nev\) &> py4tG400L100.exttrgmc006.log
    #root -l -q -b ana.C\(\"$topo\",\"su4.trg002\",$nev\) &> su4.trg002.log
    #root -l -q -b ana.C\(\"$topo\",\"st.trg002\",$nev\) &> st.trg002.log
	#root -l -q -b ana.C\(\"$topo\",\"tt.exttrgmc006\",$nev,0\) &> tt.exttrgmc006.log&
    #root -l -q -b ana.C\(\"$topo\",\"tt.trg004\",$nev\) &> tt.trg004.log
	#root -l -q -b ana.C\(\"$topo\",\"tthad.exttrgmc006\",$nev,0\) &> tthad.exttrgmc006.log


fi

if [ "${option}" = "trg002" ]
then
    root -l -q -b ana.C\(\"$topo\",\"tt.trg002\",$nev\) &> tt.trg002.log
    #root -l -q -b ana.C\(\"$topo\",\"st.trg002\",$nev\) &> st.trg002.log
    root -l -q -b ana.C\(\"$topo\",\"su4.trg002\",$nev\) &> su4.trg002.log&
	#root -l -q -b ana.C\(\"$topo\",\"j0.trg002\",$nev\) &> j0.trg002.log
    #root -l -q -b ana.C\(\"$topo\",\"j1.trg002\",$nev\) &> j1.trg002.log&
	#root -l -q -b ana.C\(\"$topo\",\"j2.trg002\",$nev\) &> j2.trg002.log
    #root -l -q -b ana.C\(\"$topo\",\"j3.trg002\",$nev\) &> j3.trg002.log&
    #root -l -q -b ana.C\(\"$topo\",\"j4.trg002\",$nev\) &> j4.trg002.log
    #root -l -q -b ana.C\(\"$topo\",\"j5.trg002\",$nev\) &> j5.trg002.log&
    #root -l -q -b ana.C\(\"$topo\",\"j6.trg002\",$nev\) &> j6.trg002.log&
fi










##########################################################################

