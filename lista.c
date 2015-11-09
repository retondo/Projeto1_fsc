#include "lista.h"

// Retorna 1 se vazia, senão retorna 0
int lista_vazia(lista *l) {
    if (l->inicio == NULL)
        return 1;
    else
        return 0;
}

int lista_iniciar(lista *l) {
    // Os argumentos da lista são iniciados como nulos se a lista existir
    if (l) {
        l->inicio = NULL;
        l->fim = NULL;
        l->tam = 0;
        return 1;
    } else {
        printf("A lista não existe!!");
        return 0;
    }
}

void lista_inserir(lista *l, processo_info *elemento) {
    // Alocando o nó novo na memória
    no *novo = (no *) malloc(sizeof(no));
    // Apontando o nó novo para o nó elemento
    novo->info = elemento;

    // Insere no começo
    // Se a lista estiver vazia insere o novo nó
    if (lista_vazia(l)) {
        l->inicio = novo;
        l->fim = novo;
        l->tam++;
    } else {
        no *atual = (no *) malloc(sizeof(no));
        no *anterior = (no *) malloc(sizeof(no));
        anterior = NULL;
        atual = l->inicio;

        // Percorre a lista até achar o nó de menor prioridade (0 tem maior prioridade) ou até achar o fim
        while(novo->info->prioridade >= atual->info->prioridade) {
            anterior = atual;
            atual = atual->prox;
            if (atual == NULL)
                break;
        }
        // Insere no meio ou no fim e atualiza o tamanho da lista
        if (anterior != NULL)
            anterior->prox = novo;
        novo->prox = atual;
        l->tam++;

        // Atualiza o inicio
        if (l->inicio == atual)
            l->inicio = novo;

        // Atualiza o fim da lista
        if (novo->prox == NULL)
            l->fim = novo;
    }
}

void lista_remover(lista *l, no *elemento) {
    // Aloca o nó excluir na memória
    no *excluir = (no *) malloc(sizeof(no));
    excluir = elemento;

    // Exclui o nó da lista e atualiza a lista
    if (l->inicio == excluir && l->fim == excluir) {
        l->inicio = NULL;
        l->fim = NULL;
        l->tam = 0;
    } else if (l->inicio == excluir) {
        l->inicio = excluir->prox;
        l->tam--;
    }
    free(excluir);
}

void imprimir_lista(lista *l) {
    no *n = (no *) malloc(sizeof(no));
    n = l->inicio;

    while(n != NULL) {
        printf("%i\n", n->info->prioridade);
        n = n->prox;
    }

    //free(n);
}





