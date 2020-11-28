#!/bin/bash

RUTA_FUNCION=$1
CLEAR_CACHE=$2
RUTA_INPUTS=$3
RUTA_LOGS=$4
ARCHIVO_LOG_RESULTADOS=$4/log.txt
FLAGS_CACHEGRIND_I=$5
FLAGS_CACHEGRIND_D=$6
mkdir -p obj
mkdir -p asm
mkdir -p $RUTA_LOGS

if [[ "$RUTA_FUNCION" == *.c ]]
then
    gcc -g -S $RUTA_FUNCION -o asm/mmult.s;
    sed -i '/.file 1/,+1d' asm/mmult.s
else #assembler
    cp $RUTA_FUNCION asm/mmult.S
fi

REAL_PATH=$(realpath asm/mmult.*)

gcc -g -c asm/mmult.* -o obj/mmult.o
if [[ "$CLEAR_CACHE" == "clear_cache=yes" ]]
then
    sed -i '/#define CLEAR_CACHE 0/c\#define CLEAR_CACHE 1' src/benchmark.c
else
    sed -i '/#define CLEAR_CACHE 1/c\#define CLEAR_CACHE 0' src/benchmark.c
fi

make

iteracion=1
for filename in `ls $RUTA_INPUTS/*.txt | sort -V`; do
    /opt/valgrind/bin/valgrind --tool=cachegrind $FLAGS_CACHEGRIND_I $FLAGS_CACHEGRIND_D bin/benchmark > /dev/null < $filename
    echo -n $iteracion" " >> $ARCHIVO_LOG_RESULTADOS
    echo -n $filename" " >> $ARCHIVO_LOG_RESULTADOS
    echo -n $CLEAR_CACHE" " >> $ARCHIVO_LOG_RESULTADOS
    echo -n $RUTA_FUNCION" " >> $ARCHIVO_LOG_RESULTADOS
    echo -n $FLAGS_CACHEGRIND_I $FLAGS_CACHEGRIND_D" " >> $ARCHIVO_LOG_RESULTADOS
    /opt/valgrind/bin/cg_annotate cachegrind.out.* $REAL_PATH | tail -n2 | head -n1 >> $ARCHIVO_LOG_RESULTADOS 
    #dim1_chachegrid_log.tst
    rm cachegrind.out.*
    ((iteracion=iteracion+1))
done
