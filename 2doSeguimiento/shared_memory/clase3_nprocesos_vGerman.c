#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main(){
    system("clear");
    int np=3, i, n=2;
    int *turno;
    int shm_id;
    int shm_size = sizeof(int);

    shm_id = shmget(IPC_PRIVATE, shm_size, IPC_CREAT | 0600);
    turno = shmat(shm_id, 0, 0);
    *turno = 0;

    pid_t root = getpid();
    int mi_turno = 0;
    for (i=0; i<np; i++) if (!fork()) break;

    if (i == 0) mi_turno = 3;
    if (i == 1) mi_turno = 2;
    if (i == 2) mi_turno = 1;

    // printf("Process i=%d mi_turno=%d [%d]\n", i, mi_turno, getpid());

    // if (getpid() != root){
        for (int v=0; v<n; v++){
            while (mi_turno != *turno){
                printf("Process %d [%d]\n", i+1, getpid());
                if (*turno == 3) *turno = 0;
                else *turno += 1;
            }
        }

    // }
    // else{
    //     while (1){
    //         if (*turno == 0){
    //             if (*nvez == n){
    //                 shmdt(turno);
    //                 shmdt(nvez);
    //                 break;
    //             }else{
    //                 printf("Soy el Padre %d\n", getpid());
    //                 *turno += 1;
    //             }
    //         }
    //     }
    // }

    if(root==getpid()){
        char b[500];
        sprintf(b,"pstree -lp %d",getpid());
        system(b);
        // for( i = 0; i < 3; i++) wait(NULL);
    }else{
        sleep(3);
    }

    return 0;
}
