#include <stdio.h>
#include <string.h>

#include "hasheador.h"


void hasheador_inicializar(hasheador_t* hasheador) {
    hasheador->estado = ESTADO_OK;
}

void hasheador_destruir(hasheador_t* hasheador) {

}

int hasheador_correr(hasheador_t* hasheador, int n_parametros, const char* parametros[]) {
    //TODO: checkear que los parametros sean correctos, y ejecutar bucle principal.
    if (n_parametros != 1 && n_parametros != 4) {
        printf("%s", MENSAJE_USO);
        hasheador->estado = ESTADO_ERROR;
    }
    
    else if (n_parametros == 1 && strlen(parametros[1]) == 2) {
        if (parametros[1][1] == CHAR_AYUDA) {
            printf("%s", MENSAJE_USO);
        }
        else if (parametros[1][1] == CHAR_VERSION) {
            printf("%s", MENSAJE_VERSION);
        }
        else {
            printf("%s", MENSAJE_USO);
            hasheador->estado = ESTADO_ERROR;
        }
    }

    else { //hay 4 parametros -i - -o -

    }
    return 0;
}

int32_t hasheador_hashear_linea(hasheador_t* hasheador, char* linea) {
    //TODO: logica de hasheo de cada línea
    return 0;
}
