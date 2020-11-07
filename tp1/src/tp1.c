#include "hasheador.h"

int main(int argc, const char *argv[]) {
    
    hasheador_t hasheador;
    hasheador_inicializar(&hasheador, argc-1, argv);
    int resultado_ejecucion = hasheador_correr(&hasheador);
    hasheador_destruir(&hasheador);
    return resultado_ejecucion;
}
