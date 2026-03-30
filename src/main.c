#include "image.h"
#include "io.h"
#include "quantizacao.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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
    Imagem* img_jinx = read_img("zimg\\Eye\\Eye.png");
    
    printf("Quantizacaoo Iniciada\n");
    //Imagem* img_jinx_uniform_quant = make_uniform_quantization(img_jinx, 2);
    //save_img(img_jinx_uniform_quant, "jinx_omg/JinxAll_Quant_Uniform_2bits.png");
    Imagem* img_jinx_no_uniform_quant = make_equality_frequence_distribution_quantization(img_jinx, 4);
    //save_img(img_jinx_no_uniform_quant, "jinx_omg/JinxAll_Quant_NoUniform_4bits.png");
}