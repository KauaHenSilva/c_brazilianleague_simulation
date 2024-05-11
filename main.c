#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct saldo{
    int vitoria;
    int derrota;
    int empate;
    int qtdGol;
}Saldo;

typedef struct time{
  int qtdJogosJogados;
  char *nome;
  Saldo saldo;
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

    int num = rand() % 3;  
    if(num == 0){
      printf("Time %02d ganhou de %02d\n", *idx, x);
      times[*idx].saldo.vitoria += 1;
      times[x].saldo.derrota += 1;
    }else if(num == 1){
      printf("Time %02d empate de %02d\n", *idx, x);
      times[*idx].saldo.empate += 1;
      times[x].saldo.empate += 1;
    }else{
      printf("Time %02d derrota de %02d\n", *idx, x);
      times[*idx].saldo.derrota += 1;
      times[x].saldo.vitoria += 1;
    }else if(num == 1){
      printf("Time %02d empate de %02d\n", *idx, x);
      times[*idx].saldo.empate += 1;
    }else{
      printf("Time %02d derrota de %02d\n", *idx, x);
      times[*idx].saldo.derrota += 1;
    }
    usleep(100000); // Adiciona um pequeno atraso para simular o jogo
  }

  pthread_mutex_unlock(&times[*idx].mutex_pont);

  free(idx);
  return NULL;
}

int comparetime(const void* a,const void* b){
  Time *teamA = (Time *)a;
  Time *teamB = (Time *)b;

  return (teamB->pontuacao - teamA->pontuacao);
}

void pontuacao(){
  for(int i=0;i<QTD_TIME;i++){
    times[i].pontuacao += (times[i].saldo.vitoria * 3);
    times[i].pontuacao += times[i].saldo.empate;
  }
}

int main(){
  times = (Time *)malloc(sizeof(Time) * QTD_TIME);

  for (int x = 0; x < QTD_TIME; x++){
    int *aux = (int *)malloc(sizeof(int));
    *aux = x;

    times[x].qtdJogosJogados = 0;
    times[x].saldo.vitoria = times[x].saldo.empate =  times[x].saldo.derrota = 0;
    times[x].saldo.qtdGol = times[x].pontuacao = 0;
    
    times[x].timesJogados = (int *)calloc(QTD_TIME, sizeof(int));
    pthread_mutex_init(&times[x].mutex_pont, NULL);

    pthread_create(&times[x].threadTime, NULL, &threadTime, (void *)aux);
  }

  for (int x = 0; x < QTD_TIME; x++)
    pthread_join(times[x].threadTime, NULL);

  pontuacao();

  qsort(times,QTD_TIME,sizeof(Time), comparetime);
  printf("Nome \t P \t V \t E \t D \t J\n");
  for (int x = 0; x < QTD_TIME; x++){
    printf(
      "%02d \t %02d \t %02d \t %02d \t %02d \t %02d \n", 
      x, times[x].pontuacao, 
      times[x].saldo.vitoria, times[x].saldo.empate,times[x].saldo.derrota,
      times[x].qtdJogosJogados
    );
    
    pthread_mutex_destroy(&times[x].mutex_pont);
    free(times[x].timesJogados);

  }

  free(times);
  return 0;
}
