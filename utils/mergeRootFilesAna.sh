#!/bin/zsh

# Parameter to scripts is: grid user name

WDIR=$PWD
SCRIPTDIR="/afs/cern.ch/user/p/phansson/scripts/root_macros/"
echo "Working in dir: "$WDIR
echo "Script dir    : "$SCRIPTDIR

# sth/phsth/fast/etc/
TYPE=$1
echo "Type is: "$TYPE
SUFFIX=$2
echo "Suffix is: "$SUFFIX

# beginning of filenames to merge
FILENAMES=($3 $4 $5 $6 $7 $8 $9 $10 $11 $12)


#for i in *.$TYPE.root
for i in ${FILENAMES}
do NAME="${i}${SUFFIX}.${TYPE}.root"
echo $i" --> "$NAME
$SCRIPTDIR/mergeRootFiles.py $i $TYPE $NAME
done


