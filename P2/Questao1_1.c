// Exercício 1: Faça um programa utilizando o posix do linux que faça dois processos filhos enviarem mensagem para um mesmo pai por meio de PIPES.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

char *mensagem1 = "Mensagem enviada do filho 1";
char *mensagem2 = "Mensagem enviada do filho 2";
char buffer1[1024];
char buffer2[1024];

int main() {
    
    int processo;
    int PIPE1[2];   //pipe1
    int PIPE2[2];   //pipe2

    pipe(PIPE1);    //Criação do pipe1
    pipe(PIPE2);    //Criação do pipe2  

    processo = fork();

    // Processo filho
    if (processo == 0) {

        //Processo filho 1
        if (fork() != 0) {

            // Escrever mensagem1 no pipe
            close(PIPE1[0]);                                         // Fechar a leitura do primeiro pipe no filho 1
            write(PIPE1[1], mensagem1, strlen(mensagem1) + 1);
            close(PIPE1[1]);                                         // Fechar a escrita do primeiro pipe no filho 1
            exit(EXIT_SUCCESS);                                      // Terminate o processo filho 1

        } else {

            //Processo filho 2
            close(PIPE2[0]);                                         // Fechar a leitura do segundo pipe no filho 2
            write(PIPE2[1], mensagem2, strlen(mensagem2) + 1);
            close(PIPE2[1]);                                         // Fechar a escrita do segundo pipe no filho 2
            exit(EXIT_SUCCESS);                                      // Terminate o processo filho 2
        }

    } else {

        wait(NULL);                                                 // Aguardar o término do primeiro filho

        // Receber string do pipe
        close(PIPE1[1]);                                            // Fechar a escrita do primeiro pipe no pai
        read(PIPE1[0], buffer1, 1024);
        printf("String recebida do filho 1: %s\n", buffer1);
        close(PIPE1[0]);                                            // Fechar a leitura do primeiro pipe no pai

        close(PIPE2[1]);                                            // Fechar a escrita do segundo pipe no pai
        read(PIPE2[0], buffer2, 1024);
        printf("String recebida do filho 2: %s\n", buffer2);
        close(PIPE2[0]);                                            // Fechar a leitura do segundo pipe no pai
    }

    return 0;
}
