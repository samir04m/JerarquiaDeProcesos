#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

int main(){
    system("clear");
    pid_t childs[2], root = getpid();
    int i, fd1[2], fd2[2];

    if(pipe(fd1)) exit(-1);
    if(pipe(fd2)) exit(-1);

    for (i=0; i<2; i++) if(!(childs[i] = fork())) break;

    if (getpid() != root){
        if(i == 0 && childs[0] == 0){
            close(fd1[0]);
            close(fd2[0]);

            FILE *file1 = fopen("file1.txt", "r");
            if (!file1){
                printf("Erro al abrir el archivo file1\n");
                exit(-1);
            }
            fseek(file1, 0, SEEK_END);
            int fsize = ftell(file1);
            fseek(file1, 0, 0);

            int nlines = 0, lsize;
            char *buffer;
            buffer = malloc((fsize)*sizeof(char));


            while(fgets(buffer, fsize, file1)){
                nlines++;
                buffer[strlen(buffer)-1] = '\0'; //cambio el salto de linea por el final de linea
                lsize = strlen(buffer);
                printf("%s\n", buffer);
            }
            printf("nlines %d\n", nlines);

            fclose(file1);
            close(fd1[1]);
            close(fd2[1]);
        }
        if(i == 1 && childs[1] == 0){
            close(fd1[1]);
            close(fd2[1]);


            close(fd1[0]);
            close(fd2[0]);
        }
    }else{
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[0]);
        close(fd2[1]);
    }
    return 0;
}
