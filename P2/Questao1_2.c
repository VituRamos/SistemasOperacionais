// Exercício 2: Shared Memory, Complete o código a seguir para que os processos pai e filho possam compartilhar um segmento de memória.
// O filho escreve no segmento e o pai imprime na tela o conteúdo da mensagem.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main()
{

    key_t key;
    int shmid;
    char *segmento;
    int modo, processo;

    /* Criar a chave: */
    // ftok -> Chave de identificação que recebe um diretório (Se retorno == -1 -> erro)
    if ((key = ftok("/sys", 'X')) == -1)
    {
        perror("ftok");
        exit(1);
    }

    /*Criar o segmento */
    // shmget e shmid ->função utilizada para criar uma área de memória compartilhada de tamanho size (Se retorno == -1 -> erro)

    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1){                           // shmget(chave de identificação, tamanho do segmento, flags de permissao)
        perror("shmget");
        exit(1);
    }

    /*Vincula o segmento de memória à variável segmento*/
    // shmat -> Anexar segmento de memória compartilhada associado
    segmento = (char *)shmat(shmid, (void *)0, 0);
    if (segmento == (char *)(-1)){
        perror("shmat");
        exit(1);
    }

    // Fork para criar um processo filho
    processo = fork();

    if (processo == 0){

        // Código do filho
        printf("Processo filho: Escrevendo no segmento de memória compartilhada\n");
        strcpy(segmento, "Olá, mundo!");

        // Desvincular do segmento no processo filho
        if (shmdt(segmento) == -1){
            perror("shmdt no filho");
            exit(1);
        }

    } else {
        // Código do pai
        wait(NULL);                                                                             // Aguardar o processo filho terminar

        printf("Processo pai: Lendo do segmento de memória compartilhada\n");
        printf("Conteúdo: %s\n", segmento);

        /* Desvincular do segmento */
        if (shmdt(segmento) == -1){
            perror("shmdt no pai");
            exit(1);
        }

        // Remover a área de memória compartilhada
        if (shmctl(shmid, IPC_RMID, NULL) == -1){
            perror("shmctl");
            exit(1);
        }
    }

    return (0);
}
