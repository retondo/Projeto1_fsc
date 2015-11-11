#include "interface.h"
#include "nucleo.h"

//****************************************************************************
//*********************** CALLBACK DOS BOTOES DO FORMULARIO *******************
//****************************************************************************
int callback_carregar_sint_chamada = 0;
int arquivo_escolhido = 0;



void prgs_callback(FL_OBJECT *obj, long user_data) {
    fdui = obj->form->fdui;

    callback_carregar_sint_chamada = 1;
    arquivo_escolhido = 1;
    cria_processos_chamada = 1;
}

void limpar_callback(FL_OBJECT *obj, long user_data) {
    fdui = obj->form->fdui;
    fl_clear_browser(fdui->acontecimentos);
}

//****************************************************************************
//******************************** FORMULARIO ********************************
//****************************************************************************

FD_projeto *create_form_projeto(void)
{
    FL_OBJECT *obj;
    fdui = ( FD_projeto * ) fl_malloc( sizeof *fdui );

    fdui->vdata = fdui->cdata = NULL;
    fdui->ldata = 0;

    fdui->projeto = fl_bgn_form( FL_NO_BOX, 600, 400 );

    obj = fl_add_box( FL_FLAT_BOX, 0, 0, 600, 400, "" );

    fdui->dados_programas = obj = fl_add_browser( FL_NORMAL_BROWSER, 20, 210, 200, 150, "" );

    fdui->acontecimentos = obj = fl_add_browser( FL_NORMAL_BROWSER, 20, 20, 200, 150, "" );

    fdui->carregar = obj = fl_add_button( FL_NORMAL_BUTTON, 5, 180, 110, 20, "Carregar Programa" );
    fl_set_object_callback(obj, prgs_callback, 0);

    fdui->log = obj = fl_add_browser( FL_NORMAL_BROWSER, 250, 10, 320, 350, "" );

    obj = fl_add_button( FL_NORMAL_BUTTON, 185, 180, 60, 20, "Limpar" );
    fl_set_object_callback(obj, limpar_callback, 0);

    fl_end_form();

    fdui->projeto->fdui = fdui;

    return fdui;
}
