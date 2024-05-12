#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "defVar/defVar.c"
#include "threads/threads.c"
#include "printResult/printResult.c"


int main()
{
  defTimes();

  runThreadTime();
  joinThreadTime();

  printTable();

  freeTimes();
  return 0;
}
  
