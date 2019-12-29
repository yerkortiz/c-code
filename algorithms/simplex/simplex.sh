#!/bin/bash
FILE=simplex.out
if test ! -f "$FILE"; then
    gcc simplex.c -o simplex.out
fi
./simplex.out <system.txt