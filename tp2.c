#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

// Função para calcular a pontuação máxima usando Programação Dinâmica
int maxPointsDynamicProgramming(int N, int *sequence) {
    if (N == 0) return 0;
    if (N == 1) return sequence[0];
    
    int *DP = (int *)malloc(N * sizeof(int));
    DP[0] = sequence[0];
    DP[1] = sequence[0] > sequence[1] ? sequence[0] : sequence[1];
    
    for (int i = 2; i < N; i++) {
        DP[i] = DP[i-1] > (sequence[i] + DP[i-2]) ? DP[i-1] : (sequence[i] + DP[i-2]);
    }
    
    int result = DP[N-1];
    free(DP);
    return result;
}

// Função para calcular a pontuação máxima usando a estratégia alternativa
int maxPointsAlternative(int N, int *sequence) {
    if (N == 0) return 0;
    if (N == 1) return sequence[0];
    
    int currentPoints = sequence[0];
    int nextPoints = sequence[0] > sequence[1] ? sequence[0] : sequence[1];
    
    for (int i = 2; i < N; i++) {
        int temp = nextPoints;
        nextPoints = nextPoints > (sequence[i] + currentPoints) ? nextPoints : (sequence[i] + currentPoints);
        currentPoints = temp;
    }
    
    return nextPoints;
}

// Função para medir o tempo de execução
void measureTime(int (*func)(int, int*), int N, int *sequence) {
    struct timeval start, end;
    struct rusage usage;
    
    gettimeofday(&start, NULL);
    func(N, sequence);
    gettimeofday(&end, NULL);
    
    getrusage(RUSAGE_SELF, &usage);
    
    double userTime = (double)usage.ru_utime.tv_sec + (double)usage.ru_utime.tv_usec / 1000000.0;
    double systemTime = (double)usage.ru_stime.tv_sec + (double)usage.ru_stime.tv_usec / 1000000.0;
    
    printf("User time: %lf\n", userTime);
    printf("System time: %lf\n", systemTime);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: ./tp2 <estrategia> entrada.txt\n");
        return 1;
    }
    
    char strategy = argv[1][0];
    char *inputFile = argv[2];
    
    FILE *file = fopen(inputFile, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    
    int N;
    fscanf(file, "%d", &N);
    
    int *sequence = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        fscanf(file, "%d", &sequence[i]);
    }
    fclose(file);
    
    int result;
    if (strategy == 'D') {
        result = maxPointsDynamicProgramming(N, sequence);
    } else if (strategy == 'A') {
        result = maxPointsAlternative(N, sequence);
    } else {
        printf("Estratégia inválida. Use 'D' para Programação Dinâmica ou 'A' para alternativa.\n");
        free(sequence);
        return 1;
    }
    
    FILE *outputFile = fopen("saida.txt", "w");
    if (!outputFile) {
        perror("Erro ao abrir o arquivo de saída");
        free(sequence);
        return 1;
    }
    fprintf(outputFile, "%d\n", result);
    fclose(outputFile);
    
    if (strategy == 'D') {
        measureTime(maxPointsDynamicProgramming, N, sequence);
    } else if (strategy == 'A') {
        measureTime(maxPointsAlternative, N, sequence);
    }
    
    free(sequence);
    return 0;
}
