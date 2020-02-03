#!/bin/sh

if [ $# -ne 1 ] ; then
  echo ""
  echo "  !!! ./MakeWGWMClass.sh [filepath] !!!"
  echo "example)"
  echo "./MakeWGWMClass.sh [filepath]"
  exit 1
fi

filepath=$1

anadir=${PWD}
datadir=$anadir/process

echo "Analyze the file..."

cd $anadir
./bin/MakeWGWMClass $filepath