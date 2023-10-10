#!/bin/bash

gcc ex3.c -o ex3 -pthread


echo "before 1"
date +%T
./ex3 10000000 1
echo " "
echo "before 2"
date +%T
./ex3 10000000 2
echo " "
echo "before 4 "
date +%T
./ex3 10000000 4
echo " "
echo "before 10 "
date +%T
./ex3 10000000 10
echo " "
echo "before 100 "
date +%T
./ex3 10000000 100
echo " "
echo "after 100"
date +%T


rm ex3

