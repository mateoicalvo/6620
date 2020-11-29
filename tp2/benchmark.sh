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
mkdir -p $RUTA_LOGS/raw

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

for filename in `ls $RUTA_INPUTS/*.txt | sort -V`; do
    /opt/valgrind/bin/valgrind --tool=cachegrind $FLAGS_CACHEGRIND_I $FLAGS_CACHEGRIND_D bin/benchmark > /dev/null < $filename
    
    dimension=$(echo $filename| cut -f 1 -d '.')    
    echo -n $dimension" " >> $ARCHIVO_LOG_RESULTADOS
    echo -n $filename" " >> $ARCHIVO_LOG_RESULTADOS
    echo -n $CLEAR_CACHE" " >> $ARCHIVO_LOG_RESULTADOS
    echo -n $RUTA_FUNCION" " >> $ARCHIVO_LOG_RESULTADOS
    echo -n $FLAGS_CACHEGRIND_I $FLAGS_CACHEGRIND_D" " >> $ARCHIVO_LOG_RESULTADOS

    archivo_log_raw=$RUTA_LOGS/raw/log_raw$dimension
    /opt/valgrind/bin/cg_annotate cachegrind.out.* $REAL_PATH > $archivo_log_raw.txt
    tail -n2 $archivo_log_raw.txt | head -n1 >> $ARCHIVO_LOG_RESULTADOS
    ruta_sin_barra="${RUTA_FUNCION//'/'/$'>'}"
    mv $archivo_log_raw.txt $archivo_log_raw$FLAGS_CACHEGRIND_D$CLEAR_CACHE$ruta_sin_barra.txt
    rm cachegrind.out.*
done
