/* Realizar la siguente estructura
    Padre ─┬──h1───n1
           ├──h2───n2───bn1
           ├──h3───n3───bn2───tn1
           ├──h4───n4───bn2
           └──h5───n5
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int i, j, k;
    pid_t childs[5]={}, padre = getpid();


    for (i=0; i<5; i++){
        childs[i] = fork();
        if (childs[i] == 0) {
            childs[0] = fork();
            if(i>=1 && i<=3 && childs[0] == 0){
                childs[0] = fork();
                if(i==2 && childs[0] == 0){
                    childs[0] = fork();
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

    printf("\nProcess %d\n", getpid());
    for (int s=0; s<5; s++){
        printf("[%d|%d]-", s, childs[s]);
    }


    // if (padre==getpid()){
    //     // for (i=0; i<8; i++) wait(NULL);
    //     printf("Termino el padre\n");
    // }else{
    //     printf("Termino el hijo\n");
    // }

    return 0;
}
