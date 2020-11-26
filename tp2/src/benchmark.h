#ifndef BENCHMARK_H
#define BENCHMARK_H

#define BENCHMARK_RESULTADO_OK 0
#define BENCHMARK_RESULTADO_ERROR -1

#define BENCHMARK_ERROR_DIMENSION -1
#define BENCHMARK_DIMENSION_OK 0

#define MSG_BENCHMARK_ERROR_FALTA_DIMENSION "\
Error, falta la dimension.\n"

#define MSG_BENCHMARK_ERROR_DIMENSION "\
Error, dimension invalida.\n"


typedef struct benchmark {
    char* matrices;
    char* cursor;
} benchmark_t;

void benchmark_crear(benchmark_t* benchmark);

int benchmark_correr(benchmark_t* benchmark);

void benchmark_destruir(benchmark_t* benchmark);

#endif
