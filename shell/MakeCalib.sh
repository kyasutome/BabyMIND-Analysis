#!/bin/sh

date=$1
month=$2
anadir="/Users/kenji/Dropbox/wagasci/babymind/software/analysis"
datadir="/Users/kenji/Dropbox/wagasci/babymind/data/physdata/$date$month"

echo "Finding a file in " $datadir
filename=$(find  $datadir -type f -name "*all*")
echo "Filename= "$filename
echo "Found a file!"
echo "Analyze a file..."

#cd $anadir
#./bin/MakeCalib $datadir/$filename