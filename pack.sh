#!/bin/bash

DIRNAME='final'
FILENAME='t8170011-t8170105-pizza2'
SHNAME='test-res2'

mkdir -p ./$DIRNAME
rm -rf ./$DIRNAME/*
touch ./$DIRNAME/$FILENAME.c
touch ./$DIRNAME/$FILENAME.h
touch ./$DIRNAME/$SHNAME.sh

echo "gcc $FILENAME.c -pthread -o assignment
./assignment 100 1000 1
" >> $DIRNAME/$SHNAME.sh
echo "#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>
#ifdef _WIN32
  #include <windows.h>
#else
  #include <unistd.h>
#endif
" >> $DIRNAME/$FILENAME.h
echo "#include \"${FILENAME}.h\"" >> $DIRNAME/$FILENAME.c

chmod 744 ./$DIRNAME/$SHNAME.sh

awk 'FNR==1 {print "\n/* Contents of:", FILENAME, "*/"} (index($1, "#include") == 0) {print}' \
./src/utils.h \
./src/theme.h \
./src/resource.h \
./src/producer.h >> $DIRNAME/$FILENAME.h

awk 'FNR==1 {print "\n/*Contents of:", FILENAME, "*/"} (index($1, "#include") == 0) {print}' \
./src/pizza1.c \
./src/producer.c \
./src/resource.c \
./src/utils.c \
./src/pizza_theme.c \
./src/corona_theme.c >> $DIRNAME/$FILENAME.c

