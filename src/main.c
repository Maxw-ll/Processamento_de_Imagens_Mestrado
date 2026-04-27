#include "image.h"
#include "io.h"
#include "operacoes_aritmeticas.h"
#include "algoritmos_melhoramento.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Função principal
int main(int argc, char const *argv[])
{

    printf("Leitura de Imagem Iniciada\n");
    
    // Carregar as imagens
    Imagem* img_jinx = read_img("zimg/Jinx/JinxGrayScale.png");
    Imagem* img_jinx_lowc = read_img("zimg/Jinx/JinxGrayLowContrast.png");
    Imagem* img_jinx_lowv = read_img("zimg/Jinx/JinxGrayLowValues.png");
    Imagem* mask = read_img("zimg/Jinx/Mascara.png");

    // Criar histograma da imagem
    Histograma* hst = make_histogram(img_jinx);

    // Aplicar os algoritmos de processamento de imagem
    Imagem* result_mapeamento_linear = mapeamento_linear(img_jinx, hst);
    Imagem* result_stretching = stretching(img_jinx, hst);
    Imagem* result_equalizacao = equalizacao(img_jinx, hst);
    Imagem* result_clipping = clipping(img_jinx, 200);

    // Salvar as imagens processadas
    save_img(result_mapeamento_linear, "Jinx_MapeamentoLinear.png");
    save_img(result_stretching, "Jinx_Stretching.png");
    save_img(result_equalizacao, "Jinx_Equalizacao.png");
    save_img(result_clipping, "Jinx_Clipping.png");

     result_mapeamento_linear = mapeamento_linear(img_jinx_lowc, hst);
     result_stretching = stretching(img_jinx_lowc, hst);
     result_equalizacao = equalizacao(img_jinx_lowc, hst);
     result_clipping = clipping(img_jinx_lowc, 200);

    // Salvar as imagens processadas
    save_img(result_mapeamento_linear, "Jinx_MapeamentoLinearLOWC.png");
    save_img(result_stretching, "Jinx_StretchingLOWC.png");
    save_img(result_equalizacao, "Jinx_EqualizacaoLOWC.png");
    save_img(result_clipping, "Jinx_ClippingLOWC.png");

     result_mapeamento_linear = mapeamento_linear(img_jinx_lowv, hst);
     result_stretching = stretching(img_jinx_lowv, hst);
     result_equalizacao = equalizacao(img_jinx_lowv, hst);
     result_clipping = clipping(img_jinx_lowv, 200);

    // Salvar as imagens processadas
    save_img(result_mapeamento_linear, "Jinx_MapeamentoLinearLOWV.png");
    save_img(result_stretching, "Jinx_StretchingLOWV.png");
    save_img(result_equalizacao, "Jinx_EqualizacaoLOWV.png");
    save_img(result_clipping, "Jinx_ClippingLOWV.png");

    

    // Liberar memória
    free_histogram(hst);
    free_image(img_jinx);
    free_image(mask);
    free_image(result_mapeamento_linear);
    free_image(result_stretching);
    free_image(result_equalizacao);
    free_image(result_clipping);

    return 0;
    


}