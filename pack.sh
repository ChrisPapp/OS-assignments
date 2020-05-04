#!/bin/bash

DIRNAME='final'
FILENAME='t8170011-t8170105-pizza1'
SHNAME='test-res1'

mkdir -p $DIRNAME
rm -rf $DIRNAME/*
touch $DIRNAME/$FILENAME.c
touch $DIRNAME/$FILENAME.h
touch $DIRNAME/$SHNAME.sh
echo "gcc $FILENAME.c -pthread -o assignment
./assignment 100 1000 1
" >> $DIRNAME/$SHNAME.sh
echo "#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <pthread.h>" >> $DIRNAME/$FILENAME.h
echo "#include <pthread.h>" >> $DIRNAME/$FILENAME.h
echo "#include \"${FILENAME}.h\"" >> $DIRNAME/$FILENAME.c
awk 'FNR==1 {print "// Contents of:", FILENAME} (index($1, "#include") == 0){print}' src/*.h >> $DIRNAME/$FILENAME.h
awk 'FNR==1 {print "// Contents of:", FILENAME} (index($1, "#include") == 0){print}' src/*.c >> $DIRNAME/$FILENAME.c
