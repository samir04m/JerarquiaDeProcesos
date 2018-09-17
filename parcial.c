#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char const *argv[]){
    pid_t padre = getpid();
    int i, j, k;

    fork();
    fork();
    if(fork() == 0){
        fork();
    }

    if(padre==getpid()){
        char b[500];
        sprintf(b,"pstree -lp %d",getpid());
        system(b);
        wait(NULL);
    }else{
        sleep(1);
    }

    return 0;
}
