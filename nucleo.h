#ifndef NUCLEO_H_
#define NUCLEO_H_

#include "lista.h"
#include <pthread.h>
#include <semaphore.h>

// DEFINIÇÃO DAS THREADS ==================================================================================================
pthread_t T_READFILE;
pthread_t T_PROCESS_CREATE;
pthread_t T_PROCESS_FINISH;
pthread_t T_SEMAPHORE_P;
pthread_t T_SEMAPHORE_V;
pthread_t T_ESCALONADOR;

pthread_attr_t T_READFILE_ATTR;
pthread_attr_t T_PROCESS_CREATE_ATTR;
pthread_attr_t T_PROCESS_FINISH_ATTR;
pthread_attr_t T_SEMAPHORE_P_ATTR;
pthread_attr_t T_SEMAPHORE_V_ATTR;
pthread_attr_t T_ESCALONADOR_ATTR;

// DEFINIÇÃO DOS SEMÁFOROS ================================================================================================

sem_t S_LISTA;
sem_t S_FILE_SELECTOR;

// OUTRAS VARIAVEIS
FILE *f;


// COMO PEDIDO NO PROJETO, SOMENTE AS FUNÇÕES 2, 3, 10 E 11 FORAM IMPLEMENTADAS ===========================================

int interruptControl();                         // Gera os numeros aleatórios
void processInterrupt();                        // 1 - Interrupção gerada pelo final do quantum time de um processo
void semaphoreP(char sem);                      // 2 - Tratamento de bloqueio de processo
void semaphoreV(char sem);                      // 3 - Tratamento de desbloqueio de processo
void ioRequest();                               // 4 - Chamada de operação de E/S
void ioFinish();                                // 5 - Sinalização de final de E/S
void memLoadRequest();                          // 6 - Chamada de operação de carregamento na memória
void memLoadFinish();                           // 7 - Sinalização de final de carregamento
void fsRequest();                               // 8 - Chamada para operação no sistema de arquivos
void fsFinish();                                // 9 - Sinalização de final de operação no sistema de arquivos
void processCreate(processo_info *processo);    // 10 - Chamada para a criação de um processo no BCP
void processFinish(no *processo);                           // 11 - Chamada para terminar a execução de um processo no BCP
void exec(int tempo);                           // Executa o processo por um tempo determinado
void read(int trilha);                          // Le uma trilha do hd
void write(int trilha);                         // Escreve em uma trilha do hd
void readFile(const char *caminho);              // Lê as instruções do arquivo sintético
void sysCall();                                  // Faz as chamadas de sistema de acordo com as intruçoões do programa sintético
void inicializarLista();
void inicializarThreads();
void inicializarSemaforos();
void selecionaArquivo();
void nucleo();
void escalonador();
processo_info *retornaProcesso();
void gerenciaInterrupcoes();

//mostra que é a primeira iteraçao do nucleo e deve chamar primeiro a syscall()
int primeira_vez;


#endif
