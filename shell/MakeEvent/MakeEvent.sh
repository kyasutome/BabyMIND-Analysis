#!/bin/sh

if [ $# -ne 1 ] ; then
  echo ""
  echo "  !!! ./MakeEvent.sh [wgrun] !!!"
  echo "example)"
  echo "./MakeEventt.sh 92"
  exit 1
fi

wgrun=$1

anadir=${PWD}
datadir=$anadir/process/2-BMBSD

#filename=$(find  $datadir -type f -name "*BMCalib*$date$month*$run-$subrun*")
#if [ $? -eq 0 ] ; then
#    echo "Found a file"
#    else
#    exit 0
#fi
#echo "Filename="$filename
#echo "Analyze the file..."

cd $anadir
./bin/MakeEvent $datadir $wgrun