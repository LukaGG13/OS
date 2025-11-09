#/!bin/bash

TIMEFORMAT=%R
for j in 1 512 1024
do
    echo "Current value is $j"
    for i in {1..10}
    do
     { time ../cfiles/main velika.bin velika.bin.copy $j; } 2>&1 | sed 's/,/./g'
    done
done
