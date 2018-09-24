/* Realizar la siguente estructura
    Padre ─┬──h1───n1
           ├──h2───n2─┬─bn1
           │          └─bn2
           └──h3───n3
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int i, j, k;
    pid_t childs[3]={}, padre = getpid();


    for (i=0; i<3; i++){
        childs[i] = fork();
        if (childs[i] == 0) {
            childs[0] = fork();
            if(i==1 && childs[0] == 0){
                for (k=0; k<2; k++){
                    childs[k] = fork();
                    if (childs[k] == 0) break;
                }
            }
            break;
        }
    }

    if(padre==getpid()){
        char b[500];
        sprintf(b,"pstree -lp %d",getpid());
        system(b);
    }else{
        sleep(1);
    }

    // printf("I'm the process %d\n", getpid());
    // for (int s=0; s<3; s++){
    //     printf("[%d]-", childs[s]);
    // }
    // printf("\n");

    // if (padre==getpid()){
    //     // for (i=0; i<8; i++) wait(NULL);
    //     printf("Termino el padre\n");
    // }else{
    //     printf("Termino el hijo\n");
    // }

    return 0;
}
