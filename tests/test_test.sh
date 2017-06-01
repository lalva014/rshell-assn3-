#!/bin/bash
echo "testing tests commands "
zeo="[ -e main.cpp ]"
fir="[ -f main.cpp ]"
sec="[ -e bin/rshell ]" 
thi="[ -f bin/rshell ]"
fou="[ -d rshell/bin ]"
fif="[ rshell ]"
six="[ -e bin/ex.sh ]"
sev="[ -f bin/ex.sh ]" 
eig="[ -d tests ]"
nin="[ bin/ex.sh ]"
ten="[ -f LICENSE ]"
ele="[ LICENSE ]"
twl="[ Base.h ]"
thr="[ -d bin ]"
frt="test LICENSE"
fit="test main.cpp"
sit="test -d bin"
set="test -d rshell"
eit="test -e /home"
nit="test bin/rshell"
a="test -f LICENSE"
b="test -d tests "
c="test -e tests"
d="test"
e="test -d bin "

# 0= true
# 1=false


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
    
    echo $six
    eval $six
    echo $?
    
    echo $sev
    eval $sev
    echo $?
    
    echo $eig
    eval $eig
    echo $?
    
    echo $nin
    eval $nin
    echo $?
    
    echo $ten
    eval $ten
    echo $?
    
    echo $ele
    eval $twl
    echo $?
    
    echo $thr
    eval $thr
    echo $?
    
    echo $frt
    eval $frt
    echo $?
    
    echo $sit
    eval $sit
    echo $?
    
    echo $set
    eval $set
    echo $?
    
    echo $eit
    eval $eit
    echo $?
    
    echo $nit
    eval $nit
    echo $?
    
    echo $a
    eval $a
    echo $?
    
    echo $b
    eval $b
    echo $?
    
    echo $c
    eval $c
    echo $?
    
    echo $d
    eval $d
    echo $?
    
    echo $e
    eval $e
    echo $?