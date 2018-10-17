#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/types.h>

void manejador(){}

int main(){
    system("clear");
    signal(SIGUSR1, manejador);
    pid_t pids[4], padre = getpid();
    int i, j = -1;

    for(i = 3; i >= 0;i--)
        if(!(pids[i] = fork())){
            if(i != 3) pids[i] = fork();
            else
                for(j = 0; j < 2; j++) if(!(pids[j] = fork())) break;
            break;
        }


    if(i == -1){
        sleep(2);
        char* a = (char*)calloc(50, 1);
        sprintf(a, "pstree -lp %d", getpid());
        system(a);
    }else sleep(3);


    if(getppid() == padre || getpid() == padre){ //si soy hijo del proceso root o soy el proceso root
        if(i != 3){
            if(i == 1) sleep(3);
            else pause();
            printf("1 Proceso: %d\n", getpid());

            if(i == -1) goto goAhead;
            kill(pids[i], SIGUSR1);
            pause();
            printf("2 Proceso: %d\n", getpid());

            goAhead:
            if(i != 0) kill(pids[i+1], SIGUSR1);
        }else{
            pause();
            printf("3 Proceso: %d\n", getpid());
            kill(pids[1], SIGUSR1);
            pause();
            printf("4 Proceso: %d\n", getpid());
            kill(getppid(), SIGUSR1);
        }
    }else{ //si soy hijo del primer hijo del proceso root, es decir nieto del root
        pause();
        printf("5 Proceso: %d\n", getpid());
        if(j != 1) kill(getppid(), SIGUSR1); //si soy cualquier nieto excepto el segundo hijo del primer hijo del root, envio una señal a mi padre
        else kill(pids[0], SIGUSR1); //si soy el segundo hijo del primer hijo del root, envio señal al primer hijo de mi padre, es decir hermano
    }

    return 0;
}
