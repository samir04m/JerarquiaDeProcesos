#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){

    int pid;
    pid = fork();
    pid = fork();
    pid = fork();

    if (pid > 0){
        printf("Soy el proceso %d y soy padre, pid=%d\n", getpid(), pid);
        while(1);
    }else{
        if (pid == 0){
            printf("Soy el proceso %d y soy hijo, pid=%d\n", getpid(), pid);
            while(1);
        }else{
            printf("Error -> %d\n", pid);
        }
    }

}
