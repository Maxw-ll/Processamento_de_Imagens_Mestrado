#include "image.h"
#include "io.h"
#include "operacoes_aritmeticas.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Função principal
int main(int argc, char const *argv[])
{

    /*
    
    printf("Quantizacaoo Iniciada\n");
    Imagem* img_jinx_uniform_quant = make_uniform_quantization(img_jinx, 2);
    save_img(img_jinx_uniform_quant, "jinx_omg/JinxAll_Quant_Uniform_2bits.png");
    Imagem* img_jinx_no_uniform_quant = make_equality_frequence_distribution_quantization(img_jinx, 4);
    save_img(img_jinx_no_uniform_quant, "jinx_omg/JinxAll_Quant_NoUniform_4bits.png");
    */
   
    printf("Leitura de Imagem Iniciada\n");
    Imagem* img_jinx = read_img("zimg/Jinx/JinxGrayScale.png");


    Imagem* mask = read_img("zimg/Jinx/Mascara.png");
    Imagem* result;


    result = multiply_image_with_image(img_jinx, mask);
    save_img(result, "JinxAll_MultMask.png");
    
    


}