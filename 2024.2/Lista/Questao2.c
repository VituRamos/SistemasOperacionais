#include <unistd.h> 
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

int count;
char charaux;

void handlerALRM(int signum){
    write(1, "\nDemorou para responder. Saindo do programa...\n", 48);
    exit(0);
}

void handlerINT(int signum){
    count++;

    if (count==3)
    {
        write(1, "\nRealmente deseja sair? [Y/n]:", 31);
        alarm(20);
        read(0,&charaux,sizeof(char));

        if (charaux == 'Y')
        {
            exit(0);
        }else if (charaux == 'n')
        {
            count = 0;
            alarm(0);
            write(1, "\nContinuando...\n", 17);
        }
        
    }
    
}

void handlerTSTP(int signum){
    int intaux = count + '0';
	write(1, "\nctrl+c apertado '", 18);
    write(1,&intaux,1);
    write(1, "' vezes\n",8);
}


int main(int argc, char* argv[])
{

    signal(SIGALRM,handlerALRM);
    signal(SIGINT,handlerINT);
    signal(SIGTSTP,handlerTSTP);
 
  while(1){}  
  return 0;


}