#!/bin/bash
i=1
z="out"
for filename in input/*.txt; do 
    for j in {1..20}; do
        touch "output"/$z$i/$z$j
        ./sa $(cat $filename) > "output"/$z$i/$z$j
    done
    ((i++))
done