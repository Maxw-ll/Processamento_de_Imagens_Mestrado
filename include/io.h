#ifndef IO_H
#define IO_H

#include "image.h"

unsigned char* create_img_data_vector(Imagem* img);
void save_img(Imagem* img, char* name);
Imagem* read_img(char* path_img);

#endif