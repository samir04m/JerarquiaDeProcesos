#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    pid_t childs[7]={}, padre = getpid();
    int i, j, k;

    for (i=0; i<3; i++) {
        childs[i] = fork();
        if (childs[i] == 0){
            if (i == 1) {
                for(j=0; j<2; j++){
                    childs[j] = fork();
                    if (childs[j] == 0){
                        if (j == 1){
                            for (k=0; k<2; k++){
                                childs[k] = fork();
                                if (childs[k] > 0) break;
                            }
                        }
                        break;
                    }
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

    // if (k == 2){
        printf("I'm the process %d\n", getpid());
        for (int s=0; s<8; s++){
            printf("[%d]-", childs[s]);
        }
        printf("\n");
    // }

    return 0;
}
