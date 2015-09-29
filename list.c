#include <list.h>
#include <stdio.h>
#include <stdlib.h>

void list_start(list *l) {
    if (!l) {

    }
}

int list_null(list *l) {
    if (l->begin == NULL)
        return 0;
    else
        return 1;
}

void list_insert(list *l, node element, int position) {

}

void list_delete(list *l, node element) {

}
