#!/bin/sh

if [ $# -ne 0 ] ; then
  echo ""
  echo "  !!! ./BMDataSanity.sh !!!"
  echo "example)"
  echo "./BMDataSanity.sh"
  exit 1
fi

srun=$1
erun=$2

dirpath=./process

anadir=${PWD}
datadir=$anadir/process

echo "Analyze the file..."

cd $anadir
./bin/BMDataSanity