#!/bin/sh

MAX=7
i=0
date=$1
mon="$2"
run=$3

unpacking="Unpacking_FW7" #latest version
#unpacking="Unpacking_JPARC_v1.35"

while [ $i -le $MAX ]; do

    if [ $i -eq 0 ]; then
	mcr="0"
    fi

    if [ $i -eq 1 ]; then
	mcr="1"
    fi

    if [ $i -eq 2 ]; then
	mcr="2"
    fi

    if [ $i -eq 3 ]; then
	mcr="3"
    fi

    if [ $i -eq 4 ]; then
	mcr="4"
    fi

    if [ $i -eq 5 ]; then
	mcr="5"
    fi

    if [ $i -eq 6 ]; then
	mcr="6"
    fi

    if [ $i -eq 7 ]; then
	mcr="7"
    fi

directory="$date$mon/mode1pw1bw35_HG50vh_HG30yb_DAC10b220y240v260h_Tin_26_9_Tout_24_2"
filename="beam_200us_MCR_"$mcr"_Run"$run"_2020_01_29_14_01_36.daq"

#beamdata
./$unpacking/bin/TDMunpack -f ~/Dropbox/wagasci/babymind/data/physdata/$directory/$filename  1>&2

    i=`expr $i + 1`
done

echo "start unpacking"

cd ./$unpacking/bin

#beamdata

ls -1 ../../../../../data/physdata/$directory/*Slot* > febs_files_list.list

./unpack -f 