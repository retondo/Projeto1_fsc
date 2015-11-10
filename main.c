#include "interface.h"
#include "nucleo.h"

int main(int argc, char * argv[]) {

    //DEFININDO SEMENTE DO RAND
    srand(time(NULL));

    cria_processos_chamada=0;
    primeira_vez=1;

    //DEFINICOES DO FORMULARIO
    FD_projeto *fd_projeto;
    fl_initialize( &argc, argv, 0, 0, 0 );
    fd_projeto = create_form_projeto( );
    fl_show_form( fd_projeto->projeto, FL_PLACE_CENTERFREE, FL_FULLBORDER, "Núcleo Gerenciador de Processos" );
    

    //INSERIR NUCLEO AQUI

    pthread_create(&T_ESCALONADOR, &T_ESCALONADOR_ATTR, (void *) &nucleo, NULL);

    //LOOP DO FORMULARIO
    fl_do_forms( );


    //FINALIZANDO FORMULARIO
    if ( fl_form_is_visible( fd_projeto->projeto ) )
        fl_hide_form( fd_projeto->projeto );
    fl_free( fd_projeto );
    fl_finish( );

    return 0;
}
