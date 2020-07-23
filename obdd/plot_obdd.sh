#!/bin/bash

make
printf "digraph{\nforcelabels=true;\n" > obdd.gv
./main
dot -Tpng obdd.gv -o obdd.png
make clean
