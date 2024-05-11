#include "printResult.h"

int comparetime(const void *a, const void *b)
{
  Time *teamA = (Time *)a;
  Time *teamB = (Time *)b;

  return (teamB->pontuacao - teamA->pontuacao);
}

void pontuacao()
{
  for (int i = 0; i < QTD_TIME; i++)
  {
    times[i].pontuacao += (times[i].saldo.vitoria * 3);
    times[i].pontuacao += times[i].saldo.empate;
  }
}

void printTable()
{
  pontuacao();
  qsort(times, QTD_TIME, sizeof(Time), comparetime);
  printf("%-11s \t P \t V \t E \t D \t J\n", "Nome");
  for (int x = 0; x < QTD_TIME; x++)
    printf(
        "%-11s \t %02d \t %02d \t %02d \t %02d \t %02d \n",
        times[x].nome, times[x].pontuacao,
        times[x].saldo.vitoria, times[x].saldo.empate, times[x].saldo.derrota,
        times[x].qtdJogosJogados);
}