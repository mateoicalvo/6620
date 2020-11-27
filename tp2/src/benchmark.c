#include "benchmark.h"

#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "matriz.h"
#include "matriz_helpers.h"
#include "cronometro.h"

#define CLEAR_CACHE 1

int parsear_dimension(benchmark_t* benchmark, size_t* dimension) {
    size_t parseada = strtol(benchmark->matrices, \
            &(benchmark->cursor), 10);
		
    if (errno) {
	    perror("");
		return BENCHMARK_ERROR_DIMENSION;
	}
	if (benchmark->matrices == benchmark->cursor) {
		fprintf(stderr, MSG_BENCHMARK_ERROR_FALTA_DIMENSION);
		return BENCHMARK_ERROR_DIMENSION;
	}
	if (parseada == 0) {
		fprintf(stderr, MSG_BENCHMARK_ERROR_DIMENSION);
		return BENCHMARK_ERROR_DIMENSION;
	}
    *dimension = parseada;
    return BENCHMARK_DIMENSION_OK;
}

int crear_matrices(benchmark_t* benchmark, matriz_t* A, matriz_t* B, \
    matriz_t* C, size_t dimension) {

    int resultado_A = matriz_crear(A, dimension);
    int resultado_B = matriz_crear(B, dimension);
    int resultado_C = matriz_crear(C, dimension);

    resultado_A = matriz_parsear(A, &benchmark->cursor);
    resultado_B = matriz_parsear(B, &benchmark->cursor);
    //TODO: ERROR CHECKING
    return 0;
}

void destruir_matrices(matriz_t* A, matriz_t* B, \
    matriz_t* C) {
        matriz_destruir(A);
        matriz_destruir(B);
        matriz_destruir(C);
}


void benchmark_crear(benchmark_t* benchmark) {

    benchmark->matrices = NULL;
    benchmark->cursor = " ";
}

int benchmark_correr(benchmark_t* benchmark) {
    matriz_t A;
    matriz_t B;
    matriz_t C;

    cronometro_t cronometro;
    cronometro_crear(&cronometro);

    size_t tamanio = 0;
    int resultado = 0;
    while ((resultado = getline(&(benchmark->matrices), &tamanio, \
        stdin)) != -1) {
        
        size_t dimension;
        int resultado = parsear_dimension(benchmark, &dimension);
        if (resultado == BENCHMARK_ERROR_DIMENSION) {
            goto fin_error;
        }
        //TODO: ERRORCHECK
        resultado = crear_matrices(benchmark, &A, &B, &C, dimension);
        cronometro_iniciar(&cronometro);
        
        #if CLEAR_CACHE
        size_t j;
		size_t dim = 1024*1024*10;
		int *v = malloc(dim*sizeof(int));
		for (j = 0; j < dim; ++j)
			v[j] = -1;
		free(v);
        #endif
        
        matriz_multiplicar(&A, &B, &C, &mmult);
        
        cronometro_detener(&cronometro);

        matriz_imprimir(&C, stdout);
        cronometro_log(&cronometro);

        destruir_matrices(&A, &B, &C);
        free(benchmark->matrices);
        benchmark->matrices = NULL;
    }
    if (feof(stdin)) {
        resultado = BENCHMARK_RESULTADO_OK;
    } else {
        resultado = BENCHMARK_RESULTADO_ERROR;
    }
    free(benchmark->matrices);
    return resultado;
fin_error:
    free(benchmark->matrices);
    return BENCHMARK_RESULTADO_ERROR;    
}

void benchmark_destruir(benchmark_t* benchmark) {

}
