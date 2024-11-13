#include <unistd.h> 
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void main(){

int pid;
pid = fork();


if (pid > 0){                   //Processo pai

   printf("Processo Pai");

}else if (pid == 0){            //Processo filho

   printf("Processo filho");
   execlp("ps", "ps", "-e", NULL);

}else{                          //Erro na criação de fork

    printf("Deu ruim");
}

}