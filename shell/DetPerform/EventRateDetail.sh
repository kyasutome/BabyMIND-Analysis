#!/bin/sh

if [ $# -ne 0 ] ; then
  echo ""
  echo "  !!! ./EventRateDetail.sh!!!"
  echo "example)"
  echo "./DetEventrate.sh"
  exit 1
fi

run=$1

#anadir=${PWD}
#datadir=$anadir/process/TEST
datadir=$anadir/process/3-EVT

#filename=$(find  $datadir -type f -name "Evt_${run}.root")
#if [ $? -eq 0 ] ; then
#    echo "Found a file"
#    else
#    exit 0
#fi

#echo "Filename="$filename
echo "Analyze the file..."

cd $anadir
./bin/eventrate_detail