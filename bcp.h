#ifndef BCP_H_
#define BCP_H_

#define PROCESSO_INATIVO 0;
#define PROCESSO_EXECUTANDO 1;
#define PROCESSO_BLOQUEADO 2;
#define PROCESSO_PRONTO 3;
#define PROCESSO_ESPERANDO 4;

typedef struct {
    char nome[30];
    long segmento_id;
    int prioridade;
    long segmento_tam;
    char semaforos[10];
} processo_info;

#endif
