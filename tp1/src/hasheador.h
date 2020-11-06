#ifndef HASHEADOR_H
#define HASHEADOR_H

#include "hash.h"

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

typedef struct hasheador {
    int estado;
} hasheador_t;

void hasheador_inicializar(hasheador_t* hasheador);

void hasheador_destruir(hasheador_t* hasheador);

int hasheador_correr(hashador_t* hasheador, int n_parametros, const char* parametros[])

int32_t hasheador_hashear_linea(hasheador_t* hasheador, char* linea);

#endif
