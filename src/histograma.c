#include "histograma.h"
#include "io.h"

#include <stdio.h>
#include <stdlib.h>

Histograma* make_histogram(Imagem* img)
{
    Histograma* hst = (Histograma*)malloc(sizeof(Histograma));
    if (hst == NULL)
    {
        return NULL;
    }

    hst->histogram = (int*)malloc(sizeof(int) * img->qtd_valores);
    hst->acumuleted_histogram = (int*)malloc(sizeof(int) * img->qtd_valores);
    hst->tam = img->qtd_valores;

    if (hst->histogram == NULL || hst->acumuleted_histogram == NULL)
    {
        free(hst->histogram);
        free(hst->acumuleted_histogram);
        free(hst);
        return NULL;
    }

    for (int i = 0; i < img->qtd_valores; i++)
    {
        hst->histogram[i] = 0;
        hst->acumuleted_histogram[i] = 0;
    }

    for (int i = 0; i < img->altura; i++)
    {
        for (int j = 0; j < img->largura; j++)
        {
            int value = img->matriz[i][j];
            hst->histogram[value] += 1;
        }
    }

    int sum_hist = 0;
    for (int i = 0; i < hst->tam; i++)
    {
        sum_hist += hst->histogram[i];
        hst->acumuleted_histogram[i] = sum_hist;
    }

    return hst;
}

void imprime_vetor(int* vector, int tam)
{
    printf("\n");
    for (int i = 0; i < tam; i++)
    {
        printf(" %d", vector[i]);
    }
    printf("\n");
}

void save_histogram(Histograma* hst, char* path_to_save)
{
    int maior_frequencia = 0;

    for (int i = 0; i < hst->tam; i++)
    {
        if (hst->histogram[i] > maior_frequencia)
        {
            maior_frequencia = hst->histogram[i];
        }
    }

    Imagem* img_histogram = create_image_gray_scale(maior_frequencia, hst->tam, 8);
    if (img_histogram == NULL)
    {
        return;
    }

    for (int j = 0; j < hst->tam; j++)
    {
        for (int i = 0; i < maior_frequencia; i++)
        {
            img_histogram->matriz[i][j] = hst->tam - 1;
            if (maior_frequencia - i <= hst->histogram[j])
            {
                img_histogram->matriz[i][j] = 0;
            }
        }
    }

    save_img(img_histogram, path_to_save);
    free_image(img_histogram);
}

void free_histogram(Histograma* hst)
{
    if (hst == NULL) return;
    free(hst->histogram);
    free(hst->acumuleted_histogram);
    free(hst);
}