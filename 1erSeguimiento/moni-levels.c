/*
    Padre───┬─hijo1───nieto1
            ├─hijo2───nieto2─┬─bisnieto1
            │                └─bisnieto2──tataranieto1─┬─chozno1
            │                                          └─chozno2───5toNieto1
            └─hijo3───nieto3─┬─bisnieto3
                             └─bisnieto4
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(){
    int i, j, k;
    pid_t childs[3]={}, padre = getpid();
    int nivel = 0;

    for (i=0; i<3; i++){
        childs[i] = fork();
        if(childs[i] == 0){
            nivel++;
            childs[0] = fork();
            if (i>=1 && i<=2 && childs[0] == 0){
                nivel++;
                for (j=0; j<2; j++){
                    childs[j] = fork();
                    if(childs[j] == 0){
                        nivel++;
                        if (i == 1 && j == 1) {
                            childs[0] = fork();
                            if (childs[0] == 0){
                                nivel++;
                                for (k=0; k<2; k++){
                                    childs[k] = fork();
                                    if (childs[k] == 0){
                                        nivel++;
                                        if (k == 1){
                                            childs[0] = fork();
                                            if (childs[0] == 0) nivel++;
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
            }
            if (i<1 && childs[0] == 0) nivel++;
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

    printf("Proceso %d en nivel %d  \n", getpid(), nivel);

    return 0;
}
