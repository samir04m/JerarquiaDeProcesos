#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>

unsigned int sizeof_dm(int rows, int cols, size_t sizeElement){
    size_t size = rows * sizeof (void *); // index size
    size += (cols * rows * sizeElement); // Data size
    return size;
}

void create_index(void **m, int rows, int cols, size_t sizeElement){
    size_t sizeRow = cols * sizeElement;
    m[0] = m + rows;
    for (int i=1; i<rows; i++){
        m[i] = (m[i-1] + sizeRow);
    }
}

void print_matrix(char **m, int rows, int cols){
    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++){
            printf("%c\t", m[r][c]);
        }
        printf("\n");
    }
}

int main(){
    system("clear");
    int i, n, shmid_turno, *turno;
    int shmid_m, rows, cols;
    char **m;

    shmid_turno = shmget(IPC_PRIVATE, sizeof(int), 0600);
    turno = shmat(shmid_turno, 0, 0);

    FILE *f = fopen("sopa_de_letras.txt", "r");
    if (!f) exit(-1);
    fscanf(f, "%d", &n);
    rows = n; cols = n;

    size_t sizeMatrix = sizeof_dm(rows, cols, sizeof(char));
    shmid_m = shmget(IPC_PRIVATE, sizeMatrix, IPC_CREAT | 0600);
    m = shmat(shmid_m, NULL, 0);
    create_index((void*)m, rows, cols, sizeof(char));

    int pos_inicio_matriz = ftell(f)+1;
    int pos_inicio_palabras = ((n*2)*n)+pos_inicio_matriz;
    fseek(f, pos_inicio_palabras, 0); //posicionar puntero despues de la matriz

    char linea[n+1], palabras[n][n];
    int n_palabras = 0;
    while(!feof(f)){
        fgets(linea, n+1, f);
        strcpy(palabras[n_palabras], linea);
        n_palabras++;
    }
    n_palabras--; //eliminar la repeticion de la ultima linea del archivo

    *turno = n_palabras;
    pid_t root = getpid();
    char palabra[n];
    for (i=0; i<n_palabras; i++){
        if (!fork()){

            break;
        }
    }



    if(root == getpid()){
        char b[500];
        sprintf(b,"pstree -lp %d",getpid());
        system(b);
    }else sleep(3);

    if (i == n_palabras){
        printf("Padre [%d]: Matriz cargada a memoria.\n", getpid());
        fseek(f, pos_inicio_matriz, 0); //reposicionamos el cursor
        char caracter;
        int cont=0, fila=0;
        for (int a=0; a<pos_inicio_palabras-2; a++){
            caracter = fgetc(f);
            if (caracter != ' ' && caracter != '\n'){
                m[fila][cont] = caracter;
                cont++;
            }
            if (cont == n) {
                fila++;
                cont=0;
            }
        }

        print_matrix(m, n, n);

        fclose(f);
        *turno = 0;
        for (int a=0; a<n_palabras; a++) wait(NULL);
    }else{
        while (i != *turno) sleep(0.5);
        // printf("I'm process son%d [%d]\n", i+1, getpid());
        printf("El proceso %d con la palabra %s\n",getpid(), palabras[i] );
        if (i < n_palabras-1) *turno += 1;
    }


    return 0;
}
