#include <stdio.h>
#include <string.h>

struct Persona {
    int id;
    char nombre[50];
    char apellido[50];
    int edad;
};

int main(){

    struct Persona personas[2];

    personas[0].id = 1000;
    strcpy(personas[0].nombre, "Juan");
    strcpy(personas[0].apellido, "Meza");
    personas[0].edad = 18;

    personas[1].id = 2030;
    strcpy(personas[1].nombre, "Ana");
    strcpy(personas[1].apellido, "de Armas");
    personas[1].edad = 21;

    for (int i=0; i<2; i++){
        printf("Persona %d\n", personas[i].id);
        printf("\tNombre: %s\n", personas[i].nombre);
        printf("\tApellido: %s\n", personas[i].apellido);
        printf("\tEdad: %d\n", personas[i].edad);
    }

    return 0;

}
