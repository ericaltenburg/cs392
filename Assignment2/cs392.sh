#!/bin/sh

make -f Makefile

gcc -O0 -o cs392_ass2 main.c libcs392_io.so

export LD_LIBRARY_PATH=$PWD
./cs392_ass2

