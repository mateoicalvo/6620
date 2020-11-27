#!/bin/bash

mkdir -p obj
mkdir -p asm
if [[ "$1" == *.c ]]
then
    gcc -g -S $1 -o asm/mmult.s;
    sed -i '/.file 1/,+1d' asm/mmult.s
else #assembler
    cp $1 asm/mmult.S
fi
gcc -g -c asm/mmult.* -o obj/mmult.o
if [[ "$2" == "yes" ]]
then
    sed -i '/#define CLEAR_CACHE 0/c\#define CLEAR_CACHE 1' src/benchmark.c
else
    sed -i '/#define CLEAR_CACHE 1/c\#define CLEAR_CACHE 0' src/benchmark.c
fi
make

for filename in $3/*.txt; do
    /opt/valgrind/bin/valgrind --tool=cachegrind bin/benchmark > /dev/null < $filename
    /opt/valgrind/bin/cg_annotate cachegrind.out.* /root/tp2/asm/mmult.*
    rm cachegrind.out.*
done

#/opt/valgrind/bin/cg_annotate cachegrind.out.2050 root/tp2/asm/mmult.* asterisk y despues rm