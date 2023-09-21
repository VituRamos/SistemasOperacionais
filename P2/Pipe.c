#include <stdlib.h>
#include <stdio.h>

int main(){

int pp[2];
pipe(pp);

char buf[1024];
int pid = fork();

if (pid==0)
{
    
    write(pp[1],"Hello\n",8);

}else{

    read(pp[0],buf,1024);
    printf("Mensagem recebida do filho: %s",buf);
}



    return 0;
}
