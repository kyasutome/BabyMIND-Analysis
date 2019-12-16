#!/bin/sh

if [ $# -ne 3 ] ; then
  echo ""
  echo "  !!! ./MakePMClass.sh [pmrun] [pmstartsub] [pmendsub] !!!"
  echo "example)"
  echo "./MakeEvt.sh 32321 3 5"
  exit 1
fi

pmrun=$1
pmssub=$2
pmesub=$3

anadir=${PWD}
datadir=$anadir/process

echo "Analyze the file..."

cd $anadir
./bin/MakePMClass $pmrun $pmssub $pmesub