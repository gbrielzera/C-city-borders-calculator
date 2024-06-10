#include <stdio.h>   // Inclui a biblioteca padrão de entrada e saída.
#include <stdlib.h>  // Inclui a biblioteca padrão de funções gerais.
#include "cidades.h" // Inclui o arquivo de cabeçalho que contém as definições das estruturas e funções relacionadas a cidades.

int main() // Função principal do programa.
{
    const char *cidades = "cidades.txt"; // Define o nome do arquivo que contém as informações das cidades.

    // Chama a função 'calcularMenorVizinhanca' para encontrar a menor vizinhança entre todas as cidades.
    double menorVizinhanca = calcularMenorVizinhanca(cidades);
    // Chama a função 'cidadeMenorVizinhanca' para obter o nome da cidade com a menor vizinhança.
    char *cidade = cidadeMenorVizinhanca(cidades);

    // Se a função 'cidadeMenorVizinhanca' retornou um nome de cidade válido (não NULL),
    // imprime o nome da cidade e o valor da menor vizinhança.
    if (cidade)
    {
        printf("Cidade com menor vizinhanca: %s\n", cidade); // Imprime o nome da cidade.
        printf("Menor vizinhanca: %.2f\n", menorVizinhanca); // Imprime o valor da menor vizinhança com duas casas decimais.
        free(cidade);                                        // Libera a memória alocada para o nome da cidade.
    }
    else // Se não foi possível calcular a menor vizinhança, imprime uma mensagem de erro.
    {
        printf("Erro ao calcular a menor vizinhanca.\n");
    }

    return 0; // Retorna 0 indicando que o programa foi concluído com sucesso.
}
