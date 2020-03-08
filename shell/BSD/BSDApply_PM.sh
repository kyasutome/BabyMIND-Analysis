#!/bin/sh

if [ $# -ne 3 ] ; then
  echo ""
  echo "  !!! ./BSDApply_PM.sh [run] [ssub] [esub] !!!"
  echo "example)"
  echo "./BSDApply_PM.sh 32462 20 34"
  exit 1
fi

run=$1
ssub=$2
esub=$3

anadir=${PWD}
datadir=$anadir/process

filename=$(find  $datadir -type f -name "PMCalib_*$run*_*$ssub*_$esub*")
if [ $? -eq 0 ] ; then
    echo "Found a file"
    else
    exit 0
fi

echo "Filename="$filename
echo "Analyze the file..."

cd $anadir
./bin/BSDApply_PM $filename $run $ssub $esub