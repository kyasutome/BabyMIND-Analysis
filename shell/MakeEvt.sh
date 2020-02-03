#!/bin/sh

if [ $# -ne 7 ] ; then
  echo ""
  echo "  !!! ./MakeEvt.sh [date] [month] [run] [subrun] [pmrun] [pmstartsub] [pmendsub] !!!"
  echo "example)"
  echo "./MakeEvt.sh 5 Dec 2 0 32321 3 5"
  exit 1
fi

date=$1
month=$2
run=$3
subrun=$4
pmrun=$5
pmssub=$6
pmesub=$7

anadir=${PWD}
datadir=$anadir/process/6-YASU/

filename=$(find  $datadir -type f -name "*BMCalib*$date$month*$run-$subrun*")
if [ $? -eq 0 ] ; then
    echo "Found a file"
    else
    exit 0
fi

echo "Filename="$filename
echo "Analyze the file..."

cd $anadir
./bin/MakeEvt $filename $date $month $run $subrun $pmrun $pmssub $pmesub