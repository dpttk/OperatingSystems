#!/bin/bash

PID=$(cat /tmp/ex1.pid)

password=$(sudo xxd  -p /proc/$PID/mem | grep -o 'pass:...')

echo "$password"

sudo kill -9 $PID 
