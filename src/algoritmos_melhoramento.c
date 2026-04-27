
#include "image.h"
#include "histograma.h"
#include "algoritmos_melhoramento.h"

/*
#######################################################

Aluno: MAXWELL PIRES SILVA
Professor: ARISTOFANES CORREA SILVA
Disciplina: PROCESSAMENTO DE IMAGEM E VISÃO COMPUTACIONAL 
27/04/2026

########################################################
*/
Imagem* create_new_image(Imagem* img)
{
    Imagem* new_img = create_image_gray_scale(img->altura, img->largura, img->qtd_bits);
    return new_img;
}

Imagem* mapeamento_linear(Imagem* img, Histograma* hst)
{
    // Criar nova imagem
    Imagem* new_img = create_new_image(img);

    int min_pixel = 255;
    int max_pixel = 0;
    
    // Encontrar os valores mínimo e máximo de intensidade no histograma
    for (int i = 0; i < hst->tam; i++) {
        if (hst->histogram[i] > 0) {
            if (i < min_pixel) min_pixel = i;
            if (i > max_pixel) max_pixel = i;
        }
    }

    // A = 255 / (max_pixel - min_pixel)
    // B = -A * min_pixel
    float A = 255.0 / (max_pixel - min_pixel);
    float B = -A * min_pixel;

    // Mapeamento linear dos pixels da nova matriz
    for (int i = 0; i < img->altura; i++) {
        for (int j = 0; j < img->largura; j++) {
            new_img->matriz[i][j] = (int)(A * img->matriz[i][j] + B);
            // Garantir que o valor dos pixels esteja entre 0 e 255
            if (new_img->matriz[i][j] < 0) new_img->matriz[i][j] = 0;
            if (new_img->matriz[i][j] > 255) new_img->matriz[i][j] = 255;
        }
    }
    
    return new_img;
}


Imagem* stretching(Imagem* img, Histograma* hst)
{
    // Criar nova imagem
    Imagem* new_img = create_new_image(img);

    int min_pixel = 255;
    int max_pixel = 0;

    // Encontrar os valores mínimo e máximo de intensidade no histograma
    for (int i = 0; i < hst->tam; i++) {
        if (hst->histogram[i] > 0) {
            if (i < min_pixel) min_pixel = i;
            if (i > max_pixel) max_pixel = i;
        }
    }

    // A = 255 / (max_pixel - min_pixel)
    // B = -A * min_pixel
    float A = 255.0 / (max_pixel - min_pixel);
    float B = -A * min_pixel;

    // Stretching dos pixels da nova matriz
    for (int i = 0; i < img->altura; i++) {
        for (int j = 0; j < img->largura; j++) {
            new_img->matriz[i][j] = (int)(A * img->matriz[i][j] + B);
            // Garantir que o valor dos pixels esteja entre 0 e 255
            if (new_img->matriz[i][j] < 0) new_img->matriz[i][j] = 0;
            if (new_img->matriz[i][j] > 255) new_img->matriz[i][j] = 255;
        }
    }

    return new_img;
}


Imagem* equalizacao(Imagem* img, Histograma* hst)
{
    // Criar nova imagem
    Imagem* new_img = create_new_image(img);

    // Calcular o histograma acumulado
    int* acumu = hst->acumuleted_histogram;
    acumu[0] = hst->histogram[0];
    for (int i = 1; i < hst->tam; i++) {
        acumu[i] = acumu[i - 1] + hst->histogram[i];
    }

    // Encontrar o número total de pixels na imagem
    int total_pixels = img->altura * img->largura;

    // Aplicar a equalização nos pixels da nova matriz
    for (int i = 0; i < img->altura; i++) {
        for (int j = 0; j < img->largura; j++) {
            int pixel_value = img->matriz[i][j];
            int new_value = (int)((acumu[pixel_value] - acumu[0]) * 255.0 / (total_pixels - acumu[0]));
            new_img->matriz[i][j] = new_value;
            // Garantir que o valor dos pixels esteja entre 0 e 255
            if (new_img->matriz[i][j] < 0) new_img->matriz[i][j] = 0;
            if (new_img->matriz[i][j] > 255) new_img->matriz[i][j] = 255;
        }
    }

    return new_img;
}


Imagem* clipping(Imagem* img, int limite)
{
    // Criar nova imagem
    Imagem* new_img = create_new_image(img);

    // Clipping dos pixels da nova matriz
    for (int i = 0; i < img->altura; i++) {
        for (int j = 0; j < img->largura; j++) {
            if (img->matriz[i][j] > limite) {
                new_img->matriz[i][j] = limite;
            } else {
                new_img->matriz[i][j] = img->matriz[i][j];
            }
        }
    }

    return new_img;
}