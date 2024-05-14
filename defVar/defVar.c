#include "defVar.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#ifndef QTD_TIME
#define QTD_TIME 20
#endif

#ifndef STRUCT_TIME
#define STRUCT_TIME
struct saldo
{
  int vitoria;
  int derrota;
  int empate;
  int qtdGol;
};

struct time
{
  int qtdJogosJogados;
  char nome[20];
  Saldo saldo;
  int pontuacao;
  int *timesJogados;
  pthread_mutex_t mutex_pont;
  pthread_t threadTime;
};
#endif

#ifndef VAR_TIMES
#define VAR_TIMES
Time *times;
int jogosCoordenados[QTD_TIME][QTD_TIME][2] = {0};
#endif

void defTimes()
{
  times = (Time *)malloc(sizeof(Time) * QTD_TIME);

  FILE *arq = fopen("../times.txt", "r");
  if (!arq)
    perror("Error ao abrir o arquivo");

  for (int x = 0; x < QTD_TIME; x++)
  {
    fscanf(arq, "%[^\n]\n", times[x].nome);

    times[x].qtdJogosJogados = 0;
    times[x].saldo.vitoria = times[x].saldo.empate = times[x].saldo.derrota = 0;
    times[x].saldo.qtdGol = times[x].pontuacao = 0;

    times[x].timesJogados = (int *)calloc(QTD_TIME, sizeof(int));
    pthread_mutex_init(&times[x].mutex_pont, NULL);
  }

  fclose(arq);
}

void freeTimes()
{
  for (int x = 0; x < QTD_TIME; x++)
  {
    pthread_mutex_destroy(&times[x].mutex_pont);
    free(times[x].timesJogados);
  }

  free(times);
}
