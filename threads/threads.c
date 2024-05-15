#include <pthread.h>
#include <stdio.h>

#include "threads.h"

#ifndef VAR_TIMES
Time *times;
int jogosCoordenados[QTD_TIME][QTD_TIME][2] = {0};
#endif

void *threadTime(void *arg){
    int *idx = (int *)arg;
    
    for (int i = 0; i < 2; i++){
        for (int x = 0; x < QTD_TIME; x++){

            if (*idx == x || jogosCoordenados[*idx][x][i] || jogosCoordenados[x][*idx][i])
                continue;

            jogosCoordenados[*idx][x][i] = 1;
            jogosCoordenados[x][*idx][i] = 1;

            times[*idx].timesJogados[x] = 1;

            int golsTimeA = rand() % 5;
            int golsTimeB = rand() % 5;

            printf(
                "├─────────────────┼─────────────────┼─────────────────┼─────────────────│\n│ %-15s │ %15d X %-15d │ %15s │\n├─────────────────┼─────────────────┼─────────────────┼─────────────────│\n",
                times[*idx].nome, golsTimeA,
                golsTimeB, times[x].nome);

            if (golsTimeA > golsTimeB){
                times[*idx].saldo.vitoria += 1;
                times[*idx].saldo.qtdGol += golsTimeA;
                times[x].saldo.derrota += 1;
                times[x].saldo.qtdGol -= golsTimeA;
            }else if (golsTimeA == golsTimeB){
                times[*idx].saldo.empate += 1;
                times[*idx].saldo.qtdGol += golsTimeA;
                times[x].saldo.empate += 1;
                times[x].saldo.qtdGol += golsTimeB;
            }else{
                times[*idx].saldo.derrota += 1;
                times[*idx].saldo.qtdGol -= golsTimeB;
                times[x].saldo.vitoria += 1;
                times[x].saldo.qtdGol += golsTimeB;
            }

            times[*idx].qtdJogosJogados += 1;
            times[x].qtdJogosJogados += 1;


            sleep(1);
        }

    }

    pthread_barrier_wait(&barrier_pont);

    free(idx);

    return NULL;
}

void runThreadTime(){
    printf("┌─────────────────┬─────────────────┬─────────────────┬─────────────────┐\n");

    for (int x = 0; x < QTD_TIME; x++){
        int *aux = (int *)malloc(sizeof(int));
        
        *aux = x;

        if (pthread_create(&times[x].threadTime, NULL, &threadTime, (void*)aux) != 0)
            perror("Erro ao criar a thread");

    }
}

void joinThreadTime(){
    for (int x = 0; x < QTD_TIME; x++)
        pthread_join(times[x].threadTime, NULL);

    printf("└─────────────────┴─────────────────┴─────────────────┴─────────────────┘\n");
}