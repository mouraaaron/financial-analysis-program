#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include "calculos.h"





float calcula_cotacao(Linha *vetor, int n_linhas, int ano_ini, int ano_fim, float capital_inicial)
{
    Linha *inicio = NULL;
    Linha *fim = NULL;

    ano_ini = ano_ini % 100;  // a struct linha guarda o ano apenas como 00 (2000) ou 25 (2025) 
    ano_fim = ano_fim %100;

    for(int i = 0; i < n_linhas; i++)
    {
        if(vetor[i].ano == ano_ini && strstr(vetor[i].mes, "jan"))
        {
            inicio = &vetor[i];
            // aqui, pegamos a struct que tenha o primeiro ano igual ao ano de fim (o mês será dezembro)
        }

        if(vetor[i].ano == ano_fim && strstr(vetor[i].mes, "dez"))
        {
            fim = &vetor[i]; 
        }
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

    ano_ini = ano_ini %100;  // a struct linha guarda o ano apenas como 00 (2000) ou 25 (2025) 
    ano_fim = ano_fim % 100;

    for(int i = 0; i < n_linhas; i++)
    {
        if(vetor[i].ano == ano_ini && strstr(vetor[i].mes, "jan"))
        {
            inicio = &vetor[i];
            // aqui, pegamos a struct que tenha o primeiro ano igual ao ano de fim (o mês será dezembro)
        }

        if(vetor[i].ano == ano_fim && strstr(vetor[i].mes, "dez"))
        {
            fim = &vetor[i]; 
        }
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

float calcula_cotacao_janela(Linha *vetor, int idx_inicio, int idx_fim, float capital) {
    // Não precisa de loop! É só pegar os valores nas posições exatas.
    float v_inicial = vetor[idx_inicio].valor;
    float v_final = vetor[idx_fim].valor;
    return (v_final / v_inicial) * capital;
}

float calcula_taxa_janela(Linha *vetor, int idx_inicio, int idx_fim, float capital) {
    // O loop corre apenas entre as duas posições da janela
    for (int i = idx_inicio; i >= idx_fim; i--) {
        capital *= (1.0 + (vetor[i].valor / 100.0));
    }
    return capital;
}

int* calcula_janelas(Linha **vetor, char **nomes_arquivos, int *n_linhas, int ano_ini, int ano_fim, float capital_inicial, int tam_janela,
     int indice_primeiro_arquivo, int qtd_arquivos)
{
    int *resultado = malloc(qtd_arquivos * sizeof(int));
    if(!resultado)
        return NULL;

    for(int i = 0; i < qtd_arquivos; i++)
    {
        resultado[i] = 0; 
    }
    
    Linha *inicio = NULL;
    Linha *fim = NULL;

    int ano_inicial = ano_ini - 2000; 
    int ano_final = ano_fim - 2000; 
    // Aqui, tive que criar 2 outras novas variáveis para o ano, por que calcula_cotação e calcula_taxa já fazem 
    // -2000 nos anos. Se fizer -2000 duas vezes aí as funções não conseguem calcular o resultado.

    Linha *vetor_ref = vetor[0];

    //vamos usar a mesma lógica para encontrar os ponteiros de início e de fim para após isso, calcular as janelas.
    printf("DEBUG BUSCA: Procurando Jan/%d e Dez/%d\n", ano_ini % 100, ano_fim % 100);
    for(int i = 0; i < n_linhas[0]; i++) 
    {

        if(i == 0) printf("EXEMPLO NO VETOR: Mes=[%s] Ano=[%d]\n", vetor[0][i].mes, vetor[0][i].ano);

        int ano_v = vetor[0][i].ano;
        char *mes_v = vetor[0][i].mes;
        
        if(vetor[0][i].ano == ano_ini && strstr(vetor[0][i].mes, "jan")) 
        {
            inicio = &vetor[0][i];
            printf("DEBUG: Achei Inicio em indice %d\n", i);
        }

        if(vetor[0][i].ano == ano_fim && strstr(vetor[0][i].mes, "dez"))
        {
            fim = &vetor[0][i];
            printf("DEBUG: Achei Fim em indice %d\n", i);
        } 
    }

    if (!inicio || !fim) //tratamento de erro
    {
        printf("ERRO: Inicio=%p, Fim=%p (Se NULL, nao encontrou)\n", (void*)inicio, (void*)fim);
        return resultado;
    }

    int distancia = (int)(inicio - fim) + 1;

    for (int deslize = 0; deslize <= distancia - tam_janela; deslize++)
    {
        Linha *janela_inicio = inicio - deslize;
        Linha *janela_fim = janela_inicio - (tam_janela - 1);

        float melhor_retorno = -100000.00; 
        int indice_vencedor = -1;

        for(int u = 0; u < qtd_arquivos; u++)
        {
            float retorno; 

            if(eh_cot(nomes_arquivos[indice_primeiro_arquivo + u]))
            {
                retorno = calcula_cotacao_janela(vetor[u], janela_inicio->ano, janela_fim->ano, capital_inicial);
            }
            else
            {
                retorno = calcula_taxa_janela(vetor[u], janela_inicio->ano, janela_fim->ano, capital_inicial);
            }

            if(retorno > melhor_retorno)
            {
                melhor_retorno = retorno; 
                indice_vencedor = u;
            }
        }
        if(indice_vencedor != -1) //evitra segfault
            resultado[indice_vencedor]++;
    }
    return resultado;
}
 
