#include <stdio.h>
#include <stdlib.h>
#include "tp2.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: ./tp2 <estrategia> entrada.txt\n");
        return 1;
    }
    
    char estrategia = argv[1][0];
    char *arquivoEntrada = argv[2];
    
    FILE *arquivo = fopen(arquivoEntrada, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    
    int N;
    fscanf(arquivo, "%d", &N);
    
    int *sequencia = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        fscanf(arquivo, "%d", &sequencia[i]);
    }
    fclose(arquivo);
    
    int resultado;
    if (estrategia == 'D') {
        resultado = maxPontosProgramacaoDinamica(N, sequencia);
    } else if (estrategia == 'A') {
        resultado = maxPontosAlternativa(N, sequencia);
    } else {
        printf("Estratégia inválida. Use 'D' para Programação Dinâmica ou 'A' para alternativa.\n");
        free(sequencia);
        return 1;
    }
    
    FILE *arquivoSaida = fopen("saida.txt", "w");
    if (!arquivoSaida) {
        perror("Erro ao abrir o arquivo de saída");
        free(sequencia);
        return 1;
    }
    fprintf(arquivoSaida, "%d\n", resultado);
    fclose(arquivoSaida);
    
    if (estrategia == 'D') {
        medirTempo(maxPontosProgramacaoDinamica, N, sequencia);
    } else if (estrategia == 'A') {
        medirTempo(maxPontosAlternativa, N, sequencia);
    }
    
    free(sequencia);
    return 0;
}
