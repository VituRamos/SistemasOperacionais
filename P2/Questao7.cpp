// 7) programa abaixo manipula uma matriz de tamanho MxN (veja os defines para o tamanho da matriz). A função SumValues soma todos os valores em uma linha da matriz.
// A linha a ser somada é identificada pela variável i. Modifique o programa principal (main) nos locais indicados para:
// 1. Criar N threads, uma para somar os valores de cada linha.
// 2. Receber o resultado do somatório de cada linha e gerar o somatório total da matriz.
// 3. Analise o programa: há problemas de sincronização que precisam ser resolvidos? Se sim, resolva-os.

#include <stdio.h>
#include "thread.h"
#include <pthread.h>
#include "semaphore.h"


/*
Threads independentes, não geram inconsistência no resultado final,
no entanto os cout's parecem fora de ordem
*/


/* number of matrix columns and rows */
#define M 5
#define N 10
 
Semaphore sem;
Thread *threads[N];
int sum_total;
int matrix[N][M];
int parcial;
 
/* thread function; it sums the values of the matrix in the row */
int SumValues(int i){
    int n = (long) i; /* number of row */
    int total = 0; /* the total of the values in the row */
    int j;
    for (j = 0; j < M; j++)          /* sum values in the "n" row */
        total += matrix[n][j];
   
    printf("The total in row %d is %d  \n", n, total);
    

    /* terminate a thread and return a total in the row */
    pthread_exit((void **)total);    
}

int main(){

    sum_total = 0;
    //sem_init(sem);
    int i=1, j;
    int total = 0; /* the total of the values in the matrix */

 
     /* initialize the matrix */
    for (i = 0; i < N; i++){
        for (j = 0; j < M; j++)
            matrix[i][j] = i * M + j;
    }

    /* create threads */
    /* COLOQUE SEU CÓDIGO PARA CRIAR AS THREADS AQUI! */
    for (i = 0; i < N; i++){
        threads[i] = new Thread(&SumValues, i);
    }

      
    /* wait for terminate a threads */
    /* COLOQUE SEU CÓDIGO PARA PEGAR O SOMATÓRIO DE LINHAS E TOTALIZAR A SOMA DA MATRIZ AQUI! */
    for (i = 0; i < N; i++){
        threads[i]->join(&parcial);
        sum_total += parcial;
    }

     printf("The total values in the matrix is %d \n", sum_total);
 

    return 0;
}