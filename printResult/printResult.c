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
  printf("┌───────────────┬──────────┬──────────┬─────────┬──────────┬──────┬───────┐\n│    Nome       │  PONTOS  │ VITÓRIAS │ EMPATES │ DERROTAS │ GOLS │ JOGOS │\n├───────────────┼──────────┼──────────┼─────────┼──────────┼──────┼───────┤\n");
  for (int x = 0; x < QTD_TIME; x++)
  {
    printf("│ %-13.13s │ %8d │ %8d │ %7d │ %8d │ %4d │ %5d │\n",
           times[x].nome,
           times[x].pontuacao,
           times[x].saldo.vitoria,
           times[x].saldo.empate,
           times[x].saldo.derrota,
           times[x].saldo.qtdGol,
           times[x].qtdJogosJogados);
  }
  printf("└───────────────┴──────────┴──────────┴─────────┴──────────┴──────┴───────┘\n");
}