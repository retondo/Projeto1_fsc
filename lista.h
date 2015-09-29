#ifndef LISTA_H_
#define LISTA_H_

typedef struct Node {
    pcb *info;
    struct Node *prox;
} node;

typedef struct List {
    node *begin;
    node *end;
} list;

void list_start();
int list_null(node *lista);
void list_insert(node *lista);

#endif
