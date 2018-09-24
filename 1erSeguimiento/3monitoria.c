#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int nivel = 0;

void crearProcesos(int n){
    if (n > 0){
        pid_t *childs = (pid_t*)calloc(n, sizeof(pid_t));
        for (int i=0; i<nivel+3; i++){
            childs[i] = fork();
            if(childs[i] == 0){
                nivel++;
                if (i == (nivel+1)/2 && (n-1) != 0){
                    childs[i] = fork();
                    if (childs[i] == 0){
                        nivel++;
                        crearProcesos(n-1);
                    }
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

    // printf("Porceso %d en nivel %d\n", getpid(), nivel);

    return 0;
}
