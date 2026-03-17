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
    int ano_ini = 2000; 
    int ano_fim = 2025;
    int quantidade = argc;
    int quantidade_arquivos = 0;
    int contador_inverso = 1; //começa após o ./juros
    double capital_inicial = 1000.00;
    int janela = 0;

    for(int i = 1; i < argc; )// o controle da variável i ocorre dentro do for 
    {
        if(strcmp(argv[i], "-c") == 0)
        {
            capital_inicial = atof(argv[i + 1]);
            i+= 2;
            contador_inverso += 2;
        }
        else if(strcmp(argv[i], "-i") == 0)
        {
            ano_ini = atoi(argv[i + 1]);
            i +=2;
            contador_inverso += 2;
        }
        else if(strcmp(argv[i], "-f") == 0)
        {
            ano_fim = atoi(argv[i+1]);
            i +=2;
            contador_inverso += 2;
        }

        else if(strcmp(argv[i], "-w") == 0)
        {
            janela = atoi(argv[i + 1]);

            if(janela < 6 || janela > 12)
            {
                printf("Erro: tamanho da janela n foi respeitado\n");
                return 1;
            }

            i += 2;
            contador_inverso += 2;
        }    
        else
        {
            break;
            //começaram os arquivos aqui
        }

    }

    int indice_primeiro_arquivo = contador_inverso;
    int quantidade_arquivos = argc - contador_inverso;

    if(janela > 0 && quantidade_arquivos < 2)
    {
    printf("Erro: -w exige pelo menos dois arquivos\n");
    return 1;
    }


    Linha **vetores = malloc(quantidade_arquivos * sizeof(Linha*));
    // cria um vetor de ponteiros para os vetores de cada arquivo. Será utilizado para verificar valores finais e comparar as janelas

    int *n_linhas = malloc(quantidade_arquivos * sizeof(int));

    for(int j = 0; j < quantidade_arquivos; j++)
    {

        char *nome_arquivo = argv[indice_primeiro_arquivo + j];
        vetores[j] = preencher_vetor(nome_arquivo, &n_linhas[j]);

    }   
    // Até aqui tenho -> um vetor de ponteiros para vetores preenchidos de cada arquivo (usar para realizar calculos)
    // vou implementar primeiro a lógica sem janelas (calcular o valor final de cada investimento)

    if(janela == 0)
    {
        imprime_pontilhado();
        imprime_periodo(ano_ini, ano_fim);
        imprime_capital_inicial(capital_inicial);

        for(int u = 0; u < quantidade_arquivos; u++)
        {
            char *nome_arquivo = argv[indice_primeiro_arquivo + u];
            // para verificar se temos um arquivo de cotação ou um arquivo de taxas 

            if(eh_cot(argv[indice_primeiro_arquivo + u]))
            {
                double resposta = calcula_cotacao(vetores[u], n_linhas[u], ano_ini, ano_fim, capital_inicial);
                imprime_resultado(nome_arquivo, resposta);
            }
            else
            {
                double resposta = caulcula_taxa(vetores[u], n_linhas[u], ano_ini, ano_fim, capital_inicial);
                imprime_resultado(nome_arquivo, resposta);
            }
            
        }

        imprime_pontilhado();
    }
    else if(janela > 0)
    {
        imprime_pontilhado();
        imprime_periodo(ano_ini, ano_fim);
        imprime_tam_janela(janela);

        int *resposta = calcula_janelas(vetores[0], argv[indice_primeiro_arquivo], vetores[1], 
            argv[indice_primeiro_arquivo + 1], n_linhas, ano_ini, ano_fim, capital_inicial, janela);

        imprime_nome_arquivo_janela(argv[indice_primeiro_arquivo]);
        printf(" %d janelas", resposta[0]);

        imprime_nome_arquivo_janela(argv[indice_primeiro_arquivo + 1]);
        printf(" %d janelas", resposta[1]);

        free(resposta);
        imprime_pontilhado();
    }
    
    free(vetores);
    free(n_linhas);

    return 0;
}
