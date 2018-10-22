#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

void manejador(){}

int main(){
    system("clear");
    signal(SIGUSR1, manejador);
    pid_t childs[2], root = getpid();
    int i;

    for (i=0; i<2; i++) if( !(childs[i] = fork()) ) break;

    if (i == 2){
        sleep(1);
        printf("Soy el padre [%d]\n", getpid());
        kill(childs[1], SIGUSR1);
        pause();
        printf("Soy el padre [%d]\n", getpid());
    }else{
        pause();
        printf("Soy el hijo %d [%d]\n", i+1, getpid());
        if (i == 1) kill(childs[0], SIGUSR1);
        else kill(getppid(), SIGUSR1);
    }

    if(root==getpid()){
        printf("\n");
        char b[500];
        sprintf(b,"pstree -lp %d",getpid());
        system(b);
    }else sleep(3);


    return 0;
}
