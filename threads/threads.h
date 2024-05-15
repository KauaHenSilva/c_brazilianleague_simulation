
/*
Essa função é uma thread, a ser executada, dentro desta função possui uma barrier_wait,
que vai garantir que uma thread só ira prosseguir quando todas as outras threads chegarem
nesse ponto, neste contexto ela é chamada após cada jogo, significando que as threads devem terminar
de jogar e ter seus dados atualizados antes que qualquer uma delas possa prosseguir para o próximo jogo.
*/
void *threadTime(void *arg);

/*
É uma função para criar múltiplas threads e executá-las, cada thread é responsável 
por um time, e cada time joga contra todos os outros times
*/
void runThreadTime();

/*
Ela será executada depois da runThreadTime, pois ela é chamada após todas as threads serem criadas
e ela espera cada thread terminar de executar
*/
void joinThreadTime();
