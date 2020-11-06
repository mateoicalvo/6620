#include "hasheador.h"

int main(int argc, const char *argv[]) {
    
    hasheador_t hasheador;
    //TODO: inicializar, correr y devolver
    hasheador_inicializar(&hasheador);
    hasheador_correr(&hasheador, argc-1, argv);

    return 0;
}
