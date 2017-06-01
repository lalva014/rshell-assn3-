#!/bin/bash

echo "testing commented commands "
zeo="ls # list all files "
fir="# [ test -e main.cpp]"
sec="###[ -e main.cpp]"
thi="##[ ]"
fou="[ -e main.cpp] ## comment #1"
fif="######################## Test -e main.cpp"
six="# [ main.cpp"
sev="# -e main.cpp ]" 
eig="[ -e main.cpp ] # ] # [ "
nin="testc main.cpp ######"
a="[ main.cpp ] ##good job"



    echo $zeo
    eval $zeo 
    echo $?
    
    echo $fir
    eval $fir
    echo $?
    
    echo $sec
    eval $sec
    echo $?
    
    echo $thi
    eval $thi
    echo $?
    
    echo $fou
    eval $fou
    echo $?
    
    echo $fif
    eval $fif
    echo $?
    
    echo $fif
    eval $fif
    echo $?
    
    echo $six
    eval $six
    echo $?
    
    echo $sev
    eval $sev
    
    echo $eig
    eval $eig
    
    echo $nin
    eval $nin
    
    echo $a
    eval $a
    