#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct time
{
  char *nome;
  int pontuacao;
  int *qtdPartidas;
  pthread_mutex_t mutex_pont;
  pthread_t threadTime;
} Time;

#define QTD_TIME 20

Time *times;
/*
Thread Time
*/
void *threadTime(void *arg){
  int *idx = (int *)arg;

  for (int x = 0; x < QTD_TIME; x++)
  {
    if (*idx == x)
      continue;
    
    if (times[*idx].qtdPartidas[x] > 0)
      continue;

    pthread_mutex_lock(&times[*idx].mutex_pont);

    times[*idx].qtdPartidas[x]++;
    times[*idx].pontuacao += 1;

    pthread_mutex_unlock(&times[*idx].mutex_pont);
  }

  for (int x = 0; x < QTD_TIME; x++)
  {
    if (*idx == x)
      continue;

    if (times[*idx].qtdPartidas[x] > 0)
      continue;

    pthread_mutex_lock(&times[*idx].mutex_pont);

    times[*idx].qtdPartidas[x]++;
    times[*idx].pontuacao += 1;

    pthread_mutex_unlock(&times[*idx].mutex_pont);
  }

  free(idx);
  return NULL;
}

int main()
{
  times = (Time *)malloc(sizeof(Time) * QTD_TIME);

  for (int x = 0; x < QTD_TIME; x++)
  {
    int *aux = (int *)malloc(sizeof(int));
    *aux = x;

    times[x].pontuacao = 0;
    times[x].qtdPartidas = (int *)calloc(sizeof(int), QTD_TIME);

    pthread_create(&times[x].threadTime, NULL, &threadTime, (void *)aux);
  }

  for (int x = 0; x < QTD_TIME; x++)
    pthread_join(times[x].threadTime, NULL);

  // for (int x = 0; x < QTD_TIME; x++)
  // {
  //   for (int y = 0; y < QTD_TIME; y++)
  //     printf("[%d]", times[x].qtdPartidas[y]);
  //   printf("\n");
  // }

  for(int x = 0 ;  x < QTD_TIME ; x++)
    printf("Time %d: %d\n", x, times[x].pontuacao);

  for (int x = 0; x < QTD_TIME; x++)
    free(times[x].qtdPartidas);
  free(times);
  return 0;
}