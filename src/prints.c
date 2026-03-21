#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "prints.h"



void imprime_pontilhado()
{
    printf("----------------------------------------\n");
}

void imprime_periodo(int ano_ini, int ano_fim)
{
    printf("Período: Janeiro %d a Dezembro %d\n", ano_ini, ano_fim);
}

void imprime_capital_inicial(float capital_inicial)
{
    printf("Capital Inicial: R$ %.2f\n", capital_inicial);
    printf("\n");
}

void imprime_resultado(const char *nome_arquivo, float resposta)
{
    char nome_sem_sufixo[50];

    strcpy(nome_sem_sufixo, nome_arquivo);

    char *ponto = strstr(nome_sem_sufixo, ".");
    if(ponto)
        *ponto = '\0';
        // substitui o ponto por \0 (string vai acabar aqui)
    
    nome_sem_sufixo[0] = toupper(nome_sem_sufixo[0]);
    //deixa a primeira letra em maiúsculo tal como nas diretrizes do trabalho

    printf("%s: R$ %.2f\n", nome_sem_sufixo, resposta);
    
}

void imprime_tam_janela(int janela)
{
    printf("Tamanho da janela: %d meses\n", janela);
    printf("\n");
}

void imprime_nome_arquivo_janela(const char *nome_arquivo)
{
    char nome_sem_sufixo[50];

    strcpy(nome_sem_sufixo, nome_arquivo);

    char *ponto = strstr(nome_sem_sufixo, ".");
    if(ponto)
        *ponto = '\0';
        // substitui o ponto por \0 (string vai acabar aqui)
    
    nome_sem_sufixo[0] = toupper(nome_sem_sufixo[0]);
    //deixa a primeira letra em maiúsculo tal como nas diretrizes do trabalho

    printf("%s:", nome_sem_sufixo);
    
}
