#!/bin/sh

if [ $# -ne 2 ] ; then
  echo ""
  echo "  !!! ./MCCalib.sh [filepath][runnumber] !!!"
  echo "example)"
  echo "./MCCalib.sh [filepath][runnumber]"
  exit 1
fi

#anadir=${PWD}
datadir="/Users/kenji/Dropbox/wagasci/MC/outputroot"

#filepath="/Users/kenji/Dropbox/wagasci/wagasci/physdata/beam/run${runnumber}"

#filename=$(find  $datadir -type f -name "*raw_run${runnumber}_mc.root")
#filename=$(find  $datadir -type f -name "*numubar_run${runnumber}_mc.root")
#if [ $? -eq 0 ] ; then
#    echo "Found a file"
#    else
#    exit 0
#fi

#echo "Filename="$filename
#echo "Analyze the file..."
#filepath="/Volumes/HDPH-UT/NewG/Run10/wagasci/run${runnumber}"

runnumber=$1
#N=$2

cd $anadir
for i in `seq 1 $N`
do
filename="${datadir}/newg_calib_run${i}_mc.root"
./bin/MCCalib $filename $i
done