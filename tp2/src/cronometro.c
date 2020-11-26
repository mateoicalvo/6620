#include "cronometro.h"

void cronometro_crear(cronometro_t* cronometro) {
}

void cronometro_iniciar(cronometro_t* cronometro) {
    clock_gettime(CLOCK_REALTIME, &(cronometro->t_inicial));
}

void cronometro_detener(cronometro_t* cronometro) {
    clock_gettime(CLOCK_REALTIME, &(cronometro->t_final));
}

double cronometro_tiempo_transcurrido(cronometro_t* cronometro) {
    
    double segundos = (float) cronometro->t_final.tv_sec \
         - cronometro->t_inicial.tv_sec;
    double nanosegundos = ((float) cronometro->t_final.tv_nsec \
         - cronometro->t_inicial.tv_nsec) / 1.0e9;
    
    return segundos + nanosegundos;
}

void cronometro_destruir(cronometro_t* cronometro) {
}
