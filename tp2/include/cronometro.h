#ifndef CRONOMETRO_H
#define CRONOMETRO_H

#include <time.h>

typedef struct cronometro {
    struct timespec t_inicial;
	struct timespec t_final;
} cronometro_t;


void cronometro_crear(cronometro_t* cronometro);

void cronometro_iniciar(cronometro_t* cronometro);

void cronometro_detener(cronometro_t* cronometro);

double cronometro_tiempo_transcurrido(cronometro_t* cronometro);

void cronometro_destruir(cronometro_t* cronometro);

void cronometro_log(cronometro_t* cronometro);

#endif
