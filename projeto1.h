#ifndef PROJETO1_H_
#define PROJETO1_H_

#include <forms.h>

/* Forms and Objects */

typedef struct {
    FL_FORM   * projeto;
    void      * vdata;
    char      * cdata;
    long        ldata;
    FL_OBJECT * lista_programas;
    FL_OBJECT * dados_programas;
    FL_OBJECT * carregar;
    FL_OBJECT * executar;
    FL_OBJECT * log;
    FL_OBJECT * acontecimentos;
} FD_projeto;

FD_projeto * create_form_projeto( void );

#endif /* PROJETO1_H_ */
