#include "matriz.h"

#include <stdlib.h>
#include <errno.h>

#include "matriz_helpers.h"

int matriz_crear(matriz_t* matriz, size_t dimension) {
    matriz->elementos = malloc(sizeof(double)*dimension*dimension);
    if (!matriz->elementos) {
        fprintf(stderr, MSG_MATRIZ_ERROR_MALLOC);
        return MATRIZ_ERROR_CREAR;
    }
    size_t cantidad_elementos = dimension * dimension;
    for (size_t elemento = 0; elemento < cantidad_elementos;\
        elemento++) {
            matriz->elementos[elemento] = 0.0;
    }
    matriz->dimension = dimension;
    return MATRIZ_OK;    
}

int matriz_parsear(matriz_t* matriz, char** elementos) {
    
    char* nptr = *elementos;
    char* endptr = *elementos;
    size_t n = matriz->dimension * matriz->dimension;
    double elemento;
    for (size_t i = 0; i < n; i++) {
        nptr = endptr;
        elemento = strtod(nptr, &endptr);
		if (errno) {
			perror("");
            return MATRIZ_ERROR;
		}
		if (nptr == endptr) {
			fprintf(stderr, MSG_MATRIZ_ERROR_PARSEAR);	
		}
        matriz->elementos[i] = elemento;
    }
    *elementos = endptr;
    //TODO: Error check y return value.
}

void matriz_destruir(matriz_t* matriz) {
    if (matriz->elementos != NULL) {
        free(matriz->elementos);
    }
    matriz->elementos = NULL;
}

int matriz_imprimir(matriz_t* matriz, FILE* destino) {

    int resultado = fprintf(destino, "Dimension: %zu.\n",
        matriz->dimension);
    if (resultado < 0) {
        perror("");
        return MATRIZ_ERROR;
    }

    size_t dimension = matriz->dimension;
    for(size_t fila = 0; fila < matriz->dimension; fila++) {
        for(size_t columna = 0; columna < matriz->dimension;\
            columna++) {
                
                resultado = fprintf(destino, " %g ", \
                    matriz->elementos[fila*dimension + columna]);
                if (resultado < 0) {
                    perror("");
                    return MATRIZ_ERROR;
                }
        }
        resultado = fprintf(destino, "\n");
        if (resultado < 0) {
            perror("");
            return MATRIZ_ERROR;
        }
    }
	return MATRIZ_OK;
}

void matriz_multiplicar(matriz_t* A, matriz_t* B,
    matriz_t* resultado) {

    double* elementosA = A->elementos;
    double* elementosB = B->elementos;
    double* elementosC = resultado->elementos;

    size_t n = A->dimension;

    matriz_multiplicar_vector(elementosA, elementosB,\
        elementosC, n);
}
