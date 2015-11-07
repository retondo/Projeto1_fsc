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

    while (1) {
        sorteio = interruptControl();
        switch (sorteio) {
        case 0:
            sysCall();
            break;
        case 1:
            processInterrupt();
            break;
        case 2:
            //semaphoreP();
            break;
        case 3:
            //semaphoreV();
            break;
        case 4:
            ioRequest();
            break;
        case 5:
            ioFinish();
            break;
        case 6:
            memLoadRequest();
            break;
        case 7:
            memLoadFinish();
            break;
        case 8:
            fsRequest();
            break;
        case 9:
            fsFinish();
            break;
        case 10:
            processCreate();
            break;
        case 11:
            processFinish();
            break;
        default:
            break;
        }
    }
}

int sysCall() {
    int num;

    // Chama o File Selector que retorna o caminho do arquivo selecionado
    // TODO: Inserir semáforo
    fname = fl_show_file_selector( "Selecione o arquivo sintetico", "", "", "" );
    // TODO: Liberar semáforo
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

int readFile(const char *caminho) {
    FILE *f;

    if (!(f = fopen(caminho, "rt"))) {
        fl_add_browser_line(fdui->log, "Nao foi possivel abrir o arquivo!!\nPor favor, selecione um arquivo valido.");
        sysCall();
    } else {
        criaProcessoBCP(f);

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

void criaProcessoBCP(FILE *f) {
    // Aloca as informaçoes do processo na memória
    processo_info *pro = (processo_info *) malloc(sizeof(processo_info));

    char nome[30], sem[10], linha[50];
    long seg_id, seg_tam;
    int prioridade, i;

    // Captura somente o cabeçalho
    for (i = 0; (fgets(linha, 50, f)) != NULL; i++) {
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

    pro->nome = nome;
    pro->segmento_id = seg_id;
    pro->prioridade = prioridade;
    pro->segmento_tam = seg_tam;
    pro->semaforos = sem;

    // Bloquear semáforo
    // Testa se o processo(programa sintetico) foi devidamente criado
    if (processCreate(pro))
        fl_add_browser_line(fdui->log, "Processo criado e inserido no BCP");
    else
        fl_add_browser_line(fdui->log, "Nao foi possivel inserir o processo no BCP");
    // Liberar semáforo

}

void processInterrupt() {

}

/*void semaphoreP(char sem) {

}

void semaphoreV(char sem) {

}*/

void ioRequest() {
    fl_add_browser_line(fdui->log, "E/S requisitada.");
}

void ioFinish() {
    fl_add_browser_line(fdui->log, "E/S finalizada.");
}

void memLoadRequest() {
    fl_add_browser_line(fdui->log, "");
}

void memLoadFinish() {

}

void fsRequest() {

}

void fsFinish() {

}

// Retorna 0 se o processo foi devidamente criado
int processCreate(processo_info *processo) {


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














