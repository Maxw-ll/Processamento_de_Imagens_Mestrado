#include "image.h"
#include <stdio.h>

Imagem* sum_image_with_image(Imagem* imgA, Imagem* imgB, int sub)
{   
    Imagem* img_result = NULL;
    
    if(imgA->altura == imgB->altura && imgA->largura == imgB->largura && imgA->qtd_bits == imgB->qtd_bits)
    {
        img_result = create_image_gray_scale(imgA->altura, imgA->largura, imgA->qtd_bits);
        if(img_result == NULL)
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }

    for(int i=0; i < imgA->altura; i++)
    {
        for(int j=0; j < imgA->largura; j++)
        {   

            int new_value = 0;
            if(sub == TRUE)
            {
                new_value = imgA->matriz[i][j] - imgB->matriz[i][j];
            }   
            else
            {
                new_value =  imgA->matriz[i][j] + imgB->matriz[i][j];
            }
        
            if(new_value > imgA->qtd_valores - 1)
            {
                img_result->matriz[i][j] = imgA->qtd_valores-1;
            }
            else if(new_value < 0)
            {
                img_result->matriz[i][j] = 0;    
            }
            else
            {
                img_result->matriz[i][j] = new_value;
            }
        }
    }
    return img_result;
}


Imagem* sum_image_with_scale(Imagem* img, int scale)
{
    Imagem* img_scaled = create_image_gray_scale(img->altura, img->largura, img->qtd_bits);

    fill_matriz_with_number(img_scaled, scale, FALSE);

    return sum_image_with_image(img, img_scaled, FALSE);
}



Imagem* multiply_with_scale(Imagem* img, float scale)
{
    Imagem *img_result = create_image_gray_scale(img->altura, img->largura, img->qtd_bits);

    if(img_result == NULL)
    {   
        printf("Imagem não Criada!");
        return NULL;
    }

    for(int i=0; i < img->altura; i++)
    {
        for(int j=0; j < img->largura; j++)
        {
            int new_value = (int)(img->matriz[i][j]*scale);

            if(new_value > img->qtd_valores-1)
            {
                img_result->matriz[i][j] = img->qtd_valores-1;
            }
            else if(new_value < 0)
            {
                img_result->matriz[i][j] = 0;
            }
            else
            {
                img_result->matriz[i][j] = new_value;
            }
        }
    }

    return img_result;
}

Imagem* divide_by_scale(Imagem* img, float scale)
{
    Imagem *img_result = create_image_gray_scale(img->largura, img->altura, img->qtd_bits);

    if(img_result == NULL || scale == 0)
    {
        return NULL;
    }

    for(int i=0; i < img->altura; i++)
    {
        for(int j=0; j < img->largura; j++)
        {
            int new_value = (int)img->matriz[i][j]/scale;

            if(new_value > img->qtd_valores-1)
            {
                img_result->matriz[i][j] = img->qtd_valores-1;
            }
            else if(new_value < 0)
            {
                img_result->matriz[i][j] = 0;
            }
            else
            {
                img_result->matriz[i][j] = new_value;
            }
        }
    }

    return img_result;
}

Imagem* multiply_image_with_image(Imagem *imgA, Imagem* imgB)
{
    if(imgA->largura != imgB->altura || imgA->qtd_bits != imgB->qtd_bits)
    {   
        printf("Imagens com tamanho incompatível para realizar multiplicação\n [A largura da primeira imagem deve ser igual a altura da segunda imagem]");
        return NULL;
    }

    Imagem* img_result = create_image_gray_scale(imgA->altura, imgB->largura, imgA->qtd_bits);

    for(int i=0; i < imgA->altura; i++)
    {
        for(int j=0; j < imgB->largura; j++)
        {   
            int sum_values = 0;
            for(int k=0; k < imgA->largura; k++)
            {
                sum_values += imgA->matriz[i][k]*imgB->matriz[k][j];
            }

            if(sum_values > imgA->qtd_valores-1)
            {
                img_result->matriz[i][j] = imgA->qtd_valores-1;
            }
            else if (sum_values < 0)
            {
                img_result->matriz[i][j] = 0;
            }
            else
            {
                img_result->matriz[i][j] = sum_values;
            }
        }
    }

    return img_result;
}


