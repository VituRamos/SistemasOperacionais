// 2) Construa um “pipeline”. Crie um programa que conecte 4 processos através de 3 pipes. Utilize fork() para criar vários processos. 
// Mande uma mensagem do quarto processo e faça a mensagem viajar pelos pipes  até chegar no primeiro processo, e exiba a mensagem.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h> 
#include <unistd.h>
#include <sys/wait.h>

char *mensagem = "Mensagem TOP";

int main(){

    char buffer[1024]; // Buffer mensagem
    int pipe1[2]; // Criação do pipe1
    int pipe2[2]; // Criação do pipe2
    int pipe3[2]; // Criação do pipe3

    // Inicializar os pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1 || pipe(pipe3) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int filho;

    // Criação de processos
    filho = fork();

    // Erro fork
    if (filho == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Processo filho
    if (filho == 0){

        filho = fork();

        // Processo neto
        if (filho == 0)
        {

            filho = fork();

            // Processo Bisneto
            if (filho == 0)
            {

                printf("Mensagem sendo enviada pelo bisneto\n");
                write(pipe1[1], mensagem, strlen(mensagem) + 1);
                exit(0);

            // Processo neto    
            } else {
                wait(NULL);

                read(pipe1[0], buffer, sizeof(buffer));
                printf("Mensagem sendo recebida pelo neto e sendo enviada para o filho: %s\n", buffer);
                write(pipe2[1], buffer, strlen(buffer) + 1);
                exit(0);
            }

        // Processo filho
        } else {
            wait(NULL);
            read(pipe2[0], buffer, sizeof(buffer));
            printf("Mensagem sendo recebida pelo filho e sendo enviada para o pai: %s\n", buffer);
            write(pipe3[1], buffer, strlen(buffer) + 1);
            exit(0);
        }

    // Processo pai
    } else {

        read(pipe3[0], buffer, sizeof(buffer));
        printf("Mensagem sendo recebida pelo pai: %s\n", buffer);
        exit(0);
    }

    return 0;
}
