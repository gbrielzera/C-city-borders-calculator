#include <stdio.h>   // Inclui a biblioteca padrão de entrada e saída.
#include <stdlib.h>  // Inclui a biblioteca padrão de funções gerais.
#include <string.h>  // Inclui a biblioteca de manipulação de strings.
#include <math.h>    // Inclui a biblioteca de funções matemáticas.
#include "cidades.h" // Inclui o arquivo de cabeçalho para as estruturas e funções relacionadas a cidades.

// Função para ler as informações das cidades de um arquivo e armazená-las em uma estrutura 'Estrada'.
Estrada *getEstrada(const char *cidades)
{
    // Tenta abrir o arquivo com o nome fornecido. Se falhar, exibe uma mensagem de erro e retorna NULL.
    FILE *file = fopen(cidades, "r");
    if (!file)
    {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", cidades);
        return NULL;
    }

    // Aloca memória para uma nova estrutura 'Estrada' e lê os dados do arquivo para ela.
    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    fscanf(file, "%d", &estrada->T); // Lê o total de posições possíveis na estrada.
    fscanf(file, "%d", &estrada->N); // Lê o número de cidades.

    // Aloca memória para armazenar as cidades e lê as informações de cada cidade do arquivo.
    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    for (int i = 0; i < estrada->N; i++)
    {
        fscanf(file, "%d %[^\n]", &estrada->C[i].Posicao, estrada->C[i].Nome);
    }

    fclose(file);   // Fecha o arquivo.
    return estrada; // Retorna a estrutura 'Estrada' preenchida.
}

// Função para calcular a 'vizinhança' de uma cidade, que é uma medida de quão central ela é em relação às outras cidades.
double calcularVizinhanca(Estrada *estrada, int indiceCidade)
{
    double vizinhanca = 0;                                // Inicializa a vizinhança como 0.
    int posicaoCidade = estrada->C[indiceCidade].Posicao; // Obtém a posição da cidade.
    double mediaPosicoes = 0;                             // Variável para calcular a média das posições das cidades.

    // Calcula a média das posições das cidades.
    for (int i = 0; i < estrada->N; i++)
    {
        mediaPosicoes += estrada->C[i].Posicao;
    }
    mediaPosicoes /= estrada->N;

    // Adiciona à vizinhança a distância absoluta da posição da cidade até a média das posições.
    vizinhanca += fabs(posicaoCidade - mediaPosicoes);

    // Adiciona à vizinhança a menor distância da cidade até os extremos da estrada.
    vizinhanca += fmin(posicaoCidade, estrada->T - posicaoCidade);

    return vizinhanca; // Retorna o valor da vizinhança calculada.
}

// Função para encontrar a menor 'vizinhança' entre todas as cidades.
double calcularMenorVizinhanca(const char *cidades)
{
    Estrada *estrada = getEstrada(cidades); // Obtém as informações das cidades.
    if (!estrada)
        return -1; // Se não conseguir obter as informações, retorna -1.

    double menorVizinhanca = -1; // Inicializa a menor vizinhança como -1.

    // Percorre todas as cidades para encontrar a menor vizinhança.
    for (int i = 0; i < estrada->N; i++)
    {
        double vizinhanca = calcularVizinhanca(estrada, i); // Calcula a vizinhança da cidade atual.

        // Se for a primeira cidade ou se a vizinhança atual for menor que a menor encontrada, atualiza a menor vizinhança.
        if (menorVizinhanca == -1 || vizinhanca < menorVizinhanca)
        {
            menorVizinhanca = vizinhanca;
        }
    }

    free(estrada->C);       // Libera a memória alocada para as cidades.
    free(estrada);          // Libera a memória alocada para a estrada.
    return menorVizinhanca; // Retorna a menor vizinhança encontrada.
}

// Função para encontrar o nome da cidade com a menor 'vizinhança'.
char *cidadeMenorVizinhanca(const char *cidades)
{
    Estrada *estrada = getEstrada(cidades); // Obtém as informações das cidades.
    if (!estrada)
        return NULL; // Se não conseguir obter as informações, retorna NULL.

    double menorVizinhanca = -1; // Inicializa a menor vizinhança como -1.
    char *cidade = NULL;         // Inicializa o ponteiro para o nome da cidade como NULL.

    // Percorre todas as cidades para encontrar a cidade com a menor vizinhança.
    for (int i = 0; i < estrada->N; i++)
    {
        double vizinhanca = calcularVizinhanca(estrada, i); // Calcula a vizinhança da cidade atual.

        // Se for a primeira cidade ou se a vizinhança atual for menor que a menor encontrada, atualiza a menor vizinhança e o nome da cidade.
        if (menorVizinhanca == -1 || vizinhanca < menorVizinhanca)
        {
            menorVizinhanca = vizinhanca;
            cidade = estrada->C[i].Nome;
        }
    }

    // Aloca memória para copiar o nome da cidade e retorna o ponteiro para essa memória.
    char *resultado = (char *)malloc((strlen(cidade) + 1) * sizeof(char));
    strcpy(resultado, cidade);

    free(estrada->C); // Libera a memória alocada para as cidades.
    free(estrada);    // Libera a memória alocada para a estrada.
    return resultado; // Retorna o nome da cidade com a menor vizinhança.
}
