#include <stdio.h>
#include <stdlib.h>

int calc(int x, int n){
    if(n == 0){
        return 1;
    }
    else{
        return x*calc(x, n-1);
    }
}


int main()
{
    int x, n;

    scanf(" %d %d", &x, &n);

    int pow;
    pow = calc(x, n);

    printf(" %d", pow);

    return 0;
}
