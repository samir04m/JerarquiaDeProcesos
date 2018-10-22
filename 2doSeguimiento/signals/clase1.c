#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>

void manejador(int s){
    printf("Signal No. [%d] proceso [%d]\n", s, getpid());
}

int main(){

    /*
        Casa una de las señales representa un evento espesifico
        para ver la señales colocar en teminal -> kill -l

        Signal retorna el puntero de la funcion que tenia por defecto
        l = signal(SIGINT, myFuncion)
        en l guarda la funcion que tenia por defecto
        asi que hacemos: signal(SIGINT, l) para dejarlo como estaba
        esto se hace en programas grandes

        Las señales SIGUSR1 y SIGUSR2, son señales del usuario, estas no son
        generada por el sistema operativo por lo cual seran las que utilizaremos

    */
    int c;
    signal(SIGUSR1, manejador);
    if ( !(c = fork()) ){
        pause();
    }else{
        sleep(1);
        kill(c, SIGUSR1);
        wait(NULL);
    }

    return 0;
}
