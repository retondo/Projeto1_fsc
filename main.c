#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <dirent.h>

void readDirectory();

int main(void)
{
    srand((unsigned) time(NULL));               //Define a semente do rand()
    setlocale(LC_ALL, "Portuguese");            //Define a linguagem pt-br

    readDirectory();


    return 0;
}

int interruptControl() {
    return rand()%20;
}

/*void readFile(char *nameFile[])
{
    if (!(f = fopen(nameFile, "r"))) {
        printf("Não foi possível abrir o arquivo %c!!", nameFile);
        exit(1);
    } else {
        while ()
    }
}*/

// Le os arquivos dentro de um diretorio e retorna seu nome
void readDirectory() {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("/home/renan/projeto1_fsc")) != NULL) {
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
