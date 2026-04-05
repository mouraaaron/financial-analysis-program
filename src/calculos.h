#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include "vetor.h"



//essa struct será utilizada para ajudar a limpar o main.

typedef struct {
    int ano_ini;
    int ano_fim;
    int janela;
    float capital_inicial;
    int indice_primeiro_arquivo;
    int quantidade_arquivos;
} parametros_aux;

int coletar_parametros(int argc, char *argv[], parametros_aux *p);

void executar_modo_padrao(Linha **vetores, int *n_linhas, char *argv[], parametros_aux *p);

void executar_modo_janelas(Linha **vetores, int *n_linhas, char *argv[], parametros_aux *p);

float calcula_cotacao(Linha *vetor,int n_linhas, int ano_ini, int ano_fim, float capital_inicial);

float caulcula_taxa(Linha *vetor, int n_linhas, int ano_ini, int ano_fim, float capital_inicial);

int* calcula_janelas(Linha **vetor, char **nomes_arquivos, int *n_linhas, int ano_ini, int ano_fim, float capital_inicial,
     int tam_janela,int indice_primeiro_arquivo,int qtd_arquivos);

float calcula_taxa_janela(Linha *vetor, int idx_inicio, int idx_fim, float capital);

float calcula_cotacao_janela(Linha *vetor, int idx_inicio, int idx_fim, float capital);