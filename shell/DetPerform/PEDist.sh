#!/bin/sh

if [ $# -ne 0 ] ; then
  echo ""
  echo "  !!! ./PEDist.sh!!!"
  echo "example)"
  echo "./DetectEff.sh"
  exit 1
fi

run=$1

anadir=${PWD}
datadir=$anadir/process/1-BMCalib

echo "Filename="$filename
echo "Analyze the file..."

cd $anadir
./bin/pedist $datadir