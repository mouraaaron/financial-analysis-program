#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include "vetor.h"


float calcula_cotacao(Linha *vetor,int n_linhas, int ano_ini, int ano_fim, float capital_inicial);

float caulcula_taxa(Linha *vetor, int n_linhas, int ano_ini, int ano_fim, float capital_inicial);

int* calcula_janelas(Linha **vetor, char **nomes_arquivos, int *n_linhas, int ano_ini, int ano_fim, float capital_inicial,
     int tam_janela,int indice_primeiro_arquivo,int qtd_arquivos);

float calcula_taxa_janela(Linha *vetor, int idx_inicio, int idx_fim, float capital);

float calcula_cotacao_janela(Linha *vetor, int idx_inicio, int idx_fim, float capital);
