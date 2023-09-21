#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

int pID;
pID = fork();

    if (pID > 0) {

        printf("Sou o processo pai (PID: %d)\n\n", getpid());

    }else if (pID == 0){

        printf("Sou o processo filho (PID: %d), filho de (PID:%d)\n\n", getpid(),getppid());
        pID = fork();

        if (pID>0){
            printf("Neto criado\n\n");
        }
        else if (pID == 0){
            printf("Sou o processo neto (PID: %d), filho de (PID: %d)\n\n", getpid(),getppid());
        }
        else{
            printf("Erro na criacao do processo");

        }

    }

return 0;
}
