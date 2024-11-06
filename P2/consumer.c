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
int shmid, counterid;
char *data;
int  *counter;
int in;



void exit(int signum){

    shmdt(data);                              //segmento 3  
    shmctl(shmid, IPC_RMID, NULL);           //
    
    exit(0);
}



void consumer()
{
    printf("Producer was born!\n");
 
    while(1) {    

        while (*counter == 0);       
        
         dado = data[in];
           
         data[in] = ' ';     //consume
           
         printf("Consumed... %c Element %d\n", dado, in);
           
         (*counter)--;
       
      
         in = ++in % REP;
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
    
         
    signal(SIGINT, exit);  
          
    consumer();       
       
    
}
