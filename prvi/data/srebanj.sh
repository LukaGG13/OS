#/!bin/bash

TIMEFORMAT=%R
for i in {1..10}
do
     { time cp srednja.bin srednja.bin.copy; } 2>&1 | sed 's/,/./g'
done
