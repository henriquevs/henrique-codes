#!/bin/sh

gcc -std=c99 -pedantic -Wall -lm -o lista lista.c

for arquivo in 1 2 3 4 5 6; do
echo "Testando entrada $arquivo"
./lista < arq$arquivo.in > arq$arquivo.out
diff arq$arquivo.out arq$arquivo.res
done