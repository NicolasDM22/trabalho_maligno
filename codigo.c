#include "codigo.h"
#include <stdlib.h>

boolean novo_codigo(Codigo* c) {
    c->byte = (U8*)malloc(1 * sizeof(U8));
    if (c->byte == NULL) return false;
    c->capacidade = 8;
    c->tamanho = 0;
    return true;
}

void free_codigo(Codigo* c) {
    if (c->byte != NULL) free(c->byte);
}

boolean adiciona_bit(Codigo* c, U8 valor) {
    if (c->tamanho == c->capacidade) {
        U8* novo = (U8*)malloc((c->capacidade / 8 + 1) * sizeof(U8));
        if (novo == NULL) return false;

        for (int i = 0; i < c->capacidade / 8; i++)
            novo[i] = c->byte[i];

        free(c->byte);
        c->byte = novo;
        
        c->capacidade += 8;
    }
    c->byte[c->tamanho / 8] <<= 1;
    if (valor == 1)
        c->byte[c->tamanho / 8] |= 1;
    c->tamanho++;
    return true;
}

boolean joga_fora_bit(Codigo* c) {
    if (c->tamanho == 0) return false;
    c->tamanho--;
    c->byte[c->tamanho / 8] >>= 1;
    return true;
}

boolean clone(Codigo original, Codigo* copia) {
    copia->byte = (U8*)malloc((original.capacidade / 8) * sizeof(U8));
    if (copia->byte == NULL) return false;
    for (int i = 0; i < original.capacidade / 8; i++)
        copia->byte[i] = original.byte[i];
    copia->capacidade = original.capacidade;
    copia->tamanho = original.tamanho;
    return true;
}
