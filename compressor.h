#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <stdio.h>                    // para FILE
#include "tabela_de_frequencias.h"
#include "huffman.h"
#include "codigo.h"

// Prototipo da função de compressão
boolean compactar_arquivo(const char* nome_arquivo_original,
                          const char* nome_arquivo_comprimido);

// Prototipo da função que grava a árvore no arquivo
void salvar_arvore(FILE* arquivo,
                   Ptr_de_no_de_arvore_binaria raiz);

#endif  // COMPRESSOR_H
