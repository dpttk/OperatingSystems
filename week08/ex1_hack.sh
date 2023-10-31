#!/bin/bash

PID=$(cat /tmp/ex1.pid)

password=$(sudo xxd -c 40 -p /proc/$PID/mem | grep -o 'pass:........')

echo "$password"
echo "0x$(grep -o 'pass:........' <<< $(sudo xxd -c 40 -p /proc/$PID/maps))"
sudo kill -9 $PID 
