#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

int main()
{
    system("clear");
    pid_t childs[2], padre = getpid();
    int i;
    int fd1[2];
    int fd2[2];

    if(pipe(fd1)) exit(-1);
    if(pipe(fd2)) exit(-1);

    for (i=0; i<2; i++) if(!(childs[i] = fork())) break;

    if (getpid() != padre){
        if (i == 0 && childs[0] == 0){
            close(fd1[0]);
            close(fd2[0]);
            close(fd2[1]);

            FILE *file1 = fopen("file1.txt", "r");
            if (!file1){
                printf("Erro al abrir el archivo file1\n");
                exit(-1);
            }
            char linea[1024];
            int n_lineas = 0, tam_linea;
            while(fgets(linea, 1024,file1)){
                n_lineas ++;
            }
            // printf("Numero de lineas %d\n",n_lineas );
            fseek(file1, 0, 0);

            write(fd1[1], &n_lineas, sizeof(int));
            while(fgets(linea, 1024,file1)){
                linea[strlen(linea)-1] = '\0';
                printf("%s", linea);
                // printf("-->%c\n",  linea[strlen(linea)]);
                tam_linea = strlen(linea)+1;
                // printf("\ntam_linea %d\n", tam_linea);
                write(fd1[1], &tam_linea, sizeof(int));
                write(fd1[1], linea, strlen(linea));
            }
            fclose(file1);

            close(fd1[1]);
        }
        if (i == 1 && childs[1] == 0){
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[0]);

            FILE *file2 = fopen("file2.txt", "r");
            if (!file2){
                printf("Erro al abrir el archivo file2\n");
                exit(-1);
            }
            char linea[1024];
            int n_lineas = 0, tam_linea;
            while(fgets(linea, 1024, file2)){
                n_lineas ++;
            }
            // printf("Numero de lineas %d\n",n_lineas );
            fseek(file2, 0, 0);

            write(fd2[1], &n_lineas, sizeof(int));
            while(fgets(linea, 1024,file2)){
                linea[strlen(linea)-1] = '\0';
                printf("%s", linea);
                // printf("-->%c\n",  linea[strlen(linea)]);
                tam_linea = strlen(linea)+1;
                // printf("\ntam_linea %d\n", tam_linea);
                write(fd2[1], &tam_linea, sizeof(int));
                write(fd2[1], linea, strlen(linea));
            }
            fclose(file2);

            close(fd2[1]);
        }

    }else{
        close(fd1[1]);
        close(fd2[1]);

        char linea[1024];
        int n_lineas_file1, n_lineas_file2, tam_linea, n;

        read(fd1[0], &n_lineas_file1, sizeof(int));
        char lectura1[n_lineas_file1][1024];

        // printf("El padre leyo: \n");

        for (int k=0; k<n_lineas_file1; k++){
            read(fd1[0], &tam_linea, sizeof(int));
            n = read(fd1[0], linea, tam_linea-1);
            linea[n] = '\0';
            strcpy(lectura1[k], linea);
            // printf("%s\n", linea);
        }

        read(fd2[0], &n_lineas_file2, sizeof(int));
        char lectura2[n_lineas_file2][1024];

        for (int k=0; k<n_lineas_file2; k++){
            read(fd2[0], &tam_linea, sizeof(int));
            n = read(fd2[0], linea, tam_linea-1);
            linea[n] = '\0';
            strcpy(lectura2[k], linea);
            // printf("%s\n", linea);
        }

        for (int a=0; a< n_lineas_file1 + n_lineas_file2; a++){
            if (a < n_lineas_file1) printf("%s\n", lectura1[a]);;
            if (a < n_lineas_file2) printf("%s\n", lectura2[a]);;
        }




        close(fd1[0]);
    }

    if(padre==getpid()){
        char b[500];
        sprintf(b,"pstree -lp %d",getpid());
        system(b);
        // for( i = 0; i < 3; i++) wait(NULL);
    }else{
        sleep(3);
    }

    return (0);
}
