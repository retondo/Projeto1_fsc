#include "nucleo.h"
#include "interface.h"
#include <string.h>

int tempo;
int trilha;
char sem[10];

int interruptControl() {
    return rand()%12;
}

void nucleo() {
    int sorteio;

    inicializarLista();
    inicializarThreads();
    inicializarSemaforos();

    while (1) {
        sorteio = interruptControl();
        switch (sorteio) {
        case 0:
            sysCall();
            break;
        case 2:
            fl_add_browser_line(fdui->log, "Gerenciando bloqueio de semaforo");
            //pthread_create(&T_SEMAPHORE_P, &T_SEMAPHORE_P_ATTR, (void *) &semaphoreP, NULL);
            break;
        case 3:
            fl_add_browser_line(fdui->log, "Gerenciando liberacao de semaforo");
            //pthread_create(&T_SEMAPHORE_V, &T_SEMAPHORE_V_ATTR, (void *) &semaphoreV, NULL);
            break;
        case 10:
            fl_add_browser_line_f(fdui->log, "Criando processo no BCP");
            selecionaArquivo();
            pthread_create(&T_PROCESS_CREATE, &T_PROCESS_CREATE_ATTR, (void *) &processCreate, retornaProcesso());
            break;
        case 11:
            pthread_create(&T_PROCESS_FINISH, &T_PROCESS_FINISH_ATTR, (void *) &processFinish, NULL);
            break;
        default:
            break;
        }
    }
}

int sysCall() {
    int num;

    selecionaArquivo();
    pthread_create(&T_READFILE, &T_READFILE_ATTR, (void *) &readFile, fname);
    num = readFile(fname);
    switch(num) {
    case 1:
        //exec(tempo);
        break;
    case 2:
        read(trilha);
        break;
    case 3:
        write(trilha);
        break;
    case 4:
        //semaphoreP(sem);
        break;
    case 5:
        //semaphoreV(sem);
        break;
    default:
        break;
    }

    return 0;
}

void gerenciaInterrupcao() {

}

int retornaInteiroDaAcao(char linha[]) {
    int k = 1, j = 0;
    char n[10];
    while (linha[k] != '\n') {
        while (linha[k] != ' ')
            k++;
        n[j] = linha[k+1];
        j++;
    }
    return (atoi(n));
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

    pro->nome = nome;
    pro->segmento_id = seg_id;
    pro->prioridade = prioridade;
    pro->segmento_tam = seg_tam;
    pro->semaforos = sem;

    return pro;
}

void selecionaArquivo() {
    // Chama o File Selector que retorna o caminho do arquivo selecionado
    sem_wait(&S_FILE_SELECTOR);
    fname = fl_show_file_selector( "Selecione o arquivo sintetico", "", "", "" );
    sem_post(&S_FILE_SELECTOR);
    if (!(f = fopen(fname, "r"))) {
            fl_add_browser_line(fdui->log, "Nao foi possivel abrir o arquivo!!");
            selecionaArquivo();
    }
}

int readFile(const char *caminho) {
    FILE *file;

    if (!(file = fopen(caminho, "r"))) {
        fl_add_browser_line(fdui->log, "Nao foi possivel abrir o arquivo!!\nPor favor, selecione um arquivo valido.");
        sysCall();
    } else {
        processCreate(retornaProcesso());

        // Captura somente o cabeçalho
        /*for (i = 0; (fgets(linha, 50, f)) != NULL; i++) {
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
            //if (linha[0] == '\n')
                //break;
            if (linha[0] == 'e'):
                // Chama a ação lida
                exec(retornaInteiroDaAcao(linha));
                break;
            case (linha[0] == 'r'):
                read(retornaInteiroDaAcao(linha));
                break;
            case (linha[0] == 'w'):
                write(retornaInteiroDaAcao(linha));
                break;
                // Tratar o nome do processo a ser chamado
            case (linha[0] == 'c'):
                call(retornaInteiroDaAcao(linha));
                break;
            case (linha[0] == 'P'):
                semaphoreP();
                break;
            case (linha[0] == 'V'):
                semaphoreV();
                break;
            default:
                // iserir callback
                printf("%s", linha);
                break;
             }
        }*/



    }
    return 1;
}

/*int criaProcessoBCP(FILE *f) {
    // Aloca as informaçoes do processo na memória


    // Bloquear semáforo
    // Testa se o processo(programa sintetico) foi devidamente criado
    if (processCreate(pro)) {
        fl_add_browser_line_f(fdui->log, "Processo %s criado e inserido no BCP", pro->nome);
        return 1;
    } else {
        fl_add_browser_line_f(fdui->log, "Nao foi possivel inserir o processo %s no BCP", pro->nome);
        return 0;
    }
    // Liberar semáforo
}*/



/*void semaphoreP(char sem) {

}

void semaphoreV(char sem) {

}*/

// Retorna 0 se o processo foi devidamente criado
int processCreate(processo_info *processo) {
    sem_wait(&S_LISTA);
    lista_inserir(bcp, processo);
    sem_post(&S_LISTA);

    return 1;
}

void processFinish() {

}

/*void exec(int tempo) {

}

void read(int trilha) {

}

void write(int trilha) {

}
*/

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
    pthread_attr_init(&T_READFILE_ATTR);
    pthread_attr_init(&T_PROCESS_CREATE_ATTR);
    pthread_attr_init(&T_PROCESS_FINISH_ATTR);
    pthread_attr_init(&T_SEMAPHORE_P_ATTR);
    pthread_attr_init(&T_SEMAPHORE_V_ATTR);
    pthread_attr_init(&T_ESCALONADOR_ATTR);

    pthread_attr_setscope(&T_READFILE_ATTR, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setscope(&T_PROCESS_CREATE_ATTR, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setscope(&T_PROCESS_FINISH_ATTR, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setscope(&T_SEMAPHORE_P_ATTR, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setscope(&T_SEMAPHORE_V_ATTR, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setscope(&T_ESCALONADOR_ATTR, PTHREAD_SCOPE_SYSTEM);
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











