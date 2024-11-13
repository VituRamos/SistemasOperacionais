#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <string.h>

void listar() {
    if (fork() == 0) {
        execl("/bin/ls", "ls", NULL); //Syscall para ls
        exit(0);
    } else {
        wait(NULL);
    }
}

void processos() {
    if (fork() == 0) {
        execl("/bin/ps", "ps", NULL); //Syscall para ps
        exit(0);
    } else {
        wait(NULL);
    }
}

void socorro() {
    printf("Comandos disponíveis:\n");
    printf("1. listar - Lista todos os arquivos do diretório\n");
    printf("2. processos - Exibe informações sobre os processos\n");
    printf("3. sair - Encerra o shell\n");
    printf("4. socorro - Exibe os comandos disponíveis\n");
}

int main() {
    key_t key;
    int shm_id;
    char *shm_ptr;
    char input[20];

    // Criação da memória compartilhada
    key = ftok(".", 'A');
    shm_id = shmget(key, 1024, 0644);
    shm_ptr = shmat(shm_id, NULL, 0);

    while (1) {
        printf("Digite um comando: ");
        scanf("%s", input);

        if (strcmp(input, "listar") == 0) {
            strcpy(shm_ptr, "Comando executado: listar\n");
            listar();
        } else if (strcmp(input, "processos") == 0) {
            strcpy(shm_ptr, "Comando executado: processos\n");
            processos();
        } else if (strcmp(input, "socorro") == 0) {
            socorro();
        } else if (strcmp(input, "sair") == 0) {
            printf("Memória compartilhada: %s\n", shm_ptr); // Exibe o conteúdo da memória compartilhada
            break;
        } else {
            printf("Comando não reconhecido.\n");
        }
    }

    // Libera a memória compartilhada
    shmdt(shm_ptr);
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}