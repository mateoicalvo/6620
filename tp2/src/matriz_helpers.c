#include "matriz_helpers.h"

void matriz_multiplicar_vector(double* A, double* B, \
    double* resultado, size_t n) {

        for(size_t fila = 0; fila < n; fila++) {
            for(size_t columna = 0; columna < n; columna++) {
                for(size_t i = 0; i < n; i++) {
                    resultado[fila*n + columna] += \
                        A[fila*n + i] * B[i*n + columna];
                }
            }
        }

}
