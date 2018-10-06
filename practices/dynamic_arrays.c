#include <stdio.h>
#include <stdlib.h> //importante para usar malloc
#include <string.h>

int main(){
    char text[25], *p_text;
    int longitud;

    strcpy(text, "tengo mas del tamanio deseado");
    longitud = strlen(text);

    printf("%d\n", longitud);

    p_text = malloc((longitud)*sizeof(char));

    strcpy(p_text, text);

    printf("Text: %s\n", p_text);

    return 0;
}
