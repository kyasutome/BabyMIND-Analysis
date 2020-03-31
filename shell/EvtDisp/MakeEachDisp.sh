#!/bin/sh

if [ $# -ne 2 ] ; then
  echo ""
  echo "  !!! ./MakeEachDisp.sh [filepath][targetentry] !!!"
  echo "example)"
  echo "./MakeEachDisp.sh [filepath][targetentry]"
  exit 1
fi

filepath=$1
targetentry=$2

#anadir=${PWD}
datadir=$anadir/process

echo "Analyze the file..."

cd $anadir
./bin/MakeEachDisp $filepath $targetentry