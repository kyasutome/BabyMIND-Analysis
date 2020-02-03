#!/bin/sh

if [ $# -ne 1 ] ; then
  echo ""
  echo "  !!! ./MakeWMClass.sh [filepath] !!!"
  echo "example)"
  echo "./MakeWMClass.sh [filepath]"
  exit 1
fi

filepath=$1

anadir=${PWD}
datadir=$anadir/process

echo "Analyze the file..."

cd $anadir
./bin/MakeWMClass $filepath