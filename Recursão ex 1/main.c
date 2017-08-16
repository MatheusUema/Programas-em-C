#include <stdio.h>
#include <stdlib.h>
#define max 100

int tam;

int v[];

int Inverte( int v[], int tam){
    int i;
    if(tam < 0){
        return 0;
    }
    else{
        printf(" %d", v[tam]);

    }
}

int main()
{
    scanf(" %d", &tam);
    int v[tam];

    int i;
    for( i=0; i < tam; i++){
        scanf(" %d", &v[tam]);
    }

    Inverte( v[tam-1], tam);
    return 0;
}

