#include "interface.h"
#include "nucleo.h"
#include "locale.h"
//#include <pthread.h>

int main(int argc, char * argv[]) {

    //DEFINIÇÃO DOS PARAMETROS DAS THREADS
    /*pthread_t functions[20];
    pthread_attr_t atrib;
    pthread_attr_init(&atrib);
    pthread_attr_setscope(&atrib,PTHREAD_SCOPE_PROCESS);
    pthread_create(&functions[1],&atrib,interruptControl,NULL);
    */

    //DEFININDO SEMENTE DO RAND
    srand(time(NULL));
    //DEFINE A LOCALIZAÇÃO PARA USO DE CARACTERES ESPECIAIS
    setlocale(LC_ALL, "Portuguese");

    //DEFINICOES DO FORMULARIO
    FD_projeto *fd_projeto;
    fl_initialize( &argc, argv, 0, 0, 0 );
    fd_projeto = create_form_projeto( );
    fl_show_form( fd_projeto->projeto, FL_PLACE_CENTERFREE, FL_FULLBORDER, "Núcleo Gerenciador de Processos - Projeto 2" );
    

    //INSERIR NUCLEO AQUI

    //LOOP DO FORMULARIO
    sysCall();
    fl_do_forms( );

    //FINALIZANDO FORMULARIO
    if ( fl_form_is_visible( fd_projeto->projeto ) )
        fl_hide_form( fd_projeto->projeto );
    fl_free( fd_projeto );
    fl_finish( );

    return 0;
}
