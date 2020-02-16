#!/bin/sh

if [ $# -ne 1 ] ; then
  echo ""
  echo "  !!! ./WGCalib.sh [filepath][runnumber] !!!"
  echo "example)"
  echo "./WGCalib.sh [filepath][runnumber]"
  exit 1
fi

runnumber=$1
#filepath="/Users/kenji/Dropbox/wagasci/wagasci/physdata/beam/run${runnumber}"
filepath="/Volumes/HDPH-UT/NewG/Run10/wagasci/run${runnumber}"

anadir=${PWD}
datadir=$anadir/process

echo "Analyze the file..."

cd $anadir
./bin/WGCalib $filepath $runnumber