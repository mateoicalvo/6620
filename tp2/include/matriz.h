#ifndef MATRIZ_H
#define MATRIZ_H

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#define MSG_MATRIZ_ERROR_MALLOC "\
Error matriz_crear, fallo malloc\n"

#define MSG_MATRIZ_ERROR_PARSEAR "\
Error matriz_parsear, faltan elementos\n"

#define MATRIZ_ERROR_CREAR -1
#define MATRIZ_OK 0
#define MATRIZ_ERROR -1

typedef struct matriz {
	size_t dimension;
	double* elementos;
	bool borrar_datos;
} matriz_t;

int matriz_crear(matriz_t* matriz, size_t dimension, bool borrar_datos);

void matriz_crear_desde(matriz_t* matriz, double* elementos, size_t dimension);

int matriz_parsear(matriz_t* matriz, char** elementos);

void matriz_destruir(matriz_t* matriz);

int matriz_imprimir(matriz_t* matriz, FILE* destino);

void matriz_multiplicar(matriz_t* A, matriz_t* B,
    matriz_t* resultado, \
	void (*f)(double*, double*, double*, size_t));

#endif
