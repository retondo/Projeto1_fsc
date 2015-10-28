#include <locale.h>
#include <time.h>
#include <forms.h>
#include "files.h"

FL_FORM *form;

/*static void InterruptControl_callback(FL_FORM *form, long user_data) {
    //fl_add_box(FL_NO_BOX, 380, 320, 120, 20, "Numero 0-20");
    fl_add_box(FL_NO_BOX, 380, 320, 120, 20, "Numero 0-20");
    printf("O número sorteado foi: %d\n", interruptControl());
}

void criarProcesso_callback(FL_OBJECT *obj, long user_data) {
    printf("Criar Processo\n");
}*/

static void criarForm(void) {

}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese");

    FL_OBJECT *interruptControl, *criarProcesso;//, *prgs, *process, *dados;

    fl_initialize(&argc, argv, "FormDemo", 0, 0);
    form = fl_bgn_form(FL_UP_BOX, 1020, 520);

    //Label do Programa sintetico
    fl_add_labelframe(FL_BORDER_FRAME, 10, 10, 250, 300, "Programas sinteticos");

    fl_add_box(FL_BORDER_BOX, 20, 30, 230, 200, "Nome do programa\nNome do programa");

    //Label dos Processos
    fl_add_labelframe(FL_BORDER_FRAME, 260, 10, 700, 300, "Processos");

    //Label dos dados do Programa sintetico
    fl_add_labelframe(FL_BORDER_FRAME, 10, 310, 250, 200, "Dados do programa selecionado");

    //Botao interruptcontrol
    interruptControl = fl_add_button(FL_NORMAL_BUTTON, 270, 320, 100, 30,"InterruptControl");
    fl_set_object_callback(interruptControl, InterruptControl_callback, 0);
    criarProcesso = fl_add_button(FL_NORMAL_BUTTON, 500, 400, 100, 30, "Criar Processo");
    fl_set_object_callback(criarProcesso, criarProcesso_callback, 0);

    fl_end_form();
    fl_show_form(form, FL_ALIGN_CENTER, FL_TRANSIENT, "Projeto 1");
    fl_do_forms();


/*
    while (1) {
        if (fl_do_forms() == yes){
            fl_add_box(FL_NO_BOX, 380, 320, 120, 20, "Do you want to Quit?");
            printf("Yes is pushed\n");
        }
    }
*/

    return 0;
}

int interruptControl() {
    return rand()%21;
}
