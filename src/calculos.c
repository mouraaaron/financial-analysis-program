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

    ano_ini = ano_ini % 100;
    ano_fim = ano_fim % 100;

    for (int i = 0; i < n_linhas; i++)
    {
        if (vetor[i].ano == ano_ini && strstr(vetor[i].mes, "jan"))
            inicio = &vetor[i];

        if (vetor[i].ano == ano_fim && strstr(vetor[i].mes, "dez"))
            fim = &vetor[i];
    }

    if (!inicio || !fim)
    {
        printf("Erro: nao foi possivel encontrar o periodo solicitado no arquivo\n");
        return capital_inicial;
    }

    float capital = capital_inicial;

    for (Linha *ptr = inicio; ptr >= fim; ptr--)
    {
        float taxa_mensal = pow(1.0 + ptr->valor, 1.0 / 12.0) - 1.0;
        capital *= (1.0f + taxa_mensal);
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
        float taxa_mensal = pow(1.0 + vetor[i].valor, 1.0 / 12.0) - 1.0;
        capital *= (1.0f + taxa_mensal);
    }
    return capital;
}

int *calcula_janelas(Linha **vetor, char **nomes_arquivos, int *n_linhas, int ano_ini, 
    int ano_fim, float capital_inicial, int tam_janela, int indice_primeiro_arquivo, int qtd_arquivos)
{
    int *resultado = malloc(qtd_arquivos * sizeof(int));
    if (!resultado)
        return NULL;
 
    for (int i = 0; i < qtd_arquivos; i++)
        resultado[i] = 0;
 
    
    int ano_ini_2d = ano_ini % 100;
    int ano_fim_2d = ano_fim % 100;
 
    int idx_inicio = -1; /* indice do jan/ano_ini no vetor de referencia */
    int idx_fim    = -1; /* indice do dez/ano_fim no vetor de referencia */
 
    for (int i = 0; i < n_linhas[0]; i++)
    {
        if (vetor[0][i].ano == ano_ini_2d && strstr(vetor[0][i].mes, "jan"))
            idx_inicio = i;
 
        if (vetor[0][i].ano == ano_fim_2d && strstr(vetor[0][i].mes, "dez"))
            idx_fim = i;
    }
 
    if (idx_inicio == -1 || idx_fim == -1)
    {
        printf("ERRO: periodo nao encontrado no vetor de referencia\n");
        return resultado;
    }
 
    /*
     * O vetor vai de dez/25 (indice 0) ate jan/00 (indice alto).
     * Portanto: idx_inicio (jan/ano_ini) > idx_fim (dez/ano_fim).
     *
     * A janela desliza do periodo mais antigo em direcao ao mais recente:
     *   janela 0: [idx_inicio .. idx_inicio - (tam_janela-1)]
     *   janela 1: [idx_inicio-1 .. idx_inicio - tam_janela   ]
     *   ...
     *
     * FIX Bug 2 e Bug 3: usar indices inteiros, nao ponteiros nem .ano,
     * e deslizar na direcao correta (diminuindo idx_inicio).
     */
    int total_meses = idx_inicio - idx_fim + 1;
    int num_janelas = total_meses - tam_janela + 1;
 
    for (int d = 0; d < num_janelas; d++)
    {
        int j_ini = idx_inicio - d;              /* mais antigo da janela */
        int j_fim = j_ini - (tam_janela - 1);    /* mais recente da janela */
 
        float melhor_retorno = -1e30f;
        int   indice_vencedor = -1;
 
        for (int u = 0; u < qtd_arquivos; u++)
        {
            float retorno;
 
            if (eh_cot(nomes_arquivos[indice_primeiro_arquivo + u]))
                retorno = calcula_cotacao_janela(vetor[u], j_ini, j_fim, capital_inicial);
            else
                retorno = calcula_taxa_janela(vetor[u], j_ini, j_fim, capital_inicial);
 
            if (retorno > melhor_retorno)
            {
                melhor_retorno  = retorno;
                indice_vencedor = u;
            }
        }
 
        if (indice_vencedor != -1)
            resultado[indice_vencedor]++;
    }
 
    return resultado;
}

