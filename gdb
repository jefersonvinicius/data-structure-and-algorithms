#!/bin/bash

# Reference: https://u.osu.edu/cstutorials/2018/09/28/how-to-debug-c-program-using-gdb-in-6-simple-steps/

set -e # exit on any error happens
gcc -I$(pwd) -D TESTING -o $(pwd)/exec -g $1
gdb exec