#include "defVar.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#ifndef QTD_TIME
#define QTD_TIME 20
#endif

#ifndef STRUCT_TIME
#define STRUCT_TIME
typedef struct saldo{
    int vitoria;
    int derrota;
    int empate;
    int qtdGol;
}Saldo;

typedef struct time{
    int qtdJogosJogados;
    char nome[20];
    Saldo saldo;
    int pontuacao;
    int *timesJogados;
    pthread_t threadTime;
}Time;
#endif

#ifndef VAR_TIMES
#define VAR_TIMES
Time *times;
int jogosCoordenados[QTD_TIME][QTD_TIME][2] = {0};
pthread_barrier_t barrier_pont;
#endif

void defTimes(){
    times = (Time *)malloc(sizeof(Time) * QTD_TIME);

    FILE *arq = fopen("../times.txt", "r");
    if (!arq)
        perror("Error ao abrir o arquivo");

    for (int x = 0; x < QTD_TIME; x++){
        fscanf(arq, "%[^\n]\n", times[x].nome);

        times[x].qtdJogosJogados = 0;
        times[x].saldo.vitoria = times[x].saldo.empate = times[x].saldo.derrota = 0;
        times[x].saldo.qtdGol = times[x].pontuacao = 0;

        times[x].timesJogados = (int *)calloc(QTD_TIME, sizeof(int));

    }
    
    pthread_barrier_init(&barrier_pont, NULL , QTD_TIME);

    fclose(arq);
}

void freeTimes(){

    for (int x = 0; x < QTD_TIME; x++){

        pthread_barrier_destroy(&barrier_pont);
        free(times[x].timesJogados);
    
    }

    free(times);
}
