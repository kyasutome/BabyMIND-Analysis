#!/bin/sh

if [ $# -ne 2 ] ; then
  echo ""
  echo "  !!! ./ChargeEff.sh [run][entry]!!!"
  echo "example)"
  echo "./ChargeEff.sh 4 2"
  exit 1
fi

run=$1
entry=$2

#anadir=${PWD}
#datadir=$anadir/process/TEST
#datadir=$anadir/process/3-EVT
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
./bin/charge_eff $filename $run $entry