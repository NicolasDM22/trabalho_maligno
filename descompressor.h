#ifndef DESCOMPRESSOR_H
#define DESCOMPRESSOR_H
#include "tabela_de_frequencias.h"
#include "huffman.h"

boolean descompactar_arquivo(const char* nome_arquivo_comprimido, const char* nome_arquivo_saida);

#endif
