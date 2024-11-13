#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int resultado = 1;
    int status;

    for (int i = 5; i > 1; i--) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Erro no fork");
            exit(1);
        } else if (pid == 0) { // Processo filho: retorna o valor de i
            exit(i);
        } else { // Processo pai: aguarda o filho terminar e multiplica o resultado
            wait(&status);
            if (WIFEXITED(status)) {
                int valor = WEXITSTATUS(status);
                resultado *= valor;
            } else {
                perror("Erro: processo filho terminou anormalmente");
                exit(1);
            }
        }
    }

    printf("O fatorial de 5 é: %d\n", resultado);
    return 0;
}
