// 6) Sincronize o código a seguir, de maneira que o processo pai imprima apenas os números impares e o processo filho os números pares.
// Para isso utilize Semáforos. Utilize memória compartilhada para comunicação entre os processos.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <semaphore.h>

#define SHM_SIZE 1024


int main()
{

sem_t *sem;
key_t key;
int shmid;

    /* Criar a chave: */
    // Chave de identificação que recebe um diretório (Se retorno == -1 -> erro)
    if ((key = ftok("/sys", 'X')) == -1)
    {
        perror("ftok");
        exit(1);
    }

    /*Criar o segmento */
    // shmget ->função utilizada para criar uma área de memória compartilhada de tamanho size (Se retorno == -1 -> erro)
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1)
    { // shmget(chave de identificação, tamanho do segmento, flags de permissao)
        perror("shmget");
        exit(1);
    }

    sem = shmat(shmid, (void *)0, 0);
    if (sem == -1)
    {
        perror("shmat");
        exit(1);
    }


    /* I am the parent */
    if (fork() != 0)
    {

        int i;

        for (i = 0; i < 10; i = i + 2)
        {
            sem_wait(sem);
            printf("Processo pai %d \n", i);
            sem_post(sem);
            sleep(1);

        }

        /*Child code */
    }
    else
    {

        int i;

        for (i = 1; i < 10; i = i + 2)
        {
            sem_wait(sem);
            printf("Processo filho %d \n", i);a
            sem_post(sem);
        }
    }


    return 0;
}