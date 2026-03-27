
/*
#######################################################

Aluno: MAXWELL PIRES SILVA
Professor: ARISTOFANES CORREA SILVA
Disciplina: PROCESSAMENTO DE IMAGEM E VISÃO COMPUTACIONAL 

########################################################
*/

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image_write.h"
#include "stb_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define FALSE 0
#define TRUE 1

/*
#######################################################

                FUNÇÕES DE IMAGEM

#######################################################
*/

//Estrutura da imagem
typedef struct
{
    int** matriz; //Valores da imagem
    int altura; //Altura
    int largura; //Largura
    int qtd_bits; //Níveis de intensidade em bits
    int qtd_valores; //Quantidade de valores
} Imagem;

typedef struct
{
    int* histogram;
    int* acumuleted_histogram;
    int tam;
} Histograma;

//Cria a imagem
Imagem* create_image_gray_scale(int altura, int largura, int n_bits)
{
    Imagem* this_image = (Imagem*)malloc(sizeof(Imagem));
    if(this_image == NULL)
    {
        return NULL;
    }
    
    int** this_matriz = (int**)malloc(sizeof(int*) * largura);

    if(this_matriz == NULL)
    {
        return NULL;
    }
    
    for(int i=0; i < altura; i++)
    {   
        int* my_col = (int*)malloc(sizeof(int) * largura);
        if(my_col == NULL)
        {
            return NULL;
        }
        this_matriz[i] = my_col;
    }
    
    this_image -> matriz = this_matriz;
    this_image -> altura = altura;
    this_image -> largura = largura;
    this_image -> qtd_bits = n_bits;
    this_image -> qtd_valores = (int)pow(2, n_bits);

    return this_image;
}


//Imprime a imagem no terminal
void show_image(Imagem *img)
{   
    printf("[Image: %d bits | %d valores]\n", img->qtd_bits, img->qtd_valores);
    for(int i=0; i < img->altura; i++)
    {
        for(int j=0; j < img->largura; j++)
        {
            int pixel = img->matriz[i][j];
            printf("%d\t", pixel);
        }
        printf("\n");
    }
}

//Preenche a matriz com valores entre 0 e o valor limite
void fill_matriz_with_random(Imagem* img)
{

    for(int i=0; i < img->altura; i++)
    {
        for(int j=0; j < img->largura; j++)
        {
            img->matriz[i][j] = rand() % (int)pow(2, img->qtd_bits);
        }
    }
}


/*
#######################################################

            FUNÇÕES DE PROCESSAMENTO

#######################################################
*/

//Quantização uniforme. Valores atribuídos fixos e divisão pela quantidade de bits
Imagem* make_uniform_quantization(Imagem* img, int n_bits)
{
    int n_faixas = (int)pow(2, n_bits);
    int new_values[n_faixas];
    int limit_values[n_faixas];
    
    int qtd_val = img->qtd_valores;
    
    
    for(int i=0; i < n_faixas; i++)
    {
        new_values[i] = (qtd_val/n_faixas) * i;
        limit_values[i] = ((qtd_val/n_faixas) * (i + 1)) - 1;
    }
    
    Imagem* new_image = create_image_gray_scale(img->altura, img->largura, n_bits);
    
    if(new_image == NULL)
    {
        return NULL;
    }
    
    for(int i=0; i < img->altura; i++)
    {
        for(int j=0; j < img->largura; j++)
        {   
            
            for(int k=0; k<n_faixas; k++)
            {
                if(img->matriz[i][j] <= limit_values[k])
                {
                    new_image->matriz[i][j] = new_values[k];
                    break;
                }
            }
        }
    }
    
    return new_image;
}


//Fazer o Histograma
Histograma* make_histogram(Imagem* img)
{
    Histograma* hst = (Histograma*)malloc(sizeof(Histograma));

    hst->histogram = (int*)malloc(sizeof(int)*img->qtd_valores);
    hst->acumuleted_histogram = (int*)malloc(sizeof(int)*img->qtd_valores);
    hst->tam = img->qtd_valores;

    //Zerar valores dos histogramas
    for(int i=0; i < img->qtd_valores; i++)
    {
        hst->histogram[i] = 0;
        hst->acumuleted_histogram[i] = 0;
    }
    
    //Preenche-los da forma correta
    for(int i=0; i < img->altura; i++)
    {
        for(int j=0; j < img->largura; j++)
        {
            int value = img->matriz[i][j];
            hst->histogram[value] += 1;
        }
    }

    int sum_hist = 0;

    for(int i=0; i < hst->tam; i++)
    {   
        sum_hist += hst->histogram[i];
        hst->acumuleted_histogram[i] = sum_hist;
    }
    
    return hst;
}

void imprime_vetor(int* vector, int tam)
{   
    printf("\n");
    for(int i=0; i < tam; i++)
    {
        printf(" %d", vector[i]);
    }
    printf("\n");
}

//Transforma a matriz da imagem em um vetor para depois ser salva
unsigned char* create_img_data_vector(Imagem* img)
{
    unsigned char* img_vector = (unsigned char*)malloc(sizeof(unsigned char) * img->altura * img->largura);

    if(img_vector == NULL)
    {
        return NULL;
    }

    int idx_vector = 0;

    for(int i=0; i < img->altura; i++)
    {
        for(int j=0; j < img->largura; j++)
        {
            img_vector[idx_vector] = (unsigned char)img->matriz[i][j];
            idx_vector++;
        }
    }

    return img_vector;

}

//Salvar a imagem
void save_img(Imagem* img, char* name)
{
    unsigned char* img_data = create_img_data_vector(img);
    stbi_write_png(name, img->largura, img->altura, 1, img_data, img->largura);
}


void save_histogram(Histograma* hst, char* path_to_save)
{
    int maior_frequencia = 0;

    for(int i=0; i < hst->tam; i++)
    {
        if(hst->histogram[i] > maior_frequencia)
        {
            maior_frequencia = hst->histogram[i];
        }
    }
    
    Imagem* img_histogram = create_image_gray_scale(maior_frequencia, hst->tam, 8);

    for(int j=0; j < hst->tam; j++)
    {   
        for(int i = 0; i < maior_frequencia; i++)
        {   
            img_histogram->matriz[i][j] = hst->tam-1;
            if(maior_frequencia - i <= hst->histogram[j])
            {
                img_histogram->matriz[i][j] = 0;
            }
            
        }
    }
    save_img(img_histogram, path_to_save);
}
    




//Quantização que leva em conta a distribuição do histograma e procura equilibrar a quantidade de valores em cada faixa
Imagem* make_equality_frequence_distribution_quantization(Imagem* img, int n_bits)
{   
    Imagem* new_image = create_image_gray_scale(img->altura, img->largura, n_bits);
    
    Histograma* hst = make_histogram(img);

    int* histogram = hst->histogram;

    save_histogram(hst, "Histograma.png");
    
    if(new_image == NULL || histogram == NULL)
    {
        return NULL;
    }

    int n_faixas = (int)pow(2, n_bits);
    int new_values[n_faixas];
    int limit_values[n_faixas-1];
    
    int count_values = 0;
    int sum_values = 0;
    int counter_for_values = 0;
    
    for(int i=0; i < img->qtd_valores; i++)
    {
        
        count_values += histogram[i];
        sum_values += histogram[i] * i;
        
        if(count_values >= (img->altura * img->largura )/n_faixas)
        {
            new_values[counter_for_values] = sum_values/count_values;
            limit_values[counter_for_values] = i;
            count_values = 0;
            sum_values = 0;
            counter_for_values += 1; 
        }

        if(counter_for_values == n_faixas - 1 && i == img->qtd_valores-1)
        {
            limit_values[counter_for_values] = img->qtd_valores;
            new_values[counter_for_values] = sum_values/count_values;
        }
        
    }

    imprime_vetor(limit_values, n_faixas);
    imprime_vetor(new_values, n_faixas);

    for(int i=0; i < img->altura; i++)
    {
        for(int j=0; j < img->largura; j++)
        {   
            for(int k=0; k < n_faixas; k++)
            {
                if(img->matriz[i][j] <= limit_values[k])
                {
                    new_image->matriz[i][j] = new_values[k];
                    break;
                }
                
            }
        }
    }
    
    return new_image;
    
}


/*
#######################################################

            FUNÇÕES DE LEITURA E ESCRITA

#######################################################
*/


//ler uma imagem em grayscale
Imagem* read_img(char* path_img)
{   
    int largura, altura, canais;
    //Caminho da imagem | largura | altura | quantidade de canais devolvidos | quantidade de canais desejados
    unsigned char* img_vector = stbi_load(path_img, &largura, &altura, &canais, 1);
    if(img_vector == NULL)
    {
        return NULL;
    }
    
    Imagem* new_image = create_image_gray_scale(altura, largura, 8);
    printf("Quantidade de Canais: %d\n", canais);
    printf("Altura: %d\n", altura);
    printf("Largura: %d\n", largura);

    for(int i=0; i < altura; i++)
    {
        for(int j=0; j < largura; j++)
        {
            new_image->matriz[i][j] = (int)img_vector[i * largura + j];
        }
    }
    return new_image;
}








//Função principal
int main(int argc, char const *argv[])
{

    /*
    //PIPELINE COM IMAGEM GERADA ALEATORIA
    srand(time(NULL));
    
    Imagem* my_image = create_image_gray_scale(16, 16, 8);
    
    if(my_image == NULL)
    {
        printf("Imagem nao criada!");
        return 0;
    }
    
    fill_matriz_with_random(my_image);
    //show_image(my_image);
    save_img(my_image, "img_random/Imagem_normal.png");
    
    
    Imagem* new_uniform_image = make_uniform_quantization(my_image, 1);
    printf("\n Quantizacao Uniforme\n");
    //show_image(new_uniform_image);
    save_img(new_uniform_image, "img_random/Imagem_uniforme.png");
    
    
    Imagem* new_no_uniform_image = make_equality_frequence_distribution_quantization(my_image, 1);
    printf("\n Quantizacao Nao Uniforme\n");
    //show_image(new_no_uniform_image);
    save_img(new_no_uniform_image, "img_random/Imagem_nao_uniforme.png");
    */
    
    printf("Leitura de Imagem Iniciada\n");
    Imagem* img_jinx = read_img("jinx_omg\\Eye\\Eye.png");
    
    printf("Quantizacaoo Iniciada\n");
    //Imagem* img_jinx_uniform_quant = make_uniform_quantization(img_jinx, 2);
    //save_img(img_jinx_uniform_quant, "jinx_omg/JinxAll_Quant_Uniform_2bits.png");
    Imagem* img_jinx_no_uniform_quant = make_equality_frequence_distribution_quantization(img_jinx, 4);
    //save_img(img_jinx_no_uniform_quant, "jinx_omg/JinxAll_Quant_NoUniform_4bits.png");

}


