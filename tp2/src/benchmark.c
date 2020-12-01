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
    matriz_t* C, double* datos, size_t dimension) {

    size_t tamanio_matriz = dimension*dimension;
    matriz_crear_desde(A, datos, dimension);
    matriz_crear_desde(B, datos+tamanio_matriz, dimension);
    matriz_crear_desde(C, datos+tamanio_matriz*2, dimension);    

    int resultado_A = matriz_parsear(A, &benchmark->cursor);
    if (resultado_A == MATRIZ_ERROR) {
        goto destruirA;
    }
    int resultado_B = matriz_parsear(B, &benchmark->cursor);
    if (resultado_B == MATRIZ_ERROR) {
        goto destruirB;
    }
    return MATRIZ_OK;

    destruirB:
    matriz_destruir(B);
    destruirA:
    matriz_destruir(A);
    
    matriz_destruir(C);
    return MATRIZ_ERROR;
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

        size_t total_elementos = sizeof(double)*dimension*dimension*3;
        double* datos = malloc(total_elementos);
        if (!datos) {
            return BENCHMARK_RESULTADO_ERROR;
        }

        resultado = crear_matrices(benchmark, &A, &B, &C, datos, dimension);
        if(resultado == MATRIZ_ERROR){
            free(datos);
            return BENCHMARK_RESULTADO_ERROR;
        }
        cronometro_iniciar(&cronometro);
        
        #if CLEAR_CACHE
        size_t j;
		size_t dim = 1024*1024*10;
		int *v = malloc(dim*sizeof(int));
        if(!v) {
            free(datos);
            destruir_matrices(&A, &B, &C);
            return BENCHMARK_RESULTADO_ERROR;
        }
		for (j = 0; j < dim; ++j)
			v[j] = -1;
		free(v);
        #endif
        
        matriz_multiplicar(&A, &B, &C, &mmult);
        
        cronometro_detener(&cronometro);

        matriz_imprimir(&C, stdout);
        cronometro_log(&cronometro);

        destruir_matrices(&A, &B, &C);
        free(datos);
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
