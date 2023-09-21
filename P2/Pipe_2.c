#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){

int pp[2];
pipe(pp);

int pp2[2];
pipe(pp2);

int pp3[2];
pipe(pp3);

char buf[1024];
int pId = fork();

    if (pId==0)
    {   
        printf("Pai\n");
        write(pp[1],"Hello\n",8);

    }else if (pId>0){

        pId = fork();

        printf("Filho\n");
        read(pp[0],buf,1024);
        printf("Mensagem recebida do pai: %s",buf);

        if (pId==0)
        {
            printf("Filho\n");
            write(pp2[1],"Hello Pipe 2\n",13);

        }else if (pId>0){

            pId = fork();
            read(pp2[0],buf,1024);
            printf("Mensagem recebida do filho: %s",buf);

            if (pId==0)
            {
                printf("Neto\n");
                write(pp3[1],"Hello Pipe 3\n",13);

            }else if(pId>0){

                printf("Bisneto\n");
                read(pp3[0],buf,1024);
                printf("Mensagem recebida do neto: %s",buf);

            }
            

        }
        

    }

    return 0;
}
