#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<wait.h>


int main(int argc, char const *argv[]){

    pid_t padre = getpid();

    fork();
    fork();
    if (!fork()){
        if(fork()) fork();
    }

    if(padre==getpid()){
        sleep(2);
        char b[500];
        sprintf(b,"pstree -lp %d",getpid());
        system(b);
    }else{
        sleep(5);
    }


    return 0;
}
