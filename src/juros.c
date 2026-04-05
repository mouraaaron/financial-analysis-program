#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "vetor.h"
#include "prints.h"
#include "calculos.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>



int main(int argc, char *argv[])   
{
    parametros_aux p; 

    if(coletar_parametros(argc, argv, &p) != 0)
        return 1;

    
    if(p.janela > 0 && p.quantidade_arquivos < 2)
    {
    printf("Erro: -w exige pelo menos dois arquivos\n");
    return 1;
    }


    Linha **vetores = malloc(p.quantidade_arquivos * sizeof(Linha*));
    // cria um vetor de ponteiros para os vetores de cada arquivo. 
    // Será utilizado para verificar valores finais e comparar as janelas
    // Depois eu descobri que isso pode ser interpretado como uma matriz

    int *n_linhas = malloc(p.quantidade_arquivos * sizeof(int));

    for(int j = 0; j < p.quantidade_arquivos; j++)
    {

        char *nome_arquivo = argv[p.indice_primeiro_arquivo + j];
        vetores[j] = preencher_vetor(nome_arquivo, &n_linhas[j]);
        
    }   
    
    // Até aqui tenho -> um vetor de ponteiros para vetores preenchidos de cada arquivo (usar para realizar calculos)
    // vou implementar primeiro a lógica sem janelas (calcular o valor final de cada investimento)
    
    //usando esquema de ponteiros para função como visto em aula. Esses são os parametros que 'processar' recebe
    void (*processar)(Linha **, int*, char**, parametros_aux*);

    if(p.janela == 0)
        processar = executar_modo_padrao;
    else   
        processar = executar_modo_janelas;

    processar(vetores, n_linhas, argv, &p);

    free(vetores);
    free(n_linhas);

    return 0;
 
}
