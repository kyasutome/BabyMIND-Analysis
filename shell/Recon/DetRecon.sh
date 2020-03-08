#!/bin/sh

if [ $# -ne 3 ] ; then
  echo ""
  echo "  !!! ./DetRecon.sh [wgrun][ientry][targetmod] !!!"
  echo "example)"
  echo "./DetRecon.sh 92 1 1"
  exit 1
fi

run=$1
ientry=$2
targetmod=$3

anadir=${PWD}
#datadir=$anadir/process/3-EVT
datadir=$anadir/process/3-MCEVT

filename=$(find  $datadir -type f -name "Evt_${run}.root")
if [ $? -eq 0 ] ; then
    echo "Found a file"
    else
    exit 0
fi
echo "Filename="$filename
echo "Analyze the file..."

cd $anadir
./bin/DetRecon $filename $run $ientry $targetmod