#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hasheador.h"
#include "hash.h"

int hasheador_inicializar(hasheador_t* hasheador, int n_parametros, const char* parametros[]) {
    if (n_parametros != 1 && n_parametros != 4) {
        hasheador->estado = ESTADO_ERROR;
    }
    else if (n_parametros == 1 && strlen(parametros[1]) == 2) {
        if (parametros[1][1] == CHAR_AYUDA) {
            hasheador->modo = MODO_AYUDA;
            hasheador->estado = ESTADO_OK;
        } else if (parametros[1][1] == CHAR_VERSION) {
            hasheador->modo = MODO_VERSION;
            hasheador->estado = ESTADO_OK;
        } else {
            hasheador->estado = ESTADO_ERROR;
        }    
    
    } else { //hay 4 parametros -i - -o -
        hasheador->modo = MODO_CORRER;
        if (strncmp(parametros[2], "-", 1) == 0) {
            hasheador->entrada = stdin;
        } else {
            hasheador->entrada = fopen(parametros[2], "r");
            if (!hasheador->entrada) {
                hasheador->estado = ESTADO_ERROR;
                goto fin;
            }
        }
        if (strncmp(parametros[4], "-", 1) == 0) {
            hasheador->salida = stdout;
        } else {
            hasheador->salida = fopen(parametros[4], "w");
            if (!hasheador->salida) {
                hasheador->estado = ESTADO_ERROR;
                if (hasheador->entrada != stdin) {
                    fclose(hasheador->entrada);
                }
            }            
        }
    }
    fin:
    return hasheador->estado;    
}

void hasheador_destruir(hasheador_t* hasheador) {
    if (hasheador->estado == ESTADO_ERROR) {
        return;
    }
    if (hasheador->entrada != stdin) {
        fclose(stdin);
    }
    if (hasheador->salida != stdout) {
        fclose(stdout);
    }
}

int hasheador_correr(hasheador_t* hasheador) {
    if (hasheador->estado == ESTADO_ERROR) {
        printf("%s", MENSAJE_USO);
        return RESULTADO_ERROR;
    } else if (hasheador->modo == MODO_AYUDA) {
        printf("%s", MENSAJE_USO);
        return RESULTADO_OK;
    } else if (hasheador->modo == MODO_VERSION) {
        printf("%s", MENSAJE_VERSION);
        return RESULTADO_OK;
    } else { // Modo correr
        hasheador_hashear_archivo(hasheador);
    }
    return 0;
}

void hasheador_hashear_archivo(hasheador_t* hasheador) {

    string_hash sh;
    
    char* line_ptr = NULL;
    size_t tamanio = 0;

    while (getline(&line_ptr, &tamanio, hasheador->entrada) != -1) {
        string_hash_init(&sh);
        string_hash_more(&sh, line_ptr, tamanio);
        string_hash_done(&sh);
        fprintf(hasheador->salida, "0x%08x %s", \
            string_hash_value(&sh), line_ptr);
    }    
    free(line_ptr);
}
