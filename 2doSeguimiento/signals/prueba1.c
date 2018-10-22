#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void){
    system("clear");

    while (1){
        printf("Proceso %d en ejercucion\n", getpid());
        sleep(2);
    }
    /*
        Mientras el programa se ejecuta desde otra terminal probar los comandos:
        kill -SIGSTOP pidDelProceso
        kill -SIGCONT pidDelProceso
        kill -SIGKILL pidDelProceso
    */

    return 0;
}
