# BabyMIND-Analysis

Analysis software for the WAGASCI/BabyMIND experiment.
Currently focused on analysis for Baby MIND.

## 1.Dependencies

Most codes require some classes in libraries.
"lib" directory includes those kinds of libraries.
If you see the Makefile, then you will find how to compile them.

go to lib/src

1. make BMBasicRecon -> create ../library/BMBasicRecon.so 
2. make BMBeaminfo   -> create ../libraty/BMBeaminfo.so
3. make BMDisp       -> create ../library/BMDisp.so
4. make PMRecon      -> create ../library/PMRecon.so
5. make BMBSD        -> create ../library/BMBSD.so
6. make move         -> move *Dict_rdict_pcm files ../library/

You sucessfully compile libraries.

## 2.Installation --- General ---

cd build
cmake_clean.sh
cmake .. 
make

## 3.Brief illustration of codes.

1. MakeCalib

Read decorded file (*all.root).
Check coincidence between  horizontal bars & vertical bars.
Fill parameters such as "plane", "channel", "view"  into the BasicRecon class 
Fill spillnumber into the Beaminfo class
Get files in process/1-BMCalib

2. PMClass

Read data taken by Proton Modules
Fill parameters into PMRecon class
Get files in process/2-PMClass

3. BSDApply

Read T2K offcial BSD
Implement beam information such as "unixtime", "P.O.T" into BMBSD class
Get files in process/3-BMBSD

4. EvtDisp

4-1. MakeEvt

Create the format for makeing Event Display
Get files in process/4-BMEVT

4-2. MakeDisp

Create the Event Display

## Shell control

Each shell script was created in order to run each program,
which you can find in the directory of "shell".

Brief usage is written in the code itself.





