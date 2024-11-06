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



void producer()
{
    printf("Producer was born!\n");
 
    while(1) {    

        while (*counter == 5);       
        
         data[in] = (char) in + 0x61;  
         printf("Stored... %c  Element %d  Counter %d\n", data[in],in,*counter);
       
         (*counter)++;
      
         in = ++in % REP;
    }
       
}
 

 
void main()
{
    printf("The Producer x Consumer Problem\n");
    int status;
    in = 0;
     
    key = ftok("/home", 'A');                       //  Segmento 1 
    shmid = shmget(key, 1024, 0644 | IPC_CREAT);   //
    data = (malloc(REP*sizeof(char)));            //            
    data = shmat(shmid, (void *)0, 0);           //
    
    
    key = ftok("/home/downloads", 'B');                         //  Segmento 2
    counterid = shmget(key, sizeof(int), 0644 | IPC_CREAT);    //    
    counter = shmat(counterid, (void *)0, 0);                 //  
    
    *counter = 0;
         
    signal(SIGINT, exit);  
          
    producer();       
       
    
}
