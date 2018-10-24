#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>

void manejador(){}

int main(){
    system("clear");
    int np, k, i;

    printf("Ingrese el numero de procesos: ");
    scanf("%d", &np);
    printf("Ingrese el numero de iteraciones: ");
    scanf("%d", &k);

    signal(SIGUSR1, manejador);
    pid_t childs[np], root=getpid();
    for(i=0; i<np; i++) if( !(childs[i] = fork()) ) break;

    for (int j=0; j<k; j++){
        if (i == np){
            sleep(1);
            printf("Soy el Padre [%d]\n", getpid());
            kill(childs[np-1], SIGUSR1);
            pause();
            printf("Soy el Padre [%d]\n", getpid());
        }else{
            pause();
            printf("Soy el Hijo %d [%d]\n", i+1, getpid());
            if (i > 0) kill(childs[i-1], SIGUSR1);
            else kill(getppid(), SIGUSR1);
        }
    }

    if(root==getpid()){
        printf("\n");
        char b[500];
        sprintf(b,"pstree -lp %d",getpid());
        system(b);
    }else sleep(3);

    return 0;
}
