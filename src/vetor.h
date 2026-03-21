#ifndef VETOR_H
#define VETOR_H
#include <stdio.h>
#include <stdbool.h>


/*
Para facilitar alocação dinâmica e armazenar dados de diferentes tipos em uma
matriz, vamos implementar a matriz como um vetor de structs de n linhas e 3 colunas
*/


typedef struct
{
    char mes[10];
    int ano;
    float valor;

} Linha;


void troca_virgula(char *string);

Linha* preencher_vetor(const char *nome_arquivo, int *n_linhas);

bool eh_cot(const char *nome_arquivo);

#endif
