#!/bin/sh

if [ $# -ne 3 ] ; then
  echo ""
  echo "  !!! ./PMCalib.sh [pmrun] [pmstartsub] [pmendsub] !!!"
  echo "example)"
  echo "./PMCalib.sh 32321 3 5"
  exit 1
fi

pmrun=$1
pmssub=$2
pmesub=$3

anadir=${PWD}
datadir=$anadir/process

echo "Analyze the file..."

cd $anadir
./bin/PMCalib $pmrun $pmssub $pmesub