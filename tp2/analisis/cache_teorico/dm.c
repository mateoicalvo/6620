#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char* argv[]) {
    
    int DIMENSION = atoi(argv[1]);

    char nombre[80];
    sprintf(nombre, "DM_%d.csv", DIMENSION);

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
    //int bits_de_index = 10;
    //int bits_de_offset = 5;
    int shift = 15;
    int* bloques = malloc(sizeof(int)*1024);
    // Inicialmente está vacio
    for (int j = 0; j < 1024; j++) {
        bloques[j] = -1;
    }
    // Fin crear cache

    int index;
    int tag;

    for (int iterB = 0; iterB < 128; ++iterB) {
        for (int iterC = 0; iterC < 128; ++iterC) {
            //calcular misses y hits
            for (int i = 0; i < DIMENSION*DIMENSION*(1 + 2*DIMENSION); ++i) {
                index = accesos[i] % 1024;
                tag = accesos[i] >> shift;
                if (bloques[index] == tag) {
                    hits+=1;
                }
                else {
                    misses+=1;
                    bloques[index] = tag;
                }
            }
            fprintf(log, "%d,0,%d,%d\n", DIMENSION, hits, misses);
            //reseteo caché
            for (int j = 0; j < 1024; j++) {
                bloques[j] = -1;
            }
            hits = 0;
            misses = 0;
            //Corro las posiciones de C 8bytes           
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
        printf("%d de 127\n", iterB);
    }        
    free(accesos);
    free(bloques);
    fclose(log);
    return 0;
}
