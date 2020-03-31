#!/bin/sh

if [ $# -ne 1 ] ; then
  echo ""
  echo "  !!! ./FindnuVertex.sh [run]!!!"
  echo "example)"
  echo "./FindnuVertex.sh 4"
  exit 1
fi

run=$1

#anadir=${PWD}
#datadir=$anadir/process/TEST
datadir=$anadir/process/4-Recon

filename=$(find  $datadir -type f -name "Recon_${run}.root")
if [ $? -eq 0 ] ; then
    echo "Found a file"
    else
    exit 0
fi

echo "Filename="$filename
echo "Analyze the file..."

cd $anadir
./bin/find_nuvertex $filename $run