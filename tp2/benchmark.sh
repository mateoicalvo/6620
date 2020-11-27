if [ "compilar" == "$1" ]
then
    mkdir -p obj
    mkdir -p asm
    if [[ "$2" == *.c ]]
    then
        gcc -g -S $2 -o asm/mmult.s;
        sed -i '/.file 1/,+1d' asm/mmult.s
    else #assembler
        echo asembly
        cp $2 asm/mmult.S
    fi
    gcc -g -c asm/mmult.* -o obj/mmult.o
    make
fi
