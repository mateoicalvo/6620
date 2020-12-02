#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define BLOQUES 256
#define ASOCIATIVIDAD 4


int main(int argc, const char* argv[]) {
    srand(time(NULL));   // Initialization, should only be called once.

    int DIMENSION = atoi(argv[1]);

    char nombre[80];
    sprintf(nombre, "4WAY_%d.csv", DIMENSION);

    FILE* log = fopen(nombre, "w");
    
    //Calculo direcciones accedidas
    int* accesos = malloc(sizeof(int)*DIMENSION*DIMENSION*(1 + 2*DIMENSION));
    int base_b = DIMENSION*DIMENSION*8;
    int base_c = 3*base_b;
    
    int contador = 0;
    for (int fila = 0; fila < DIMENSION; fila++) {
        for (int columna = 0; columna < DIMENSION; columna++) {
            for (int elemento = 0; elemento < DIMENSION; elemento++) {
                accesos[contador] = (fila*DIMENSION + elemento)*8;
                accesos[contador+1] = base_b + (elemento*DIMENSION + columna)*8;
                contador += 2;
            }
            accesos[contador] = base_c + (fila*DIMENSION + columna)*8;
            contador+=1;
        }
    }
    //Fin calculo direcciones accedidas

    // Creo cache
    int hits = 0;
    int misses = 0;
    //int bits_de_index = 9;
    //int bits_de_offset = 5;
    int shift = 13;
    int* bloques = malloc(sizeof(int)*1024);
    // Inicialmente está vacio
    for (int j = 0; j < 1024; j++) {
        bloques[j] = -1;
    }

    int index;
    int tag;

    for (int iterB = 0; iterB < 32; ++iterB) {
        for (int iterC = 0; iterC < 32; ++iterC) {
            //calcular misses y hits
            for (int i = 0; i < DIMENSION*DIMENSION*(1 + 2*DIMENSION); ++i) {
                index = accesos[i] % BLOQUES;
                tag = accesos[i] >> shift;

                for (char a = 0; a < ASOCIATIVIDAD; ++a) {
                    if (bloques[(4*index)+a] == tag) {
                        hits+=1;
                        goto encontrado;
                    }
                }
                misses += 1;
                //ACA EL RANDOM

                bloques[(4*index) + (rand() % ASOCIATIVIDAD)] = tag;
                encontrado:
                ;
            }
            fprintf(log, "%d,4,%d,%d\n", DIMENSION, hits, misses);
            for (int j = 0; j < 1024; j++) {
                bloques[j] = -1;
            }
            hits = 0;
            misses = 0;
            //Corro las direcciones de C en 8 bytes
            for (int posicion = 2*DIMENSION; posicion < DIMENSION*DIMENSION*(1 + 2*DIMENSION); posicion+=2*DIMENSION) {
                accesos[posicion] += 8;
            }  
        }
        //shiftear B
        for (int j = 0; j < DIMENSION*DIMENSION; j+=(2*DIMENSION)+1) {
            for (int k = 1; k < 2*DIMENSION; k+=2) {
                accesos[k+j] +=8;
            }
        }
        printf("%d de 31\n", iterB);
    }    
    
    free(accesos);
    free(bloques);
    fclose(log);
    return 0;
}
