#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include "calculos.h"
#include "prints.h"


int coletar_parametros(int argc, char *argv[], parametros_aux *p) 
{
    // Inicialização com os seus valores default
    p->ano_ini = 2000; 
    p->ano_fim = 2025;
    p->capital_inicial = 1000.00;
    p->janela = 0;
    
    int contador_inverso = 1; 

    for(int i = 1; i < argc; )
    {
        if(strcmp(argv[i], "-c") == 0)
        {
            p->capital_inicial = atof(argv[i + 1]);
            i += 2;
            contador_inverso += 2;
        }
        else if(strcmp(argv[i], "-i") == 0)
        {
            p->ano_ini = atoi(argv[i + 1]);
            i += 2;
            contador_inverso += 2;
        }
        else if(strcmp(argv[i], "-f") == 0)
        {
            p->ano_fim = atoi(argv[i + 1]);
            i += 2;
            contador_inverso += 2;
        }
        else if(strcmp(argv[i], "-w") == 0)
        {
            p->janela = atoi(argv[i + 1]);

            if(p->janela < 6 || p->janela > 12)
            {
                printf("Erro: tamanho da janela n foi respeitado\n");
                return 1; 
            }

            i += 2;
            contador_inverso += 2;
        }    
        else
        {
            break; // Fim dos comandos "-x"
        }
    }

    // Atribuição final baseada no seu contador_inverso
    p->indice_primeiro_arquivo = contador_inverso;
    p->quantidade_arquivos = argc - contador_inverso;

    return 0; // Sucesso
}

void executar_modo_padrao(Linha **vetores, int *n_linhas, char *argv[], parametros_aux *p)
{
    imprime_pontilhado();
    imprime_periodo(p->ano_ini, p->ano_fim);
    imprime_capital_inicial(p->capital_inicial);

    for(int u = 0; u < p->quantidade_arquivos; u++) {
        char *nome_arquivo = argv[p->indice_primeiro_arquivo + u];

        if(eh_cot(argv[p->indice_primeiro_arquivo + u])) {
            double resposta = calcula_cotacao(vetores[u], n_linhas[u], p->ano_ini, p->ano_fim, p->capital_inicial);
            imprime_resultado(nome_arquivo, resposta);
        } else {
            double resposta = caulcula_taxa(vetores[u], n_linhas[u], p->ano_ini, p->ano_fim, p->capital_inicial);
            imprime_resultado(nome_arquivo, resposta);
        }
    }
    imprime_pontilhado();
}

void executar_modo_janelas(Linha **vetores, int *n_linhas, char *argv[], parametros_aux *p) 
{
    imprime_pontilhado();
    imprime_periodo(p->ano_ini, p->ano_fim);
    imprime_tam_janela(p->janela);

    char **nomes_arquivos = malloc(p->quantidade_arquivos * sizeof(char*));

    for(int w = 0; w < p->quantidade_arquivos; w++) {
        nomes_arquivos[w] = argv[p->indice_primeiro_arquivo + w];
    }

    int *resposta = calcula_janelas(vetores, nomes_arquivos, n_linhas, p->ano_ini, p->ano_fim, p->capital_inicial, 
        p->janela, 0, p->quantidade_arquivos);

    for(int i = 0; i < p->quantidade_arquivos; i++) {
        imprime_nome_arquivo_janela(nomes_arquivos[i]);
        printf(" %d janelas\n", resposta[i]);
    }

    free(resposta);
    free(nomes_arquivos);
    imprime_pontilhado();
}

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
 
    int idx_inicio = -1;  
    int idx_fim    = -1; 
 
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
 

    
     /* O vetor vai de dez/25 (indice 0) ate jan/00 (indice alto).
     A janela desliza do periodo mais antigo em direcao ao mais recente: */
     

    int total_meses = idx_inicio - idx_fim + 1;
    int num_janelas = total_meses - tam_janela + 1;
 
    for (int d = 0; d < num_janelas; d++)
    {
        int j_ini = idx_inicio - d;             
        int j_fim = j_ini - (tam_janela - 1);    
 
        float melhor_retorno = -1e30f;
        int indice_vencedor = -1;
 
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

