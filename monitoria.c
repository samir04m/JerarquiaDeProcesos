/*
    Padre───┬─hijo1───nieto1─┬─bisnieto1
            │                └─bisnieto2
            ├─hijo2───nieto2─┬─bisnieto3
            │                └─bisnieto4──tataranieto1─┬─chozno1
            │                                          └─chozno2───5toNieto1
            └─hijo3───nieto3

*/
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<wait.h>

int main(int argc, char const *argv[])
{
    int i, j = -1, k = -1, nivel = 0;
    pid_t childs[3], padre = getpid();


    for( i = 0; i < 3; i++)
    {
        childs[i] = fork();
        if(childs[i] == 0){
            nivel++;
            childs[i] = fork();
            if(childs[i] == 0){
                nivel++;
                if(nivel == 2 && i == 0){
                    for( j = 0; j < 2; j++ ){
                        childs[j] = fork();
                        if(childs[j] == 0){
                            nivel ++;
                            break;
                        }
                    }
                }
                if(nivel == 2 && i == 1){
                    for( j = 0; j < 2; j++ ){
                        childs[j] = fork();
                        if(childs[j] == 0){
                            nivel ++;
                            if(nivel == 3 && j == 1){
                                childs[j] = fork();
                                if(childs[j] == 0){
                                    nivel++;

                                    for( k = 0; k < 2; k++)
                                    {
                                        childs[k] = fork();
                                        if(childs[k] == 0){
                                            nivel++;
                                            if(k == 1){
                                                childs[k] = fork();
                                                if(childs[k] == 0){
                                                    nivel++;
                                                    break;
                                                }
                                            }
                                            break;
                                        }
                                    }

                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            }
            break;
        }


    }

    if(padre==getpid()){
        sleep(2);
        char b[500];
        sprintf(b,"pstree -lp %d",getpid());
        system(b);
    }else{
        sleep(5);
    }

    printf("Proceso %d en nivel %d  \n", getpid(), nivel);

    // if (padre==getpid()){
    //     printf("Termino el padre\n");
    // }else{
    //     printf("Termino el hijo\n");
    // }

    return 0;
}
