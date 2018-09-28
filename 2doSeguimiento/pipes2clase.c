#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

int main()
{
    pid_t childs[3], padre = getpid();
    int fd1[2], fd2[2], i, n;
    char buffer_out[1024], buffer_in[1024];

    pipe(fd1);
    pipe(fd2);

    for (i=0; i<3; i++){
        if (childs[i] = fork()) break;
    }

    if (getpid() != padre){
        if (i == 0 && childs[0] == 0){
            close(fd1[0]);
            close(fd2[0]);
            close(fd2[1]);
            strcpy(buffer_out, "Vengo del proceso i=1");
            write(fd1[1], buffer_out, strlen(buffer_out));
            close(fd1[1]);
        }
        if (i == 1 && childs[1] == 0){
            close(fd1[1]);
            close(fd2[0]);
            n = read(fd1[0], buffer_in, sizeof(buffer_out));
            buffer_in[n] = '\0';
            write(fd2[1], buffer_in, strlen(buffer_in));
            close(fd1[0]);
            close(fd2[1]);
        }
        if (i == 2 && childs[2] == 0){
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[1]);
            n = read(fd2[0], buffer_in, sizeof(buffer_out));
            buffer_in[n] = '\0';
            printf("Process %d: Leido: %s \n", getpid(), buffer_in);
            close(fd2[0]);
        }

    }else{
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[0]);
        close(fd2[1]);
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
