/*
1)  Crie um programa em C que multiplica todos os elementos de um array por 4 ou por um valor fornecido pelo usuário
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define lenght 1000000000 //Tamanho do vetor a ser executado
int *vector;
long sizeThread;

/*
  Minha thread onde eu multiplico 4 pelo valor
  do array
*/

void *myThreadFun(void *vargp);

/*
  Main onde é criado as 4 threads 
*/

int main(int argc, char* argv[])
{
    //Vetor --------------------------
    printf("Criando o vetor...\n");
    int i = 0;
    int max = lenght;
    vector = malloc(max * sizeof(int));
    
    for(i; i < max; i++){
        *(vector + i) = i+1;
    }
    //Vetor --------------------------

    printf("Inicioando o programa...\n");
    //Inicialização....
    sizeThread = atoi(argv[1]);
    int * arg = malloc(sizeof(int) * sizeThread);
    pthread_t * threads = malloc (sizeof(pthread_t) * sizeThread);
    for(int j = 0 ;j < sizeThread ;j++){
        *(arg + j) = j;
        pthread_create(&threads[j], NULL, myThreadFun, &arg[j]);
    }

    for(int k = 0 ;k < sizeThread ;k++){
        pthread_join(threads[k], NULL);
    }
    free(threads);


    printf("Finalizado...\n");

    /*
    for(int x = 0 ;x < lenght ;x++){
        printf("size -> %d \n",vector[x]);
    }
    */

    free(vector);
    return 0;
}

void *myThreadFun(void *vargp)
{
    int flag = 0;
    int *getArg = (int *)vargp;
    int myid = getArg[0];

    do{
      *( vector +(flag + myid * (lenght/sizeThread))  ) = *( vector +  (flag + myid * (lenght/sizeThread))  ) * 4;
      flag++;
    }while(flag < lenght/sizeThread);
}
