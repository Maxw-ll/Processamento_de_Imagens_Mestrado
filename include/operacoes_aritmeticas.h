
#ifndef ARITMETICAS_H
#define ARITMETICAS_H

#include "image.h"

Imagem* sum_image_with_image(Imagem* imgA, Imagem* imgB, int sub);
Imagem* sum_image_with_scale(Imagem* img, int scale);
Imagem* multiply_with_scale(Imagem* img, float scale);
Imagem* divide_by_scale(Imagem* img, float scale);
Imagem* multiply_image_with_image(Imagem *imgA, Imagem* imgB);

#endif