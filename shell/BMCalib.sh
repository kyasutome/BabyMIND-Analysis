#!/bin/sh

if [ $# -ne 3 ] ; then
  echo ""
  echo "  !!! ./BMCalib.sh [date] [month] [run] !!!"
  echo "example)"
  echo "./BMCalib.sh 5 Dec 2"
  exit 1
fi

date=$1
month=$2
run=$3

anadir=${PWD}
datadir=$anadir/../../data/physdata/$date$month

filename=$(find  $datadir -type f -name "*Run$run*all*")
if [ $? -eq 0 ] ; then
    echo "Found a file"
    else
    exit 0
fi

echo "Filename="$filename
echo "Analyze the file..."

cd $anadir
./bin/BMCalib $filename $date $month $run