#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include "vetor.h"


float calcula_cotacao(Linha *vetor,int n_linhas, int ano_ini, int ano_fim, float capital_inicial);

float caulcula_taxa(Linha *vetor, int n_linhas, int ano_ini, int ano_fim, float capital_inicial);

int* calcula_janelas(Linha *vetor1, const char *nome_1, Linha *vetor2, const char *nome_2, int n_linhas, 
    int ano_ini, int ano_fim, float capital_inicial, int janela);