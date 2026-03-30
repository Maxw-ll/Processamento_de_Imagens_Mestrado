
/*
Definição da Struct de Imagem e suas funções principais
*/

#ifndef IMAGE_H
#define IMAGE_H

typedef struct
{
    int** matriz;
    int altura;
    int largura;
    int qtd_bits;
    int qtd_valores;
} Imagem;

Imagem* create_image_gray_scale(int altura, int largura, int n_bits);
void show_image(Imagem *img);
void fill_matriz_with_random(Imagem* img);
void free_image(Imagem* img);

#endif