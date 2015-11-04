#ifndef LISTA_H_
#define LISTA_H_

#include <stdio.h>
#include <stdlib.h>
#include "bcp.h"

typedef struct No {
    processo_info *info;
    struct No *prox;
} no;

typedef struct Lista {
    no *inicio;
    no *fim;
    int tam;
} lista;

void lista_iniciar(lista *l);
void lista_inserir(lista *l, no *elemento);
void lista_remover(lista *l, no *elemento);
void imprimir_lista(lista *l);
int lista_vazia(lista *l);

#endif
