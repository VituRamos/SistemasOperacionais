/*Escrever um programa C que cria uma árvore de 3 processos, onde o processo A faz um fork() criando um processo B, o processo B, por sua vez, faz um fork() criando um processo C.
Cada processo deve exibir uma mensagem "Eu sou o processo XXX, filho de YYY", onde XXX e YYY são PIDs de processos.
Utilizar wait() para garantir que o processo C imprima sua resposta antes do B, e que o processo B imprima sua resposta antes do A.
Utilizar sleep() (man 3 sleep) para haver um intervalo de 1 segundo entre cada mensagem impressa.*/

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){

    int pId;
    pId = fork();
    
    //Processo Pai / Erro primeiro fork
    if(pId < 0){                                    

        printf("Erro na chamada fork 1");
        
    //Proocesso filho
    }else if(pId == 0){                             
        
        
        pId = fork();

            //Processo filho / Erro no segundo fork
            if (pId < 0){

                printf("Erro na chamada fork 1\n");

            //Processo neto
            }else if (pId == 0){                    

                sleep(1);
                printf("Eu sou o processo C, PID %d\n", getpid()); 

            //Processo filho
            }else{

            wait(NULL);
            sleep(1);
            printf("Eu sou o processo B, PID %d\n", getpid()); 

            }
    
    //Processo Pai
    }else{                                           
     
        wait(NULL);
        sleep(1);
        printf("Eu sou o processo A, PID %d\n", getpid()); 

    }
   
    return 0;

}
