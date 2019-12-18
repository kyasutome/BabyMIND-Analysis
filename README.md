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

You successfully compile libraries.

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

2. BSDApply

Read T2K offcial BSD
Implement beam information such as "unixtime", "P.O.T" into BMBSD class
Get files in process/3-BMBSD

3. EvtDisp

3-1. PMClass

Read data taken by Proton Modules
Fill parameters into PMRecon class
Get files in process/2-PMClass

3-2. MakeEvt

Create the format for makeing Event Display
Get files in process/4-BMEVT

3-3. MakeDisp

Create the Event Display

Event Display (This is the very immature version. Will be updated more.)
1. Color dots means Each Bunch.
2. Currently using the spill matching between Baby MIND & Proton Module

4. DataSanity

Create the data taking efficiency plot using "BMBSD*.root"
which is a output of program 2 "BSDApply".

## Shell control

Each shell script was created in order to run each program,
which you can find in the directory of "shell".

Brief usage is written in the code itself.


## Instruction for Classes

1. BMBasicRecon
<mod> Module ID (same as simulation)
0: Proton Module
1: upstream WAGASCI 
2: downstream WAGASCI
3: North Wall MRD
4: South Wall MRD
5: Baby MIND
6: YASU tracker


<Layout>

             -------------        -------------------    
              Wall MRD (4)
              -------------          
------   -------  -------            Baby MIND(5)
 WG(1)    PM(0)    WG(2)
------   -------  -------        
                                  --------------------
           -------------         
           Wall MRD (3)
           ------------- 


<view> For Y channel (side view) (0), For channel X (top view) (1)
<pln> Scintillator plane ID
<channel> MPPC channel ID
<HG> High Gain
<LG> Low Gain
<Ltime> Leading Time in each waveform
<Ftime> Falling Time in each waveform
<Htime> Hit Time from Spill
<timedif> Ltime - Ftime
<bunch> T2K beam bunch nomber (1~8), -1 for outside bunch timing
<bm_event> entries

2. BMBeaminfo

<spillnum> spillnumber obtained by GDCC

3. BMDisp
"unixtime" obtained by Proton Modules (not by BSD infromation!!!) was added newly.


  


