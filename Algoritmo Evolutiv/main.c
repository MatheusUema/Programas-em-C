#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Algoritmo Evolutivo */
/* Explicação : Este algoritmo funciona dessa forma: primeiro nós definimos uma função que irá determinar o valor, y, de cada
indivíduo, x. Dessa forma, cada indivíduo possui uma identidade representada por um número de 1 a 40 e cada x tem um determinado
valor y calculado pela função. Após isso, nós geramos 5 indivíduos aleatórios e procuramos qual o indivíduo de maior valor (indiv
max ) dentre esses 5 individuos do grupo.
                Tendo esse indiv max, nós usamos ele para "reproduzir-se" com os outros individuos do grupo a fim de evoluir
o valor de cada um da seguinte forma, fazemos a média do valor dos dois, gerando um filho. Esse filho vai ter um valor mais
próximo do valor do indiv max de forma que o grupo, a medida que vai se reproduzindo, vai se aproximando do indiv max,
constituindo com o tempo um grupo apenas de indivíduos máximos(ou com o valor mais próximo possível do maximo).
                Por fim, o algoritmo tem como objetivo evoluir um grupo qualquer de individuos em um grupo no qual seus valores
são os máximos possíveis determinados pela função.  */


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

    //Funçao que mistura os individuos com o individuo de maior valor

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
    /* Determinando variáveis */

    int pop_inicial[5], geracao[5];  //População inicial e Gerações posteriores
    int i, j, valor, MaiorValor = 0, indiv_max, var, dif;
    float media;  //média da população
    int a = 0;

    srand(time(NULL));  //função random

    for (i = 0; i < 5; i++)
        {
        pop_inicial[i] = rand()%40;    //Determina indivíduos aleatórios na população inicial

        Pop(pop_inicial[i]);           //Atribui os valores(y) de cada individuo

        printf("Individuo %d %d ",a, pop_inicial[i]);//Imprime os individuos pra população inicial

        /* Identificando qual o indivíduo de maior valor na população inicial */

        valor = Pop(pop_inicial[i]);   //Identifica qual individuo da população é o de valor máximo

        if(valor >= MaiorValor)
            {
            MaiorValor = valor;
            indiv_max = pop_inicial[i];
            j = i;
            }
        a++;

    }
    printf("\n\n");

    printf(" indiv_max  %d \n", indiv_max);  //Imprime qual é o indivíduo de maior valor

    geracao[j] = indiv_max;     //Guarda o indivíduo máximo na nova geração de individuos

    a = 0; // contador de gerações

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
        for( i = 0; i < 5; i++)     //Calculador da novo indivíduo mais forte
        {
            valor = Pop(geracao[i]);
            if(valor >= MaiorValor)
            {
            MaiorValor = valor;
            indiv_max = geracao[i];
            j = i;
            }
        }

        for( i = 0; i < 5; i++)     //Gerador da nova geração
        {
            geracao[i] = Transa(indiv_max, geracao[i]);
            printf(" filho %d %d   ",a+1 ,geracao[i]);
        }

        printf(" indiv_max  %d \n", indiv_max);  //Imprime novo indivíduo mais forte
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
