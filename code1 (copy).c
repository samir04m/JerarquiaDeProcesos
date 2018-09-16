/* Realizar la siguente estructura
            h1   n1
          /     /
    Padre ----h2----n2---bn1
          \     \
           h3    n3
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int i, j;
    pid_t childs[2], padre = getpid();

    for (i=0; i<3; i++){
        childs[i] = fork();
        if (childs[i] == 0){
            if (i ==  1){
                for (j=0; j<3; j++){
                    childs[j] = fork();
                    if (childs[j] == 0){
                        if (j == 1){
                            fork();
                        }
                        break;
                    }
                }
            }
            break;
        }
    }
    if(i==2){
        wait(NULL);
    }

    if(padre==getpid()){
        char b[500];
        sprintf(b,"pstree -lp %d",getpid());
        system(b);
    }else{
        sleep(1);
    }

    if (padre==getpid()){
        // for (i=0; i<7; i++) wait(NULL);
        printf("Termino el padre\n");
    }else{
        printf("Termino el hijo\n");
    }

    return 0;
}
