#include "benchmark.h"

int main(int argc, char const *argv[]) {
    
    benchmark_t benchmark;
    benchmark_crear(&benchmark);
    int resultado = benchmark_correr(&benchmark);
    //TODO: ERROR CHECK

    benchmark_destruir(&benchmark);
    return resultado;
}
