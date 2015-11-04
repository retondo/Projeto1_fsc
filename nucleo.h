#ifndef NUCLEO_H_
#define NUCLEO_H_

#include "lista.h"

// COMO PEDIDO NO PROJETO, SOMENTE AS FUNÇÕES 2, 3, 10 E 11 FORAM IMPLEMENTADAS

int interruptControl();     // Gera os numeros aleatórios
void processInterrupt();    // 1 - Interrupção gerada pelo final do quantum time de um processo
void semaphoreP(char sem);          // 2 - Tratamento de bloqueio de processo
void semaphoreV(char sem);          // 3 - Tratamento de desbloqueio de processo
void ioRequest();           // 4 - Chamada de operação de E/S
void ioFinish();            // 5 - Sinalização de final de E/S
void memLoadRequest();      // 6 - Chamada de operação de carregamento na memória
void memLoadFinish();       // 7 - Sinalização de final de carregamento
void fsRequest();           // 8 - Chamada para operação no sistema de arquivos
void fsFinish();            // 9 - Sinalização de final de operação no sistema de arquivos
void processCreate();       // 10 - Chamada para a criação de um processo no BCP
void processFinish();       // 11 - Chamada para terminar a existência de um processo no BCP
void exec(int tempo);
void read(int trilha);
void write(int trilha);
int readFile(const char caminho);
int sysCall();

#endif
