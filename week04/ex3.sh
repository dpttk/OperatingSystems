#!/bin/bash

gcc ex3.c -o ex3

./ex3 3 &

pstree
sleep 1s
pstree
sleep 3s
pstree
sleep 5s
pstree




./ex3 5 &


pstree
sleep 1s
pstree
sleep 3s
pstree
sleep 5s
pstree
sleep 4s
pstree
sleep 4s
pstree




rm ex3
