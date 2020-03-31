#!/bin/sh

if [ $# -ne 0 ] ; then
  echo ""
  echo "  !!! ./BasicDisp.sh [filepath] !!!"
  echo "example)"
  echo "./BasicDisp.sh [filepath]"
  exit 1
fi

#anadir=${PWD}
datadir=$anadir/process/6-YASU

filename=$(find  $datadir -type f -name "*BMCalib*")
if [ $? -eq 0 ] ; then
    echo "Found a file"
    else
    exit 0
fi

echo "Filename="$filename
echo "Analyze the file..."

cd $anadir
./bin/BasicDist $datadir