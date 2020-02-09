#!/bin/sh

if [ $# -ne 0 ] ; then
  echo ""
  echo "  !!! ./DataSanity.sh !!!"
  echo "example)"
  echo "./DataSanity.sh"
  exit 1
fi

dirpath=./process

anadir=${PWD}
datadir=$anadir/process

echo "Analyze the file..."

cd $anadir
./bin/DataSanity