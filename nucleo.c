#include "nucleo.h"
#include "interface.h"
#include <string.h>

int tempo, trilha, i = 0;
char sem[10];

int interruptControl() {
    return (rand()%11)+1;
}

void nucleo() {

    inicializarLista();
    inicializarThreads();
    inicializarSemaforos();

    pthread_create(&T_ESCALONADOR, &T_ESCALONADOR_ATTR, (void *) &escalonador, NULL);
    gerenciaInterrupcoes();
}

void gerenciaInterrupcoes() {
    int sorteio;

    fl_add_browser_line_f(fdui->acontecimentos, "Por favor, \ncarregue um arquivo sintetico.");
    while (!callback_carregar_sint_chamada || !arquivo_escolhido)
        usleep(200);

    while (1) {
        sorteio = interruptControl();

        if (cria_processos_chamada) {
            sorteio = 0;
        }
        cria_processos_chamada = 0;
        fl_add_browser_line_f(fdui->acontecimentos, "Sorteio: %i", sorteio);
        fl_set_browser_bottomline(fdui->acontecimentos, 1000000);
        switch (sorteio) {
        case 0:
            sysCall();
            break;
        case 2:
            //fl_add_browser_line(fdui->log, "Gerenciando bloqueio de semaforo");
            //pthread_create(&T_SEMAPHORE_P, &T_SEMAPHORE_P_ATTR, (void *) &semaphoreP, NULL);
            break;
        case 3:
            //fl_add_browser_line(fdui->log, "Gerenciando liberacao de semaforo");
            //pthread_create(&T_SEMAPHORE_V, &T_SEMAPHORE_V_ATTR, (void *) &semaphoreV, NULL);
            break;
        case 10:
            pthread_create(&T_PROCESS_CREATE, &T_PROCESS_CREATE_ATTR, (void *) &processCreate, NULL);
            pthread_join(T_PROCESS_CREATE, NULL);
            break;
        case 11:
            pthread_create(&T_PROCESS_FINISH, &T_PROCESS_FINISH_ATTR, (void *) &processFinish, NULL);
            break;
        default:
            break;
        }
        sleep(1);
    }
}

void executarInstrucao(int instrucao) {
    switch(instrucao) {
    case 1:
        exec();
        break;
    case 2:
        read(trilha);
        break;
    case 3:
        write(trilha);
        break;
    case 4:
        //call();
        break;
    case 5:
        //semaphoreP(sem);
        break;
    case 6:
        //semaphoreV(sem);
    default:
        break;
    }
}

void sysCall() {
    pthread_create(&T_PROCESS_CREATE, &T_PROCESS_CREATE_ATTR, (void *) &processCreate, NULL);
    pthread_join(T_PROCESS_CREATE, NULL);
}

processo_info *retornaProcesso() {
    processo_info *pro = (processo_info *) malloc(sizeof(processo_info));

    char nome[30], sem[10], linha[50];
    long seg_id, seg_tam;
    int prioridade, i;

    // Captura somente o cabeçalho
    for (i = 0; i <= 5; i++) {
        fgets(linha, 50, f);
        switch (i) {
        case 0:
            strcpy(nome, linha);
            break;
        case 1:
            seg_id = atol(linha);
            break;
        case 2:
            prioridade = atoi(linha);
            break;
        case 3:
            seg_tam = atol(linha);
            break;
        case 4:
            strcpy(sem, linha);
            break;
        default:
            break;
        }
    }

    fclose(f);

    strcpy(pro->nome, nome);
    pro->segmento_id = seg_id;
    pro->prioridade = prioridade;
    pro->segmento_tam = seg_tam;
    strcpy(pro->semaforos, sem);
    strcpy(pro->caminho, fname);

    return pro;
}

void readFile(const char *caminho) {
    FILE *file;
    char acao[15], linha;
    int i;

    if (!(file = fopen(caminho, "r"))) {
        fl_add_browser_line(fdui->log, "Nao foi possivel abrir o arquivo!!\nPor favor, selecione um arquivo valido.");
    } else {
        fl_add_browser_line_f(fdui->dados_programas, "========== Executando processo ==========");
        for (i = 0; !feof(file); i++) {
            if (i >= 6) {
                linha = fgetc(file);
                if (linha == 'e') {
                    fscanf(file, "%s %i\n", acao, &tempo);
                    executarInstrucao(1);
                } else if (linha == 'r') {
                    fscanf(file, "%s %i\n", acao, &trilha);
                    executarInstrucao(2);
                } else if (linha == 'w') {
                    fscanf(file, "%s %i\n", acao, &trilha);
                    executarInstrucao(3);
                } else if (linha == 'c') {
                    fscanf(file, "all(%s)\n", acao);
                    executarInstrucao(4);
                } else if (linha == 'P') {
                    fscanf(file, "(%c)\n", acao);
                    executarInstrucao(5);
                } else if (linha == 'V') {
                    fscanf(file, "(%c)\n", acao);
                    executarInstrucao(6);
                }
            }
        }
        // Finaliza o processo
        fl_add_browser_line_f(fdui->log, "Processo em execucao finalizado com sucesso.");
        pthread_create(&T_PROCESS_FINISH, &T_PROCESS_FINISH_ATTR, (void *) &processFinish, NULL);
        pthread_join(T_PROCESS_FINISH, NULL);
    }
}

void escalonador() {
    while (1) {
        if (!lista_vazia(bcp)) {
            usleep(2000);
            sem_wait(&S_LISTA);
            pthread_create(&T_READFILE, &T_READFILE_ATTR, (void *) &readFile, (void *) fname);
            sem_post(&S_LISTA);
        }
    }
}

/*void semaphoreP(char sem) {

}

void semaphoreV(char sem) {

}*/
void showFileSelector(FL_OBJECT *obj, long user_data) {
    fdui = obj->form->fdui;

    sem_wait(&S_FILE_SELECTOR);
    fname = fl_show_fselector("Carregar programa", "", "", "");
    sem_post(&S_FILE_SELECTOR);
}

void processCreate() {
    processo_info *p;

    showFileSelector(fdui->carregar, 0);
    if (!(f = fopen(fname, "r"))) {
            fl_add_browser_line(fdui->log, "Nao foi possivel abrir o arquivo!!\n Processo nao criado");
            return;
    }
    sem_wait(&S_LISTA);
    p = retornaProcesso();
    lista_inserir(bcp, p);
    fl_add_browser_line_f(fdui->log, "Processo %s criado no BCP", p->nome);
    sem_post(&S_LISTA);
}

void processFinish() {
    sem_wait(&S_LISTA);
    if (!lista_vazia(bcp)) {
        fl_add_browser_line_f(fdui->log, "Processo em execucao finalizado", bcp->inicio->info->nome);
        lista_remover(bcp);
    }
    sem_post(&S_LISTA);
}

void exec() {
    fl_add_browser_line_f(fdui->dados_programas, "Executando");
    usleep(20);
}

void read(int trilha) {
    fl_add_browser_line_f(fdui->dados_programas, "Trilha %i lida", trilha);
    usleep(20);
}

void write(int trilha) {
    fl_add_browser_line_f(fdui->dados_programas, "Dados escritos na trilha %i", trilha);
    usleep(20);
}

void inicializarLista() {
    fl_add_browser_line(fdui->log, "Inicializando lista de processos...");
    bcp = (lista *) malloc(sizeof(lista));
    if(lista_iniciar(bcp))
        fl_add_browser_line(fdui->log, "Feito.");
    else {
        fl_add_browser_line(fdui->log, "Fatal Error: Nao foi possivel criar a lista de processos!!");
        exit(1);
    }
}

void inicializarThreads() {
    pthread_attr_setscope(&T_READFILE_ATTR, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setscope(&T_PROCESS_CREATE_ATTR, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setscope(&T_PROCESS_FINISH_ATTR, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setscope(&T_SEMAPHORE_P_ATTR, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setscope(&T_SEMAPHORE_V_ATTR, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setscope(&T_ESCALONADOR_ATTR, PTHREAD_SCOPE_SYSTEM);

    pthread_attr_init(&T_READFILE_ATTR);
    pthread_attr_init(&T_PROCESS_CREATE_ATTR);
    pthread_attr_init(&T_PROCESS_FINISH_ATTR);
    pthread_attr_init(&T_SEMAPHORE_P_ATTR);
    pthread_attr_init(&T_SEMAPHORE_V_ATTR);
    pthread_attr_init(&T_ESCALONADOR_ATTR);
}

void inicializarSemaforos() {
    sem_init(&S_LISTA, 1, 1);
    sem_init(&S_FILE_SELECTOR, 1, 1);
}

void ioRequest() {
    // NÃO IMPLEMENTADA
}

void ioFinish() {
    // NÃO IMPLEMENTADA
}

void memLoadRequest() {
    // NÃO IMPLEMENTADA
}

void memLoadFinish() {
    // NÃO IMPLEMENTADA
}

void fsRequest() {
    // NÃO IMPLEMENTADA
}

void fsFinish() {
    // NÃO IMPLEMENTADA
}

void processInterrupt() {
    // NÃO IMPLEMENTADA
}











