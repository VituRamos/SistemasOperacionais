#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
 
#define SHM_SIZE 1024



const int REP = 5;
char dado;
key_t key;
int shmid, counterid, flagid, turnid;
char *data;
int  *counter;
int in;
int *flag[2];
int *turn;



void exit(int signum){

    shmdt(data);                              //segmento 3  
    shmctl(shmid, IPC_RMID, NULL);           //
    
    exit(0);
}



void consumer()
{
    printf("Consumer was born!\n");
 
    while(1) {    

        while (*counter == 0); 

        flag[0] = 0;  

        while (flag[1] && turn == 1);

        dado = data[in];
        data[in] = ' ';     //consume
        printf("Consumed... %c Element %d\n", dado, in);
        (*counter)--;
        in = ++in % REP;

        turn = 1;
        flag[0] = 1;
        
    }
       
}
 

 
void main()
{
    printf("The Producer x Consumer Problem\n");
    int status;
    in = 0;
     
    key = ftok("/home", 'A');                       //  Segmento   
    shmid = shmget(key, 1024, 0644 | IPC_CREAT);   //
    data = (malloc(REP*sizeof(char)));            //     1        
    data = shmat(shmid, (void *)0, 0);           //
    
    key = ftok("/home/downloads", 'B');                          //  Segmento   
    counterid = shmget(key, sizeof(int), 0644 | IPC_CREAT);     //    2
    counter = shmat(counterid, (void *)0, 0);                  //  
    
    key = ftok("/home/Documentos", 'C');                      //  Segmento   
    flagid = shmget(key, sizeof(int), 0644 | IPC_CREAT);     //    3
    flag[2] = shmat(flagid, (void *)0, 0);                  //  

    key = ftok("/home/Documentos", 'D');                      //  Segmento   
    turnid = shmget(key, sizeof(int), 0644 | IPC_CREAT);     //    4
    turn = shmat(turnid, (void *)0, 0);                     //   
         
    signal(SIGINT, exit);  
          
    consumer();       
       
    
}
