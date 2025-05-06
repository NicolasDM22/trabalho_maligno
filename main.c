#include <stdio.h>
#include "compressor.h"
#include "descompressor.h"

int main()
{
    const char* arquivo_original      = "C:/Users/nicol/CLionProjects/untitled/entrada.txt";
    const char* arquivo_comprimido    = "saida.huff";
    const char* arquivo_descomprimido = "saida_descompactado.txt";

    printf("Compactando o arquivo: %s\n", arquivo_original);
    if (compactar_arquivo(arquivo_original, arquivo_comprimido)) {
        printf("Arquivo compactado com sucesso: %s\n", arquivo_comprimido);
    }
    else {
        printf("Erro ao compactar o arquivo.\n");
        return 1;
    }

    printf("Descompactando o arquivo: %s\n", arquivo_comprimido);
    if (descompactar_arquivo(arquivo_comprimido, arquivo_descomprimido)) {
        printf("Arquivo descompactado com sucesso: %s\n", arquivo_descomprimido);
    }
    else {
        printf("Erro ao descompactar o arquivo.\n");
        return 1;
    }

    return 0;
}
