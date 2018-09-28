#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

int main()
{
    pid_t childs[3], padre = getpid();
    int i, n;
    int fd1[2];
    int fd2[2];
    char buffer[1024];

    pipe(fd1);
    pipe(fd2);

    

}
