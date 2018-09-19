#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char const *argv[]){
    pid_t padre = getpid();
    // pid_t *childs = (pid_t*)calloc(n, sizeof(pid_t));
    int n;

    for (int i=0; i<2; i++){
        fork();
        if (i%2 == 0) {
            fork();
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
