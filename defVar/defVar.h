
typedef struct time Time;
typedef struct saldo Saldo;

/*
Inicializa todas as structs, aloca memória para os times e
inicializa a barreira com a quantidade de threads que vai ser utilizada em
pthread_barrier_wait(&barrier_pont);
*/
void defTimes();

/*
Vai destruir todas as barreiras e liberar a memória alocada para os times
*/
void freeTimes();