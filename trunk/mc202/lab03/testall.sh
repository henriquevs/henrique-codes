#!/bin/sh

gcc -std=c99 -pedantic -Wall -lm -o principal *.c

for arquivo in 1 2 3; do
echo "Testando entrada $arquivo"
./principal < arq$arquivo.in > arq$arquivo.out
diff arq$arquivo.out arq$arquivo.res
done

