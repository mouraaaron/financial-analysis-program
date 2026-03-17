#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include "calculos.h"





float calcula_cotacao(Linha *vetor, int n_linhas, int ano_ini, int ano_fim, float capital_inicial)
{
    Linha *inicio = NULL;
    Linha *fim = NULL;

    ano_ini = ano_ini - 2000;  // a struct linha guarda o ano apenas como 00 (2000) ou 25 (2025) 
    ano_fim = ano_fim - 2000;

    for(int i = 0; i < n_linhas; i++)
    {
        if(vetor[i].ano == ano_fim && fim == NULL)
        {
            fim = &vetor[i];
            // aqui, pegamos a struct que tenha o primeiro ano igual ao ano de fim (o mês será dezembro)
        }

        if(vetor[i].ano == ano_ini && inicio == NULL)
        {
            inicio = &vetor[i+ 11]; //!!possível segfault

            // aqui, pegamos a struct que tenha o primeiro ano igual ao ano de inicio + 11 posições (o mês será janeiro)
        }

        if (inicio && fim)
            break;
    }


    if (!inicio || !fim) //tratamento de erro
    {
        printf("Erro: nao foi possivel encontrar o periodo solicitado no arquivo\n");
        return capital_inicial;
    }

    float D = (capital_inicial)/(inicio->valor);

    float resposta = D * (fim->valor);
    return resposta; 
    
}

float caulcula_taxa(Linha *vetor, int n_linhas, int ano_ini, int ano_fim, float capital_inicial)
{
    Linha *inicio = NULL;
    Linha *fim = NULL;

    ano_ini = ano_ini - 2000;  // a struct linha guarda o ano apenas como 00 (2000) ou 25 (2025) 
    ano_fim = ano_fim - 2000;

    for(int i = 0; i < n_linhas; i++)
    {
        if(vetor[i].ano == ano_fim && fim == NULL)
        {
            fim = &vetor[i];
            // aqui, pegamos a struct que tenha o primeiro ano igual ao ano de fim (o mês será dezembro)
        }

        if(vetor[i].ano == ano_ini && inicio == NULL)
        {
            inicio = &vetor[i+ 11]; //!!possível segfault

            // aqui, pegamos a struct que tenha o primeiro ano igual ao ano de inicio + 11 posições (o mês será janeiro)
        }

        if (inicio && fim)
            break;
    }


    if (!inicio || !fim) //tratamento de erro
    {
        printf("Erro: nao foi possivel encontrar o periodo solicitado no arquivo\n");
        return capital_inicial;
    }
    //agora que encontramos o inicio e o fim, vamos utilizar a logica de calculo de taxas

    float capital = capital_inicial;

    Linha *ptr = inicio; 

    while(ptr >= fim)
    {
        float taxa_anual = ptr->valor;
        float taxa_mensal = pow(1 + taxa_anual / 100.0, 1.0/12.0) - 1;
        capital *= (1 + taxa_mensal);
        ptr--; 
    }

    return capital;
}

int* calcula_janelas(Linha *vetor1, const char *nome_1, Linha *vetor2, const char *nome_2,
    int n_linhas, int ano_ini, int ano_fim, float capital_inicial, int tam_janela)
{
    int *resultado = malloc(2 * sizeof(int));
    if(!resultado)
        return NULL;

    resultado[0] = 0;
    resultado[1] = 0;

    Linha *inicio = NULL;
    Linha *fim = NULL;

    ano_ini = ano_ini - 2000; 
    ano_fim = ano_fim - 2000; 

    //vamos usar a mesma lógica para encontrar os ponteiros de início e de fim para após isso, calcular as janelas.
    for(int i = 0; i < n_linhas; i++)
    {
        if(vetor1[i].ano == ano_fim && fim == NULL)
        {
            fim = &vetor1[i];
            // aqui, pegamos a struct que tenha o primeiro ano igual ao ano de fim (o mês será dezembro)
        }

        if(vetor1[i].ano == ano_ini && inicio == NULL)
        {
            inicio = &vetor1[i+ 11]; //!!possível segfault

            // aqui, pegamos a struct que tenha o primeiro ano igual ao ano de inicio + 11 posições (o mês será janeiro)
        }

        if (inicio && fim)
            break;
    }


    if (!inicio || !fim) //tratamento de erro
    {
        printf("Erro: nao foi possivel encontrar o periodo solicitado no arquivo\n");
        return NULL;
    }

    int distancia = inicio - fim;

    for (int deslize = 0; deslize <= distancia - tam_janela; deslize++)
    {
        Linha *janela_inicio = inicio - deslize;
        Linha *janela_fim = janela_inicio - (tam_janela - 1);

        float resp1, resp2;

        if (eh_cot(nome_1))
        {
            resp1 = calcula_cotacao(vetor1, n_linhas, janela_inicio->ano, janela_fim->ano,capital_inicial);
        }
        else
        {
            resp1 = calcula_taxa(vetor1, n_linhas, janela_inicio->ano, janela_fim->ano, capital_inicial);
        }

        if (eh_cot(nome_2))
        {
            resp2 = calcula_cotacao(vetor2, n_linhas, janela_inicio->ano, janela_fim->ano, capital_inicial);
        }
        else
        {
            resp2 = calcula_taxa(vetor2, n_linhas, janela_inicio->ano, janela_fim->ano, capital_inicial);
        }

        if (resp1 > resp2)
            resultado[0]++;
        else if (resp2 > resp1)
            resultado[1]++;
    }

    return resultado;
}

 