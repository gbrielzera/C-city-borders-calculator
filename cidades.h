#ifndef CIDADES_H // Se CIDADES_H não foi definido anteriormente,
#define CIDADES_H // define CIDADES_H para evitar inclusões múltiplas do mesmo arquivo.

// Definição da estrutura 'Cidade', que armazena informações sobre uma cidade.
typedef struct
{
    char Nome[256]; // Nome da cidade, com espaço para até 255 caracteres + terminador nulo.
    int Posicao;    // Posição da cidade ao longo da estrada.
} Cidade;

// Definição da estrutura 'Estrada', que armazena informações sobre todas as cidades em uma estrada.
typedef struct
{
    int N;     // Número total de cidades na estrada.
    int T;     // Comprimento total da estrada.
    Cidade *C; // Ponteiro para um vetor de 'Cidade', onde cada elemento representa uma cidade.
} Estrada;

// Declaração de funções que serão implementadas em outro arquivo.
Estrada *getEstrada(const char *nomeArquivo);            // Função para inicializar as cidades no TAD 'Estrada'.
double calcularMenorVizinhanca(const char *nomeArquivo); // Função para calcular e retornar a menor vizinhança entre todas as cidades.
char *cidadeMenorVizinhanca(const char *nomeArquivo);    // Função para retornar o nome da cidade com a menor vizinhança.

#endif // Fim da verificação de inclusão múltipla.
