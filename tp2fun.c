#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "tp2.h"

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
