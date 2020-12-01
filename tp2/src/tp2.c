#include <stdio.h>
#include "benchmark.h"

#define MSG_ERROR_BENCHMARK "Error en la ejecucion del benchmark.\n"

int main(int argc, char const *argv[]) {
    
    benchmark_t benchmark;
    benchmark_crear(&benchmark);
    int resultado = benchmark_correr(&benchmark);
    if (resultado == BENCHMARK_RESULTADO_ERROR) {
        fprintf(stderr, MSG_ERROR_BENCHMARK);
    }

    benchmark_destruir(&benchmark);
    return resultado;
}
