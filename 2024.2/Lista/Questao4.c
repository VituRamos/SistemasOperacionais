#include <unistd.h> 
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void main(){

int pid;
pid = fork();

if (pid > 0){ //Pai
    wait();
    sleep(1);
    printf("Eu sou o processo %d, filho de %d\n",getpid(),getppid());

}else if (pid == 0){ //filho

    pid = fork();

    if (pid > 0 ){}//filho
    else if (pid == 0){ //Processo neto
       printf("Eu sou o processo %d, filho de %d\n",getpid(),getppid());
       exit(0);
    }

    wait();
    sleep(1);
    printf("Eu sou o processo %d, filho de %d\n",getpid(),getppid());

}else{
    printf("Erro");
}

}