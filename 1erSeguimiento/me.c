#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char const *argv[]){
    pid_t h, padre = getpid();
    int i, j, k, n, nivel = 0;

    printf("Ingrese el valor de n: \n");
    scanf("%d", &n);

    for (i=0; i<n; i++){
        h = fork();
        if(h == 0){
            nivel++;
            if (i>0){
                for (j=0; j<i; j++){
                    for (k=0; k<nivel+1; k++){
                        h = fork();
                        if(h == 0){
                            nivel++;
                            break;
                        }
                    }
                    if (h > 0) break;
                }
            }
            break;
        }
    }

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
