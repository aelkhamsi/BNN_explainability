#!/bin/bash

make
printf "digraph{\n" > obdd.gv
./main
dot -Tpng obdd.gv -o test.png
make clean
