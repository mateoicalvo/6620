#!/bin/bash

RUTA_FUNCION=$1
CLEAR_CACHE=$2
RUTA_INPUTS=$3

FLAGS_CACHEGRIND_I=$5
FLAGS_CACHEGRIND_D=$6
mkdir -p obj
mkdir -p asm


if [[ "$RUTA_FUNCION" == *.c ]]
then
    gcc -g -S $RUTA_FUNCION -o asm/mmult.s;
    sed -i '/.file 1/,+1d' asm/mmult.s
    es_assembler="No"
else #assembler
    cp $RUTA_FUNCION asm/mmult.S
    es_assembler="Si"
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

RUTA_LOGS=$4
func_name=$(basename $RUTA_FUNCION | cut -d'.' -f1)
tipo_cache=$(echo ${FLAGS_CACHEGRIND_D:5} | tr , _)
clear_cache=$(echo $CLEAR_CACHE | tr = _)

ruta_final=$RUTA_LOGS/$func_name/$tipo_cache/$clear_cache
mkdir -p $ruta_final/raw

ARCHIVO_LOG_RESULTADOS=$ruta_final/log.txt
GREEN='\033[0;32m'
NC='\033[0m' # No Color

for filename in `ls $RUTA_INPUTS/*.txt | sort -V`; do
    /opt/valgrind/bin/valgrind --tool=cachegrind --log-file=/dev/null $FLAGS_CACHEGRIND_I $FLAGS_CACHEGRIND_D bin/benchmark > /dev/null < $filename
    
    dimension=$(echo $filename| tr -cd '[[:digit:]]')    
    echo -n $dimension" " >> $ARCHIVO_LOG_RESULTADOS
    echo -n $filename" " >> $ARCHIVO_LOG_RESULTADOS
    echo -n $CLEAR_CACHE" " >> $ARCHIVO_LOG_RESULTADOS
    echo -n $RUTA_FUNCION" " >> $ARCHIVO_LOG_RESULTADOS
    echo -n $FLAGS_CACHEGRIND_I $FLAGS_CACHEGRIND_D" " >> $ARCHIVO_LOG_RESULTADOS

    archivo_log_raw=$ruta_final/$dimension.txt
    /opt/valgrind/bin/cg_annotate cachegrind.out.* $REAL_PATH > $archivo_log_raw
    tail -n2 $archivo_log_raw | head -n1 >> $ARCHIVO_LOG_RESULTADOS
    mv $archivo_log_raw $ruta_final/raw/$dimension.txt
    rm cachegrind.out.*
    printf "Dimension: $dimension, $func_name, $tipo_cache, $clear_cache ${GREEN}Finalizado${NC}.\n"
done

if [[ "$es_assembler" == "Si" ]]
then
    mv asm/mmult.S $ruta_final/mmult.S
else
    mv asm/mmult.s $ruta_final/mmult.s
fi

rm obj/mmult.o
