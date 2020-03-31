#!/bin/sh

if [ $# -ne 2 ] ; then
  echo ""
  echo "  !!! ./CheckRecon.sh [wgrun][entry] !!!"
  echo "example)"
  echo "./CheckRecon.sh 92 1"
  exit 1
fi

run=$1
entry=$2

#anadir=${PWD}
datadir=$anadir/process/4-Recon

filename=$(find  $datadir -type f -name "Recon_${run}.root")
if [ $? -eq 0 ] ; then
    echo "Found a file"
    else
    exit 0
fi
echo "Filename="$filename
echo "Analyze the file..."

cd $anadir
./bin/CheckRecon $filename $run $entry