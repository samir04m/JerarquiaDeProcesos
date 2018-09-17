#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

void crearProcesos(int n){
    if (n > 0){
        pid_t childs[3];
        for (int i=0; i<3; i++){
            childs[i] = fork();
            if(childs[i] == 0){
                if (i == 1 && (n-1) != 0){
                    childs[i] = fork();
                    if (childs[i] == 0) crearProcesos(n-1);
                }
                break;
            }
        }
    }
}

int main(int argc, char const *argv[]){
    pid_t padre = getpid();
    int n;

    printf("Ingrese el valor de n: \n");
    scanf("%d", &n);

    if(n < 0) abort();
    crearProcesos(n);


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
