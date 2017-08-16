#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>


int Contador ( int num, int k,int c){

  if(num > 10){

    if(k == num%10){
        c++;
    }
        num = num/10;

        return Contador(num, k, c);

  }
  else{

    if( k == num){
        c++;
    }
    return c;
  }
}

int main(){
    int k, num, c;
    scanf(" %d %d", &num, &k);

    c = Contador(num, k ,0);

    printf(" %d", c);

    return 0;
}
