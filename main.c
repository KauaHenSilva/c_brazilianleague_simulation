#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct time{
  int qtdJogosJogados;
  char *nome;
  int pontuacao;
  int *timesJogados;
  pthread_mutex_t mutex_pont;
  pthread_t threadTime;
} Time;

#define QTD_TIME 20

Time *times;
int jogosCoordenados[QTD_TIME][QTD_TIME] = {0};

void *threadTime(void *arg){
  int *idx = (int *)arg;

  pthread_mutex_lock(&times[*idx].mutex_pont);

  for (int x = 0; x < QTD_TIME; x++){
    if (*idx == x || jogosCoordenados[*idx][x] || jogosCoordenados[x][*idx])
      continue;

    jogosCoordenados[*idx][x] = 1;
    jogosCoordenados[x][*idx] = 1;

    times[*idx].qtdJogosJogados += 1;
    times[x].qtdJogosJogados += 1;

    times[*idx].timesJogados[x] = 1;
    times[*idx].pontuacao += 1;

    printf("Time %02d ganhou de %02d\n", *idx, x);
    usleep(100000); // Adiciona um pequeno atraso para simular o jogo
  }

  pthread_mutex_unlock(&times[*idx].mutex_pont);

  free(idx);
  return NULL;
}

int main(){
  times = (Time *)malloc(sizeof(Time) * QTD_TIME);

  for (int x = 0; x < QTD_TIME; x++){
    int *aux = (int *)malloc(sizeof(int));
    *aux = x;

    times[x].qtdJogosJogados = 0;
    times[x].pontuacao = 0;
    times[x].timesJogados = (int *)calloc(QTD_TIME, sizeof(int));
    pthread_mutex_init(&times[x].mutex_pont, NULL);

    pthread_create(&times[x].threadTime, NULL, &threadTime, (void *)aux);
  }

  for (int x = 0; x < QTD_TIME; x++)
    pthread_join(times[x].threadTime, NULL);

  for (int x = 0; x < QTD_TIME; x++){
    
    printf("Time %d: %d\n", x, times[x].pontuacao);
    printf("Time %d jogou %d jogos\n", x, times[x].qtdJogosJogados);
    pthread_mutex_destroy(&times[x].mutex_pont);
    free(times[x].timesJogados);

  }

  free(times);
  return 0;
}