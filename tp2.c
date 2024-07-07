#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

// Função para calcular a pontuação máxima usando Programação Dinâmica
int maxPontosProgramacaoDinamica(int N, int *sequencia) {
    if (N == 0) return 0;
    if (N == 1) return sequencia[0];
    
    int *DP = (int *)malloc(N * sizeof(int));
    DP[0] = sequencia[0];
    DP[1] = sequencia[0] > sequencia[1] ? sequencia[0] : sequencia[1];
    
    for (int i = 2; i < N; i++) {
        DP[i] = DP[i-1] > (sequencia[i] + DP[i-2]) ? DP[i-1] : (sequencia[i] + DP[i-2]);
    }
    
    int resultado = DP[N-1];
    free(DP);
    return resultado;
}

// Função para calcular a pontuação máxima usando a estratégia alternativa
int maxPontosAlternativa(int N, int *sequencia) {
    if (N == 0) return 0;
    if (N == 1) return sequencia[0];
    
    int pontosAtuais = sequencia[0];
    int pontosProximos = sequencia[0] > sequencia[1] ? sequencia[0] : sequencia[1];
    
    for (int i = 2; i < N; i++) {
        int temp = pontosProximos;
        pontosProximos = pontosProximos > (sequencia[i] + pontosAtuais) ? pontosProximos : (sequencia[i] + pontosAtuais);
        pontosAtuais = temp;
    }
    
    return pontosProximos;
}

// Função para medir o tempo de execução
void medirTempo(int (*funcao)(int, int*), int N, int *sequencia) {
    struct timeval inicio, fim;
    struct rusage uso;
    
    gettimeofday(&inicio, NULL);
    funcao(N, sequencia);
    gettimeofday(&fim, NULL);
    
    getrusage(RUSAGE_SELF, &uso);
    
    double tempoUsuario = (double)uso.ru_utime.tv_sec + (double)uso.ru_utime.tv_usec / 1000000.0;
    double tempoSistema = (double)uso.ru_stime.tv_sec + (double)uso.ru_stime.tv_usec / 1000000.0;
    
    printf("Tempo de usuário: %lf\n", tempoUsuario);
    printf("Tempo de sistema: %lf\n", tempoSistema);
}

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
