#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "hasheador.h"
#include "hash.h"


/*
Devuelve true si el null-terminated string str se encuentra en array.
Si se especifica pos, se devuelve alli la posicion.
Params:
    str: string que se quiere buscar
    array: arreglo de strings
    array_size: tamanio de array
    pos: puntero donde se devuelve la posicion, NULL para ignorar
        comportamiento
Retorno:
    true si str se encuentra en array, false en caso contrario.
    si str se encuentra en array y pos no es NULL, pos contiene
    la posicion de str en array.
    Si str no se encuentra en array, pos no se altera.
*/
static bool str_en_array(const char* str, \
    const char** array, size_t array_size, size_t* pos) {

        for (size_t i = 0; i < array_size; i++) {
            if (!strcmp(array[i], str)) {
                if (pos) {
                    *pos = i;
                }                
                return true;
            }
        }
        return false;
}

int hasheador_inicializar(hasheador_t* hasheador, int n_parametros, const char* parametros[]) {
    
    hasheador->modo = MODO_CORRER;
    hasheador->estado = ESTADO_OK;
    
    if (str_en_array(PARAM_AYUDA, parametros, n_parametros, NULL)) {
        hasheador->modo = MODO_AYUDA;
    } else if (str_en_array(PARAM_VERSION, parametros, n_parametros, NULL)) {
        hasheador->modo = MODO_VERSION;
    }

    size_t posicion = 0;

    if (str_en_array(PARAM_INPUT, parametros, n_parametros, &posicion)) {
        if (*parametros[posicion + 1] == '-') {
            hasheador->entrada = stdin;
        } else {
            hasheador->entrada = fopen(parametros[posicion + 1], "r");
            if (!hasheador->entrada) {
                hasheador->estado = ESTADO_ERROR;
                goto fin;
            }
        }
    } else {
        hasheador->entrada = stdin;
    }

    if (str_en_array(PARAM_OUTPUT, parametros, n_parametros, &posicion)) {
        if (*parametros[posicion + 1] == '-') {
            hasheador->salida = stdout;
        } else {
            hasheador->salida = fopen(parametros[posicion + 1], "w");
            if (!hasheador->salida) {
                hasheador->estado = ESTADO_ERROR;
                if (hasheador->entrada != stdin) {
                    fclose(hasheador->entrada);
                }
            }
        }
    } else {
        hasheador->salida = stdout;
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
    int resultado = 0;
    if (hasheador->estado == ESTADO_ERROR) {
        printf("%s", MENSAJE_USO);
        resultado =  RESULTADO_ERROR;
    } else if (hasheador->modo == MODO_AYUDA) {
        printf("%s", MENSAJE_USO);
        resultado = RESULTADO_OK;
    } else if (hasheador->modo == MODO_VERSION) {
        printf("%s", MENSAJE_VERSION);
        resultado = RESULTADO_OK;
    } else { // Modo correr
        resultado = hasheador_hashear_archivo(hasheador);
    }
    return resultado;
}

int hasheador_hashear_archivo(hasheador_t* hasheador) {

    string_hash sh;
    
    char* line_ptr = NULL;
    size_t tamanio = 0;
    int resultado = 0;
    while ((resultado = getline(&line_ptr, &tamanio, hasheador->entrada)) != -1) {
        string_hash_init(&sh);
        string_hash_more(&sh, line_ptr, tamanio);
        string_hash_done(&sh);
        fprintf(hasheador->salida, "0x%08x %s", \
            string_hash_value(&sh), line_ptr);
    }
    if (feof(hasheador->entrada)) {
        resultado = RESULTADO_OK;
    } else {
        resultado = RESULTADO_ERROR;
    }
    free(line_ptr);
    return resultado;
}
