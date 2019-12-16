#!/bin/sh

if [ $# -ne 6 ] ; then
  echo ""
  echo "  !!! ./MakeEvt.sh [date] [month] [run] [pmrun] [pmstartsub] [pmendsub] !!!"
  echo "example)"
  echo "./MakeEvt.sh 5 Dec 2 32321 3 5"
  exit 1
fi

date=$1
month=$2
run=$3
pmrun=$4
pmssub=$5
pmesub=$6

anadir=${PWD}
datadir=$anadir/process

filename=$(find  $datadir -type f -name "*BMCalib*$date$month*$run*")
if [ $? -eq 0 ] ; then
    echo "Found a file"
    else
    exit 0
fi

echo "Filename="$filename
echo "Analyze the file..."

cd $anadir
./bin/MakeEvt $filename $date $month $run $pmrun $pmssub $pmesub