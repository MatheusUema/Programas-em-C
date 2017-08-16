#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Algoritmo Evolutivo */
/* Explica��o : Este algoritmo funciona dessa forma: primeiro n�s definimos uma fun��o que ir� determinar o valor, y, de cada
indiv�duo, x. Dessa forma, cada indiv�duo possui uma identidade representada por um n�mero de 1 a 40 e cada x tem um determinado
valor y calculado pela fun��o. Ap�s isso, n�s geramos 5 indiv�duos aleat�rios e procuramos qual o indiv�duo de maior valor (indiv
max ) dentre esses 5 individuos do grupo.
                Tendo esse indiv max, n�s usamos ele para "reproduzir-se" com os outros individuos do grupo a fim de evoluir
o valor de cada um da seguinte forma, fazemos a m�dia do valor dos dois, gerando um filho. Esse filho vai ter um valor mais
pr�ximo do valor do indiv max de forma que o grupo, a medida que vai se reproduzindo, vai se aproximando do indiv max,
constituindo com o tempo um grupo apenas de indiv�duos m�ximos(ou com o valor mais pr�ximo poss�vel do maximo).
                Por fim, o algoritmo tem como objetivo evoluir um grupo qualquer de individuos em um grupo no qual seus valores
s�o os m�ximos poss�veis determinados pela fun��o.  */


int mut;
int Pop(int individuo){
    int valor;

    // y = 20x

    if( individuo >= 0 && individuo <= 20){
        valor = individuo;
    }

    // y = -x + 40

    else if( individuo > 20 && individuo <= 40){
        valor = -individuo + 40;
    }

    return valor;
}

int Transa(int Melhor, int Indiv){

    //Fun�ao que mistura os individuos com o individuo de maior valor

    int mutacao;
    mutacao = rand()%100; //determinando um numero aleatorio entre 0 e 100 para a variavel mutacao

    //A mutacao tem 15% de chance de acontecer

    if(mutacao <= 15)
    {
        mutacao = 3;   //quando ocorre mutacao, varia-se o filho em 3
    }
    else
    {
        mutacao = 0;
    }

    //Momento de realizacao da mistura dos individuos

    int filho;
    filho = ((Melhor + Indiv)/2 + mutacao);  //---->Transa

    return filho;

}

int main()
{
    /* Determinando vari�veis */

    int pop_inicial[5], geracao[5];  //Popula��o inicial e Gera��es posteriores
    int i, j, valor, MaiorValor = 0, indiv_max, var, dif;
    float media;  //m�dia da popula��o
    int a = 0;

    srand(time(NULL));  //fun��o random

    for (i = 0; i < 5; i++)
        {
        pop_inicial[i] = rand()%40;    //Determina indiv�duos aleat�rios na popula��o inicial

        Pop(pop_inicial[i]);           //Atribui os valores(y) de cada individuo

        printf("Individuo %d %d ",a, pop_inicial[i]);//Imprime os individuos pra popula��o inicial

        /* Identificando qual o indiv�duo de maior valor na popula��o inicial */

        valor = Pop(pop_inicial[i]);   //Identifica qual individuo da popula��o � o de valor m�ximo

        if(valor >= MaiorValor)
            {
            MaiorValor = valor;
            indiv_max = pop_inicial[i];
            j = i;
            }
        a++;

    }
    printf("\n\n");

    printf(" indiv_max  %d \n", indiv_max);  //Imprime qual � o indiv�duo de maior valor

    geracao[j] = indiv_max;     //Guarda o indiv�duo m�ximo na nova gera��o de individuos

    a = 0; // contador de gera��es

    for( i = 0; i < 5; i++){

        if(i != j){
            geracao[i] = Transa(indiv_max, pop_inicial[i]);
        }
        printf(" filho 0 %d   ", geracao[i]);
    }

    printf(" \n\n");

    for( i = 0; i < 5; i++)
    {
        media = (media + geracao[i])/5;
    }

    while(dif > 2)           //gerador de populacoes novas enquanto a condicao de parada nao se realiza
    {

        dif = 0;
        media = 0;
        MaiorValor = 0;
        for( i = 0; i < 5; i++)     //Calculador da novo indiv�duo mais forte
        {
            valor = Pop(geracao[i]);
            if(valor >= MaiorValor)
            {
            MaiorValor = valor;
            indiv_max = geracao[i];
            j = i;
            }
        }

        for( i = 0; i < 5; i++)     //Gerador da nova gera��o
        {
            geracao[i] = Transa(indiv_max, geracao[i]);
            printf(" filho %d %d   ",a+1 ,geracao[i]);
        }

        printf(" indiv_max  %d \n", indiv_max);  //Imprime novo indiv�duo mais forte
        printf( " \n\n");

        for( i = 0; i < 5; i++)
        {
            var = geracao[i] - indiv_max;
            if( var != 0)
                {
                dif++;
                }
        }
        a++;
    }

    return 0;
}
