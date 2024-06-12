#include "cidades.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para comparar cidades com base em suas posições
// Essa função é usada pelo qsort para ordenar as cidades pela posição
int compararCidades(const void *a, const void *b)
{
    return ((Cidade *)a)->Posicao - ((Cidade *)b)->Posicao;
}

// Função para ler as informações das cidades de um arquivo e armazená-las em uma estrutura 'Estrada'
Estrada *getEstrada(const char *nomeArquivo)
{
    // Abre o arquivo para leitura
    FILE *file = fopen(nomeArquivo, "r");
    if (!file)
    {
        // Caso ocorra um erro ao abrir o arquivo, imprime uma mensagem de erro e retorna NULL
        perror("Erro ao abrir arquivo");
        return NULL;
    }

    // Aloca memória para a estrutura Estrada
    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (!estrada)
    {
        // Caso ocorra um erro de alocação de memória, imprime uma mensagem de erro, fecha o arquivo e retorna NULL
        perror("Erro de alocacao de memoria");
        fclose(file);
        return NULL;
    }

    // Lê o valor de T e N do arquivo
    fscanf(file, "%d", &estrada->T);
    fscanf(file, "%d", &estrada->N);

    // Aloca memória para o array de cidades
    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (!estrada->C)
    {
        // Caso ocorra um erro de alocação de memória, imprime uma mensagem de erro, fecha o arquivo, libera a memória de estrada e retorna NULL
        perror("Erro de alocacao de memoria");
        fclose(file);
        free(estrada);
        return NULL;
    }

    // Lê as posições e os nomes das cidades do arquivo
    for (int i = 0; i < estrada->N; i++)
    {
        if (fscanf(file, "%d ", &estrada->C[i].Posicao) != 1)
        {
            // Caso ocorra um erro ao ler a posição da cidade, imprime uma mensagem de erro, fecha o arquivo, libera a memória alocada e retorna NULL
            fprintf(stderr, "Erro ao ler posicao da cidade %d\n", i);
            fclose(file);
            free(estrada->C);
            free(estrada);
            return NULL;
        }
        // Lê o nome da cidade (até 256 caracteres) e remove o caractere de nova linha
        fgets(estrada->C[i].Nome, 256, file);
        estrada->C[i].Nome[strcspn(estrada->C[i].Nome, "\n")] = '\0';

        // Verifica se há cidades com posições duplicadas
        for (int j = 0; j < i; j++)
        {
            if (estrada->C[i].Posicao == estrada->C[j].Posicao)
            {
                // Caso ocorra uma duplicação de posições, imprime uma mensagem de erro, fecha o arquivo, libera a memória alocada e retorna NULL
                fprintf(stderr, "Erro: posicao da cidade duplicada\n");
                fclose(file);
                free(estrada->C);
                free(estrada);
                return NULL;
            }
        }
    }

    // Fecha o arquivo e retorna a estrutura estrada
    fclose(file);
    return estrada;
}

// Função para calcular a menor vizinhança entre todas as cidades
double calcularMenorVizinhanca(const char *nomeArquivo)
{
    // Chama a função getEstrada para ler as cidades do arquivo
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada)
        return -1.0;

    // Ordena as cidades pela posição
    qsort(estrada->C, estrada->N, sizeof(Cidade), compararCidades);

    // Inicializa a menor vizinhança com o valor máximo possível (T)
    double menorVizinhanca = estrada->T;

    // Calcula a vizinhança de cada cidade
    for (int i = 0; i < estrada->N; i++)
    {
        // Calcula o início da vizinhança da cidade
        double inicio = (i == 0) ? 0 : (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
        // Calcula o fim da vizinhança da cidade
        double fim = (i == estrada->N - 1) ? estrada->T : (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
        // Calcula o tamanho da vizinhança
        double vizinhanca = fim - inicio;

        // Atualiza a menor vizinhança encontrada
        if (vizinhanca < menorVizinhanca)
            menorVizinhanca = vizinhanca;
    }

    // Libera a memória alocada
    free(estrada->C);
    free(estrada);

    // Retorna a menor vizinhança
    return menorVizinhanca;
}

// Função para encontrar o nome da cidade com a menor vizinhança
char *cidadeMenorVizinhanca(const char *nomeArquivo)
{
    // Chama a função getEstrada para ler as cidades do arquivo
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada)
        return NULL;

    // Ordena as cidades pela posição
    qsort(estrada->C, estrada->N, sizeof(Cidade), compararCidades);

    // Inicializa a menor vizinhança com o valor máximo possível (T) e o nome da cidade com a menor vizinhança como NULL
    double menorVizinhanca = estrada->T;
    char *cidadeMenor = NULL;

    // Calcula a vizinhança de cada cidade
    for (int i = 0; i < estrada->N; i++)
    {
        // Calcula o início da vizinhança da cidade
        double inicio = (i == 0) ? 0 : (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
        // Calcula o fim da vizinhança da cidade
        double fim = (i == estrada->N - 1) ? estrada->T : (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
        // Calcula o tamanho da vizinhança
        double vizinhanca = fim - inicio;

        // Atualiza a menor vizinhança e o nome da cidade com a menor vizinhança
        if (vizinhanca < menorVizinhanca)
        {
            menorVizinhanca = vizinhanca;

            // Aloca memória para o nome da cidade com a menor vizinhança
            cidadeMenor = malloc(strlen(estrada->C[i].Nome) + 1);
            if (!cidadeMenor)
            {
                // Caso ocorra um erro de alocação de memória, imprime uma mensagem de erro, libera a memória alocada e retorna NULL
                perror("Erro de alocação de memória");
                free(estrada->C);
                free(estrada);
                return NULL;
            }

            // Copia o nome da cidade com a menor vizinhança
            strcpy(cidadeMenor, estrada->C[i].Nome);
        }
    }

    // Libera a memória alocada
    free(estrada->C);
    free(estrada);

    // Retorna o nome da cidade com a menor vizinhança
    return cidadeMenor;
}
