#include "files.h"

// Guarda as informações do programa sintético
typedef struct {
    char nome[50];
    long seg_id;
    int prioridade;
    long seg_tam;
    char sem[30];
} prog_dados;

void lerArquivo(char *nomeArquivo)
{
    FILE *f;
    char l[50];
    int i = 0;

    prog_dados *prog = (prog_dados *) malloc(sizeof(prog_dados));

    // rt siginifica que deverá ler um arquivo de texto
    if (!(f = fopen(nomeArquivo, "rt"))) {
        printf("Não foi possível abrir o arquivo %s!!\n\n", nomeArquivo);
        exit(1);
    } else {
        for (i = 0; (fgets(l, 50, f)) != NULL; i++) {
            switch (i) {
            case 0:
                strcpy(prog->nome, l);
                break;
            case 1:
                prog->seg_id = atol(l);
                break;
            case 2:
                prog->prioridade = atoi(l);
                break;
            case 3:
                prog->seg_tam = atol(l);
                break;
            case 4:
                strcpy(prog->sem, l);
                break;
            default:
                // iserir callback
                printf("%s", l);
                break;
            }
        }
    }
}

// Exibe o conteúdo de um diretório
void lerDiretorio(char *diretorio) {
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir (diretorio)) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
          if (ent->d_name[0] != '.')
            printf ("%s\n", ent->d_name);
      }
      closedir (dir);
    } else {
      /* could not open directory */
      perror ("");
      exit(1);
    }
}
