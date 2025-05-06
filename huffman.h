#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "tabela_de_frequencias.h"
#include "codigo.h"

Ptr_de_no_de_arvore_binaria monte_arvore_huffman(Tabela_de_frequencias* tab);
void gera_codigos(Ptr_de_no_de_arvore_binaria raiz, Codigo codigos[256], Codigo* atual);

#endif
