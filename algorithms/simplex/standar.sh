#!/bin/bash
FILE=standar.out
if test ! -f "$FILE"; then
    gcc standar.c -o standar.out
fi
(./standar.out < system.txt) > standar.txt 