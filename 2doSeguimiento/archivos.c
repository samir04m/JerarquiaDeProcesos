#include <stdio.h> //IO
#include <stdlib.h> // manejo de archivos

int main(){

    FILE *archivo = fopen("prueba.txt", "r");

    if (!archivo){
        printf("Erro al abrir el archivo\n");
        exit(-1);
    }

    fseek(archivo, 0, 2);
    int tam = ftell(archivo);
    fseek(archivo, 0, 0);

    tam -= 1; // porque siempre toma un espacion en blanco al final

    char lectura[tam];

    for (int i=0; i<tam; i++){
        lectura[i] = getc(archivo);
        printf("En la Posicion %d esta %c\n", i, lectura[i]);
    }

    fclose(archivo);

    return 0;
}
