#include <lista.h>
#include <stdio.h>
#include <stdlib.h>

void iniciar() {
    no *lista = (no *) malloc(sizeof(no));
    no *inicio = (no *) malloc(sizeof(no));

    if (!lista) {
        printf("Não foi possível criar uma lista. Memória insuficiente!!");
        exit(1);
    } else {
        lista->prox = NULL;
        inicio = lista;
        tam = 0;
    }
}

int vazio() {
    if (inicio == NULL)
        return 0;
    else
        return 1;
}
