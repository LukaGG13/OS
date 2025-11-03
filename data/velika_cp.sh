#/!bin/bash

TIMEFORMAT=%R
for i in {1..10}
do
     { time cp velika.bin velika.bin.copy; } 2>&1 | sed 's/,/./g'
done
