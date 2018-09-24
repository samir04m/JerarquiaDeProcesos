#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char const *argv[]){
    pid_t padre = getpid();
    int i, j, k, n;

    printf("Ingrese el valor de  n:");
    scanf("%d", &n);

    for (i=0; i<n; i++){
        if(!fork()){
            if(i==n-1){
                for (j=0; j<n/2; j++){
                    if(!fork()){
                        if(j==(n/2)-1){
                            for (k=0; k<n/4; k++){
                                if(!fork()){
                                    break;
                                }
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
        wait(NULL);
    }else{
        sleep(1);
    }

    return 0;
}
