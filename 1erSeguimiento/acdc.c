#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>

struct individuo {
    double f1, f2, fitness;
};

void manejador(){}

void imprimir(struct individuo individuos[], int size){
    int lim;
    if (size >= 10) lim = 10;
    else lim = size;

    for (int a=0; a<lim; a++){
        printf("Individuo %d: \n", a+1);
        printf("\tFeature 1: %.2f", individuos[a].f1);
        printf("\tFeature 2: %.2f", individuos[a].f2);
        printf("\tFitness  : %.2f\n", individuos[a].fitness);
    }
    printf("\n");
}

double getFitness(double f1, double f2){
    return (f1*f2)/2;
}

void ordenar(struct individuo individuos[], int size){
    struct individuo aux;
    for (int a=0; a<size-1; a++){
        for (int b=a+1; b<size; b++){
            if (individuos[a].fitness < individuos[b].fitness){
                aux = individuos[a];
                individuos[a] = individuos[b];
                individuos[b] = aux;
            }
        }
    }
}

int main(){
    system("clear");
    int np; //numero de procesos
    int k; // numero de evoluciones
    int ni; // numero de individuos

    printf("Ingrese la cantidad de procesos: ");
    scanf("%d", &np);
    printf("Ingrese la cantidad de evoluciones: ");
    scanf("%d", &k);
    printf("Ingrese la cantidad de individuos: ");
    scanf("%d", &ni);

    if (ni%np != 0){
        printf("Saliendo: El numero de individuos no es divisible exactamente por el numero de procesos\n" );
        exit(-1);
    }

    signal(SIGUSR1, manejador);

    int i, shm_id;
    struct individuo *individuos;
    shm_id = shmget(IPC_PRIVATE, ni*sizeof(struct individuo), 0600);
    individuos = shmat(shm_id, 0, 0);

    pid_t childs[np], root = getpid();
    for (i=0; i<np; i++) if ( !(childs[i] = fork()) ) break;
    srand (getpid());

    for (int e=0; e<k; e++){
        if (i == np){
            if (e == 0) sleep(2);
            // printf("1 root pid=%d  i=%d\n", getpid(), i);
            for (int a=0; a<np; a++) kill(childs[a], SIGUSR1);
            pause();
            // printf("2 root pid=%d  i=%d\n", getpid(), i);
            printf("\t\t\t\tGeneracion %d\n", e+1);
            ordenar(individuos, ni);
            imprimir(individuos, ni);
        }else{
            pause();
            // printf("child %d [%d]\n", i+1, getpid());
            int segmento = ni/np;
            int inicio = segmento*i;
            int fin = inicio + segmento;
            for (int a=inicio; a<fin; a++){
                individuos[a].f1 = rand() % 91 + 10; // numero aleatorio entre 10 y 100
                individuos[a].f2 = rand() % 91 + 10;
                individuos[a].fitness = getFitness(individuos[a].f1, individuos[a].f2);
            }

            if (i == np-1){
                sleep(0.2) ;
                kill(getppid(), SIGUSR1);
            }
        }
        if (e == k-1){
            shmdt(individuos);
            if (i == np ) shmctl(shm_id, IPC_RMID, 0);
        }
    }

    if(root==getpid()){
        char b[500];
        sprintf(b,"pstree -lp %d",getpid());
        system(b);
    }else sleep(3);

    return 0;
}
