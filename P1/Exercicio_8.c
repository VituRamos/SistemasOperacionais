/*A seguinte informação: "processos pai e filho compartilham código, mas não dados";
é verdadeira? Demonstre a sua resposta com um programa - exemplo.*/

/*A frase é verdadeira visto que pai e filho podem compartilhar o mesmo programa executável, porém, eles
possuem espacos de enderecamento diferentes. Dessa forma eles nao compartilham dados diretamente*/

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){

int pai_variavel = 10;

    int pid;

    pid = fork();

    if (pid == 0) { // Este trecho é executado no processo filho

        printf("Processo filho - ID: %d\n", getpid());
        printf("Variável no processo filho: %d\n", pai_variavel);

        pai_variavel = 20; // Modifica a variável no processo filho
        printf("Variável no processo filho (após a modificação): %d\n", pai_variavel);

    } else if (pid > 0){ // Este trecho é executado no processo pai

        printf("Processo pai - ID: %d\n", getpid());
        printf("Variável no processo pai: %d\n", pai_variavel);

    }else{

        printf("Erro no fork");

    }

    // Saída final após a execução de ambos os processos
    printf("Variável no processo pai (após a execução do processo filho): %d\n", pai_variavel);

    return 0;

}
