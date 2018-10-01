#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <sys/types.h>

int main()
{
    pid_t childs[3], padre = getpid();
    int i, j=-1, n, npipes = 6;
    int fd[npipes][2]; //filas (n tuberias), columnas


    for(int k=0; k<npipes; k++) if(pipe(fd[k])) exit(-1);

    for (i=0; i<3; i++){
        if (!(childs[i] = fork())){
            if (i == 2){
                for(j=0; j<2; j++)
                    if ((childs[j] = fork())) break;
            }
            break;
        }
    }

    if (getpid() != padre){

        if (j > 0){
            // printf("%d hijo i=%d j=%d\n", getpid(), i, j);
            for (int k=0; k<npipes; k++){
                if ((j+2) != k) close(fd[k][0]);
                if ((j+3) != k) close(fd[k][1]);
            }
        }else{
            for (int k=0; k<npipes; k++){
                if (i != k) close(fd[k][0]);
                if ((i+1) != k) close(fd[k][1]);
            }
        }

        int TAM;

        if (j > 0){
            read(fd[j+2][0], &TAM, sizeof(int));
            char info[TAM];
            n = read(fd[j+2][0], info, TAM);
            info[n] = '\0';
            printf("Process %d: leido: %s\n", getpid(), info);
            write(fd[j+3][1], &TAM, sizeof(int));
            write(fd[j+3][1], info, TAM);
            close(fd[j+2][0]);
            close(fd[j+3][1]);
        }else{
            read(fd[i][0], &TAM, sizeof(int));
            char info[TAM];
            n = read(fd[i][0], info, TAM);
            info[n] = '\0';
            printf("Process %d: leido: %s\n", getpid(), info);
            write(fd[i+1][1], &TAM, sizeof(int));
            write(fd[i+1][1], info, TAM);
            close(fd[i][0]);
            close(fd[i+1][1]);
        }


    }else{
        close(fd[0][0]);
        for (int k=1; k<npipes; k++){
            if (k != 5) close(fd[k][0]);
            close(fd[k][1]);
        }
        char buffer[1024];
        strcpy(buffer, "Hola soy mensaje");
        int TAM = strlen(buffer);
        write(fd[0][1], &TAM, sizeof(int));
        write(fd[0][1], buffer, TAM);
        close(fd[0][1]);
    }


    if (padre==getpid()){
        char b[500];
        sprintf(b,"pstree -lp %d", getpid());
        system(b);
        // for( i = 0; i < 3; i++) wait(NULL);
    } else{
        sleep(3);
    }

    return 0;
}
