#!/bin/bash
FILE=gen_mtrx.out
if test ! -f "$FILE"; then
    gcc generate_matrix.c -o gen_mtrx.out
fi
#recibe n variables, m restricciones y o = 0 para minimizar, 1 para maximizar
if [ $# -eq 3 ]; then
    n=$1
    m=$2
    o=$3
    (echo "$m $n $o" && ./gen_mtrx.out $m $n 0 10 && ./gen_mtrx.out $m 1 0 10 && ./gen_mtrx.out 1 $n 0 10 && ./gen_mtrx.out $m 1 0 3) > system.txt
fi


