#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "vetor.h"



/*
dez./25 5,34 -> esse é um exemplo de entrada. A linguagem C não vai entender 5,34 como
um float pois está com uma vírgula. Precisamos trocar essa vírgula por um ponto (.) em
todos os arquivos.
*/

void troca_virgula(char *string)
{
    for(int i = 0; string[i]!= '\0'; i++)
    {
        if(string[i] == ',' )
            string[i] = '.';
    }
}

Linha* preencher_vetor(const char *nome_arquivo, int *n_linhas)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    if(!arquivo)
    {
        *n_linhas = -1;
        return NULL;
    }

    // primeiro, vamos declarar o vetor com 10 espaços. Caso exceda, dobramos a qtd de linhas
    
    int teto = 10; 
    int contagem_linhas = 0; 

    Linha *vetor = malloc(teto * sizeof(Linha));
    if(!vetor)
    {
        *n_linhas = -2;
        fclose(arquivo);
        return NULL; 
    }

    char armazem_temporario[25];

    while(fgets(armazem_temporario, sizeof(armazem_temporario), arquivo))
    {
        if(contagem_linhas >= teto)
        {
            teto *= 2;
            Linha *temp = realloc(vetor, teto * sizeof(*vetor));
            vetor = temp; 
        }
            
        char mes_linha_arquivo[5];
        char valor_linha_arquivo[10];
        int ano;

        //O sscanf retorna quantos itens ele conseguiu ler
        if(sscanf(armazem_temporario, "%[^.]./%d %s", mes_linha_arquivo, &ano ,valor_linha_arquivo) == 3)
        {
            strcpy(vetor[contagem_linhas].mes, mes_linha_arquivo);
            vetor[contagem_linhas].ano = ano;
            troca_virgula(valor_linha_arquivo);
            vetor[contagem_linhas].valor = atof(valor_linha_arquivo);

            contagem_linhas++;
        }
    }

    *n_linhas = contagem_linhas;

    if (contagem_linhas > 0) {
        Linha *temp = realloc(vetor, contagem_linhas * sizeof *vetor);
        if (temp)
            vetor = temp;
    } else {
        free(vetor);
        vetor = NULL;
    }

    return vetor;
    
}

bool eh_cot(const char *nome_arquivo)
{
    if(strstr(nome_arquivo, ".cot") != NULL)
        return true;
        
    return false;

}
