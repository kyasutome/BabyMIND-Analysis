#!/bin/sh

if [ $# -ne 4 ] ; then
  echo ""
  echo "  !!! ./BSDApply_WGnocut.sh [run] [date] [mon] [hour] !!!"
  echo "example)"
  echo "./BSDApply_WGnocut.sh 92 1 10 13"
  exit 1
fi

run=$1
date=$2
mon=$3
hour=$4

anadir=${PWD}
datadir=$anadir/process/0-WGnocut

#filename=$(find  $datadir -type f -name "*WGCalib_$run*$ssub*$esub*")
#if [ $? -eq 0 ] ; then
#    echo "Found a file"
#    else
#    exit 0
#fi

#echo "Filename="$filename
#echo "Analyze the file..."

cd $anadir
./bin/BSDApply_WGnocut $datadir $run $date $mon $hour