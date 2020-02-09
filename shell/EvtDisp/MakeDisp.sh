#!/bin/sh

if [ $# -ne 2 ] ; then
  echo ""
  echo "  !!! ./MakeDisp.sh [run] [ientry] !!!"
  echo "example)"
  echo "./MakeDisp.sh 29 1"
  exit 1
fi

run=$1
entry=$2

anadir=${PWD}
#datadir=$anadir/process/TEST
datadir=$anadir/process/3-EVT

filename=$(find  $datadir -type f -name "Evt_${run}.root")
if [ $? -eq 0 ] ; then
    echo "Found a file"
    else
    exit 0
fi

echo "Filename="$filename
echo "Analyze the file..."

cd $anadir
./bin/MakeDisp $filename $run $entry