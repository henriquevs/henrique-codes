#!/bin/sh

gcc -std=c99 -pedantic -Wall -lm -o lab03_ra105063 lab03_ra105063.c

for arquivo in 1 2 3; do
echo "Testando entrada $arquivo"
./lista < arq$arquivo.in > arq$arquivo.out
diff arq$arquivo.out arq$arquivo.res
done
