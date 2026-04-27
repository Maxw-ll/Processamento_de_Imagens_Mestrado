
#ifndef ALG_MELHORAMENTO
#define ALG_MELHORAMENTO

#include "image.h"
#include "histograma.h"

Imagem* mapeamento_linear(Imagem* img, Histograma* hst);
Imagem* stretching(Imagem* img, Histograma* hst);
Imagem* equalizacao(Imagem* img, Histograma* hst);
Imagem* clipping(Imagem* img, int limite);

#endif