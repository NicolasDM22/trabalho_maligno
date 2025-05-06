#include "huffman.h"
#include "fila_prioridade.h"
#include <stdlib.h>

Ptr_de_no_de_arvore_binaria monte_arvore_huffman(Tabela_de_frequencias* tab)
{
    ordena_fila_por_frequencia(tab);

    while (tab->quantidade_de_posicoes_preenchidas > 1)
    {
        Ptr_de_no_de_arvore_binaria primeiro = tab->vetor[0];
        Ptr_de_no_de_arvore_binaria segundo = tab->vetor[1];

        Elemento novo_elem;
        novo_elem.byte = NULL;
        novo_elem.frequencia = primeiro->informacao.frequencia + segundo->informacao.frequencia;

        Ptr_de_no_de_arvore_binaria novo_no = (Ptr_de_no_de_arvore_binaria)malloc(sizeof(Struct_do_no_de_arvore_binaria));
        if (novo_no == NULL) return NULL;

        novo_no->informacao = novo_elem;
        novo_no->esquerda = primeiro;
        novo_no->direita = segundo;

        U8 posicao_certa = 255;
        for (U16 i = 0; i < tab->quantidade_de_posicoes_preenchidas - 1; i++) {
            if (novo_elem.frequencia <= tab->vetor[i]->informacao.frequencia) {
                tab->vetor[i] = tab->vetor[i + 2];
            } else {
                if (posicao_certa == 255) {
                    posicao_certa = i;
                }
                tab->vetor[i + 1] = tab->vetor[i + 2];
            }
        }
        
        if (posicao_certa == 255) {
            posicao_certa = tab->quantidade_de_posicoes_preenchidas - 2;
        }
        
        tab->vetor[posicao_certa] = novo_no;
        tab->vetor[tab->quantidade_de_posicoes_preenchidas - 1] = NULL;
        tab->quantidade_de_posicoes_preenchidas--;
    }

    return tab->vetor[0];
}

void gera_codigos(Ptr_de_no_de_arvore_binaria raiz, Codigo codigos[256], Codigo* atual)
{
    if (raiz == NULL)
        return;

    if (raiz->esquerda == NULL && raiz->direita == NULL)
    {
        clone(*atual, &codigos[*raiz->informacao.byte]);
        return;
    }

    adiciona_bit(atual, 0);
    gera_codigos(raiz->esquerda, codigos, atual);
    joga_fora_bit(atual);

    adiciona_bit(atual, 1);
    gera_codigos(raiz->direita, codigos, atual);
    joga_fora_bit(atual);
}

