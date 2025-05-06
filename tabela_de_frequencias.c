#include <stdlib.h>
#include "tabela_de_frequencias.h"

// Inicializa a tabela zerando vetores e contador
void nova_tabela_de_frequencias(Tabela_de_frequencias* tab) {
    tab->quantidade_de_posicoes_preenchidas = 0;
    for (int i = 0; i < 256; i++) {
        tab->vetor[i] = NULL;
    }
}

// Inclui um byte na tabela: se já existir, incrementa; senão, cria um novo nó
boolean inclua_byte(U8 byte, Tabela_de_frequencias* tab) {
    // busca por nó existente
    for (U16 i = 0; i < tab->quantidade_de_posicoes_preenchidas; i++) {
        Ptr_de_no_de_arvore_binaria no = tab->vetor[i];
        if (*(no->informacao.byte) == byte) {
            no->informacao.frequencia++;
            return true;
        }
    }
    // cria novo nó de folha
    Ptr_de_no_de_arvore_binaria novo = malloc(sizeof(*novo));
    if (!novo) return false;
    novo->esquerda = novo->direita = NULL;
    // armazena o byte
    novo->informacao.byte = malloc(sizeof(*(novo->informacao.byte)));
    if (!novo->informacao.byte) {
        free(novo);
        return false;
    }
    *(novo->informacao.byte) = byte;
    novo->informacao.frequencia = 1;
    // insere no vetor
    tab->vetor[tab->quantidade_de_posicoes_preenchidas++] = novo;
    return true;
}

// Recompacta o vetor movendo todos os nós não-NULL para o início
void junte_nodos_no_inicio_do_vetor(Tabela_de_frequencias* tab) {
    U16 write = 0;
    for (U16 read = 0; read < 256; read++) {
        if (tab->vetor[read] != NULL) {
            tab->vetor[write++] = tab->vetor[read];
        }
    }
    // preenche o restante com NULL
    for (U16 i = write; i < 256; i++) {
        tab->vetor[i] = NULL;
    }
    tab->quantidade_de_posicoes_preenchidas = write;
}
