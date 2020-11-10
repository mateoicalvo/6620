#ifndef HASHEADOR_H
#define HASHEADOR_H

#include <stdint.h>
#include <stdio.h>

#define MENSAJE_USO "\
Usage:\n\
tp1 -h\n\
tp1 -V\n\
tp1 -i in_file -o out_file\n\
Options:\n\
-V, --version\n\
Print version and quit.\n\
-h, --help\n\
Print this information and quit.\n\
-i, --input\n\
Specify input stream/file, \"-\" for stdin.\n\
-o, --output\n\
Specify output stream/file, \"-\" for stdout.\n\
Examples:\n\
tp1 < in.txt > out.txt\n\
cat in.txt | tp1 -i - > out.txt\n"

#define MENSAJE_VERSION "version 0.1\n"

#define ESTADO_OK 0
#define ESTADO_ERROR -1
#define PARAM_AYUDA "-h"
#define PARAM_VERSION "-V"
#define PARAM_INPUT "-i"
#define PARAM_OUTPUT "-o"

#define MODO_AYUDA 0
#define MODO_VERSION 1
#define MODO_CORRER 2

#define RESULTADO_OK 0
#define RESULTADO_ERROR -1

typedef struct hasheador {
    FILE* entrada;
    FILE* salida;
    int estado;
    int modo;
} hasheador_t;

/*
Inicializa un hasheador, con sus parametros recibidos.
Params:
    hasheador: un puntero valido
    n_parametros: cantidad de parametros recibidos
    parametros: array de strings que contiene los parametros
Retorno:
    ESTADO_OK (0) si no hay fallos, ESTADO_ERROR (-1) en caso contrario
*/
int hasheador_inicializar(hasheador_t* hasheador, int n_parametros, \
    const char* parametros[]);

/*
Destruye y libera todos los recursos adquiridos en hasheador.
*/
void hasheador_destruir(hasheador_t* hasheador);

/*
Ejecuta el hasheador segun el modo elegido en los parametros recibidos
*/
int hasheador_correr(hasheador_t* hasheador);

/*
Para cada linea de la entrada del hasheador, calcula su valor de hash, e
imprime el resultado seguido de la linea.
*/
int hasheador_hashear_archivo(hasheador_t* hasheador);

#endif
