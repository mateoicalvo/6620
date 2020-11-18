#include "hasheador.h"

#define MSG_ERROR_INIT "Error al inicializar el hasheador en main."
#define MSG_ERROR_CORRER "Error en la ejecucion del hasheador en main."

int main(int argc, const char *argv[]) {
    
    hasheador_t hasheador;
    int resultado = hasheador_inicializar(&hasheador, argc, argv);
    if (resultado == ESTADO_ERROR) {
        fprintf(stderr, "%s\n", MSG_ERROR_INIT);
        return resultado;
    }
    
    resultado = hasheador_correr(&hasheador);
    if (resultado == RESULTADO_ERROR) {
        fprintf(stderr, "%s\n", MSG_ERROR_CORRER);
        hasheador_destruir(&hasheador);
        return resultado;
    }
    hasheador_destruir(&hasheador);
    return RESULTADO_OK;
}
