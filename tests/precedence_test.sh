#!/bin/bash
echo "testing precedence_tests commands "
zeo="([ -e main.cpp ] || echo a ) && echo b"
fir="echo begin && ([ -e main.cpp ] && echo passed)"
sec="echo begin || ([ -e main.cpp ] && echo passed)"
thi="([ -e main.cpp ] && echo passed) || echo end"
fou="([ main.cc ] || echo begin/skip ) && echo end "
fif="echo begin && ( [ -e main.cpp ] && echo passed && [ -e main ] || (echo it && echo successfully) && echo wow)"
six="echo begin || ( [ -e main.cpp ] && echo passed && [ -e main ] || (echo it && echo successfully) && echo wow)"
sev="echo begin || ( test main.cpp && echo passed) "
eig="echo start || test main.cpp && (test main.cpp && echo end)"
nin="echo testing test -e main.cpp  && (test -e main.cpp && test And.h); echo pass"
ten="( test /home || test adsfasdf) && (test asdfadfs || test /home)"
ele="[ main.cpp ] || ( [ /home ] || echo should not be outputed)"
twl="echo nothing || (  ([ main.cpp ] || echo a ) && echo pass )"
thr="echo double || (  ([ main.cpp ] || echo a ) && echo pass )"
frt="test LICENSE && (echo pass || echo failed)"
fit="test LICENSE || (echo pass || echo failed)"
sit="([ main.cpp ] && echo pass) || echo failed && ( echo 2 || [ /home ] ); echo end"
set="echo next ;(test main.cpp && echo pass)"
eit="echo 18 ; (test main.cpp || echo idk)"
nit="([ -d LICENSE ] || test -f LICENSE) || echo end"
a="(echo what now && (( [ main.cpp ] || test -e main.cpp || test -e main.cpp)  && echo next && test /home )"
b="(echo what now || (( [ main.cpp ] || test || test)  && echo next && test /home )"
c="(echo what now && (( [ main.cpp ] || test || test)  || echo next && test /home )"
d="(echo what now && (( [ main.cpp ] || test || test)  || echo next ||test /home )"
e="(echo what now && (( [ main.cpp ] || test || test)  && echo next || test /home )"

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