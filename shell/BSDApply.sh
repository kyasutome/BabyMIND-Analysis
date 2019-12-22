#!/bin/sh

if [ $# -ne 6 ] ; then
  echo ""
  echo "  !!! ./BSDApply.sh [date] [month] [run] [bmmon] [bmdate] [bmhour] !!!"
  echo "example)"
  echo "./BSDApply.sh 5 Dec 2 5 12 22"
  exit 1
fi

date=$1
month=$2
run=$3
bmmon=$4
bmdate=$5
bmhour=$6

anadir=${PWD}
datadir=$anadir/process

#filename=$(find  $datadir -type f -name "*BMCalib*$date$month*$run*")
filename=$(find  $datadir -type f -name "*BMCalib_$date$month*$run*")
if [ $? -eq 0 ] ; then
    echo "Found a file"
    else
    exit 0
fi

echo "Filename="$filename
echo "Analyze the file..."

cd $anadir
./bin/BSDApply $filename $date $month $run $bmmon $bmdate $bmhour