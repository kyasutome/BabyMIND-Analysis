#!/bin/sh

if [ $# -ne 1 ] ; then
  echo ""
  echo "  !!! ./WGCalib.sh [filepath][runnumber] !!!"
  echo "example)"
  echo "./WGCalib.sh [filepath][runnumber]"
  exit 1
fi

runnumber=$1
#anadir=${PWD}

#datadir="/Users/kenji/Dropbox/wagasci/wagasci/physdata/beam"
#filename=$(find  $datadir -type f -name "*_${runnumber}_ecal_dif_0_tree.root")
#if [ $? -eq 0 ] ; then
#    echo "Found a file"
#    else
#    exit 0
#fi

echo "Filename="$filename
echo "Analyze the file..."

#filepath="/Users/kenji/Dropbox/wagasci/wagasci/physdata/beam/run${runnumber}"
filepath="/Volumes/HDPH-UT/NewG/Run10/wagasci/run${runnumber}"
#filepath="/Volumes/BabyMIND12/WAGASCI/data_quality/run${runnumber}"

cd $anadir
./bin/WGCalib $filepath $runnumber