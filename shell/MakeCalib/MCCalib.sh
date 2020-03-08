#!/bin/sh

if [ $# -ne 1 ] ; then
  echo ""
  echo "  !!! ./MCCalib.sh [filepath][runnumber] !!!"
  echo "example)"
  echo "./MCCalib.sh [filepath][runnumber]"
  exit 1
fi

anadir=${PWD}
datadir="/Users/kenji/Dropbox/wagasci/MC/data"
runnumber=$1
#filepath="/Users/kenji/Dropbox/wagasci/wagasci/physdata/beam/run${runnumber}"

filename=$(find  $datadir -type f -name "*run${runnumber}_mc.root")
if [ $? -eq 0 ] ; then
    echo "Found a file"
    else
    exit 0
fi

echo "Filename="$filename
echo "Analyze the file..."
#filepath="/Volumes/HDPH-UT/NewG/Run10/wagasci/run${runnumber}"



cd $anadir
./bin/MCCalib $filename $runnumber