#include "hasheador.h"

int main(int argc, const char *argv[]) {
    
    hasheador_t hasheador;
    //TODO: inicializar, correr y devolver
    hasheador_inicializar(&hasheador, argc-1, argv);
    hasheador_correr(&hasheador);
    hasheador_destruir(&hasheador);

    return 0;
}
