#include "image.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Imagem* create_image_gray_scale(int altura, int largura, int n_bits)
{
    Imagem* this_image = (Imagem*)malloc(sizeof(Imagem));
    if (this_image == NULL)
    {
        return NULL;
    }

    int** this_matriz = (int**)malloc(sizeof(int*) * altura);
    if (this_matriz == NULL)
    {
        free(this_image);
        return NULL;
    }

    for (int i = 0; i < altura; i++)
    {
        this_matriz[i] = (int*)malloc(sizeof(int) * largura);
        if (this_matriz[i] == NULL)
        {
            for (int k = 0; k < i; k++)
            {
                free(this_matriz[k]);
            }
            free(this_matriz);
            free(this_image);
            return NULL;
        }
    }

    this_image->matriz = this_matriz;
    this_image->altura = altura;
    this_image->largura = largura;
    this_image->qtd_bits = n_bits;
    this_image->qtd_valores = (int)pow(2, n_bits);

    return this_image;
}

void show_image(Imagem *img)
{
    printf("[Image: %d bits | %d valores]\n", img->qtd_bits, img->qtd_valores);
    for (int i = 0; i < img->altura; i++)
    {
        for (int j = 0; j < img->largura; j++)
        {
            printf("%d\t", img->matriz[i][j]);
        }
        printf("\n");
    }
}

void fill_matriz_with_number(Imagem* img, int number, int random)
{
    for (int i = 0; i < img->altura; i++)
    {
        for (int j = 0; j < img->largura; j++)
        {   
            if(random == TRUE)
            {
                img->matriz[i][j] = rand() % img->qtd_valores;
            }
            else
            {
                img->matriz[i][j] = number;
            }
        }
    }
}

void free_image(Imagem* img)
{
    if (img == NULL) return;

    for (int i = 0; i < img->altura; i++)
    {
        free(img->matriz[i]);
    }
    free(img->matriz);
    free(img);
}