/*Um procedimento para contar o número de vezes que o usuário enviou o sinal SIGINT para o processo em execução.
Pressionar Ctl-C no teclado envia esse sinal. Quando o processo recebe o sinal SIGTSTP (Ctl-Z), ele deve imprimir no terminal o número de sinais SIGINT que recebeu.
Depois de receber 3 sinais SIGINT, o programa deve perguntar se o usuário deseja sair do programa.
Se o usuário não responder em 20 segundos, um sinal SIGALRM deve forçar a saída do programa.*/

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <wait.h>

int count;
char caux;

void handlerAL(int signum){
	
    write(1, "\nDemorou muito para responder.Saindo...\n", 40);
    exit(0);
}

void handlerINT(int signum){

	count++;

	if(count == 3){
        write(1, "\nRealmente Deseja Sair? [Y/N]: ", 31);
        alarm(20);
        read(0, &caux, sizeof(caux));

         if (caux == 'y' || caux == 'Y')
         {
            exit(0);
         }else
         {
            write(1,"\nContinuando...\n",16);
            count = 0;
         }

    };
}

void handlerTSTP(int signum){

    int iaux = count + '0';

	write(1, "\nctrl+c apertado '", 18);
    write(1,&iaux,1);
    write(1, "' vezes\n",8);

}

int main (){

    signal(SIGALRM, handlerAL);
	signal(SIGTSTP, handlerTSTP);
	signal(SIGINT, handlerINT);

    while(1){
        pause();
    }

    return 0;
}
