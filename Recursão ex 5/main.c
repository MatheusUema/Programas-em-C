#include <stdio.h>
#include <stdlib.h>

int mdc(int x, int y){
    if(x > y){
        return mdc(x-y, y);
    }
    else if( y > x){
        return mdc(y, x);
    }
    else if( x == y){
        return x;
    }
}

int main()
{
    int x, y;
while(1){
    scanf("%d  %d",&x, &y);

    int lol;
    lol = mdc(x, y);

    printf(" %d", lol);
    }

}
