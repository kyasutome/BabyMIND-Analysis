#!/bin/sh

if [ $# -ne 1 ] ; then
  echo ""
  echo "  !!! ./WMDataQuality.sh [filepath] !!!"
  echo "example)"
  echo "./WMDataQuality.sh [filepath]"
  exit 1
fi

filepath=$1

anadir=${PWD}
datadir=$anadir/process

echo "Analyze the file..."

cd $anadir
./bin/WMDataQuality $filepath