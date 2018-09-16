#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    int h;

    switch (h = fork()) {
        case 0:
            printf("I am son %d and my father is %d\n", getpid(), getppid());
            while(1);
        case -1:
            printf("Error\n");
            exit(1);
        default:
            printf("I am the father %d and my father is %d\n", getpid(), getppid());
            while(1);
    }


}
