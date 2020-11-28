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
if [[ "$2" == "clear_cache=yes" ]]
then
    sed -i '/#define CLEAR_CACHE 0/c\#define CLEAR_CACHE 1' src/benchmark.c
else
    sed -i '/#define CLEAR_CACHE 1/c\#define CLEAR_CACHE 0' src/benchmark.c
fi

make

dim_actual=1
for filename in `ls $3/*.txt | sort -V`; do
    /opt/valgrind/bin/valgrind --tool=cachegrind bin/benchmark > /dev/null < $filename
    echo -n $dim_actual" " >> $4
    echo -n $2" " >> $4
    echo -n $1" " >> $4
    /opt/valgrind/bin/cg_annotate cachegrind.out.* /root/tp2/asm/mmult.* | tail -n2 | head -n1 >> $4  
    rm cachegrind.out.*
    ((dim_actual=dim_actual+1))
done
