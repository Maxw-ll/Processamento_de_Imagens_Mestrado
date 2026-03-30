#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "io.h"
#include "stb_image_write.h"
#include "stb_image.h"
#include "image.h"

#include <stdio.h>
#include <stdlib.h>

unsigned char* create_img_data_vector(Imagem* img)
{
    unsigned char* img_vector = (unsigned char*)malloc(sizeof(unsigned char) * img->altura * img->largura);
    if (img_vector == NULL)
    {
        return NULL;
    }

    int idx_vector = 0;
    for (int i = 0; i < img->altura; i++)
    {
        for (int j = 0; j < img->largura; j++)
        {
            img_vector[idx_vector] = (unsigned char)img->matriz[i][j];
            idx_vector++;
        }
    }

    return img_vector;
}

void save_img(Imagem* img, char* name)
{
    unsigned char* img_data = create_img_data_vector(img);
    if (img_data == NULL)
    {
        return;
    }

    stbi_write_png(name, img->largura, img->altura, 1, img_data, img->largura);
    free(img_data);
}

Imagem* read_img(char* path_img)
{
    int largura, altura, canais;

    unsigned char* img_vector = stbi_load(path_img, &largura, &altura, &canais, 1);
    if (img_vector == NULL)
    {
        return NULL;
    }

    Imagem* new_image = create_image_gray_scale(altura, largura, 8);
    if (new_image == NULL)
    {
        stbi_image_free(img_vector);
        return NULL;
    }

    printf("Quantidade de Canais: %d\n", canais);
    printf("Altura: %d\n", altura);
    printf("Largura: %d\n", largura);

    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            new_image->matriz[i][j] = (int)img_vector[i * largura + j];
        }
    }

    stbi_image_free(img_vector);
    return new_image;
}