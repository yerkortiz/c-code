#!/bin/bash
echo "MOVIENDO WEAITAS EN " $target1 "HACIA" $target2
target1="/Users/yerko/codes/c-code/operating-systems/syscalls/fork"
target2="/Users/yerko/codes/c-code/operating-systems/syscalls"
for f in "$target1"/*
do
	mv $(basename $f) $target2
done
