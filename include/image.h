
/*
Definição da Struct de Imagem e suas funções principais
*/

#ifndef IMAGE_H
#define IMAGE_H

#define TRUE 1
#define FALSE 0

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
void fill_matriz_with_number(Imagem* img, int number, int random);
void free_image(Imagem* img);

#endif