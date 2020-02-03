#!/bin/sh

if [ $# -ne 5 ] ; then
  echo ""
  echo "  !!! ./MakeDisp.sh [date] [month] [run] [subrun] [ientry] !!!"
  echo "example)"
  echo "./MakeDisp.sh 8 Nov 0 0 1"
  exit 1
fi

date=$1
month=$2
run=$3
subrun=$4
entry=$5

anadir=${PWD}
datadir=$anadir/process

filename=$(find  $datadir -type f -name "*BMEvt_${date}${month}_${run}-${subrun}*")
if [ $? -eq 0 ] ; then
    echo "Found a file"
    else
    exit 0
fi

echo "Filename="$filename
echo "Analyze the file..."

cd $anadir
./bin/MakeDisp $filename $date $month $run $subrun $entry