#!/bin/sh

if [ $# -ne 5 ] ; then
  echo ""
  echo "  !!! ./DetRecon.sh [wgrun][ientry][targetmod][mon][date] !!!"
  echo "example)"
  echo "./DetRecon.sh 92 1 1 Jan 1"
  exit 1
fi

run=$1
ientry=$2
targetmod=$3
mon=$4
date=$5

#anadir=${PWD}
#datadir=$anadir/process/3-EVT
datadir=$anadir/process/3-MCEVT

filename=$(find  $datadir -type f -name "Evt_${run}.root")
if [ $? -eq 0 ] ; then
    echo "Found a file"
    else
    exit 0
fi

echo "Filename="$filename
echo "Analyze the file..."

cd $anadir

for MON in "1"
do 
    #for DATE in "1" "2" "3" "4" "5" "6" "7"
    #for DATE in "25" "26" "27" "28" "29" "30" "31"
    for DATE in "25"
    do
    ./bin/DetRecon $filename $run $ientry $targetmod $MON $DATE
    done
done