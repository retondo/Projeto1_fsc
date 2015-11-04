#ifndef PROJETO1_H_
#define PROJETO1_H_

#include <forms.h>
#include <stdlib.h>

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

FD_projeto *fdui;
const char *fname;

FD_projeto * create_form_projeto( void );
void prgs_callback(FL_OBJECT *obj, long user_data);
void prgsAuto_callback(FL_OBJECT *obj, long user_data);
void sorteio_callback(FL_OBJECT *obj, long user_data);
void limpar_callback(FL_OBJECT *obj, long user_data);
void cria_processo_callback(FL_OBJECT *obj, long user_data);

#endif /* PROJETO1_H_ */
