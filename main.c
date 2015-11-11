#include "nucleo.h"

int main(int argc, char * argv[]) {

    //DEFININDO SEMENTE DO RAND
    srand(time(NULL));

    cria_processos_chamada=0;
    primeira_vez=1;

    XInitThreads();

    //DEFINICOES DO FORMULARIO
    FD_projeto *fd_projeto;
    fl_initialize( &argc, argv, 0, 0, 0 );
    fd_projeto = create_form_projeto();
    fl_show_form( fd_projeto->projeto, FL_PLACE_CENTERFREE, FL_FULLBORDER, "Núcleo Gerenciador de Processos" );

    // THREAD DO NÚCLEO
    pthread_attr_setscope(&T_NUCLEO_ATTR, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_init(&T_NUCLEO_ATTR);
    pthread_create(&T_NUCLEO, &T_NUCLEO_ATTR, (void *) &nucleo, NULL);

    //LOOP DO FORMULARIO
    while(1) {
        //printf("passei antees do_forms\n");
        //fflush(stdout);
        fl_do_forms();
        sleep(1);
    }

    //pthread_join(T_ESCALONADOR, NULL);

    //FINALIZANDO FORMULARIO
    if ( fl_form_is_visible( fd_projeto->projeto ) )
        fl_hide_form( fd_projeto->projeto );
    fl_free( fd_projeto );
    fl_finish();

    return 0;
}
