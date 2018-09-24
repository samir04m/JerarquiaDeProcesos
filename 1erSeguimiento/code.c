/* Crear cuatro procesos, uno abajo del otro, padre, hijo, nieto, bisnieto*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    pid_t pid;
    int n = 4;
    int i;
    for (i=0; i<n; i++){
        pid = fork();
        if (pid > 0) break;
    }

    printf("Padre %d saliendo --- creo hijo %d\n", getpid(), pid);
    exit(0);
}
