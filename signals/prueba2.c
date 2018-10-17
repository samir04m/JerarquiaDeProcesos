#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void mySignalHandler(int sig){
    printf("Signal number is %d\n", sig);
}

int main(void){
    system("clear");

    signal(SIGIO, &mySignalHandler);

    while (1){
        printf("Proceso %d en ejercucion\n", getpid());
        sleep(2);
    }

    /* Para probar la recebcion de la señal, en otra terminal ingresar:
        kill -SIGIO pidDelProceso
    */

    return 0;
}
