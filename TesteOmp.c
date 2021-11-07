/*
1)  Crie um programa em C que multiplica todos os elementos de um array por 4 ou por um valor fornecido pelo usuário
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>


#define size 1000000000 //Tamanho do vetor a ser executado
int *vector;
int fim;

void function();

int main(int argc, char* argv[])
{   

    printf("Criando o vetor...\n");
    int i = 0;//, fim = 0;
    int max = size;
    vector = malloc(max * sizeof(unsigned long));

    for(i = 0; i < max; i++){
        *(vector + i) = i+1;
    }
    printf("Inicioando o programa...\n");

    int thread_count = strtol(argv[1],NULL,10);
    #pragma omp parallel num_threads(thread_count) 
    function();

    printf("Finalizado...\n");
    //printf("Result -> %lu \n",vector[size]);
    /*
    for(int i = 0; i < size; i++){
        printf("%d, ",vector[i]);
    }
    printf("\n");
    */

    free(vector);
	return 0;
}

void function()
{
  int f = 0;  
  int idThread = omp_get_thread_num();
  int sizeThread = omp_get_num_threads();
   do{ 

        *( vector +  (f + idThread * (size/sizeThread))  ) = *( vector +  (f + idThread * (size/sizeThread))  ) * 4;
        //printf("%d\n",*( vector +  (f + idThread * (size/sizeThread))  ));
        f++;
        //printf("Thread - %d, resultado %d \n",idThread,vector[idThread+sizeThread*fim]);
//   }while(vector[size] != size + 1);
    }while(f < size/sizeThread);
}
