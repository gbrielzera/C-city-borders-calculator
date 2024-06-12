#include "cidades.h" // Inclui o cabeçalho onde estão definidas as estruturas e funções utilizadas
#include <stdio.h>   // Inclui a biblioteca padrão de entrada e saída
#include <stdlib.h>  // Inclui a biblioteca padrão de alocação de memória e outras funções utilitárias

int main()
{
    const char *nomeArquivo = "nomeArquivo.txt"; // Nome do arquivo que contém os dados das cidades

    // Chama a função que calcula a menor vizinhança e armazena o resultado
    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);

    // Chama a função que encontra o nome da cidade com a menor vizinhança e armazena o resultado
    char *cidadeMenor = cidadeMenorVizinhanca(nomeArquivo);

    // Verifica se foi possível encontrar a cidade com a menor vizinhança
    if (cidadeMenor)
    {
        // Imprime a menor vizinhança e o nome da cidade com a menor vizinhança
        printf("Menor vizinhanca de estrada: %.2f\n", menorVizinhanca);
        printf("Cidade com menor vizinhanca: %s\n", cidadeMenor);
        // Libera a memória alocada para o nome da cidade
        free(cidadeMenor);
    }
    else
    {
        // Caso ocorra um erro, imprime uma mensagem de erro
        printf("Erro ao calcular a menor vizinhanca ou ao encontrar a cidade.\n");
    }

    // Retorna 0 para indicar que o programa terminou com sucesso
    return 0;
}
