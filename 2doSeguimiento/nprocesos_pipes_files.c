#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

int nbytes = 8;

int main()
{
    pid_t padre = getpid();
    int i, j, n;
    char buffer[1024];

    printf("Ingrese el numero de n procesos:");
    scanf("%d", &n);

    pid_t childs[n];
    int fd[n][2];

    for (j=0; j<n; j++) if( pipe(fd[j]) ) exit(-1);
    for (i=0; i<n; i++) if(!(childs[i] = fork())) break;

    if (getpid() != padre){
        for (j=0; j<n; j++){
            if (i != j) close(fd[j][0]);
            if ((i+1) != j) close(fd[j][1]);
        }
        int TAM;
        read(fd[i][0], &TAM, sizeof(int));
        char lectura[TAM];
        printf("lectura TAM %d\n", TAM);
        for (int j=0; j<TAM; j++){
            read(fd[i][0], &lectura[j], sizeof(char));
            printf("Process %d: leido %d: %c\n", getpid(), j, lectura[j]);
        }

        int np = nbytes/n;
        printf("TAM %d np %d\n", TAM, np);
        char lectura2[TAM-np];

        for (int k=np; k<TAM; k++){
            lectura2[k-np] = lectura[k];
            // printf("%c en %d\n", lectura[k], k);
        }
        TAM = strlen(lectura2);
        printf("lectura2  TAM %d\n", TAM);
        // read(fd[i][0], lectura, TAM);
        // printf("Tamano de la lectura %d\n", (int)strlen(lectura));
        write(fd[i+1][1], &TAM, sizeof(int));
        write(fd[i+1][1], lectura2, TAM);
        close(fd[i][0]);
        close(fd[i+1][1]);
    }else{
        close(fd[0][0]);
        for (j=1; j<n; j++){
            close(fd[j][0]);
            close(fd[j][1]);
        }
        FILE *archivo = fopen("caracteres.txt", "r");
        if (!archivo){
            printf("Erro al abrir el archivo\n");
            exit(-1);
        }
        fseek(archivo, 0, SEEK_END);
        int TAM = ftell(archivo);
        fseek(archivo, 0, 0);

        char info[TAM], info2[TAM];
        TAM -=  1;

        int restar = 0, c=0;
        for (int i=0; i<TAM; i++){
            info[i] = getc(archivo);
            if (info[i] != '\n'){
                info2[c] = info[i];
                c++;
            }else{
                restar++;
            }
        }
        fclose(archivo);

        TAM -= restar;
        nbytes = TAM;
        write(fd[0][1], &TAM, sizeof(int));
        for (int k=0; k<TAM; k++){
            printf("En la Posicion %d esta %c\n", k, info2[k]);
            write(fd[0][1], &info2[k], sizeof(char));
        }

        // info[TAM-1] = '\0';

        close(fd[0][1]);
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
