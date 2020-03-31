#!/bin/sh

if [ $# -ne 1 ] ; then
  echo ""
  echo "  !!! ./MakeMCEvent.sh [run] !!!"
  echo "example)"
  echo "./MakeMCEvent.sh 92"
  exit 1
fi

vertex=$1
run=$2

#anadir=${PWD}
datadir=$anadir/process/1-MCCalib

#filename=$(find  $datadir -type f -name "*MCCalib_$run*")
#if [ $? -eq 0 ] ; then
#    echo "Found a file"
#    else
#    exit 0
#fi
#echo "Filename="$filename
#echo "Analyze the file..."

cd $anadir
./bin/MakeMCEvent $datadir $vertex $run