#!/bin/sh

if [ $# -ne 2 ] ; then
  echo ""
  echo "  !!! ./WGDataSanity.sh [start run][end run] !!!"
  echo "example)"
  echo "./WGDataSanity.sh 92 92"
  exit 1
fi

srun=$1
erun=$2

dirpath=./process

#anadir=${PWD}
datadir=$anadir/process

echo "Analyze the file..."

cd $anadir
./bin/WGDataSanity $srun $erun