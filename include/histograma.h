/*
    Definições da estrutura do Histograma e suas funções

*/

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "image.h"

typedef struct
{
    int* histogram;
    int* acumuleted_histogram;
    int tam;
} Histograma;

Histograma* make_histogram(Imagem* img);
void imprime_vetor(int* vector, int tam);
void save_histogram(Histograma* hst, char* path_to_save);
void free_histogram(Histograma* hst);

#endif


