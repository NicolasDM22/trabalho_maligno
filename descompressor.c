#include "descompressor.h"
#include <stdio.h>
#include <stdlib.h>

static Ptr_de_no_de_arvore_binaria ler_arvore(FILE* arquivo)
{
    int c = fgetc(arquivo);
    if (c == EOF) return NULL;

    if (c == '1')
    {
        int byte_lido = fgetc(arquivo);
        if (byte_lido == EOF) return NULL;

        Ptr_de_no_de_arvore_binaria novo_no = (Ptr_de_no_de_arvore_binaria)malloc(sizeof(Struct_do_no_de_arvore_binaria));
        if (novo_no == NULL) return NULL;

        novo_no->esquerda = NULL;
        novo_no->direita = NULL;
        novo_no->informacao.byte = (U8*)malloc(sizeof(U8));
        *(novo_no->informacao.byte) = (U8)byte_lido;
        novo_no->informacao.frequencia = 0;
        return novo_no;
    }
    else if (c == '0')
    {
        Ptr_de_no_de_arvore_binaria novo_no = (Ptr_de_no_de_arvore_binaria)malloc(sizeof(Struct_do_no_de_arvore_binaria));
        if (novo_no == NULL) return NULL;

        novo_no->esquerda = ler_arvore(arquivo);
        novo_no->direita = ler_arvore(arquivo);
        novo_no->informacao.byte = NULL;
        novo_no->informacao.frequencia = 0;
        return novo_no;
    }

    return NULL;
}

boolean descompactar_arquivo(const char* nome_arquivo_comprimido, const char* nome_arquivo_saida)
{
    FILE* comprimido = fopen(nome_arquivo_comprimido, "rb");
    if (comprimido == NULL) return false;

    // Ler a árvore de Huffman salva
    Ptr_de_no_de_arvore_binaria raiz = ler_arvore(comprimido);

    // Pular o separador '\n'
    int separador = fgetc(comprimido);
    if (separador != '\n')
    {
        fclose(comprimido);
        return false;
    }

    FILE* saida = fopen(nome_arquivo_saida, "wb");
    if (saida == NULL)
    {
        fclose(comprimido);
        return false;
    }

    Ptr_de_no_de_arvore_binaria atual = raiz;
    int byte_lido;
    int contador_bits = 0;

    while ((byte_lido = fgetc(comprimido)) != EOF)
    {
        for (int i = 7; i >= 0; i--)
        {
            int bit = (byte_lido >> i) & 1;

            if (bit == 0)
                atual = atual->esquerda;
            else
                atual = atual->direita;

            if (atual->esquerda == NULL && atual->direita == NULL)
            {
                fputc(*(atual->informacao.byte), saida);
                atual = raiz;
            }
        }
    }

    fclose(comprimido);
    fclose(saida);
    return true;
}
