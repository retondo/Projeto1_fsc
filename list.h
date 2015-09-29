#ifndef LISTA_H_
#define LISTA_H_

#include "pcb.h"

typedef struct Node {
    pcb *info;
    struct Node *prox;
} node;

typedef struct List {
    node *begin;
    node *end;
} list;

void list_start();
int list_null(list *l);
void list_insert(list *l, node element, int position); //element tipo node??
void list_delete(list *l, node element);

#endif
