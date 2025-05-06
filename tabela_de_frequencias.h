#ifndef TABELA_DE_FREQUENCIAS_H
#define TABELA_DE_FREQUENCIAS_H

#include "meustiposonlinegdb.h"

// Elemento armazenando byte e sua frequência
typedef struct {
    U8 *byte;
    U64 frequencia;
} Elemento;

// Nó na árvore binária de Huffman
typedef struct Struct_do_no_de_arvore_binaria {
    struct Struct_do_no_de_arvore_binaria *esquerda;
    Elemento informacao;
    struct Struct_do_no_de_arvore_binaria *direita;
} Struct_do_no_de_arvore_binaria;

// Ponteiro para nó de árvore
typedef Struct_do_no_de_arvore_binaria *Ptr_de_no_de_arvore_binaria;

// Tabela de frequências dos 256 possíveis valores de byte
typedef struct {
    Ptr_de_no_de_arvore_binaria vetor[256];
    U16 quantidade_de_posicoes_preenchidas;
} Tabela_de_frequencias;

// Protótipos de funções
void    nova_tabela_de_frequencias         (Tabela_de_frequencias *tab);
boolean inclua_byte                        (U8 byte, Tabela_de_frequencias *tab);
void    junte_nodos_no_inicio_do_vetor     (Tabela_de_frequencias *tab);

#endif // TABELA_DE_FREQUENCIAS_H
