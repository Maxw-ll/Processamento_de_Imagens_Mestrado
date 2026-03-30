/*
#######################################################

Aluno: MAXWELL PIRES SILVA
Professor: ARISTOFANES CORREA SILVA
Disciplina: PROCESSAMENTO DE IMAGEM E VISÃO COMPUTACIONAL 

########################################################
*/

#include "quantizacao.h"
#include "histograma.h"

#include <stdlib.h>
#include <math.h>

Imagem* make_uniform_quantization(Imagem* img, int n_bits)
{
    int n_faixas = (int)pow(2, n_bits);
    int new_values[n_faixas];
    int limit_values[n_faixas];
    int qtd_val = img->qtd_valores;

    for (int i = 0; i < n_faixas; i++)
    {
        new_values[i] = (qtd_val / n_faixas) * i;
        limit_values[i] = ((qtd_val / n_faixas) * (i + 1)) - 1;
    }

    Imagem* new_image = create_image_gray_scale(img->altura, img->largura, n_bits);
    if (new_image == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < img->altura; i++)
    {
        for (int j = 0; j < img->largura; j++)
        {
            for (int k = 0; k < n_faixas; k++)
            {
                if (img->matriz[i][j] <= limit_values[k])
                {
                    new_image->matriz[i][j] = new_values[k];
                    break;
                }
            }
        }
    }

    return new_image;
}

Imagem* make_equality_frequence_distribution_quantization(Imagem* img, int n_bits)
{
    Imagem* new_image = create_image_gray_scale(img->altura, img->largura, n_bits);
    Histograma* hst = make_histogram(img);

    if (new_image == NULL || hst == NULL || hst->histogram == NULL)
    {
        free_image(new_image);
        free_histogram(hst);
        return NULL;
    }

    int* histogram = hst->histogram;
    save_histogram(hst, "Histograma.png");

    int n_faixas = (int)pow(2, n_bits);
    int new_values[n_faixas];
    int limit_values[n_faixas];

    int count_values = 0;
    int sum_values = 0;
    int counter_for_values = 0;
    int alvo = (img->altura * img->largura) / n_faixas;

    for (int i = 0; i < img->qtd_valores && counter_for_values < n_faixas; i++)
    {
        count_values += histogram[i];
        sum_values += histogram[i] * i;

        if (count_values >= alvo && counter_for_values < n_faixas - 1)
        {
            new_values[counter_for_values] = sum_values / count_values;
            limit_values[counter_for_values] = i;
            count_values = 0;
            sum_values = 0;
            counter_for_values++;
        }
    }

    if (count_values > 0 && counter_for_values < n_faixas)
    {
        new_values[counter_for_values] = sum_values / count_values;
        limit_values[counter_for_values] = img->qtd_valores - 1;
        counter_for_values++;
    }

    while (counter_for_values < n_faixas)
    {
        new_values[counter_for_values] = new_values[counter_for_values - 1];
        limit_values[counter_for_values] = img->qtd_valores - 1;
        counter_for_values++;
    }

    imprime_vetor(limit_values, n_faixas);
    imprime_vetor(new_values, n_faixas);

    for (int i = 0; i < img->altura; i++)
    {
        for (int j = 0; j < img->largura; j++)
        {
            for (int k = 0; k < n_faixas; k++)
            {
                if (img->matriz[i][j] <= limit_values[k])
                {
                    new_image->matriz[i][j] = new_values[k];
                    break;
                }
            }
        }
    }

    free_histogram(hst);
    return new_image;
}










