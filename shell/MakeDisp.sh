#!/bin/sh

if [ $# -ne 4 ] ; then
  echo ""
  echo "  !!! ./MakeDisp.sh [date] [month] [run] [ientry] !!!"
  echo "example)"
  echo "./MakeDisp.sh 8 Nov 0 1"
  exit 1
fi

date=$1
month=$2
run=$3
entry=$4

anadir=${PWD}
datadir=$anadir/process

#filename=$(find  $datadir -type f -name "*BMCalib_$date$month_$run*")
filename=$(find  $datadir -type f -name "*BMEvt_8Nov_0*")
if [ $? -eq 0 ] ; then
    echo "Found a file"
    else
    exit 0
fi

echo "Filename="$filename
echo "Analyze the file..."

cd $anadir
./bin/MakeDisp $filename $date $month $run $entry