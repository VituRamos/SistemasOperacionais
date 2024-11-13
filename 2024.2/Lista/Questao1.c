/*Faça um programa para disparar uma mensagen de bons estudos a cada 10 segundos utilizando a API posix do linux.*/

#include <unistd.h> 
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void handlerAL(int signum){
    write(1,"Bons estudos!\n",14);
}

int main(){

    signal(SIGALRM,handlerAL);

    while(1){
        alarm(10);
        pause();
    }

    return 0;
}