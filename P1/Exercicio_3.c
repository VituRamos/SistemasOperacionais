/*Crie um processo para printar na tela uma lista de processos em execução no sistema.*/

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){

    int pId;
    pId = fork();
    
    if(pId > 0){                                    //Id para processo pai

        printf("Pai pid %d \n", getpid());        
    
    }else if(pId == 0){                             //Id para processo filho
           
        printf("Filho pid %d \n", getpid());
        execl("/bin/ps","bin/ps",NULL);
        
    }else{                                          //Id erro na chamada fork 
     
       printf("Erro na chamada fork\n");

    }
   
    return 0;

}
