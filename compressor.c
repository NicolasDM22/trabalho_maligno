#include "compressor.h"
#include <stdio.h>
#include <stdlib.h>

void salvar_arvore(FILE* arquivo, Ptr_de_no_de_arvore_binaria raiz)
{
    if (raiz == NULL) return;

    if (raiz->esquerda == NULL && raiz->direita == NULL)
    {
        fputc('1', arquivo); // Nó folha
        fputc(*raiz->informacao.byte, arquivo); // Byte armazenado
    }
    else
    {
        fputc('0', arquivo); // Nó interno
        salvar_arvore(arquivo, raiz->esquerda);
        salvar_arvore(arquivo, raiz->direita);
    }
}

boolean compactar_arquivo(const char* nome_arquivo_original, const char* nome_arquivo_comprimido)
{
    FILE* original = fopen(nome_arquivo_original, "rb");
    if (original == NULL) return false;

    // Primeira leitura: contar frequências
    Tabela_de_frequencias tab;
    nova_tabela_de_frequencias(&tab);

    int byte_lido;
    while ((byte_lido = fgetc(original)) != EOF)
    {
        inclua_byte((U8)byte_lido, &tab);
    }

    // Gerar árvore de Huffman
    Ptr_de_no_de_arvore_binaria raiz = monte_arvore_huffman(&tab);
    if (raiz == NULL)
    {
        fclose(original);
        return false;
    }

    // Gerar códigos
    Codigo codigos[256];
    for (int i = 0; i < 256; i++)
        codigos[i].byte = NULL;

    Codigo atual;
    novo_codigo(&atual);
    gera_codigos(raiz, codigos, &atual);
    free_codigo(&atual);

    // Recomeçar o arquivo
    rewind(original);

    FILE* comprimido = fopen(nome_arquivo_comprimido, "wb");
    if (comprimido == NULL)
    {
        fclose(original);
        return false;
    }

    // Primeiro salva a árvore no começo do arquivo
    salvar_arvore(comprimido, raiz);
    fputc('\n', comprimido); // Um separador especial

    U8 buffer = 0;
    int bits_no_buffer = 0;

    while ((byte_lido = fgetc(original)) != EOF)
    {
        Codigo* c = &codigos[(U8)byte_lido];

        for (int i = 0; i < c->tamanho; i++)
        {
            U8 posicao_byte = i / 8;
            U8 posicao_bit = 7 - (i % 8);
            U8 bit = (c->byte[posicao_byte] >> posicao_bit) & 1;

            buffer = (buffer << 1) | bit;
            bits_no_buffer++;

            if (bits_no_buffer == 8)
            {
                fputc(buffer, comprimido);
                buffer = 0;
                bits_no_buffer = 0;
            }
        }
    }

    // Escrever o restante se sobrar bits
    if (bits_no_buffer > 0)
    {
        buffer <<= (8 - bits_no_buffer);
        fputc(buffer, comprimido);
    }

    fclose(original);
    fclose(comprimido);
    return true;
}
