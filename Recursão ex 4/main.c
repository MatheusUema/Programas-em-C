#include <stdio.h>
#include <stdlib.h>


int binario(int x, int n){
    if(x != 0){
        if(x%2 == 0){
            return 0*pow(10,n)+ binario(x/2, n+1);
        }
        else if(x%2 == 1){
            return 1*pow(10,n) + binario(x/2, n+1);
        }
    }
    else if(x == 0){
        return 0;
    }
}

int main()
{

while(1){
    int x;
    scanf(" %d", &x);

    int bi;
    bi = binario(x, 0);
    printf(" %d", bi);
    printf("\n");


    }

}
