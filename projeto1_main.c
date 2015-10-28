#include "projeto1.h"
#include <stdlib.h>
#include <forms.h>
#include <dirent.h>
#include <string.h>
//#include <pthread.h>

int interruptControl() {
    return rand()%21;
}

//****************************************************************************
//*********************** CALBACK DOS BOTOES DO FORMULARIO *******************
//****************************************************************************

void prgs_callback(FL_OBJECT *obj, long user_data) {    
    FD_projeto *fdui = obj->form->fdui;
    const char *fname;
    if ( ( fname = fl_show_file_selector( "File To Load", "", "*txt", "" ) ) )
    {
        if ( ! fl_load_browser( fdui->dados_programas, fname ) )
            fl_add_browser_line( fdui->dados_programas,"NO SUCH FILE!" );
        else
            fl_add_browser_line( fdui->acontecimentos,  "Programa Carregado");
    }

}

void sorteio_callback(FL_OBJECT *obj, long user_data) {
    FD_projeto *fdui = obj->form->fdui;
    char num[100];
    sprintf(num, "O numero sorteado foi: %d", interruptControl());
    fl_add_browser_line( fdui->acontecimentos, num );
}

void limpar_callback(FL_OBJECT *obj, long user_data) {
    FD_projeto *fdui = obj->form->fdui;
    fl_clear_browser(fdui->acontecimentos);   
}

void cria_processo_callback(FL_OBJECT *obj, long user_data) {
    FD_projeto *fdui = obj->form->fdui;
    fl_add_browser_line( fdui->acontecimentos, "Funcao ainda nao implementada" );  
}


//****************************************************************************
//******************************** FORMULARIO ********************************
//****************************************************************************

FD_projeto *
create_form_projeto( void )
{
    FL_OBJECT *obj;
    FD_projeto *fdui = ( FD_projeto * ) fl_malloc( sizeof *fdui );

    fdui->vdata = fdui->cdata = NULL;
    fdui->ldata = 0;

    fdui->projeto = fl_bgn_form( FL_NO_BOX, 600, 400 );

    obj = fl_add_box( FL_FLAT_BOX, 0, 0, 600, 400, "" );

    fdui->dados_programas = obj = fl_add_browser( FL_NORMAL_BROWSER, 20, 210, 200, 150, "" );

    fdui->acontecimentos = obj = fl_add_browser( FL_NORMAL_BROWSER, 20, 20, 200, 150, "" );

    fdui->carregar = obj = fl_add_button( FL_NORMAL_BUTTON, 5, 180, 110, 20, "Carregar Programa" );
    fl_set_object_callback(obj, prgs_callback, 0);

    fdui->executar = obj = fl_add_button( FL_NORMAL_BUTTON, 60, 370, 120, 20, "Criar Processo" );
    fl_set_object_callback(obj, cria_processo_callback, 0);

    fdui->log = obj = fl_add_browser( FL_NORMAL_BROWSER, 250, 10, 320, 350, "" );

    obj = fl_add_button( FL_NORMAL_BUTTON, 120, 180, 60, 20, "Sorteio" );
    fl_set_object_callback(obj, sorteio_callback, 0);

    obj = fl_add_button( FL_NORMAL_BUTTON, 185, 180, 60, 20, "Limpar" );
    fl_set_object_callback(obj, limpar_callback, 0);

    fl_end_form( );

    fdui->projeto->fdui = fdui;

    return fdui;
}


//****************************************************************************
//**********************************INICIO MAIN*******************************
//****************************************************************************


int main(int argc, char * argv[ ] ){   

    //DEFINIÇÃO DOS PARAMETROS DAS THREADS
    /*pthread_t functions[20];
    pthread_attr_t atrib;
    pthread_attr_init(&atrib);
    pthread_attr_setscope(&atrib,PTHREAD_SCOPE_PROCESS);
    pthread_create(&functions[1],&atrib,interruptControl,NULL);           
    */

    //DEFININDO SEMENTE DO RAND
    srand((unsigned) time(NULL));

    //DEFINICOES DO FORMULARIO
    FD_projeto *fd_projeto;
    fl_initialize( &argc, argv, 0, 0, 0 );
    fd_projeto = create_form_projeto( );
    fl_show_form( fd_projeto->projeto, FL_PLACE_CENTERFREE, FL_FULLBORDER, "projeto" );
    
    //LOOP DO FORMULARIO
    fl_do_forms( );

    //FINALIZANDO FORMULARIO
    if ( fl_form_is_visible( fd_projeto->projeto ) )
        fl_hide_form( fd_projeto->projeto );
    fl_free( fd_projeto );
    fl_finish( );

    return 0;
}
