#ifndef QUANTIZATION_H
#define QUANTIZATION_H

#include "image.h"

Imagem* make_uniform_quantization(Imagem* img, int n_bits);
Imagem* make_equality_frequence_distribution_quantization(Imagem* img, int n_bits);

#endif