#include "fila_prioridade.h"

void ordena_fila_por_frequencia(Tabela_de_frequencias* tab)
{
    junte_nodos_no_inicio_do_vetor(tab);

    for (U16 i = 1; i < tab->quantidade_de_posicoes_preenchidas; i++)
    {
        Ptr_de_no_de_arvore_binaria atual = tab->vetor[i];
        U16 j = i;

        while (j > 0 && tab->vetor[j - 1]->informacao.frequencia > atual->informacao.frequencia)
        {
            tab->vetor[j] = tab->vetor[j - 1];
            j--;
        }

        tab->vetor[j] = atual;
    }
}
