#!/bin/bash

./run

File1=Res2.png 
File2=data/fcm.bin
validated=false 

if test -f "$File1"; then  
    cp Res2.png /home/dreamvu/data5/lut/
    cp Res2.png ../data5/lut/       
    rm Res2.png data.zip
    validated=true
fi

if test -f "$File2"; then         
    cp -r data/fcm.bin ../data5/fusion/
    cp -r data/fcm.bin /home/dreamvu/data5/fusion/
fi

if $validated; then     
    rm -rf data	   
    echo "[PAL:INFO] Camera data files are installed successfully." 
fi
 


